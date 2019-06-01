cmake_minimum_required(VERSION 3.13)
project(os234123_ex3)

set(CMAKE_CXX_STANDARD 11)

include_directories(part1)

add_executable(os234123_ex3
        part1/Headers.hpp
        part1/PCQueue.cpp
        part1/PCQueue.hpp
        part1/Semaphore.hpp part1/Semaphore.cpp
        tests/queue_test.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
target_link_libraries(os234123_ex3 pthread)

