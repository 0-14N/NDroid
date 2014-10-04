#!/usr/bin/python
###################################################
# author: Chenxiong (R0r5ch4ch) Qian
# date: 2014-10-4
#
# run: python generate.py [libc.dyn|libm.dyn|...]
###################################################
import sys, string

IN_OUT_DIC = {"libc.dyn": "lib_c.h", "libm.dyn": "lib_m.h"}

def generateHeadFile(filename, funcOffsetDic):
    with open(filename, 'w') as headFile:
        #generate head
        flag = string.upper(filename.split(".")[0])
        defLine =  \
        """
#ifndef _FLAG_HOOK_H
#define _FLAG_HOOK_H
#ifdef __cplusplus

extern "C"
{
#endif
        """.replace("FLAG", flag)
        headFile.write(defLine)
        headFile.write("\n")

        includeLine = "#include \"sys_lib_hook.h\"\n\n"
        headFile.write(includeLine)

        flag = string.upper(filename.split(".")[0].split("_")[-1])
        for func in funcOffsetDic.keys():
            offset = "0x" + funcOffsetDic[func]
            decValue = int(offset, 0) & 0xfffffffe
            offset = hex(decValue)
            defLine = "#define %s_OFFSET_%s %s\n" % (string.upper(func), flag, offset)
            headFile.write(defLine)
        
        headFile.write("\n")
	#void sysLib$1$2HookHandler(CPUState*, int);
        for func in funcOffsetDic.keys():
            defLine = "void sysLib%s%sHookHandler(CPUState* env, int isBefore);\n" % (flag, func.title())
            headFile.write(defLine)
        
        #generate "int startOfLib*Calls(int curPC, int lib*StartAddr);"
        defLine = "\nint startOfLib%sCalls(int curPC, int lib%sStartAddr);\n" % (flag, flag)
        headFile.write(defLine)

        #generate "sysLibHookHandler hookLib*Calls(int curPC, CPUState* env);"
        defLine = "\nsysLibHookHandler hookLib%sCalls(int curPC, int lib%sStartAddr, CPUState* env);\n" % (flag, flag)
        headFile.write(defLine)

        #generate the lib_*_2.c file contain implementation of 
        #"startOfLib*Calls" and "hookLib*Calls"
        cFileName = "lib_" + string.lower(flag) + "2.c"
        with open(cFileName, 'w') as cFile:
            includeLine = "#include \"lib_" + string.lower(flag) + ".h\"\n"
            cFile.write(includeLine)

            #generate implementation of "startOfLib%sCalls
            impLineStart = "\nint startOfLib%sCalls(int curPC, int lib%sStartAddr){\n" \
                    "\tswitch(curPC - lib%sStartAddr){\n" \
                    % (flag, flag, flag)
            cFile.write(impLineStart)
            #generate switch body
            for func in funcOffsetDic.keys():
                caseLine = "\t\tcase %s_OFFSET_%s:\n" % (string.upper(func), flag)
                cFile.write(caseLine)
            #generate tail
            impLineTail = "\t\t\treturn (1);\n"\
                        "\t\tdefault:\n"\
                        "\t\t\treturn (0);\n"\
                        "\t}\n"\
                        "\treturn (0);\n}\n"
            cFile.write(impLineTail)

            #generate implementation of "sysLibHookHandler hookLib*Calls(int curPC, CPUState* env);"
            impLineStart = "\nsysLibHookHandler hookLib%sCalls(int curPC, int lib%sStartAddr, CPUState* env){\n"\
                    "\tswitch(curPC - lib%sStartAddr){\n" \
                    % (flag, flag, flag)
            cFile.write(impLineStart)
            #generate switch body
            for func in funcOffsetDic.keys():
                caseLine = "\t\tcase %s_OFFSET_%s:\n"\
                        "\t\t\tsysLib%s%sHookHandler(env, 1);\n"\
                        "\t\t\treturn sysLib%s%sHookHandler;\n"\
                        % (string.upper(func), flag, flag, func.title(), flag, func.title())
                cFile.write(caseLine)
            #generate tail
            impLineTail = "\t\tdefault:\n"\
                    "\t\t\tbreak;\n"\
                    "\t}\n"\
                    "\treturn (NULL);\n"\
                    "}\n"
            cFile.write(impLineTail)


        defLine = \
        """
#ifdef __cplusplus
}
#endif

#endif
        """
        headFile.write(defLine)

def main():
    if len(sys.argv) != 2:
        sys.exit(2)
    
    if sys.argv[1] not in IN_OUT_DIC:
        print "Wrong file name! Must be libc.dyn, libm.dyn"

    funcOffsetDic = {}
    
    with open(sys.argv[1], 'r') as dynF:
        for line in dynF:
            tokens = line.split()
            if len(tokens) == 6:
                if not tokens[5].startswith("_"):
                    if (tokens[5] not in funcOffsetDic) and (tokens[0] not in funcOffsetDic.values()):
                        funcOffsetDic[tokens[5]] = tokens[0]
    
    generateHeadFile(IN_OUT_DIC[sys.argv[1]], funcOffsetDic) 


if __name__ == '__main__':
    main()
