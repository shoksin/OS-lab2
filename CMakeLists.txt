cmake_minimum_required(VERSION 3.14)
project(ThreadsLab)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(threads_lib threads.cpp threads.h)
target_include_directories(threads_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(threads_app main.cpp)
target_link_libraries(threads_app PRIVATE threads_lib)

add_executable(threads_test thread_tests.cpp)
target_link_libraries(threads_test PRIVATE threads_lib gtest gtest_main)

add_test(NAME threads_test COMMAND threads_test)