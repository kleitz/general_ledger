/*!
 * \file            db_jelines.h
 * \brief           Interface to journal entry lines functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_JELINES_H
#define PG_GENERAL_LEDGER_DATABASE_DB_JELINES_H

#include <stdbool.h>
#include "datastruct/data_structures.h"

/*!
 * \brief           Creates the journal entry lines table in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_jelines_table(void);

/*!
 * \brief           Drops the journal entry lines table from the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_jelines_table(void);

/*!
 * \brief           Creates a report listing all journal entry lines..
 * \returns         A ds_str containing the report.
 */
ds_str db_list_jelines_report(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_JELINES_H  */

