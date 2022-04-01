//
// Created by sumover on 2022/3/30.
//

#include "JSONBool.h"

std::string JSONBool::toString() {
    return val ? "true" : "false";
}

int JSONBool::parse(JSONParser &jsonParser) {
    jsonParser.skipWhiteSpace();
    if (jsonParser.matchWord("true")) {
        val = true;
        jsonParser.next(4);
    } else if (jsonParser.matchWord("false")) {
        val = false;
        jsonParser.next(5);
    } else return -1;
    return 0;
}
