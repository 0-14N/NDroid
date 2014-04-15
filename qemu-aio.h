/*
 * QEMU aio implementation
 *
 * Copyright IBM, Corp. 2008
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 */

#ifndef QEMU_AIO_H
#define QEMU_AIO_H

#include "qemu-common.h"
#include "qemu-char.h"

/* Returns 1 if there are still outstanding AIO requests; 0 otherwise */
typedef int (AioFlushHandler)(void *opaque);

/* Runs all currently allowed AIO callbacks of completed requests in the
 * respective AIO backend. Returns 0 if no requests was handled, non-zero
 * if at least one queued request was handled. */
typedef int (AioProcessQueue)(void *opaque);

/* Flush any pending AIO operation. This function will block until all
 * outstanding AIO operations have been completed or cancelled. */
void qemu_aio_flush(void);

/* Wait for a single AIO completion to occur.  This function will wait
 * until a single AIO event has completed and it will ensure something
 * has moved before returning. This can issue new pending aio as
 * result of executing I/O completion or bh callbacks. */
void qemu_aio_wait(void);

/*
 * Runs all currently allowed AIO callbacks of completed requests. Returns 0
 * if no requests were handled, non-zero if at least one request was
 * processed.
 */
int qemu_aio_process_queue(void);

/* Register a file descriptor and associated callbacks.  Behaves very similarly
 * to qemu_set_fd_handler2.  Unlike qemu_set_fd_handler2, these callbacks will
 * be invoked when using either qemu_aio_wait() or qemu_aio_flush().
 *
 * Code that invokes AIO completion functions should rely on this function
 * instead of qemu_set_fd_handler[2].
 */
int qemu_aio_set_fd_handler(int fd,
                            IOHandler *io_read,
                            IOHandler *io_write,
                            AioFlushHandler *io_flush,
                            AioProcessQueue *io_process_queue,
                            void *opaque);

#endif
