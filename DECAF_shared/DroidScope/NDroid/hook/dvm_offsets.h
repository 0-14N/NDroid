#ifndef _DVM_OFFSETS_H
#define _DVM_OFFSETS_H

#ifdef __cplusplus

extern "C"
{
#endif



	/**
	 * 								 dvmCallMethodV
	 *								________________					  dvmInterpret	
	 * 0x00063830 -->|              	|     __\ _______________
	 *               |              	|    /  /|               |<-- 0x0002e128
	 *               |								|   /    |							 |
	 *               |________________|  /     |							 |
	 * 0x000639d4 -->|blx dvmInterpret| /      |_______________|
	 *               |________________|        /
	 * 0x000639d8 -->|________________| /_____/
	 * 							 |								| \
	 * 							 |								|
	 * 							 |________________|
	 */
/*
 *
 * We drop this the multi-level implementation!
 * Replace it with Identifier flag implementation!!!
 * Please refer to *.c files under "jni_bridge"
 */

/*
#define OFFSET_DVM_INTERPRET 0x0002E128

#define OFFSET_DVM_CALL_METHODV	0x00063830
#define OFFSET_DVM_CALL_METHODV_CALL_INTERPRET 0x000639D4
#define OFFSET_DVM_CALL_METHODV_RET_INTERPRET  0x000639D8

#define OFFSET_DVM_CALL_METHODA 0x0006367C
#define OFFSET_DVM_CALL_METHODA_CALL_INTERPRET 0x00063816
#define OFFSET_DVM_CALL_METHODA_RET_INTERPRET  0x0006381A
*/

/**
 * Identifier Flag implementation:
 * ***********************************************************
 *
 * CallVoidMethod(..., jmethodID methodID, ...){
 *                                     \
 *                                      \
 *                                       \_________
 *                                                \|/
 * 		Method* meth = dvmGetVirtulizedMethod(..., methodID, ...);
 * 		          \
 * 		           \_________
 * 		                    \|/
 * 		dvmCallMethodV(..., meth, ...);
 * }                       \
 *                          \_________
 *                                   \|/
 * void dvmCallMethodV(..., Method* method, ...){
 *          							___________/
 *          						\|/
 * 		dvmInterpret(..., method, ...);A
 * }
 */

/**
 * When Java calls Native methods,
 * "dvmCallJNIMethod" should be called.
 */
#define OFFSET_DVM_CALL_JNI_METHOD_BEGIN 0x00050f84
#define OFFSET_DVM_CALL_JNI_METHOD_END 0x00051186

#define OFFSET_DVM_GET_VIRTULIZED_METHOD_BEGIN 0x0006f054
#define OFFSET_DVM_GET_VIRTULIZED_METHOD_END 0x0006f0b6

#define OFFSET_DVM_INTERPRET_BEGIN 0x0002e128
#define OFFSET_DVM_INTERPRET_END 0x0002e234

#define OFFSET_DVM_CREATE_STRING_FROM_CSTR_BEGIN 0x000587ee
#define OFFSET_DVM_CREATE_STRING_FROM_CSTR_END 0x000587ec   //special case!!!
#define OFFSET_DVM_CREATE_STRING_FROM_UNICODE_BEGIN 0x00058808
#define OFFSET_DVM_CREATE_STRING_FROM_UNICODE_END 0x00058848
#define OFFSET_DVM_STRING_OBJECT_CHARS_BEGIN 0x000588d6
#define OFFSET_DVM_STRING_OBJECT_CHARS_END 0x000588e0
#define OFFSET_DVM_CREATE_CSTR_FROM_STRING_BEGIN 0x0005884a
#define OFFSET_DVM_CREATE_CSTR_FROM_STRING_END 0x0005889a
#define OFFSET_DVM_GET_STRING_UTF_REGION_BEGIN 0x000588e2
#define OFFSET_DVM_GET_STRING_UTF_REGION_END 0x00058688

#ifdef __cplusplus
}
#endif

#endif
