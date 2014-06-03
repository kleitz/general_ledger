/*!
 * \file            ds_vector.c
 * \brief           Implementation of generic doubly-linked vector data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "ds_vector.h"

/*!  Vector data structure  */
struct ds_vector {
    size_t size;                        /*!<  Size of vector                */
    size_t current;                     /*!<  Current position              */
    bool free_on_delete;                /*!<  'Free on delete' flag         */
    void ** data;                       /*!<  Data array                    */
    void (*data_destructor)(void *);    /*!<  Data destructor function      */
};

struct ds_vector * ds_vector_create(const size_t size,
                                    const bool free_on_delete,
                                    void (*destructor)(void *)) {
    struct ds_vector * new_vector = malloc(sizeof *new_vector);
    if ( !new_vector ) {
        return NULL;
    }

    new_vector->data = calloc(size, sizeof *new_vector->data);
    if ( !new_vector->data ) {
        free(new_vector);
        return NULL;
    }

    new_vector->size = size;
    new_vector->free_on_delete = free_on_delete;
    new_vector->data_destructor = destructor ? destructor : free;

    return new_vector;
}

void ds_vector_destroy(struct ds_vector * vector) {
    ds_vector_clear(vector);
    free(vector->data);
    free(vector);
}

void ds_vector_destructor(void * vector) {
    ds_vector_destroy(vector);
}

void ds_vector_clear(struct ds_vector * vector) {
    assert(vector);

    for ( size_t i = 0; i < vector->size; ++i ) {
        vector->data_destructor(vector->data[i]);
        vector->data[i] = NULL;
    }
}

void ds_vector_set(struct ds_vector * vector,
                   const size_t index,
                   void * element) {
    assert(vector);

    if ( index >= vector->size ) {
        assert(false);
    }

    if ( vector->data[index] ) {
        vector->data_destructor(vector->data[index]);
    }

    vector->data[index] = element;
}

void * ds_vector_element(struct ds_vector * vector, const size_t index) {
    assert(vector);

    if ( index >= vector->size ) {
        assert(false);
        return NULL;
    }

    return vector->data[index];
}

size_t ds_vector_size(struct ds_vector * vector) {
    assert(vector);
    return vector->size;
}

void ds_vector_seek_start(struct ds_vector * vector) {
    assert(vector);
    vector->current = 0;
}

void * ds_vector_get_next_data(struct ds_vector * vector) {
    assert(vector);

    if ( vector->current >= vector->size ) {
        return NULL;
    }

    return vector->data[vector->current++];
}

