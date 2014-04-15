/* Declarations for use by hardware emulation.  */
#ifndef QEMU_HW_H
#define QEMU_HW_H

#include "qemu-common.h"
#include "irq.h"

#if defined(TARGET_PHYS_ADDRESS_SPACE_BITS) && !defined(NEED_CPU_H)
#include "cpu.h"
#endif

/* VM Load/Save */

/* This function writes a chunk of data to a file at the given position.
 * The pos argument can be ignored if the file is only being used for
 * streaming.  The handler should try to write all of the data it can.
 */
typedef int (QEMUFilePutBufferFunc)(void *opaque, const uint8_t *buf,
                                    int64_t pos, int size);

/* Read a chunk of data from a file at the given position.  The pos argument
 * can be ignored if the file is only be used for streaming.  The number of
 * bytes actually read should be returned.
 */
typedef int (QEMUFileGetBufferFunc)(void *opaque, uint8_t *buf,
                                    int64_t pos, int size);

/* Close a file and return an error code */
typedef int (QEMUFileCloseFunc)(void *opaque);

/* Called to determine if the file has exceeded it's bandwidth allocation.  The
 * bandwidth capping is a soft limit, not a hard limit.
 */
typedef int (QEMUFileRateLimit)(void *opaque);

/* Called to change the current bandwidth allocation. This function must return
 * the new actual bandwidth. It should be new_rate if everything goes ok, and
 * the old rate otherwise
 */
typedef int64_t (QEMUFileSetRateLimit)(void *opaque, int64_t new_rate);
typedef int64_t (QEMUFileGetRateLimit)(void *opaque);

QEMUFile *qemu_fopen_ops(void *opaque, QEMUFilePutBufferFunc *put_buffer,
                         QEMUFileGetBufferFunc *get_buffer,
                         QEMUFileCloseFunc *close,
                         QEMUFileRateLimit *rate_limit,
                         QEMUFileSetRateLimit *set_rate_limit,
			 QEMUFileGetRateLimit *get_rate_limit);
QEMUFile *qemu_fopen(const char *filename, const char *mode);
QEMUFile *qemu_fdopen(int fd, const char *mode);
QEMUFile *qemu_fopen_socket(int fd);
QEMUFile *qemu_popen(FILE *popen_file, const char *mode);
QEMUFile *qemu_popen_cmd(const char *command, const char *mode);
int qemu_stdio_fd(QEMUFile *f);
void qemu_fflush(QEMUFile *f);
int qemu_fclose(QEMUFile *f);
void qemu_put_buffer(QEMUFile *f, const uint8_t *buf, int size);
void qemu_put_byte(QEMUFile *f, int v);

static inline void qemu_put_ubyte(QEMUFile *f, unsigned int v)
{
    qemu_put_byte(f, (int)v);
}

#define qemu_put_sbyte qemu_put_byte

void qemu_put_be16(QEMUFile *f, unsigned int v);
void qemu_put_be32(QEMUFile *f, unsigned int v);
void qemu_put_be64(QEMUFile *f, uint64_t v);
#ifdef CONFIG_ANDROID
void qemu_put_float(QEMUFile *f, float v);
#endif
int qemu_get_buffer(QEMUFile *f, uint8_t *buf, int size);
int qemu_get_byte(QEMUFile *f);

static inline unsigned int qemu_get_ubyte(QEMUFile *f)
{
    return (unsigned int)qemu_get_byte(f);
}

#define qemu_get_sbyte qemu_get_byte

unsigned int qemu_get_be16(QEMUFile *f);
unsigned int qemu_get_be32(QEMUFile *f);
uint64_t qemu_get_be64(QEMUFile *f);
#ifdef CONFIG_ANDROID
float qemu_get_float(QEMUFile *f);
#endif
int qemu_file_rate_limit(QEMUFile *f);
int64_t qemu_file_set_rate_limit(QEMUFile *f, int64_t new_rate);
int64_t qemu_file_get_rate_limit(QEMUFile *f);
int qemu_file_has_error(QEMUFile *f);
void qemu_file_set_error(QEMUFile *f);

/* Try to send any outstanding data.  This function is useful when output is
 * halted due to rate limiting or EAGAIN errors occur as it can be used to
 * resume output. */
void qemu_file_put_notify(QEMUFile *f);

static inline void qemu_put_be64s(QEMUFile *f, const uint64_t *pv)
{
    qemu_put_be64(f, *pv);
}

static inline void qemu_put_be32s(QEMUFile *f, const uint32_t *pv)
{
    qemu_put_be32(f, *pv);
}

static inline void qemu_put_be16s(QEMUFile *f, const uint16_t *pv)
{
    qemu_put_be16(f, *pv);
}

static inline void qemu_put_8s(QEMUFile *f, const uint8_t *pv)
{
    qemu_put_byte(f, *pv);
}

static inline void qemu_get_be64s(QEMUFile *f, uint64_t *pv)
{
    *pv = qemu_get_be64(f);
}

static inline void qemu_get_be32s(QEMUFile *f, uint32_t *pv)
{
    *pv = qemu_get_be32(f);
}

