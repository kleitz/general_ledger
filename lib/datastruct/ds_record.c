/*!
 * \file            ds_record.c
 * \brief           Implementation of record database structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "data_structures.h"

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

void ds_record_set_field(struct ds_record * record,
                         const size_t index,
                         ds_str field) {
    assert(record);

    ds_vector_set(record->fields, index, field);
}

ds_str ds_record_get_field(struct ds_record * record, const size_t index) {
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

ds_record ds_record_tokenize(ds_str str, const char delim) {
    if ( ds_str_is_empty(str) ) {
        return NULL;
    }

    ds_list field_list = ds_list_create(false, NULL);
    
    ds_str src = ds_str_dup(str);
    ds_str left, right;
    do {
        ds_str_split(src, &left, &right, delim);
        ds_list_append(field_list, left);
        ds_str_destroy(src);
        src = right;
    } while ( src );

    ds_record record = ds_record_create(ds_list_length(field_list));
    ds_list_seek_start(field_list);
    ds_str cur_field;
    for ( size_t i = 0; (cur_field = ds_list_get_next_data(field_list)); ++i ) {
        ds_record_set_field(record, i, cur_field);
    }

    ds_list_destroy(field_list);

    return record;
}

ds_str ds_record_make_delim_string(ds_record record, const char delim) {
    ds_str result = ds_str_dup(ds_record_get_field(record, 0));
    ds_str delim_str = ds_str_create_sprintf("%c", delim);
    for ( size_t i = 1; i < ds_record_size(record); ++i ) {
        ds_str_concat(result, delim_str);
        ds_str_concat(result, ds_record_get_field(record, i));
    }
    ds_str_destroy(delim_str);

    return result;
}

ds_str ds_record_make_values_string(ds_record record) {
    ds_str quote_str = ds_str_create("'");
    ds_str delim_str = ds_str_create(",");
    ds_str result = ds_str_decorate(ds_record_get_field(record, 0),
                                    quote_str, NULL);
    for ( size_t i = 1; i < ds_record_size(record); ++i ) {
        ds_str_concat(result, delim_str);
        ds_str quoted_field = ds_str_decorate(ds_record_get_field(record, i),
                                              quote_str, NULL);
        ds_str_concat(result, quoted_field);
        ds_str_destroy(quoted_field);
    }
    ds_str_destroy(delim_str);
    ds_str_destroy(quote_str);

    return result;
}


