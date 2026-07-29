#ifndef LINEAR_PROBED_MAP_HPP
#define LINEAR_PROBED_MAP_HPP

#include <functional>
#include <optional>
#include <vector>
#include "state_node.hpp"


/*
- Template class that defines the structure of the LinearProbedMap datastructure
- Contains:
    - Capacity: The amount of space the map can physically store
    - num_elements: The current number of elements that are inside of the map
    - max_load_factor: Computed as such: (num elements / capacity). If this ratio is >= 0.7 we have to resize the capacity.
*/
template<typename K, typename V> 
class LinearProbedMap {
    // Map attributes
    private:
        std::vector<HashNode<K,V>> table;
        size_t capacity;
        size_t num_elements;
        float max_load_factor;

    public:
        LinearProbedMap(size_t init_capacity = 16, float max_lf = 0.7f)
            // Member variables initialized in memory
            : capacity(init_capacity), num_elements(0), max_load_factor(max_lf)
        {
            // allocates space for 16 hashnode elements inside of the table
            table.resize(capacity);
        }
    
    // Private helper method that computes the index based on the hash function: n%size
    private:
        size_t getIndex(const K& key, size_t cap) const {
            return std::hash<K>{}(key) % cap;
        }

        void resize(size_t new_capacity) {
            // logic to resize the table
        }
    

    public:
        void insert(const K& key, const V& value){
            if((float)(num_elements + 1) / capacity > max_load_factor){
                //resize
                resize(capacity * 2);
            }
            size_t startIndex = getIndex(key, capacity);
            size_t target_index = startIndex;
            int tombstone = -1;
            for(size_t i = 0; i < capacity; ++i) {
                size_t currIndex = (startIndex + i) % capacity;
                // case where state is EMPTY
                if(table[currIndex].state == SlotState::EMPTY){
                    // empty slot found for our data, so we can exit loop
                    target_index = currIndex;
                    break;
                }
                // case where state is OCCUPIED
                if(table[currIndex].state == SlotState::OCCUPIED){
                    // checks if we are updating an existing key in the map, otherwise we continue to next slot
                    if(table[currIndex].key == key){
                        table[currIndex].value = value;
                    }
                }
                // case where state is DELETED
                if(table[currIndex].state == SlotState::DELETED){
                    // finds the first deleted slot so that we can use it to save the key value pair to.
                    if(tombstone == -1){
                        tombstone = currIndex;
                    }
                }
            }

            /*
             When placing the key value pair inside a slot, we first prioritize the tombstone(DELETED) slot before an empty one
            */
            
            // if tombstone was found, then we update the tombstone slot to be the new key value pair
            if(tombstone != -1){
                table[tombstone].key = key;
                table[tombstone].value = value;
                num_elements++;
                table[tombstone].state = SlotState::OCCUPIED;
            
            } // else we just use the empty slot to place our key value pair into
            else{
                table[target_index].key = key;
                table[target_index].value = value;
                num_elements++;
                table[target_index].state = SlotState::OCCUPIED;
            }
            
        }
   
        std::optional<V> get(const K& key) const {
            
        }
    
        bool remove(const K& key) {

        }

};

#endif