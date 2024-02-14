
#include"src/wizardry.h" 
#include<stdio.h>
#include<time.h>

typedef struct
{
    size_t x, y, z;
} vec3_t;

int main(void)
{
    srand(time(NULL));
    printf("WIZARDRY TEST\n");
    int* list = list_init(int);

    list_append(list, 3);
    list_append(list, 6);
    list_append(list, 2);

    if(list_length(list) != 3)
    {
        fprintf(stderr, "LIST LENGTH ASSERTION FAILED:\nEXPECTED LENGTH == 3, GOT %zu\n", list_length(list));
        list_free(list);
        exit(1);
    }


    for(size_t i = 0; i < list_length(list); i++)
        fprintf(stderr, "%d\n", list[i]);

    if(list[0] != 3 || list[1] != 6 || list[2] != 2)
    {
        fprintf(stderr, "LIST VALUE ASSERTION FAILD:\nEXPECTED: 3 6 2\n");
        list_free(list);
        exit(1);
    }

    list_pop(list);
    if(list_length(list) != 2)
    {
        fprintf(stderr, "LIST POP FAILED:\nEXPECTED LENGTH == 2\n, GOT %zu", list_length(list));
        list_free(list);
        exit(1);
    }

    for(size_t i = list_length(list); i < 1000; i++)
    {
        list_append(list, (rand() % 1000000));
    }

    fprintf(stderr, "LIST LENGTH AFTER RANDOM APPENDING: %zu\n", list_length(list));
    list_free(list);

    vec3_t a = (vec3_t){.x = 3, .y = 5, .z = 2};
    vec3_t b = (vec3_t){.x = 2, .y = 9, .z = 4};
    vec3_t c = (vec3_t){.x = 9, .y = 1, .z = 69420};

    vec3_t* vec_list = list_init(vec3_t);
    list_append(vec_list, a);
    list_append(vec_list, b);
    list_append(vec_list, c);

    for(size_t i = 0; i < list_length(vec_list); i++)
        fprintf(stderr, "%zu %zu %zu\n", vec_list[i].x, vec_list[i].y, vec_list[i].z);

    list_remove_at(vec_list, 1);
    printf("\n"); 

    for(size_t i = 0; i < list_length(vec_list); i++)
        fprintf(stderr, "%zu %zu %zu\n", vec_list[i].x, vec_list[i].y, vec_list[i].z);


    vec3_t d = vec_list[list_length(vec_list)-1];
    if(d.x != c.x || d.y != c.y || d.z != c.z )
    {
        fprintf(stderr, "LIST VALUE REMOVE AT FAILED:\nEXPECTED: %zu %zu %zu GOT: %zu %zu %zu", c.x, c.y, c.z, d.x, d.y, d.z);
        list_free(vec_list);
        exit(1);
    }

    list_free(vec_list);

    fprintf(stderr, "\nLIST APPEND TEST\n");

    int* list_a = list_init(int);
    int* list_b = list_init(int);

    list_append(list_a, 1);
    list_append(list_a, 2);
    list_append(list_a, 3);

    list_append(list_b, 4);
    list_append(list_b, 5);
    list_append(list_b, 6);

    list_append_list(list_a, list_b);

    for(size_t i = 0; i < list_length(list_a); i++)
        fprintf(stderr, "%d ", list_a[i]);

    fprintf(stderr, "\nLIST INSERT AT TEST:\n");
    list_insert_at(list_a, -30, 1);
    for(size_t i = 0; i < list_length(list_a); i++)
        fprintf(stderr, "%d ", list_a[i]);

    list_free(list_a);
    list_free(list_b);

    fprintf(stderr, "\nLINKED LIST TEST\n");

    linked_list_t linked = linked_init(int);

    linked_push_front(linked, 5);

    int value = 0;
    linked_get_value(linked, linked.head, &value);
    fprintf(stderr, "%d\n", value);
    if(value != 5)
    {
        fprintf(stderr, "LINKED LIST FAILED:\nEXPECTED 5, GOT %d", value);
        linked_free(linked);
        exit(1);
    }

    fprintf(stderr, "\n");
    linked_push_front(linked, 2);
    linked_push_front(linked, 9);
    linked_push_front(linked, 1);
    linked_push_front(linked, 4);

    for(node_t* i = linked.head; i != NULL; i = i->next)
    {
        linked_get_value(linked, i, &value);
        fprintf(stderr, "%d ", value);
    }
    fprintf(stderr, "\n");

    linked_pop_front(linked);

    for(node_t* i = linked.head; i != NULL; i = i->next)
    {
        linked_get_value(linked, i, &value);
        fprintf(stderr, "%d ", value);
    }

    linked_free(linked);
    

    fprintf(stderr, "\nTEST PASSED\n");
    return 0;
}

