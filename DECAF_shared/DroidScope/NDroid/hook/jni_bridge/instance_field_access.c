/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-15
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "instance_field_access.h"

//TODO: Currently, we ignore volatile fields

extern int addrJObjDvmDecodeIndirectRef;
extern int addrObjectDvmDecodeIndirectRef;

jniHookHandler hookInstanceFieldAccess(int curPC, int dvmStartAddr, CPUState* env){
	switch (curPC - dvmStartAddr){
		case GetObjectField_OFFSET:
			hookGetObjectField(env, 1);
			return hookGetObjectField;
		case GetBooleanField_OFFSET:
			hookGetBooleanField(env, 1);
			return hookGetBooleanField;
		case GetByteField_OFFSET:
			hookGetByteField(env, 1);
			return hookGetByteField;
		case GetCharField_OFFSET:
			hookGetCharField(env, 1);
			return hookGetCharField;
		case GetShortField_OFFSET:
			hookGetShortField(env, 1);
			return hookGetShortField;
		case GetIntField_OFFSET:
			hookGetIntField(env, 1);
			return hookGetIntField;
		case GetLongField_OFFSET:
			hookGetLongField(env, 1);
			return hookGetLongField;
		case GetFloatField_OFFSET:
			hookGetFloatField(env, 1);
			return hookGetFloatField;
		case GetDoubleField_OFFSET:
			hookGetDoubleField(env, 1);
			return hookGetDoubleField;

		case SetObjectField_OFFSET:
			hookSetObjectField(env, 1);
			return hookSetObjectField;
		case SetBooleanField_OFFSET:
			hookSetBooleanField(env, 1);
			return hookSetBooleanField;
		case SetByteField_OFFSET:
			hookSetByteField(env, 1);
			return hookSetByteField;
		case SetCharField_OFFSET:
			hookSetCharField(env, 1);
			return hookSetCharField;
		case SetShortField_OFFSET:
			hookSetShortField(env, 1);
			return hookSetShortField;
		case SetIntField_OFFSET:
			hookSetIntField(env, 1);
			return hookSetIntField;
		case SetLongField_OFFSET:
			hookSetLongField(env, 1);
			return hookSetLongField;
		case SetFloatField_OFFSET:
			hookSetFloatField(env, 1);
			return hookSetFloatField;
		case SetDoubleField_OFFSET:
			hookSetDoubleField(env, 1);
			return hookSetDoubleField;
	}
	return NULL;
}

/*
 * _ctype Get##_jname##Field(JNIEnv* env, jobject jobj,
 * 			jfieldID fieldID)
 */
int getInstanceFieldOffset = -1;
void hookGetInstanceField(CPUState* env, int isStart, int isObjectRef){
	DECAF_printf("GetInstanceField[%d]\n", isStart);
	if (isStart && getInstanceFieldOffset == -1){
		assert(DECAF_read_mem(env, 
					env->regs[2] + OFFSET_INSTANCE_FIELD_BYTEOFFSET,
				 &getInstanceFieldOffset, 4) != -1);	
		addrJObjDvmDecodeIndirectRef = env->regs[1];
	}else{
		if (getInstanceFieldOffset != -1){
			assert(addrObjectDvmDecodeIndirectRef != -1);
			//get field's taint
			int fieldTaint = 0;
			assert(DECAF_read_mem(env, addrObjectDvmDecodeIndirectRef + getInstanceFieldOffset + 4,
						&fieldTaint, 4) != -1);
			//set taint
			if (fieldTaint > 0){
				DECAF_printf("	get field@%x has taint:%x\n", 
						addrObjectDvmDecodeIndirectRef + getInstanceFieldOffset,
						fieldTaint);
				if (isObjectRef){
					addTaint(env->regs[0], fieldTaint);
				}
				addTaintToReg(0, fieldTaint);
			}

			addrObjectDvmDecodeIndirectRef = -1;
			getInstanceFieldOffset = -1;
		}
	}
}

/**
 * void Set##_jname##Field(JNIEnv* env, jobject jobj,
 * 			jfieldID fieldID, _ctype value)
 */
int setInstanceFieldOffset = -1;
void hookSetInstanceField(CPUState* env, int isStart, int isObjectRef){
	DECAF_printf("SetInstanceField[%d]\n", isStart);
	if (isStart && setInstanceFieldOffset == -1){
		assert(DECAF_read_mem(env, env->regs[2] + OFFSET_INSTANCE_FIELD_BYTEOFFSET,
					&setInstanceFieldOffset, 4) != -1);
		addrJObjDvmDecodeIndirectRef = env->regs[1];
	}else{
		if (setInstanceFieldOffset != -1){
			assert(addrObjectDvmDecodeIndirectRef != -1);
			//get taint
			int fieldTaint = getRegTaint(3);
			if (isObjectRef){
				fieldTaint |= getTaint(env->regs[3]);
			}
			//set taint
			if (fieldTaint > 0){
				assert(DECAF_write_mem(env, addrObjectDvmDecodeIndirectRef + setInstanceFieldOffset + 4,
						&fieldTaint, 4) != -1);	
				DECAF_printf("	set field@%x with taint:%x\n", 
						addrObjectDvmDecodeIndirectRef + setInstanceFieldOffset,
						fieldTaint);
			}

			addrObjectDvmDecodeIndirectRef = -1;
			setInstanceFieldOffset = -1;
		}
	}
}

void hookGetObjectField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 1);
}

void hookGetBooleanField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 0);
}

void hookGetByteField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 0);
}

void hookGetCharField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 0);
}

void hookGetShortField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 0);
}

void hookGetIntField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 0);
}

void hookGetLongField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 0);
}

void hookGetFloatField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 0);
}

void hookGetDoubleField(CPUState* env, int isStart){
	hookGetInstanceField(env, isStart, 0);
}

void hookSetObjectField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 1);
}

void hookSetBooleanField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 0);
}

void hookSetByteField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 0);
}

void hookSetCharField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 0);
}

void hookSetShortField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 0);
}

void hookSetIntField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 0);
}

void hookSetLongField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 0);
}

void hookSetFloatField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 0);
}

void hookSetDoubleField(CPUState* env, int isStart){
	hookSetInstanceField(env, isStart, 0);
}
