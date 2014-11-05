include_directories( ${LIBMONADIC_SOURCE_DIR}/include )

add_executable( objects_test  main.cpp )
target_link_libraries( objects_test monadic )
