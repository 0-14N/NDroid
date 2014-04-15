/*
 * QEMU System Emulator
 *
 * Copyright (c) 2003-2008 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <zlib.h>

/* Needed early for CONFIG_BSD etc. */
#include "config-host.h"

#ifndef _WIN32
#include <sys/times.h>
#include <sys/wait.h>
#include <termios.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#ifdef __NetBSD__
#include <net/if_tap.h>
#endif
#ifdef __linux__
#include <linux/if_tun.h>
#endif
#include <arpa/inet.h>
#include <dirent.h>
#include <netdb.h>
#include <sys/select.h>
#ifdef CONFIG_BSD
#include <sys/stat.h>
#if defined(__FreeBSD__) || defined(__DragonFly__)
#include <libutil.h>
#else
#include <util.h>
#endif
#elif defined (__GLIBC__) && defined (__FreeBSD_kernel__)
#include <freebsd/stdlib.h>
#else
#ifdef __linux__
#include <pty.h>
#include <malloc.h>
#include <linux/rtc.h>

/* For the benefit of older linux systems which don't supply it,
   we use a local copy of hpet.h. */
/* #include <linux/hpet.h> */
#include "hpet.h"

#include <linux/ppdev.h>
#include <linux/parport.h>
#endif
#ifdef __sun__
#include <sys/stat.h>
#include <sys/ethernet.h>
#include <sys/sockio.h>
#include <netinet/arp.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h> // must come after ip.h
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <net/if.h>
#include <syslog.h>
#include <stropts.h>
#endif
#endif
#endif

#if defined(__OpenBSD__)
#include <util.h>
#endif

#if defined(CONFIG_VDE)
#include <libvdeplug.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <malloc.h>
#include <sys/timeb.h>
#include <mmsystem.h>
#define getopt_long_only getopt_long
#define memalign(align, size) malloc(size)
#endif

#include "qemu-common.h"
#include "net.h"
#include "monitor.h"
#include "sysemu.h"
#include "qemu-timer.h"
#include "qemu-char.h"
#include "audio/audio.h"
#include "qemu_socket.h"
#include "qemu-log.h"

#if defined(CONFIG_SLIRP)
#include "libslirp.h"
#endif


static VLANState *first_vlan;

/***********************************************************/
/* network device redirectors */

#if defined(DEBUG_NET) || defined(DEBUG_SLIRP)
static void hex_dump(FILE *f, const uint8_t *buf, int size)
{
    int len, i, j, c;

    for(i=0;i<size;i+=16) {
        len = size - i;
        if (len > 16)
            len = 16;
        fprintf(f, "%08x ", i);
        for(j=0;j<16;j++) {
            if (j < len)
                fprintf(f, " %02x", buf[i+j]);
            else
                fprintf(f, "   ");
        }
        fprintf(f, " ");
        for(j=0;j<len;j++) {
            c = buf[i+j];
            if (c < ' ' || c > '~')
                c = '.';
            fprintf(f, "%c", c);
        }
        fprintf(f, "\n");
    }
}
#endif

static int parse_macaddr(uint8_t *macaddr, const char *p)
{
    int i;
    char *last_char;
    long int offset;

    errno = 0;
    offset = strtol(p, &last_char, 0);    
    if (0 == errno && '\0' == *last_char &&
            offset >= 0 && offset <= 0xFFFFFF) {
        macaddr[3] = (offset & 0xFF0000) >> 16;
        macaddr[4] = (offset & 0xFF00) >> 8;
        macaddr[5] = offset & 0xFF;
        return 0;
    } else {
        for(i = 0; i < 6; i++) {
            macaddr[i] = strtol(p, (char **)&p, 16);
            if (i == 5) {
                if (*p != '\0')
                    return -1;
            } else {
                if (*p != ':' && *p != '-')
                    return -1;
                p++;
            }
        }
        return 0;    
    }

    return -1;
}

static int get_str_sep(char *buf, int buf_size, const char **pp, int sep)
{
    const char *p, *p1;
    int len;
    p = *pp;
    p1 = strchr(p, sep);
    if (!p1)
        return -1;
    len = p1 - p;
    p1++;
    if (buf_size > 0) {
        if (len > buf_size - 1)
            len = buf_size - 1;
        memcpy(buf, p, len);
        buf[len] = '\0';
    }
    *pp = p1;
    return 0;
}

int parse_host_src_port(struct sockaddr_in *haddr,
                        struct sockaddr_in *saddr,
                        const char *input_str)
{
    char *str = strdup(input_str);
    char *host_str = str;
    char *src_str;
    const char *src_str2;
    char *ptr;

    /*
     * Chop off any extra arguments at the end of the string which
     * would start with a comma, then fill in the src port information
     * if it was provided else use the "any address" and "any port".
     */
    if ((ptr = strchr(str,',')))
        *ptr = '\0';

    if ((src_str = strchr(input_str,'@'))) {
        *src_str = '\0';
        src_str++;
    }

    if (parse_host_port(haddr, host_str) < 0)
        goto fail;

    src_str2 = src_str;
    if (!src_str || *src_str == '\0')
        src_str2 = ":0";

    if (parse_host_port(saddr, src_str2) < 0)
        goto fail;

    free(str);
    return(0);

fail:
    free(str);
    return -1;
}

int parse_host_port(struct sockaddr_in *saddr, const char *str)
{
    char buf[512];
    struct hostent *he;
    const char *p, *r;
    int port;

    p = str;
    if (get_str_sep(buf, sizeof(buf), &p, ':') < 0)
        return -1;
    saddr->sin_family = AF_INET;
    if (buf[0] == '\0') {
        saddr->sin_addr.s_addr = 0;
    } else {
        if (qemu_isdigit(buf[0])) {
            if (!inet_aton(buf, &saddr->sin_addr))
                return -1;
        } else {
            if ((he = gethostbyname(buf)) == NULL)
                return - 1;
            saddr->sin_addr = *(struct in_addr *)he->h_addr;
        }
    }
    port = strtol(p, (char **)&r, 0);
    if (r == p)
        return -1;
    saddr->sin_port = htons(port);
    return 0;
}

#if !defined(_WIN32) && 0
static int parse_unix_path(struct sockaddr_un *uaddr, const char *str)
{
    const char *p;
    int len;

    len = MIN(108, strlen(str));
    p = strchr(str, ',');
    if (p)
	len = MIN(len, p - str);

    memset(uaddr, 0, sizeof(*uaddr));

    uaddr->sun_family = AF_UNIX;
    memcpy(uaddr->sun_path, str, len);

    return 0;
}
#endif

void qemu_format_nic_info_str(VLANClientState *vc, uint8_t macaddr[6])
{
    snprintf(vc->info_str, sizeof(vc->info_str),
             "model=%s,macaddr=%02x:%02x:%02x:%02x:%02x:%02x",
             vc->model,
             macaddr[0], macaddr[1], macaddr[2],
             macaddr[3], macaddr[4], macaddr[5]);
}

static char *assign_name(VLANClientState *vc1, const char *model)
{
    VLANState *vlan;
    char buf[256];
    int id = 0;

    for (vlan = first_vlan; vlan; vlan = vlan->next) {
        VLANClientState *vc;

        for (vc = vlan->first_client; vc; vc = vc->next)
            if (vc != vc1 && strcmp(vc->model, model) == 0)
                id++;
    }

    snprintf(buf, sizeof(buf), "%s.%d", model, id);

    return strdup(buf);
}

VLANClientState *qemu_new_vlan_client(VLANState *vlan,
                                      const char *model,
                                      const char *name,
                                      NetCanReceive *can_receive,
                                      NetReceive *receive,
                                      NetReceiveIOV *receive_iov,
                                      NetCleanup *cleanup,
                                      void *opaque)
{
    VLANClientState *vc, **pvc;
    vc = qemu_mallocz(sizeof(VLANClientState));
    vc->model = strdup(model);
    if (name)
        vc->name = strdup(name);
    else
        vc->name = assign_name(vc, model);
    vc->can_receive = can_receive;
    vc->receive = receive;
    vc->receive_iov = receive_iov;
    vc->cleanup = cleanup;
    vc->opaque = opaque;
    vc->vlan = vlan;

    vc->next = NULL;
    pvc = &vlan->first_client;
    while (*pvc != NULL)
        pvc = &(*pvc)->next;
    *pvc = vc;
    return vc;
}

void qemu_del_vlan_client(VLANClientState *vc)
{
    VLANClientState **pvc = &vc->vlan->first_client;

    while (*pvc != NULL)
        if (*pvc == vc) {
            *pvc = vc->next;
            if (vc->cleanup) {
                vc->cleanup(vc);
            }
            free(vc->name);
            free(vc->model);
            qemu_free(vc);
            break;
        } else
            pvc = &(*pvc)->next;
}

VLANClientState *qemu_find_vlan_client(VLANState *vlan, void *opaque)
{
    VLANClientState **pvc = &vlan->first_client;

    while (*pvc != NULL)
        if ((*pvc)->opaque == opaque)
            return *pvc;
        else
            pvc = &(*pvc)->next;

    return NULL;
}

