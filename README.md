# multi_index_cache
multi platform cross language multi index cache ( a.k.a MPCLMI CACHE )

Motivation :
In my previouse work experiance a set of application written in C++ and Java needed 
to share data .
I decided to write a generator program for those who develope in both languages and require non distributed 
version of shared data faster then filesystem.
In stead of standard IDL Java annotations and java reflexion has been chosen as 
a main driver for this code generator.


Structure ( work in progress ) :
* [src/](../../tree/dev/src/) -- the root directory
   * [com/](../../src/com/)
      * [mpclmi/](../../src/com/mpclmi/)
        * [generator/](../../src/com/mpclmi/generator/) 
            * [Generator.java](../../src/com/mpclmi/generator/Generator.java) 
            * [cpp/](../../src/com/mpclmi/generator/cpp/) -- C++ code generator
            * [java/](../../src/com/mpclmi/generator/java) -- Java code generator
        * [test/](../../tree/com/mpclmi/test/)
* [system/](../../src/system/) -- C++ shared memory and multi index container 
* [config.mk](../../config.mk)
* [prog.mk](../../src/prog.mk)
* [Makefile](../../src/Makefile)


The Make or other build system will generate cpp and java code based on input from IDL .
The IDL in the form of annotated Java classes is used as an input to Generator.java , under generator/ directory 
reside classes ( design in progress with some thoughts on visitor , delegate , etc ) , 
whose role is to process IDL ( annotated Java classes ) and produce intermediate result . 
This intermediate result can be fed into CodePrinter which produces Java, C++ or both.

Phase-I 
generate C++ code only

Phase-II 
Generate Java code using JNI interface to C++ system library interfacing via provided by MPCLMI classes in 
system/ directory

Phase-III
To research and implement pure Java solution for Java developers without a need to compile code with C++ compiler.


