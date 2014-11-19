
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

# Find Boost
FIND_PACKAGE(Boost COMPONENTS thread filesystem system regex timer)
IF (Boost_FOUND)
    set( BOOST_FILESYSTEM_VERSION 2 )
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
    ADD_DEFINITIONS( "-D__BOOST__" )
    set( DEPS "${DEPS};${Boost_LIBRARIES};monadic" )
ENDIF()
#

add_executable( poltest main.cpp )
target_link_libraries( poltest ${DEPS} )
