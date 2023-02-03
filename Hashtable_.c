#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </Users/macbookpro/dataStructures/Linked_list.c>


#define CAPACITY 50000 // Size of the HashTable.

unsigned long hash_function(char *str)
{
    unsigned long i = 0;

    for (int j = 0; str[j]; j++)
        i += str[j];

    return i % CAPACITY;
}

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
    int size;
    int count;
} HashTable;


Ht_item *create_item(char* key,int value)
{
    // Creates a pointer to a new HashTable item.
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    item->key = malloc(strlen(key)+1);
    item->value = malloc(sizeof(value));
    item->next = NULL;
    strcpy(item->key, key); 
    item->value = value;
    return item;
}

HashTable *create_table(int size)
{
    // Creates a new HashTable.
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *));

    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL; /*why set to NULL after calloc*/

    return table;
}


void ht_insert(HashTable *table, char *key, int value)
{
    int hash_key = hash_function(key);
    Ht_item *item = create_item(hash_key, value);
    Ht_item *current_item = table->items[hash_key];

    if (current_item == NULL)
    {
        // Key does not exist.
        if (table->count == table->size) /*so what we can still continue add items*/
        {
            // HashTable is full.
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }

        // Insert directly.
        table->items[hash_key] = item;
        //table->count++;
    }
    else{
        // Handle the collision.
        while(current_item->next != NULL)
        {
            current_item = current_item->next;
        }
        current_item->next = item;
        return;
    }
    table->count++;
    
}

int ht_search(HashTable *table, char *key)
{
    // Searches for the key in the HashTable.
    int hash_key = hash_function(key);
    Ht_item *item = table->items[hash_key];

    // Loop through the list
    while(strcmp(item->key, key) == 0 && item != NULL)
        item = item->next;
    
    if (item == NULL)
    {
        return 0;
    }

    return item->value;
}

void ht_delete(HashTable *table, char *key)
{
    int hash_key = hash_function(key);
    Ht_item *head = table->items[hash_key];

    // Check the head
    if (head == NULL){ printf("Does not exist\n"); return;} /* ata maskim li lihtov caha? */

    if (strcmp(head->key, key) == 0)
    {
        table->items[hash_key] = head->next;
        free(head->key);/*Is it necessary to delete the information?*/
        free(head->value);
        free(head);
        return;
    }
    
    else
    {
        // Search for the key in the list
        // Using two pointers to connect the nodes later
        Ht_item *temp, *curr;
        temp = head;
        curr = head->next;
        while (strcmp(curr->key, key) == 0 && curr != NULL)
        {
            temp = curr;
            curr = curr->next;
        }
        if (curr = NULL)
        {
            printf("Does not exist\n");
            return;
        }
        temp->next = curr->next;

        // Frees an item
        free(curr->key);
        free(curr->value);
        free(curr);

    }
}

void print_search(HashTable *table, char *key)
{
    char *val;

    if ((val = ht_search(table, key)) == NULL)
    {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_table(HashTable *table)
{
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table -> size; i++)
    {
        if (table -> items[i])
        {
            printf("Index:%d, Key:%s, Value:%s\n", i, table -> items[i] -> key, table -> items[i] -> value);
        }
    }

    printf("-------------------\n\n");
}

int main()
{
    HashTable *ht = create_table(CAPACITY);
    ht_insert(ht, (char *)"1", (char *)"First address");
    ht_insert(ht, (char *)"2", (char *)"Second address");
    ht_insert(ht, (char *)"Hel", (char *)"Third address");
    ht_insert(ht, (char *)"Cau", (char *)"Fourth address");
    print_search(ht, (char *)"1");
    print_search(ht, (char *)"2");
    print_search(ht, (char *)"3");
    print_search(ht, (char *)"Hel");
    print_search(ht, (char *)"Cau"); // Collision!
    print_table(ht);
    ht_delete(ht, (char *)"1");
    ht_delete(ht, (char *)"Cau");
    print_table(ht);
    free_table(ht);
    return 0;
}