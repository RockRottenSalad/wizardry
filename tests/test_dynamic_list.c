
#include "../src/wizardry.h"
#include<stdio.h>

typedef struct
{
    size_t x, y, z;
} vec3_t;

void list_test(void)
{
    fprintf(stderr, "\nDYNAMIC LIST TEST\n");
    int* list = list_init(int);

    int test_data[3] = {3, 6, 2};

    list_append(list, test_data[0]);
    list_append(list, test_data[1]);
    list_append(list, test_data[2]);

    if(list_length(list) != 3)
    {
//        fprintf(stderr, "LIST LENGTH ASSERTION FAILED:\nEXPECTED LENGTH == 3, GOT %zu\n", list_length(list));
        list_free(list);
        exit(1);
    }


    for(size_t i = 0; i < list_length(list); i++)
    {
        fprintf(stderr, "%d\n", list[i]);
        assert(list[i] == test_data[i]);
    }

    list_pop(list);
    if(list_length(list) != 2 || list[0] != test_data[0] || list[1] != test_data[1])
    {
 //       fprintf(stderr, "LIST POP FAILED:\nEXPECTED LENGTH == 2\n, GOT %zu", list_length(list));
        list_free(list);
        exit(1);
    }

    for(size_t i = list_length(list); i < 1000; i++)
    {
        list_append(list, (rand() % 1000000));
    }

  //  fprintf(stderr, "LIST LENGTH AFTER RANDOM APPENDING: %zu\n", list_length(list));
    assert(list_length(list) == 1000);
    list_free(list);

    vec3_t a = (vec3_t){.x = 3, .y = 5, .z = 2};
    vec3_t b = (vec3_t){.x = 2, .y = 9, .z = 4};
    vec3_t c = (vec3_t){.x = 9, .y = 1, .z = 69420};

    vec3_t* vec_list = list_init(vec3_t);
    list_append(vec_list, a);
    list_append(vec_list, b);
    list_append(vec_list, c);
/*
    for(size_t i = 0; i < list_length(vec_list); i++)
    {
        fprintf(stderr, "%zu %zu %zu\n", vec_list[i].x, vec_list[i].y, vec_list[i].z);
    }
    */

    // NOTE: vim made me faster by making me lazier
    assert(vec_list[0].x == a.x);
    assert(vec_list[0].y == a.y);
    assert(vec_list[0].z == a.z);
    assert(vec_list[1].x == b.x);
    assert(vec_list[1].y == b.y);
    assert(vec_list[1].z == b.z);
    assert(vec_list[2].x == c.x);
    assert(vec_list[2].y == c.y);
    assert(vec_list[2].z == c.z);

    list_remove_at(vec_list, 1);
    printf("\n"); 

    for(size_t i = 0; i < list_length(vec_list); i++)
        fprintf(stderr, "%zu %zu %zu\n", vec_list[i].x, vec_list[i].y, vec_list[i].z);

    assert(vec_list[0].x == a.x);
    assert(vec_list[0].y == a.y);
    assert(vec_list[0].z == a.z);
    assert(vec_list[1].x == c.x);
    assert(vec_list[1].y == c.y);
    assert(vec_list[1].z == c.z);


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

    assert(list_a[0] == list_a[0]);
    assert(list_a[1] == list_a[1]);
    assert(list_a[2] == list_a[2]);
    
    assert(list_a[3] == list_b[0]);
    assert(list_a[4] == list_b[1]);
    assert(list_a[5] == list_b[2]);


    list_free(list_a);
    list_free(list_b);

}

