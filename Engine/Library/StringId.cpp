#include "StringId.hpp"

#include "crc64.h"
#include "crc32.h"

using namespace Azgard;

template<long unsigned int size = 1048576>
class StringHashTable64 {
public:
    const char* data[size];

    const char* get(long unsigned int id) noexcept {
        return data[id%size];
    }

    long unsigned int insert(const char* string, long unsigned int length) noexcept {
        long unsigned int seed = crc64(string, length);
        data[seed%size] = string;
        return seed;
    }
};


template<unsigned int size = 1048576>
class StringHashTable32 {
public:
    const char* data[size];

    const char* get(unsigned int id) noexcept {
        return data[id%size];
    }

    unsigned int insert(const char* string, unsigned int length) noexcept {
        unsigned int seed = crc32(string, length);
        data[seed%size] = string;
        return seed;
    }
};

// Allocating 4.1MB(2^22 bytes) for the hash table
static StringHashTable64<4194304> hash_table;

StringId::StringId(const char* string) {
    this->id = hash_table.insert(string, sizeof(string));
}

StringId::~StringId() {}

const char* StringId::cString() noexcept {
    return hash_table.get(this->id);
}

bool StringId::operator==(StringId& other) noexcept {
    return this->id == other.id;
}

StringId StringId::operator = (const char* string) noexcept {
    return StringId(string);
}