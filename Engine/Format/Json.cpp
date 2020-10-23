#include "Json.hpp"

using namespace Azgard;

JsonHandle::JsonHandle(rapidjson::Document* document): doc{document} {}


JsonValue::JsonValue(rapidjson::Value* value, rapidjson::Document* document): val{value}, doc{document} {}

const char* JsonValue::readAsString() { return this->val->GetString();}
int JsonValue::readAsFloat() { return this->val->GetFloat();}
int JsonValue::readAsDouble() { return this->val->GetDouble();}
int JsonValue::readAsInt() { return this->val->GetInt();}
int JsonValue::readAsLongInt() { return this->val->GetInt64();}
int JsonValue::readAsUnsignedInt() { return this->val->GetUint();}
int JsonValue::readAsLongUnsignedInt() { return this->val->GetUint64();}
JsonValue JsonValue::readAsArray(int index) { return JsonValue(&this->val->GetArray()[index], this->doc);}
bool JsonValue::readAsBool() { return this->val->GetBool(); }

void JsonValue::erase(JsonValue value) {
    this->val->EraseMember(*value.val);
}

JsonValue JsonValue::get(const char* key) {
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

void JsonValue::insertInt(const char* key, int value) {
    rapidjson::Value _key(key, this->doc->GetAllocator());
    this->val->AddMember(
        _key,
        value,
        this->doc->GetAllocator()
    );
}

void JsonValue::insertString(const char* key, const char* value) {
    rapidjson::Value _key(key, this->doc->GetAllocator());
    rapidjson::Value _value(value, this->doc->GetAllocator());

    this->val->AddMember(
        _key,
        _value,
        this->doc->GetAllocator()
    );
}

void JsonValue::insertArray(const char* key) {
    rapidjson::Value _key(key, this->doc->GetAllocator());
    rapidjson::Value _value;
    this->val->AddMember(
        _key,
        _value,
        this->doc->GetAllocator()
    );
    this->val->FindMember(key)->value.SetArray();
}

void JsonValue::insertValue(const char* key, JsonValue value) {
    rapidjson::Value _key(key, this->doc->GetAllocator());
    this->val->AddMember(
        _key,
        *value.val,
        this->doc->GetAllocator()
    );
}

void JsonValue::pushBackValue(JsonValue v) {
    this->val->PushBack(*v.val, this->doc->GetAllocator());
}
void JsonValue::pushBackInt(int i) {
    this->val->PushBack(i, this->doc->GetAllocator());
}
void JsonValue::pushBackBool(bool i) {
    this->val->PushBack(i, this->doc->GetAllocator());
}
void JsonValue::pushBackString(const char* str) {
    this->val->PushBack(
        rapidjson::Value(str,
        this->doc->GetAllocator()),
        this->doc->GetAllocator()
    );
}

JsonValue JsonValue::operator[](const char* key) {
    return this->get(key);
}

JsonValue JsonValue::operator[](int key) {
    return this->readAsArray(key);
}

JsonValue JsonValue::operator=(const char* str) {
    this->val->Set(str, this->doc->GetAllocator());
    return *this;
}

JsonValue& JsonValue::operator=(JsonValue& value) {
    this->val->CopyFrom(*(value.val), value.doc->GetAllocator());
    this->doc = value.doc;
    return *this;
}

JsonValue& JsonValue::operator=(JsonValue value) {
    this->val->CopyFrom(*(value.val), value.doc->GetAllocator());
    this->doc = value.doc;
    return *this;
}

JsonValue& JsonValue::operator=(float val) {
    this->val->SetFloat(val);
    return *this;
}

JsonValue& JsonValue::operator=(double val) {
    this->val->SetDouble(val);
    return *this;
}

JsonValue& JsonValue::operator=(int val) {
    this->val->SetInt(val);
    return *this;
}

JsonValue& JsonValue::operator=(long int val) {
    this->val->SetInt64(val);
    return *this;
}

JsonValue& JsonValue::operator=(unsigned int val) {
    this->val->SetInt64(val);
    return *this;
}

bool JsonValue::has(const char* key) { return this->val->HasMember(key); }

bool JsonValue::isNull() { return this->val->IsNull(); }


JsonDocument::JsonDocument(File* file) {
    rapidjson::Document* doc = new rapidjson::Document();
    doc->Parse(file->getBuffer().c_str());
    this->document = new JsonHandle(doc);
}

JsonDocument::JsonDocument(const char* src) {
    rapidjson::Document* doc = new rapidjson::Document();
    doc->Parse(src);
    this->document = new JsonHandle(doc);
}

JsonDocument::~JsonDocument() {
    delete document;
}

JsonValue JsonDocument::get(const char* key) {
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

bool JsonDocument::has(const char* key) { return this->document->doc->HasMember(key); }

bool JsonDocument::isNull(const char* key) { return this->get(key).val->IsNull();}

bool JsonDocument::erase(const char* key) { return this->document->doc->RemoveMember(key); }

void JsonDocument::insertInt(const char* key, int value) {
    rapidjson::Value _key(key, this->document->doc->GetAllocator());
    this->document->doc->AddMember(
        _key,
        value,
        this->document->doc->GetAllocator()
    );
}

void JsonDocument::insertString(const char* key, const char* value) {
    rapidjson::Value _key(key, this->document->doc->GetAllocator());
    rapidjson::Value _value(value, this->document->doc->GetAllocator());

    this->document->doc->AddMember(
        _key,
        _value,
        this->document->doc->GetAllocator()
    );
}

void JsonDocument::insertArray(const char* key) {
    rapidjson::Value _key(key, this->document->doc->GetAllocator());
    rapidjson::Value _value;
    this->document->doc->AddMember(
        _key,
        _value,
        this->document->doc->GetAllocator()
    );
    this->document->doc->FindMember(key)->value.SetArray();
}

void JsonDocument::insertValue(const char* key, JsonValue value) {
    rapidjson::Value _key(key, this->document->doc->GetAllocator());
    this->document->doc->AddMember(
        _key,
        *value.val,
        this->document->doc->GetAllocator()
    );
}

JsonValue JsonDocument::readAsArray(int index) { return JsonValue(&this->document->doc->GetArray()[index], this->document->doc);}


JsonValue JsonDocument::operator[](const char* key) {
    return this->get(key);
}

JsonValue JsonDocument::operator[](int key) {
    return this->readAsArray(key);
}

void JsonDocument::save(File* handle) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    this->document->doc->Accept(writer);

    handle->write(buffer.GetString());
}
