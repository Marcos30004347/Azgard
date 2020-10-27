#ifndef AZGARD_LIB_STRING
#define AZGARD_LIB_STRING

#include "Core/Engine.hpp"

namespace Azgard {

unsigned int cStrLen(const char* str);
bool cStrCmp(const char* a, const char* b);
long int hashCStr(const char *s);

class String {
private:
    char* _data = nullptr;
    unsigned int _length = 0;

public:
    // String(String& other);
    String(const char* text);
    String(char* text, unsigned int length);

    ~String();

    void concat(String other);
    void insert(String other, unsigned int where);
    unsigned int match(String pattern, unsigned int from = 0);
    
    inline const char* cString() { return (const char*)_data; }
    inline unsigned int length() { return this->_length; }
    static inline unsigned int noPos() { return -1; } 

    char operator[](int index) {
        return _data[index];
    }

};

}


#endif