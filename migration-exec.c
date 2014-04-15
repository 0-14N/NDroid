/*
 * QEMU live migration
 *
 * Copyright IBM, Corp. 2008
 * Copyright Dell MessageOne 2008
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *  Charles Duffy     <charles_duffy@messageone.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 */

#include "qemu-common.h"
#include "qemu_socket.h"
#include "migration.h"
#include "qemu-char.h"
#include "sysemu.h"
#include "buffered_file.h"
#include "block.h"
#include <sys/types.h>
#include <sys/wait.h>

//#define DEBUG_MIGRATION_EXEC

#ifdef DEBUG_MIGRATION_EXEC
#define DPRINTF(fmt, ...) \
    do { printf("migration-exec: " fmt, ## __VA_ARGS__); } while (0)
#else
#define DPRINTF(fmt, ...) \
    do { } while (0)
#endif

static int file_errno(FdMigrationState *s)
{
    return errno;
}

static int file_write(FdMigrationState *s, const void * buf, size_t size)
{
    return write(s->fd, buf, size);
}

static int exec_close(FdMigrationState *s)
{
    int ret = 0;
    DPRINTF("exec_close\n");
    if (s->opaque) {
        ret = qemu_fclose(s->opaque);
        s->opaque = NULL;
        s->fd = -1;
        if (ret != -1 &&
            WIFEXITED(ret)
            && WEXITSTATUS(ret) == 0) {
            ret = 0;
        } else {
            ret = -1;
    }
    }
    return ret;
}

MigrationState *exec_start_outgoing_migration(const char *command,
                                             int64_t bandwidth_limit,
                                             int detach)
{
    FdMigrationState *s;
    FILE *f;

    s = qemu_mallocz(sizeof(*s));

    f = popen(command, "w");
    if (f == NULL) {
        DPRINTF("Unable to popen exec target\n");
        goto err_after_alloc;
    }

    s->fd = fileno(f);
    if (s->fd == -1) {
        DPRINTF("Unable to retrieve file descriptor for popen'd handle\n");
        goto err_after_open;
    }

    if (fcntl(s->fd, F_SETFD, O_NONBLOCK) == -1) {
        DPRINTF("Unable to set nonblocking mode on file descriptor\n");
        goto err_after_open;
    }

    s->opaque = qemu_popen(f, "w");

    s->close = exec_close;
    s->get_error = file_errno;
    s->write = file_write;
    s->mig_state.cancel = migrate_fd_cancel;
    s->mig_state.get_status = migrate_fd_get_status;
    s->mig_state.release = migrate_fd_release;

    s->state = MIG_STATE_ACTIVE;
    s->mon_resume = NULL;
    s->bandwidth_limit = bandwidth_limit;

    if (!detach)
        migrate_fd_monitor_suspend(s);

    migrate_fd_connect(s);
    return &s->mig_state;

err_after_open:
    pclose(f);
err_after_alloc:
    qemu_free(s);
    return NULL;
}

static void exec_accept_incoming_migration(void *opaque)
{
    QEMUFile *f = opaque;
    int ret;

    vm_stop(0); /* just in case */
    ret = qemu_loadvm_state(f);
    if (ret < 0) {
        fprintf(stderr, "load of migration failed\n");
        goto err;
    }
    qemu_announce_self();
    DPRINTF("successfully loaded vm state\n");
    /* we've successfully migrated, close the fd */
    qemu_set_fd_handler2(qemu_stdio_fd(f), NULL, NULL, NULL, NULL);
    vm_start();

err:
    qemu_fclose(f);
}

int exec_start_incoming_migration(const char *command)
{
    QEMUFile *f;

    DPRINTF("Attempting to start an incoming migration\n");
    f = qemu_popen_cmd(command, "r");
    if(f == NULL) {
        DPRINTF("Unable to apply qemu wrapper to popen file\n");
        return -errno;
    }

    qemu_set_fd_handler2(qemu_stdio_fd(f), NULL,
			 exec_accept_incoming_migration, NULL,
			 (void *)(unsigned long)f);

    return 0;
}
