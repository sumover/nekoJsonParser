//
// Created by sumov on 2022/3/31.
//

#include <gtest/gtest.h>

#include <JSONBool.h>

TEST(jsonbool, false_test) {
    JSONParser jsonParser("false");
    JSONBool jsonBool;
    int code = jsonBool.parse(jsonParser);
    ASSERT_EQ(code, 0);
    ASSERT_FALSE(jsonBool);
}

TEST(jsonbool, true_test) {
    JSONParser jsonParser("true");
    JSONBool jsonBool;
    int code = jsonBool.parse(jsonParser);
    ASSERT_EQ(code, 0);
    ASSERT_TRUE(jsonBool);
}

TEST(jsonbool, error_test) {
    JSONParser jsonParser("flse");
    JSONBool jsonBool;
    int code = jsonBool.parse(jsonParser);
    ASSERT_NE(code, 0);
}

