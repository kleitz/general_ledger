/*!
 * \file            db_structure.h
 * \brief           Interface to database structure functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_STRUCTURE_H
#define PG_GENERAL_LEDGER_DATABASE_DB_STRUCTURE_H

#include <stdbool.h>

/*!
 * \brief           Creates an empty database structure.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_database_structure(void);

/*!
 * \brief           Deletes the database structure.
 * \returns         `true` on success, `false` on failure.
 */
bool db_delete_database_structure(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_STRUCTURE_H  */

