//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONARRAY_H
#define JSONPARSER_JSONARRAY_H

#include "JSONBody.h"
#include <vector>

class JSONArray : public JSONBody {
    std::vector<JSONBody *> array;

public:
    JSONArray();

    JSONArray(const JSONArray &jsonArray) = default;

    ~JSONArray() override;

    JSONBody *get(int index);

    void append(JSONBody *val);

    void set(int index, JSONBody *val);

    std::string toString() override;

    int parse(JSONParser &jsonParser) override;
};


#endif //JSONPARSER_JSONARRAY_H
