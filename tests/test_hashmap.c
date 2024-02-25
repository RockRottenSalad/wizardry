
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
//    hashmap_add(hashmap, "actually, i dont", 42);
//    hashmap_add(hashmap, "but i'm trying to cause one", 13);
//    hashmap_add(hashmap, "for testing obviously", 93);

    int value = 0;

    hashmap_get(hashmap, "apple", &value);
    assert(value == 5);

    hashmap_get(hashmap, "cookie", &value);
    assert(value == 2);

    hashmap_get(hashmap, "wasd", &value);
    assert(value == 40);

    hashmap_get(hashmap, "keyboard", &value);
    assert(value == 20);

    hashmap_get(hashmap, "word", &value);
    assert(value == 34);

    hashmap_get(hashmap, "i like collisions", &value);
    assert(value == 10);

    hashmap_remove(&hashmap, "wasd");

    hashmap_get(hashmap, "i like collisions", &value);
    assert(value == 10);

    hashmap_free(hashmap);

    fprintf(stderr, "\nHASHMAP TEST PASSED\n");
}

