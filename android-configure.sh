#!/bin/sh
#
# this script is used to rebuild the Android emulator from sources
# in the current directory. It also contains logic to speed up the
# rebuild if it detects that you're using the Android build system
#
# here's the list of environment variables you can define before
# calling this script to control it (besides options):
#
#

# first, let's see which system we're running this on
cd `dirname $0`

# source common functions definitions
. android/build/common.sh

# Parse options
OPTION_TARGETS=""
OPTION_DEBUG=no
OPTION_IGNORE_AUDIO=no
OPTION_NO_PREBUILTS=no
OPTION_TRY_64=no
OPTION_HELP=no
OPTION_DEBUG=no
OPTION_STATIC=no
OPTION_MINGW=no

GLES_INCLUDE=
GLES_LIBS=
GLES_SUPPORT=no
GLES_PROBE=yes

HOST_CC=${CC:-gcc}
OPTION_CC=

TARGET_ARCH=arm

for opt do
  optarg=`expr "x$opt" : 'x[^=]*=\(.*\)'`
  case "$opt" in
  --help|-h|-\?) OPTION_HELP=yes
  ;;
  --verbose)
    if [ "$VERBOSE" = "yes" ] ; then
        VERBOSE2=yes
    else
        VERBOSE=yes
    fi
  ;;
  --debug) OPTION_DEBUG=yes
  ;;
  --install=*) OPTION_TARGETS="$OPTION_TARGETS $optarg";
  ;;
  --sdl-config=*) SDL_CONFIG=$optarg
  ;;
  --mingw) OPTION_MINGW=yes
  ;;
  --cc=*) OPTION_CC="$optarg"
  ;;
  --no-strip) OPTION_NO_STRIP=yes
  ;;
  --debug) OPTION_DEBUG=yes
  ;;
  --ignore-audio) OPTION_IGNORE_AUDIO=yes
  ;;
  --no-prebuilts) OPTION_NO_PREBUILTS=yes
  ;;
  --try-64) OPTION_TRY_64=yes
  ;;
  --static) OPTION_STATIC=yes
  ;;
  --arch=*) TARGET_ARCH=$optarg
  ;;
  --gles-include=*) GLES_INCLUDE=$optarg
  GLES_SUPPORT=yes
  ;;
  --gles-libs=*) GLES_LIBS=$optarg
  GLES_SUPPORT=yes
  ;;
  --no-gles) GLES_PROBE=no
  ;;
  *)
    echo "unknown option '$opt', use --help"
    exit 1
  esac
done

# Print the help message
#
if [ "$OPTION_HELP" = "yes" ] ; then
    cat << EOF

Usage: rebuild.sh [options]
Options: [defaults in brackets after descriptions]
EOF
    echo "Standard options:"
    echo "  --help                   print this message"
    echo "  --install=FILEPATH       copy emulator executable to FILEPATH [$TARGETS]"
    echo "  --cc=PATH                specify C compiler [$HOST_CC]"
    echo "  --arch=ARM               specify target architecture [$TARGET_ARCH]"
    echo "  --sdl-config=FILE        use specific sdl-config script [$SDL_CONFIG]"
    echo "  --no-strip               do not strip emulator executable"
    echo "  --debug                  enable debug (-O0 -g) build"
    echo "  --ignore-audio           ignore audio messages (may build sound-less emulator)"
    echo "  --no-prebuilts           do not use prebuilt libraries and compiler"
    echo "  --try-64                 try to build a 64-bit executable (may crash)"
    echo "  --mingw                  build Windows executable on Linux"
    echo "  --static                 build a completely static executable"
    echo "  --verbose                verbose configuration"
    echo "  --debug                  build debug version of the emulator"
    echo "  --gles-include=PATH      specify path to GLES emulation headers"
    echo "  --gles-libs=PATH         specify path to GLES emulation host libraries"
    echo "  --no-gles                disable GLES emulation support"
    echo ""
    exit 1
fi

