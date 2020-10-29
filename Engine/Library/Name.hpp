#ifndef AZGARD_LIB_NAME
#define AZGARD_LIB_NAME

#include "Core/Engine.hpp"
#include "Library/String.hpp"

namespace Azgard {

class Name {
    class HashTableKey {
    public:
        long unsigned int hash = -1;
        long unsigned int index = -1;
        friend class Name;
    };

    HashTableKey key;

    static void startUpNameHashTable();
    static void shutDownNameHashTable();

    friend class LibraryManager;
public:
    const char* value() noexcept;

    Name();
    Name(const char* const string); // constructor
    Name(const Name& other); // copy constructor
    Name(Name&& other); // move constructor
    ~Name();

    Name& operator = (Name&& other) noexcept; // move assignment
    Name& operator = (const Name& other) noexcept; // copy assignment

    bool operator == (const char* other);
    bool operator == (Name& other) noexcept;
};

}

#endif