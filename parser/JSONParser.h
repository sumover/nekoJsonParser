//
// Created by sumover on 2022/3/30.
//

#ifndef JSONPARSER_JSONPARSER_H
#define JSONPARSER_JSONPARSER_H

#include <cstring>
#include <cstdlib>

class JSONParser {
    char *parserString, *errorInfo;
    size_t index, len, line;
    int errorCode = 0;

public:
    explicit JSONParser();

    explicit JSONParser(const char *json);

    void load(const char *json);

    void clear() {
        len = index = parserString[0] = 0;
    }

    char get() {
        char res = parserString[index];
        next();
        return res;
    }

    char peek() const { return parserString[index]; }

    void next(int step = 1);

    void skipWhiteSpace();

    bool matchWord(const char *word);

    void setErrorInfo(const char *info);

    void setErrorCode(int code);

    const char *getErrorInfo() const;

    int getErrorCode() const;

    void printErrorInfo() const;

    bool error() const { return errorCode != 0; }

    explicit operator bool() const { return index < len; }
};


#endif //JSONPARSER_JSONPARSER_H
