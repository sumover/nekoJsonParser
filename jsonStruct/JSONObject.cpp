//
// Created by sumover on 2022/3/30.
//

#include "JSONObject.h"
#include "JSONString.h"


void JSONObject::set(std::string &&key, JSONBody *val) {
    fields[key] = val;
}

void JSONObject::set(std::string &key, JSONBody *val) {
    fields[key] = val;
}

std::string JSONObject::toString() {
    if (fields.empty()) return "{}";
    std::string res = "{\n";
    bool flag = false;
    for (const auto &pair: fields) {
        if (flag) res += ",\n";
        JSONString key(pair.first);
        res += key.toString() + " : " + pair.second->toString();
        flag = true;
    }
    return res + "\n}\n";
}

JSONBody *JSONObject::get(const std::string &key) {
    return this->fields[key];
}

JSONBody *JSONObject::get(std::string &&key) {
    return this->fields[key];
}

int JSONObject::parse(JSONParser &jsonParser) {
    jsonParser.skipWhiteSpace();
    fields.clear();
    if (!jsonParser || jsonParser.peek() != '{') {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("JSON object must begin with `{`");
        return -1;
    } else jsonParser.get();
    jsonParser.skipWhiteSpace();
    if (!jsonParser) {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("expect more rather than single `{`");
        return -1;
    }
    if (jsonParser.peek() == '}') {
        jsonParser.get();
        return 0;
    }
    JSONString key;
    JSONBody *value;
    key.parse(jsonParser);
    if (jsonParser.error()) return jsonParser.getErrorCode();
    jsonParser.skipWhiteSpace();
    if (jsonParser.peek() != ':') {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("expect `:` between key and value");
        return -1;
    } else jsonParser.get();
    value = JSONBody::valueParse(jsonParser);
    if (jsonParser.error()) return jsonParser.getErrorCode();
    fields[std::string(key.c_str())] = value;
    while (true) {
        jsonParser.skipWhiteSpace();
        if (!jsonParser) {
            jsonParser.setErrorCode(-1);
            jsonParser.setErrorInfo("expect `}`");
            return -1;
        }
        if (jsonParser.peek() == ',') {
            jsonParser.get();
            key.parse(jsonParser);
            if (jsonParser.error()) return jsonParser.getErrorCode();
            jsonParser.skipWhiteSpace();
            if (jsonParser.peek() != ':') {
                jsonParser.setErrorCode(-1);
                jsonParser.setErrorInfo("expect `:` between key and value");
                return -1;
            } else jsonParser.get();
            value = JSONBody::valueParse(jsonParser);
            if (jsonParser.error()) return jsonParser.getErrorCode();
            fields[std::string(key.c_str())] = value;
            continue;
        } else if (jsonParser.peek() == '}') {
            jsonParser.get();
            break;
        } else {
            jsonParser.setErrorCode(-1);
            jsonParser.setErrorInfo("expect `,` between datas.");
            return -1;
        }
    }
    return 0;
}

JSONObject::~JSONObject() {
    for (auto &item: fields) {
        delete item.second;
    }
}

