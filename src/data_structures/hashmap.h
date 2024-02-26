#ifndef HASHMAP_H
#define HASHMAP_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define HASHMAP_SIZE 100

size_t hash(const char* key);
size_t hash_generic(const char *key, size_t key_size);

#define KEY_OFFSET(HASH_PAIR) (void*)(HASH_PAIR.data) + hashmap->type_size
#define KEY_OFFSET_PTR(HASH_PAIR) (void*)(HASH_PAIR->data) + hashmap->type_size

struct hash_pair_t 
{
    struct hash_pair_t *next;
    size_t key_len;

    void *data;
    //char *key;
};

typedef struct hash_pair_t hash_pair_t;

typedef struct
{
    hash_pair_t *hashmap;
    // key_size here is only used in generic hashmap
    size_t size, key_size, type_size, elements;
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

// GENERIC HASHMAP
#define g_hashmap_init(KEY_TYPE, TYPE)\
    g_hashmap_init_internal(sizeof(KEY_TYPE), sizeof(TYPE), HASHMAP_SIZE)
hashmap_t g_hashmap_init_internal(size_t key_size, size_t type_size, size_t start_size);

#define g_hashmap_add(HASHMAP, KEY, VALUE)\
    do{\
        typeof(KEY) _KEY = KEY;\
        typeof(VALUE) _VALUE = VALUE;\
        g_hashmap_add_internal(&HASHMAP, &_KEY, &_VALUE);\
    }while(0)

void g_hashmap_add_internal(hashmap_t *hashmap, const void *key, const void *value);

#define g_hashmap_get(HASHMAP, KEY, DEST)\
    g_hashmap_get_internal(&HASHMAP, KEY, DEST)

void g_hashmap_get_internal(hashmap_t *hashmap, const void *key, void *dest);

#endif