int qemu_can_send_packet(VLANClientState *sender)
{
    VLANState *vlan = sender->vlan;
    VLANClientState *vc;

    for (vc = vlan->first_client; vc != NULL; vc = vc->next) {
        if (vc == sender) {
            continue;
        }

        /* no can_receive() handler, they can always receive */
        if (!vc->can_receive || vc->can_receive(vc)) {
            return 1;
        }
    }
    return 0;
}

static int
qemu_deliver_packet(VLANClientState *sender, const uint8_t *buf, int size)
{
    VLANClientState *vc;
    int ret = -1;

    sender->vlan->delivering = 1;

    for (vc = sender->vlan->first_client; vc != NULL; vc = vc->next) {
        ssize_t len;

        if (vc == sender) {
            continue;
        }

        if (vc->link_down) {
            ret = size;
            continue;
        }

        len = vc->receive(vc, buf, size);

        ret = (ret >= 0) ? ret : len;
    }

    sender->vlan->delivering = 0;

    return ret;
}

void qemu_flush_queued_packets(VLANClientState *vc)
{
    VLANPacket *packet;

    while ((packet = vc->vlan->send_queue) != NULL) {
        int ret;

        vc->vlan->send_queue = packet->next;

        ret = qemu_deliver_packet(packet->sender, packet->data, packet->size);
        if (ret == 0 && packet->sent_cb != NULL) {
            packet->next = vc->vlan->send_queue;
            vc->vlan->send_queue = packet;
            break;
        }

        if (packet->sent_cb)
            packet->sent_cb(packet->sender);

        qemu_free(packet);
    }
}

static void qemu_enqueue_packet(VLANClientState *sender,
                                const uint8_t *buf, int size,
                                NetPacketSent *sent_cb)
{
    VLANPacket *packet;

    packet = qemu_malloc(sizeof(VLANPacket) + size);
    packet->next = sender->vlan->send_queue;
    packet->sender = sender;
    packet->size = size;
    packet->sent_cb = sent_cb;
    memcpy(packet->data, buf, size);
    sender->vlan->send_queue = packet;
}

ssize_t qemu_send_packet_async(VLANClientState *sender,
                               const uint8_t *buf, int size,
                               NetPacketSent *sent_cb)
{
    int ret;

    if (sender->link_down) {
        return size;
    }

#ifdef DEBUG_NET
    printf("vlan %d send:\n", sender->vlan->id);
    hex_dump(stdout, buf, size);
#endif

    if (sender->vlan->delivering) {
        qemu_enqueue_packet(sender, buf, size, NULL);
        return size;
    }

    ret = qemu_deliver_packet(sender, buf, size);
    if (ret == 0 && sent_cb != NULL) {
        qemu_enqueue_packet(sender, buf, size, sent_cb);
        return 0;
    }

    qemu_flush_queued_packets(sender);

    return ret;
}

void qemu_send_packet(VLANClientState *vc, const uint8_t *buf, int size)
{
    qemu_send_packet_async(vc, buf, size, NULL);
}

static ssize_t vc_sendv_compat(VLANClientState *vc, const struct iovec *iov,
                               int iovcnt)
{
    uint8_t buffer[4096];
    size_t offset = 0;
    int i;

    for (i = 0; i < iovcnt; i++) {
        size_t len;

        len = MIN(sizeof(buffer) - offset, iov[i].iov_len);
        memcpy(buffer + offset, iov[i].iov_base, len);
        offset += len;
    }

    return vc->receive(vc, buffer, offset);
}

static ssize_t calc_iov_length(const struct iovec *iov, int iovcnt)
{
    size_t offset = 0;
    int i;

    for (i = 0; i < iovcnt; i++)
        offset += iov[i].iov_len;
    return offset;
}

static int qemu_deliver_packet_iov(VLANClientState *sender,
                                   const struct iovec *iov, int iovcnt)
{
    VLANClientState *vc;
    int ret = -1;

    sender->vlan->delivering = 1;

    for (vc = sender->vlan->first_client; vc != NULL; vc = vc->next) {
        ssize_t len;

        if (vc == sender) {
            continue;
        }

        if (vc->link_down) {
            ret = calc_iov_length(iov, iovcnt);
            continue;
        }

        if (vc->receive_iov) {
            len = vc->receive_iov(vc, iov, iovcnt);
        } else {
            len = vc_sendv_compat(vc, iov, iovcnt);
        }

        ret = (ret >= 0) ? ret : len;
    }

    sender->vlan->delivering = 0;

    return ret;
}

static ssize_t qemu_enqueue_packet_iov(VLANClientState *sender,
                                       const struct iovec *iov, int iovcnt,
                                       NetPacketSent *sent_cb)
{
    VLANPacket *packet;
    size_t max_len = 0;
    int i;

    max_len = calc_iov_length(iov, iovcnt);

    packet = qemu_malloc(sizeof(VLANPacket) + max_len);
    packet->next = sender->vlan->send_queue;
    packet->sender = sender;
    packet->sent_cb = sent_cb;
    packet->size = 0;

    for (i = 0; i < iovcnt; i++) {
        size_t len = iov[i].iov_len;

        memcpy(packet->data + packet->size, iov[i].iov_base, len);
        packet->size += len;
    }

    sender->vlan->send_queue = packet;

    return packet->size;
}

ssize_t qemu_sendv_packet_async(VLANClientState *sender,
                                const struct iovec *iov, int iovcnt,
                                NetPacketSent *sent_cb)
{
    int ret;

    if (sender->link_down) {
        return calc_iov_length(iov, iovcnt);
    }

    if (sender->vlan->delivering) {
        return qemu_enqueue_packet_iov(sender, iov, iovcnt, NULL);
    }

    ret = qemu_deliver_packet_iov(sender, iov, iovcnt);
    if (ret == 0 && sent_cb != NULL) {
        qemu_enqueue_packet_iov(sender, iov, iovcnt, sent_cb);
        return 0;
    }

    qemu_flush_queued_packets(sender);

    return ret;
}

ssize_t
qemu_sendv_packet(VLANClientState *vc, const struct iovec *iov, int iovcnt)
{
    return qemu_sendv_packet_async(vc, iov, iovcnt, NULL);
}

static void config_error(Monitor *mon, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    if (mon) {
        monitor_vprintf(mon, fmt, ap);
    } else {
        fprintf(stderr, "qemu: ");
        vfprintf(stderr, fmt, ap);
        exit(1);
    }
    va_end(ap);
}

#if defined(CONFIG_SLIRP)

/* slirp network adapter */

struct slirp_config_str {
    struct slirp_config_str *next;
    const char *str;
};

static int slirp_inited;
static struct slirp_config_str *slirp_redirs;
#ifndef _WIN32
static const char *slirp_smb_export;
#endif
static VLANClientState *slirp_vc;

#ifndef _WIN32
static void slirp_smb(const char *exported_dir);
#endif
static void slirp_redirection(Monitor *mon, const char *redir_str);

int slirp_can_output(void)
{
    return !slirp_vc || qemu_can_send_packet(slirp_vc);
}

void slirp_output(const uint8_t *pkt, int pkt_len)
{
#ifdef DEBUG_SLIRP
    printf("slirp output:\n");
    hex_dump(stdout, pkt, pkt_len);
#endif
    if (!slirp_vc)
        return;
    qemu_send_packet(slirp_vc, pkt, pkt_len);
}

int slirp_is_inited(void)
{
    return slirp_inited;
}

static ssize_t slirp_receive(VLANClientState *vc, const uint8_t *buf, size_t size)
{
#ifdef DEBUG_SLIRP
    printf("slirp input:\n");
    hex_dump(stdout, buf, size);
#endif
    slirp_input(buf, size);
    return size;
}

static int slirp_in_use;

static void net_slirp_cleanup(VLANClientState *vc)
{
    slirp_in_use = 0;
}

static int net_slirp_init(VLANState *vlan, const char *model, const char *name,
                          int restricted, const char *ip)
{
    if (slirp_in_use) {
        /* slirp only supports a single instance so far */
        return -1;
    }
    if (!slirp_inited) {
        slirp_inited = 1;
        slirp_init(restricted, ip);

        while (slirp_redirs) {
            struct slirp_config_str *config = slirp_redirs;

            slirp_redirection(NULL, config->str);
            slirp_redirs = config->next;
            qemu_free(config);
        }
#ifndef _WIN32
        if (slirp_smb_export) {
            slirp_smb(slirp_smb_export);
        }
#endif
    }

    slirp_vc = qemu_new_vlan_client(vlan, model, name, NULL, slirp_receive,
                                    NULL, net_slirp_cleanup, NULL);
    slirp_vc->info_str[0] = '\0';
    slirp_in_use = 1;
    return 0;
}

static void net_slirp_redir_print(void *opaque, int is_udp,
                                  struct in_addr *laddr, u_int lport,
                                  struct in_addr *faddr, u_int fport)
{
    Monitor *mon = (Monitor *)opaque;
    uint32_t h_addr;
    uint32_t g_addr;
    char buf[16];

