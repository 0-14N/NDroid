#ifndef _DVM_OFFSETS_H
#define _DVM_OFFSETS_H

#ifdef __cplusplus

extern "C"
{
#endif

/**
 * When Java calls Native methods,
 * "dvmCallJNIMethod" should be called.
 */
#define OFFSET_DVM_CALL_JNI_METHOD 0x00050f84


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
#define OFFSET_DVM_INTERPRET 0x0002E128

#define OFFSET_DVM_CALL_METHODV	0x00063830
#define OFFSET_DVM_CALL_METHODV_CALL_INTERPRET 0x000639D4
#define OFFSET_DVM_CALL_METHODV_RET_INTERPRET  0x000639D8

#define OFFSET_DVM_CALL_METHODA 0x0006367C
#define OFFSET_DVM_CALL_METHODA_CALL_INTERPRET 0x00063816
#define OFFSET_DVM_CALL_METHODA_RET_INTERPRET  0x0006381A

#ifdef __cplusplus
}
#endif

#endif
