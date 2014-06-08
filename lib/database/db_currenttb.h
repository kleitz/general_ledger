/*!
 * \file            db_currenttb.h
 * \brief           Interface to current trial balance functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_CURRENTTB_H
#define PG_GENERAL_LEDGER_DATABASE_DB_CURRENTTB_H

#include <stdbool.h>
#include "datastruct/data_structures.h"

/*!
 * \brief           Creates the current TB view in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_current_trial_balance_view(void);

/*!
 * \brief           Drops the current TB view from the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_current_trial_balance_view(void);

/*!
 * \brief           Runs the current trial balance report.
 * \returns         The report.
 */
ds_str db_current_trial_balance_report(ds_str entity);

/*!
 * \brief           Creates the check total view in the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_create_check_total_view(void);

/*!
 * \brief           Drops the check total view from the database.
 * \returns         `true` on success, `false` on failure.
 */
bool db_drop_check_total_view(void);

/*!
 * \brief           Runs the check total report.
 * \returns         The report.
 */
ds_str db_check_total_report(ds_str entity);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_CURRENTTB_H  */

