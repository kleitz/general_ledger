/*!
 * \file            db_standingdata.c
 * \brief           Implementation of standing data functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "gl_general/gl_general.h"
#include "db_internal.h"

bool db_create_standingdata_table(void) {
    gl_log_msg("Creating standingdata table...");
    bool status = false;
    ds_str query = ds_str_create(db_create_standingdata_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

bool db_drop_standingdata_table(void) {
    gl_log_msg("Dropping standingdata table...");
    bool status = false;
    ds_str query = ds_str_create(db_drop_standingdata_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

ds_str db_show_standingdata_report(void) {
    gl_log_msg("Running 'show standing data' report...");
    ds_str report = NULL;
    ds_str query = ds_str_create(db_show_standingdata_report_sql());
    if ( query ) {
        report = db_create_report_from_query(query);
        ds_str_destroy(query);
    }
    return report;
}

