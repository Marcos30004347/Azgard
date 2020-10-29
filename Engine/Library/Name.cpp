#include "Name.hpp"

using namespace Azgard;


class HashedItem {
public:
    const char* value;

    HashedItem* next = nullptr;
    HashedItem* previous = nullptr;
    long unsigned int* references = nullptr;
 
    HashedItem(const char* value, long unsigned int* refs): value{value}, references{refs} {}

    HashedItem() {}
};


template<long unsigned int array_size = 1048576>
class StringHashTable {
    SpinLock lock;

    HashedItem** data;
    long unsigned int count = 0;

    friend class Azgard::Name;
public:
    StringHashTable() {
        AZG_DEBUG_SCOPE;
        lock.lock();
        AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Creating hash table of %lu bytes!", sizeof(HashedItem)*array_size);
    
        this->data = AZG_NEW HashedItem*[array_size];

        for(int i=0; i<array_size; i++) {
            this->data[i] = nullptr;
        }

        lock.unlock();
    }

    ~StringHashTable() {
        HashedItem* tmp = nullptr;
        HashedItem* _tmp = nullptr;

        lock.lock();

        for(int i=0; i<array_size; i++) {
            tmp = this->data[i];

            while(tmp) {
                 _tmp = tmp->next;
                delete tmp->references;
                delete tmp;

                tmp = _tmp;
            }
        }

        if(this->data)delete this->data;

        lock.unlock();
    }


    const char* get(Name::HashTableKey ref) noexcept {
        AZG_DEBUG_SCOPE;
        long int pos = ref.index;
        lock.lock();
        HashedItem* tmp = data[ref.hash%array_size];

        while(pos) {
            pos--;
            tmp = tmp->next;
        }
        lock.unlock();

        return tmp->value;
    }


    Azgard::Name::HashTableKey insert(const char* string) noexcept {
        AZG_DEBUG_SCOPE;
        lock.lock();

        long unsigned int seed = Azgard::hashCStr(string);
        count++;

        if(data[seed%array_size]) {
            HashedItem* emplaced = data[seed%array_size];
            AZG_LOG_WARNING(LogChannel::CORE_CHANNEL, "Name HashTable have hash collision of %s with %s!", string, data[seed%array_size]->value);

            HashedItem* tmp = data[seed%array_size];
            long int pos = 0;

            do {

                if(Azgard::cStrCmp(string, tmp->value)) {
                    *tmp->references += 1;
    
                    lock.unlock();

                    Name::HashTableKey key;
                    key.hash = seed;
                    key.index = pos;
                    return key;
                }
                pos++;
                tmp = tmp->next;
            } while(tmp->next);
        
            tmp->next = AZG_NEW HashedItem(string, AZG_NEW unsigned long(1));
            tmp->next->previous = tmp;
            Name::HashTableKey key;

            key.hash = seed;
            key.index = pos;
            lock.unlock();

            return key;

        }
    
    
        data[seed%array_size] = AZG_NEW HashedItem(string,  AZG_NEW unsigned long(1));
    
        Azgard::Name::HashTableKey key;
    
        key.hash = seed;
        key.index = 0;
        lock.unlock();
        return key;
    }

    void reference(Azgard::Name::HashTableKey ref) {
        lock.lock();
        HashedItem* tmp = this->data[ref.hash%array_size];
        long unsigned int index = ref.index;

        while(index > 0) {
            tmp = tmp->next;
            index--;
        }

        *tmp->references += 1;

        lock.unlock();
    }

    void unreference(Azgard::Name::HashTableKey& ref) {
        AZG_DEBUG_SCOPE;
        lock.lock();
        HashedItem* &tmp = this->data[ref.hash%array_size];
        long unsigned int index = ref.index;

        while(index > 0) {
            tmp = tmp->next;
            index--;
        }

        *tmp->references -= 1;
        if(*tmp->references == 0) {
            if(tmp->previous) tmp->previous->next = tmp->next;
            if(tmp->next) tmp->next->previous - tmp->previous;
    
            delete tmp->references;
            delete tmp;
            tmp = nullptr;
        }

        lock.unlock();
    }
};

StringHashTable<>* NameHashTable = nullptr;



Name::Name(const char* const string){
    this->key = NameHashTable->insert(string);
}

Name::Name(const Name& other){
    NameHashTable->reference(other.key);
    this->key = other.key;
}


Name::Name(Name&& other) {
    NameHashTable->reference(other.key);
    this->key = other.key;
}

Name::~Name() {
    NameHashTable->unreference(this->key);
}

const char* Name::value() noexcept {
    return NameHashTable->get(this->key);
}

bool Name::operator == (Name& other) noexcept {
    return (
        (this->key.hash == other.key.hash) && (this->key.index == other.key.index)
    );
}

Name& Name::operator = (const Name& other) noexcept {
    NameHashTable->reference(other.key);
    key = other.key;
    return *this;
}

Name& Name::operator=(Name&& other) noexcept {
    NameHashTable->reference(other.key);
    key = other.key;
    return *this;
}

bool Name::operator == (const char* string) {
    if(this->key.hash != Azgard::hashCStr(string)) {
        return false;
    }

    return Azgard::cStrCmp(this->value(), string);
}

Name::Name(): key{} {

}


void Name::startUpNameHashTable() {
    NameHashTable = AZG_NEW StringHashTable<>();
}


void Name::shutDownNameHashTable() {
    delete NameHashTable;
    NameHashTable = nullptr;
}