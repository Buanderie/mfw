
include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

add_executable( footest main.cpp )
target_link_libraries( footest monadic )
