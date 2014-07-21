#!/usr/bin/python
#author: Chenxiong Qian
#date: 2014-7-21

#pull memory maps of system apps and extract
#system libraries/memory modules.

import subprocess

pids = []
modules = []

if __name__ == '__main__':
    p = subprocess.Popen("adb shell ls /proc/", shell=True, stdout=subprocess.PIPE)
    out = p.communicate()[0].split('\n')
    for line in out:
        line = line.strip()
        try:
            pid = int(line)
            pids.append(pid)
        except ValueError:
            continue

    for pid in pids:
        p = subprocess.Popen("adb shell cat /proc/" + str(pid) + "/maps", shell=True, stdout=subprocess.PIPE)
        out = p.communicate()[0].split('\n')
        for line in out:
            tokens = line.strip().split()
            if len(tokens) >= 6:
                if tokens[5] not in modules:
                    modules.append(tokens[5])
    
    for module in modules:
        print "StringHashtable_add(pTable, \"" + module + "\");"
