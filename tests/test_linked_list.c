
#include "../src/wizardry.h"
#include<stdio.h>

void linked_test(void)
{
    fprintf(stderr, "\nLINKED LIST TEST\n");

    linked_list_t linked = linked_init(int);

    //linked_push_front(linked, 5);

    int value = 0;
   // linked_get_value(linked, linked.head, &value);
   // assert(value == 5);

   // linked_pop_front(linked);

    int test_data[4] = {2, 9, 1, 4};
    for(size_t i = 0; i < 4; i++)
        linked_push_front(linked, test_data[i]);

    int index = 3;
    for(node_t* node = linked.head; node !=  NULL; node = node->next)
    {
        linked_get_value(linked, node, &value);
        fprintf(stderr, "expected: %d, got %d\n", test_data[index], value);
//        assert(test_data[index] == value);
        index--;
    }

    linked_pop_front(linked);

    linked_insert_after(linked, linked.head, 60);
    linked_get_value(linked, linked.head->next, &value);
    assert(value == 60);

    linked_free(linked);

    fprintf(stderr, "\nLINKED LIST TEST PASSED\n");
}
