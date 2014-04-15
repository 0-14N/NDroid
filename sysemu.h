#ifndef SYSEMU_H
#define SYSEMU_H
/* Misc. things related to the system emulator.  */

#include "qemu-common.h"
#include "qemu-option.h"
#include "qemu-queue.h"
#include "qemu-timer.h"
#include "qdict.h"
#include "qerror.h"

#ifdef _WIN32
#include <windows.h>
#endif

/* vl.c */
extern const char *bios_name;

#define QEMU_FILE_TYPE_BIOS   0
#define QEMU_FILE_TYPE_KEYMAP 1
char *qemu_find_file(int type, const char *name);

extern int vm_running;
extern const char *qemu_name;
extern uint8_t qemu_uuid[];
int qemu_uuid_parse(const char *str, uint8_t *uuid);
#define UUID_FMT "%02hhx%02hhx%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx"

typedef struct vm_change_state_entry VMChangeStateEntry;
typedef void VMChangeStateHandler(void *opaque, int running, int reason);

VMChangeStateEntry *qemu_add_vm_change_state_handler(VMChangeStateHandler *cb,
                                                     void *opaque);
void qemu_del_vm_change_state_handler(VMChangeStateEntry *e);

void vm_start(void);
void vm_stop(int reason);

uint64_t ram_bytes_remaining(void);
uint64_t ram_bytes_transferred(void);
uint64_t ram_bytes_total(void);

int64_t cpu_get_ticks(void);
void cpu_enable_ticks(void);
void cpu_disable_ticks(void);

void qemu_system_reset_request(void);
void qemu_system_shutdown_request(void);
void qemu_system_powerdown_request(void);
int qemu_shutdown_requested(void);
int qemu_reset_requested(void);
int qemu_powerdown_requested(void);
void qemu_system_killed(int signal, pid_t pid);
#ifdef NEED_CPU_H
#if !defined(TARGET_SPARC)
// Please implement a power failure function to signal the OS
#define qemu_system_powerdown() do{}while(0)
#else
void qemu_system_powerdown(void);
#endif
#endif
void qemu_system_reset(void);

void do_savevm(Monitor *mon, const char *name);
void do_loadvm(Monitor *mon, const char *name);
void do_delvm(Monitor *mon, const char *name);
void do_info_snapshots(Monitor *mon, Monitor* err);

void qemu_announce_self(void);

void main_loop_wait(int timeout);

int qemu_savevm_state_begin(QEMUFile *f);
int qemu_savevm_state_iterate(QEMUFile *f);
int qemu_savevm_state_complete(QEMUFile *f);
int qemu_savevm_state(QEMUFile *f);
int qemu_loadvm_state(QEMUFile *f);

void qemu_errors_to_file(FILE *fp);
void qemu_errors_to_mon(Monitor *mon);
void qemu_errors_to_previous(void);
void qemu_error(const char *fmt, ...) __attribute__ ((format(printf, 1, 2)));
void qemu_error_internal(const char *file, int linenr, const char *func,
                         const char *fmt, ...)
                         __attribute__ ((format(printf, 4, 5)));

