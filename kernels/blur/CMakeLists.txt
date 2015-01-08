project(NODE_BLUR)

# Find OpenCV
find_package(OpenCV 2)
if( OpenCV_FOUND )
        include_directories (${OpenCV_INCLUDE_DIRS})
        set( DEPS "${DEPS};${OpenCV_LIBS}" )
endif()

LINK_DIRECTORIES( ${LIBMONADIC_BINARY_DIR} )
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
set( DEPS "${DEPS};monadic" )

add_library( node_blur SHARED blur.cpp )
ADD_DEPENDENCIES( node_blur monadic )
target_link_libraries( node_blur ${DEPS} )
