cmake_minimum_required(VERSION 2.8)
project (LIBMONADIC)

# Set custom cmake scripts directory
set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${LIBMONADIC_SOURCE_DIR}/cmake")
# Set CMake options
set( USE_CUDA TRUE CACHE BOOL "Use nVidia CUDA as GPGPU API")
option(USE_CLANG "build application with clang" OFF) # OFF is the default

# Configure CLANG

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
include_directories( ${LIBMONADIC_SOURCE_DIR}/corenodes )
include_directories( ${LIBMONADIC_SOURCE_DIR}/coreobjects )
IF( USE_CUDA AND CUDA_FOUND )
    include_directories( ${CUDA_INCLUDE_DIRS} )
ENDIF()

# Global shit
IF( USE_CUDA AND CUDA_FOUND )
    file ( GLOB_RECURSE CORE_CPP ./src/*.c* )
    file ( GLOB_RECURSE CORE_NODES_CPP ./corenodes/*/*.c* )
    file ( GLOB_RECURSE CORE_OBJECTS_CPP ./coreobjects/*/*.c* )
    set( ALL_CPP ${CORE_CPP} ${CORE_NODES_CPP} ${CORE_OBJECTS_CPP} )
    cuda_add_library( monadic SHARED ${ALL_CPP} )
ELSE()
    file ( GLOB_RECURSE CORE_CPP ./src/*.cpp )
    file ( GLOB_RECURSE CORE_NODES_CPP ./corenodes/*/*.cpp )
    file ( GLOB_RECURSE CORE_OBJECTS_CPP ./coreobjects/*/*.cpp )
    set( ALL_CPP ${CORE_CPP} ${CORE_NODES_CPP} ${CORE_OBJECTS_CPP} )
    add_library( monadic SHARED ${ALL_CPP} )
ENDIF()


# Link libraries
target_link_libraries( monadic ${Boost_LIBRARIES} )
