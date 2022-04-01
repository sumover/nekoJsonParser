//
// Created by sumover on 2022/3/30.
//

#include "JSONArray.h"

std::unique_ptr<JSONBody> &JSONArray::get(int index) {
    return this->array.at(index);
}

void JSONArray::append(std::unique_ptr<JSONBody> val) {
    this->array.push_back(std::move(val));
}

void JSONArray::set(int index, std::unique_ptr<JSONBody> val) {
    this->array[index] = std::move(val);
}

std::string JSONArray::toString() {
    if (array.empty()) return "[]";
    std::string res = "[";
    bool flag = false;
    for (std::unique_ptr<JSONBody> &item: array) {
        if (flag) res += " ,";
        res += item->toString();
        flag = true;
    }
    return res + ']';
}

int JSONArray::parse(JSONParser &jsonParser) {
    array.clear();
    jsonParser.skipWhiteSpace();
    if (jsonParser.get() != '[') {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("array must begin with a `[`");
        return -1;
    }
    jsonParser.skipWhiteSpace();
    std::unique_ptr<JSONBody> value;
    if (!jsonParser) {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("missing `]`");
        return -1;
    }
    if (jsonParser.peek() == ']') {
        jsonParser.get();
        return 0;
    }
    value = std::move(JSONBody::valueParse(jsonParser));
    array.push_back(std::move(value));
    if (jsonParser.getErrorCode() != 0) return jsonParser.getErrorCode();
    while (true) {
        jsonParser.skipWhiteSpace();
        if (!jsonParser) {
            jsonParser.setErrorCode(-1);
            jsonParser.setErrorInfo("expect `]`");
            return -1;
        }
        if (jsonParser.peek() == ',') {
            jsonParser.get();
            value = JSONBody::valueParse(jsonParser);
            if (jsonParser.getErrorCode() != 0) return jsonParser.getErrorCode();
            array.push_back(std::move(value));
            continue;
        } else if (jsonParser.peek() == ']') break;
        else {
            jsonParser.setErrorCode(-1);
            jsonParser.setErrorInfo("expect `,` between datas.");
            return -1;
        }
    }
    jsonParser.get();
    return 0;
}

JSONArray::~JSONArray() {
}

JSONArray::JSONArray() : array() {

}

JSONArray::JSONArray(JSONArray &&jsonArray) noexcept: array(jsonArray.array) {

}
