//
// Created by sumover on 2022/3/30.
//

#include "JSONArray.h"

JSONBody *JSONArray::get(int index) {
    return this->array[index];
}

void JSONArray::append(JSONBody *val) {
    this->array.push_back(val);
}

void JSONArray::set(int index, JSONBody *val) {
    this->array[index] = val;
}

std::string JSONArray::toString() {
    if (array.empty()) return "[]";
    std::string res = "[";
    bool flag = false;
    for (const auto &item: array) {
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
    JSONBody *value = nullptr;
    if (!jsonParser) {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("missing `]`");
        return -1;
    }
    if (jsonParser.peek() == ']') {
        jsonParser.get();
        return 0;
    }
    value = JSONBody::valueParse(jsonParser);
    array.push_back(value);
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
            array.push_back(value);
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
    for (auto item: array) delete item;
}

JSONArray::JSONArray() : array() {

}
