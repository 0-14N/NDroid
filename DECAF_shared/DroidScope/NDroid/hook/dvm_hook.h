/*
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-7-24
 */
#ifndef _DVM_HOOK_H
#define _DVM_HOOK_H

#ifdef __cplusplus

extern "C"
{
#endif

#include "dvm_offsets.h"

//===========method info begin========
/*
 * struct Method {
 *    ClassObject*    clazz;
 *    u4              accessFlags;
 *    u2             methodIndex;
 *    u2              registersSize;  // ins + locals
 *    u2              outsSize;
 *    u2              insSize;
 *    const char*     name;
 *    DexProto        prototype;
 *    const char*     shorty;
 *    const u2*       insns;          // instructions, in memory-mapped .dex
 *    int             jniArgInfo;
 *    DalvikBridgeFunc nativeFunc;
 *    bool fastJni;
 *    bool noRef;
 *    bool shouldTrace;
 *    const RegisterMap* registerMap;
 *    bool            inProfile;
 * };
 *
 */
#define METHOD_ACCESS_FLAG_OFFSET 4
#define METHOD_REGISTER_SIZE_OFFSET 10
#define METHOD_OUTS_SIZE_OFFSET 12
#define METHOD_INS_SIZE_OFFSET 14
#define METHOD_NAME_OFFSET 16
#define METHOD_SHORTY_OFFSET 28
#define METHOD_INSN_OFFSET 32
#define ACC_STATIC 0x0008
#define ACC_NATIVE 0x0100

/*
 * struct Object {
 *    ClassObject*    clazz;
 *    u4              lock;
 * };
 *
 * struct ClassObject : Object {
 * 	#ifdef WITH_TAINT_TRACKING
 *   	// x2 space for interleaved taint tags
 *    // CLASS_FIELD_SLOTS = 8
 *   	u4              instanceData[CLASS_FIELD_SLOTS*2];
 *	#else
 *   	u4              instanceData[CLASS_FIELD_SLOTS];
 *	#endif
 *   const char*     descriptor;
 *   char*           descriptorAlloc;
 *   ...
 * }
 *
 * struct StringObject : Object {
 * 	 u4							instanceData[1];
 *	 ...
 * }
 *
 * **instanceData[0] stores reference to char array (ArrayObject)
 *   instanceData[3] stores number of characters in the char array
 *
 * struct ArrayObject : Object {
 * 	 u4 						length;
 * 	 Taint					taint;
 * 	 u8 						contents[1];
 * }
 */
#define CLASS_DESCRIPTOR_OFFSET 40

#define STRING_INSTANCE_DATA_OFFSET 8
#define STRING_LENGTH_OFFSET 20
#define STRING_TAINT_OFFSET 12
#define STRING_ARRAY_LENGTH_OFFSET 8
#define STRING_CONTENT_OFFSET 16
//===========method info end==========

	void dvmCallJNIMethodCallback(CPUState* env);

	void dvmPlatformInvokeCallback(CPUState* env);

#ifdef __cplusplus
}
#endif

#endif
