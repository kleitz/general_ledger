/*!
 * \file            ds_record.c
 * \brief           Implementation of record database structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "ds_record.h"
#include "ds_vector.h"
#include "ds_str.h"

/*!  Vector data structure  */
struct ds_record {
    struct ds_vector * fields;          /*!<  Vector of fields  */
};

struct ds_record * ds_record_create(const size_t size) {
    struct ds_record * new_record = malloc(sizeof *new_record);
    if ( !new_record ) {
        return NULL;
    }

    new_record->fields = ds_vector_create(size, true, ds_str_destructor);
    if ( !new_record->fields ) {
        free(new_record);
        return NULL;
    }

    return new_record;
}

void ds_record_destroy(struct ds_record * record) {
    assert(record);

    ds_vector_destroy(record->fields);
    free(record);
}

void ds_record_destructor(void * record) {
    ds_record_destroy(record);
}

void ds_record_clear(struct ds_record * record) {
    assert(record);

    ds_vector_clear(record->fields);
}

void ds_record_set(struct ds_record * record,
                   const size_t index,
                   ds_str field) {
    assert(record);

    ds_vector_set(record->fields, index, field);
}

ds_str ds_record_field(struct ds_record * record, const size_t index) {
    assert(record);

    return ds_vector_element(record->fields, index);
}

size_t ds_record_size(struct ds_record * record) {
    assert(record);

    return ds_vector_size(record->fields);
}

void ds_record_seek_start(struct ds_record * record) {
    assert(record);

    ds_vector_seek_start(record->fields);
}

ds_str ds_record_get_next_data(struct ds_record * record) {
    assert(record);

    return ds_vector_get_next_data(record->fields);
}

