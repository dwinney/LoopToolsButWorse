## LoopToolsButWorse

The [LoopTools](https://feynarts.de/looptools/) package provides highly-optimized implementations of one-loop scalar and tensor integrals. Although written primarily in Fortran, an interface with C and C++ is provided through provided compilation scripts. Thesse scripts and makefiles involved tend to be highly opaque making linking a precompiled LoopTools libarary with an existing C++ projects a higly nontrivial task.

This repository is a modified version of LoopTools-2.16 aimed at allowing LoopTools functions to be incorporated with other CMake projects as well as usable with ROOT's [cling](https://root.cern/cling/) interpreter. Necessary modifications to the makefiles mean some of the more advanced functionalities (e.g. MathLink) are not guarenteed to work as intended (hence *ButWorse*). 

### Installation
Default LoopTools installation produces a *static* Fortran (.a) library. This poses a problem when using the cling interpreter which currently can only load dynamic libraries. 

Installation for LoopToolsButWorse follows exactly as vanilla LoopTools:
```bash
./configure
make
make install
```
This will produce the following installation structure in the top level directory:
```
lib/
    libLoopTools.so
include/
    clooptools.h
    looptools.h
bin/
    f++
    fcc
    lt
```
Note the installed library has been renamed and now produces a .so file (compilation so far only tested on Ubuntu). Architecture-related suffices have been omitted to make above structure uniform across platforms. After building this way, the LoopTools can be linked using CMake, e.g. through:
```
find_library( LOOPLIB NAMES LoopTools libLoopTools 
                      HINTS "$ENV{LOOPTOOLS}/lib")

enable_language(Fortran)
add_executable( myProject ${CMAKE_CURRENT_SOURCE_DIR}/myProject.cpp )
set_property(TARGET myProject PROPERTY LINKER_LANGUAGE Fortran)
target_link_libraries( test ${LOOPLIB} )
```
with `LOOPTOOL` an environment variable set to the top level directory.
An example CMakefile is provided.

### Usage
In principle all the functionality of LoopTools is accessable in the normal way using the built-in C/C++ syntax. Minor changes have been made to the `inini()` and `ltexi()` to suppress command-line messages when calculation produces no errors.
