/**
 * author: Chenxiong (R0r5ch4ch) Qian
 * date: 2014-11-16
 */

#include "DECAF_shared/utils/OutputWrapper.h"
#include "static_field_access.h"


jniHookHandler hookStaticFieldAccess(int curPC, int dvmStartAddr, CPUState* env){
	switch (curPC - dvmStartAddr){
		case GetStaticObjectField_OFFSET:
			hookGetStaticObjectField(env, 1);
			return hookGetStaticObjectField;
		case GetStaticBooleanField_OFFSET:
			hookGetStaticBooleanField(env, 1);
			return hookGetStaticBooleanField;
		case GetStaticByteField_OFFSET:
			hookGetStaticByteField(env, 1);
			return hookGetStaticByteField;
		case GetStaticCharField_OFFSET:
			hookGetStaticCharField(env, 1);
			return hookGetStaticCharField;
		case GetStaticShortField_OFFSET:
			hookGetStaticShortField(env, 1);
			return hookGetStaticShortField;
		case GetStaticIntField_OFFSET:
			hookGetStaticIntField(env, 1);
			return hookGetStaticIntField;
		case GetStaticLongField_OFFSET:
			hookGetStaticLongField(env, 1);
			return hookGetStaticLongField;
		case GetStaticFloatField_OFFSET:
			hookGetStaticFloatField(env, 1);
			return hookGetStaticFloatField;
		case GetStaticDoubleField_OFFSET:
			hookGetStaticDoubleField(env, 1);
			return hookGetStaticDoubleField;

		case SetStaticObjectField_OFFSET:
			hookSetStaticObjectField(env, 1);
			return hookSetStaticObjectField;
		case SetStaticBooleanField_OFFSET:
			hookSetStaticBooleanField(env, 1);
			return hookSetStaticBooleanField;
		case SetStaticByteField_OFFSET:
			hookSetStaticByteField(env, 1);
			return hookSetStaticByteField;
		case SetStaticCharField_OFFSET:
			hookSetStaticCharField(env, 1);
			return hookSetStaticCharField;
		case SetStaticShortField_OFFSET:
			hookSetStaticShortField(env, 1);
			return hookSetStaticShortField;
		case SetStaticIntField_OFFSET:
			hookSetStaticIntField(env, 1);
			return hookSetStaticIntField;
		case SetStaticLongField_OFFSET:
			hookSetStaticLongField(env, 1);
			return hookSetStaticLongField;
		case SetStaticFloatField_OFFSET:
			hookSetStaticFloatField(env, 1);
			return hookSetStaticFloatField;
		case SetStaticDoubleField_OFFSET:
			hookSetStaticDoubleField(env, 1);
			return hookSetStaticDoubleField;
	}
	return NULL;
}

/*
 * _ctype GetStatic##_jname##Field(JNIEnv* env, jclass jclazz, 
 * 				jfieldID fieldID)
 */
int addrGetStaticField = -1;
int getStaticFieldTaint = 0;
void hookGetStaticField(CPUState* env, int isStart, int isObjectRef){
	DECAF_printf("GetStaticField[%d]\n", isStart);
	if (isStart && addrGetStaticField == -1){
		assert(DECAF_read_mem(env, env->regs[2] + OFFSET_STATIC_FIELD_TAINT,
					&getStaticFieldTaint, 4) != -1);
		addrGetStaticField = env->regs[2];
		DECAF_printf("	StaticField@%x has taint: %x\n", env->regs[2], getStaticFieldTaint);
	}else{
		if (addrGetStaticField != -1){
			if (getStaticFieldTaint > 0){
				if (isObjectRef){
					addTaint(env->regs[0], getStaticFieldTaint);
				}
				addTaintToReg(0, getStaticFieldTaint);
				getStaticFieldTaint = 0;
			}
			addrGetStaticField = -1;
		}
	}
}

/*
 * void SetStatic##_jname##Field(JNIEnv* env, jclass jclazz, 
 * 			jfieldID fieldID, _ctype value)
 */
void hookSetStaticField(CPUState* env, int isStart, int isObjectRef){
	DECAF_printf("SetStaticField[%d]\n", isStart);
	if (isStart){
		int fieldTaint = getRegTaint(3);
		if (isObjectRef){
			fieldTaint |= getTaint(env->regs[3]);
		}
		if (fieldTaint > 0){
			DECAF_printf("		Set StaticField@%x with taint:%x\n", 
					env->regs[2] + OFFSET_STATIC_FIELD_TAINT, fieldTaint);
			assert(DECAF_write_mem(env, env->regs[2] + OFFSET_STATIC_FIELD_TAINT,
						&fieldTaint, 4) > 0);
		}
	}
}

void hookGetStaticObjectField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 1);
}

void hookGetStaticBooleanField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 0);
}

void hookGetStaticByteField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 0);
}

void hookGetStaticCharField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 0);
}

void hookGetStaticShortField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 0);
}

void hookGetStaticIntField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 0);
}

void hookGetStaticLongField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 0);
}

void hookGetStaticFloatField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 0);
}

void hookGetStaticDoubleField(CPUState* env, int isStart){
	hookGetStaticField(env, isStart, 0);
}

void hookSetStaticObjectField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 1);
}

void hookSetStaticBooleanField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 0);
}

void hookSetStaticByteField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 0);
}

void hookSetStaticCharField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 0);
}

void hookSetStaticShortField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 0);
}

void hookSetStaticIntField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 0);
}

void hookSetStaticLongField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 0);
}

void hookSetStaticFloatField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 0);
}

void hookSetStaticDoubleField(CPUState* env, int isStart){
	hookSetStaticField(env, isStart, 0);
}
