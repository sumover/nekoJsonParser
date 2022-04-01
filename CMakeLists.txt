cmake_minimum_required(VERSION 3.23)
project(jsonParser)

set(CMAKE_CXX_STANDARD 17)

file(COPY testData DESTINATION test/)

add_subdirectory(parser)
add_subdirectory(jsonStruct)

enable_testing()
add_subdirectory(test)

add_executable(jsonParser main.cpp)
