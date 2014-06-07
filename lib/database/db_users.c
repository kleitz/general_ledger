/*!
 * \file            db_users.c
 * \brief           Implementation of users functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "db_internal.h"
#include "gl_general/gl_general.h"

bool db_create_users_table(void) {
    gl_log_msg("Creating users table...");
    return db_execute_query(db_create_users_table_sql());
}

bool db_drop_users_table(void) {
    gl_log_msg("Dropping users table...");
    return db_execute_query(db_drop_users_table_sql());
}

ds_str db_list_users_report(void) {
    gl_log_msg("Creating 'list users' report...");
    return db_create_report_from_query(db_list_users_report_sql());
}

