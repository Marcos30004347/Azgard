#include "Json.hpp"

using namespace Azgard;

JsonHandle::JsonHandle(rapidjson::Document* document): doc{document} {}


JsonValue::JsonValue(rapidjson::Value* value, rapidjson::Document* document): val{value}, doc{document} {}

AZG_API const char* JsonValue::readAsString() { return this->val->GetString();}
AZG_API int JsonValue::readAsFloat() { return this->val->GetFloat();}
AZG_API int JsonValue::readAsDouble() { return this->val->GetDouble();}
AZG_API int JsonValue::readAsInt() { return this->val->GetInt();}
AZG_API int JsonValue::readAsLongInt() { return this->val->GetInt64();}
AZG_API int JsonValue::readAsUnsignedInt() { return this->val->GetUint();}
AZG_API int JsonValue::readAsLongUnsignedInt() { return this->val->GetUint64();}
AZG_API JsonValue JsonValue::readAsArray(int index) { return JsonValue(&this->val->GetArray()[index], this->doc);}
AZG_API bool JsonValue::readAsBool() { return this->val->GetBool(); }
AZG_API void JsonValue::erase(JsonValue value) { this->val->EraseMember(*value.val); }

AZG_API JsonValue JsonValue::get(const char* key) {
    if(!this->val->HasMember(key)) {
        rapidjson::Value _key(key, this->doc->GetAllocator());
        this->val->AddMember(
            _key,
            rapidjson::Value(),
            this->doc->GetAllocator()
        );
        this->val->FindMember(key)->value.SetNull();
    }
    return JsonValue(&this->val->FindMember(key)->value, this->doc);
}

AZG_API void JsonValue::insertInt(const char* key, int value) {
    rapidjson::Value _key(key, this->doc->GetAllocator());
    this->val->AddMember(
        _key,
        value,
        this->doc->GetAllocator()
    );
}

AZG_API void JsonValue::insertString(const char* key, const char* value) {
    rapidjson::Value _key(key, this->doc->GetAllocator());
    rapidjson::Value _value(value, this->doc->GetAllocator());

    this->val->AddMember(
        _key,
        _value,
        this->doc->GetAllocator()
    );
}

AZG_API void JsonValue::insertArray(const char* key) {
    rapidjson::Value _key(key, this->doc->GetAllocator());
    rapidjson::Value _value;
    this->val->AddMember(
        _key,
        _value,
        this->doc->GetAllocator()
    );
    this->val->FindMember(key)->value.SetArray();
}

AZG_API void JsonValue::insertValue(const char* key, JsonValue value) {
    rapidjson::Value _key(key, this->doc->GetAllocator());
    this->val->AddMember(
        _key,
        *value.val,
        this->doc->GetAllocator()
    );
}

AZG_API void JsonValue::pushBackValue(JsonValue v) {
    this->val->PushBack(*v.val, this->doc->GetAllocator());
}
AZG_API void JsonValue::pushBackInt(int i) {
    this->val->PushBack(i, this->doc->GetAllocator());
}
AZG_API void JsonValue::pushBackBool(bool i) {
    this->val->PushBack(i, this->doc->GetAllocator());
}
AZG_API void JsonValue::pushBackString(const char* str) {
    this->val->PushBack(
        rapidjson::Value(str,
        this->doc->GetAllocator()),
        this->doc->GetAllocator()
    );
}

AZG_API JsonValue JsonValue::operator[](const char* key) {
    return this->get(key);
}

AZG_API JsonValue JsonValue::operator[](int key) {
    return this->readAsArray(key);
}

AZG_API JsonValue JsonValue::operator=(const char* str) {
    this->val->Set(str, this->doc->GetAllocator());
    return *this;
}

AZG_API JsonValue& JsonValue::operator=(JsonValue& value) {
    this->val->CopyFrom(*(value.val), value.doc->GetAllocator());
    this->doc = value.doc;
    return *this;
}

