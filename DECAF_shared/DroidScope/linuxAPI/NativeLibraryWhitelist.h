/**
 * Copyright (C) <2012> <Syracuse System Security (Sycure) Lab>
 *
 * This library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file NativeLibraryWhitelist.h
 *   Creates a list of known native libraries for the Android system.
 * @author Lok Yan
 * @date 5 Jan 2012
 */

#ifndef NATIVE_LIBRARY_WHITELIST_H
#define NATIVE_LIBRARY_WHITELIST_H

#include "DECAF_shared/utils/HashtableWrapper.h"

static void NativeLibraryWhitelist_free(StringHashtable* pTable)
{
  StringHashtable_free(pTable);
}

static StringHashtable* NativeLibraryWhitelist_new()
{
  StringHashtable* pTable = StringHashtable_new();
  if (pTable == NULL)
  {
    return (pTable);
  }

	/*
  StringHashtable_add(pTable, "/lib/egl/libGLES_android.so");
  StringHashtable_add(pTable, "/lib/hw/gps.goldfish.so");
  StringHashtable_add(pTable, "/lib/hw/gralloc.default.so");
  StringHashtable_add(pTable, "/lib/hw/sensors.goldfish.so");
  StringHashtable_add(pTable, "/lib/invoke_mock_media_player.so");
  StringHashtable_add(pTable, "/lib/libacc.so");
  StringHashtable_add(pTable, "/lib/libandroid_runtime.so");
  StringHashtable_add(pTable, "/lib/libandroid_servers.so");
  StringHashtable_add(pTable, "/lib/libandroid.so");
  StringHashtable_add(pTable, "/lib/libaudioeffect_jni.so");
  StringHashtable_add(pTable, "/lib/libaudioflinger.so");
  StringHashtable_add(pTable, "/lib/libbinder.so");
  StringHashtable_add(pTable, "/lib/libcamera_client.so");
  StringHashtable_add(pTable, "/lib/libcameraservice.so");
  StringHashtable_add(pTable, "/lib/libc_malloc_debug_leak.so");
  StringHashtable_add(pTable, "/lib/libc_malloc_debug_qemu.so");
  StringHashtable_add(pTable, "/lib/libcrypto.so");
  StringHashtable_add(pTable, "/lib/libc.so");
  StringHashtable_add(pTable, "/lib/libctest.so");
  StringHashtable_add(pTable, "/lib/libcutils.so");
  StringHashtable_add(pTable, "/lib/libdbus.so");
  StringHashtable_add(pTable, "/lib/libdiskconfig.so");
  StringHashtable_add(pTable, "/lib/libdl.so");
  StringHashtable_add(pTable, "/lib/libdrm1_jni.so");
  StringHashtable_add(pTable, "/lib/libdrm1.so");
  StringHashtable_add(pTable, "/lib/libdvm.so");
  StringHashtable_add(pTable, "/lib/libeffects.so");
  StringHashtable_add(pTable, "/lib/libEGL.so");
  StringHashtable_add(pTable, "/lib/libemoji.so");
  StringHashtable_add(pTable, "/lib/libETC1.so");
  StringHashtable_add(pTable, "/lib/libexif.so");
  StringHashtable_add(pTable, "/lib/libexpat.so");
  StringHashtable_add(pTable, "/lib/libFFTEm.so");
  StringHashtable_add(pTable, "/lib/libGLESv1_CM.so");
  StringHashtable_add(pTable, "/lib/libGLESv2.so");
  StringHashtable_add(pTable, "/lib/libgui.so");
  StringHashtable_add(pTable, "/lib/libhardware_legacy.so");
  StringHashtable_add(pTable, "/lib/libhardware.so");
  StringHashtable_add(pTable, "/lib/libicui18n.so");
  StringHashtable_add(pTable, "/lib/libicuuc.so");
  StringHashtable_add(pTable, "/lib/libiprouteutil.so");
  StringHashtable_add(pTable, "/lib/libjnigraphics.so");
  StringHashtable_add(pTable, "/lib/libjni_latinime.so");
  StringHashtable_add(pTable, "/lib/libjni_pinyinime.so");
  StringHashtable_add(pTable, "/lib/libjpeg.so");
  StringHashtable_add(pTable, "/lib/liblog.so");
  StringHashtable_add(pTable, "/lib/libmedia_jni.so");
  StringHashtable_add(pTable, "/lib/libmediaplayerservice.so");
  StringHashtable_add(pTable, "/lib/libmedia.so");
  StringHashtable_add(pTable, "/lib/libmock_ril.so");
  StringHashtable_add(pTable, "/lib/libm.so");
  StringHashtable_add(pTable, "/lib/libnativehelper.so");
  StringHashtable_add(pTable, "/lib/libnetlink.so");
  StringHashtable_add(pTable, "/lib/libnetutils.so");
  StringHashtable_add(pTable, "/lib/libnfc_ndef.so");
  StringHashtable_add(pTable, "/lib/libOpenSLES.so");
  StringHashtable_add(pTable, "/lib/libpagemap.so");
  StringHashtable_add(pTable, "/lib/libpixelflinger.so");
  StringHashtable_add(pTable, "/lib/libreference-cdma-sms.so");
  StringHashtable_add(pTable, "/lib/libreference-ril.so");
  StringHashtable_add(pTable, "/lib/libril.so");
  StringHashtable_add(pTable, "/lib/librtp_jni.so");
  StringHashtable_add(pTable, "/lib/libsensorservice.so");
  StringHashtable_add(pTable, "/lib/libskiagl.so");
  StringHashtable_add(pTable, "/lib/libskia.so");
  StringHashtable_add(pTable, "/lib/libsonivox.so");
  StringHashtable_add(pTable, "/lib/libsoundpool.so");
  StringHashtable_add(pTable, "/lib/libsqlite_jni.so");
  StringHashtable_add(pTable, "/lib/libsqlite.so");
  StringHashtable_add(pTable, "/lib/libSR_AudioIn.so");
  StringHashtable_add(pTable, "/lib/libsrec_jni.so");
  StringHashtable_add(pTable, "/lib/libssl.so");
  StringHashtable_add(pTable, "/lib/libstagefright_amrnb_common.so");
  StringHashtable_add(pTable, "/lib/libstagefright_avc_common.so");
  StringHashtable_add(pTable, "/lib/libstagefright_color_conversion.so");
  StringHashtable_add(pTable, "/lib/libstagefright_enc_common.so");
  StringHashtable_add(pTable, "/lib/libstagefright_foundation.so");
  StringHashtable_add(pTable, "/lib/libstagefright_omx.so");
  StringHashtable_add(pTable, "/lib/libstagefright.so");
  StringHashtable_add(pTable, "/lib/libstdc++.so");
  StringHashtable_add(pTable, "/lib/libstlport.so");
  StringHashtable_add(pTable, "/lib/libsurfaceflinger_client.so");
  StringHashtable_add(pTable, "/lib/libsurfaceflinger.so");
  StringHashtable_add(pTable, "/lib/libsystem_server.so");
  StringHashtable_add(pTable, "/lib/libsysutils.so");
  StringHashtable_add(pTable, "/lib/libterm.so");
  StringHashtable_add(pTable, "/lib/libthread_db.so");
  StringHashtable_add(pTable, "/lib/libttspico.so");
  StringHashtable_add(pTable, "/lib/libttssynthproxy.so");
  StringHashtable_add(pTable, "/lib/libui.so");
  StringHashtable_add(pTable, "/lib/libutils.so");
  StringHashtable_add(pTable, "/lib/libvorbisidec.so");
  StringHashtable_add(pTable, "/lib/libwebcore.so");
  StringHashtable_add(pTable, "/lib/libwpa_client.so");
  StringHashtable_add(pTable, "/lib/libz.so");
  StringHashtable_add(pTable, "/lib/soundfx/libbundlewrapper.so");
  StringHashtable_add(pTable, "/lib/soundfx/libreverbwrapper.so");
  StringHashtable_add(pTable, "/lib/soundfx/libvisualizer.so");
	*/

		/* START NDROID */
		//the following code is produced by 'NDroid/scripts/pullMemMaps.py'
StringHashtable_add(pTable, "/init");
StringHashtable_add(pTable, "[heap]");
StringHashtable_add(pTable, "/dev/__properties__");
StringHashtable_add(pTable, "[stack]");
StringHashtable_add(pTable, "/bin/app_process");
StringHashtable_add(pTable, "/bin/linker");
StringHashtable_add(pTable, "/lib/liblog.so");
StringHashtable_add(pTable, "/lib/libc.so");
StringHashtable_add(pTable, "/lib/libstdc++.so");
StringHashtable_add(pTable, "/lib/libm.so");
StringHashtable_add(pTable, "/lib/libcutils.so");
StringHashtable_add(pTable, "/lib/libutils.so");
StringHashtable_add(pTable, "/lib/libcorkscrew.so");
StringHashtable_add(pTable, "/lib/libgccdemangle.so");
StringHashtable_add(pTable, "/lib/libz.so");
StringHashtable_add(pTable, "/lib/libbinder.so");
StringHashtable_add(pTable, "/lib/libandroid_runtime.so");
StringHashtable_add(pTable, "/lib/libandroidfw.so");
StringHashtable_add(pTable, "/lib/libskia.so");
StringHashtable_add(pTable, "/lib/libemoji.so");
StringHashtable_add(pTable, "/lib/libjpeg.so");
StringHashtable_add(pTable, "/lib/libexpat.so");
StringHashtable_add(pTable, "/lib/libnativehelper.so");
StringHashtable_add(pTable, "/lib/libstlport.so");
StringHashtable_add(pTable, "/lib/libnetutils.so");
StringHashtable_add(pTable, "/lib/libui.so");
StringHashtable_add(pTable, "/lib/libhardware.so");
StringHashtable_add(pTable, "/lib/libgui.so");
StringHashtable_add(pTable, "/lib/libhardware_legacy.so");
StringHashtable_add(pTable, "/lib/libwpa_client.so");
StringHashtable_add(pTable, "/lib/libEGL.so");
StringHashtable_add(pTable, "/lib/libGLES_trace.so");
StringHashtable_add(pTable, "/lib/libGLESv2.so");
StringHashtable_add(pTable, "/lib/libcamera_client.so");
StringHashtable_add(pTable, "/lib/libsqlite.so");
StringHashtable_add(pTable, "/lib/libicuuc.so");
StringHashtable_add(pTable, "/lib/libgabi++.so");
StringHashtable_add(pTable, "/lib/libicui18n.so");
StringHashtable_add(pTable, "/lib/libdvm.so");
StringHashtable_add(pTable, "/lib/libGLESv1_CM.so");
StringHashtable_add(pTable, "/lib/libETC1.so");
StringHashtable_add(pTable, "/lib/libsonivox.so");
StringHashtable_add(pTable, "/lib/libcrypto.so");
StringHashtable_add(pTable, "/lib/libssl.so");
StringHashtable_add(pTable, "/lib/libmedia.so");
StringHashtable_add(pTable, "/lib/libstagefright_foundation.so");
StringHashtable_add(pTable, "/lib/libaudioutils.so");
StringHashtable_add(pTable, "/lib/libspeexresampler.so");
StringHashtable_add(pTable, "/lib/libmedia_native.so");
StringHashtable_add(pTable, "/lib/libusbhost.so");
StringHashtable_add(pTable, "/lib/libharfbuzz.so");
StringHashtable_add(pTable, "/lib/libhwui.so");
StringHashtable_add(pTable, "/dev/ashmem/dalvik-heap");
StringHashtable_add(pTable, "/dev/ashmem/dalvik-bitmap-1");
StringHashtable_add(pTable, "/dev/ashmem/dalvik-bitmap-2");
StringHashtable_add(pTable, "/dev/ashmem/dalvik-mark-stack");
StringHashtable_add(pTable, "/dev/ashmem/dalvik-card-table");
StringHashtable_add(pTable, "/dev/ashmem/dalvik-LinearAlloc");
StringHashtable_add(pTable, "/framework/core.jar");
StringHashtable_add(pTable, "/framework/core.odex");
StringHashtable_add(pTable, "/dev/ashmem/dalvik-aux-structure");
StringHashtable_add(pTable, "/framework/core-junit.jar");
StringHashtable_add(pTable, "/framework/core-junit.odex");
StringHashtable_add(pTable, "/framework/bouncycastle.jar");
StringHashtable_add(pTable, "/framework/bouncycastle.odex");
StringHashtable_add(pTable, "/framework/framework.jar");
StringHashtable_add(pTable, "/framework/android.policy.jar");
StringHashtable_add(pTable, "/framework/services.jar");
StringHashtable_add(pTable, "/framework/apache-xml.jar");
StringHashtable_add(pTable, "/lib/libstagefright_yuv.so");
StringHashtable_add(pTable, "/framework/ext.jar");
StringHashtable_add(pTable, "/framework/ext.odex");
StringHashtable_add(pTable, "/framework/framework.odex");
StringHashtable_add(pTable, "/framework/android.policy.odex");
StringHashtable_add(pTable, "/framework/services.odex");
StringHashtable_add(pTable, "/framework/apache-xml.odex");
StringHashtable_add(pTable, "/lib/libjavacore.so");
StringHashtable_add(pTable, "/usr/icu/icudt48l.dat");
StringHashtable_add(pTable, "/dev/ashmem/SurfaceFlinger");
StringHashtable_add(pTable, "/framework/framework-res.apk");
StringHashtable_add(pTable, "/fonts/Roboto-Regular.ttf");
StringHashtable_add(pTable, "/lib/libmedia_jni.so");
StringHashtable_add(pTable, "/lib/libstagefright.so");
StringHashtable_add(pTable, "/lib/libdrmframework.so");
StringHashtable_add(pTable, "/lib/libstagefright_omx.so");
StringHashtable_add(pTable, "/lib/libvorbisidec.so");
StringHashtable_add(pTable, "/lib/libchromium_net.so");
StringHashtable_add(pTable, "/lib/libstagefright_enc_common.so");
StringHashtable_add(pTable, "/lib/libstagefright_avc_common.so");
StringHashtable_add(pTable, "/lib/libmtp.so");
StringHashtable_add(pTable, "/lib/libexif.so");
StringHashtable_add(pTable, "/lib/libstagefright_amrnb_common.so");
StringHashtable_add(pTable, "/lib/libandroid.so");
StringHashtable_add(pTable, "/dev/ashmem/gralloc-buffer");
StringHashtable_add(pTable, "/lib/librs_jni.so");
StringHashtable_add(pTable, "/lib/libRS.so");
StringHashtable_add(pTable, "/lib/libbcc.so");
StringHashtable_add(pTable, "/lib/libbcinfo.so");
StringHashtable_add(pTable, "/lib/libwebcore.so");
StringHashtable_add(pTable, "/usr/share/zoneinfo/zoneinfo.dat");
StringHashtable_add(pTable, "/dev/binder");
StringHashtable_add(pTable, "/lib/libandroid_servers.so");
StringHashtable_add(pTable, "/lib/libsystem_server.so");
StringHashtable_add(pTable, "/lib/libsensorservice.so");
StringHashtable_add(pTable, "/lib/libsurfaceflinger.so");
StringHashtable_add(pTable, "/lib/libinput.so");
StringHashtable_add(pTable, "/lib/libsuspend.so");
StringHashtable_add(pTable, "/lib/hw/sensors.goldfish.so");
StringHashtable_add(pTable, "/lib/hw/power.goldfish.so");
StringHashtable_add(pTable, "/lib/hw/lights.goldfish.so");
StringHashtable_add(pTable, "/lib/libsoundpool.so");
StringHashtable_add(pTable, "/lib/hw/gralloc.goldfish.so");
StringHashtable_add(pTable, "/fonts/AndroidClock.ttf");
StringHashtable_add(pTable, "/fonts/AndroidClock_Highlight.ttf");
StringHashtable_add(pTable, "/app/SettingsProvider.apk");
StringHashtable_add(pTable, "/app/SettingsProvider.odex");
StringHashtable_add(pTable, "/data/data/com.android.providers.settings/databases/settings.db-shm");
StringHashtable_add(pTable, "/dev/ashmem/CursorWindow:");
StringHashtable_add(pTable, "/data/locksettings.db-shm");
StringHashtable_add(pTable, "/lib/libOpenglSystemCommon.so");
StringHashtable_add(pTable, "/lib/lib_renderControl_enc.so");
StringHashtable_add(pTable, "/lib/libGLESv2_enc.so");
StringHashtable_add(pTable, "/lib/libGLESv1_enc.so");
StringHashtable_add(pTable, "/lib/hw/gralloc.default.so");
StringHashtable_add(pTable, "/app/Contacts.apk");
StringHashtable_add(pTable, "/app/Launcher2.apk");
StringHashtable_add(pTable, "/app/Mms.apk");
StringHashtable_add(pTable, "/app/VoiceDialer.apk");
StringHashtable_add(pTable, "/app/Browser.apk");
StringHashtable_add(pTable, "/app/Calculator.apk");
StringHashtable_add(pTable, "/app/Calendar.apk");
StringHashtable_add(pTable, "/dev/ashmem/decode_fd");
StringHashtable_add(pTable, "/dev/ashmem/dalvik-jit-code-cache");
StringHashtable_add(pTable, "/app/Music.apk");
StringHashtable_add(pTable, "/lib/hw/gps.goldfish.so");
StringHashtable_add(pTable, "/app/Gallery2.apk");
StringHashtable_add(pTable, "/dev/ashmem/AudioFlinger::Client");
StringHashtable_add(pTable, "/app/SystemUI.apk");
StringHashtable_add(pTable, "/app/SystemUI.odex");
StringHashtable_add(pTable, "/fonts/Roboto-Light.ttf");
StringHashtable_add(pTable, "/fonts/DroidNaskh-Regular-SystemUI.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansEthiopic-Regular.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansHebrew-Regular.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansThai.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansArmenian.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansGeorgian.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansDevanagari-Regular.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansTamil-Regular.ttf");
StringHashtable_add(pTable, "/fonts/AnjaliNewLipi-light.ttf");
StringHashtable_add(pTable, "/fonts/Lohit-Bengali.ttf");
StringHashtable_add(pTable, "/fonts/Lohit-Kannada.ttf");
StringHashtable_add(pTable, "/fonts/Lohit-Telugu.ttf");
StringHashtable_add(pTable, "/fonts/AndroidEmoji.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansFallback.ttf");
StringHashtable_add(pTable, "/fonts/MTLmr3m.ttf");
StringHashtable_add(pTable, "/app/TelephonyProvider.apk");
StringHashtable_add(pTable, "/app/Phone.apk");
StringHashtable_add(pTable, "/app/Phone.odex");
StringHashtable_add(pTable, "/app/TelephonyProvider.odex");
StringHashtable_add(pTable, "/app/Launcher2.odex");
StringHashtable_add(pTable, "/app/Settings.apk");
StringHashtable_add(pTable, "/app/QuickSearchBox.apk");
StringHashtable_add(pTable, "/app/DeskClock.apk");
StringHashtable_add(pTable, "/fonts/Roboto-Bold.ttf");
StringHashtable_add(pTable, "/app/Settings.odex");
StringHashtable_add(pTable, "/bin/servicemanager");
StringHashtable_add(pTable, "/bin/vold");
StringHashtable_add(pTable, "/lib/libsysutils.so");
StringHashtable_add(pTable, "/lib/libdiskconfig.so");
StringHashtable_add(pTable, "/app/UserDictionaryProvider.apk");
StringHashtable_add(pTable, "/app/UserDictionaryProvider.odex");
StringHashtable_add(pTable, "/app/ContactsProvider.apk");
StringHashtable_add(pTable, "/app/ContactsProvider.odex");
StringHashtable_add(pTable, "/app/ApplicationsProvider.apk");
StringHashtable_add(pTable, "/app/ApplicationsProvider.odex");
StringHashtable_add(pTable, "/app/SpeechRecorder.apk");
StringHashtable_add(pTable, "/app/TaintDroidNotify.apk");
StringHashtable_add(pTable, "/app/VideoEditor.apk");
StringHashtable_add(pTable, "/app/WAPPushManager.apk");
StringHashtable_add(pTable, "/app/WAPPushManager.odex");
StringHashtable_add(pTable, "/bin/debuggerd");
StringHashtable_add(pTable, "/bin/rild");
StringHashtable_add(pTable, "/lib/libril.so");
StringHashtable_add(pTable, "/lib/libreference-ril.so");
StringHashtable_add(pTable, "/bin/surfaceflinger");
StringHashtable_add(pTable, "/dev/graphics/fb0");
StringHashtable_add(pTable, "/lib/egl/libGLES_android.so");
StringHashtable_add(pTable, "/lib/libpixelflinger.so");
StringHashtable_add(pTable, "/dev/ashmem/mspace");
StringHashtable_add(pTable, "/app/Contacts.odex");
StringHashtable_add(pTable, "/bin/drmserver");
StringHashtable_add(pTable, "/lib/drm/libfwdlockengine.so");
StringHashtable_add(pTable, "/bin/mediaserver");
StringHashtable_add(pTable, "/lib/libaudioflinger.so");
StringHashtable_add(pTable, "/lib/libcommon_time_client.so");
StringHashtable_add(pTable, "/lib/libeffects.so");
StringHashtable_add(pTable, "/lib/libpowermanager.so");
StringHashtable_add(pTable, "/lib/libcameraservice.so");
StringHashtable_add(pTable, "/lib/libmediaplayerservice.so");
StringHashtable_add(pTable, "/lib/libaah_rtp.so");
StringHashtable_add(pTable, "/lib/hw/camera.goldfish.so");
StringHashtable_add(pTable, "/lib/hw/audio_policy.default.so");
StringHashtable_add(pTable, "/lib/hw/audio.primary.goldfish.so");
StringHashtable_add(pTable, "/lib/hw/local_time.default.so");
StringHashtable_add(pTable, "/lib/soundfx/libbundlewrapper.so");
StringHashtable_add(pTable, "/lib/soundfx/libreverbwrapper.so");
StringHashtable_add(pTable, "/lib/soundfx/libvisualizer.so");
StringHashtable_add(pTable, "/lib/soundfx/libaudiopreprocessing.so");
StringHashtable_add(pTable, "/lib/libwebrtc_audio_preprocessing.so");
StringHashtable_add(pTable, "/lib/soundfx/libdownmix.so");
StringHashtable_add(pTable, "/bin/dbus-daemon");
StringHashtable_add(pTable, "/lib/libdbus.so");
StringHashtable_add(pTable, "/bin/installd");
StringHashtable_add(pTable, "/app/CalendarProvider.apk");
StringHashtable_add(pTable, "/framework/android.test.runner.jar");
StringHashtable_add(pTable, "/framework/android.test.runner.odex");
StringHashtable_add(pTable, "/app/CalendarProvider.odex");
StringHashtable_add(pTable, "/bin/keystore");
StringHashtable_add(pTable, "/lib/hw/keystore.default.so");
StringHashtable_add(pTable, "/lib/libkeystore_client.so");
StringHashtable_add(pTable, "/app/DownloadProvider.apk");
StringHashtable_add(pTable, "/app/MediaProvider.apk");
StringHashtable_add(pTable, "/app/DrmProvider.apk");
StringHashtable_add(pTable, "/app/DownloadProvider.odex");
StringHashtable_add(pTable, "/app/MediaProvider.odex");
StringHashtable_add(pTable, "/data/data/com.android.providers.media/databases/internal.db-shm");
StringHashtable_add(pTable, "/app/DrmProvider.odex");
StringHashtable_add(pTable, "/bin/qemud");
StringHashtable_add(pTable, "/data/data/com.android.inputmethod.latin/files/userunigram.en_US.dict");
StringHashtable_add(pTable, "/app/LatinIME.apk");
StringHashtable_add(pTable, "/app/LatinIME.odex");
StringHashtable_add(pTable, "/lib/libjni_latinime.so");
StringHashtable_add(pTable, "/data/data/com.android.inputmethod.latin/files/contacts.en_US.dict");
StringHashtable_add(pTable, "/app/Exchange2.apk");
StringHashtable_add(pTable, "/app/Exchange2.odex");
StringHashtable_add(pTable, "/lib/libdrmframework_jni.so");
StringHashtable_add(pTable, "/app/Mms.odex");
StringHashtable_add(pTable, "/bin/ash");
StringHashtable_add(pTable, "/sbin/adbd");
StringHashtable_add(pTable, "/app/Email.apk");
StringHashtable_add(pTable, "/app/Email.odex");
StringHashtable_add(pTable, "/app/DeskClock.odex");
StringHashtable_add(pTable, "/app/VoiceDialer.odex");
StringHashtable_add(pTable, "/lib/libsrec_jni.so");
StringHashtable_add(pTable, "/usr/srec/config/en.us/models/generic11_f.swimdl");
StringHashtable_add(pTable, "/usr/srec/config/en.us/models/generic11_m.swimdl");
StringHashtable_add(pTable, "/fonts/DroidSansHebrew-Bold.ttf");
StringHashtable_add(pTable, "/fonts/DroidSansTamil-Bold.ttf");
StringHashtable_add(pTable, "/app/Calendar.odex");
StringHashtable_add(pTable, "/app/Browser.odex");
StringHashtable_add(pTable, "/data/data/com.android.browser/databases/browser2.db-shm");
StringHashtable_add(pTable, "/data/data/com.android.browser/cache/webviewCacheChromium/index");
StringHashtable_add(pTable, "/data/data/com.android.browser/cache/webviewCacheChromium/data_0");
StringHashtable_add(pTable, "/data/data/com.android.browser/cache/webviewCacheChromium/data_1");
StringHashtable_add(pTable, "/data/data/com.android.browser/cache/webviewCacheChromium/data_2");
StringHashtable_add(pTable, "/data/data/com.android.browser/cache/webviewCacheChromium/data_3");
StringHashtable_add(pTable, "/bin/netd");
StringHashtable_add(pTable, "/lib/libmdnssd.so");
StringHashtable_add(pTable, "/app/Gallery2.odex");
StringHashtable_add(pTable, "/app/Calculator.odex");
StringHashtable_add(pTable, "/app/Music.odex");
StringHashtable_add(pTable, "directory");
/* END NDROID */

  return (pTable);
}

#endif//NATIVE_LIBRARY_WHITELIST_H
