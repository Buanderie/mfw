project(NODE_NUMBER)

include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
target_link_libraries( monadic )

add_library( node_number SHARED number.cpp )
