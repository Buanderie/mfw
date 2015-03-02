cmake_minimum_required(VERSION 2.8)
project (LIBMONADIC)

# Set custom cmake scripts directory
set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${LIBMONADIC_SOURCE_DIR}/cmake")

# Set CMake options
set( USE_CUDA FALSE CACHE BOOL "Use nVidia CUDA as GPGPU API")
option(USE_CLANG "build application with clang" OFF) # OFF is the default

option( USE_ZMQ "Use 0MQ for message passing" OFF)

# Configure CLANG
if( USE_CLANG )
    SET (CMAKE_C_COMPILER             "/usr/bin/clang")
    SET (CMAKE_C_FLAGS                "-Wall -std=c99")
    SET (CMAKE_C_FLAGS_DEBUG          "-g")
    SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

    SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
    SET (CMAKE_CXX_FLAGS                "-Wall")
    SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
    SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    SET (CMAKE_AR      "/usr/bin/llvm-ar")
    SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
    SET (CMAKE_NM      "/usr/bin/llvm-nm")
    SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
    SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
endif( USE_CLANG )

# Look for CUDA
IF( USE_CUDA )
find_package( CUDA )
IF( CUDA_FOUND )
    SET( CUDA_NVCC_FLAGS "-arch;sm_20" )
    ADD_DEFINITIONS( -D__WITH_CUDA__ )
ENDIF()
ENDIF()

# Look for 0MQ
IF( USE_ZMQ )
find_package(ZeroMQ REQUIRED)
if(ZEROMQ_FOUND)
set( DEPS "${DEPS};${ZeroMQ_LIBRARIES}" )
include_directories( ${ZeroMQ_INCLUDE_DIR} )
ADD_DEFINITIONS( -D__USE_ZMQ__ )
else()
message("Can't find ZeroMQ")
endif()
ENDIF( USE_ZMQ )


# Add Dynamic Library Loader dependency, pthread, uuid (if UNIX-based)
if( ${MONADIC_CURRENT_SYSTEM} STREQUAL "LINUX" )
	set( DEPS "${DEPS};dl" )
        set( DEPS "${DEPS};pthread" )
        set( DEPS "${DEPS};uuid" )
endif()

# Look for OpenMP
find_package(OpenMP)
if( OpenMP_FOUND )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Set include directories
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
include_directories( ${LIBMONADIC_SOURCE_DIR}/objects )

IF( USE_CUDA AND CUDA_FOUND )
    include_directories( ${CUDA_INCLUDE_DIRS} )
ENDIF()

# Global source fetching
IF( USE_CUDA AND CUDA_FOUND )
    file ( GLOB_RECURSE CORE_CPP ./src/*.c* )
    file ( GLOB_RECURSE CORE_OBJECTS_CPP ./objects/*/*.c* )
    set( ALL_CPP ${CORE_CPP} ${CORE_OBJECTS_CPP} )
    cuda_add_library( monadic SHARED ${ALL_CPP} )
ELSE()
    file ( GLOB_RECURSE CORE_CPP ./src/*.cpp )
    file ( GLOB_RECURSE CORE_OBJECTS_CPP ./objects/*/*.cpp )
    set( ALL_CPP ${CORE_CPP} ${CORE_OBJECTS_CPP} )
    message( ${ALL_CPP} )
    if( ${MONADIC_CURRENT_SYSTEM} STREQUAL "WINDOWS" )
      add_library( monadic ${ALL_CPP} )
    else()
      add_library( monadic SHARED ${ALL_CPP} )
    endif()
ENDIF()


# Link libraries
target_link_libraries( monadic ${DEPS} )
