add_library(parser JSONString.cpp)

target_sources(
        parser
        PRIVATE
        JSONArray.cpp JSONBody.cpp JSONBool.cpp JSONNull.cpp JSONNumber.cpp JSONObject.cpp JSONParser.cpp JSONString.cpp

        PUBLIC
        JSONArray.h
        JSONBody.h
        JSONBool.h
        JSONNull.h
        JSONNumber.h
        JSONObject.h
        JSONParser.h
        JSONString.h
)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_LIST_DIR})