static inline void qemu_get_be16s(QEMUFile *f, uint16_t *pv)
{
    *pv = qemu_get_be16(f);
}

static inline void qemu_get_8s(QEMUFile *f, uint8_t *pv)
{
    *pv = qemu_get_byte(f);
}

// Signed versions for type safety
static inline void qemu_put_sbuffer(QEMUFile *f, const int8_t *buf, int size)
{
    qemu_put_buffer(f, (const uint8_t *)buf, size);
}

static inline void qemu_put_sbe16(QEMUFile *f, int v)
{
    qemu_put_be16(f, (unsigned int)v);
}

static inline void qemu_put_sbe32(QEMUFile *f, int v)
{
    qemu_put_be32(f, (unsigned int)v);
}

static inline void qemu_put_sbe64(QEMUFile *f, int64_t v)
{
    qemu_put_be64(f, (uint64_t)v);
}

static inline size_t qemu_get_sbuffer(QEMUFile *f, int8_t *buf, int size)
{
    return qemu_get_buffer(f, (uint8_t *)buf, size);
}

static inline int qemu_get_sbe16(QEMUFile *f)
{
    return (int)qemu_get_be16(f);
}

static inline int qemu_get_sbe32(QEMUFile *f)
{
    return (int)qemu_get_be32(f);
}

static inline int64_t qemu_get_sbe64(QEMUFile *f)
{
    return (int64_t)qemu_get_be64(f);
}

static inline void qemu_put_s8s(QEMUFile *f, const int8_t *pv)
{
    qemu_put_8s(f, (const uint8_t *)pv);
}

static inline void qemu_put_sbe16s(QEMUFile *f, const int16_t *pv)
{
    qemu_put_be16s(f, (const uint16_t *)pv);
}

static inline void qemu_put_sbe32s(QEMUFile *f, const int32_t *pv)
{
    qemu_put_be32s(f, (const uint32_t *)pv);
}

static inline void qemu_put_sbe64s(QEMUFile *f, const int64_t *pv)
{
    qemu_put_be64s(f, (const uint64_t *)pv);
}

static inline void qemu_get_s8s(QEMUFile *f, int8_t *pv)
{
    qemu_get_8s(f, (uint8_t *)pv);
}

static inline void qemu_get_sbe16s(QEMUFile *f, int16_t *pv)
{
    qemu_get_be16s(f, (uint16_t *)pv);
}

static inline void qemu_get_sbe32s(QEMUFile *f, int32_t *pv)
{
    qemu_get_be32s(f, (uint32_t *)pv);
}

static inline void qemu_get_sbe64s(QEMUFile *f, int64_t *pv)
{
    qemu_get_be64s(f, (uint64_t *)pv);
}

#ifdef CONFIG_ANDROID
void qemu_put_string(QEMUFile *f, const char* str);
char* qemu_get_string(QEMUFile *f);
#endif

#ifdef NEED_CPU_H
#if TARGET_LONG_BITS == 64
#define qemu_put_betl qemu_put_be64
#define qemu_get_betl qemu_get_be64
#define qemu_put_betls qemu_put_be64s
#define qemu_get_betls qemu_get_be64s
#define qemu_put_sbetl qemu_put_sbe64
#define qemu_get_sbetl qemu_get_sbe64
#define qemu_put_sbetls qemu_put_sbe64s
#define qemu_get_sbetls qemu_get_sbe64s
#else
#define qemu_put_betl qemu_put_be32
#define qemu_get_betl qemu_get_be32
#define qemu_put_betls qemu_put_be32s
#define qemu_get_betls qemu_get_be32s
#define qemu_put_sbetl qemu_put_sbe32
#define qemu_get_sbetl qemu_get_sbe32
#define qemu_put_sbetls qemu_put_sbe32s
#define qemu_get_sbetls qemu_get_sbe32s
#endif
#endif

int64_t qemu_ftell(QEMUFile *f);
int64_t qemu_fseek(QEMUFile *f, int64_t pos, int whence);

typedef void SaveStateHandler(QEMUFile *f, void *opaque);
typedef int SaveLiveStateHandler(QEMUFile *f, int stage, void *opaque);
typedef int LoadStateHandler(QEMUFile *f, void *opaque, int version_id);

int register_savevm(const char *idstr,
                    int instance_id,
                    int version_id,
                    SaveStateHandler *save_state,
                    LoadStateHandler *load_state,
                    void *opaque);

int register_savevm_live(const char *idstr,
                         int instance_id,
                         int version_id,
                         SaveLiveStateHandler *save_live_state,
                         SaveStateHandler *save_state,
                         LoadStateHandler *load_state,
                         void *opaque);

void unregister_savevm(const char *idstr, void *opaque);

typedef void QEMUResetHandler(void *opaque);

void qemu_register_reset(QEMUResetHandler *func, int order, void *opaque);

/* handler to set the boot_device for a specific type of QEMUMachine */
/* return 0 if success */
typedef int QEMUBootSetHandler(void *opaque, const char *boot_device);
void qemu_register_boot_set(QEMUBootSetHandler *func, void *opaque);

#endif
