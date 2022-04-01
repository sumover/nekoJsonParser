add_library(parser JSONParser.cpp)

target_sources(
        parser
        PRIVATE
        JSONParser.cpp
        PUBLIC
        JSONParser.h
)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_LIST_DIR})

