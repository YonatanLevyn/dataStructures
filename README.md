# dataStructures/Hashtable

This is an implementation of a Hashtable in C
=======================

* Linked-list based chaining for dealing with collisions.
* Simple hash function (more advanced hash functions may be needed for applications with larger data sets)

The implementation includes the following files:

Hashtable.c: contains the main hashtable implementation, including functions for creating and manipulating the hashtable.

hashtable.h: contains the header file for the hashtable implementation, including function prototypes and definitions for the data types used.

The implementation includes the following methods:

* ht_insert: This function inserts a new item with the given key and value into the hash table. 
It calculates the hash value of the key using a hash function, 
which determines the index in the items array to insert the item. 
If a collision occurs, the function creates a linked list of Ht_items at that index. 
If an item with the same key already exists in the hash table, its value is updated. 
The function returns 1 on success and 0 on failure.

* ht_search: This function searches the hash table for an item with the given key and returns its value. 
If the item is not found, it returns -1.

* ht_delete: This function deletes the item with the given key from the hash table. 
If the item is found, it is removed from the table and its memory is freed. 
If the item is not found, the function does nothing.






