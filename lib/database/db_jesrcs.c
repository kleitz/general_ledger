/*!
 * \file            db_jesrcs.c
 * \brief           Implementation of journal entry sources functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "gl_general/gl_general.h"
#include "db_internal.h"

bool db_create_jesrcs_table(void) {
    gl_log_msg("Creating jesrcs table...");
    bool status = false;
    ds_str query = ds_str_create(db_create_jesrcs_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

bool db_drop_jesrcs_table(void) {
    gl_log_msg("Dropping jesrcs table...");
    bool status = false;
    ds_str query = ds_str_create(db_drop_jesrcs_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

ds_str db_list_jesrcs_report(void) {
    gl_log_msg("Running 'list journal entry sources' report...");
    ds_str report = NULL;
    ds_str query = ds_str_create(db_list_jesrcs_report_sql());
    if ( query ) {
        report = db_create_report_from_query(query);
        ds_str_destroy(query);
    }
    return report;
}

