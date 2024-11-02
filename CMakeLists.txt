cmake_minimum_required(VERSION 3.12)
project(Practice_formal_)

set(CMAKE_CXX_STANDARD 20)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0028 NEW)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

include_directories(/usr/include /usr/include/gtest solution_src)
link_directories(/usr/lib)

add_subdirectory(solution_src)

add_executable(CTests main_test.cpp gtests/tests.cpp)
target_link_libraries(CTests pthread gtest gtest_main SolutionLib)
add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(CTests -fprofile-arcs)

add_executable(Main main.cpp)
target_link_libraries(Main SolutionLib)

set(CMAKE_EXE_LINKER_FLAGS --coverage)
