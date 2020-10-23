#ifndef AZGARD_LIB_STRING
#define AZGARD_LIB_STRING

#include <ostream>

namespace Azgard {

class String {
private:
    char* data;

public:
    String(const char* text);
    String(char* text, unsigned int length);
    ~String();
    const char* cString();

    friend std::ostream& operator<<(std::ostream& os, const String& dt) {
        os << dt.data;
        return os;
    }
};

}


#endif