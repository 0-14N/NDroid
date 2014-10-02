#! /usr/bin/python
######################################################
# python generate.py JNIAPIS_ADDRS.log libdvmStartAddr
#   -- libdvmStartAddr is the address of "libdvm.so".
#      e.g. 0x406f2000
######################################################
import sys

def generate_head_file(filename, dvmStartAddr):
    with open(filename, 'r') as log, open("JNI_APIS_OFFSETS.h", 'w') as headFile:
        defLine = "#define DVM_START_ADDR %s\n\n" % hex(dvmStartAddr)
        headFile.write(defLine)
        for line in log:
            tokens = line.split(":")
            funcAddr = int(tokens[2].strip(), 0)
            defLine = "#define %s %s\n" % (tokens[1].strip(), 
                    hex((funcAddr - dvmStartAddr) & 0xfffffffe))
            headFile.write(defLine)


def main():
    if len(sys.argv) != 3:
        sys.exit(2)

    try:
        dvmStartAddr = int(sys.argv[2], 0)
        generate_head_file(sys.argv[1], dvmStartAddr)
    except:
        print "Wrong libdvmStartAddr"

if __name__ == "__main__":
    main()
