#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hashtable.h"         

size_t hash_function(char* str)
{
    size_t i = 0;
    for (size_t j = 0; str[j]; j++)
    {
        i += str[j];
    }
    return i % CAPACITY;
}

Ht_item *create_item(char *key,int value)
{
    // Creates a pointer to a new HashTable item.
    Ht_item *item = (Ht_item *)malloc(sizeof(Ht_item));
    CHECK_MAL(item == NULL, NULL, "malloc failed to allocate memory");
    item->key = (char*)malloc(sizeof(key)+1);
    CHECK_MAL(item->key == NULL, NULL, "malloc failed to allocate memory");
    strcpy(item->key, key);
    item->value = value;
    item->next = NULL;
    return item;

}

HashTable *create_table(size_t size)
{
    // Creates a new HashTable.
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    CHECK_MAL(table == NULL, NULL, "malloc failed to allocate memory");
    table->size = size;
    table->count = 0;
    table->items = (Ht_item **)malloc(table->size * sizeof(Ht_item *));
    CHECK_MAL(table->items == NULL, NULL, "malloc failed to allocate memory");
    for (size_t i = 0; i < table->size; i++)
        table->items[i] = NULL; 
    return table;
}

int ht_insert(HashTable *table, char* key, int value)
{
    size_t hash_key = hash_function(key);
    Ht_item *item = table->items[hash_key];
    if (item == NULL)
    {
        table->items[hash_key] = create_item(key, value);
    }
    else
    {
        // Loop while checking that key does not exist
        while (item->next != NULL && strcmp(item->key, key) == 0)
        {
            item = item->next;
        }
        if (strcmp(item->key, key) == 0)
        {
            printf("Key already exist!\n");
            return 0;
        }
    
        item->next = create_item(key, value);
    }
    table->count++;
    printf("%lu elements in the table\n", table->count);
    return 0;
}

int ht_search(HashTable *table, char *key)
{
    // Searches for the key in the HashTable.
    size_t hash_key = hash_function(key);
    Ht_item *item = table->items[hash_key];

    // Loop through the list
    while (item != NULL)
    {
    if (strcmp(item->key, key) == 0)
    {
        return item->value;
    }
    item = item->next;
    }
    // Does not exist
    return 0; 
}

void ht_delete(HashTable *table, char *key)
{
    size_t hash_key = hash_function(key);
    Ht_item *head = table->items[hash_key];

    // Check the head
    if (head == NULL)
    { 
        printf("Does not exist\n");
        return;
    } 
    if (strcmp(head->key, key) == 0)
    {
        table->items[hash_key] = head->next;
        free(head->key);
        free(head);
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
        if (curr == NULL)
        {
            printf("Does not exist\n");
            return;
        }
        temp->next = curr->next;

        // Frees an item
        free(curr->key);
        free(curr);
    }
    // Update number of elements
    table->count--;
}

void print_search(HashTable *table, char *key)
{
    int val;
    if ((val = ht_search(table, key)) == 0)
    {
        printf("Key: %s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key: %s, Value: %d\n", key, val);
    }
}

void print_table(HashTable *table)
{
    printf("\nHash Table\n-------------------\n");
    printf("%lu items in the table \n", table->count);

    for (size_t i = 0; i < table->size; i++)
    {
        Ht_item *item = table->items[i];
        printf("\n");
        printf("Hash_key %lu: ", i);
        while(item)
        {
            printf("Index: %lu, Key: %s, Value: %d -> ", i, item->key, item->value);
            item = item->next;
        }
        printf("NULL");
    }
    printf("\n");
    printf("-------------------\n\n");
}

void free_list(Ht_item *item)
{
    Ht_item *ptr;
    while (item->next != NULL)
    {
        ptr = item->next;
        free(item->key);
        free(item);
        item = ptr;
    }
    free(item->key);
    free(item);
}

void free_table(HashTable *table)
{
    // Frees the table.
    for (size_t i = 0; i < table->size; i++)
    {
        Ht_item *item = table->items[i];
        if (item != NULL)
        {
            free_list(item);
        }
    }
    free(table->items);
    free(table);
}

int main()
{
    HashTable *ht = create_table(CAPACITY);
    ht_insert(ht, "Dudu", 123);
    ht_insert(ht, "Yona", 213);
    ht_insert(ht, "Kobi", 231);
    ht_insert(ht, "Dudu", 312);
    print_search(ht,"Dudu");
    ht_delete(ht, "Dudu");
    print_table(ht);
    free_table(ht);
    return 0;
}
