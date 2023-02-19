#define CAPACITY 100 // Size of the HashTable.
#define CHECK_MAL(__cond__, __ret__, __fmt__, args...)     \
    do{                                                    \
        if(__cond__)                                       \
        {                                                  \
            printf(__fmt__"\n", ##args);                   \
            return __ret__;                                \
        }                                                  \
    } while(0)

// Defines the HashTable item.
typedef struct Ht_item
{
    char* key;
    int value;
    struct Ht_item* next;
} Ht_item;

// Defines the HashTable
typedef struct HashTable
{
    // Contains an array of pointers to items.
    Ht_item **items;
    size_t size;
    size_t count;
} HashTable;

HashTable *create_table(size_t size);
int ht_insert(HashTable *table, char* key, int value);
int ht_search(HashTable *table, char *key);
void ht_delete(HashTable *table, char *key);