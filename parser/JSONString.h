//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONSTRING_H
#define JSONPARSER_JSONSTRING_H


#include "JSONBody.h"

class JSONString : public JSONBody {

    std::string val;
public:
    JSONString() = default;

    explicit JSONString(std::string val);

    virtual ~JSONString() override {}

    std::string toString() override;

    const char *c_str() const;

    int parse(JSONParser &jsonParser) override;

};


#endif //JSONPARSER_JSONSTRING_H