    h_addr = ntohl(faddr->s_addr);
    g_addr = ntohl(laddr->s_addr);

    monitor_printf(mon, "  %s |", is_udp ? "udp" : "tcp" );
    snprintf(buf, 15, "%d.%d.%d.%d", (h_addr >> 24) & 0xff,
                                     (h_addr >> 16) & 0xff,
                                     (h_addr >> 8) & 0xff,
                                     (h_addr) & 0xff);
    monitor_printf(mon, " %15s |", buf);
    monitor_printf(mon, " %5d |", fport);

    snprintf(buf, 15, "%d.%d.%d.%d", (g_addr >> 24) & 0xff,
                                     (g_addr >> 16) & 0xff,
                                     (g_addr >> 8) & 0xff,
                                     (g_addr) & 0xff);
    monitor_printf(mon, " %15s |", buf);
    monitor_printf(mon, " %5d\n", lport);

}

static void net_slirp_redir_list(Monitor *mon)
{
    if (!mon)
        return;

    monitor_printf(mon, " Prot |    Host Addr    | HPort |    Guest Addr   | GPort\n");
    monitor_printf(mon, "      |                 |       |                 |      \n");
    slirp_redir_loop(net_slirp_redir_print, mon);
}

static void net_slirp_redir_rm(Monitor *mon, const char *port_str)
{
    int host_port;
    char buf[256] = "";
    const char *p = port_str;
    int is_udp = 0;
    int n;

    if (!mon)
        return;

    if (!port_str || !port_str[0])
        goto fail_syntax;

    get_str_sep(buf, sizeof(buf), &p, ':');

    if (!strcmp(buf, "tcp") || buf[0] == '\0') {
        is_udp = 0;
    } else if (!strcmp(buf, "udp")) {
        is_udp = 1;
    } else {
        goto fail_syntax;
    }

    host_port = atoi(p);

    n = slirp_redir_rm(is_udp, host_port);

    monitor_printf(mon, "removed %d redirections to %s port %d\n", n,
                        is_udp ? "udp" : "tcp", host_port);
    return;

 fail_syntax:
    monitor_printf(mon, "invalid format\n");
}

static void slirp_redirection(Monitor *mon, const char *redir_str)
{
    struct in_addr guest_addr;
    int host_port, guest_port;
    const char *p;
    char buf[256], *r;
    int is_udp;

    p = redir_str;
    if (get_str_sep(buf, sizeof(buf), &p, ':') < 0) {
        goto fail_syntax;
    }
    if (!strcmp(buf, "tcp") || buf[0] == '\0') {
        is_udp = 0;
    } else if (!strcmp(buf, "udp")) {
        is_udp = 1;
    } else {
        goto fail_syntax;
    }

    if (get_str_sep(buf, sizeof(buf), &p, ':') < 0) {
        goto fail_syntax;
    }
    host_port = strtol(buf, &r, 0);
    if (r == buf) {
        goto fail_syntax;
    }

    if (get_str_sep(buf, sizeof(buf), &p, ':') < 0) {
        goto fail_syntax;
    }
    if (buf[0] == '\0') {
        pstrcpy(buf, sizeof(buf), "10.0.2.15");
    }
    if (!inet_aton(buf, &guest_addr)) {
        goto fail_syntax;
    }

    guest_port = strtol(p, &r, 0);
    if (r == p) {
        goto fail_syntax;
    }

    if (slirp_redir(is_udp, host_port, guest_addr, guest_port) < 0) {
        config_error(mon, "could not set up redirection '%s'\n", redir_str);
    }
    return;

 fail_syntax:
    config_error(mon, "invalid redirection format '%s'\n", redir_str);
}

void net_slirp_redir(Monitor *mon, const char *redir_str, const char *redir_opt2)
{
    struct slirp_config_str *config;

    if (!slirp_inited) {
        if (mon) {
            monitor_printf(mon, "user mode network stack not in use\n");
        } else {
            config = qemu_malloc(sizeof(*config));
            config->str = redir_str;
            config->next = slirp_redirs;
            slirp_redirs = config;
        }
        return;
    }

    if (!strcmp(redir_str, "remove")) {
        net_slirp_redir_rm(mon, redir_opt2);
        return;
    }

    if (!strcmp(redir_str, "list")) {
        net_slirp_redir_list(mon);
        return;
    }

    slirp_redirection(mon, redir_str);
}

#ifndef _WIN32

static char smb_dir[1024];

static void erase_dir(char *dir_name)
{
    DIR *d;
    struct dirent *de;
    char filename[1024];

    /* erase all the files in the directory */
    if ((d = opendir(dir_name)) != NULL) {
        for(;;) {
            de = readdir(d);
            if (!de)
                break;
            if (strcmp(de->d_name, ".") != 0 &&
                strcmp(de->d_name, "..") != 0) {
                snprintf(filename, sizeof(filename), "%s/%s",
                         smb_dir, de->d_name);
                if (unlink(filename) != 0)  /* is it a directory? */
                    erase_dir(filename);
            }
        }
        closedir(d);
        rmdir(dir_name);
    }
}

/* automatic user mode samba server configuration */
static void smb_exit(void)
{
    erase_dir(smb_dir);
}

static void slirp_smb(const char *exported_dir)
{
    char smb_conf[1024];
    char smb_cmdline[1024];
    FILE *f;

    /* XXX: better tmp dir construction */
    snprintf(smb_dir, sizeof(smb_dir), "/tmp/qemu-smb.%ld", (long)getpid());
    if (mkdir(smb_dir, 0700) < 0) {
        fprintf(stderr, "qemu: could not create samba server dir '%s'\n", smb_dir);
        exit(1);
    }
    snprintf(smb_conf, sizeof(smb_conf), "%s/%s", smb_dir, "smb.conf");

    f = fopen(smb_conf, "w");
    if (!f) {
        fprintf(stderr, "qemu: could not create samba server configuration file '%s'\n", smb_conf);
        exit(1);
    }
    fprintf(f,
            "[global]\n"
            "private dir=%s\n"
            "smb ports=0\n"
            "socket address=127.0.0.1\n"
            "pid directory=%s\n"
            "lock directory=%s\n"
            "log file=%s/log.smbd\n"
            "smb passwd file=%s/smbpasswd\n"
            "security = share\n"
            "[qemu]\n"
            "path=%s\n"
            "read only=no\n"
            "guest ok=yes\n",
            smb_dir,
            smb_dir,
            smb_dir,
            smb_dir,
            smb_dir,
            exported_dir
            );
    fclose(f);
    atexit(smb_exit);

    snprintf(smb_cmdline, sizeof(smb_cmdline), "%s -s %s",
             SMBD_COMMAND, smb_conf);

    slirp_add_exec(0, smb_cmdline, 4, 139);
}

/* automatic user mode samba server configuration */
void net_slirp_smb(const char *exported_dir)
{
    if (slirp_smb_export) {
        fprintf(stderr, "-smb given twice\n");
        exit(1);
    }
    slirp_smb_export = exported_dir;
    if (slirp_inited) {
        slirp_smb(exported_dir);
    }
}

#endif /* !defined(_WIN32) */

void do_info_slirp(Monitor *mon)
{
    slirp_stats();
}

struct VMChannel {
    CharDriverState *hd;
    int port;
};

static int vmchannel_can_read(void *opaque)
{
    struct VMChannel *vmc = (struct VMChannel*)opaque;
    return slirp_socket_can_recv(4, vmc->port);
}

static void vmchannel_read(void *opaque, const uint8_t *buf, int size)
{
    struct VMChannel *vmc = (struct VMChannel*)opaque;
    slirp_socket_recv(4, vmc->port, buf, size);
}

#endif /* CONFIG_SLIRP */

#if !defined(_WIN32)

typedef struct TAPState {
    VLANClientState *vc;
    int fd;
    char down_script[1024];
    char down_script_arg[128];
    uint8_t buf[4096];
} TAPState;

static int launch_script(const char *setup_script, const char *ifname, int fd);

static ssize_t tap_receive_iov(VLANClientState *vc, const struct iovec *iov,
                               int iovcnt)
{
    TAPState *s = vc->opaque;
    ssize_t len;

    do {
        len = writev(s->fd, iov, iovcnt);
    } while (len == -1 && (errno == EINTR || errno == EAGAIN));

    return len;
}

static ssize_t tap_receive(VLANClientState *vc, const uint8_t *buf, size_t size)
{
    TAPState *s = vc->opaque;
    ssize_t len;

    do {
        len = write(s->fd, buf, size);
    } while (len == -1 && (errno == EINTR || errno == EAGAIN));

    return len;
}

static int tap_can_send(void *opaque)
{
    TAPState *s = opaque;

    return qemu_can_send_packet(s->vc);
}

#ifdef __sun__
static ssize_t tap_read_packet(int tapfd, uint8_t *buf, int maxlen)
{
    struct strbuf sbuf;
    int f = 0;

    sbuf.maxlen = maxlen;
    sbuf.buf = (char *)buf;

    return getmsg(tapfd, NULL, &sbuf, &f) >= 0 ? sbuf.len : -1;
}
#else
static ssize_t tap_read_packet(int tapfd, uint8_t *buf, int maxlen)
{
    return read(tapfd, buf, maxlen);
}
#endif

