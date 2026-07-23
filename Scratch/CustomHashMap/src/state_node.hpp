// used to prevent multiple inclusions of this header
#ifndef STATE_NODE_HPP
#define STATE_NODE_HPP


/*
- ENUM that keeps track of the state of each slot 
- Used when we are probing for open slots
- Slot states:
    - EMPTY: slot was never occupied
    - OCCUPIED: slot currently occupied 
    - DELETED: slot was previously occupied 
*/

enum class SlotState {
    EMPTY, 
    OCCUPIED, 
    DELETED
};


/*
- Template struct that contains the key-value pair along with the slot status
*/
template<typename K, typename V> struct HashNode {
    K key;
    V value;
    SlotState state = SlotState::EMPTY;
};

#endif