AZG_API JsonValue& JsonValue::operator=(JsonValue value) {
    this->val->CopyFrom(*(value.val), value.doc->GetAllocator());
    this->doc = value.doc;
    return *this;
}

AZG_API JsonValue& JsonValue::operator=(float val) {
    this->val->SetFloat(val);
    return *this;
}

AZG_API JsonValue& JsonValue::operator=(double val) {
    this->val->SetDouble(val);
    return *this;
}

AZG_API JsonValue& JsonValue::operator=(int val) {
    this->val->SetInt(val);
    return *this;
}

AZG_API JsonValue& JsonValue::operator=(long int val) {
    this->val->SetInt64(val);
    return *this;
}

AZG_API JsonValue& JsonValue::operator=(unsigned int val) {
    this->val->SetInt64(val);
    return *this;
}

AZG_API bool JsonValue::has(const char* key) { return this->val->HasMember(key); }

AZG_API bool JsonValue::isNull() { return this->val->IsNull(); }


AZG_API JsonDocument::JsonDocument(File* file) {
    rapidjson::Document* doc = new rapidjson::Document();
    doc->Parse(file->getBuffer().c_str());
    this->document = new JsonHandle(doc);
}

AZG_API JsonDocument::JsonDocument(const char* src) {
    rapidjson::Document* doc = new rapidjson::Document();
    doc->Parse(src);
    this->document = new JsonHandle(doc);
}

AZG_API JsonDocument::~JsonDocument() {
    delete document;
}

AZG_API JsonValue JsonDocument::get(const char* key) {
    if(!this->document->doc->HasMember(key)) {
        rapidjson::Value _key(key, this->document->doc->GetAllocator());
        this->document->doc->AddMember(
            _key,
            rapidjson::Value(),
            this->document->doc->GetAllocator()
        );
        this->document->doc->FindMember(key)->value.SetNull();
    }

    return JsonValue(&this->document->doc->FindMember(key)->value, this->document->doc);
}

AZG_API bool JsonDocument::has(const char* key) { return this->document->doc->HasMember(key); }

AZG_API bool JsonDocument::isNull(const char* key) { return this->get(key).val->IsNull();}

AZG_API bool JsonDocument::erase(const char* key) { return this->document->doc->RemoveMember(key); }

AZG_API void JsonDocument::insertInt(const char* key, int value) {
    rapidjson::Value _key(key, this->document->doc->GetAllocator());
    this->document->doc->AddMember(
        _key,
        value,
        this->document->doc->GetAllocator()
    );
}

AZG_API void JsonDocument::insertString(const char* key, const char* value) {
    rapidjson::Value _key(key, this->document->doc->GetAllocator());
    rapidjson::Value _value(value, this->document->doc->GetAllocator());

    this->document->doc->AddMember(
        _key,
        _value,
        this->document->doc->GetAllocator()
    );
}

AZG_API void JsonDocument::insertArray(const char* key) {
    rapidjson::Value _key(key, this->document->doc->GetAllocator());
    rapidjson::Value _value;
    this->document->doc->AddMember(
        _key,
        _value,
        this->document->doc->GetAllocator()
    );
    this->document->doc->FindMember(key)->value.SetArray();
}

AZG_API void JsonDocument::insertValue(const char* key, JsonValue value) {
    rapidjson::Value _key(key, this->document->doc->GetAllocator());
    this->document->doc->AddMember(
        _key,
        *value.val,
        this->document->doc->GetAllocator()
    );
}

AZG_API JsonValue JsonDocument::readAsArray(int index) { return JsonValue(&this->document->doc->GetArray()[index], this->document->doc);}


AZG_API JsonValue JsonDocument::operator[](const char* key) {
    return this->get(key);
}

AZG_API JsonValue JsonDocument::operator[](int key) {
    return this->readAsArray(key);
}

AZG_API void JsonDocument::save(File* handle) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    this->document->doc->Accept(writer);

    handle->write(buffer.GetString());
}
