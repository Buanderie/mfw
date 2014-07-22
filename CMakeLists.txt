cmake_minimum_required(VERSION 2.8)

project (MonadicFramework)

# Handle platform specifics
if ( "${CMAKE_SYSTEM_NAME}" MATCHES "Windows" )
    ADD_DEFINITIONS( -D__WINDOWS__ )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
	  message( "POLBAK" )
    ADD_DEFINITIONS( -D__LINUX__ )
elseif( "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" )
    ADD_DEFINITIONS( -D__MACOSX__ )
endif()

add_subdirectory(libmonadic)
add_subdirectory(nodes)
add_subdirectory(tests)
