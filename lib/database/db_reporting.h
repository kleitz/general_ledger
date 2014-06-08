/*!
 * \file            db_reporting.h
 * \brief           Interface to database reporting functionality.
 * \details         Function implementations may be provided by the individual
 * database components.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_REPORTING_H
#define PG_GENERAL_LEDGER_DATABASE_DB_REPORTING_H

/*!
 * \brief           Creates a text report from a query.
 * \param query     The SELECT query to run.
 * \returns         A ds_str containing the report, or `NULL` on failure.
 */
ds_str db_create_report_from_query(ds_str query);

/*!
 * \brief           Creates a ds_recordset from a query.
 * \param query     The SELECT query to run.
 * \returns         A ds_recordset containing the query result, or
 * `NULL` on failure.
 */
ds_recordset db_create_recordset_from_query(ds_str query);

/*!
 * \brief           Runs the current trial balance report.
 * \returns         The report.
 */
ds_str db_current_trial_balance_report(ds_str entity);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_REPORTING_H  */

