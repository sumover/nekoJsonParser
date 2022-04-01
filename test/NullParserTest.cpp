//
// Created by sumov on 2022/3/31.
//


#include <gtest/gtest.h>
#include <JSONNull.h>

TEST(NullParser, test1) {
    std::unique_ptr<JSONNull> jsonNull = std::make_unique<JSONNull>();
    JSONParser parser("null");
    int code = jsonNull->parse(parser);
    ASSERT_EQ(code, 0);
    ASSERT_STREQ(jsonNull->toString().c_str(), "null");
}

TEST(nullparser, test2) {
    std::unique_ptr<JSONNull> jsonNull = std::make_unique<JSONNull>();
    JSONParser parser("123213123");
    int code = jsonNull->parse(parser);
    ASSERT_NE(code, 0);
}