static void tap_send(void *opaque);

static void tap_send_completed(VLANClientState *vc)
{
    TAPState *s = vc->opaque;

    qemu_set_fd_handler2(s->fd, tap_can_send, tap_send, NULL, s);
}

static void tap_send(void *opaque)
{
    TAPState *s = opaque;
    int size;

    do {
        size = tap_read_packet(s->fd, s->buf, sizeof(s->buf));
        if (size <= 0) {
            break;
        }

        size = qemu_send_packet_async(s->vc, s->buf, size, tap_send_completed);
        if (size == 0) {
            qemu_set_fd_handler2(s->fd, NULL, NULL, NULL, NULL);
        }
    } while (size > 0);
}

static void tap_cleanup(VLANClientState *vc)
{
    TAPState *s = vc->opaque;

    if (s->down_script[0])
        launch_script(s->down_script, s->down_script_arg, s->fd);

    qemu_set_fd_handler(s->fd, NULL, NULL, NULL);
    close(s->fd);
    qemu_free(s);
}

/* fd support */

static TAPState *net_tap_fd_init(VLANState *vlan,
                                 const char *model,
                                 const char *name,
                                 int fd)
{
    TAPState *s;

    s = qemu_mallocz(sizeof(TAPState));
    s->fd = fd;
    s->vc = qemu_new_vlan_client(vlan, model, name, NULL, tap_receive,
                                 tap_receive_iov, tap_cleanup, s);
    qemu_set_fd_handler2(s->fd, tap_can_send, tap_send, NULL, s);
    snprintf(s->vc->info_str, sizeof(s->vc->info_str), "fd=%d", fd);
    return s;
}

#if defined (CONFIG_BSD) || defined (__FreeBSD_kernel__)
static int tap_open(char *ifname, int ifname_size)
{
    int fd;
    char *dev;
    struct stat s;

    TFR(fd = open("/dev/tap", O_RDWR));
    if (fd < 0) {
        fprintf(stderr, "warning: could not open /dev/tap: no virtual network emulation\n");
        return -1;
    }

    fstat(fd, &s);
    dev = devname(s.st_rdev, S_IFCHR);
    pstrcpy(ifname, ifname_size, dev);

    fcntl(fd, F_SETFL, O_NONBLOCK);
    return fd;
}
#elif defined(__sun__)
#define TUNNEWPPA       (('T'<<16) | 0x0001)
/*
 * Allocate TAP device, returns opened fd.
 * Stores dev name in the first arg(must be large enough).
 */
static int tap_alloc(char *dev, size_t dev_size)
{
    int tap_fd, if_fd, ppa = -1;
    static int ip_fd = 0;
    char *ptr;

    static int arp_fd = 0;
    int ip_muxid, arp_muxid;
    struct strioctl  strioc_if, strioc_ppa;
    int link_type = I_PLINK;;
    struct lifreq ifr;
    char actual_name[32] = "";

    memset(&ifr, 0x0, sizeof(ifr));

    if( *dev ){
       ptr = dev;
       while( *ptr && !qemu_isdigit((int)*ptr) ) ptr++;
       ppa = atoi(ptr);
    }

    /* Check if IP device was opened */
    if( ip_fd )
       close(ip_fd);

    TFR(ip_fd = open("/dev/udp", O_RDWR, 0));
    if (ip_fd < 0) {
       syslog(LOG_ERR, "Can't open /dev/ip (actually /dev/udp)");
       return -1;
    }

    TFR(tap_fd = open("/dev/tap", O_RDWR, 0));
    if (tap_fd < 0) {
       syslog(LOG_ERR, "Can't open /dev/tap");
       return -1;
    }

    /* Assign a new PPA and get its unit number. */
    strioc_ppa.ic_cmd = TUNNEWPPA;
    strioc_ppa.ic_timout = 0;
    strioc_ppa.ic_len = sizeof(ppa);
    strioc_ppa.ic_dp = (char *)&ppa;
    if ((ppa = ioctl (tap_fd, I_STR, &strioc_ppa)) < 0)
       syslog (LOG_ERR, "Can't assign new interface");

    TFR(if_fd = open("/dev/tap", O_RDWR, 0));
    if (if_fd < 0) {
       syslog(LOG_ERR, "Can't open /dev/tap (2)");
       return -1;
    }
    if(ioctl(if_fd, I_PUSH, "ip") < 0){
       syslog(LOG_ERR, "Can't push IP module");
       return -1;
    }

    if (ioctl(if_fd, SIOCGLIFFLAGS, &ifr) < 0)
	syslog(LOG_ERR, "Can't get flags\n");

    snprintf (actual_name, 32, "tap%d", ppa);
    pstrcpy(ifr.lifr_name, sizeof(ifr.lifr_name), actual_name);

    ifr.lifr_ppa = ppa;
    /* Assign ppa according to the unit number returned by tun device */

    if (ioctl (if_fd, SIOCSLIFNAME, &ifr) < 0)
        syslog (LOG_ERR, "Can't set PPA %d", ppa);
    if (ioctl(if_fd, SIOCGLIFFLAGS, &ifr) <0)
        syslog (LOG_ERR, "Can't get flags\n");
    /* Push arp module to if_fd */
    if (ioctl (if_fd, I_PUSH, "arp") < 0)
        syslog (LOG_ERR, "Can't push ARP module (2)");

    /* Push arp module to ip_fd */
    if (ioctl (ip_fd, I_POP, NULL) < 0)
        syslog (LOG_ERR, "I_POP failed\n");
    if (ioctl (ip_fd, I_PUSH, "arp") < 0)
        syslog (LOG_ERR, "Can't push ARP module (3)\n");
    /* Open arp_fd */
    TFR(arp_fd = open ("/dev/tap", O_RDWR, 0));
    if (arp_fd < 0)
       syslog (LOG_ERR, "Can't open %s\n", "/dev/tap");

    /* Set ifname to arp */
    strioc_if.ic_cmd = SIOCSLIFNAME;
    strioc_if.ic_timout = 0;
    strioc_if.ic_len = sizeof(ifr);
    strioc_if.ic_dp = (char *)&ifr;
    if (ioctl(arp_fd, I_STR, &strioc_if) < 0){
        syslog (LOG_ERR, "Can't set ifname to arp\n");
    }

    if((ip_muxid = ioctl(ip_fd, I_LINK, if_fd)) < 0){
       syslog(LOG_ERR, "Can't link TAP device to IP");
       return -1;
    }

    if ((arp_muxid = ioctl (ip_fd, link_type, arp_fd)) < 0)
        syslog (LOG_ERR, "Can't link TAP device to ARP");

    close (if_fd);

    memset(&ifr, 0x0, sizeof(ifr));
    pstrcpy(ifr.lifr_name, sizeof(ifr.lifr_name), actual_name);
    ifr.lifr_ip_muxid  = ip_muxid;
    ifr.lifr_arp_muxid = arp_muxid;

    if (ioctl (ip_fd, SIOCSLIFMUXID, &ifr) < 0)
    {
      ioctl (ip_fd, I_PUNLINK , arp_muxid);
      ioctl (ip_fd, I_PUNLINK, ip_muxid);
      syslog (LOG_ERR, "Can't set multiplexor id");
    }

    snprintf(dev, dev_size, "tap%d", ppa);
    return tap_fd;
}

static int tap_open(char *ifname, int ifname_size)
{
    char  dev[10]="";
    int fd;
    if( (fd = tap_alloc(dev, sizeof(dev))) < 0 ){
       fprintf(stderr, "Cannot allocate TAP device\n");
       return -1;
    }
    pstrcpy(ifname, ifname_size, dev);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    return fd;
}
#elif defined (_AIX)
static int tap_open(char *ifname, int ifname_size)
{
    fprintf (stderr, "no tap on AIX\n");
    return -1;
}
#else
static int tap_open(char *ifname, int ifname_size)
{
    struct ifreq ifr;
    int fd, ret;

    TFR(fd = open("/dev/net/tun", O_RDWR));
    if (fd < 0) {
        fprintf(stderr, "warning: could not open /dev/net/tun: no virtual network emulation\n");
        return -1;
    }
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if (ifname[0] != '\0')
        pstrcpy(ifr.ifr_name, IFNAMSIZ, ifname);
    else
        pstrcpy(ifr.ifr_name, IFNAMSIZ, "tap%d");
    ret = ioctl(fd, TUNSETIFF, (void *) &ifr);
    if (ret != 0) {
        fprintf(stderr, "warning: could not configure /dev/net/tun: no virtual network emulation\n");
        close(fd);
        return -1;
    }
    pstrcpy(ifname, ifname_size, ifr.ifr_name);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    return fd;
}
#endif

