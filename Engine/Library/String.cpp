/**
 * Todo: There is probably a better implementation of a string class than that. Use one.
 */

#include"String.hpp"
#include "crc64.h"

using namespace Azgard;

String::String(const char* text) {
    AZG_DEBUG_SCOPE

    unsigned int string_len = Azgard::cStrLen(text);

    _data = (char*)Azgard::allocBytes(string_len, __FILE__, __LINE__);

    Azgard::copyBytes((void*)text, _data, string_len);

    _data[string_len] = '\0';

    this->_length = string_len;

}


String::String(char* text, unsigned int size) {
    AZG_DEBUG_SCOPE
    _data = (char*)Azgard::allocBytes(size + 1, __FILE__, __LINE__);
    for(int i=0; i<size; i++) _data[i] = text[i];
    _data[size] = '\0';
    this->_length = size;
}

// String::String(String& other) {
//     AZG_DEBUG_SCOPE
//     this->_data = new char[other.length()];
//     Azgard::copyBytes(other._data, this->_data, other.length());
//     this->_length = other.length();
// }

String::~String() {
    AZG_DEBUG_SCOPE
    if(_data) {
        delete _data;
    }
}

void Azgard::cStrCpy(char* src, char* dest){
    unsigned int s = 0;
    do {
        dest[s] = src[s];
        s++;
    } while(src[s] != '\0');
}


unsigned int Azgard::cStrLen(const char* str) {
    AZG_DEBUG_SCOPE
    unsigned int s = 0;

    while(str[s++] != '\0') {}
    return s - 1;
}

long int Azgard::hashCStr(const char *s) {
    AZG_DEBUG_SCOPE
    return crc64(s, Azgard::cStrLen(s));
}

bool Azgard::cStrCmp(const char* a, const char* b) {
    AZG_DEBUG_SCOPE

    unsigned int s = 0;
    while(a[s] != '\0' && b[s] != '\0') {
        if(a[s] != b[s]) return false;
        s++;
    }

    return true;
}


void computeLPSArray(char* pat, int M, int* lps) { 
    int len = 0; 
  
    lps[0] = 0;
  
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } else { 
            if (len != 0) { 
                len = lps[len - 1]; 
            } else { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 


unsigned int String::match(String pattern, unsigned int text_from) {
    AZG_DEBUG_SCOPE
    int M = pattern.length(); 
    int N = this->length(); 
  
    int lps[M]; 
  
    char* txt = this->_data;
    char* pat = pattern._data;

    computeLPSArray(pat, M, lps); 

    int i = text_from;
    int j = 0;



    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) {
            return i - j;
            // j = lps[j - 1]; 
        }  else if (i < N && pat[j] != txt[i]) { 
            // Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
    return String::noPos();
}



void String::concat(String other) {
    AZG_DEBUG_SCOPE
    char* tmp = this->_data;
    this->_data = new char[this->length() + other.length()];

    Azgard::copyBytes(tmp, this->_data, this->length());
    Azgard::copyBytes(other._data, this->_data + this->length(), other.length());

    this->_length = this->length() + other.length();

    delete tmp;
}

void String::insert(String other, unsigned int where) {
    AZG_DEBUG_SCOPE
    char* tmp = this->_data;

    this->_data = new char[this->length() + other.length()];

    Azgard::copyBytes(tmp, this->_data, where);
    Azgard::copyBytes(other._data, this->_data + where, other.length());
    Azgard::copyBytes(tmp + where, this->_data + where + other.length(), this->length() - where);

    this->_length = this->length() + other.length();
    delete tmp;
}
