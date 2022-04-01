add_library(jsonStruct JSONBody.cpp)

target_sources(jsonStruct
        PRIVATE
        JSONBody.cpp
        JSONString.cpp
        JSONObject.cpp
        JSONNumber.cpp
        JSONNull.cpp
        JSONBool.cpp
        JSONArray.cpp
        PUBLIC
        JSONString.h
        JSONObject.h JSONNumber.h JSONNull.h JSONBool.h JSONArray.h
        )

target_include_directories(jsonStruct PUBLIC ${CMAKE_CURRENT_LIST_DIR})