static int launch_script(const char *setup_script, const char *ifname, int fd)
{
    sigset_t oldmask, mask;
    int pid, status;
    char *args[3];
    char **parg;

    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    /* try to launch network script */
    pid = fork();
    if (pid == 0) {
        int open_max = sysconf(_SC_OPEN_MAX), i;

        for (i = 0; i < open_max; i++) {
            if (i != STDIN_FILENO &&
                i != STDOUT_FILENO &&
                i != STDERR_FILENO &&
                i != fd) {
                close(i);
            }
        }
        parg = args;
        *parg++ = (char *)setup_script;
        *parg++ = (char *)ifname;
        *parg++ = NULL;
        execv(setup_script, args);
        _exit(1);
    } else if (pid > 0) {
        while (waitpid(pid, &status, 0) != pid) {
            /* loop */
        }
        sigprocmask(SIG_SETMASK, &oldmask, NULL);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            return 0;
        }
    }
    fprintf(stderr, "%s: could not launch network script\n", setup_script);
    return -1;
}

static int net_tap_init(VLANState *vlan, const char *model,
                        const char *name, const char *ifname1,
                        const char *setup_script, const char *down_script)
{
    TAPState *s;
    int fd;
    char ifname[128];

    if (ifname1 != NULL)
        pstrcpy(ifname, sizeof(ifname), ifname1);
    else
        ifname[0] = '\0';
    TFR(fd = tap_open(ifname, sizeof(ifname)));
    if (fd < 0)
        return -1;

    if (!setup_script || !strcmp(setup_script, "no"))
        setup_script = "";
    if (setup_script[0] != '\0') {
	if (launch_script(setup_script, ifname, fd))
	    return -1;
    }
    s = net_tap_fd_init(vlan, model, name, fd);
    snprintf(s->vc->info_str, sizeof(s->vc->info_str),
             "ifname=%s,script=%s,downscript=%s",
             ifname, setup_script, down_script);
    if (down_script && strcmp(down_script, "no")) {
        snprintf(s->down_script, sizeof(s->down_script), "%s", down_script);
        snprintf(s->down_script_arg, sizeof(s->down_script_arg), "%s", ifname);
    }
    return 0;
}

#endif /* !_WIN32 */

#if defined(CONFIG_VDE)
typedef struct VDEState {
    VLANClientState *vc;
    VDECONN *vde;
} VDEState;

static void vde_to_qemu(void *opaque)
{
    VDEState *s = opaque;
    uint8_t buf[4096];
    int size;

    size = vde_recv(s->vde, (char *)buf, sizeof(buf), 0);
    if (size > 0) {
        qemu_send_packet(s->vc, buf, size);
    }
}

static ssize_t vde_receive(VLANClientState *vc, const uint8_t *buf, size_t size)
{
    VDEState *s = vc->opaque;
    ssize_t ret;

    do {
      ret = vde_send(s->vde, (const char *)buf, size, 0);
    } while (ret < 0 && errno == EINTR);

    return ret;
}

static void vde_cleanup(VLANClientState *vc)
{
    VDEState *s = vc->opaque;
    qemu_set_fd_handler(vde_datafd(s->vde), NULL, NULL, NULL);
    vde_close(s->vde);
    qemu_free(s);
}

static int net_vde_init(VLANState *vlan, const char *model,
                        const char *name, const char *sock,
                        int port, const char *group, int mode)
{
    VDEState *s;
    char *init_group = strlen(group) ? (char *)group : NULL;
    char *init_sock = strlen(sock) ? (char *)sock : NULL;

    struct vde_open_args args = {
        .port = port,
        .group = init_group,
        .mode = mode,
    };

    s = qemu_mallocz(sizeof(VDEState));
    s->vde = vde_open(init_sock, (char *)"QEMU", &args);
    if (!s->vde){
        free(s);
        return -1;
    }
    s->vc = qemu_new_vlan_client(vlan, model, name, NULL, vde_receive,
                                 NULL, vde_cleanup, s);
    qemu_set_fd_handler(vde_datafd(s->vde), vde_to_qemu, NULL, s);
    snprintf(s->vc->info_str, sizeof(s->vc->info_str), "sock=%s,fd=%d",
             sock, vde_datafd(s->vde));
    return 0;
}
#endif

/* network connection */
typedef struct NetSocketState {
    VLANClientState *vc;
    int fd;
    int state; /* 0 = getting length, 1 = getting data */
    unsigned int index;
    unsigned int packet_len;
    uint8_t buf[4096];
    struct sockaddr_in dgram_dst; /* contains inet host and port destination iff connectionless (SOCK_DGRAM) */
} NetSocketState;

typedef struct NetSocketListenState {
    VLANState *vlan;
    char *model;
    char *name;
    int fd;
} NetSocketListenState;

/* XXX: we consider we can send the whole packet without blocking */
static ssize_t net_socket_receive(VLANClientState *vc, const uint8_t *buf, size_t size)
{
    NetSocketState *s = vc->opaque;
    uint32_t len;
    len = htonl(size);

    send_all(s->fd, (const uint8_t *)&len, sizeof(len));
    return send_all(s->fd, buf, size);
}

static ssize_t net_socket_receive_dgram(VLANClientState *vc, const uint8_t *buf, size_t size)
{
    NetSocketState *s = vc->opaque;

    return sendto(s->fd, (const void *)buf, size, 0,
                  (struct sockaddr *)&s->dgram_dst, sizeof(s->dgram_dst));
}

static void net_socket_send(void *opaque)
{
    NetSocketState *s = opaque;
    int size, err;
    unsigned l;
    uint8_t buf1[4096];
    const uint8_t *buf;

    size = recv(s->fd, (void *)buf1, sizeof(buf1), 0);
    if (size < 0) {
        err = socket_error();
        if (err != EWOULDBLOCK)
            goto eoc;
    } else if (size == 0) {
        /* end of connection */
    eoc:
        qemu_set_fd_handler(s->fd, NULL, NULL, NULL);
        closesocket(s->fd);
        return;
    }
    buf = buf1;
    while (size > 0) {
        /* reassemble a packet from the network */
        switch(s->state) {
        case 0:
            l = 4 - s->index;
            if (l > size)
                l = size;
            memcpy(s->buf + s->index, buf, l);
            buf += l;
            size -= l;
            s->index += l;
            if (s->index == 4) {
                /* got length */
                s->packet_len = ntohl(*(uint32_t *)s->buf);
                s->index = 0;
                s->state = 1;
            }
            break;
        case 1:
            l = s->packet_len - s->index;
            if (l > size)
                l = size;
            if (s->index + l <= sizeof(s->buf)) {
                memcpy(s->buf + s->index, buf, l);
            } else {
                fprintf(stderr, "serious error: oversized packet received,"
                    "connection terminated.\n");
                s->state = 0;
                goto eoc;
            }

            s->index += l;
            buf += l;
            size -= l;
            if (s->index >= s->packet_len) {
                qemu_send_packet(s->vc, s->buf, s->packet_len);
                s->index = 0;
                s->state = 0;
            }
            break;
        }
    }
}

static void net_socket_send_dgram(void *opaque)
{
    NetSocketState *s = opaque;
    int size;

    size = recv(s->fd, (void *)s->buf, sizeof(s->buf), 0);
    if (size < 0)
        return;
    if (size == 0) {
        /* end of connection */
        qemu_set_fd_handler(s->fd, NULL, NULL, NULL);
        return;
    }
    qemu_send_packet(s->vc, s->buf, size);
}

static int net_socket_mcast_create(struct sockaddr_in *mcastaddr)
{
    struct ip_mreq imr;
    int fd;
    int val, ret;
    if (!IN_MULTICAST(ntohl(mcastaddr->sin_addr.s_addr))) {
	fprintf(stderr, "qemu: error: specified mcastaddr \"%s\" (0x%08x) does not contain a multicast address\n",
		inet_ntoa(mcastaddr->sin_addr),
                (int)ntohl(mcastaddr->sin_addr.s_addr));
	return -1;

    }
    fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket(PF_INET, SOCK_DGRAM)");
        return -1;
    }

    val = 1;
    ret=setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                   (const char *)&val, sizeof(val));
    if (ret < 0) {
	perror("setsockopt(SOL_SOCKET, SO_REUSEADDR)");
	goto fail;
    }

    ret = bind(fd, (struct sockaddr *)mcastaddr, sizeof(*mcastaddr));
    if (ret < 0) {
        perror("bind");
        goto fail;
    }

    /* Add host to multicast group */
    imr.imr_multiaddr = mcastaddr->sin_addr;
    imr.imr_interface.s_addr = htonl(INADDR_ANY);

    ret = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                     (const char *)&imr, sizeof(struct ip_mreq));
    if (ret < 0) {
	perror("setsockopt(IP_ADD_MEMBERSHIP)");
	goto fail;
    }

    /* Force mcast msgs to loopback (eg. several QEMUs in same host */
    val = 1;
    ret=setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP,
                   (const char *)&val, sizeof(val));
    if (ret < 0) {
	perror("setsockopt(SOL_IP, IP_MULTICAST_LOOP)");
	goto fail;
    }

    socket_set_nonblock(fd);
    return fd;
fail:
    if (fd >= 0)
        closesocket(fd);
    return -1;
}

