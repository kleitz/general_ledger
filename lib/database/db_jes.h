/*!
 * \file            db_jes.h
 * \brief           Interface to journal entries functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_JES_H
#define PG_GENERAL_LEDGER_DATABASE_DB_JES_H

#include <stdbool.h>
#include "datastruct/data_structures.h"

/*!
 * \brief           Creates the journal entries table in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_jes_table(void);

/*!
 * \brief           Drops the jes table from the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_jes_table(void);

/*!
 * \brief           Creates a report listing all journal entries.
 * \returns         A ds_str containing the report.
 */
ds_str db_list_jes_report(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_JES_H  */

