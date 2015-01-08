project(NODE_VIDEOINPUT)

LINK_DIRECTORIES( ${LIBMONADIC_BINARY_DIR} )
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
target_link_libraries( monadic )

add_library( node_foo SHARED foonode.cpp )
add_dependencies( node_foo monadic )
target_link_libraries( node_foo monadic )