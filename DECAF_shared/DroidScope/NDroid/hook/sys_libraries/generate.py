#!/usr/bin/python
#############################################
# author: Chenxiong (R0r5ch4ch) Qian
# date: 2014-10-4
#
# run: python generate.py [libc.dyn|libm.dyn|...]
#############################################
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

        for func in funcOffsetDic.keys():
            offset = "0x" + funcOffsetDic[func]
            defLine = "#define %s_OFFSET %s\n" % (string.upper(func), offset)
            headFile.write(defLine)


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
                    if tokens[5] not in funcOffsetDic:
                        funcOffsetDic[tokens[5]] = tokens[0]
    
    generateHeadFile(IN_OUT_DIC[sys.argv[1]], funcOffsetDic) 


if __name__ == '__main__':
    main()
