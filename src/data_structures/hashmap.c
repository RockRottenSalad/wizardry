
#include "hashmap.h"

size_t hash(const char *key)
{
    size_t index = 0;
    index = 2 * key[0] * key[0];

    for(size_t i = 0; i < strlen(key); i++)
    {
        index *= key[i] + (key[i]*2+1);
    }

    index *= index;

    return index;
}

size_t hash_generic(const char *key, size_t key_size)
{
    size_t index = 0;
    for(size_t i = 0; i < key_size; i++)
    {
        index *= key[i] + (key[i] * 2 + 1);
    }
    index *= index;
    return index;
}

// STRING-KEY HASHMAP
hashmap_t hashmap_init_internal(size_t type_size, size_t start_size)
{
    hashmap_t new_hashmap = {0};

    new_hashmap.hashmap = (hash_pair_t*)malloc(start_size * sizeof(hash_pair_t));
    if(new_hashmap.hashmap == NULL)
        return new_hashmap;

    new_hashmap.type_size = type_size;
    new_hashmap.size = start_size;

    memset(new_hashmap.hashmap, 0, start_size * sizeof(hash_pair_t));

    return new_hashmap;
}

void hashmap_add_internal(hashmap_t *hashmap, const char *key, void *data)
{
    size_t index = hash(key) % hashmap->size;
    fprintf(stderr, "index: %zu, key: %s, value: %d\n", index, key, *(int*)data);
    size_t key_len = strlen(key);

    hash_pair_t hash_pair = {0}, *iterator = &hashmap->hashmap[index], *prev = NULL;

    hash_pair.next = NULL;
    hash_pair.key_len = key_len;

    hash_pair.data = malloc(hashmap->type_size + key_len + 1);
    if(hash_pair.data == NULL)
        return;

    (void)memcpy(hash_pair.data, data, hashmap->type_size);
    (void)strcpy(KEY_OFFSET(hash_pair), key);

    // Collision
    if(iterator->key_len != 0)
    {
        fprintf(stderr, "add: handling collision\n");
        do{
            prev = iterator;
            iterator = iterator->next;
        }while(iterator != NULL);

        prev->next = (hash_pair_t*)malloc(sizeof(hash_pair_t));
        iterator = prev->next;
    }

    (void)memcpy(iterator, &hash_pair, sizeof(hash_pair_t));
    
}

void hashmap_get_internal(hashmap_t *hashmap, const char *key, void *dest)
{
    size_t index = hash(key) % hashmap->size;

    hash_pair_t *hash_pair = &hashmap->hashmap[index], *prev = NULL;
    if(hash_pair->key_len == 0)
        return;

    while(strcmp(KEY_OFFSET_PTR(hash_pair), key) != 0)
    {
        fprintf(stderr, "get: handling collision\n");
        if(hash_pair == NULL) // TODO: handle error
            return;
        prev = hash_pair;
        hash_pair = hash_pair->next;
    }

    (void)memcpy(dest, hash_pair->data, hashmap->type_size);
}

void hashmap_remove(hashmap_t *hashmap, const char *key)
{
    size_t index = hash(key) % hashmap->size;

    //hash_pair_t *hash_pair_prev = NULL; 
    hash_pair_t *hash_pair = &hashmap->hashmap[index], *prev = NULL;

    while(strcmp(KEY_OFFSET_PTR(hash_pair), key) != 0)
    {
        if(hash_pair == NULL) // TODO: handle error
            return;
        prev = hash_pair;
        hash_pair = hash_pair->next;
    }

    free(hash_pair->data);

    if(&hashmap->hashmap[index] != hash_pair)
    {
        free(hash_pair);
        prev->next = NULL;
    }
    else if(hash_pair->next != NULL)
        (void)memmove(hash_pair, hash_pair->next, sizeof(hash_pair_t));
    else
        memset(hash_pair, 0, sizeof(hash_pair_t));

}

void hashmap_recursive_free_internal(hash_pair_t *ptr)
{
    if(ptr == NULL)
        return;
    else
        hashmap_recursive_free_internal(ptr->next);

    free(ptr->data);
}

hashmap_t hashmap_free_internal(hashmap_t *hashmap)
{
    hashmap_t null_hashmap = {0};

    // NOTE: maybe split up freeing process to multiple threads? 
    // e.g. 2 threads, 1 starts at 0 and the other starts halfway 
    for(size_t i = 0; i < hashmap->size; i++)
    {
        hashmap_recursive_free_internal(&hashmap->hashmap[i]);
    }

    free(hashmap->hashmap);

    // prevent accidental reuse of free'ed hashmap
    return null_hashmap;
}

// GENERIC-HASHMAP

hashmap_t g_hashmap_init_internal(size_t key_size, size_t type_size, size_t start_size)
{
    hashmap_t new_hashmap = {0};
    new_hashmap.hashmap = (hash_pair_t*)malloc(sizeof(hash_pair_t) * start_size);

    if(new_hashmap.hashmap == NULL)
        return new_hashmap;

    memset(new_hashmap.hashmap, 0, sizeof(hash_pair_t) * start_size);

    new_hashmap.key_size = key_size;
    new_hashmap.type_size = type_size;

    return new_hashmap;
}

void g_hashmap_add_internal(hashmap_t *hashmap, const void *key, const void *value)
{
    size_t index = hash_generic(key, hashmap->key_size) % hashmap->size;
    hash_pair_t hash_pair = {0};

    hash_pair.next = NULL;
    hash_pair.key_len = hashmap->key_size;

    hash_pair.data = malloc(hashmap->key_size + hashmap->type_size);
    if(hash_pair.data == NULL)
        return; 
    (void)memcpy(hash_pair.data, value, hashmap->type_size);
    (void)memcpy(KEY_OFFSET(hash_pair), key, hashmap->key_size);

    hashmap->hashmap[index] = hash_pair;

}

void g_hashmap_get_internal(hashmap_t *hashmap, const void *key, void *dest)
{
    size_t index = hash_generic(key, hashmap->key_size) % hashmap->size;
    hash_pair_t *hash_pair = NULL;

    hash_pair = &hashmap->hashmap[index];
    (void)memcpy(dest, hash_pair->data, hashmap->type_size);
}


