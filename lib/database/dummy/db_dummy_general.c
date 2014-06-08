/*!
 * \file            db_dummy_general.c
 * \brief           Implementation of dummy database functionality.
 * \details         This module is useful when compiling for testing purpose
 * on a system without any of the supported database development libraries
 * available.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

/*!  UNIX feature test macro  */
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "gl_general/gl_general.h"
#include "database/db_internal.h"
#include "datastruct/data_structures.h"

bool db_connect(const char * host, const char * database,
                const char * username, const char * password) {
    gl_log_msg("Dummy connection made.");
    (void)host;
    (void)database;
    (void)username;
    (void)password;
    return true;
}

void db_close(void) {
    gl_log_msg("Dummy connection closed.");
}

bool db_execute_query(ds_str query) {
    gl_log_msg("Dummy query successful");
    (void)query;
    return true;
}

ds_recordset db_create_recordset_from_query(ds_str query) {
    const size_t num_fields = 4;
    const size_t num_rows = 5;
    ds_recordset set = ds_recordset_create(num_fields);

    ds_record field_names = ds_record_create(num_fields);
    for ( size_t i = 0; i < num_fields; ++i ) {
        ds_str field = ds_str_create_sprintf("Header %zu", i+1);
        ds_record_set_field(field_names, i, field);
    }

    ds_recordset_set_headers(set, field_names);

    for ( size_t j = 0; j < num_rows; ++j ) {
        ds_record record = ds_record_create(num_fields);
        for ( size_t i = 0; i < num_fields; ++i ) {
            ds_str data = ds_str_create_sprintf("Dummy data %zu", i+1);
            ds_record_set_field(record, i, data);
        }
        ds_recordset_add_record(set, record);
    }

    (void)query;
    return set;
}

