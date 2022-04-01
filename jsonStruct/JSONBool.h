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

    explicit JSONBool(bool v);

    JSONBool(const JSONBool &jsonBool) = default;

    ~JSONBool() override {}

    explicit operator bool() const { return val; }

    explicit operator int() const { return int(val); }

    JSONBool &operator=(bool v) {
        this->val = v;
        return *this;
    }

    int parse(JSONParser &jsonParser) override;

    std::string toString() override;
};


#endif //JSONPARSER_JSONBOOL_H
