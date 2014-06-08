/*!
 * \file            db_jesrcs.h
 * \brief           Interface to journal entry sources functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_JESRCS_H
#define PG_GENERAL_LEDGER_DATABASE_DB_JESRCS_H

#include <stdbool.h>
#include "datastruct/data_structures.h"

/*!
 * \brief           Creates the JE sources table in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_jesrcs_table(void);

/*!
 * \brief           Drops the jesrcs table from the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_jesrcs_table(void);

/*!
 * \brief           Creates a report listing all journal entry sources.
 * \returns         A ds_str containing the report.
 */
ds_str db_list_jesrcs_report(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_JESRCS_H  */

