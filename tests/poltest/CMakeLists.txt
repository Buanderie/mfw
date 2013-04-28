

include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

add_executable( poltest main.cpp )
target_link_libraries( poltest monadic )
