#ifndef WIZARDRY_LINKED_LIST_H
#define WIZARDRY_LINKED_LIST_H

#include<stdlib.h>
#include<string.h>

 // TODO: Don't malloc each node(too slow)
 // instead, create a "malloc pool", make one fat malloc at a time
 // and hand out chunks to use as nodes. 

typedef struct node_t node_t;
// node size =  2 pointers + type_size
// NOTE: Only to be used inside linked_list functions with linked_list pointer
// as a parameter
#define NODE_SIZE\
    (sizeof(node_t*)*2) + linked_list->type_size
#define NODE_DATA_OFFSET\
    (sizeof(node_t*)*2)

// NOTE: Maybe something like this for error handling?
// Could throw this enum into the linked list struct
enum linked_list_error_t {NO_ERROR = 0, INSERTION_ERROR};

// NOTE: Currently ptr to data is accessed by taking 
// the pointer to the node and offseting it by 16 bytes(the size of 2 pointers)
// This is just temporary for now, but it should work just fine
struct node_t
{
    struct node_t *next, *prev;
//    void* data;
};

typedef struct
{
    node_t *head, *tail;
    
    size_t type_size;
} linked_list_t;

#define linked_init(TYPE)\
    linked_init_internal(sizeof(TYPE))
// NOTE: Don't use
#define generic_linked_init()\
    linked_init_internal((size_t)0) 

linked_list_t linked_init_internal(size_t type_size);

#define linked_free(LIST)\
    linked_free_internal(&LIST)

void linked_free_recursive_internal(node_t* node, node_t* end);
void linked_free_internal(linked_list_t *linked_list);

#define linked_push_front(LIST, VALUE)\
do{\
    typeof(VALUE) _VALUE = VALUE;\
    linked_push_front_internal(&LIST, (void*)(&_VALUE));\
}while(0)
void linked_push_front_internal(linked_list_t* linked_list, void* data);

#define linked_push_back(LIST, VALUE)\
do{\
    typeof(VALUE) _VALUE = VALUE;\
    linked_push_back_internal(&LIST, (void*)(&_VALUE));\
}while(0)
void linked_push_back_internal(linked_list_t* linked_list, void* data);

#define linked_pop_front(LIST)\
    linked_pop_front_internal(&LIST)
void linked_pop_front_internal(linked_list_t* linked_list);

#define linked_pop_back(LIST)\
    linked_pop_back_internal(&LIST)
void linked_pop_back_internal(linked_list_t* linked_list);


#define linked_get_value(LIST, NODE, DEST)\
    linked_get_value_internal(&LIST, NODE, (void*)DEST)

void linked_get_value_internal(linked_list_t* linked_list, node_t* node, void* dest);

#define linked_get_value_at(LIST, INDEX, DEST)\
    linked_get_value_at_internal(&LIST, INDEX, (void*)DEST)

void linked_get_value_at_internal(linked_list_t* linked_list, size_t index, void* dest);

#define linked_insert_after(LIST, DEST_NODE, VALUE)\
    do{\
        typeof(VALUE) _VALUE = VALUE;\
        linked_insert_after_internal(&LIST, DEST_NODE, (void*)(&_VALUE));\
    }while(0)

void linked_insert_after_internal(linked_list_t* linked_list, node_t* dest, void* data);

#endif /* WIZARDRY_LINKED_LIST_H */
