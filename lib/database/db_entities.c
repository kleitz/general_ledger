/*!
 * \file            db_entities.c
 * \brief           Implementation of entities functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

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

