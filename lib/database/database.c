#include <stdlib.h>

#include "gl_general/gl_general.h"
#include "database/database.h"
#include "database/db_users.h"
#include "database/db_entities.h"
#include "delim_file_read/delim_file_read.h"
#include "datastruct/data_structures.h"

int db_create_database_structure(void) {
    int status = db_create_users_table();
    status = db_create_entities_table();
    return status;
}

int db_delete_database_structure(void) {
    int status = db_drop_users_table();
    status = db_drop_entities_table();
    return status;
}

int db_load_sample_data(void) {
    int status = db_add_sample_data("users", "sample_data/users");
    status = db_add_sample_data("entities", "sample_data/entities");
    return status;
}

int db_add_sample_data(const char * table, const char * filename) {
    int ret_val = 0;
    ds_recordset data = delim_file_read(filename);
    ds_recordset_seek_start(data);
    ds_str query;
    while ( (query = ds_recordset_get_next_insert_query(data, table)) ) {
        ret_val = db_execute_query(ds_str_cstr(query));
        ds_str_destroy(query);
        if ( ret_val ) {
            ds_recordset_destroy(data);
            return ret_val;
        }
    }

    ds_recordset_destroy(data);
    return 0;
}

ds_str db_create_report_from_query(const char * query) {
    ds_recordset results = db_create_recordset_from_query(query);
    ds_str report = ds_recordset_get_text_report(results);
    ds_recordset_destroy(results);
    return report;
}

