//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONARRAY_H
#define JSONPARSER_JSONARRAY_H

#include "JSONBody.h"
#include <vector>

class JSONArray : public JSONBody {

    std::vector<std::unique_ptr<JSONBody> > array;

public:
    JSONArray();

    JSONArray(const JSONArray &jsonArray) = default;

    JSONArray(JSONArray &&jsonArray) noexcept ;

    ~JSONArray() override;

    std::unique_ptr<JSONBody> &get(int index);

    void append(std::unique_ptr<JSONBody> val);

    void set(int index, std::unique_ptr<JSONBody> val);

    std::string toString() override;

    int parse(JSONParser &jsonParser) override;
};


#endif //JSONPARSER_JSONARRAY_H
