//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONOBJECT_H
#define JSONPARSER_JSONOBJECT_H

#include "JSONBody.h"

#include <map>

class JSONObject : public JSONBody {
private:
    std::map<std::string, JSONBody *> fields;

public:

    JSONObject() {}

    ~JSONObject() override;

    JSONObject(const JSONObject &jsonObject) = default;

    void set(std::string &&key, JSONBody *val);

    void set(std::string &key, JSONBody *val);

    JSONBody *get(const std::string &key);

    JSONBody *get(std::string &&key);

    unsigned count(std::string key) {
        return fields.count(key);
    }

    bool empty() const { return fields.empty(); }

    size_t size() const { return fields.size(); }


    std::string toString() override;

    int parse(JSONParser &jsonParser) override;
};


#endif //JSONPARSER_JSONOBJECT_H
