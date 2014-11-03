

include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

add_executable( filesystem_test  main.cpp )
target_link_libraries( filesystem_test monadic )
