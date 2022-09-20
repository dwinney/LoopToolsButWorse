cmake_minimum_required (VERSION 3.0)

project (example LANGUAGES CXX Fortran)

set(CMAKE_CXX_FLAGS "-fPIC -O3") 
set(CMAKE_BUILD_TYPE "Release")

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

add_executable( test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp )
set_property(TARGET test PROPERTY LINKER_LANGUAGE Fortran)
target_link_libraries( test ${LOOPLIB} )
