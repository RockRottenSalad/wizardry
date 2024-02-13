#ifndef WIZARDRY_LINKED_LIST_H
#define WIZARDRY_LINKED_LIST_H

#include<stdlib.h>

 // TODO: Don't malloc each node(too slow)
 // instead, create a "malloc pool", make one fat malloc at a time
 // and hand out chunks to use as nodes. 

struct node_t
{
    void* data;
    struct node_t *next, *prev;
};
typedef struct node_t node_t;

typedef struct
{
    node_t *head, *tail;
    
    // If type_size is set to 0, then this turns into a generic type list
    size_t type_size;
} linked_list_t;

#define linked_init(TYPE)\
    linked_init_internal(sizeof(TYPE))
#define generic_linked_init()\
    linked_init_internal((size_t)0)

linked_list_t linked_init_internal(size_t type_size);

node_t* linked_free_recursive_internal(node_t* node, node_t* end);
void linked_free(linked_list_t *linked_list);

#define linked_push_front(LIST, VALUE)\
{\
    typeof(VALUE) _VALUE = VALUE;\
    linked_push_front_internal(LIST, (void*)(&_VALUE);\
}
void linked_push_front_internal(linked_list_t linked_list, void* data);

#define linked_push_back(LIST, VALUE)\
{\
    typeof(VALUE) _VALUE = VALUE;\
    linked_push_back_internal(LIST, (void*)(&_VALUE);\
}
void linked_push_back_internal(linked_list_t linked_list, void* data);


void linked_pop_front(linked_list_t linked_list);
void linked_pop_back(linked_list_t linked_list);


#endif /* WIZARDRY_LINKED_LIST_H */
