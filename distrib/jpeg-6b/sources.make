# this file is included by various Makefiles and defines the set of sources used by our version of LibPng
#
LIBJPEG_SOURCES := jcapimin.c jcapistd.c jccoefct.c jccolor.c jcdctmgr.c jchuff.c \
	jcinit.c jcmainct.c jcmarker.c jcmaster.c jcomapi.c jcparam.c \
	jcphuff.c jcprepct.c jcsample.c jctrans.c jdapimin.c jdapistd.c \
	jdatadst.c jdatasrc.c jdcoefct.c jdcolor.c jddctmgr.c jdhuff.c \
	jdinput.c jdmainct.c jdmarker.c jdmaster.c jdmerge.c jdphuff.c \
	jdpostct.c jdsample.c jdtrans.c jerror.c jfdctflt.c jfdctfst.c \
	jfdctint.c jidctflt.c jidctfst.c jidctint.c jidctred.c jquant1.c \
	jquant2.c jutils.c jmemmgr.c

# jmem-ashmem.c doesn't compile for Windows.
#LIBJPEG_CFLAGS += -DUSE_ANDROID_ASHMEM
#LIBJPEG_SOURCES += jmem-ashmem.c

# the original android memory manager.
# use sdcard as libjpeg decoder's backing store
LIBJPEG_SOURCES += jmem-android.c

LIBJPEG_CFLAGS += -DAVOID_TABLES
LIBJPEG_CFLAGS += -O3 -fstrict-aliasing
#LIBJPEG_CFLAGS += -march=armv6j

# enable tile based decode
LIBJPEG_CFLAGS += -DANDROID_TILE_BASED_DECODE

LIBJPEG_SOURCES := $(LIBJPEG_SOURCES:%=$(LIBJPEG_DIR)/%)

