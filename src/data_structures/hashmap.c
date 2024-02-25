
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

    new_hashmap.hashmap = (hash_pair_t**)malloc(start_size * sizeof(hash_pair_t*));
    new_hashmap.type_size = type_size;
    new_hashmap.size = start_size;

    memset(new_hashmap.hashmap, 0, start_size * sizeof(hash_pair_t*));

    return new_hashmap;
}

void hashmap_add_internal(hashmap_t *hashmap, const char *key, void *data)
{
    size_t index = hash(key) % hashmap->size;
    fprintf(stderr, "index: %zu\n", index);
    size_t key_len = strlen(key);

    hash_pair_t *hash_pair = NULL;

    hash_pair = (hash_pair_t*)malloc( (key_len + 1) + hashmap->type_size + sizeof(hash_pair_t*));
//    hash_pair->key = (char*)malloc(key_len+1 + hashmap->type_size);

    hash_pair->key = (char*)hash_pair;
//    (void)memcpy(hash_pair->key, key, key_len);
    strcpy(hash_pair->key, key);
//    hash_pair->key[key_len] = '\0';
    hash_pair->next = NULL;

    (void)memcpy(hash_pair->data, data, hashmap->type_size);

    if(hashmap->hashmap[index] != NULL)
    {
        hash_pair_t **hash_dest = &hashmap->hashmap[index]->next;
        while(*hash_dest != NULL)
        {
            hash_dest = &(*hash_dest)->next;
        }
        *hash_dest = hash_pair;
    }
    else
        hashmap->hashmap[index] = hash_pair;

}

void hashmap_get_internal(hashmap_t *hashmap, const char *key, void *dest)
{
    size_t index = hash(key) % hashmap->size;

    hash_pair_t* hash_pair = hashmap->hashmap[index];
    if(hash_pair == NULL)
        return;

    (void)memcpy(dest, hash_pair->data, hashmap->type_size);
}

void hashmap_remove(hashmap_t *hashmap, const char *key)
{
    size_t index = hash(key) % hashmap->size;

    hash_pair_t *hash_pair_prev = NULL; 
    hash_pair_t *hash_pair = hashmap->hashmap[index];

    while(strcmp(hash_pair->key, key) != 0 && hash_pair != NULL)
    {
        hash_pair = hash_pair->next;
    }

    if(hash_pair->next != NULL && hash_pair_prev != NULL)
        hash_pair_prev->next = hash_pair->next;

    free(hash_pair);
}

void hashmap_recursive_free_internal(hash_pair_t *ptr)
{
    if(ptr == NULL)
        return;
    else
        hashmap_recursive_free_internal(ptr->next);

    free(ptr);
}

hashmap_t hashmap_free_internal(hashmap_t *hashmap)
{
    hashmap_t null_hashmap = {0};

    // NOTE: maybe split up freeing process to multiple threads? 
    // e.g. 2 threads, 1 starts at 0 and the other starts halfway 
    for(size_t i = 0; i < hashmap->size; i++)
    {
        hashmap_recursive_free_internal(hashmap->hashmap[i]);
    }

    free(hashmap->hashmap);

    return null_hashmap;
}
