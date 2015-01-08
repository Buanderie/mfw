project(NODE_VIDEODISPLAY)

# Find OpenCV
find_package(OpenCV 2)
if( OpenCV_FOUND )
        include_directories (${OpenCV_INCLUDE_DIRS})
        set( DEPS "${DEPS};${OpenCV_LIBS}" )
endif()

#Find SDL
find_package(SDL)
if( SDL_FOUND )
        include_directories (${SDL_INCLUDE_DIR})
        set( DEPS "${DEPS};${SDL_LIBRARY}" )
endif()

LINK_DIRECTORIES( ${LIBMONADIC_BINARY_DIR} )
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
set( DEPS "${DEPS};monadic" )

add_library( node_videodisplay SHARED videodisplay.cpp )
target_link_libraries( node_videodisplay ${DEPS} )
add_dependencies( node_videodisplay monadic )