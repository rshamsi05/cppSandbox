#ifndef LINEAR_PROBED_MAP_HPP
#define LINEAR_PROBED_MAP_HPP

#include <functional>
#include <optional>
#include <vector>
#include <stdexcept>
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
        explicit LinearProbedMap(size_t init_capacity = 16, float max_lf = 0.7f)
            // Member variables initialized in memory
            : capacity(init_capacity), num_elements(0), max_load_factor(max_lf)
        {
            // allocates space for 16 hashnode elements inside of the table
            table.resize(capacity);
        }
    
    private:
        // Private helper method that computes the index based on the hash function: n%size
        size_t getIndex(const K& key, size_t cap) const {
            return std::hash<K>{}(key) % cap;
        }
        // Private helper method that resizes the current table to be 2*capacity
        void resize(size_t new_capacity) {
            // create new table with bigger capacity and resets the values of capacity and num_elements.
            std::vector<HashNode<K,V>> new_table = std::vector<HashNode<K,V>>(new_capacity);
            capacity = new_capacity;
            num_elements = 0;
            // transfer data over
            for(const auto& node: table){
                if(node.state == SlotState::OCCUPIED){
                    size_t startIndex = getIndex(node.key, new_capacity);

                    // Linearly probe
                    for(size_t i = 0; i < new_capacity; ++i){
                        size_t currIndex = (startIndex + i)%new_capacity;
                        if(new_table[currIndex].state == SlotState::EMPTY){
                            new_table[currIndex].key = node.key;
                            new_table[currIndex].value = node.value;
                            new_table[currIndex].state = SlotState::OCCUPIED;
                            num_elements++;
                            break;
                        }
                    }
                }
            }
            table = std::move(new_table);
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
                        return; // we can return out of the function after we simply update the value
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
            // get index of the key
            size_t startIndex = getIndex(key, capacity);
            // probe for space with the same key
            for(size_t i = 0; i < capacity; ++i){
                size_t currIndex = (startIndex+i)%capacity;
                // if the slot where we lookup the key is empty, the key does not exist in the map and we must return an exception.
                if(table[currIndex].state == SlotState::EMPTY){
                    throw std::out_of_range("Key does not exist in the hashmap!");
                }
                // if the state of the slot is deleted, then we skip it
                if(table[currIndex].state == SlotState::DELETED){
                    continue;
                }
                // if the state of the slot is occupied and the keys match, we found the value we want to return.
                if(table[currIndex].state == SlotState::OCCUPIED && table[currIndex].key == key){
                    return table[currIndex].value;
                }
            }
            // if loop exits, key was not found in map and we throw an out of range exception.
            throw std::out_of_range("Key does not exist in the hashmap!");

        }
    
        bool remove(const K& key) {
            size_t startIndex = getIndex(key, capacity);
            for(size_t i = 0; i < capacity; ++i){
                size_t currIndex = (startIndex+i)%capacity;
                // if the slot where we lookup the key is empty, the key does not exist in the map and we must return false.
                if(table[currIndex].state == SlotState::EMPTY){
                    return false;
                }
                if(table[currIndex].state == SlotState::OCCUPIED && table[currIndex].key == key){
                    table[currIndex].state = SlotState::DELETED;
                    num_elements--;
                    return true;
                }
            }
            return false;
        }

};

#endif