#define qemu_error_new(fmt, ...) \
    qemu_error_internal(__FILE__, __LINE__, __func__, fmt, ## __VA_ARGS__)

/* TAP win32 */
int tap_win32_init(VLANState *vlan, const char *model,
                   const char *name, const char *ifname);

/* SLIRP */
void do_info_slirp(Monitor *mon);

extern int autostart;
extern int bios_size;
extern int cirrus_vga_enabled;
extern int std_vga_enabled;
extern int vmsvga_enabled;
extern int xenfb_enabled;
extern int graphic_width;
extern int graphic_height;
extern int graphic_depth;
extern DisplayType display_type;
extern const char *keyboard_layout;
extern int win2k_install_hack;
extern int rtc_td_hack;
extern int alt_grab;
extern int usb_enabled;
extern int no_virtio_balloon;
extern int smp_cpus;
extern int cursor_hide;
extern int graphic_rotate;
extern int no_quit;
extern int semihosting_enabled;
extern int old_param;
extern QEMUClock *rtc_clock;

#define MAX_NODES 64
extern int nb_numa_nodes;
extern uint64_t node_mem[MAX_NODES];

#define MAX_OPTION_ROMS 16
extern const char *option_rom[MAX_OPTION_ROMS];
extern int nb_option_roms;

#ifdef NEED_CPU_H
#if defined(TARGET_SPARC) || defined(TARGET_PPC)
#define MAX_PROM_ENVS 128
extern const char *prom_envs[MAX_PROM_ENVS];
extern unsigned int nb_prom_envs;
#endif
#endif

#if 0
typedef enum {
    BLOCK_ERR_REPORT, BLOCK_ERR_IGNORE, BLOCK_ERR_STOP_ENOSPC,
    BLOCK_ERR_STOP_ANY
} BlockInterfaceErrorAction;

struct DriveInfo {
    BlockDriverState *bdrv;
    BlockInterfaceType type;
    int bus;
    int unit;
    int used;
    int drive_opt_idx;
    BlockInterfaceErrorAction onerror;
    char serial[21];
};

#define MAX_IDE_DEVS	2
#define MAX_SCSI_DEVS	7
#define MAX_DRIVES 32

extern int nb_drives;
extern DriveInfo drives_table[MAX_DRIVES+1];

extern int drive_get_index(BlockInterfaceType type, int bus, int unit);
extern int drive_get_max_bus(BlockInterfaceType type);
extern void drive_uninit(BlockDriverState *bdrv);
extern void drive_remove(int index);
extern const char *drive_get_serial(BlockDriverState *bdrv);
extern BlockInterfaceErrorAction drive_get_onerror(BlockDriverState *bdrv);

BlockDriverState *qdev_init_bdrv(DeviceState *dev, BlockInterfaceType type);

struct drive_opt {
    const char *file;
    char opt[1024];
    int used;
};

extern struct drive_opt drives_opt[MAX_DRIVES];
extern int nb_drives_opt;

extern int drive_add(const char *file, const char *fmt, ...);
extern int drive_init(struct drive_opt *arg, int snapshot, void *machine);
int add_init_drive(const char *opts);
#endif

/* acpi */
void qemu_system_hot_add_init(void);
void qemu_system_device_hot_add(int pcibus, int slot, int state);

/* device-hotplug */

typedef int (dev_match_fn)(void *dev_private, void *arg);

void destroy_nic(dev_match_fn *match_fn, void *arg);
void destroy_bdrvs(dev_match_fn *match_fn, void *arg);

#ifndef CONFIG_ANDROID
/* pci-hotplug */
void pci_device_hot_add(Monitor *mon, const char *pci_addr, const char *type,
                        const char *opts);
void drive_hot_add(Monitor *mon, const char *pci_addr, const char *opts);
void pci_device_hot_remove(Monitor *mon, const char *pci_addr);
void pci_device_hot_remove_success(int pcibus, int slot);
#endif

/* serial ports */

#define MAX_SERIAL_PORTS 4

extern CharDriverState *serial_hds[MAX_SERIAL_PORTS];

/* parallel ports */

#define MAX_PARALLEL_PORTS 3

extern CharDriverState *parallel_hds[MAX_PARALLEL_PORTS];

/* virtio consoles */

#define MAX_VIRTIO_CONSOLES 1

extern CharDriverState *virtcon_hds[MAX_VIRTIO_CONSOLES];

#define TFR(expr) do { if ((expr) != -1) break; } while (errno == EINTR)

#ifdef NEED_CPU_H
/* loader.c */
int get_image_size(const char *filename);
int load_image(const char *filename, uint8_t *addr); /* deprecated */
int load_image_targphys(const char *filename, target_phys_addr_t, int max_sz);
int load_elf(const char *filename, int64_t address_offset,
             uint64_t *pentry, uint64_t *lowaddr, uint64_t *highaddr);
int load_aout(const char *filename, target_phys_addr_t addr, int max_sz);
int load_uimage(const char *filename, target_ulong *ep, target_ulong *loadaddr,
                int *is_linux);

int fread_targphys(target_phys_addr_t dst_addr, size_t nbytes, FILE *f);
int fread_targphys_ok(target_phys_addr_t dst_addr, size_t nbytes, FILE *f);
int read_targphys(int fd, target_phys_addr_t dst_addr, size_t nbytes);
void pstrcpy_targphys(target_phys_addr_t dest, int buf_size,
                      const char *source);
#endif

void do_usb_add(Monitor *mon, const char *devname);
void do_usb_del(Monitor *mon, const char *devname);
void usb_info(Monitor *mon);

int get_param_value(char *buf, int buf_size,
                    const char *tag, const char *str);
int check_params(char *buf, int buf_size,
                 const char * const *params, const char *str);

void register_devices(void);

#endif