static void net_socket_cleanup(VLANClientState *vc)
{
    NetSocketState *s = vc->opaque;
    qemu_set_fd_handler(s->fd, NULL, NULL, NULL);
    close(s->fd);
    qemu_free(s);
}

static NetSocketState *net_socket_fd_init_dgram(VLANState *vlan,
                                                const char *model,
                                                const char *name,
                                                int fd, int is_connected)
{
    struct sockaddr_in saddr;
    int newfd;
    socklen_t saddr_len;
    NetSocketState *s;

    /* fd passed: multicast: "learn" dgram_dst address from bound address and save it
     * Because this may be "shared" socket from a "master" process, datagrams would be recv()
     * by ONLY ONE process: we must "clone" this dgram socket --jjo
     */

    if (is_connected) {
	if (getsockname(fd, (struct sockaddr *) &saddr, &saddr_len) == 0) {
	    /* must be bound */
	    if (saddr.sin_addr.s_addr==0) {
		fprintf(stderr, "qemu: error: init_dgram: fd=%d unbound, cannot setup multicast dst addr\n",
			fd);
		return NULL;
	    }
	    /* clone dgram socket */
	    newfd = net_socket_mcast_create(&saddr);
	    if (newfd < 0) {
		/* error already reported by net_socket_mcast_create() */
		close(fd);
		return NULL;
	    }
	    /* clone newfd to fd, close newfd */
	    dup2(newfd, fd);
	    close(newfd);

	} else {
	    fprintf(stderr, "qemu: error: init_dgram: fd=%d failed getsockname(): %s\n",
		    fd, strerror(errno));
	    return NULL;
	}
    }

    s = qemu_mallocz(sizeof(NetSocketState));
    s->fd = fd;

    s->vc = qemu_new_vlan_client(vlan, model, name, NULL, net_socket_receive_dgram,
                                 NULL, net_socket_cleanup, s);
    qemu_set_fd_handler(s->fd, net_socket_send_dgram, NULL, s);

    /* mcast: save bound address as dst */
    if (is_connected) s->dgram_dst=saddr;

    snprintf(s->vc->info_str, sizeof(s->vc->info_str),
	    "socket: fd=%d (%s mcast=%s:%d)",
	    fd, is_connected? "cloned" : "",
	    inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));
    return s;
}

static void net_socket_connect(void *opaque)
{
    NetSocketState *s = opaque;
    qemu_set_fd_handler(s->fd, net_socket_send, NULL, s);
}

static NetSocketState *net_socket_fd_init_stream(VLANState *vlan,
                                                 const char *model,
                                                 const char *name,
                                                 int fd, int is_connected)
{
    NetSocketState *s;
    s = qemu_mallocz(sizeof(NetSocketState));
    s->fd = fd;
    s->vc = qemu_new_vlan_client(vlan, model, name, NULL, net_socket_receive,
                                 NULL, net_socket_cleanup, s);
    snprintf(s->vc->info_str, sizeof(s->vc->info_str),
             "socket: fd=%d", fd);
    if (is_connected) {
        net_socket_connect(s);
    } else {
        qemu_set_fd_handler(s->fd, NULL, net_socket_connect, s);
    }
    return s;
}

static NetSocketState *net_socket_fd_init(VLANState *vlan,
                                          const char *model, const char *name,
                                          int fd, int is_connected)
{
    int so_type=-1, optlen=sizeof(so_type);

    if(getsockopt(fd, SOL_SOCKET, SO_TYPE, (char *)&so_type,
        (socklen_t *)&optlen)< 0) {
	fprintf(stderr, "qemu: error: getsockopt(SO_TYPE) for fd=%d failed\n", fd);
	return NULL;
    }
    switch(so_type) {
    case SOCK_DGRAM:
        return net_socket_fd_init_dgram(vlan, model, name, fd, is_connected);
    case SOCK_STREAM:
        return net_socket_fd_init_stream(vlan, model, name, fd, is_connected);
    default:
        /* who knows ... this could be a eg. a pty, do warn and continue as stream */
        fprintf(stderr, "qemu: warning: socket type=%d for fd=%d is not SOCK_DGRAM or SOCK_STREAM\n", so_type, fd);
        return net_socket_fd_init_stream(vlan, model, name, fd, is_connected);
    }
    return NULL;
}

static void net_socket_accept(void *opaque)
{
    NetSocketListenState *s = opaque;
    NetSocketState *s1;
    struct sockaddr_in saddr;
    socklen_t len;
    int fd;

    for(;;) {
        len = sizeof(saddr);
        fd = accept(s->fd, (struct sockaddr *)&saddr, &len);
        if (fd < 0 && errno != EINTR) {
            return;
        } else if (fd >= 0) {
            break;
        }
    }
    s1 = net_socket_fd_init(s->vlan, s->model, s->name, fd, 1);
    if (!s1) {
        closesocket(fd);
    } else {
        snprintf(s1->vc->info_str, sizeof(s1->vc->info_str),
                 "socket: connection from %s:%d",
                 inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));
    }
}

static int net_socket_listen_init(VLANState *vlan,
                                  const char *model,
                                  const char *name,
                                  const char *host_str)
{
    NetSocketListenState *s;
    int fd, val, ret;
    struct sockaddr_in saddr;

    if (parse_host_port(&saddr, host_str) < 0)
        return -1;

    s = qemu_mallocz(sizeof(NetSocketListenState));

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return -1;
    }
    socket_set_nonblock(fd);

    /* allow fast reuse */
    val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&val, sizeof(val));

    ret = bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret < 0) {
        perror("bind");
        return -1;
    }
    ret = listen(fd, 0);
    if (ret < 0) {
        perror("listen");
        return -1;
    }
    s->vlan = vlan;
    s->model = strdup(model);
    s->name = name ? strdup(name) : NULL;
    s->fd = fd;
    qemu_set_fd_handler(fd, net_socket_accept, NULL, s);
    return 0;
}

static int net_socket_connect_init(VLANState *vlan,
                                   const char *model,
                                   const char *name,
                                   const char *host_str)
{
    NetSocketState *s;
    int fd, connected, ret, err;
    struct sockaddr_in saddr;

    if (parse_host_port(&saddr, host_str) < 0)
        return -1;

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return -1;
    }
    socket_set_nonblock(fd);

    connected = 0;
    for(;;) {
        ret = connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
        if (ret < 0) {
            err = socket_error();
            if (err == EINTR || err == EWOULDBLOCK) {
            } else if (err == EINPROGRESS) {
                break;
#ifdef _WIN32
            } else if (err == WSAEALREADY) {
                break;
#endif
            } else {
                perror("connect");
                closesocket(fd);
                return -1;
            }
        } else {
            connected = 1;
            break;
        }
    }
    s = net_socket_fd_init(vlan, model, name, fd, connected);
    if (!s)
        return -1;
    snprintf(s->vc->info_str, sizeof(s->vc->info_str),
             "socket: connect to %s:%d",
             inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));
    return 0;
}

static int net_socket_mcast_init(VLANState *vlan,
                                 const char *model,
                                 const char *name,
                                 const char *host_str)
{
    NetSocketState *s;
    int fd;
    struct sockaddr_in saddr;

    if (parse_host_port(&saddr, host_str) < 0)
        return -1;


    fd = net_socket_mcast_create(&saddr);
    if (fd < 0)
	return -1;

    s = net_socket_fd_init(vlan, model, name, fd, 0);
    if (!s)
        return -1;

    s->dgram_dst = saddr;

    snprintf(s->vc->info_str, sizeof(s->vc->info_str),
             "socket: mcast=%s:%d",
             inet_ntoa(saddr.sin_addr), ntohs(saddr.sin_port));
    return 0;

}

typedef struct DumpState {
    VLANClientState *pcap_vc;
    int fd;
    int pcap_caplen;
} DumpState;

#define PCAP_MAGIC 0xa1b2c3d4

struct pcap_file_hdr {
    uint32_t magic;
    uint16_t version_major;
    uint16_t version_minor;
    int32_t thiszone;
    uint32_t sigfigs;
    uint32_t snaplen;
    uint32_t linktype;
};

struct pcap_sf_pkthdr {
    struct {
        int32_t tv_sec;
        int32_t tv_usec;
    } ts;
    uint32_t caplen;
    uint32_t len;
};

static ssize_t dump_receive(VLANClientState *vc, const uint8_t *buf, size_t size)
{
    DumpState *s = vc->opaque;
    struct pcap_sf_pkthdr hdr;
    int64_t ts;
    int caplen;

    /* Early return in case of previous error. */
    if (s->fd < 0) {
        return size;
    }

    ts = muldiv64(qemu_get_clock(vm_clock), 1000000, get_ticks_per_sec());
    caplen = size > s->pcap_caplen ? s->pcap_caplen : size;

    hdr.ts.tv_sec = ts / 1000000;
    hdr.ts.tv_usec = ts % 1000000;
    hdr.caplen = caplen;
    hdr.len = size;
    if (write(s->fd, &hdr, sizeof(hdr)) != sizeof(hdr) ||
        write(s->fd, buf, caplen) != caplen) {
        qemu_log("-net dump write error - stop dump\n");
        close(s->fd);
        s->fd = -1;
    }

    return size;
}

