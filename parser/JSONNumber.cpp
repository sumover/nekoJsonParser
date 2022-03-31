//
// Created by sumover on 2022/3/30.
//

#include "JSONNumber.h"

/**
 * 全世界最恶心的解析器
 * @param jsonParser
 * @return code
 */
int JSONNumber::parse(JSONParser &jsonParser) {
    this->val = 0;
    int flag = 1;
    jsonParser.skipWhiteSpace();
    if (!jsonParser) {
        jsonParser.setErrorCode(-1);
        jsonParser.setErrorInfo("cannot parse to Number");
        return -1;
    }
    if (jsonParser.peek() == '-') {
        jsonParser.get();
        flag = -1;
        if (!jsonParser) {
            jsonParser.setErrorCode(-1);
            jsonParser.setErrorInfo("cannot parse `-` to Number.");
            return -1;
        }
    }
    double intPart = 0, doublePart = 0;
    if (jsonParser.peek() == '0') {
        jsonParser.get();
        intPart = 0;
        if (!jsonParser) return val = intPart;
        if (std::isdigit(jsonParser.peek())) {
            jsonParser.setErrorCode(-1);
            jsonParser.setErrorInfo("Integer parts may not start with `0`.");
            return jsonParser.getErrorCode();
        }
    } else {
        while (jsonParser && isdigit(jsonParser.peek())) intPart = intPart * 10 + jsonParser.get() - '0';
        this->val += intPart;
        if (!jsonParser) return 0;
    }
    if (!jsonParser) return 0;

    if (jsonParser.peek() == '.') {
        jsonParser.get();
        if (!jsonParser) {
            jsonParser.setErrorCode(-1);
            jsonParser.setErrorInfo("No fractional part was captured.");
            return -1;
        }
        double exp = 0.1;
        while (jsonParser) {
            if (!std::isdigit(jsonParser.peek())) {
                if (isspace(jsonParser.peek()) || jsonParser.peek() == 'e' || jsonParser.peek() == ',' ||
                    jsonParser.peek() == 'E')
                    break;
                else if (jsonParser.peek() == '.') {
                    jsonParser.setErrorCode(-1);
                    jsonParser.setErrorInfo("Number cannot have more than one `.`");
                    return -1;
                } else {
                    jsonParser.setErrorCode(-1);
                    jsonParser.setErrorInfo("connot parse an character to Number.");
                    return -1;
                }
            }
            doublePart += exp * (jsonParser.get() - '0');
            exp /= 10.0;
        }
        this->val += doublePart;
        if (!jsonParser) return 0;
    }

    if (jsonParser.peek() == 'e' || jsonParser.peek() == 'E') {
        jsonParser.get();
        if (!jsonParser)return 0;
        int eFlag = 1, e = 0;
        if (jsonParser.peek() == '+') jsonParser.get();
        if (jsonParser.peek() == '-') jsonParser.get(), eFlag = -1;

        while (jsonParser) {
            if (std::isspace(jsonParser.peek())) break;
            if (!isdigit(jsonParser.peek())) {
                jsonParser.setErrorCode(-1);
                jsonParser.setErrorInfo("cannot to parse non-numeric characters into numbers.");
                return -1;
            }
            e = e * 10 + jsonParser.get() - '0';
        }
        if (eFlag > 0) while (e--) this->val *= 10.0;
        if (eFlag < 0) while (e--) this->val /= 10.0;
    }
    return 0;
}

std::string JSONNumber::toString() {
    std::stringstream s;
    s << val;
    return s.str();
}
