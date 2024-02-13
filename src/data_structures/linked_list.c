
#include "data_structures/linked_list.h"

linked_list_t linked_init_internal(size_t type_size)
{
    linked_list_t linked_list = {0};
    linked_list.type_size = type_size;
    return linked_list;
}

node_t* linked_free_recursive_internal(node_t* node, node_t* end)
{
    if(node != end)
        linked_free_recursive_internal(node->next, end);
    free(node);
}

void linked_free(linked_list_t *linked_list)
{
    linked_free_recursive_internal(linked_list->head, linked_list->tail);

    linked_list->head = linked_list->tail = linked_list->size = 0;
}
