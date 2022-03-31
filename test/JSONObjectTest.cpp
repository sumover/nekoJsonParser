//
// Created by sumover on 2022/3/31.
//

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include <JSONObject.h>
#include <JSONNumber.h>

class JSONObjectTest : public testing::Test {
public:
    JSONParser *parser;
    JSONObject jsonObject;
    std::vector<std::string> filePaths = {
            "E:\\jsonParser\\testData\\test1.json",
            "E:\\jsonParser\\testData\\test2.json",
            "E:\\jsonParser\\testData\\test3.json",
            "E:\\jsonParser\\testData\\test4.json",
            "E:\\jsonParser\\testData\\test5.json"
    };
    std::vector<char *> json;
protected:
    void SetUp() override {
        parser = new JSONParser();
        for (const auto &filePath: filePaths) {
            std::ifstream reader(filePath.c_str());
            char *s_json = (char *) malloc(sizeof(char) * 256);
            if (!reader.is_open()) {
                std::cout << "cannot open " << filePath << std::endl;
                return;
            } else std::cout << "file " << filePath << " opened." << std::endl;
            reader.get(s_json, 256, -1);
            json.push_back(s_json);
            reader.close();
        }
    }

    void TearDown() override {
        if (!parser->error()) std::cout << jsonObject.toString() << std::endl;
        else parser->printErrorInfo();

    }
};


TEST_F(JSONObjectTest, test_0) {
    parser->load(json[0]);
    jsonObject.parse(*parser);
    ASSERT_FALSE(parser->error());
    ASSERT_TRUE(jsonObject.empty());
}

TEST_F(JSONObjectTest, test_1) {
    parser->load(json[1]);
    jsonObject.parse(*parser);
    ASSERT_FALSE(parser->error());
    ASSERT_FALSE(jsonObject.empty());
    ASSERT_EQ(1, jsonObject.count("a"));
    auto val = jsonObject.get("a");
    auto number = dynamic_cast<JSONNumber *>(val);
    ASSERT_EQ(int(*number), 123123);
}

TEST_F(JSONObjectTest, test_2) {
    parser->load(json[2]);
    jsonObject.parse(*parser);
    ASSERT_FALSE(parser->error());
    ASSERT_FALSE(jsonObject.empty());
    ASSERT_EQ(jsonObject.count("a"), 1);
    ASSERT_EQ(jsonObject.count("b"), 1);
    ASSERT_EQ(jsonObject.count("c"), 1);
    ASSERT_EQ(jsonObject.count("d"), 1);
    ASSERT_EQ(jsonObject.count("e"), 1);
}

TEST_F(JSONObjectTest, test_3) {
    parser->load(json[3]);
    jsonObject.parse(*parser);
    ASSERT_FALSE(parser->error());
}

TEST_F(JSONObjectTest, test_4) {
    parser->load(json[4]);
    jsonObject.parse(*parser);
    ASSERT_FALSE(parser->error());
}