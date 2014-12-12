project(NODE_SOBEL)

# Find OpenCV
find_package(OpenCV 2)
if( OpenCV_FOUND )
        include_directories (${OpenCV_INCLUDE_DIRS})
        set( DEPS "${DEPS};${OpenCV_LIBS}" )
endif()

include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
set( DEPS "${DEPS};monadic" )

message( "${DEPS}" )

add_library( node_sobel SHARED sobel.cpp )
target_link_libraries( node_sobel ${DEPS} )
