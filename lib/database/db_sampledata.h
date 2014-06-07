/*!
 * \file            db_sampledata.h
 * \brief           Interface to database sample data functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_SAMPLEDATA_H
#define PG_GENERAL_LEDGER_DATABASE_DB_SAMPLEDATA_H

#include <stdbool.h>

/*!
 * \brief           Loads sample data into the database.
 */
bool db_load_sample_data(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_SAMPLEDATA_H  */

