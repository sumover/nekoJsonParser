//
// Created by sumover on 2022/3/30.
//

#include "JSONObject.h"
#include "JSONString.h"
#include "JSONBool.h"
#include "JSONNumber.h"
#include "JSONArray.h"
#include "JSONNull.h"
#include "JSONBody.h"


std::string JSONObject::toString() {
    if (fields.empty()) return "{}";
    std::string res = "{\n";
    bool flag = false;
    for (auto &&pair: fields) {
        if (flag) res += ",\n";
        JSONString key(pair.first);
        res += key.toString() + " : " + pair.second->toString();
        flag = true;
    }
    return res + "\n}\n";
}

std::unique_ptr<JSONBody> &JSONObject::get(const std::string &key) {
    return this->fields[key];
}

std::unique_ptr<JSONBody> &JSONObject::get(std::string &&key) {
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
    std::unique_ptr<JSONBody> value;
    key.parse(jsonParser);
    if (jsonParser.error()) return jsonParser.getErrorCode();
    jsonParser.skipWhiteSpace();
    if (jsonParser.peek() != ':') {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("expect `:` between key and value");
        return -1;
    } else jsonParser.get();
    value = std::move(JSONBody::valueParse(jsonParser));
    if (jsonParser.error()) return jsonParser.getErrorCode();
    fields[std::string(key.c_str())] = std::move(value);
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
            fields[std::string(key.c_str())] = std::move(value);
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
}

void JSONObject::set(const std::string &key, int val) {
    std::unique_ptr<JSONBody> number = std::make_unique<JSONNumber>(val);
    this->set(key, std::move(number));
}

void JSONObject::set(const std::string &key, double val) {
    std::unique_ptr<JSONBody> number = std::make_unique<JSONNumber>(val);
    this->set(key, std::move(number));
}

void JSONObject::set(const std::string &key, const std::string &val) {
    std::unique_ptr<JSONBody> json_str = std::make_unique<JSONString>(val);
    this->set(key, std::move(json_str));
}

void JSONObject::setNull(const std::string &key) {
    this->set(key, std::make_unique<JSONNull>());
}

void JSONObject::set(const std::string &key, bool val) {
    std::unique_ptr<JSONBody> json_bool = std::make_unique<JSONBool>(val);
    this->set(key, std::move(json_bool));
}

JSONObject::JSONObject(JSONObject &&jsonObject) noexcept: fields(std::move(jsonObject.fields)) {

}

void JSONObject::set(std::string &&key, std::unique_ptr<JSONBody> &val) {
    fields[key] = std::move(val);
}

void JSONObject::set(std::string &key, std::unique_ptr<JSONBody> &val) {
    fields[key] = std::move(val);
}

void JSONObject::set(std::string key, std::unique_ptr<JSONBody> val) {
    fields[key] = std::move(val);
}

std::map<std::string, std::unique_ptr<JSONBody>> &JSONObject::getDict() {
    return this->fields;
}

void JSONObject::removeKey(const std::string& key) {
    this->fields.erase(key);
}