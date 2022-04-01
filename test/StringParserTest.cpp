//
// Created by sumover on 2022/3/31.
//
#include <gtest/gtest.h>
#include <JSONString.h>

class StringParserTest : public testing::Test {
public:
    int size = 0;
    std::vector<const char *> json = {
            R"("aa")",
            R"("")",
            R"("aa\taa\naa\baa")",
            R"("aa\"")"
    }, result = {
            "aa",
            "",
            "aa\taa\naa\baa",
            "aa\""
    };
    std::vector<int> codes = {
            0, 0, 0, 0
    };

    JSONString jsonString;
    JSONParser *jsonParser;

    void SetUp() override {
        size = codes.size();
        jsonParser = new JSONParser("");
    }
};

TEST_F(StringParserTest, test1) {
    for (int i = 0; i < size; ++i) {
        jsonParser->load(json[i]);
        int code = jsonString.parse(*jsonParser);
        ASSERT_EQ(code, codes[i]);
        ASSERT_STREQ(result[i], jsonString.c_str());
    }
}
