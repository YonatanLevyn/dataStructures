/**
 * @file Hashtable.c
 *
 * @brief This code is a C implementation of a hash table data structure
 *
 * @author Yonatan Levy Nahum
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Defining the maximum capacity of the hash table as CAPACITY, which is set to 100.
 */
#define CAPACITY 100 

/**
 * A macro function CHECK_MAL is defined to check for memory allocation errors. 
 * If the condition cond evaluates to true, the macro prints an error message 
 * to the console using the given format string fmt and optional arguments. 
 * It then returns the value ret.
*/
#define CHECK_MAL(__cond__, __ret__, __fmt__, args...)     \
    do{                                                    \
        if(__cond__)                                       \
        {                                                  \
            printf(__fmt__"\n", ##args);                   \
            return __ret__;                                \
        }                                                  \
    } while(0)

/**
 * Ht_item is a structure that represents an item stored in the hash table
 * It contains a pointer to a character array representing the key,
 * an integer value, and a pointer to the next Ht_item in the case of collision
*/
typedef struct Ht_item
{
    char* key;
    int value;
    struct Ht_item* next;
} Ht_item;

/**
 * HashTable is a structure that represents the hash table
 * It contains an array of Ht_item pointers named items, 
 * which represents the table itself, as well as two size_t
 * variables: size, representing the size of the table, and count,  
 * representing the number of items currently stored in the table
*/
typedef struct HashTable
{
    Ht_item **items;
    size_t size;
    size_t count;
} HashTable;


/**
 * @brief Inserts the key, value pair into the hash table.
 * after the insertion prints the number of elements in the table
 * or a failed message if the key already exist
 * @param table A pointer to the hash table.
 * @param key A pointer to the key.
 * @param value An integer value.
 * @returns 1 for success and 0 if the key already exit 
 */
int ht_insert(HashTable *table, char* key, int value);

/**
 * @brief Search for the item in the table.
 * @param table A pointer to the hash table.
 * @param key A pointer to the key.
 * @returns The requested value. If the return value
 * is 0, the requested key-value pair was not in the table.
 */
int ht_search(HashTable *table, char *key);

/**
 * 
 * @brief Removes the item corresponding to the specified key from the hash table.
 * @param table A pointer to the hash table.
 * @param key A pointer to the key.
 */
void ht_delete(HashTable *table, char *key);