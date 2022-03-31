//
// Created by sumover on 2022/3/30.
//

#include "JSONParser.h"

#include <cstdio>
#include <cstdlib>
#include <cctype>

void JSONParser::skipWhiteSpace() {
    while (parserString[index] != 0) {
        if (isspace(parserString[index]))
            next();
        else break;
    }
}

void JSONParser::load(const char *json) {
    strcpy(parserString, json);
    len = strlen(json);
    index = 0;
}

void JSONParser::next(int step) {
    if (step + index < len) {
        while (step--) {
            if (parserString[index] == '\n') line++;
            index++;
        }
    } else index = len;

}

bool JSONParser::matchWord(const char *word) {
    for (int i = 0; word[i] != 0; ++i) {
        if (word[i] != parserString[i + index]) return false;
    }
    return true;
}

void JSONParser::setErrorInfo(const char *info) {
    strcpy(errorInfo, info);
}

void JSONParser::setErrorCode(int code) {
    if (errorCode != 0)
        return;
    errorCode = code;
}

const char *JSONParser::getErrorInfo() const {
    return errorInfo;
}

int JSONParser::getErrorCode() const {
    return errorCode;
}

void JSONParser::printErrorInfo() const {
    printf("error %d at %d:: ", errorCode, line);
    printf("%s", errorInfo);
}

JSONParser::JSONParser() :
        index(0), len(0),
        errorCode(0), line(1) {
    parserString = (char *) malloc(sizeof(char) * (1000));
    errorInfo = (char *) malloc(sizeof(char *) * 200);
    memset(errorInfo, 0, sizeof(char) * 200);
}

JSONParser::JSONParser(const char *json) : JSONParser() {
    strcpy(parserString, json);
}
