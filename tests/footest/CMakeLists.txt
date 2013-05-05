

include_directories( ${LIBMONADIC_SOURCE_DIR}/include )
include_directories( ${LIBMONADIC_SOURCE_DIR}/corenodes )

add_executable( footest main.cpp )
target_link_libraries( footest monadic )
