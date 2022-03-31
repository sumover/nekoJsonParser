//
// Created by sumov on 2022/3/30.
//

#ifndef JSONPARSER_JSONNUMBER_H
#define JSONPARSER_JSONNUMBER_H


#include "JSONBody.h"
#include "sstream"

class JSONNumber : public JSONBody {
    double val;
public:
    JSONNumber() : val(0) {}

    JSONNumber(double v) : val(v) {}

    JSONNumber(int v) : val(v) {}

    JSONNumber &operator=(const double v) {
        val = v;
        return *this;
    }

    JSONNumber &operator=(const int v) {
        val = v;
        return *this;
    }

    explicit operator double() const { return val; }

    explicit operator int() const { return int(val); }


    std::string toString() override;

    int parse(JSONParser &jsonParser) override;

    ~JSONNumber() override = default;

};


#endif //JSONPARSER_JSONNUMBER_H
