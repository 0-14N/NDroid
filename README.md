NDroid
=========
NDroid is a dynamic taint analysis system on Android, which focus on tracing information flow through JNI with low performance overhead. More details about NDroid can be found in our publicated paper [here]( http://www4.comp.polyu.edu.hk/~csxluo/NDroid.pdf).

####NDroid uses following open source projects:
* [TaintDroid](http://appanalysis.org)
* [DroidScope](https://code.google.com/p/decaf-platform/wiki/DroidScope)
* [darm](http://darm.re)

####Please note that:
* The old NDroid prototype's code is kind of messy and not extensible. Therefore, I am rebuilding NDroid with goals: making it faster, more effective and extensible.
* Currently, this version is still under developing, so that it cannot be used to analyze apps. Once the core functions are completed, I will create a patch.
* The TaintDroid source code I use is [4.1.1_r6](http://appanalysis.org/download_4.1.html).
