#ifndef HASHMAP_H
#define HASHMAP_H

#include<stdlib.h>
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
    hash_pair_t *hashmap;
    size_t size, type_size, elements;
} hashmap_t;


hashmap_t hashmap_init_internal(size_t type_size, size_t start_size);

void hashmap_add(hashmap_t *hashmap, const char *key, void *data);

void hashmap_remove(hashmap_t *hashmap, const char *key);

void hashmap_recursive_free_internal(hash_pair_t *hashmap);

#define hashmap_free(HASHMAP)\
    HASHMAP = hashmap_free_internal(&HASHMAP);

hashmap_t hashmap_free_internal(hashmap_t *hashmap);

#endif
