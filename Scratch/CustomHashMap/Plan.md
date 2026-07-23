# Linear Probed Custom Hash Map Implementation Plan

This document outlines the refined step-by-step implementation plan for building a custom template Hash Map using **Open Addressing with Linear Probing** in C++.

---

## 🔍 Key C++ Design Considerations & Potential Pitfalls

Before implementing, keep these critical C++ concepts and edge cases in mind:

1. **Handling Missing Keys (`get` return type)**
   - Unlike Java, which can return `null` for missing keys, C++ types might not be nullable or default-constructible.
   - **Recommended Approach**: Return `std::optional<V>` (requires `<optional>`, C++17) or a pointer `const V*` (`nullptr` if not found). Returning `std::optional<V>` is clean, explicit, and modern.

2. **Two-Pass vs. Smart Single-Pass Insertion**
   - **Pitfall**: Inserting directly into the first tombstone (`DELETED` slot) without completing the probe chain can lead to **duplicate keys** if the key already exists further down the probe chain.
   - **Refined Logic**: When inserting:
     1. Probe through the chain to check if the key *already exists* in an `OCCUPIED` slot. If found, update its value and stop.
     2. Keep track of the *first* `DELETED` slot seen along the search path.
     3. If the key is not found in the chain, place the new entry into that first `DELETED` slot (or the `EMPTY` slot where the search terminated).

3. **Table Capacity & Minimum Size**
   - Initial capacity must be $> 0$ (e.g., `8` or `16`) to prevent modulo-by-zero (`key_hash % capacity`) errors.
   - Minimum capacity guarantees open slots when load factor $< 0.7$, preventing infinite probe loops.

4. **Memory Management (`std::vector` vs. Raw Pointers)**
   - Using `std::vector<HashNode<K, V>>` allows C++ to handle dynamic memory allocation, copy constructors, move operations, and destructors automatically (Rule of 0).
   - If using a raw dynamic array (`HashNode<K, V>*`), you must explicitly implement the **Rule of 5** (Destructor, Copy Constructor, Copy Assignment, Move Constructor, Move Assignment).

---

## 🏗️ Step-by-Step Implementation Roadmap

### Step 1: Define Bucket State & Node Structure
- Create an `enum class SlotState`:
  - `EMPTY`: Slot was never used.
  - `OCCUPIED`: Slot currently holds a valid key-value pair.
  - `DELETED`: Slot previously held a key, now acts as a tombstone.
- Create a `HashNode<K, V>` template struct:
  - `K key`
  - `V value`
  - `SlotState state = SlotState::EMPTY`

### Step 2: Define Map Class & Data Members
- Declare template class `LinearProbedMap<typename K, typename V>`:
  - `std::vector<HashNode<K, V>> table`
  - `size_t capacity` (initial default = `16`)
  - `size_t num_elements` (count of `OCCUPIED` slots)
  - `float max_load_factor` (default = `0.7f`)

### Step 3: Hash Calculation Helper
- Private helper function `size_t getIndex(const K& key, size_t cap) const`:
  - Compute `std::hash<K>{}(key) % cap`.

### Step 4: Core Operations Implementation

#### 1. `insert(const K& key, const V& value)`
1. Check load factor: `if ((float)(num_elements + 1) / capacity > max_load_factor) rehash(capacity * 2);`
2. Start probing at `index = getIndex(key, capacity)`.
3. Loop through indices `(index + i) % capacity`:
   - If slot is `OCCUPIED` and `slot.key == key` $\rightarrow$ update value, return.
   - If slot is `DELETED` and no target index saved yet $\rightarrow$ record this slot as the first available tombstone.
   - If slot is `EMPTY` $\rightarrow$ search ends.
4. Place key-value into target slot (first `DELETED` slot if found, else the `EMPTY` slot), set state to `OCCUPIED`, increment `num_elements`.

#### 2. `get(const K& key) -> std::optional<V>` (or `const V*`)
1. Start probing at `index = getIndex(key, capacity)`.
2. Loop `(index + i) % capacity`:
   - If slot is `OCCUPIED` and `slot.key == key` $\rightarrow$ return `slot.value`.
   - If slot is `EMPTY` $\rightarrow$ break search chain, return `std::nullopt` (or `nullptr`).
   - If slot is `DELETED` $\rightarrow$ continue probing.

#### 3. `remove(const K& key) -> bool`
1. Start probing at `index = getIndex(key, capacity)`.
2. Loop `(index + i) % capacity`:
   - If slot is `OCCUPIED` and `slot.key == key` $\rightarrow$ set state to `SlotState::DELETED`, decrement `num_elements`, return `true`.
   - If slot is `EMPTY` $\rightarrow$ key not found, return `false`.
   - If slot is `DELETED` $\rightarrow$ continue probing.

### Step 5: Dynamic Rehashing & Capacity Management
- `rehash(size_t new_capacity)`:
  1. Allocate new table of size `new_capacity`.
  2. Reset `num_elements = 0`.
  3. Loop through old table slots:
     - If slot is `OCCUPIED`, insert its key and value into the new table. (Ignore `DELETED` slots).
  4. Swap old table with new table and update `capacity`.

---

## 🧪 Testing & Verification Checklist (`main.cpp`)

- [ ] **Basic Operations**: Verify `insert`, `get`, and `remove` with `int` keys and `std::string` values.
- [ ] **Collision Probe Verification**: Insert keys that resolve to the same initial index and check lookups.
- [ ] **Tombstone Continuity**: Insert Key A and Key B (colliding), remove Key A, and ensure `get(Key B)` still succeeds past the deleted slot.
- [ ] **Tombstone Reuse**: Remove Key A, insert Key C, verify Key C reuses Key A's deleted slot.
- [ ] **Rehashing**: Insert elements past load factor 0.7, confirm table capacity doubles and all elements are retrievable.
- [ ] **Missing Key Lookup**: Verify searching for non-existent keys correctly returns empty result without crashing or infinite loop.
