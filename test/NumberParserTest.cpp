//
// Created by sumov on 2022/3/31.
//

#include <gtest/gtest.h>
#include <JSONNumber.h>


class NumberParseTest : public testing::Test {
public:
    JSONNumber number;
    JSONParser *parser;

    std::vector<double> values = {
            213123,
            1,
            0,
            01,
            123,
            0.1,
            0.02,
            0.001,
            1e2,
            12.333e2,
            123e-1,
            123213
    };
    std::vector<std::string> json = {
            "213123.",
            "1",
            "0",
            "01",
            "123",
            "0.1",
            "0.02",
            "0.001",
            "1e2",
            "12.333e2",
            "123e-1",
            "123213    ",
    };
    std::vector<int> codes = {
            -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0
    };

protected:
    void SetUp() override {
        parser = new JSONParser("");
    }
};


TEST_F(NumberParseTest, test) {
    for (int i = 0; i < codes.size(); ++i) {
        parser->load(json[i].c_str());
        int code = number.parse(*parser);
        ASSERT_EQ(code, codes[i]);
        if (code == 0) {
            ASSERT_DOUBLE_EQ(double(number), values[i]);
        } else parser->printErrorInfo();
    }
}