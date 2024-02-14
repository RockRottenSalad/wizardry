
#include "dynamic_list.h"

void* list_init_internal(size_t type_size, size_t start_length)
{
    list_meta_data_t list_meta_data = {0};
    void *list = NULL;

    list_meta_data.type_size = type_size;
    list_meta_data.capacity = start_length;
    list_meta_data.allocated = (type_size * start_length) + sizeof(list_meta_data_t);
    list_meta_data.ptr = malloc(list_meta_data.allocated);
    
    (void)memcpy(list_meta_data.ptr, &list_meta_data, sizeof(list_meta_data_t));
    list = list_meta_data.ptr + sizeof(list_meta_data_t);

    return list;
}

inline
list_meta_data_t* list_get_meta_data(void* list)
{
    return (list_meta_data_t*)(list - sizeof(list_meta_data_t) );
}

void* list_append_internal(void* list, void* value, size_t elements)
{
    list_meta_data_t *list_meta_data = list_get_meta_data(list);
    void *tmp = NULL;
//    void *list_offset = list, *tmp = NULL;

    if(list_meta_data->length + elements >= list_meta_data->capacity)
    {
        list_meta_data->capacity += elements + LIST_DEFAULT_SIZE;
        list_meta_data->allocated = (list_meta_data->capacity * list_meta_data->type_size) + sizeof(list_meta_data_t);

        // TODO: Check for error(implement once wizardry error system is done)
        tmp = realloc(list_meta_data->ptr, list_meta_data->allocated);
        assert(tmp != NULL);
        list_meta_data = tmp;
        list_meta_data->ptr = tmp;

//        list_offset = list_meta_data->ptr + sizeof(list_meta_data_t);
        list = list_meta_data->ptr + sizeof(list_meta_data_t);
    }

    // TODO: Check for errors
    (void)memcpy(
            list + (list_meta_data->length * list_meta_data->type_size), // Address after last element
            value,
            list_meta_data->type_size * elements
            );
    list_meta_data->length += elements;

    return list;
}

void list_remove_range(void *list, size_t start, size_t end)
{
    list_meta_data_t *list_meta_data = list_get_meta_data(list);
    void *dest = NULL, *src = NULL;

    // Out of bounds
    if(end > list_meta_data->length - 1)
        return;
   
    dest = list + (start * list_meta_data->type_size);
   // src = dest + list_meta_data->type_size;
    src = list + (end * list_meta_data->type_size);
    (void)memmove(dest, src, (end - start) * list_meta_data->type_size); 

    list_meta_data->length -= end - start;
}

void* list_insert_at_internal(void *list, void* value, size_t index)
{
    list_meta_data_t *list_meta_data = list_get_meta_data(list);
    void *dest = NULL, *tmp = NULL;

    // Out of bounds
    if(index > list_meta_data->length - 1)
        return list;
    else if(list_meta_data->length + 1 >= list_meta_data->capacity)
    {
        list_meta_data->capacity += LIST_DEFAULT_SIZE + 1;
        list_meta_data->allocated = (list_meta_data->capacity * list_meta_data->type_size) + sizeof(list_meta_data_t);

        // TODO: Check for error(implement once wizardry error system is done)
        tmp = realloc(list_meta_data->ptr, list_meta_data->allocated);
        assert(tmp != NULL);
        list_meta_data = tmp;
        list_meta_data->ptr = tmp;

        list = list_meta_data->ptr + sizeof(list_meta_data_t);
    }

    dest = list + (list_meta_data->type_size * index);
    (void)memmove(dest + list_meta_data->type_size, dest, list_meta_data->length - index);
    (void)memcpy(dest, value, list_meta_data->type_size);

    return list;
}

void list_clear(void *list)
{
    list_meta_data_t *list_meta_data = list_get_meta_data(list);

    memset(list, 0, (list_meta_data->type_size * list_meta_data->length));
}

void* list_shrink(void *list, size_t new_capacity)
{
    list_meta_data_t *list_meta_data = list_get_meta_data(list);
    void *tmp = NULL;

    // TODO: error out here
    if(new_capacity >= list_meta_data->capacity)
        return list;
    
    list_meta_data->capacity = new_capacity;
    list_meta_data->allocated = (new_capacity * list_meta_data->type_size) 
        + sizeof(list_meta_data_t);
    tmp = realloc(list_meta_data->ptr, list_meta_data->allocated);

    // TODO: error out here
    assert(tmp != NULL);

    list_meta_data = tmp;
    list_meta_data->ptr = tmp;
    list_meta_data->length = (list_meta_data->allocated - sizeof(list_meta_data_t) ) / list_meta_data->type_size;

    tmp += sizeof(list_meta_data_t);
    return tmp;
} 

void list_pop(void *list)
{
    list_meta_data_t *list_meta_data = list_get_meta_data(list);
    if(list_meta_data->length <= 0)
        return;
    list_meta_data->length--;
}

size_t list_length(void *list)
{
    list_meta_data_t *list_meta_data = list_get_meta_data(list);
    return list_meta_data->length;
}

void* list_free_internal(void* list)
{
    list_meta_data_t *list_meta_data = list_get_meta_data(list);
    free(list_meta_data->ptr);

    return NULL;
}
