//
// Created by sumover on 2022/3/30.
//

#include "JSONString.h"

#include <utility>

std::string JSONString::toString() {
    std::string res = "\"";
    for (const auto &item: val) {
        if (item == '\"' ||
            item == '\'' ||
            item == '\\' ||
            item == '\b' ||
            item == '\f' ||
            item == '\n' ||
            item == '\r' ||
            item == '\t') {
            res += '\\';
        } else res += item;

        switch (item) {
            case '\"':
                res += '\"';
                break;
            case '\'':
                res += '\'';
                break;
            case '\\':
                res += '\\';
                break;
            case '\b':
                res += 'b';
                break;
            case '\f':
                res += 'f';
                break;
            case '\n':
                res += 'n';
                break;
            case '\r':
                res += 'r';
                break;
            case '\t':
                res += 't';
                break;
            default:
                break;
        }
    }
    return res + "\"";
}

JSONString::JSONString(std::string val) : val(std::move(val)) {

}

int JSONString::parse(JSONParser &jsonParser) {
    this->val = "";
    jsonParser.skipWhiteSpace();
    if (!jsonParser) {
        jsonParser.setErrorInfo("no string can be parsed.");
        jsonParser.setErrorCode(-1);
        return -1;
    }
    if (jsonParser.peek() == '\"') {
        jsonParser.get();
    } else {
        jsonParser.setErrorInfo("string type must begin with a `\"`");
        jsonParser.setErrorCode(-1);
        return -1;
    }
    if (!jsonParser) {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("single \" cannot construct a string.");
        return -1;
    }
    if (jsonParser.peek() == '\"') {
        jsonParser.get();
        return 0;
    }
    while (jsonParser.peek() != '\"') {
        if (!jsonParser) {
            jsonParser.setErrorCode(-1);
            jsonParser.setErrorInfo("expect right \".");
            return -1;
        }
        switch (jsonParser.peek()) {
            case '\\': {
                jsonParser.get();
                if (!jsonParser) {
                    jsonParser.setErrorCode(-1);
                    jsonParser.setErrorInfo("expect right \".");
                    return -1;
                }
                switch (jsonParser.peek()) {
                    case '\"':
                        val += '\"';
                        break;
                    case '\\':
                        val += '\\';
                        break;
                    case '\'':
                        val += '\'';
                        break;
                    case 'b':
                        val += '\b';
                        break;
                    case 'f':
                        val += '\f';
                        break;
                    case 'n':
                        val += '\n';
                        break;
                    case 'r':
                        val += '\r';
                        break;
                    case 't':
                        val += '\t';
                        break;
                    default: {
                        jsonParser.setErrorCode(-1);
                        char *err = R"(no control character like \ )";
                        err[strlen(err) - 1] = jsonParser.peek();
                        jsonParser.setErrorInfo(err);
                        return -1;
                    }
                }
                jsonParser.get();
                break;
            }
            case '\n': {
                jsonParser.setErrorCode(-1);
                jsonParser.setErrorInfo("A string cannot cross lines.");
                return -1;
            }
            default: {
                val += jsonParser.get();
            }
        }
    }
    jsonParser.get();
    return 0;
}

const char *JSONString::c_str() const {
    return val.c_str();
}
