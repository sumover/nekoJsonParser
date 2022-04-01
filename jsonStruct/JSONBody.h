//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONBODY_H
#define JSONPARSER_JSONBODY_H

#include <string>
#include <memory>

#include "../parser/JSONParser.h"

class JSONBody {
public:
    virtual std::string toString() = 0;

    JSONBody() = default;

    virtual ~JSONBody() {}

    virtual int parse(JSONParser &jsonParser) = 0;

    static std::unique_ptr<JSONBody> valueParse(JSONParser &jsonParser);
};


#endif //JSONPARSER_JSONBODY_H
