#include "Name.hpp"
#include <iostream>
using namespace Azgard;


class StringHasher: public Hashable<const char*> {
public:
    const char* string;
    StringHasher(const char* str): string{str} {}

    long unsigned int hash(long unsigned int count) {
        return Azgard::hashCStr(this->string);
    }

    const char* getHashableObject() {
        return string;
    }

    bool compare(const char* other) {
        return Azgard::cStrCmp(this->string, other);
    }

};

ConcurrentHashTable<const char*>* Name::NameHashTable = nullptr;

void Name::startUpNameHashTable() {
    Name::NameHashTable = new ConcurrentHashTable<const char*>();
}
void Name::shutDownNameHashTable() {
    delete Name::NameHashTable;
    Name::NameHashTable = nullptr;
}

Name::Name(const char* string) {
    this->reference = NameHashTable->insert(StringHasher(string));
}

Name::~Name() {
    if(NameHashTable) NameHashTable->remove(this->reference);
}

const char* Name::value() noexcept {
    return NameHashTable->get(this->reference);
}

bool Name::operator == (Name& other) noexcept {
    if(this->reference.isSecure() || other.reference.isSecure()) {
        return this->reference.getHash() == other.reference.getHash();
    } else {
        Azgard::cStrCmp(NameHashTable->get(this->reference), NameHashTable->get(other.reference));
        return true;
    }
}

Name& Name::operator = (Name& other) noexcept {
    reference = Azgard::move(other.reference);
    return *this;
}

Name::Name() {
    reference = NameHashTable->insert(StringHasher(""));
}