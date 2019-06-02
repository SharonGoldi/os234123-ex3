cmake_minimum_required(VERSION 3.13)
project(os234123_ex3)

set(CMAKE_CXX_STANDARD 11)

include_directories(part1)

add_executable(os234123_ex3
        part1/PCQueue.cpp
        part1/Semaphore.cpp
        part2/Game.cpp
        part2/utils.cpp
        part2/Thread.hpp
        part2/main.cpp
        part2/ConsumerThread.cpp
        part2/Task.cpp
        part2/Thread.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
target_link_libraries(os234123_ex3 pthread)

