//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONNULL_H
#define JSONPARSER_JSONNULL_H

#include "JSONBody.h"


class JSONNull : public JSONBody {
public:
    JSONNull() : JSONBody() {}

    ~JSONNull() override;

    std::string toString() override;

    int parse(JSONParser &jsonParser) override;
};

#endif //JSONPARSER_JSONNULL_H
