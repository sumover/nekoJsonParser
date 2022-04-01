//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONBOOL_H
#define JSONPARSER_JSONBOOL_H


#include "JSONBody.h"

class JSONBool : public JSONBody {
    bool val;

public:

    JSONBool() = default;

    JSONBool(const JSONBool &jsonBool) = default;

    ~JSONBool() {}

    explicit operator bool() const { return val; }

    int parse(JSONParser &jsonParser) override;

    std::string toString() override;
};


#endif //JSONPARSER_JSONBOOL_H
