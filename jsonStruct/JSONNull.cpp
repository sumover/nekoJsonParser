//
// Created by sumover on 2022/3/30.
//

#include "JSONNull.h"

std::string JSONNull::toString() {
    return "null";
}

int JSONNull::parse(JSONParser &jsonParser) {
    jsonParser.skipWhiteSpace();
    if (jsonParser.matchWord("null")) jsonParser.next(4);
    else return -1;
    return 0;
}

JSONNull::~JSONNull() = default;
