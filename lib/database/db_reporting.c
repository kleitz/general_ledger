/*!
 * \file            db_reporting.c
 * \brief           Implementation of database reporting functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "db_internal.h"
#include "gl_general/gl_general.h"

ds_str db_create_report_from_query(const char * query) {
    ds_recordset results = db_create_recordset_from_query(query);
    ds_str report = ds_recordset_get_text_report(results);
    ds_recordset_destroy(results);
    return report;
}

ds_str db_current_trial_balance_report(void) {
    gl_log_msg("Creating 'current trial balance' report...");
    return db_create_report_from_query(db_current_trial_balance_report_sql());
}

