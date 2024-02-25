
#include "linked_list.h"

linked_list_t linked_init_internal(size_t type_size)
{
    linked_list_t linked_list = {0};
    linked_list.type_size = type_size;
    linked_list.head = linked_list.tail = NULL;
    return linked_list;
}

void linked_free_recursive_internal(node_t* node, node_t* end)
{
    if(node != end)
        linked_free_recursive_internal(node->next, end);
    free(node);
}

void linked_free_internal(linked_list_t *linked_list)
{
    linked_free_recursive_internal(linked_list->head, linked_list->tail);

    linked_list->head = linked_list->tail = NULL;
    linked_list->type_size = 0;
}

void linked_push_front_internal(linked_list_t* linked_list, void* data)
{
    node_t* new_head = (node_t*)malloc(NODE_SIZE);

    new_head->prev = NULL;
    new_head->next = linked_list->head;
//    new_head->data = new_head + NODE_DATA_OFFSET;

    // TODO: Error handling
    (void)memcpy((void*)(new_head) + NODE_DATA_OFFSET, data, linked_list->type_size);

    if(linked_list->head != NULL)
        linked_list->head->prev = new_head;

    linked_list->head = new_head;
    if(linked_list->tail == NULL)
        linked_list->tail = new_head;
}

// NOTE: assumes list at least has 1 element
void linked_pop_front_internal(linked_list_t* linked_list)
{
    node_t* prev_head = linked_list->head;
    if(linked_list->head->next != NULL)
        linked_list->head->next->prev = NULL;

    if(linked_list->head == linked_list->tail)
        linked_list->tail = NULL;

    linked_list->head = linked_list->head->next;

    free(prev_head);
}

// NOTE: assumes list at least has 1 element
void linked_pop_back_internal(linked_list_t* linked_list)
{
    node_t* prev_tail = linked_list->tail;
    if(linked_list->tail->prev != NULL)
        linked_list->tail->prev = NULL;

    linked_list->tail = linked_list->tail->prev;

    free(prev_tail);
}

void linked_get_value_internal(linked_list_t* linked_list, node_t* node, void* dest)
{
    // TODO: check for errors

    //(void)memcpy(dest, node->data, linked_list->type_size);
    (void)memcpy(dest, (void*)node + NODE_DATA_OFFSET, linked_list->type_size);
}

void linked_get_value_at_internal(linked_list_t* linked_list, size_t index, void* dest)
{
    node_t* node = linked_list->head;
    for(size_t i = 0; i < index; i++)
    {
        node = node->next;
    }
//    (void)memcpy(dest, node->data, linked_list->type_size);
    (void)memcpy(dest, (void*)(node) + NODE_DATA_OFFSET, linked_list->type_size);
}

// Assumes dest isn't NULL, dest->next is allowed to be NULL
void linked_insert_after_internal(linked_list_t* linked_list, node_t* dest, void* data)
{
    node_t* new_node = (node_t*)malloc(NODE_SIZE);
//    new_node->data = new_node + NODE_DATA_OFFSET;
//    (void)memcpy(new_node->data, data, linked_list->type_size);
    (void)memcpy((void*)(new_node) + NODE_DATA_OFFSET, data, linked_list->type_size);

    node_t* tmp = dest->next;
    dest->next = new_node;

    new_node->next = tmp;
    new_node->prev = dest;

    if(tmp != NULL)
        tmp->prev = new_node;
}


