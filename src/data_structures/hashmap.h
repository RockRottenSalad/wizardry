#ifndef HASHMAP_H
#define HASHMAP_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define HASHMAP_SIZE 100

size_t hash(const char* key);

struct hash_pair_t 
{
    char *key;
    struct hash_pair_t *next;

    void *data;
};

typedef struct hash_pair_t hash_pair_t;

typedef struct
{
    hash_pair_t **hashmap;
    size_t size, type_size, elements;
} hashmap_t;

#define hashmap_init(TYPE)\
    hashmap_init_internal(sizeof(TYPE), HASHMAP_SIZE)

hashmap_t hashmap_init_internal(size_t type_size, size_t start_size);

#define hashmap_add(HASHMAP, KEY, VALUE)\
do{\
    typeof(VALUE) _VALUE = VALUE;\
    hashmap_add_internal(&HASHMAP, KEY, (void*)(&_VALUE));\
}while(0)

void hashmap_add_internal(hashmap_t *hashmap, const char *key, void *value);

#define hashmap_get(HASHMAP, KEY, DEST)\
    hashmap_get_internal(&HASHMAP, KEY, (void*)DEST)

void hashmap_get_internal(hashmap_t *hashmap, const char *key, void *dest);

void hashmap_remove(hashmap_t *hashmap, const char *key);

void hashmap_recursive_free_internal(hash_pair_t *hashmap);

#define hashmap_free(HASHMAP)\
    HASHMAP = hashmap_free_internal(&HASHMAP);

hashmap_t hashmap_free_internal(hashmap_t *hashmap);

#endif
