//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONARRAY_H
#define JSONPARSER_JSONARRAY_H

#include "JSONBody.h"
#include <vector>

class JSONArray : public JSONBody {
    typedef std::unique_ptr<JSONBody> pJSONBody;

    std::vector<pJSONBody> array;

public:
    JSONArray();

    JSONArray(const JSONArray &jsonArray) = default;

    ~JSONArray() override;

    pJSONBody &get(int index);

    void append(pJSONBody val);

    void set(int index, pJSONBody val);

    std::string toString() override;

    int parse(JSONParser &jsonParser) override;
};


#endif //JSONPARSER_JSONARRAY_H
