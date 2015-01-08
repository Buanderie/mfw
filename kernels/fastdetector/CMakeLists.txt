project(NODE_FASTDETECTOR)

# Find OpenCV
find_package(OpenCV 2)
if( OpenCV_FOUND )
        include_directories (${OpenCV_INCLUDE_DIRS})
        set( DEPS "${DEPS};${OpenCV_LIBS}" )
endif()

LINK_DIRECTORIES( ${LIBMONADIC_BINARY_DIR} )
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
set( DEPS "${DEPS};monadic" )

message( "${DEPS}" )

add_library( node_fastdetector SHARED fastdetector.cpp )
ADD_DEPENDENCIES( node_fastdetector monadic )
target_link_libraries( node_fastdetector ${DEPS} )
