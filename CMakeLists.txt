cmake_minimum_required (VERSION 3.0)

project (example)

set(CMAKE_CXX_FLAGS "-fPIC -O3") 
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_Fortran_COMPILER  gfortran)
set(CMAKE_CC_COMPILER  gcc)
set(CMAKE_CXX_COMPILER  g++)

enable_language(Fortran)

# Set output lib and bin locations
set(CMAKE_INSTALL_BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_BINDIR})

find_library( LOOPLIB NAMES LoopTools libLoopTools 
                       HINTS "$ENV{LOOPTOOLS}/lib")
if (LOOPLIB)
    include_directories("$ENV{LOOPTOOLS}/include")
    message("-- LoopTools found! (${LOOPLIB})")
else()
    message("-- LoopTools not found! AAAAAAAAAAAAAAAAAAAA")
    message("-- I looked in $ENV{LOOPTOOLS}/lib")
endif()

# Need to append the flags associated with gFortran
SET(FORTRAN_FLAGS " -O3 -g -fomit-frame-pointer -ffast-math -fPIC -Wall -m64 -lLoopTools -L/lib/../lib -lgfortran -lm -lgcc_s -lgcc -lquadmath -lm -lgcc_s -lgcc -lgcc_s -lgcc -lpthread -lrt")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${FORTRAN_FLAGS}")

add_executable( test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp )
set_property(TARGET test PROPERTY LINKER_LANGUAGE Fortran)
target_link_libraries( test ${LOOPLIB} )