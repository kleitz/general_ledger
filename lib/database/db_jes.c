/*!
 * \file            db_jes.c
 * \brief           Implementation of journal entries functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "gl_general/gl_general.h"
#include "db_internal.h"

bool db_create_jes_table(void) {
    gl_log_msg("Creating jes table...");
    bool status = false;
    ds_str query = ds_str_create(db_create_jes_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

bool db_drop_jes_table(void) {
    gl_log_msg("Dropping jes table...");
    bool status = false;
    ds_str query = ds_str_create(db_drop_jes_table_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

ds_str db_list_jes_report(void) {
    gl_log_msg("Running 'list journal entries' report...");
    ds_str report = NULL;
    ds_str query = ds_str_create(db_list_jes_report_sql());
    if ( query ) {
        report = db_create_report_from_query(query);
        ds_str_destroy(query);
    }
    return report;
}

bool db_create_all_jes_view(void) {
    gl_log_msg("Creating all JEs view...");
    bool status = false;
    ds_str query = ds_str_create(db_create_all_jes_view_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

bool db_drop_all_jes_view(void) {
    gl_log_msg("Dropping all JEs view...");
    bool status = false;
    ds_str query = ds_str_create(db_drop_all_jes_view_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

ds_str db_all_jes_report(ds_str je_num) {
    gl_log_msg("Running 'All JEs' report...");
    ds_str report = NULL;
    ds_str query;
    
    if ( je_num ) {
        const char * cquery = db_all_jes_number_report_sql();
        query = ds_str_create_sprintf(cquery, ds_str_cstr(je_num));
    }
    else {
        query = ds_str_create(db_all_jes_report_sql());
    }

    if ( query ) {
        report = db_create_report_from_query(query);
        ds_str_destroy(query);
    }
    return report;
}