# On Linux, try to use our prebuilt toolchain to generate binaries
# that are compatible with Ubuntu 8.04
if [ -z "$CC" -a -z "$OPTION_CC" -a "$HOST_OS" = linux ] ; then
    HOST_CC=`dirname $0`/../../prebuilts/tools/gcc-sdk/gcc
    if [ -f "$HOST_CC" ] ; then
        echo "Using prebuilt toolchain: $HOST_CC"
        CC="$HOST_CC"
    fi
fi

echo "OPTION_CC='$OPTION_CC'"
if [ -n "$OPTION_CC" ]; then
    echo "Using specified C compiler: $OPTION_CC"
    CC="$OPTION_CC"
fi

if [ -z "$CC" ]; then
  CC=$HOST_CC
fi

# we only support generating 32-bit binaris on 64-bit systems.
# And we may need to add a -Wa,--32 to CFLAGS to let the assembler
# generate 32-bit binaries on Linux x86_64.
#
if [ "$OPTION_TRY_64" != "yes" ] ; then
    force_32bit_binaries
fi

case $OS in
    linux-*)
        TARGET_DLL_SUFFIX=.so
        ;;
    darwin-*)
        TARGET_DLL_SUFFIX=.dylib
        ;;
    windows*)
        TARGET_DLL_SUFFIX=.dll
esac

TARGET_OS=$OS
if [ "$OPTION_MINGW" = "yes" ] ; then
    enable_linux_mingw
    TARGET_OS=windows
    TARGET_DLL_SUFFIX=.dll
else
    enable_cygwin
fi

# Are we running in the Android build system ?
check_android_build


# Adjust a few things when we're building within the Android build
# system:
#    - locate prebuilt directory
#    - locate and use prebuilt libraries
#    - copy the new binary to the correct location
#
if [ "$OPTION_NO_PREBUILTS" = "yes" ] ; then
    IN_ANDROID_BUILD=no
fi

# This is the list of static and shared host libraries we need to link
# against in order to support OpenGLES emulation properly. Note that in
# the case of a standalone build, we will find these libraries inside the
# platform build tree and copy them into objs/lib/ automatically, unless
# you use --gles-libs to point explicitely to a different directory.
#
if [ "$OPTION_TRY_64" != "yes" ] ; then
    GLES_SHARED_LIBRARIES="libOpenglRender libGLES_CM_translator libGLES_V2_translator libEGL_translator"
else
    GLES_SHARED_LIBRARIES="lib64OpenglRender lib64GLES_CM_translator lib64GLES_V2_translator lib64EGL_translator"
fi

if [ "$IN_ANDROID_BUILD" = "yes" ] ; then
    locate_android_prebuilt

    # use ccache if USE_CCACHE is defined and the corresponding
    # binary is available.
    #
    # note: located in PREBUILT/ccache/ccache in the new tree layout
    #       located in PREBUILT/ccache in the old one
    #
    if [ -n "$USE_CCACHE" ] ; then
        CCACHE="$ANDROID_PREBUILT/ccache/ccache$EXE"
        if [ ! -f $CCACHE ] ; then
            CCACHE="$ANDROID_PREBUILT/ccache$EXE"
        fi
        if [ ! -f $CCACHE ] ; then
            CCACHE="$ANDROID_PREBUILTS/ccache/ccache$EXE"
        fi
        if [ -f $CCACHE ] ; then
            CC="$CCACHE $CC"
            log "Prebuilt   : CCACHE=$CCACHE"
	else
            log "Prebuilt   : CCACHE can't be found"
        fi
    fi

    # finally ensure that our new binary is copied to the 'out'
    # subdirectory as 'emulator'
    HOST_BIN=$(get_android_abs_build_var HOST_OUT_EXECUTABLES)
    if [ "$TARGET_OS" = "windows" ]; then
        HOST_BIN=$(echo $HOST_BIN | sed "s%$OS/bin%windows/bin%")
    fi
    if [ -n "$HOST_BIN" ] ; then
        OPTION_TARGETS="$OPTION_TARGETS $HOST_BIN/emulator$EXE"
        log "Targets    : TARGETS=$OPTION_TARGETS"
    fi

    # find the Android SDK Tools revision number
    TOOLS_PROPS=$ANDROID_TOP/sdk/files/tools_source.properties
    if [ -f $TOOLS_PROPS ] ; then
        ANDROID_SDK_TOOLS_REVISION=`awk -F= '/Pkg.Revision/ { print $2; }' $TOOLS_PROPS 2> /dev/null`
        log "Tools      : Found tools revision number $ANDROID_SDK_TOOLS_REVISION"
    else
        log "Tools      : Could not locate $TOOLS_PROPS !?"
    fi

    # Try to find the GLES emulation headers and libraries automatically
    if [ "$GLES_PROBE" = "yes" ]; then
        GLES_SUPPORT=yes
        if [ -z "$GLES_INCLUDE" ]; then
            log "GLES       : Probing for headers"
            GLES_INCLUDE=$ANDROID_TOP/development/tools/emulator/opengl/host/include
            if [ -d "$GLES_INCLUDE" ]; then
                log "GLES       : Headers in $GLES_INCLUDE"
            else
                echo "Warning: Could not find OpenGLES emulation include dir: $GLES_INCLUDE"
                echo "Disabling GLES emulation from this build!"
                GLES_SUPPORT=no
            fi
        fi
        if [ -z "$GLES_LIBS" ]; then
            log "GLES       : Probing for host libraries"
            GLES_LIBS=$(dirname "$HOST_BIN")/lib
            if [ -d "$GLES_LIBS" ]; then
                echo "GLES       : Libs in $GLES_LIBS"
            else
                echo "Warning: Could nof find OpenGLES emulation libraries in: $GLES_LIBS"
                echo "Disabling GLES emulation from this build!"
                GLES_SUPPORT=no
            fi
        fi
    fi
