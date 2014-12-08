cmake_minimum_required(VERSION 2.8)

include_directories(${LIBMONADIC_SOURCE_SIR}/include)

#
project(MonadicFramework_Test)
include_directories(${LIBMONADIC_SOURCE_SIR}/include)

message("pol: ${LIBMONADIC_SOURCE_DIR}/include")


#-------------------
# Test
#-------------------
#add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()
include_directories(${LIBMONADIC_SOURCE_SIR}/include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${LIBMONADIC_SOURCE_SIR}/include)
link_directories(${gtest_BINARY_DIR}/src)
include_directories(${LIBMONADIC_SOURCE_SIR}/include)
file(GLOB TEST_SRC_FILES ${MonadicFramework_SOURCE_DIR}/test/*.cpp)
add_executable(mfw_test ${TEST_SRC_FILES})
add_dependencies(mfw_test googletest monadic)
include_directories(${LIBMONADIC_SOURCE_SIR}/include)
if(NOT WIN32)
        include_directories(${LIBMONADIC_SOURCE_SIR}/include)
        target_link_libraries(  mfw_test
                                monadic
                                gtest
                                gtest_main
                                pthread
        )
        include_directories(${LIBMONADIC_SOURCE_SIR}/include)
else()
        include_directories(${LIBMONADIC_SOURCE_SIR}/include)
        target_link_libraries(mfw_test
               debug ${gtest_BINARY_DIR}/src/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
               optimized ${gtest_BINARY_DIR}/src/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
        target_link_libraries(mfw_test
               debug ${gtest_BINARY_DIR}/src/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
               optimized ${gtest_BINARY_DIR}/src/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
endif()

include_directories(${LIBMONADIC_SOURCE_SIR}/include)

#-------------------
# Miscellaneous Test Projects
#-------------------
add_subdirectory( footest )
add_subdirectory( poltest )
add_subdirectory( filesystem_test )
add_subdirectory( objects_test )
