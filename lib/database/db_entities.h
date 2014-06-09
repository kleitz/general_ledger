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

/*!
 * \brief           Returns an entity name from an ID.
 * \param entity_id The entity ID.
 * \returns         The string, containing an "Unknown entity" string if
 * the ID is not found.
 */
ds_str db_get_entity_name_from_id(ds_str entity_id);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_ENTITIES_H  */

