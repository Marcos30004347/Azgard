#ifndef AZGARD_LIB_STRING
#define AZGARD_LIB_STRING

namespace Azgard {

#define STRING_ID_HASHTABLE 1

class StringId {
public:
    const char* cString() noexcept;
    StringId(const char* string);
    ~StringId();

    bool operator == (StringId& other) noexcept;
    StringId operator = (const char* cstring) noexcept;
private:
    long unsigned int id;
};

}

#endif