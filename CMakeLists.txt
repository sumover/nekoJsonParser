cmake_minimum_required(VERSION 3.23)
project(jsonParser)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(parser)

enable_testing()
add_subdirectory(test)

add_executable(jsonParser main.cpp)