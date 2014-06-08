/*!
 * \file            db_standingdata.h
 * \brief           Interface to journal entries functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_STANDINGDATA_H
#define PG_GENERAL_LEDGER_DATABASE_DB_STANDINGDATA_H

#include <stdbool.h>
#include "datastruct/data_structures.h"

/*!
 * \brief           Creates the standing data table in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_standingdata_table(void);

/*!
 * \brief           Drops the standingdata table from the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_standingdata_table(void);

/*!
 * \brief           Creates a report showing standing data.
 * \returns         A ds_str containing the report.
 */
ds_str db_show_standingdata_report(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_STANDINGDATA_H  */

