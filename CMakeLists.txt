cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)

project(FordAlorithm)

add_executable(FordAlgorithm main.cpp FileToGraphParser.cpp FileToGraphParser.h Graph.h Graph.cpp FordAlgo.h FordAlgo.cpp)
add_executable(Generator GraphGenerator.cpp GraphGenerator.h generator.cpp Graph.h Graph.cpp)
add_executable(PerfChecker PerfChecker.cpp GraphGenerator.h GraphGenerator.cpp FordAlgo.cpp FordAlgo.h Graph.cpp Graph.h)


install(TARGETS FordAlgorithm Generator PerfChecker)


