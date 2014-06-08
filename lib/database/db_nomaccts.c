/*!
 * \file            db_nomaccts.c
 * \brief           Implementation of nominal accounts functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "gl_general/gl_general.h"
#include "db_internal.h"

bool db_create_nomaccts_table(void) {
    gl_log_msg("Creating nomaccts table...");
    bool status = false;
    ds_str query = ds_str_create(db_create_nomaccts_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

bool db_drop_nomaccts_table(void) {
    gl_log_msg("Dropping nomaccts table...");
    bool status = false;
    ds_str query = ds_str_create(db_drop_nomaccts_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

ds_str db_list_nomaccts_report(void) {
    gl_log_msg("Running 'list nominal accounts' report...");
    ds_str report = NULL;
    ds_str query = ds_str_create(db_list_nomaccts_report_sql());
    if ( query ) {
        report = db_create_report_from_query(query);
        ds_str_destroy(query);
    }
    return report;
}

