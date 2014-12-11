cmake_minimum_required(VERSION 2.8)

project(MonadicFramework)

option(BUILD_TESTS "Build Unit tests" ON)

# Handle platform specifics
if ( "${CMAKE_SYSTEM_NAME}" MATCHES "Windows" )
	SET( MONADIC_CURRENT_SYSTEM "WINDOWS" )
    ADD_DEFINITIONS( -D__WINDOWS__ )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
	SET( MONADIC_CURRENT_SYSTEM "LINUX" )
    ADD_DEFINITIONS( -D__LINUX__ )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" )
	SET( MONADIC_CURRENT_SYSTEM "MACOSX" )
    ADD_DEFINITIONS( -D__MACOSX__ )
endif()

add_subdirectory(libmonadic)
add_subdirectory(kernels)
add_subdirectory(mfwedit)

if( BUILD_TESTS )
    add_subdirectory(googletest)
    add_subdirectory( test )
endif( BUILD_TESTS )
