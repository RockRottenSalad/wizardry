
#include "../src/wizardry.h"
#include<stdio.h>


void hashmap_test(void)
{
    fprintf(stderr, "\nHASHMAP TEST\n");
    hashmap_t hashmap = hashmap_init(int);

    hashmap_add(hashmap, "apple", 5);
    hashmap_add(hashmap, "cookie", 2);
    hashmap_add(hashmap, "wasd", 40);
    hashmap_add(hashmap, "keyboard", 20);
    hashmap_add(hashmap, "word", 34);
    hashmap_add(hashmap, "i like collisions", 10);
    hashmap_add(hashmap, "actually, i dont", 42);
    hashmap_add(hashmap, "but i'm trying to cause one", 13);
    hashmap_add(hashmap, "for testing obviously", 93);

    int value = 0;

    hashmap_get(hashmap, "apple", &value);
    assert(value == 5);


    fprintf(stderr, "\nHASHMAP TEST PASSED\n");
}

