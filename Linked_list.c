#include <stdio.h>
#include <stdlib.h>


typedef struct node {
   int value;
   struct node* next;
}node;

node* head = NULL;

void insert(int value)
{
         node *temp, *ptr;

        /*allocating memmory for the new node*/
        temp = malloc(sizeof(node));
        if(temp == NULL)
        {
                printf("Out of Memory Space\n");
                exit(0);
        }
        temp->value = value;
        temp->next = NULL;
        if(head == NULL)
        {
                head = temp;
                return;
        }
         ptr = head;
         /*loop until reaching the last node*/
          while(ptr->next != NULL)
          {
            ptr = ptr->next;
          }
         /*last node point to the new one*/
         ptr->next = temp;

        
}

int search_by_index(int index)
{
     node *ptr = head;
     while(index > 0 && ptr != NULL)
      { 
         index--;
         ptr = ptr->next ;
      }
     if(ptr == NULL)
         {
            printf("Index not Foundֿֿ\n");
            return 0;
         }
      return ptr->value;
}

/*search for first appearance of element*/
node* search_by_element(int value)
{
   node *ptr = head;
   while (ptr->value != value)
   {
      ptr = ptr->next;
   }
   if (ptr == NULL)
   {
      printf("Element not found");
      return 0;
   }else{
      return ptr;
   }
}

void delete_by_index(int index)
{
        node *tracer, *ptr;
        if(head == NULL)
        {
                printf("The List is Empty\n");
                return 0;
        }else{
                if(index == 0)
                {
                        /*save pointer to be able to deallocate*/
                        ptr = head;
                        head = head->next ;
                        printf("The deleted element is:%d\n", ptr->value);
                        free(ptr);
                }
                else
                {
                        ptr = head;
                        for(int i = 0; i < index; i++) { 
                           tracer = ptr;
                           ptr = ptr->next ;
                                if(ptr == NULL)
                                {
                                    printf("Index not Found\n");
                                    return 0;
                                }
                        }
                        tracer->next = ptr->next;
                        printf("The deleted element is:%d\n", ptr->value );
                        free(ptr);
                }
        }
}

/*deallocating the list*/
node* free_linkedlist(node* head)
{
   if (head == NULL){
      printf("The List is empty\n");
      return 0;
   }
   node* temp = head;
   free(temp);
   return free_linkedlist(head->next);
 
}



