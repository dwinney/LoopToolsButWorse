## LoopToolsButWorse

The [LoopTools](https://feynarts.de/looptools/) package provides highly-optimized implementations of one-loop scalar and tensor integrals. Although written in Fortran, an interface with C/C++ and scripts to compile simple CXX projects is provided. These scripts are rather opaque and make incorporating LoopTools into an existing C++ library nontrivial.

This repository is a modified version of LoopTools-2.16 aimed at allowing LoopTools functions to be incorporated with other CMake projects as well as usable with ROOT's [cling](https://root.cern/cling/) interpreter. Necessary modifications to the makefiles mean some of the more advanced functionalities (e.g. MathLink) are not guarenteed to work as intended (hence *ButWorse*). 

With the exception of a minor change described below, all the source code is unchanged with only changes to installation, all credit goes to the original authors.

### Installation
Default LoopTools installation produces a *static* Fortran (.a) library. This poses a problem when using the cling interpreter which currently can only load dynamic libraries. 

Installation follows exactly as vanilla LoopTools:
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
Note the installed library has been renamed and now produces an explicitly .so file (so far only tested on Ubuntu-20.04.5 with g++/gFortran-9.4.0). Architecture-dependend suffixes in filenames have been omitted to make above install structure uniform across platforms. 

After building this way, the LoopTools can be linked using CMake, e.g. through:
```
find_library( LOOPLIB NAMES LoopTools libLoopTools HINTS "$ENV{LOOPTOOLS}/lib")

enable_language(Fortran)

add_executable( myProject ${CMAKE_CURRENT_SOURCE_DIR}/myProject.cpp )

set_property(TARGET myProject PROPERTY LINKER_LANGUAGE Fortran)
target_link_libraries( myProject ${LOOPLIB} )
```
with `LOOPTOOL` an environment variable set to the top level directory.
An example CMakefile is provided.

### Usage
All the functionality of LoopTools is accessable in the normal way using the built-in C/C++ syntax. 
Minor changes have been made to the `itini()` and `ltexi()` to suppress command-line messages when calculation produces no errors. This is to prevent superfluous things being printed to command-line when multiple instances of LoopTools functions (i.e. `itini()` calls) are used repeatedly inside another code.
