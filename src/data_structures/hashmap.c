
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

hashmap_t hashmap_init_internal(size_t type_size, size_t start_size)
{
    hashmap_t new_hashmap = {0};

    new_hashmap.hashmap = (hash_pair_t*)malloc(start_size * sizeof(hash_pair_t));
    new_hashmap.type_size = type_size;
    new_hashmap.size = start_size;

    memset(new_hashmap.hashmap, 0, start_size * sizeof(hash_pair_t));

    return new_hashmap;
}

void hashmap_add(hashmap_t *hashmap, const char *key, void *data)
{
    size_t index = hash(key) % hashmap->size;
    size_t key_len = strlen(key);

    hash_pair_t *hash_pair = NULL;
    hash_pair_t *empty_pair_slot = NULL;

    hash_pair = (hash_pair_t*)malloc( (key_len + 1) + hashmap->type_size + sizeof(void*));

    hash_pair->key = (char*)hash_pair;
    (void)memcpy(hash_pair->key, key, key_len);
    hash_pair->key[key_len] = '\0';

    hash_pair->next = (hash_pair_t*)(hash_pair->key + key_len + 1);
    (void)memset(hash_pair->next, 0, sizeof(void*));

    hash_pair->data = hash_pair->next + sizeof(void*);
    (void)memcpy(hash_pair->data, data, hashmap->type_size);

    empty_pair_slot = &hashmap->hashmap[index];
    while(empty_pair_slot != NULL)
    {
        empty_pair_slot = empty_pair_slot->next;
    }
    
    (void)memcpy(empty_pair_slot, hash_pair, sizeof(hash_pair_t));
}

void hashmap_remove(hashmap_t *hashmap, const char *key)
{
    size_t index = hash(key) % hashmap->size;
}

void hashmap_recursive_free_internal(hash_pair_t *ptr)
{
    if(ptr == NULL)
        return;
    else
        hashmap_recursive_free_internal(ptr);

    free(ptr);
}

hashmap_t hashmap_free_internal(hashmap_t *hashmap)
{
    hashmap_t null_hashmap = {0};

    // NOTE: maybe split up freeing process to multiple threads? 
    // e.g. 2 threads, 1 starts at 0 and the other starts halfway 
    for(hash_pair_t* ptr = hashmap->hashmap;
        ptr != hashmap->hashmap + hashmap->size;
        ptr += sizeof(hash_pair_t))
    {
        hashmap_recursive_free_internal(ptr);
    }

    free(hashmap->hashmap);

    return null_hashmap;
}
