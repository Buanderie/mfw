project(NODE_VIDEOINPUT)

include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
target_link_libraries( monadic )
add_library( node_foo SHARED foonode.cpp )
