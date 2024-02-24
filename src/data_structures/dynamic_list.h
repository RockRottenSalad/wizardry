#ifndef WIZARDRY_DYNAMIC_LIST_H
#define WIZARDRY_DYNAMIC_LIST_H

#include<stdlib.h>
#include<assert.h>
#include<string.h>

// Meta data for dynamic list
// This is written at the very start of the list memory 
// The pointer returned by list_init is offset by the size of the meta data
typedef struct
{
    size_t length;
    size_t type_size;

    size_t allocated; 
    size_t capacity;
    void* ptr;
} list_meta_data_t;


#define LIST_DEFAULT_SIZE 32

// Init a generic dynamic list for a specific type
#define list_init(TYPE)\
    (TYPE*)list_init_internal(sizeof(TYPE), LIST_DEFAULT_SIZE)
#define list_init_length(TYPE, LENGTH)\
    (TYPE*)list_init_internal(sizeof(TYPE), LENGTH)
void* list_init_internal(size_t type_size, size_t start_length);
list_meta_data_t* list_get_meta_data(void* list);

// NOTE: Little hacky, but this is to make rvalue arguments valid
#define list_append(LIST, VALUE)\
do{\
    typeof(VALUE) _VALUE = VALUE;\
    LIST = (typeof(LIST))list_append_internal(LIST, (void*)(&_VALUE), 1);\
}while(0)
#define list_append_list(DEST, SRC)\
    DEST = (typeof(DEST))list_append_internal(DEST, (void*)SRC, list_length(SRC))
#define list_nappend_list(DEST, SRC, LEN)\
    DEST = (typeof(DEST))list_append_internal(DEST, (void*)SRC, LEN)
void* list_append_internal(void* list, void* value, size_t elements);

#define list_remove_at(LIST, INDEX)\
    list_remove_range(LIST, INDEX, INDEX+1)

// Deletes from start to end-1.
// e.g. start = 0, end = 1 will only remove the element at index 0
void list_remove_range(void *list, size_t start, size_t end);

#define list_insert_at(LIST, VALUE, INDEX)\
do{\
    typeof(VALUE) _VALUE = VALUE;\
    LIST = (typeof(LIST))list_insert_at_internal(LIST, (void*)(&_VALUE), INDEX);\
}while(0)
void* list_insert_at_internal(void *list, void* value, size_t index);

//void list_insert_at(void *dest, void *src, size_t elements);
void list_insert_list_at(void *dest, void *src, size_t elements);

// NOTE: untested 
void list_clear(void *list);

// NOTE: untested 
#define list_trim(LIST)\
    LIST = (typeof(LIST))list_shrink(LIST, list_length(LIST));

// NOTE: untested 
void* list_shrink(void *list, size_t new_capacity);

// NOTE: untested
// ALSO, consider using this to grow list in the insert/append functions
// Instead of making a shrink and grow function
// write a "resize" function which takes a bool as an arugment.
// The bool determines where to grow or shrink, make some defines
// like #define GROW true, etc
void* list_grow(void *list, size_t new_capacity);

void list_pop(void* list);

size_t list_length(void* list);

// Returns NULL to override the pointer and prevent accidental reuse of freed list
#define list_free(LIST)\
    LIST = list_free_internal(LIST);
void* list_free_internal(void* list);

#endif /* WIZARDRY_DYNAMIC_LIST_H */
