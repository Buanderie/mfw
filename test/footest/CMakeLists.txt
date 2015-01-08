
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

add_executable( aaa main.cpp )
target_link_libraries( aaa monadic )
