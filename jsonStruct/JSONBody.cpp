//
// Created by sumover on 2022/3/30.
//


#include "JSONBody.h"
#include "JSONObject.h"
#include "JSONArray.h"
#include "JSONString.h"
#include "JSONBool.h"
#include "JSONNull.h"
#include "JSONNumber.h"
#include "../parser/JSONParser.h"

#include <memory>

std::unique_ptr<JSONBody> JSONBody::valueParse(JSONParser &jsonParser) {
    jsonParser.skipWhiteSpace();
    std::unique_ptr<JSONBody> value = nullptr;
    if (jsonParser.peek() == '[') {
        value = std::make_unique<JSONArray>();
        int code = value->parse(jsonParser);
        if (code != 0) return nullptr;
    } else if (jsonParser.peek() == '{') {
        value = std::make_unique<JSONObject>();
        int code = value->parse(jsonParser);
        if (code != 0) return nullptr;
    } else if (jsonParser.peek() == '\"') {
        value = std::make_unique<JSONString>();
        int code = value->parse(jsonParser);
        if (code != 0) return nullptr;
    } else if (jsonParser.peek() == 't' || jsonParser.peek() == 'f') {
        value = std::make_unique<JSONBool>();
        int code = value->parse(jsonParser);
        if (code != 0) return nullptr;
    } else if (jsonParser.peek() == 'n') {
        value = std::make_unique<JSONNull>();
        int code = value->parse(jsonParser);
        if (code != 0)return nullptr;
    } else if (std::isdigit(jsonParser.peek()) || jsonParser.peek() == '-') {
        value = std::make_unique<JSONNumber>();
        int code = value->parse(jsonParser);
        if (code != 0) return nullptr;
    } else {
        jsonParser.setErrorCode(-2);
        jsonParser.setErrorInfo("cannot parse into any JSON object.");
        return nullptr;
    }
    return value;
}

