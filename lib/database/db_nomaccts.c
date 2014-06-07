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
    return db_execute_query(db_create_nomaccts_table_sql());
}

bool db_drop_nomaccts_table(void) {
    gl_log_msg("Dropping nomaccts table...");
    return db_execute_query(db_drop_nomaccts_table_sql());
}

ds_str db_list_nomaccts_report(void) {
    gl_log_msg("Running 'list nominal accounts' report...");
    return db_create_report_from_query(db_list_nomaccts_report_sql());
}

