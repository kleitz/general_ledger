/*!
 * \file            db_entities.h
 * \brief           Interface to entities functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_ENTITIES_H
#define PG_GENERAL_LEDGER_DATABASE_DB_ENTITIES_H

#include <stdbool.h>
#include "datastruct/ds_str.h"

/*!
 * \brief           Creates the entities table in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_entities_table(void);

/*!
 * \brief           Drops the entities table in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_entities_table(void);

/*!
 * \brief           Creates a report listing all entities.
 * \returns         A ds_str containing the report.
 */
ds_str db_list_entities_report(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_ENTITIES_H  */

