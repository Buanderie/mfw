project(NODE_ADD)

include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
target_link_libraries( monadic )

add_library( node_add SHARED add.cpp )
