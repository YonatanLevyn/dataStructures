#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    strcpy(item->key, key); 
    item->value = value;
    item->next = NULL;
    return item;
}

HashTable *create_table(int size)
{
    // Creates a new HashTable.
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item **)malloc(table->size * sizeof(Ht_item *));

    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL; 
    return table;
}


void ht_insert(HashTable *table, char *key, int value)
{
    int hash_key = hash_function(key);
    Ht_item *current_item = table->items[hash_key];

    if (current_item == NULL)
    {
        current_item->key = malloc(strlen(key)+1);
        strcpy(current_item->key, key); 
        current_item->value = value;
        current_item->next = NULL;
    }
    else{
        Ht_item *item = create_item(key, value);
        while(current_item != NULL)
       {
          current_item = current_item->next;
       }
       current_item = item;
    }
    table->count++;
}

int ht_search(HashTable *table, char *key)
{
    // Searches for the key in the HashTable.
    int hash_key = hash_function(key);
    Ht_item *item = table->items[hash_key];

    // Loop through the list
    while(item != NULL)
        if(strcmp(item->key, key) == 0){
            return item->value;
        }
        item = item->next;
    // Does not exist
    return 0; 
}

void ht_delete(HashTable *table, char *key)
{
    int hash_key = hash_function(key);
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
        free(head->value);
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
    // Update number of elements
    table->count--;
}

void print_search(HashTable *table, char *key)
{
    int val;

    if ((val = ht_search(table, key)) == NULL)
    {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key:%s, Value:%d\n", key, val);
    }
}

void print_table(HashTable *table)
{
    printf("\nHash Table\n-------------------\n");
    printf("%d items in the table");

    for (int i = 0; i < table->size; i++)
    {
        Ht_item *item = table->items[i];
        printf("Hash_key%d:", i);
        while(item)
        {
            printf("Key:%s, Value:%d -> ", i, item->key, item->value);
            item = item->next;
        }
        printf("NULL\n");
    }

    printf("-------------------\n\n");
}

int main()
{
    HashTable *ht = create_table(CAPACITY);
    ht_insert(ht, (char *)"dudu", (int)123);
    ht_insert(ht, (char *)"yosi", (int)213);
    ht_insert(ht, (char *)"itzik", (int)231);
    ht_insert(ht, (char *)"avi", (int)312);
    print_search(ht, (char *)"dudu");
    print_search(ht, (char *)"yosi");
    print_search(ht, (char *)"itzik");
    print_table(ht);
    ht_delete(ht, (char *)"dudu");
    print_table(ht);
    free_table(ht);
    return 0;
}