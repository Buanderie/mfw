cmake_minimum_required(VERSION 2.8)

#
project(MonadicFramework_Test)

#-------------------
# Test
#-------------------
add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
link_directories(${gtest_BINARY_DIR}/src)

file(GLOB TEST_SRC_FILES ${MonadicFramework_SOURCE_DIR}/test/*.cpp)
add_executable(mfw_test ${TEST_SRC_FILES})
add_dependencies(mfw_test googletest)

if(NOT WIN32)
        target_link_libraries(  mfw_test
                                gtest
                                gtest_main
                                pthread
        )
else()
        target_link_libraries(mfw_test
               debug ${gtest_BINARY_DIR}/src/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
               optimized ${gtest_BINARY_DIR}/src/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
        target_link_libraries(mfw_test
               debug ${gtest_BINARY_DIR}/src/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
               optimized ${gtest_BINARY_DIR}/src/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
endif()

#-------------------
# Miscellaneous Test Projects
#-------------------
add_subdirectory( footest )
add_subdirectory( poltest )
add_subdirectory( filesystem_test )
add_subdirectory( objects_test )

