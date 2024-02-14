
#include "linked_list.h"

linked_list_t linked_init_internal(size_t type_size)
{
    linked_list_t linked_list = {0};
    linked_list.type_size = type_size;
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
    size_t node_size = NODE_SIZE;
    node_t* new_head = (node_t*)malloc(node_size);

    new_head->prev = NULL;
    new_head->next = linked_list->head;
    new_head->data = new_head + NODE_DATA_OFFSET;

    // TODO: Error handling
    (void)memcpy(new_head->data, data, linked_list->type_size);

    linked_list->head = new_head;
    if(linked_list->tail == NULL)
        linked_list->tail = new_head;
}

void linked_pop_front_internal(linked_list_t* linked_list)
{
    node_t* prev_head = linked_list->head;
    if(linked_list->head->next != NULL)
        linked_list->head->next->prev = NULL;

    linked_list->head = linked_list->head->next;

    free(prev_head);
}

void linked_pop_back_internal(linked_list_t* linked_list)
{
    node_t* prev_tail = linked_list->head;
    if(linked_list->tail->prev != NULL)
        linked_list->tail->prev = NULL;

    linked_list->tail = linked_list->tail->prev;

    free(prev_tail);
}

void linked_get_value_internal(linked_list_t* linked_list, node_t* node, void* dest)
{
    // TODO: check for errors

    (void)memcpy(dest, node->data, linked_list->type_size);
}