static void net_dump_cleanup(VLANClientState *vc)
{
    DumpState *s = vc->opaque;

    close(s->fd);
    qemu_free(s);
}

static int net_dump_init(Monitor *mon, VLANState *vlan, const char *device,
                         const char *name, const char *filename, int len)
{
    struct pcap_file_hdr hdr;
    DumpState *s;

    s = qemu_malloc(sizeof(DumpState));

    s->fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (s->fd < 0) {
        config_error(mon, "-net dump: can't open %s\n", filename);
        return -1;
    }

    s->pcap_caplen = len;

    hdr.magic = PCAP_MAGIC;
    hdr.version_major = 2;
    hdr.version_minor = 4;
    hdr.thiszone = 0;
    hdr.sigfigs = 0;
    hdr.snaplen = s->pcap_caplen;
    hdr.linktype = 1;

    if (write(s->fd, &hdr, sizeof(hdr)) < sizeof(hdr)) {
        config_error(mon, "-net dump write error: %s\n", strerror(errno));
        close(s->fd);
        qemu_free(s);
        return -1;
    }

    s->pcap_vc = qemu_new_vlan_client(vlan, device, name, NULL, dump_receive, NULL,
                                      net_dump_cleanup, s);
    snprintf(s->pcap_vc->info_str, sizeof(s->pcap_vc->info_str),
             "dump to %s (len=%d)", filename, len);
    return 0;
}

/* find or alloc a new VLAN */
VLANState *qemu_find_vlan(int id)
{
    VLANState **pvlan, *vlan;
    for(vlan = first_vlan; vlan != NULL; vlan = vlan->next) {
        if (vlan->id == id)
            return vlan;
    }
    vlan = qemu_mallocz(sizeof(VLANState));
    vlan->id = id;
    vlan->next = NULL;
    pvlan = &first_vlan;
    while (*pvlan != NULL)
        pvlan = &(*pvlan)->next;
    *pvlan = vlan;
    return vlan;
}

static int nic_get_free_idx(void)
{
    int index;

    for (index = 0; index < MAX_NICS; index++)
        if (!nd_table[index].used)
            return index;
    return -1;
}

void qemu_check_nic_model(NICInfo *nd, const char *model)
{
    const char *models[2];

    models[0] = model;
    models[1] = NULL;

    qemu_check_nic_model_list(nd, models, model);
}

void qemu_check_nic_model_list(NICInfo *nd, const char * const *models,
                               const char *default_model)
{
    int i, exit_status = 0;

    if (!nd->model)
        nd->model = strdup(default_model);

    if (strcmp(nd->model, "?") != 0) {
        for (i = 0 ; models[i]; i++)
            if (strcmp(nd->model, models[i]) == 0)
                return;

        fprintf(stderr, "qemu: Unsupported NIC model: %s\n", nd->model);
        exit_status = 1;
    }

    fprintf(stderr, "qemu: Supported NIC models: ");
    for (i = 0 ; models[i]; i++)
        fprintf(stderr, "%s%c", models[i], models[i+1] ? ',' : '\n');

    exit(exit_status);
}

int net_client_init(Monitor *mon, const char *device, const char *p)
{
    static const char * const fd_params[] = {
        "vlan", "name", "fd", NULL
    };
    char buf[1024];
    int vlan_id, ret;
    VLANState *vlan;
    char *name = NULL;

    vlan_id = 0;
    if (get_param_value(buf, sizeof(buf), "vlan", p)) {
        vlan_id = strtol(buf, NULL, 0);
    }
    vlan = qemu_find_vlan(vlan_id);

    if (get_param_value(buf, sizeof(buf), "name", p)) {
        name = qemu_strdup(buf);
    }
    if (!strcmp(device, "nic")) {
        static const char * const nic_params[] = {
            "vlan", "name", "macaddr", "model", NULL
        };
        NICInfo *nd;
        uint8_t *macaddr;
        int idx = nic_get_free_idx();

        if (check_params(buf, sizeof(buf), nic_params, p) < 0) {
            config_error(mon, "invalid parameter '%s' in '%s'\n", buf, p);
            ret = -1;
            goto out;
        }
        if (idx == -1 || nb_nics >= MAX_NICS) {
            config_error(mon, "Too Many NICs\n");
            ret = -1;
            goto out;
        }
        nd = &nd_table[idx];
        macaddr = nd->macaddr;
        macaddr[0] = 0x52;
        macaddr[1] = 0x54;
        macaddr[2] = 0x00;
        macaddr[3] = 0x12;
        macaddr[4] = 0x34;
        macaddr[5] = 0x56 + idx;

        if (get_param_value(buf, sizeof(buf), "macaddr", p)) {
            if (parse_macaddr(macaddr, buf) < 0) {
                config_error(mon, "invalid syntax for ethernet address\n");
                ret = -1;
                goto out;
            }
        }
        if (get_param_value(buf, sizeof(buf), "model", p)) {
            nd->model = strdup(buf);
        }
        nd->vlan = vlan;
        nd->name = name;
        nd->used = 1;
        name = NULL;
        nb_nics++;
        vlan->nb_guest_devs++;
        ret = idx;
    } else
    if (!strcmp(device, "none")) {
        if (*p != '\0') {
            config_error(mon, "'none' takes no parameters\n");
            ret = -1;
            goto out;
        }
        /* does nothing. It is needed to signal that no network cards
           are wanted */
        ret = 0;
    } else
#ifdef CONFIG_SLIRP
    if (!strcmp(device, "user")) {
        static const char * const slirp_params[] = {
            "vlan", "name", "hostname", "restrict", "ip", NULL
        };
        int restricted = 0;
        char *ip = NULL;

        if (check_params(buf, sizeof(buf), slirp_params, p) < 0) {
            config_error(mon, "invalid parameter '%s' in '%s'\n", buf, p);
            ret = -1;
            goto out;
        }
        if (get_param_value(buf, sizeof(buf), "hostname", p)) {
            pstrcpy(slirp_hostname, sizeof(slirp_hostname), buf);
        }
        if (get_param_value(buf, sizeof(buf), "restrict", p)) {
            restricted = (buf[0] == 'y') ? 1 : 0;
        }
        if (get_param_value(buf, sizeof(buf), "ip", p)) {
            ip = qemu_strdup(buf);
        }
        vlan->nb_host_devs++;
        ret = net_slirp_init(vlan, device, name, restricted, ip);
        qemu_free(ip);
    } else if (!strcmp(device, "channel")) {
        long port;
        char name[20], *devname;
        struct VMChannel *vmc;

        port = strtol(p, &devname, 10);
        devname++;
        if (port < 1 || port > 65535) {
            config_error(mon, "vmchannel wrong port number\n");
            ret = -1;
            goto out;
        }
        vmc = malloc(sizeof(struct VMChannel));
        snprintf(name, 20, "vmchannel%ld", port);
        vmc->hd = qemu_chr_open(name, devname, NULL);
        if (!vmc->hd) {
            config_error(mon, "could not open vmchannel device '%s'\n",
                         devname);
            ret = -1;
            goto out;
        }
        vmc->port = port;
        slirp_add_exec(3, vmc->hd, 4, port);
        qemu_chr_add_handlers(vmc->hd, vmchannel_can_read, vmchannel_read,
                NULL, vmc);
        ret = 0;
    } else
#endif
#ifdef _WIN32
    if (!strcmp(device, "tap")) {
        static const char * const tap_params[] = {
            "vlan", "name", "ifname", NULL
        };
        char ifname[64];

        if (check_params(buf, sizeof(buf), tap_params, p) < 0) {
            config_error(mon, "invalid parameter '%s' in '%s'\n", buf, p);
            ret = -1;
            goto out;
        }
        if (get_param_value(ifname, sizeof(ifname), "ifname", p) <= 0) {
            config_error(mon, "tap: no interface name\n");
            ret = -1;
            goto out;
        }
        vlan->nb_host_devs++;
        ret = tap_win32_init(vlan, device, name, ifname);
    } else
#elif defined (_AIX)
#else
    if (!strcmp(device, "tap")) {
        char ifname[64], chkbuf[64];
        char setup_script[1024], down_script[1024];
        int fd;
        vlan->nb_host_devs++;
        if (get_param_value(buf, sizeof(buf), "fd", p) > 0) {
            if (check_params(chkbuf, sizeof(chkbuf), fd_params, p) < 0) {
                config_error(mon, "invalid parameter '%s' in '%s'\n", chkbuf, p);
                ret = -1;
                goto out;
            }
            fd = strtol(buf, NULL, 0);
            fcntl(fd, F_SETFL, O_NONBLOCK);
            net_tap_fd_init(vlan, device, name, fd);
            ret = 0;
        } else {
            static const char * const tap_params[] = {
                "vlan", "name", "ifname", "script", "downscript", NULL
            };
            if (check_params(chkbuf, sizeof(chkbuf), tap_params, p) < 0) {
                config_error(mon, "invalid parameter '%s' in '%s'\n", chkbuf, p);
                ret = -1;
                goto out;
            }
            if (get_param_value(ifname, sizeof(ifname), "ifname", p) <= 0) {
                ifname[0] = '\0';
            }
            if (get_param_value(setup_script, sizeof(setup_script), "script", p) == 0) {
                pstrcpy(setup_script, sizeof(setup_script), DEFAULT_NETWORK_SCRIPT);
            }
            if (get_param_value(down_script, sizeof(down_script), "downscript", p) == 0) {
                pstrcpy(down_script, sizeof(down_script), DEFAULT_NETWORK_DOWN_SCRIPT);
            }
            ret = net_tap_init(vlan, device, name, ifname, setup_script, down_script);
        }
    } else
#endif
    if (!strcmp(device, "socket")) {
        char chkbuf[64];
        if (get_param_value(buf, sizeof(buf), "fd", p) > 0) {
            int fd;
            if (check_params(chkbuf, sizeof(chkbuf), fd_params, p) < 0) {
                config_error(mon, "invalid parameter '%s' in '%s'\n", chkbuf, p);
                ret = -1;
                goto out;
            }
            fd = strtol(buf, NULL, 0);
            ret = -1;
            if (net_socket_fd_init(vlan, device, name, fd, 1))
                ret = 0;
        } else if (get_param_value(buf, sizeof(buf), "listen", p) > 0) {
            static const char * const listen_params[] = {
                "vlan", "name", "listen", NULL
            };
            if (check_params(chkbuf, sizeof(chkbuf), listen_params, p) < 0) {
                config_error(mon, "invalid parameter '%s' in '%s'\n", chkbuf, p);
                ret = -1;
                goto out;
            }
            ret = net_socket_listen_init(vlan, device, name, buf);
        } else if (get_param_value(buf, sizeof(buf), "connect", p) > 0) {
            static const char * const connect_params[] = {
                "vlan", "name", "connect", NULL
            };
            if (check_params(chkbuf, sizeof(chkbuf), connect_params, p) < 0) {
                config_error(mon, "invalid parameter '%s' in '%s'\n", chkbuf, p);
                ret = -1;
                goto out;
            }
            ret = net_socket_connect_init(vlan, device, name, buf);
        } else if (get_param_value(buf, sizeof(buf), "mcast", p) > 0) {
            static const char * const mcast_params[] = {
                "vlan", "name", "mcast", NULL
            };
            if (check_params(chkbuf, sizeof(chkbuf), mcast_params, p) < 0) {
                config_error(mon, "invalid parameter '%s' in '%s'\n", chkbuf, p);
                ret = -1;
                goto out;
            }
            ret = net_socket_mcast_init(vlan, device, name, buf);
        } else {
            config_error(mon, "Unknown socket options: %s\n", p);
            ret = -1;
            goto out;
        }
        vlan->nb_host_devs++;
    } else
#ifdef CONFIG_VDE
    if (!strcmp(device, "vde")) {
        static const char * const vde_params[] = {
            "vlan", "name", "sock", "port", "group", "mode", NULL
        };
        char vde_sock[1024], vde_group[512];
	int vde_port, vde_mode;

        if (check_params(buf, sizeof(buf), vde_params, p) < 0) {
            config_error(mon, "invalid parameter '%s' in '%s'\n", buf, p);
            ret = -1;
            goto out;
        }
        vlan->nb_host_devs++;
        if (get_param_value(vde_sock, sizeof(vde_sock), "sock", p) <= 0) {
	    vde_sock[0] = '\0';
	}
	if (get_param_value(buf, sizeof(buf), "port", p) > 0) {
	    vde_port = strtol(buf, NULL, 10);
	} else {
	    vde_port = 0;
	}
	if (get_param_value(vde_group, sizeof(vde_group), "group", p) <= 0) {
	    vde_group[0] = '\0';
	}
	if (get_param_value(buf, sizeof(buf), "mode", p) > 0) {
	    vde_mode = strtol(buf, NULL, 8);
	} else {
	    vde_mode = 0700;
	}
	ret = net_vde_init(vlan, device, name, vde_sock, vde_port, vde_group, vde_mode);
    } else
#endif
    if (!strcmp(device, "dump")) {
        int len = 65536;

        if (get_param_value(buf, sizeof(buf), "len", p) > 0) {
            len = strtol(buf, NULL, 0);
        }
        if (!get_param_value(buf, sizeof(buf), "file", p)) {
            snprintf(buf, sizeof(buf), "qemu-vlan%d.pcap", vlan_id);
        }
        ret = net_dump_init(mon, vlan, device, name, buf, len);
    } else {
        config_error(mon, "Unknown network device: %s\n", device);
        ret = -1;
        goto out;
    }
    if (ret < 0) {
        config_error(mon, "Could not initialize device '%s'\n", device);
    }
out:
    qemu_free(name);
    return ret;
}

