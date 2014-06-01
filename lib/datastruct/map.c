/*!
 * \file            map.c
 * \brief           Implementation of map data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


/*!
 * \brief           Enables POSIX library functions
 */

#define _POSIX_C_SOURCE 200809L


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "map.h"

/*!  Structure to hold a key-value pair node  */
struct kv_pair_node {
    char * key;                 /*!<  A pointer to the key          */
    char * value;               /*!<  A pointer to the value        */
    struct kv_pair_node * next; /*!<  A pointer to the next node    */
};

/*!  Structure to hold a hash map  */
struct map {
    struct kv_pair_node ** lists;   /*!<  Pointer to array of lists */
    size_t hash_size;               /*!<  Size of array of lists    */
};

/*!
 * \brief           Calculates a hash of a string.
 * \details         Uses Dan Bernstein's djb2 algorithm.
 * \param str       A pointer to a string
 * \returns         The hash value
 */
static unsigned long djb2hash(const char * str);

/*!
 * \brief           Makes a new key-value pair node.
 * \param key       The key.
 * \param value     The value.
 * \returns         A pointer to the newly-created node.
 */
static struct kv_pair_node *
kv_pair_node_make(const char * key, const char * value);

/*!
 * \brief           Frees a key-value pair node.
 * \param node      A pointer to the node to free.
 * \returns         A pointer to the next node.
 */
static struct kv_pair_node *
kv_pair_node_free(struct kv_pair_node * node);

struct map * map_init(const size_t hash_size) {
    struct map * new_map = malloc(sizeof *new_map);
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

void map_destroy(struct map * map) {
    for ( size_t idx = 0; idx < map->hash_size; ++idx ) {
        struct kv_pair_node * current_node = map->lists[idx];
        while ( current_node ) {
            current_node = kv_pair_node_free(current_node);
        }
    }
    free(map->lists);
    free(map);
}

const char * map_get_value(struct map * map, const char * key) {
    size_t hash_index = djb2hash(key) % map->hash_size;
    struct kv_pair_node * current_node = map->lists[hash_index];

    while ( current_node ) {
        if ( !strcmp(current_node->key, key) ) {
            return current_node->value;
        }
        current_node = current_node->next;
    }

    return NULL;
}

void map_insert(struct map * map, const char * key, const char * value) {
    size_t hash_index = djb2hash(key) % map->hash_size;
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
kv_pair_node_make(const char * key, const char * value) {
    struct kv_pair_node * new_node = malloc(sizeof *new_node);
    if ( !new_node ) {
        fprintf(stderr, "Couldn't allocate memory for map.\n");
        exit(EXIT_SUCCESS);
    }

    new_node->key = strdup(key);
    if ( !new_node->key ) {
        fprintf(stderr, "Couldn't allocate memory for map node key.\n");
        exit(EXIT_SUCCESS);
    }

    new_node->value = strdup(value);
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
    free(node->key);
    free(node->value);
    free(node);

    return next_node;
}

static unsigned long djb2hash(const char * str) {
    unsigned long hash = 5381;
    int c;

    while ( (c = *str++) ) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

void map_print_all(hash_map map, FILE * outfile) {
    int num = 1;
    for ( size_t idx = 0; idx < map->hash_size; ++idx ) {
        struct kv_pair_node * current_node = map->lists[idx];
        while ( current_node ) {
            fprintf(outfile, "%3d (%3zu) - %s : %s\n", num++, idx,
                    current_node->key, current_node->value);
            current_node = current_node->next;
        }
    }
}