fi  # IN_ANDROID_BUILD = no

if [ "$GLES_SUPPORT" = "yes" ]; then
    if [ -z "$GLES_INCLUDE" -o -z "$GLES_LIBS" ]; then
        echo "ERROR: You must use both --gles-include and --gles-libs at the same time!"
        echo "       Or use --no-gles to disable its support from this build."
        exit 1
    fi

    GLES_HEADER=$GLES_INCLUDE/libOpenglRender/render_api.h
    if [ ! -f "$GLES_HEADER" ]; then
        echo "ERROR: Missing OpenGLES emulation header file: $GLES_HEADER"
        echo "Please fix this by using --gles-include to point to the right directory!"
        exit 1
    fi

    mkdir -p objs/lib

    for lib in $GLES_SHARED_LIBRARIES; do
        GLES_LIB=$GLES_LIBS/${lib}$TARGET_DLL_SUFFIX
        if [ ! -f "$GLES_LIB" ]; then
            echo "ERROR: Missing OpenGLES emulation host library: $GLES_LIB"
            echo "Please fix this by using --gles-libs to point to the right directory!"
            if [ "$IN_ANDROID_BUILD" = "true" ]; then
                echo "You might also be missing the library because you forgot to rebuild the whole platform!"
            fi
            exit 1
        fi
        cp $GLES_LIB objs/lib
        if [ $? != 0 ]; then
            echo "ERROR: Could not find required OpenGLES emulation library: $GLES_LIB"
            exit 1
        else
            log "GLES       : Copying $GLES_LIB"
        fi
    done
fi

# we can build the emulator with Cygwin, so enable it
enable_cygwin

setup_toolchain

###
###  SDL Probe
###

if [ -n "$SDL_CONFIG" ] ; then

	# check that we can link statically with the library.
	#
	SDL_CFLAGS=`$SDL_CONFIG --cflags`
	SDL_LIBS=`$SDL_CONFIG --static-libs`

	# quick hack, remove the -D_GNU_SOURCE=1 of some SDL Cflags
7	# since they break recent Mingw releases
	SDL_CFLAGS=`echo $SDL_CFLAGS | sed -e s/-D_GNU_SOURCE=1//g`

	log "SDL-probe  : SDL_CFLAGS = $SDL_CFLAGS"
	log "SDL-probe  : SDL_LIBS   = $SDL_LIBS"


	EXTRA_CFLAGS="$SDL_CFLAGS"
	EXTRA_LDFLAGS="$SDL_LIBS"

	case "$OS" in
		freebsd-*)
		EXTRA_LDFLAGS="$EXTRA_LDFLAGS -lm -lpthread"
		;;
	esac

	cat > $TMPC << EOF
