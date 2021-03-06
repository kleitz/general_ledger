/*!
 * \file            db_entities.c
 * \brief           Implementation of entities functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <assert.h>
#include "db_internal.h"
#include "gl_general/gl_general.h"

bool db_create_entities_table(void) {
    gl_log_msg("Creating entities table...");
    bool status = false;
    ds_str query = ds_str_create(db_create_entities_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

bool db_drop_entities_table(void) {
    gl_log_msg("Dropping entities table...");
    bool status = false;
    ds_str query = ds_str_create(db_drop_entities_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

ds_str db_list_entities_report(void) {
    gl_log_msg("Creating 'list entities' report...");
    ds_str report = NULL;
    ds_str query = ds_str_create(db_list_entities_report_sql());
    if ( query ) {
        report = db_create_report_from_query(query);
        ds_str_destroy(query);
    }
    return report;
}

ds_str db_get_entity_name_from_id(ds_str entity_id) {
    const char * cquery = db_get_entity_name_from_id_sql();
    ds_str query = ds_str_create_sprintf(cquery, ds_str_cstr(entity_id));
    ds_recordset set = db_create_recordset_from_query(query);
    ds_str result;

    if ( ds_recordset_num_records(set) == 0 ) {
        result = ds_str_create_sprintf("Unknown entity [%s]",
                ds_str_cstr(entity_id));
    }
    else if ( ds_recordset_num_records(set) == 1 ) {
        ds_recordset_seek_start(set);
        ds_record record = ds_recordset_next_record(set);
        ds_str entity_name = ds_record_get_field(record, 0);
        result = ds_str_create_sprintf("%s [%s]",
                ds_str_cstr(entity_name),
                ds_str_cstr(entity_id));
    }
    else {
        assert(false);
    }

    ds_recordset_destroy(set);
    ds_str_destroy(query);

    return result;
}
