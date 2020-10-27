#ifndef AZGARD_LIB_NAME
#define AZGARD_LIB_NAME

#include "Core/Engine.hpp"
#include "Concurrent/ConcurrentHashTable.hpp"

namespace Azgard {

class Name {
    ConcurrentHashTable<const char*>::Ref reference;
    static ConcurrentHashTable<const char*>* NameHashTable;

    static void startUpNameHashTable();
    static void shutDownNameHashTable();

    friend class Engine;
public:
    const char* value() noexcept;


    Name(const char* string);
    ~Name();

    Name& operator = (Name& other) noexcept;
    bool operator == (Name& other) noexcept;
};

}

#endif