#include <SDL.h>
#undef main
int main( int argc, char** argv ) {
   return SDL_Init (SDL_INIT_VIDEO);
}
EOF
	feature_check_link  SDL_LINKING

	if [ $SDL_LINKING != "yes" ] ; then
		echo "You provided an explicit sdl-config script, but the corresponding library"
		echo "cannot be statically linked with the Android emulator directly."
		echo "Error message:"
		cat $TMPL
		clean_exit
	fi
	log "SDL-probe  : static linking ok"

	# now, let's check that the SDL library has the special functions
	# we added to our own sources
	#
	cat > $TMPC << EOF
#include <SDL.h>
#undef main
int main( int argc, char** argv ) {
	int  x, y;
	SDL_Rect  r;
	SDL_WM_GetPos(&x, &y);
	SDL_WM_SetPos(x, y);
	SDL_WM_GetMonitorDPI(&x, &y);
	SDL_WM_GetMonitorRect(&r);
	return SDL_Init (SDL_INIT_VIDEO);
}
EOF
	feature_check_link  SDL_LINKING

	if [ $SDL_LINKING != "yes" ] ; then
		echo "You provided an explicit sdl-config script in SDL_CONFIG, but the"
		echo "corresponding library doesn't have the patches required to link"
		echo "with the Android emulator. Unsetting SDL_CONFIG will use the"
		echo "sources bundled with the emulator instead"
		echo "Error:"
		cat $TMPL
		clean_exit
	fi

	log "SDL-probe  : extra features ok"
	clean_temp

	EXTRA_CFLAGS=
	EXTRA_LDFLAGS=
fi

###
###  Audio subsystems probes
###
PROBE_COREAUDIO=no
PROBE_ALSA=no
PROBE_OSS=no
PROBE_ESD=no
PROBE_PULSEAUDIO=no
PROBE_WINAUDIO=no

case "$TARGET_OS" in
    darwin*) PROBE_COREAUDIO=yes;
    ;;
    linux-*) PROBE_ALSA=yes; PROBE_OSS=yes; PROBE_ESD=yes; PROBE_PULSEAUDIO=yes;
    ;;
    freebsd-*) PROBE_OSS=yes;
    ;;
    windows) PROBE_WINAUDIO=yes
    ;;
esac

ORG_CFLAGS=$CFLAGS
ORG_LDFLAGS=$LDFLAGS

if [ "$OPTION_IGNORE_AUDIO" = "yes" ] ; then
PROBE_ESD_ESD=no
PROBE_ALSA=no
PROBE_PULSEAUDIO=no
fi

# Probe a system library
#
# $1: Variable name (e.g. PROBE_ESD)
# $2: Library name (e.g. "Alsa")
# $3: Path to source file for probe program (e.g. android/config/check-alsa.c)
# $4: Package name (e.g. libasound-dev)
#
probe_system_library ()
{
    if [ `var_value $1` = yes ] ; then
        CFLAGS="$ORG_CFLAGS"
        LDFLAGS="$ORG_LDFLAGS -ldl"
        cp -f android/config/check-esd.c $TMPC
        compile
        if [ $? = 0 ] ; then
            log "AudioProbe : $2 seems to be usable on this system"
        else
            if [ "$OPTION_IGNORE_AUDIO" = no ] ; then
                echo "The $2 development files do not seem to be installed on this system"
                echo "Are you missing the $4 package ?"
                echo "Correct the errors below and try again:"
                cat $TMPL
                clean_exit
            fi
            eval $1=no
            log "AudioProbe : $2 seems to be UNUSABLE on this system !!"
        fi
    fi
}

probe_system_library PROBE_ESD        ESounD     android/config/check-esd.c libesd-dev
probe_system_library PROBE_ALSA       Alsa       android/config/check-alsa.c libasound-dev
probe_system_library PROBE_PULSEAUDIO PulseAudio android/config/check-pulseaudio.c libpulse-dev

