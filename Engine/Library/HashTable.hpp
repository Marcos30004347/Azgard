#ifndef AZGARD_LIB_HASHTABLE
#define AZGARD_LIB_HASHTABLE

#include "Core/Engine.hpp"
#include "Library/String.hpp"

namespace Azgard {

template<typename T>
class Hashable {
public:
    virtual long unsigned int hash(long unsigned int count) = 0;
    virtual T getHashableObject() = 0;
    virtual bool compare(T other) = 0;
};


template<typename T, long unsigned int array_size = 1048576, unsigned int id = 0>
class HashTable {
    struct Item {
        T value;
        Item* next = nullptr;
        Item(T value): value{value} {}
        Item() {}
    };

    Item** data;
    long unsigned int count = 0;

public:
    HashTable() {
        AZG_DEBUG_SCOPE;
        AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Creating hash table of %lu bytes!", sizeof(T)*array_size);
        this->data = new Item*[array_size];

        for(int i=0; i<array_size; i++) {
            this->data[i] = nullptr;
        }
    }
    ~HashTable() {
        Item* tmp;
        Item* _tmp;
        for(int i=0; i<array_size; i++) {
            while(tmp) {
                _tmp = tmp->next;
                delete tmp;
                tmp = _tmp;
            }
            delete this->data[i];
        }
    }
    class Ref {
        long int list;
        long int position;

        template<typename _T, long unsigned int _array_size, unsigned int _id>
        friend class HashTable;
        Ref(long int list, long int position): list{list}, position{position} {}
    public:
        Ref(): list{-1}, position{-1} {}
        inline long int getHash() {
            return this->list;
        }
        inline bool isSecure() {
            return this->position == 0;
        }
    };

    T& get(Ref& ref) noexcept {
        AZG_DEBUG_SCOPE;
        long int pos = ref.position;
        Item* tmp = data[ref.list];

    
        while(pos) {
            pos--;
            tmp = tmp->next;
        }
        return tmp->value;
    }


    Ref insert(Hashable<T>&& hasher) noexcept {
        AZG_DEBUG_SCOPE;
        
        long int seed = hasher.hash(this->count)%array_size;
    
        count++;

        if(data[seed%array_size]) {
            Item* emplaced = data[seed%array_size];
            AZG_LOG_WARNING(LogChannel::CORE_CHANNEL, "Hash table collision in count %lu", seed);
            
            Item* tmp = data[seed];
            long int pos = 1;


            while(tmp->next) {
                pos++;

                if(hasher.compare(data[seed%array_size]->value)) {
                    return Ref(seed, pos - 1);
                }

                tmp = tmp->next;
            }
        
            tmp->next = new Item(hasher.getHashableObject());

            return Ref(seed, pos);

        }
        data[seed] = new Item(hasher.getHashableObject());
        return Ref(seed, 0);
    }


    void remove(Ref& ref) {
        AZG_DEBUG_SCOPE;

        long int pos = ref.position - 1;
        Item* tmp = data[ref.list];
        if(pos == 0) delete tmp;
        else {
            while(tmp && pos > 0) {
                tmp = tmp->next;
                pos--;
            }
            if(tmp) {
                Item* _tmp = tmp->next;
                tmp->next = tmp->next->next;
                delete _tmp;
            }
        }
    }
};




}

#endif