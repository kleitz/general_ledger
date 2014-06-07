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
    return db_execute_query(db_create_entities_table_sql());
}

bool db_drop_entities_table(void) {
    gl_log_msg("Dropping entities table...");
    return db_execute_query(db_drop_entities_table_sql());
}

ds_str db_list_entities_report(void) {
    gl_log_msg("Creating 'list entities' report...");
    return db_create_report_from_query(db_list_entities_report_sql());
}

