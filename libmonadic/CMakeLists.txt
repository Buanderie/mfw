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

# Handle platform specifics
if ( "${CMAKE_SYSTEM_NAME}" MATCHES "Windows" )
    ADD_DEFINITIONS( -D__WINDOWS__ )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
    ADD_DEFINITIONS( -D__LINUX__ )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" )
    ADD_DEFINITIONS( -D__MACOSX__ )
endif()

# Look for CUDA
IF( USE_CUDA )
find_package( CUDA )
IF( CUDA_FOUND )
    SET( CUDA_NVCC_FLAGS "-arch;sm_20" )
    ADD_DEFINITIONS( -D__WITH_CUDA__ )
ENDIF()
ENDIF()

# Look for Boost
find_package( Boost COMPONENTS system filesystem REQUIRED )
if( Boost_FOUND)
    include_directories( ${Boost_INCLUDE_DIR} )
    ADD_DEFINITIONS( "-D__WITHBOOST__" )
    message( ${Boost_INCLUDE_DIR} )
endif()

# Set include directories
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
include_directories( ${LIBMONADIC_SOURCE_DIR}/objects )

IF( USE_CUDA AND CUDA_FOUND )
    include_directories( ${CUDA_INCLUDE_DIRS} )
ENDIF()

# Global shit
IF( USE_CUDA AND CUDA_FOUND )
    file ( GLOB_RECURSE CORE_CPP ./src/*.c* )
    file ( GLOB_RECURSE CORE_OBJECTS_CPP ./objects/*/*.c* )
    set( ALL_CPP ${CORE_CPP} ${CORE_OBJECTS_CPP} )
    cuda_add_library( monadic SHARED ${ALL_CPP} )
ELSE()
    file ( GLOB_RECURSE CORE_CPP ./src/*.cpp )
    file ( GLOB_RECURSE CORE_OBJECTS_CPP ./objects/*/*.cpp )
    set( ALL_CPP ${CORE_CPP} ${CORE_OBJECTS_CPP} )
    add_library( monadic SHARED ${ALL_CPP} )
ENDIF()


# Link libraries
target_link_libraries( monadic ${Boost_LIBRARIES} dl )
