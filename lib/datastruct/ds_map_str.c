/*!
 * \file            ds_map_str.c
 * \brief           Implementation of string-string hash map data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data_structures.h"

/*!  Structure to hold a hash map  */
struct ds_map_str {
    ds_list * lists;                /*!<  Array of lists */
    size_t hash_size;               /*!<  Size of array of lists    */
};

ds_map_str ds_map_str_init(const size_t hash_size) {
    ds_map_str new_map = malloc(sizeof *new_map);
    if ( !new_map ) {
        return NULL;
    }

    new_map->hash_size = hash_size;
    new_map->lists = malloc(hash_size * sizeof *(new_map->lists));
    if ( !new_map->lists ) {
        free(new_map);
        return NULL;
    }
    
    for ( size_t idx = 0; idx < new_map->hash_size; ++idx ) {
        new_map->lists[idx] = ds_list_create(true, ds_kvpair_destructor);
        if ( !new_map->lists[idx] ) {
            for ( size_t j = 0; j < idx; ++j ) {
                ds_list_destroy(new_map->lists[j]);
            }
            free(new_map->lists);
            free(new_map);
            return NULL;
        }
    }

    return new_map;
}

void ds_map_str_destroy(ds_map_str map) {
    for ( size_t idx = 0; idx < map->hash_size; ++idx ) {
        ds_list_destroy(map->lists[idx]);
    }
    free(map->lists);
    free(map);
}

ds_str ds_map_str_get_value(ds_map_str map, ds_str key) {
    size_t hash_index = ds_str_hash(key) % map->hash_size;

    ds_list list = map->lists[hash_index];
    ds_kvpair pair;
    for ( ds_list_seek_start(list);
          (pair = ds_list_get_next_data(list));
        ) {
        ds_str test_key = ds_kvpair_get_key(pair);
        if ( !ds_str_compare(test_key, key) ) {
            return ds_kvpair_get_value(pair);
        }
    }

    return NULL;
}

void ds_map_str_insert(ds_map_str map, ds_str key, ds_str value) {
    size_t hash_index = ds_str_hash(key) % map->hash_size;
    ds_kvpair new_pair = ds_kvpair_create(key, value);
    assert(new_pair);
    ds_list_append(map->lists[hash_index], new_pair);
}

