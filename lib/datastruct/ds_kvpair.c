/*!
 * \file            ds_kvpair.h
 * \brief           Implementation of string key-value pair data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include "ds_kvpair.h"

/*!  Structure to hold a key-value pair node  */
struct ds_kvpair {
    ds_str key;                 /*!<  The key          */
    ds_str value;               /*!<  The value        */
};

ds_kvpair ds_kvpair_create(ds_str key, ds_str value) {
    ds_kvpair new_pair = malloc(sizeof *new_pair);
    if ( !new_pair ) {
        return NULL;
    }

    new_pair->key = ds_str_dup(key);
    if ( !new_pair->key ) {
        free(new_pair);
        return NULL;
    }

    new_pair->value = ds_str_dup(value);
    if ( !new_pair->value ) {
        ds_str_destroy(new_pair->key);
        free(new_pair);
        return NULL;
    }

    return new_pair;
}

void ds_kvpair_destroy(ds_kvpair pair) {
    if ( pair ) {
        ds_str_destroy(pair->key);
        ds_str_destroy(pair->value);
        free(pair);
    }
}

void ds_kvpair_destructor(void * pair) {
    ds_kvpair_destroy(pair);
}

ds_str ds_kvpair_get_key(ds_kvpair pair) {
    return pair->key;
}

ds_str ds_kvpair_get_value(ds_kvpair pair) {
    return pair->value;
}

