#ifndef LINEAR_PROBED_MAP_HPP
#define LINEAR_PROBED_MAP_HPP

#include <functional>
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
    
    // Private helper method that computes the hashcode for the key
    private:
        size_t getIndex(const K& key, size_t cap) const {
            return std::hash<K>{}(key) % cap;
        }

};

#endif