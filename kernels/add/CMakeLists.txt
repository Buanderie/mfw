project(NODE_ADD)

LINK_DIRECTORIES( ${LIBMONADIC_BINARY_DIR} )
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

add_library( node_add SHARED add.cpp )
ADD_DEPENDENCIES( node_add monadic )
target_link_libraries( node_add monadic )