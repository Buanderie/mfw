project(NODE_NUMBER)

LINK_DIRECTORIES( ${LIBMONADIC_BINARY_DIR} )
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

add_library( node_number SHARED number.cpp )
add_dependencies( node_number monadic )
target_link_libraries( node_number monadic )