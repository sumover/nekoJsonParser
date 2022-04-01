//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONOBJECT_H
#define JSONPARSER_JSONOBJECT_H

#include "JSONBody.h"

#include <map>

class JSONObject : public JSONBody {
private:
    std::map<std::string, std::unique_ptr<JSONBody>> fields;

public:

    JSONObject() {}

    JSONObject(JSONObject &&jsonObject) noexcept;

    ~JSONObject() override;

    JSONObject(const JSONObject &jsonObject) = default;

    void set(std::string &&key, std::unique_ptr<JSONBody> &val);

    void set(std::string &key, std::unique_ptr<JSONBody> &val);

    void set(std::string, std::unique_ptr<JSONBody>);

    void set(const std::string &key, int val);

    void set(const std::string &key, double val);

    void set(const std::string &key, const std::string &val);

    void set(const std::string &key, bool val);

    void setNull(const std::string &key);

    std::unique_ptr<JSONBody> &get(const std::string &key);

    std::unique_ptr<JSONBody> &get(std::string &&key);

    unsigned count(const std::string &key) { return fields.count(key); }

    bool empty() const { return fields.empty(); }

    size_t size() const { return fields.size(); }


    std::string toString() override;

    int parse(JSONParser &jsonParser) override;
};


#endif //JSONPARSER_JSONOBJECT_H
