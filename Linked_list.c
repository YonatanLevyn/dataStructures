#include <stdio.h>
#include <stdlib.h>


typedef struct node {
   int value;
   node* next;
}node;

node* start = NULL;

void insert(int value)
{
        node *temp,*ptr;

        /*allocating memmory for the new node*/
        temp = malloc(sizeof(node));
        if(temp == NULL)
        {
                printf("nOut of Memory Space:n");
                exit(0);
        }
        temp->value = value;
        temp->next = NULL;
        if(start == NULL)
        {
                start = temp;
        }
        else
        {
                ptr = start;
                /*loop until reaching the last node*/
                while(ptr->next != NULL)
                {
                        ptr = ptr->next;
                }
                 /*last node point to the new one*/
                ptr->next = temp;
        }
}

int search_by_index(int index)
{
     node *tracer, *ptr;
     for(int i = 0; i < index; i++) { 
         tracer = ptr;
         ptr = ptr->next ;
         if(ptr==NULL)
         {
            printf("nIndex not Found:n");
            return;
         }
      }
      return tracer->value;
}

/*search for first appearance of element*/
node* search_by_element(int value)
{
   node *ptr;
   while (ptr->value != value)
   {
      ptr = ptr->next;
   }
   if (ptr == NULL)
   {
      printf("Element not found");
      return;
   }else{
      
      return ptr;
   }
}

void delete_by_index(int index)
{
        node *tracer, *ptr;
        if(start==NULL)
        {
                printf("nThe List is Empty:n");
                exit(0);
        }else{
                if(index == 0)
                {
                        /*save pointer to be able to free the memory later*/
                        ptr = start;
                        start = start->next ;
                        printf("nThe deleted element is:%dt", ptr->value);
                        free(ptr);
                }
                else
                {
                        ptr = start;
                        for(int i = 0; i < index; i++) { 
                           tracer = ptr;
                           ptr = ptr->next ;
                                if(ptr==NULL)
                                {
                                        printf("nIndex not Found:n");
                                        return;
                                }
                        }
                        tracer->next = ptr->next;
                        printf("nThe deleted element is:%dt", ptr->value );
                        free(ptr);
                }
        }
}