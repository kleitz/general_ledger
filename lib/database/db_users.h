/*!
 * \file            db_users.h
 * \brief           Interface to users functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_USERS_H
#define PG_GENERAL_LEDGER_DATABASE_DB_USERS_H

#include <stdbool.h>
#include "datastruct/data_structures.h"

/*!
 * \brief           Creates the users table in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_users_table(void);

/*!
 * \brief           Drops the users table from the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_users_table(void);

/*!
 * \brief           Creates a report listing all users.
 * \returns         A ds_str containing the report.
 */
ds_str db_list_users_report(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_USERS_H  */

