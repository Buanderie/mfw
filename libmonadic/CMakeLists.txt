cmake_minimum_required(VERSION 2.8)
project (LIBMONADIC)

# Set custom cmake scripts directory
set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${LIBMONADIC_SOURCE_DIR}/cmake")
# Set CMake options
set( USE_CUDA FALSE CACHE BOOL "Use nVidia CUDA as GPGPU API")
option(USE_CLANG "build application with clang" OFF) # OFF is the default

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

# Look for MessagePack
find_package( MessagePack )
include_directories( ${MessagePack_INCLUDE_DIR} )
set( DEPS "${DEPS};${MessagePack_LIBRARIES}" )

# Find Boost
FIND_PACKAGE(Boost COMPONENTS filesystem system)
IF (Boost_FOUND)
    set( BOOST_FILESYSTEM_VERSION 2 )
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
    ADD_DEFINITIONS( "-D__BOOST__" )
    set( DEPS "${DEPS};${Boost_LIBRARIES}" )
ENDIF()
#

# Add Dynamic Library Loader dependency (if UNIX-based)
if( ${MONADIC_CURRENT_SYSTEM} STREQUAL "LINUX" )
	set( DEPS "${DEPS};dl" )
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
    #file ( GLOB_RECURSE CORE_OBJECTS_CPP ./objects/*/*.cpp )
    set( ALL_CPP ${CORE_CPP} ${CORE_OBJECTS_CPP} )
    if( ${MONADIC_CURRENT_SYSTEM} STREQUAL "WINDOWS" )
      add_library( monadic ${ALL_CPP} )
    else()
      add_library( monadic SHARED ${ALL_CPP} )
    endif()
ENDIF()


# Link libraries
target_link_libraries( monadic ${DEPS} )
