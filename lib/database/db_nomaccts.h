/*!
 * \file            db_nomaccts.h
 * \brief           Interface to nominal accounts functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_NOMACCTS_H
#define PG_GENERAL_LEDGER_DATABASE_DB_NOMACCTS_H

#include <stdbool.h>
#include "datastruct/data_structures.h"

/*!
 * \brief           Creates the nominal accounts table in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_nomaccts_table(void);

/*!
 * \brief           Drops the nomaccts table from the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_nomaccts_table(void);

/*!
 * \brief           Creates a report listing all nominal accounts.
 * \returns         A ds_str containing the report.
 */
ds_str db_list_nomaccts_report(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_NOMACCTS_H  */