CFLAGS=$ORG_CFLAGS
LDFLAGS=$ORG_LDFLAGS

# create the objs directory that is going to contain all generated files
# including the configuration ones
#
mkdir -p objs

###
###  Compiler probe
###

####
####  Host system probe
####

# because the previous version could be read-only
rm -f $TMPC

# check host endianess
#
HOST_BIGENDIAN=no
if [ "$TARGET_OS" = "$OS" ] ; then
cat > $TMPC << EOF
#include <inttypes.h>
int main(int argc, char ** argv){
        volatile uint32_t i=0x01234567;
        return (*((uint8_t*)(&i))) == 0x01;
}
EOF
feature_run_exec HOST_BIGENDIAN
fi

# check size of host long bits
HOST_LONGBITS=32
if [ "$TARGET_OS" = "$OS" ] ; then
cat > $TMPC << EOF
int main(void) {
        return sizeof(void*)*8;
}
EOF
feature_run_exec HOST_LONGBITS
fi

# check whether we have <byteswap.h>
#
feature_check_header HAVE_BYTESWAP_H      "<byteswap.h>"
feature_check_header HAVE_MACHINE_BSWAP_H "<machine/bswap.h>"
feature_check_header HAVE_FNMATCH_H       "<fnmatch.h>"

# Build the config.make file
#

case $TARGET_OS in
    windows)
        TARGET_EXEEXT=.exe
        ;;
    *)
        TARGET_EXEEXT=
        ;;
esac

create_config_mk
echo "" >> $config_mk
if [ $TARGET_ARCH = arm ] ; then
echo "TARGET_ARCH       := arm" >> $config_mk
fi

if [ $TARGET_ARCH = x86 ] ; then
echo "TARGET_ARCH       := x86" >> $config_mk
fi

echo "HOST_PREBUILT_TAG := $TARGET_OS" >> $config_mk
echo "HOST_EXEEXT       := $TARGET_EXEEXT" >> $config_mk
echo "PREBUILT          := $ANDROID_PREBUILT" >> $config_mk
echo "PREBUILTS         := $ANDROID_PREBUILTS" >> $config_mk

PWD=`pwd`
echo "SRC_PATH          := $PWD" >> $config_mk
if [ -n "$SDL_CONFIG" ] ; then
echo "QEMU_SDL_CONFIG   := $SDL_CONFIG" >> $config_mk
fi
echo "CONFIG_COREAUDIO  := $PROBE_COREAUDIO" >> $config_mk
echo "CONFIG_WINAUDIO   := $PROBE_WINAUDIO" >> $config_mk
echo "CONFIG_ESD        := $PROBE_ESD" >> $config_mk
echo "CONFIG_ALSA       := $PROBE_ALSA" >> $config_mk
echo "CONFIG_OSS        := $PROBE_OSS" >> $config_mk
echo "CONFIG_PULSEAUDIO := $PROBE_PULSEAUDIO" >> $config_mk
echo "BUILD_STANDALONE_EMULATOR := true" >> $config_mk
if [ $OPTION_DEBUG = yes ] ; then
    echo "BUILD_DEBUG_EMULATOR := true" >> $config_mk
fi
if [ $OPTION_STATIC = yes ] ; then
    echo "CONFIG_STATIC_EXECUTABLE := true" >> $config_mk
fi

if [ -n "$ANDROID_SDK_TOOLS_REVISION" ] ; then
    echo "ANDROID_SDK_TOOLS_REVISION := $ANDROID_SDK_TOOLS_REVISION" >> $config_mk
fi

if [ "$OPTION_MINGW" = "yes" ] ; then
    echo "" >> $config_mk
    echo "USE_MINGW := 1" >> $config_mk
    echo "HOST_OS   := windows" >> $config_mk
fi

if [ "$GLES_INCLUDE" -a "$GLES_LIBS" ]; then
    echo "QEMU_OPENGLES_INCLUDE    := $GLES_INCLUDE" >> $config_mk
    echo "QEMU_OPENGLES_LIBS       := $GLES_LIBS"    >> $config_mk
fi

