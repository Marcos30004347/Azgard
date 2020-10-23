
#include"String.hpp"

#include <malloc.h>
#include <string.h>

using namespace Azgard;


String::String(const char* text) {
    unsigned int string_len = strlen(text);
    data = (char*)malloc(string_len);
    memcpy(data, text, string_len);
    data[string_len] = '\0';
}


String::String(char* text, unsigned int length) {
    data = (char*)malloc(length + 1);
    for(int i=0; i<length; i++) data[i] = text[i];
    data[length] = '\0';
}

const char* String::cString() { return (const char*)data; }

String::~String() { delete data; }