void net_client_uninit(NICInfo *nd)
{
    nd->vlan->nb_guest_devs--;
    nb_nics--;
    nd->used = 0;
    free((void *)nd->model);
}

static int net_host_check_device(const char *device)
{
    int i;
    const char *valid_param_list[] = { "tap", "socket", "dump"
#ifdef CONFIG_SLIRP
                                       ,"user"
#endif
#ifdef CONFIG_VDE
                                       ,"vde"
#endif
    };
    for (i = 0; i < sizeof(valid_param_list) / sizeof(char *); i++) {
        if (!strncmp(valid_param_list[i], device,
                     strlen(valid_param_list[i])))
            return 1;
    }

    return 0;
}

void net_host_device_add(Monitor *mon, const char *device, const char *opts)
{
    if (!net_host_check_device(device)) {
        monitor_printf(mon, "invalid host network device %s\n", device);
        return;
    }
    if (net_client_init(mon, device, opts ? opts : "") < 0) {
        monitor_printf(mon, "adding host network device %s failed\n", device);
    }
}

void net_host_device_remove(Monitor *mon, int vlan_id, const char *device)
{
    VLANState *vlan;
    VLANClientState *vc;

    vlan = qemu_find_vlan(vlan_id);

    for (vc = vlan->first_client; vc != NULL; vc = vc->next) {
        if (!strcmp(vc->name, device)) {
            break;
        }
    }

    if (!vc) {
        monitor_printf(mon, "can't find device %s\n", device);
        return;
    }
    if (!net_host_check_device(vc->model)) {
        monitor_printf(mon, "invalid host network device %s\n", device);
        return;
    }
    qemu_del_vlan_client(vc);
}

int net_client_parse(const char *str)
{
    const char *p;
    char *q;
    char device[64];

    p = str;
    q = device;
    while (*p != '\0' && *p != ',') {
        if ((q - device) < sizeof(device) - 1)
            *q++ = *p;
        p++;
    }
    *q = '\0';
    if (*p == ',')
        p++;

    return net_client_init(NULL, device, p);
}

void do_info_network(Monitor *mon)
{
    VLANState *vlan;
    VLANClientState *vc;

    for(vlan = first_vlan; vlan != NULL; vlan = vlan->next) {
        monitor_printf(mon, "VLAN %d devices:\n", vlan->id);
        for(vc = vlan->first_client; vc != NULL; vc = vc->next)
            monitor_printf(mon, "  %s: %s\n", vc->name, vc->info_str);
    }
}

int do_set_link(Monitor *mon, const char *name, const char *up_or_down)
{
    VLANState *vlan;
    VLANClientState *vc = NULL;

    for (vlan = first_vlan; vlan != NULL; vlan = vlan->next)
        for (vc = vlan->first_client; vc != NULL; vc = vc->next)
            if (strcmp(vc->name, name) == 0)
                goto done;
done:

    if (!vc) {
        monitor_printf(mon, "could not find network device '%s'", name);
        return 0;
    }

    if (strcmp(up_or_down, "up") == 0)
        vc->link_down = 0;
    else if (strcmp(up_or_down, "down") == 0)
        vc->link_down = 1;
    else
        monitor_printf(mon, "invalid link status '%s'; only 'up' or 'down' "
                       "valid\n", up_or_down);

    if (vc->link_status_changed)
        vc->link_status_changed(vc);

    return 1;
}

void net_cleanup(void)
{
    VLANState *vlan;

    /* close network clients */
    for(vlan = first_vlan; vlan != NULL; vlan = vlan->next) {
        VLANClientState *vc = vlan->first_client;

        while (vc) {
            VLANClientState *next = vc->next;

            qemu_del_vlan_client(vc);

            vc = next;
        }
    }
}

void net_client_check(void)
{
    VLANState *vlan;

    for(vlan = first_vlan; vlan != NULL; vlan = vlan->next) {
        if (vlan->nb_guest_devs == 0 && vlan->nb_host_devs == 0)
            continue;
        if (vlan->nb_guest_devs == 0)
            fprintf(stderr, "Warning: vlan %d with no nics\n", vlan->id);
        if (vlan->nb_host_devs == 0)
            fprintf(stderr,
                    "Warning: vlan %d is not connected to host network\n",
                    vlan->id);
    }
}
