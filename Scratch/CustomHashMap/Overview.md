# Creating Custom Hashmap using Linear Probing from Scratch

### Open Addresing
- Method for handling collisions when storing keys inside of a Hashtable.
- At any point the size of the table must be greater than or equal to the total number of keys(We can increase table size by copying old data if needed)
- Load factor(number of keys / table_size) should be kept below 0.7


### Concept of Linear Probing
- Hash table is search sequentially that starts from the original locaiton of the hash. If in case the locatiion is already occupied, then we check for the next location.
- Hash function used: ```(n+1)%table_size```


### Hashtable Functions with Linear Probing specifics
- Insert(Key): Maps a key to a value by passing through hash function.
    - Linear Probing: Hash function is applied to the key to generate index. If that slot is occupied, probe till we fi8nd an empty or deleted slot
- Get(Key): Recomputes the hash function on the key to directly jump to the array index and retrieve the paired value. 
    - Linear Probing: Hash function generates the starting index and probing continues until key is found or empty slot is encountered. Returns value if cooresponding key is found.
- Delete(Key): Locates key via the hash function and clears the entry from the bucket.
    - Linear Probing: Instead of just removing an element completely, The slot is marked as deleted using dummy node(k = -1, v = -1), ensuring that when we try to search a key with the same hash as the last item that got deleted, it doesnt say it doesnt exist, and when we want to insert a new item, that slot labeled as deleted can be used to fill in new data.


### Example Usecase
Java code for showcase as I dont know how this would look like in c++.
```Java
LinearProbedMap<Integer, String> map = new LinearProbedMap<>();
map.insert(0, "Value1");
map.insert(1, "Value2");
map.get(1); // will return Value2
map.delete(0); // will remove <0,"Value1"> pair from the table.
```


