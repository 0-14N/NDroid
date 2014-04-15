/*
 * QEMU KVM support
 *
 * Copyright (C) 2006-2008 Qumranet Technologies
 * Copyright IBM, Corp. 2008
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#undef __user
#define __xuser  /* nothing */
#include <linux/kvm.h>

#include "qemu-common.h"
#include "sysemu.h"
#include "kvm.h"
#include "cpu.h"
#include "gdbstub.h"

#ifdef CONFIG_KVM_GS_RESTORE
#include "kvm-gs-restore.h"
#endif

//#define DEBUG_KVM

#ifdef DEBUG_KVM
#define dprintf(fmt, ...) \
    do { fprintf(stderr, fmt, ## __VA_ARGS__); } while (0)
#else
#define dprintf(fmt, ...) \
    do { } while (0)
#endif

#ifdef KVM_CAP_EXT_CPUID

static struct kvm_cpuid2 *try_get_cpuid(KVMState *s, int max)
{
    struct kvm_cpuid2 *cpuid;
    int r, size;

    size = sizeof(*cpuid) + max * sizeof(*cpuid->entries);
    cpuid = (struct kvm_cpuid2 *)qemu_mallocz(size);
    cpuid->nent = max;
    r = kvm_ioctl(s, KVM_GET_SUPPORTED_CPUID, cpuid);
    if (r == 0 && cpuid->nent >= max) {
        r = -E2BIG;
    }
    if (r < 0) {
        if (r == -E2BIG) {
            qemu_free(cpuid);
            return NULL;
        } else {
            fprintf(stderr, "KVM_GET_SUPPORTED_CPUID failed: %s\n",
                    strerror(-r));
            exit(1);
        }
    }
    return cpuid;
}

uint32_t kvm_arch_get_supported_cpuid(CPUState *env, uint32_t function, int reg)
{
    struct kvm_cpuid2 *cpuid;
    int i, max;
    uint32_t ret = 0;
    uint32_t cpuid_1_edx;

    if (!kvm_check_extension(env->kvm_state, KVM_CAP_EXT_CPUID)) {
        return -1U;
    }

    max = 1;
    while ((cpuid = try_get_cpuid(env->kvm_state, max)) == NULL) {
        max *= 2;
    }

    for (i = 0; i < cpuid->nent; ++i) {
        if (cpuid->entries[i].function == function) {
            switch (reg) {
            case R_EAX:
                ret = cpuid->entries[i].eax;
                break;
            case R_EBX:
                ret = cpuid->entries[i].ebx;
                break;
            case R_ECX:
                ret = cpuid->entries[i].ecx;
                break;
            case R_EDX:
                ret = cpuid->entries[i].edx;
                if (function == 0x80000001) {
                    /* On Intel, kvm returns cpuid according to the Intel spec,
                     * so add missing bits according to the AMD spec:
                     */
                    cpuid_1_edx = kvm_arch_get_supported_cpuid(env, 1, R_EDX);
                    ret |= cpuid_1_edx & 0xdfeff7ff;
                }
                break;
            }
        }
    }

    qemu_free(cpuid);

    return ret;
}

#else

uint32_t kvm_arch_get_supported_cpuid(CPUState *env, uint32_t function, int reg)
{
    return -1U;
}

#endif

#ifndef KVM_MP_STATE_RUNNABLE
#define KVM_MP_STATE_RUNNABLE 0
#endif

int kvm_arch_init_vcpu(CPUState *env)
{
    struct {
        struct kvm_cpuid2 cpuid;
        struct kvm_cpuid_entry2 entries[100];
    } __attribute__((packed)) cpuid_data;
    uint32_t limit, i, j, cpuid_i;
    uint32_t unused;

    env->mp_state = KVM_MP_STATE_RUNNABLE;

    cpuid_i = 0;

    cpu_x86_cpuid(env, 0, 0, &limit, &unused, &unused, &unused);

    for (i = 0; i <= limit; i++) {
        struct kvm_cpuid_entry2 *c = &cpuid_data.entries[cpuid_i++];

        switch (i) {
        case 2: {
            /* Keep reading function 2 till all the input is received */
            int times;

            c->function = i;
            c->flags = KVM_CPUID_FLAG_STATEFUL_FUNC |
                       KVM_CPUID_FLAG_STATE_READ_NEXT;
            cpu_x86_cpuid(env, i, 0, &c->eax, &c->ebx, &c->ecx, &c->edx);
            times = c->eax & 0xff;

            for (j = 1; j < times; ++j) {
                c = &cpuid_data.entries[cpuid_i++];
                c->function = i;
                c->flags = KVM_CPUID_FLAG_STATEFUL_FUNC;
                cpu_x86_cpuid(env, i, 0, &c->eax, &c->ebx, &c->ecx, &c->edx);
            }
            break;
        }
        case 4:
        case 0xb:
        case 0xd:
            for (j = 0; ; j++) {
                c->function = i;
                c->flags = KVM_CPUID_FLAG_SIGNIFCANT_INDEX;
                c->index = j;
                cpu_x86_cpuid(env, i, j, &c->eax, &c->ebx, &c->ecx, &c->edx);

                if (i == 4 && c->eax == 0)
                    break;
                if (i == 0xb && !(c->ecx & 0xff00))
                    break;
                if (i == 0xd && c->eax == 0)
                    break;

                c = &cpuid_data.entries[cpuid_i++];
            }
            break;
        default:
            c->function = i;
            c->flags = 0;
            cpu_x86_cpuid(env, i, 0, &c->eax, &c->ebx, &c->ecx, &c->edx);
            break;
        }
    }
    cpu_x86_cpuid(env, 0x80000000, 0, &limit, &unused, &unused, &unused);

    for (i = 0x80000000; i <= limit; i++) {
        struct kvm_cpuid_entry2 *c = &cpuid_data.entries[cpuid_i++];

        c->function = i;
        c->flags = 0;
        cpu_x86_cpuid(env, i, 0, &c->eax, &c->ebx, &c->ecx, &c->edx);
    }

    cpuid_data.cpuid.nent = cpuid_i;

    return kvm_vcpu_ioctl(env, KVM_SET_CPUID2, &cpuid_data);
}

static int kvm_has_msr_star(CPUState *env)
{
    static int has_msr_star;
    int ret;

    /* first time */
    if (has_msr_star == 0) {        
        struct kvm_msr_list msr_list, *kvm_msr_list;

        has_msr_star = -1;

        /* Obtain MSR list from KVM.  These are the MSRs that we must
         * save/restore */
        msr_list.nmsrs = 0;
        ret = kvm_ioctl(env->kvm_state, KVM_GET_MSR_INDEX_LIST, &msr_list);
        if (ret < 0)
            return 0;

        kvm_msr_list = qemu_mallocz(sizeof(msr_list) +
                                    msr_list.nmsrs * sizeof(msr_list.indices[0]));

        kvm_msr_list->nmsrs = msr_list.nmsrs;
        ret = kvm_ioctl(env->kvm_state, KVM_GET_MSR_INDEX_LIST, kvm_msr_list);
        if (ret >= 0) {
            int i;

            for (i = 0; i < kvm_msr_list->nmsrs; i++) {
                if (kvm_msr_list->indices[i] == MSR_STAR) {
                    has_msr_star = 1;
                    break;
                }
            }
        }

        free(kvm_msr_list);
    }

    if (has_msr_star == 1)
        return 1;
    return 0;
}

int kvm_arch_init(KVMState *s, int smp_cpus)
{
    int ret;

    /* create vm86 tss.  KVM uses vm86 mode to emulate 16-bit code
     * directly.  In order to use vm86 mode, a TSS is needed.  Since this
     * must be part of guest physical memory, we need to allocate it.  Older
     * versions of KVM just assumed that it would be at the end of physical
     * memory but that doesn't work with more than 4GB of memory.  We simply
     * refuse to work with those older versions of KVM. */
    ret = kvm_ioctl(s, KVM_CHECK_EXTENSION, KVM_CAP_SET_TSS_ADDR);
    if (ret <= 0) {
        fprintf(stderr, "kvm does not support KVM_CAP_SET_TSS_ADDR\n");
        return ret;
    }

    /* this address is 3 pages before the bios, and the bios should present
     * as unavaible memory.  FIXME, need to ensure the e820 map deals with
     * this?
     */
    return kvm_vm_ioctl(s, KVM_SET_TSS_ADDR, 0xfffbd000);
}
                    
static void set_v8086_seg(struct kvm_segment *lhs, const SegmentCache *rhs)
{
    lhs->selector = rhs->selector;
    lhs->base = rhs->base;
    lhs->limit = rhs->limit;
    lhs->type = 3;
    lhs->present = 1;
    lhs->dpl = 3;
    lhs->db = 0;
    lhs->s = 1;
    lhs->l = 0;
    lhs->g = 0;
    lhs->avl = 0;
    lhs->unusable = 0;
}

static void set_seg(struct kvm_segment *lhs, const SegmentCache *rhs)
{
    unsigned flags = rhs->flags;
    lhs->selector = rhs->selector;
    lhs->base = rhs->base;
    lhs->limit = rhs->limit;
    lhs->type = (flags >> DESC_TYPE_SHIFT) & 15;
    lhs->present = (flags & DESC_P_MASK) != 0;
    lhs->dpl = rhs->selector & 3;
    lhs->db = (flags >> DESC_B_SHIFT) & 1;
    lhs->s = (flags & DESC_S_MASK) != 0;
    lhs->l = (flags >> DESC_L_SHIFT) & 1;
    lhs->g = (flags & DESC_G_MASK) != 0;
    lhs->avl = (flags & DESC_AVL_MASK) != 0;
    lhs->unusable = 0;
}

static void get_seg(SegmentCache *lhs, const struct kvm_segment *rhs)
{
    lhs->selector = rhs->selector;
    lhs->base = rhs->base;
    lhs->limit = rhs->limit;
    lhs->flags =
	(rhs->type << DESC_TYPE_SHIFT)
	| (rhs->present * DESC_P_MASK)
	| (rhs->dpl << DESC_DPL_SHIFT)
	| (rhs->db << DESC_B_SHIFT)
	| (rhs->s * DESC_S_MASK)
	| (rhs->l << DESC_L_SHIFT)
	| (rhs->g * DESC_G_MASK)
	| (rhs->avl * DESC_AVL_MASK);
}

static void kvm_getput_reg(__u64 *kvm_reg, target_ulong *qemu_reg, int set)
{
    if (set)
        *kvm_reg = *qemu_reg;
    else
        *qemu_reg = *kvm_reg;
}

static int kvm_getput_regs(CPUState *env, int set)
{
    struct kvm_regs regs;
    int ret = 0;

    if (!set) {
        ret = kvm_vcpu_ioctl(env, KVM_GET_REGS, &regs);
        if (ret < 0)
            return ret;
    }

    kvm_getput_reg(&regs.rax, &env->regs[R_EAX], set);
    kvm_getput_reg(&regs.rbx, &env->regs[R_EBX], set);
    kvm_getput_reg(&regs.rcx, &env->regs[R_ECX], set);
    kvm_getput_reg(&regs.rdx, &env->regs[R_EDX], set);
    kvm_getput_reg(&regs.rsi, &env->regs[R_ESI], set);
    kvm_getput_reg(&regs.rdi, &env->regs[R_EDI], set);
    kvm_getput_reg(&regs.rsp, &env->regs[R_ESP], set);
    kvm_getput_reg(&regs.rbp, &env->regs[R_EBP], set);
#ifdef TARGET_X86_64
    kvm_getput_reg(&regs.r8, &env->regs[8], set);
    kvm_getput_reg(&regs.r9, &env->regs[9], set);
    kvm_getput_reg(&regs.r10, &env->regs[10], set);
    kvm_getput_reg(&regs.r11, &env->regs[11], set);
    kvm_getput_reg(&regs.r12, &env->regs[12], set);
    kvm_getput_reg(&regs.r13, &env->regs[13], set);
    kvm_getput_reg(&regs.r14, &env->regs[14], set);
    kvm_getput_reg(&regs.r15, &env->regs[15], set);
#endif

    kvm_getput_reg(&regs.rflags, &env->eflags, set);
    kvm_getput_reg(&regs.rip, &env->eip, set);

    if (set)
        ret = kvm_vcpu_ioctl(env, KVM_SET_REGS, &regs);

    return ret;
}

static int kvm_put_fpu(CPUState *env)
{
    struct kvm_fpu fpu;
    int i;

    memset(&fpu, 0, sizeof fpu);
    fpu.fsw = env->fpus & ~(7 << 11);
    fpu.fsw |= (env->fpstt & 7) << 11;
    fpu.fcw = env->fpuc;
    for (i = 0; i < 8; ++i)
	fpu.ftwx |= (!env->fptags[i]) << i;
    memcpy(fpu.fpr, env->fpregs, sizeof env->fpregs);
    memcpy(fpu.xmm, env->xmm_regs, sizeof env->xmm_regs);
    fpu.mxcsr = env->mxcsr;

    return kvm_vcpu_ioctl(env, KVM_SET_FPU, &fpu);
}

static int kvm_put_sregs(CPUState *env)
{
    struct kvm_sregs sregs;

    memcpy(sregs.interrupt_bitmap,
           env->interrupt_bitmap,
           sizeof(sregs.interrupt_bitmap));

    if ((env->eflags & VM_MASK)) {
	    set_v8086_seg(&sregs.cs, &env->segs[R_CS]);
	    set_v8086_seg(&sregs.ds, &env->segs[R_DS]);
	    set_v8086_seg(&sregs.es, &env->segs[R_ES]);
	    set_v8086_seg(&sregs.fs, &env->segs[R_FS]);
	    set_v8086_seg(&sregs.gs, &env->segs[R_GS]);
	    set_v8086_seg(&sregs.ss, &env->segs[R_SS]);
    } else {
	    set_seg(&sregs.cs, &env->segs[R_CS]);
	    set_seg(&sregs.ds, &env->segs[R_DS]);
	    set_seg(&sregs.es, &env->segs[R_ES]);
	    set_seg(&sregs.fs, &env->segs[R_FS]);
	    set_seg(&sregs.gs, &env->segs[R_GS]);
	    set_seg(&sregs.ss, &env->segs[R_SS]);

	    if (env->cr[0] & CR0_PE_MASK) {
		/* force ss cpl to cs cpl */
		sregs.ss.selector = (sregs.ss.selector & ~3) |
			(sregs.cs.selector & 3);
		sregs.ss.dpl = sregs.ss.selector & 3;
	    }
    }

    set_seg(&sregs.tr, &env->tr);
    set_seg(&sregs.ldt, &env->ldt);

    sregs.idt.limit = env->idt.limit;
    sregs.idt.base = env->idt.base;
    sregs.gdt.limit = env->gdt.limit;
    sregs.gdt.base = env->gdt.base;

    sregs.cr0 = env->cr[0];
    sregs.cr2 = env->cr[2];
    sregs.cr3 = env->cr[3];
    sregs.cr4 = env->cr[4];

    sregs.cr8 = cpu_get_apic_tpr(env);
    sregs.apic_base = cpu_get_apic_base(env);

    sregs.efer = env->efer;

    return kvm_vcpu_ioctl(env, KVM_SET_SREGS, &sregs);
}

static void kvm_msr_entry_set(struct kvm_msr_entry *entry,
                              uint32_t index, uint64_t value)
{
    entry->index = index;
    entry->data = value;
}

static int kvm_put_msrs(CPUState *env)
{
    struct {
        struct kvm_msrs info;
        struct kvm_msr_entry entries[100];
    } msr_data;
    struct kvm_msr_entry *msrs = msr_data.entries;
    int n = 0;

    kvm_msr_entry_set(&msrs[n++], MSR_IA32_SYSENTER_CS, env->sysenter_cs);
    kvm_msr_entry_set(&msrs[n++], MSR_IA32_SYSENTER_ESP, env->sysenter_esp);
    kvm_msr_entry_set(&msrs[n++], MSR_IA32_SYSENTER_EIP, env->sysenter_eip);
    if (kvm_has_msr_star(env))
	kvm_msr_entry_set(&msrs[n++], MSR_STAR, env->star);
    kvm_msr_entry_set(&msrs[n++], MSR_IA32_TSC, env->tsc);
#ifdef TARGET_X86_64
    /* FIXME if lm capable */
    kvm_msr_entry_set(&msrs[n++], MSR_CSTAR, env->cstar);
    kvm_msr_entry_set(&msrs[n++], MSR_KERNELGSBASE, env->kernelgsbase);
    kvm_msr_entry_set(&msrs[n++], MSR_FMASK, env->fmask);
    kvm_msr_entry_set(&msrs[n++], MSR_LSTAR, env->lstar);
#endif
    msr_data.info.nmsrs = n;

    return kvm_vcpu_ioctl(env, KVM_SET_MSRS, &msr_data);

}


static int kvm_get_fpu(CPUState *env)
{
    struct kvm_fpu fpu;
    int i, ret;

    ret = kvm_vcpu_ioctl(env, KVM_GET_FPU, &fpu);
    if (ret < 0)
        return ret;

    env->fpstt = (fpu.fsw >> 11) & 7;
    env->fpus = fpu.fsw;
    env->fpuc = fpu.fcw;
    for (i = 0; i < 8; ++i)
	env->fptags[i] = !((fpu.ftwx >> i) & 1);
    memcpy(env->fpregs, fpu.fpr, sizeof env->fpregs);
    memcpy(env->xmm_regs, fpu.xmm, sizeof env->xmm_regs);
    env->mxcsr = fpu.mxcsr;

    return 0;
}

static int kvm_get_sregs(CPUState *env)
{
    struct kvm_sregs sregs;
    uint32_t hflags;
    int ret;

    ret = kvm_vcpu_ioctl(env, KVM_GET_SREGS, &sregs);
    if (ret < 0)
        return ret;

    memcpy(env->interrupt_bitmap, 
           sregs.interrupt_bitmap,
           sizeof(sregs.interrupt_bitmap));

    get_seg(&env->segs[R_CS], &sregs.cs);
    get_seg(&env->segs[R_DS], &sregs.ds);
    get_seg(&env->segs[R_ES], &sregs.es);
    get_seg(&env->segs[R_FS], &sregs.fs);
    get_seg(&env->segs[R_GS], &sregs.gs);
    get_seg(&env->segs[R_SS], &sregs.ss);

    get_seg(&env->tr, &sregs.tr);
    get_seg(&env->ldt, &sregs.ldt);

    env->idt.limit = sregs.idt.limit;
    env->idt.base = sregs.idt.base;
    env->gdt.limit = sregs.gdt.limit;
    env->gdt.base = sregs.gdt.base;

    env->cr[0] = sregs.cr0;
    env->cr[2] = sregs.cr2;
    env->cr[3] = sregs.cr3;
    env->cr[4] = sregs.cr4;

    cpu_set_apic_base(env, sregs.apic_base);

    env->efer = sregs.efer;
    //cpu_set_apic_tpr(env, sregs.cr8);

#define HFLAG_COPY_MASK ~( \
			HF_CPL_MASK | HF_PE_MASK | HF_MP_MASK | HF_EM_MASK | \
			HF_TS_MASK | HF_TF_MASK | HF_VM_MASK | HF_IOPL_MASK | \
			HF_OSFXSR_MASK | HF_LMA_MASK | HF_CS32_MASK | \
			HF_SS32_MASK | HF_CS64_MASK | HF_ADDSEG_MASK)



    hflags = (env->segs[R_CS].flags >> DESC_DPL_SHIFT) & HF_CPL_MASK;
    hflags |= (env->cr[0] & CR0_PE_MASK) << (HF_PE_SHIFT - CR0_PE_SHIFT);
    hflags |= (env->cr[0] << (HF_MP_SHIFT - CR0_MP_SHIFT)) &
	    (HF_MP_MASK | HF_EM_MASK | HF_TS_MASK);
    hflags |= (env->eflags & (HF_TF_MASK | HF_VM_MASK | HF_IOPL_MASK));
    hflags |= (env->cr[4] & CR4_OSFXSR_MASK) <<
	    (HF_OSFXSR_SHIFT - CR4_OSFXSR_SHIFT);

    if (env->efer & MSR_EFER_LMA) {
        hflags |= HF_LMA_MASK;
    }

    if ((hflags & HF_LMA_MASK) && (env->segs[R_CS].flags & DESC_L_MASK)) {
        hflags |= HF_CS32_MASK | HF_SS32_MASK | HF_CS64_MASK;
    } else {
        hflags |= (env->segs[R_CS].flags & DESC_B_MASK) >>
		(DESC_B_SHIFT - HF_CS32_SHIFT);
        hflags |= (env->segs[R_SS].flags & DESC_B_MASK) >>
		(DESC_B_SHIFT - HF_SS32_SHIFT);
        if (!(env->cr[0] & CR0_PE_MASK) ||
                   (env->eflags & VM_MASK) ||
                   !(hflags & HF_CS32_MASK)) {
                hflags |= HF_ADDSEG_MASK;
            } else {
                hflags |= ((env->segs[R_DS].base |
                                env->segs[R_ES].base |
                                env->segs[R_SS].base) != 0) <<
                    HF_ADDSEG_SHIFT;
            }
    }
    env->hflags = (env->hflags & HFLAG_COPY_MASK) | hflags;

    return 0;
}

static int kvm_get_msrs(CPUState *env)
{
    struct {
        struct kvm_msrs info;
        struct kvm_msr_entry entries[100];
    } msr_data;
    struct kvm_msr_entry *msrs = msr_data.entries;
    int ret, i, n;

    n = 0;
    msrs[n++].index = MSR_IA32_SYSENTER_CS;
    msrs[n++].index = MSR_IA32_SYSENTER_ESP;
    msrs[n++].index = MSR_IA32_SYSENTER_EIP;
    if (kvm_has_msr_star(env))
	msrs[n++].index = MSR_STAR;
    msrs[n++].index = MSR_IA32_TSC;
#ifdef TARGET_X86_64
    /* FIXME lm_capable_kernel */
    msrs[n++].index = MSR_CSTAR;
    msrs[n++].index = MSR_KERNELGSBASE;
    msrs[n++].index = MSR_FMASK;
    msrs[n++].index = MSR_LSTAR;
#endif
    msr_data.info.nmsrs = n;
    ret = kvm_vcpu_ioctl(env, KVM_GET_MSRS, &msr_data);
    if (ret < 0)
        return ret;

    for (i = 0; i < ret; i++) {
        switch (msrs[i].index) {
        case MSR_IA32_SYSENTER_CS:
            env->sysenter_cs = msrs[i].data;
            break;
        case MSR_IA32_SYSENTER_ESP:
            env->sysenter_esp = msrs[i].data;
            break;
        case MSR_IA32_SYSENTER_EIP:
            env->sysenter_eip = msrs[i].data;
            break;
        case MSR_STAR:
            env->star = msrs[i].data;
            break;
#ifdef TARGET_X86_64
        case MSR_CSTAR:
            env->cstar = msrs[i].data;
            break;
        case MSR_KERNELGSBASE:
            env->kernelgsbase = msrs[i].data;
            break;
        case MSR_FMASK:
            env->fmask = msrs[i].data;
            break;
        case MSR_LSTAR:
            env->lstar = msrs[i].data;
            break;
#endif
        case MSR_IA32_TSC:
            env->tsc = msrs[i].data;
            break;
        }
    }

    return 0;
}

int kvm_arch_put_registers(CPUState *env)
{
    int ret;

    ret = kvm_getput_regs(env, 1);
    if (ret < 0)
        return ret;

    ret = kvm_put_fpu(env);
    if (ret < 0)
        return ret;

    ret = kvm_put_sregs(env);
    if (ret < 0)
        return ret;

    ret = kvm_put_msrs(env);
    if (ret < 0)
        return ret;

    ret = kvm_put_mp_state(env);
    if (ret < 0)
        return ret;

    ret = kvm_get_mp_state(env);
    if (ret < 0)
        return ret;

    return 0;
}

int kvm_arch_get_registers(CPUState *env)
{
    int ret;

    ret = kvm_getput_regs(env, 0);
    if (ret < 0)
        return ret;

    ret = kvm_get_fpu(env);
    if (ret < 0)
        return ret;

    ret = kvm_get_sregs(env);
    if (ret < 0)
        return ret;

    ret = kvm_get_msrs(env);
    if (ret < 0)
        return ret;

    return 0;
}

int kvm_arch_vcpu_run(CPUState *env)
{
#ifdef CONFIG_KVM_GS_RESTORE
    if (gs_need_restore  != KVM_GS_RESTORE_NO)
        return no_gs_ioctl(env->kvm_fd, KVM_RUN, 0);
    else
#endif
        return kvm_vcpu_ioctl(env, KVM_RUN, 0);
}

int kvm_arch_pre_run(CPUState *env, struct kvm_run *run)
{
    /* Try to inject an interrupt if the guest can accept it */
    if (run->ready_for_interrupt_injection &&
        (env->interrupt_request & CPU_INTERRUPT_HARD) &&
        (env->eflags & IF_MASK)) {
        int irq;

        env->interrupt_request &= ~CPU_INTERRUPT_HARD;
        irq = cpu_get_pic_interrupt(env);
        if (irq >= 0) {
            struct kvm_interrupt intr;
            intr.irq = irq;
            /* FIXME: errors */
            dprintf("injected interrupt %d\n", irq);
            kvm_vcpu_ioctl(env, KVM_INTERRUPT, &intr);
        }
    }

    /* If we have an interrupt but the guest is not ready to receive an
     * interrupt, request an interrupt window exit.  This will
     * cause a return to userspace as soon as the guest is ready to
     * receive interrupts. */
    if ((env->interrupt_request & CPU_INTERRUPT_HARD))
        run->request_interrupt_window = 1;
    else
        run->request_interrupt_window = 0;

    dprintf("setting tpr\n");
    run->cr8 = cpu_get_apic_tpr(env);

#ifdef CONFIG_KVM_GS_RESTORE
    gs_base_pre_run();
#endif

    return 0;
}

int kvm_arch_post_run(CPUState *env, struct kvm_run *run)
{
#ifdef CONFIG_KVM_GS_RESTORE
    gs_base_post_run();
#endif
    if (run->if_flag)
        env->eflags |= IF_MASK;
    else
        env->eflags &= ~IF_MASK;
    
    cpu_set_apic_tpr(env, run->cr8);
    cpu_set_apic_base(env, run->apic_base);

    return 0;
}

static int kvm_handle_halt(CPUState *env)
{
    if (!((env->interrupt_request & CPU_INTERRUPT_HARD) &&
          (env->eflags & IF_MASK)) &&
        !(env->interrupt_request & CPU_INTERRUPT_NMI)) {
        env->halted = 1;
        env->exception_index = EXCP_HLT;
        return 0;
    }

    return 1;
}

int kvm_arch_handle_exit(CPUState *env, struct kvm_run *run)
{
    int ret = 0;

    switch (run->exit_reason) {
    case KVM_EXIT_HLT:
        dprintf("handle_hlt\n");
        ret = kvm_handle_halt(env);
        break;
    }

    return ret;
}

#ifdef KVM_CAP_SET_GUEST_DEBUG
int kvm_arch_insert_sw_breakpoint(CPUState *env, struct kvm_sw_breakpoint *bp)
{
    const static uint8_t int3 = 0xcc;

    if (cpu_memory_rw_debug(env, bp->pc, (uint8_t *)&bp->saved_insn, 1, 0) ||
        cpu_memory_rw_debug(env, bp->pc, (uint8_t *)&int3, 1, 1))
        return -EINVAL;
    return 0;
}

int kvm_arch_remove_sw_breakpoint(CPUState *env, struct kvm_sw_breakpoint *bp)
{
    uint8_t int3;

    if (cpu_memory_rw_debug(env, bp->pc, &int3, 1, 0) || int3 != 0xcc ||
        cpu_memory_rw_debug(env, bp->pc, (uint8_t *)&bp->saved_insn, 1, 1))
        return -EINVAL;
    return 0;
}

static struct {
    target_ulong addr;
    int len;
    int type;
} hw_breakpoint[4];

static int nb_hw_breakpoint;

static int find_hw_breakpoint(target_ulong addr, int len, int type)
{
    int n;

    for (n = 0; n < nb_hw_breakpoint; n++)
        if (hw_breakpoint[n].addr == addr && hw_breakpoint[n].type == type &&
            (hw_breakpoint[n].len == len || len == -1))
            return n;
    return -1;
}

int kvm_arch_insert_hw_breakpoint(target_ulong addr,
                                  target_ulong len, int type)
{
    switch (type) {
    case GDB_BREAKPOINT_HW:
        len = 1;
        break;
    case GDB_WATCHPOINT_WRITE:
    case GDB_WATCHPOINT_ACCESS:
        switch (len) {
        case 1:
            break;
        case 2:
        case 4:
        case 8:
            if (addr & (len - 1))
                return -EINVAL;
            break;
        default:
            return -EINVAL;
        }
        break;
    default:
        return -ENOSYS;
    }

    if (nb_hw_breakpoint == 4)
        return -ENOBUFS;

    if (find_hw_breakpoint(addr, len, type) >= 0)
        return -EEXIST;

    hw_breakpoint[nb_hw_breakpoint].addr = addr;
    hw_breakpoint[nb_hw_breakpoint].len = len;
    hw_breakpoint[nb_hw_breakpoint].type = type;
    nb_hw_breakpoint++;

    return 0;
}

int kvm_arch_remove_hw_breakpoint(target_ulong addr,
                                  target_ulong len, int type)
{
    int n;

    n = find_hw_breakpoint(addr, (type == GDB_BREAKPOINT_HW) ? 1 : len, type);
    if (n < 0)
        return -ENOENT;

    nb_hw_breakpoint--;
    hw_breakpoint[n] = hw_breakpoint[nb_hw_breakpoint];

    return 0;
}

void kvm_arch_remove_all_hw_breakpoints(void)
{
    nb_hw_breakpoint = 0;
}

static CPUWatchpoint hw_watchpoint;

int kvm_arch_debug(struct kvm_debug_exit_arch *arch_info)
{
    int handle = 0;
    int n;

    if (arch_info->exception == 1) {
        if (arch_info->dr6 & (1 << 14)) {
            if (cpu_single_env->singlestep_enabled)
                handle = 1;
        } else {
            for (n = 0; n < 4; n++)
                if (arch_info->dr6 & (1 << n))
                    switch ((arch_info->dr7 >> (16 + n*4)) & 0x3) {
                    case 0x0:
                        handle = 1;
                        break;
                    case 0x1:
                        handle = 1;
                        cpu_single_env->watchpoint_hit = &hw_watchpoint;
                        hw_watchpoint.vaddr = hw_breakpoint[n].addr;
                        hw_watchpoint.flags = BP_MEM_WRITE;
                        break;
                    case 0x3:
                        handle = 1;
                        cpu_single_env->watchpoint_hit = &hw_watchpoint;
                        hw_watchpoint.vaddr = hw_breakpoint[n].addr;
                        hw_watchpoint.flags = BP_MEM_ACCESS;
                        break;
                    }
        }
    } else if (kvm_find_sw_breakpoint(cpu_single_env, arch_info->pc))
        handle = 1;

    if (!handle)
        kvm_update_guest_debug(cpu_single_env,
                        (arch_info->exception == 1) ?
                        KVM_GUESTDBG_INJECT_DB : KVM_GUESTDBG_INJECT_BP);

    return handle;
}

void kvm_arch_update_guest_debug(CPUState *env, struct kvm_guest_debug *dbg)
{
    const uint8_t type_code[] = {
        [GDB_BREAKPOINT_HW] = 0x0,
        [GDB_WATCHPOINT_WRITE] = 0x1,
        [GDB_WATCHPOINT_ACCESS] = 0x3
    };
    const uint8_t len_code[] = {
        [1] = 0x0, [2] = 0x1, [4] = 0x3, [8] = 0x2
    };
    int n;

    if (kvm_sw_breakpoints_active(env))
        dbg->control |= KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_SW_BP;

    if (nb_hw_breakpoint > 0) {
        dbg->control |= KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_HW_BP;
        dbg->arch.debugreg[7] = 0x0600;
        for (n = 0; n < nb_hw_breakpoint; n++) {
            dbg->arch.debugreg[n] = hw_breakpoint[n].addr;
            dbg->arch.debugreg[7] |= (2 << (n * 2)) |
                (type_code[hw_breakpoint[n].type] << (16 + n*4)) |
                (len_code[hw_breakpoint[n].len] << (18 + n*4));
        }
    }
}
#endif /* KVM_CAP_SET_GUEST_DEBUG */
