#ifndef AZGARD_LIB_JSON
#define AZGARD_LIB_JSON

#include "Core/Engine.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

#include "Library/File.hpp"

namespace Azgard {

class JsonHandle {
    rapidjson::Document* doc = nullptr;
    JsonHandle(rapidjson::Document* document);
    friend class JsonValue;
    friend class JsonDocument;
};

class JsonValue {
    friend class JsonDocument;
    rapidjson::Value* val = nullptr;
    rapidjson::Document* doc = nullptr;
    JsonValue(rapidjson::Value* value, rapidjson::Document* document);
public:
    AZG_API bool has(const char* key);
    AZG_API bool isNull();
    AZG_API const char* readAsString();
    AZG_API int readAsFloat();
    AZG_API int readAsDouble();
    AZG_API int readAsInt();
    AZG_API int readAsLongInt();
    AZG_API int readAsUnsignedInt();
    AZG_API int readAsLongUnsignedInt();
    AZG_API JsonValue readAsArray(int index);
    AZG_API bool readAsBool();
    AZG_API void erase(JsonValue value);
    AZG_API JsonValue get(const char* key);
    AZG_API void insertInt(const char* key, int value);
    AZG_API void insertString(const char* key, const char* value);
    AZG_API void insertArray(const char* key);
    AZG_API void insertValue(const char* key, JsonValue value);
    AZG_API void pushBackValue(JsonValue v);
    AZG_API void pushBackInt(int i);
    AZG_API void pushBackBool(bool i);
    AZG_API void pushBackString(const char* str);
    AZG_API JsonValue operator[](const char* key);
    AZG_API JsonValue operator[](int key);
    AZG_API JsonValue operator=(const char* str);
    AZG_API JsonValue& operator=(JsonValue& value);
    AZG_API JsonValue& operator=(JsonValue value);
    AZG_API JsonValue& operator=(float val);
    AZG_API JsonValue& operator=(double val);
    AZG_API JsonValue& operator=(int val);
    AZG_API JsonValue& operator=(long int val);
    AZG_API JsonValue& operator=(unsigned int val);
};

class JsonDocument {
    JsonHandle* document = nullptr;
public:
    AZG_API JsonDocument(const char* src);
    AZG_API JsonDocument(File* file);
    AZG_API ~JsonDocument();
    AZG_API JsonValue get(const char* key);
    AZG_API bool has(const char* key);
    AZG_API bool isNull(const char* key);
    AZG_API bool erase(const char* key);
    AZG_API void insertInt(const char* key, int value);
    AZG_API void insertString(const char* key, const char* value);
    AZG_API void insertArray(const char* key);
    AZG_API void insertValue(const char* key, JsonValue value);
    AZG_API JsonValue readAsArray(int index);
    AZG_API JsonValue operator[](const char* key);
    AZG_API JsonValue operator[](int key);
    AZG_API void save(File* handle);
};

}

#endif