cmake_minimum_required (VERSION 2.6)
project (FsLibc)

option(ENABLE_TESTS "Enable Testings" OFF)

set (FsLibc_VERSION_MAJOR 0)
set (FsLibc_VERSION_MINOR 8)


set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wextra")
set(CMAKE_C_FLAGS_RELCHECK "${CMAKE_C_FLAGS_RELEASE} -DALT_FSLC_NAMES")

add_subdirectory(libc)

if(ENABLE_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()
