project(NODE_BAR)

LINK_DIRECTORIES( ${LIBMONADIC_BINARY_DIR} )
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

add_library( node_bar SHARED foonode.cpp )
ADD_DEPENDENCIES( node_bar monadic )
target_link_libraries( node_bar monadic )