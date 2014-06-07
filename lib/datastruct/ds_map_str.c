/*!
 * \file            ds_map_str.c
 * \brief           Implementation of string-string hash map data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

/*!  Structure to hold a key-value pair node  */
struct kv_pair_node {
    ds_str key;                 /*!<  A pointer to the key          */
    ds_str value;               /*!<  A pointer to the value        */
    struct kv_pair_node * next; /*!<  A pointer to the next node    */
};

/*!  Structure to hold a hash map  */
struct ds_map_str {
    struct kv_pair_node ** lists;   /*!<  Pointer to array of lists */
    size_t hash_size;               /*!<  Size of array of lists    */
};

/*!
 * \brief           Makes a new key-value pair node.
 * \param key       The key.
 * \param value     The value.
 * \returns         A pointer to the newly-created node.
 */
static struct kv_pair_node *
kv_pair_node_make(ds_str key, ds_str value);

/*!
 * \brief           Frees a key-value pair node.
 * \param node      A pointer to the node to free.
 * \returns         A pointer to the next node.
 */
static struct kv_pair_node *
kv_pair_node_free(struct kv_pair_node * node);

ds_map_str ds_map_str_init(const size_t hash_size) {
    ds_map_str new_map = malloc(sizeof *new_map);
    if ( !new_map ) {
        fprintf(stderr, "Could't allocate memory for map.\n");
        exit(EXIT_FAILURE);
    }

    new_map->hash_size = hash_size;
    new_map->lists = malloc(hash_size * sizeof *(new_map->lists));
    if ( !new_map->lists ) {
        fprintf(stderr, "Could't allocate memory for map.\n");
        exit(EXIT_FAILURE);
    }
    
    for ( size_t idx = 0; idx < new_map->hash_size; ++idx ) {
        new_map->lists[idx] = NULL;
    }

    return new_map;
}

void ds_map_str_destroy(ds_map_str map) {
    for ( size_t idx = 0; idx < map->hash_size; ++idx ) {
        struct kv_pair_node * current_node = map->lists[idx];
        while ( current_node ) {
            current_node = kv_pair_node_free(current_node);
        }
    }
    free(map->lists);
    free(map);
}

ds_str ds_map_str_get_value(ds_map_str map, ds_str key) {
    size_t hash_index = ds_str_hash(key) % map->hash_size;
    struct kv_pair_node * current_node = map->lists[hash_index];

    while ( current_node ) {
        if ( !ds_str_compare(current_node->key, key) ) {
            return current_node->value;
        }
        current_node = current_node->next;
    }

    return NULL;
}

void ds_map_str_insert(ds_map_str map, ds_str key, ds_str value) {
    size_t hash_index = ds_str_hash(key) % map->hash_size;
    struct kv_pair_node * current_node = map->lists[hash_index];

    if ( !current_node ) {
        map->lists[hash_index] = kv_pair_node_make(key, value);
    }
    else {
        while ( current_node->next ) {
            current_node = current_node->next;
        }
        current_node->next = kv_pair_node_make(key, value);
    }
}

static struct kv_pair_node *
kv_pair_node_make(ds_str key, ds_str value) {
    struct kv_pair_node * new_node = malloc(sizeof *new_node);
    if ( !new_node ) {
        fprintf(stderr, "Couldn't allocate memory for map.\n");
        exit(EXIT_SUCCESS);
    }

    new_node->key = ds_str_dup(key);
    if ( !new_node->key ) {
        fprintf(stderr, "Couldn't allocate memory for map node key.\n");
        exit(EXIT_SUCCESS);
    }

    new_node->value = ds_str_dup(value);
    if ( !new_node->value ) {
        fprintf(stderr, "Couldn't allocate memory for map node value.\n");
        exit(EXIT_SUCCESS);
    }

    new_node->next = NULL;

    return new_node;
}

static struct kv_pair_node *
kv_pair_node_free(struct kv_pair_node * node) {
    if ( !node ) {
        return NULL;
    }

    struct kv_pair_node * next_node = node->next;
    ds_str_destroy(node->key);
    ds_str_destroy(node->value);
    free(node);

    return next_node;
}

