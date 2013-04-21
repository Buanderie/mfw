cmake_minimum_required(VERSION 2.8)
project (LIBMONADIC)

set( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${LIBMONADIC_SOURCE_DIR}/cmake")

# Look for Boost
find_package( Boost COMPONENTS thread REQUIRED )
if( Boost_FOUND)
    include_directories( ${Boost_INCLUDE_DIR} )
    ADD_DEFINITIONS( "-D__WITHBOOST__" )
endif()

# Set include directories
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

# Global shit
file ( GLOB_RECURSE CORE_CPP ./src/*.c* )
file ( GLOB_RECURSE NODES_CPP ./nodes/*/*.c* )
add_library( monadic ${FILES_CPP} ${NODES_CPP} )

# Link libraries
target_link_libraries( monadic ${Boost_LIBRARIES} )
