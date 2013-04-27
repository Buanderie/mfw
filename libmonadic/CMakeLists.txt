cmake_minimum_required(VERSION 2.8)
project (LIBMONADIC)

# Set custom cmake scripts directory
set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${LIBMONADIC_SOURCE_DIR}/cmake")
# Set CMake options
set( USE_CUDA TRUE CACHE BOOL "Use nVidia CUDA  as GPGPU API")
option(USE_CLANG "build application with clang" OFF) # OFF is the default

# Configure CLANG

# Look for CUDA
IF( USE_CUDA )
find_package( CUDA )
IF( CUDA_FOUND )
    SET( CUDA_NVCC_FLAGS "-arch;sm_20" )
    ADD_DEFINITIONS( -DWITH_CUDA )
ENDIF()
ENDIF()

# Look for Boost
find_package( Boost COMPONENTS thread REQUIRED )
if( Boost_FOUND)
    include_directories( ${Boost_INCLUDE_DIR} )
    ADD_DEFINITIONS( "-D__WITHBOOST__" )
endif()

# Set include directories
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
IF( USE_CUDA AND CUDA_FOUND )
    include_directories( ${CUDA_INCLUDE_DIRS} )
ENDIF()

# Global shit
IF( USE_CUDA AND CUDA_FOUND )
    file ( GLOB_RECURSE CORE_CPP ./src/*.c* )
    file ( GLOB_RECURSE NODES_CPP ./nodes/*/*.c* )
    cuda_add_library( monadic SHARED ${CORE_CPP} ${NODES_CPP} )
ELSE()
    file ( GLOB_RECURSE CORE_CPP ./src/*.cpp )
    file ( GLOB_RECURSE NODES_CPP ./nodes/*/*.cpp )
    add_library( monadic SHARED ${CORE_CPP} ${NODES_CPP} )
ENDIF()


# Link libraries
target_link_libraries( monadic ${Boost_LIBRARIES} )
