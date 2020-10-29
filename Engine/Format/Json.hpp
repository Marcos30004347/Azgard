#ifndef AZGARD_LIB_JSON
#define AZGARD_LIB_JSON

#include "Core/Engine.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

#include "File/FileHandle.hpp"

namespace Azgard {

class JsonHandle {
    rapidjson::Document* doc = nullptr;
    JsonHandle(rapidjson::Document* document);
    friend class JsonValue;
    friend class JsonDocument;
};

class AZG_API JsonValue {
    friend class JsonDocument;
    rapidjson::Value* val = nullptr;
    rapidjson::Document* doc = nullptr;
    JsonValue(rapidjson::Value* value, rapidjson::Document* document);
public:
    bool has(const char* key);
    bool isNull();
    const char* readAsString();
    int readAsFloat();
    int readAsDouble();
    int readAsInt();
    int readAsLongInt();
    int readAsUnsignedInt();
    int readAsLongUnsignedInt();
    JsonValue readAsArray(int index);
    bool readAsBool();
    void erase(JsonValue value);
    JsonValue get(const char* key);
    void insertInt(const char* key, int value);
    void insertString(const char* key, const char* value);
    void insertArray(const char* key);
    void insertValue(const char* key, JsonValue value);
    void pushBackValue(JsonValue v);
    void pushBackInt(int i);
    void pushBackBool(bool i);
    void pushBackString(const char* str);
    JsonValue operator[](const char* key);
    JsonValue operator[](int key);
    JsonValue operator=(const char* str);
    JsonValue& operator=(JsonValue& value);
    JsonValue& operator=(JsonValue value);
    JsonValue& operator=(float val);
    JsonValue& operator=(double val);
    JsonValue& operator=(int val);
    JsonValue& operator=(long int val);
    JsonValue& operator=(unsigned int val);
};

class AZG_API JsonDocument {
    JsonHandle* document = nullptr;
public:
    JsonDocument(const char* src);
    JsonDocument(FileHandle& file);
    ~JsonDocument();
    JsonValue get(const char* key);
    bool has(const char* key);
    bool isNull(const char* key);
    bool erase(const char* key);
    void insertInt(const char* key, int value);
    void insertString(const char* key, const char* value);
    void insertArray(const char* key);
    void insertValue(const char* key, JsonValue value);
    JsonValue readAsArray(int index);
    JsonValue operator[](const char* key);
    JsonValue operator[](int key);
    void save(FileHandle handle);
};

}

#endif