/*!
 * \file            db_jelines.c
 * \brief           Implementation of journal entries functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "gl_general/gl_general.h"
#include "db_internal.h"

bool db_create_jelines_table(void) {
    gl_log_msg("Creating jelines table...");
    return db_execute_query(db_create_jelines_table_sql());
}

bool db_drop_jelines_table(void) {
    gl_log_msg("Dropping jelines table...");
    return db_execute_query(db_drop_jelines_table_sql());
}

ds_str db_list_jelines_report(void) {
    gl_log_msg("Running 'list journal entry lines' report...");
    return db_create_report_from_query(db_list_jelines_report_sql());
}