# Build the config-host.h file
#
config_h=objs/config-host.h
echo "/* This file was autogenerated by '$PROGNAME' */" > $config_h
echo "#define CONFIG_QEMU_SHAREDIR   \"/usr/local/share/qemu\"" >> $config_h
echo "#define HOST_LONG_BITS  $HOST_LONGBITS" >> $config_h
if [ "$HAVE_BYTESWAP_H" = "yes" ] ; then
  echo "#define CONFIG_BYTESWAP_H 1" >> $config_h
fi
if [ "$HAVE_MACHINE_BYTESWAP_H" = "yes" ] ; then
  echo "#define CONFIG_MACHINE_BSWAP_H 1" >> $config_h
fi
if [ "$HAVE_FNMATCH_H" = "yes" ] ; then
  echo "#define CONFIG_FNMATCH  1" >> $config_h
fi
echo "#define CONFIG_GDBSTUB  1" >> $config_h
echo "#define CONFIG_SLIRP    1" >> $config_h
echo "#define CONFIG_SKINS    1" >> $config_h
echo "#define CONFIG_TRACE    1" >> $config_h

case "$TARGET_OS" in
    windows)
        echo "#define CONFIG_WIN32  1" >> $config_h
        ;;
    *)
        echo "#define CONFIG_POSIX  1" >> $config_h
        ;;
esac

case "$TARGET_OS" in
    linux-*)
        echo "#define CONFIG_KVM_GS_RESTORE 1" >> $config_h
        ;;
esac

# only Linux has fdatasync()
case "$TARGET_OS" in
    linux-*)
        echo "#define CONFIG_FDATASYNC    1" >> $config_h
        ;;
esac

case "$TARGET_OS" in
    linux-*|darwin-*)
        echo "#define CONFIG_MADVISE  1" >> $config_h
        ;;
esac

# the -nand-limits options can only work on non-windows systems
if [ "$TARGET_OS" != "windows" ] ; then
    echo "#define CONFIG_NAND_LIMITS  1" >> $config_h
fi
echo "#define QEMU_VERSION    \"0.10.50\"" >> $config_h
echo "#define QEMU_PKGVERSION \"Android\"" >> $config_h
case "$CPU" in
    x86) CONFIG_CPU=I386
    ;;
    ppc) CONFIG_CPU=PPC
    ;;
    x86_64) CONFIG_CPU=X86_64
    ;;
    *) CONFIG_CPU=$CPU
    ;;
esac
echo "#define HOST_$CONFIG_CPU    1" >> $config_h
if [ "$HOST_BIGENDIAN" = "1" ] ; then
  echo "#define HOST_WORDS_BIGENDIAN 1" >> $config_h
fi
BSD=0
case "$TARGET_OS" in
    linux-*) CONFIG_OS=LINUX
    ;;
    darwin-*) CONFIG_OS=DARWIN
              BSD=1
    ;;
    freebsd-*) CONFIG_OS=FREEBSD
              BSD=1
    ;;
    windows*) CONFIG_OS=WIN32
    ;;
    *) CONFIG_OS=$OS
esac

if [ "$OPTION_STATIC" = "yes" ] ; then
    echo "CONFIG_STATIC_EXECUTABLE := true" >> $config_mk
    echo "#define CONFIG_STATIC_EXECUTABLE  1" >> $config_h
fi

case $TARGET_OS in
    linux-*|darwin-*)
        echo "#define CONFIG_IOVEC 1" >> $config_h
        ;;
esac

echo "#define CONFIG_$CONFIG_OS   1" >> $config_h
if [ $BSD = 1 ] ; then
    echo "#define CONFIG_BSD       1" >> $config_h
    echo "#define O_LARGEFILE      0" >> $config_h
    echo "#define MAP_ANONYMOUS    MAP_ANON" >> $config_h
fi

echo "#define CONFIG_ANDROID       1" >> $config_h

if [ "$GLES_INCLUDE" -a "$GLES_LIBS" ]; then
    echo "#define CONFIG_ANDROID_OPENGLES 1" >> $config_h
fi

log "Generate   : $config_h"

echo "Ready to go. Type 'make' to build emulator"
