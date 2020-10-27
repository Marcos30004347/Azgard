/**
 * Concurrent wrapper above ConcurrentHashTable.
 * 
 * In the future we beybe won more performance by building
 * a native Concurrent Hash Table, in lock free or lock style,
 * but for now thats ok.
 **/

#ifndef AZGARD_LIB_CONCURRENT_HASHTABLE
#define AZGARD_LIB_CONCURRENT_HASHTABLE

#include "Core/Engine.hpp"
#include "Library/String.hpp"
#include "Library/SpinLock.hpp"
#include "Library/HashTable.hpp"

namespace Azgard {

#define AZGARD_HASH_TABLE_REFERENCE_EQUAL_STRINGS


template<typename T, long unsigned int array_size = 1048576, unsigned int id = 0>
class ConcurrentHashTable {
    SpinLock lock;

    struct Item {
        T value;
        Item* next = nullptr;
        Item(T value): value{value} {}
        Item() {}
    };

    Item** data;
    long unsigned int count = 0;

public:
    ConcurrentHashTable() {
        AZG_DEBUG_SCOPE;
        lock.lock();
        AZG_LOG_DEBUG(LogChannel::CORE_CHANNEL, "Creating hash table of %lu bytes!", sizeof(T)*array_size);
        this->data = new Item*[array_size];

        for(int i=0; i<array_size; i++) {
            this->data[i] = nullptr;
        }
        lock.unlock();
    }
    ~ConcurrentHashTable() {
        Item* tmp;
        Item* _tmp;
        lock.lock();

        for(int i=0; i<array_size; i++) {
            while(tmp) {
                _tmp = tmp->next;
                delete tmp;
                tmp = _tmp;
            }
            delete this->data[i];
        }
        lock.unlock();

    }
    class Ref {
        long int list;
        long int position;

        template<typename _T, long unsigned int _array_size, unsigned int _id>
        friend class ConcurrentHashTable;
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
        lock.lock();
        Item* tmp = data[ref.list];

        while(pos) {
            pos--;
            tmp = tmp->next;
        }
        lock.unlock();

        return tmp->value;
    }


    Ref insert(Hashable<T>&& hasher) noexcept {
        AZG_DEBUG_SCOPE;
        lock.lock();
        
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
                    lock.unlock();
                    return Ref(seed, pos - 1);
                }

                tmp = tmp->next;
            }
        
            tmp->next = new Item(hasher.getHashableObject());

            lock.unlock();
            return Ref(seed, pos);

        }
        data[seed] = new Item(hasher.getHashableObject());
        
        lock.unlock();
        return Ref(seed, 0);
    }


    void remove(Ref& ref) {
        AZG_DEBUG_SCOPE;
        lock.lock();

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
        lock.lock();
    }
};





}

#endif