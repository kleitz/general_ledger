/*!
 * \file            delim_file_read.c
 * \brief           Implementation of delimited file reading functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gl_general/gl_general.h"
#include "datastruct/data_structures.h"
#include "delim_file_read.h"

/*!  Maximum size of buffers  */
#define MAX_LINE_SIZE 1024

static ds_record get_next_record(FILE * file, const char delim) {
    ds_str line = ds_str_create("");
    ds_str success;
    success = ds_str_getline(line, MAX_LINE_SIZE, file);
    ds_str_trim_leading(line);

    while ( success &&
            (ds_str_is_empty(line) || ds_str_char_at_index(line, 0) == '#') ) {
        success = ds_str_getline(line, MAX_LINE_SIZE, file);
        ds_str_trim_leading(line);
    }

    ds_record result;
    if ( success ) {
        result = ds_record_tokenize(line, delim);
    }
    else {
        result = NULL;
    }

    ds_str_destroy(line);
    return result;
}

ds_recordset delim_file_read(const char * filename, const char delim) {
    FILE * delim_file = fopen(filename, "r");
    if ( !delim_file ) {
        gl_log_msg("Couldn't open log file '%s'.", filename);
        return NULL;
    }

    ds_record headers = get_next_record(delim_file, delim);
    assert(headers);
    size_t num_fields = ds_record_size(headers);

    ds_record types = get_next_record(delim_file, delim);
    assert(types);
    assert(ds_record_size(headers) == ds_record_size(types));

    ds_recordset set = ds_recordset_create(num_fields);
    assert(set);
    if ( !set ) {
        ds_record_destroy(headers);
        ds_record_destroy(types);
        return NULL;
    }
    ds_recordset_set_headers(set, headers);

    for ( size_t i = 0; i < ds_record_size(types); ++i ) {
        ds_str field = ds_record_get_field(types, i);
        if ( !ds_str_compare_cstr(field, "string") ) {
            ds_recordset_set_type(set, i, DS_FIELD_STRING);
        }
        else if ( !ds_str_compare_cstr(field, "integer") ) {
            ds_recordset_set_type(set, i, DS_FIELD_INT);
        }
        else if ( !ds_str_compare_cstr(field, "double") ) {
            ds_recordset_set_type(set, i, DS_FIELD_DOUBLE);
        }
        else if ( !ds_str_compare_cstr(field, "boolean") ) {
            ds_recordset_set_type(set, i, DS_FIELD_BOOLEAN);
        }
        else {
            ds_recordset_set_type(set, i, DS_FIELD_STRING);
        }
    }

    ds_record_destroy(types);
    ds_record row = NULL;

    while ( (row = get_next_record(delim_file, delim)) ) {
        if ( ds_record_size(row) != num_fields ) {
            ds_recordset_destroy(set);
            return NULL;
        }
        ds_recordset_add_record(set, row);
    }

    fclose(delim_file);
    return set;
}

