/*!
 * \file            db_currenttb.c
 * \brief           Implementation of current TB functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "gl_general/gl_general.h"
#include "db_internal.h"

bool db_create_current_trial_balance_view(void) {
    gl_log_msg("Creating current trial balance view...");
    bool status = false;
    ds_str query = ds_str_create(db_create_current_trial_balance_view_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

bool db_drop_current_trial_balance_view(void) {
    gl_log_msg("Dropping current trial balance view...");
    bool status = false;
    ds_str query = ds_str_create(db_drop_current_trial_balance_view_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

ds_str db_current_trial_balance_report(ds_str entity) {
    gl_log_msg("Creating 'current trial balance' report...");
    ds_str query;
    if ( entity ) {
        const char * cquery = db_current_trial_balance_entity_report_sql();
        query = ds_str_create_sprintf(cquery, ds_str_cstr(entity));
    }
    else {
        const char * cquery = db_current_trial_balance_report_sql();
        query = ds_str_create(cquery);
    }
    ds_str report = db_create_report_from_query(query);
    ds_str_destroy(query);
    return report;
}

bool db_create_check_total_view(void) {
    gl_log_msg("Creating check total view...");
    bool status = false;
    ds_str query = ds_str_create(db_create_check_total_view_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

bool db_drop_check_total_view(void) {
    gl_log_msg("Dropping check total view...");
    bool status = false;
    ds_str query = ds_str_create(db_drop_check_total_view_sql());
    if ( query ) {
        status = db_execute_query(query);
        ds_str_destroy(query);
    }
    return status;
}

ds_str db_check_total_report(ds_str entity) {
    gl_log_msg("Creating 'check total' report...");
    ds_str query;
    if ( entity ) {
        const char * cquery = db_check_total_entity_report_sql();
        query = ds_str_create_sprintf(cquery, ds_str_cstr(entity));
    }
    else {
        const char * cquery = db_check_total_report_sql();
        query = ds_str_create(cquery);
    }
    ds_str report = db_create_report_from_query(query);
    ds_str_destroy(query);
    return report;
}

