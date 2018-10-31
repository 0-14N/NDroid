NDroid
=========
NDroid is a dynamic taint analysis system on Android, which focus on tracing information flow through JNI with low performance overhead. More details about NDroid can be found in our published paper [here]( http://www4.comp.polyu.edu.hk/~csxluo/NDroid.pdf).

#### NDroid uses following open source projects:
* [TaintDroid](http://appanalysis.org)
* [DroidScope](https://code.google.com/p/decaf-platform/wiki/DroidScope)
* [darm](http://darm.re)

#### Please note that:
* The old NDroid prototype's code is kind of messy and not extensible. Therefore, I am rebuilding NDroid with goals: making it faster, more effective and extensible.
* Currently, this version is still under developing, so that it cannot be used to analyze apps. Once the core functions are completed, I will create a patch.
* The TaintDroid source code I use is [4.1.1_r6](http://appanalysis.org/download_4.1.html).

#### How to build?
* Build TaintDroid 4.1.1_r6 following the instruction [here](http://appanalysis.org/download_4.1.html).
* Clone NDroid source code: cd TaintDroid/external/ & git clone https://github.com/0-14N/NDroid.git ndroid
* Setup building environment: cd TaintDroid/ & . build/envsetup.sh & lunch full-eng
* Build NDroid: cd TaintDroid/external/ndroid & ./android-configure.sh & make
* Run NDroid: cd objs &  ./emulator -sysdir TaindDroid/out/target/product/generic/ -kernel TaintDroid/prebuilt/android-arm/kernel/kernel-qemu-armv7 -qemu -monitor stdio
* Try "ps", "pt", "pm pid" commands provided by DroidScope, make sure they all work.
* Start tracing process with command "nd_trace_pid pid" or "nd_trace_uid uid"; stop tracing by typing "nd_stop_trace_pid pid" or "nd_stop_trace_uid uid". 
* The log of NDroid "NDroid.log" is under directory "objs".

#### Issues:
* If commands provided by DroidScope ("ps", "pt") output nothing, try modifying files "objs/kernelinfo.conf" and "ndroid/DECAF_shared/DroidScope/DS_Common.h", making the offesets correclty.
* As reported by my friends, there are bugs for decoding Thumb-2 instructions and handling taint propagations of certain ARM instructions. (Not fixed yet.)

#### Others:
* There is little possibility that I will continue working on NDroid for following reasons:
  1. Android Lollipop totally abandoned DVM! (So do I ... )
  2. I have to admit that the performance overhead produced by NDroid makes it impractical for analyzing real apps with large amounts of native code.
  3. I don't have enough time since I am working on new research projects.
