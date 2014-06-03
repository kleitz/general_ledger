/*!
 * \file            delim_file_read.c
 * \brief           Implementation of delimited file reading functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gl_general/gl_general.h"
#include "stringhelp/string_functions.h"
#include "datastruct/data_structures.h"
#include "delim_file_read.h"

/*!  Maximum size of buffers  */
#define MAX_BUFFER_SIZE 1024

static ds_list delim_file_line_read(FILE * file, const char delim) {
    char buffer[MAX_BUFFER_SIZE];
    if ( !fgets(buffer, MAX_BUFFER_SIZE, file) ) {
        return NULL;
    }

    ds_list list = ds_list_create(true, NULL);
    if ( !list ) {
        return NULL;
    }

    size_t buflen = strlen(buffer);
    if ( buflen && buffer[buflen - 1] == '\n' ) {
        buffer[buflen - 1] = '\0';
    }

    char field[MAX_BUFFER_SIZE] = {0};

    char * buf_ptr = buffer;
    while ( *buf_ptr ) {
        size_t fld_ptr = 0;
        while ( *buf_ptr && *buf_ptr != delim ) {
            field[fld_ptr++] = *buf_ptr++;
        }
        field[fld_ptr] = '\0';
        buf_ptr++;

        char * new_field = strdup(field);
        if ( !new_field ) {
            gl_log_msg("Couldn't allocate memory for field");
            ds_list_destroy(list);
            return NULL;
        }

        ds_list_append(list, new_field);
    }

    return list;
}

ds_result_set delim_file_read(const char * filename) {
    FILE * delim_file = fopen(filename, "r");
    if ( !delim_file ) {
        gl_log_msg("Couldn't open log file '%s'.", filename);
        return NULL;
    }

    ds_list headers = delim_file_line_read(delim_file, ':');
    assert(headers);
    size_t num_fields = ds_list_length(headers);

    ds_result_set set = ds_result_set_create(num_fields);
    if ( !set ) {
        ds_list_destroy(headers);
        return NULL;
    }
    ds_result_set_set_headers(set, headers);

    ds_list row = NULL;

    while ( (row = delim_file_line_read(delim_file, ':')) ) {
        if ( ds_list_length(row) != num_fields ) {
            ds_result_set_destroy(set);
            return NULL;
        }
        ds_result_set_add_record(set, row);
    }

    fclose(delim_file);
    return set;
}

