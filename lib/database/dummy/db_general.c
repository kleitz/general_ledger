
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gl_general/gl_general.h"
#include "database/database.h"
#include "database/database_sql.h"
#include "datastruct/data_structures.h"

void db_connect(const char * host, const char * database,
                const char * username, const char * password) {
    gl_log_msg("Dummy connection made.");
    (void)host;
    (void)database;
    (void)username;
    (void)password;
}

void db_close(void) {
    gl_log_msg("Dummy connection closed.");
}

int db_execute_query(const char * query) {
    gl_log_msg("Dummy query successful");
    (void)query;
    return 0;
}

ds_result_set db_create_result_set_from_query(const char * query) {
    const size_t num_fields = 4;
    const size_t num_rows = 5;
    ds_result_set result_set = ds_result_set_create(num_fields);

    ds_list field_names = ds_list_create(true, NULL);
    for ( size_t i = 0; i < num_fields; ++i ) {
        char buffer[20];
        sprintf(buffer, "Header %zu", i+1);
        char * f = strdup(buffer);
        if ( !f ) {
            gl_error_quit("Couldn't duplicate string.");
        }
        ds_list_append(field_names, f);
    }

    ds_result_set_set_headers(result_set, field_names);

    for ( size_t j = 0; j < num_rows; ++j ) {
        ds_list record = ds_list_create(true, NULL);
        for ( size_t i = 0; i < num_fields; ++i ) {
            char buffer[20];
            sprintf(buffer, "Dummy data %zu", i+1);
            char * f = strdup(buffer);
            if ( !f ) {
                gl_error_quit("Couldn't duplicate string.");
            }
            ds_list_append(record, f);
        }
        ds_result_set_add_record(result_set, record);
    }
    (void)query;
    return result_set;
}

ds_recordset db_create_recordset_from_query(const char * query) {
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

