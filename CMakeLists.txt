cmake_minimum_required(VERSION 3.10)
project(CountingPrimes)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    /opt/homebrew/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/algos
)

link_directories(/opt/homebrew/lib)

find_package(yaml-cpp REQUIRED)

add_executable(primes 
    src/main.cpp
    src/run_with_time_limit.cpp
    src/algos/brute_force.cpp
    src/algos/optimized_brute_force.cpp
)

target_link_libraries(primes yaml-cpp)