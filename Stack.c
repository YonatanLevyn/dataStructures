#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef enum
{
    STACK_CHAR,
    STACK_INT
}datatype;


typedef struct stack
{
    int type_size;
    size_t size;
    void* data;
    void* top;
}stack;

stack stackCreator(size_t size, datatype type){
    /* Check which datatype we store in order to allocate memory for it*/
    int effectiveSize;
    if (type == STACK_CHAR){
        effectiveSize = sizeof(char);
    } else {
        effectiveSize = sizeof(int);
    }

    /* Creating a stack*/
    stack s = {
        .size = size,
        .type_size = effectiveSize,
        .data = malloc(effectiveSize),
        .top = NULL
    };
    return s;

}
bool isfull(stack *s) {
  if (s->top == (s->size*s->type_size)+s->data){
    return true;
  }else{
    return false;
  }
}

void push(stack* s,void *item){
    if (isfull(s->top)){
        printf("%c\n", "the stack is full!");
    }
    if (s->top == NULL){
        s->top = s->data;
        /*s->data[0] = *item;*/
        memcpy(s->data, item, s->type_size);
    }else{
        s->top += s->type_size;
        memcpy(s->top, item, s->type_size);
    }
}

void show_top(stack* s){
    printf('%c\n',*(s->top));
}

void pop(stack* s){
    memset(s->top, 0, s->type_size);
    s->top -= s->type_size;
    

}


/* free()*/