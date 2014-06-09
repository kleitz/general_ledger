/*!
 * \file            db_sql.h
 * \brief           Interface to database specific SQL strings.
 * \details         Function implementations are provided by the individual
 * database components.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_SQL_H
#define PG_GENERAL_LEDGER_DATABASE_DB_SQL_H

/*!
 * \brief           Returns the SQL query to create the users table.
 * \returns         The SQL query.
 */
const char * db_create_users_table_sql(void);

/*!
 * \brief           Returns the SQL query to drop the users table.
 * \returns         The SQL query.
 */
const char * db_drop_users_table_sql(void);

/*!
 * \brief           Returns the SQL query to run the "list users" report.
 * \returns         The SQL query.
 */
const char * db_list_users_report_sql(void);

/*!
 * \brief           Returns the SQL query to create the entities table.
 * \returns         The SQL query.
 */
const char * db_create_entities_table_sql(void);

/*!
 * \brief           Returns the SQL query to drop the entities table.
 * \returns         The SQL query.
 */
const char * db_drop_entities_table_sql(void);

/*!
 * \brief           Returns the SQL query to run the "list entities" report.
 * \returns         The SQL query.
 */
const char * db_list_entities_report_sql(void);

/*!
 * \brief           Returns the SQL query to create the journal entries table.
 * \returns         The SQL query.
 */
const char * db_create_jes_table_sql(void);

/*!
 * \brief           Returns the SQL query to drop the journal entries table.
 * \returns         The SQL query.
 */
const char * db_drop_jes_table_sql(void);

/*!
 * \brief           Returns the SQL query to run the "list journal entries"
 * report.
 * \returns         The SQL query.
 */
const char * db_list_jes_report_sql(void);

/*!
 * \brief           Returns the SQL query to create the nominal accounts table.
 * \returns         The SQL query.
 */
const char * db_create_nomaccts_table_sql(void);

/*!
 * \brief           Returns the SQL query to drop the nominal accounts table.
 * \returns         The SQL query.
 */
const char * db_drop_nomaccts_table_sql(void);

/*!
 * \brief           Returns the SQL query to run the "list nominal accounts"
 * report.
 * \returns         The SQL query.
 */
const char * db_list_nomaccts_report_sql(void);

/*!
 * \brief           Returns the SQL query to create the JE lines table.
 * \returns         The SQL query.
 */
const char * db_create_jelines_table_sql(void);

/*!
 * \brief           Returns the SQL query to drop the JE lines table.
 * \returns         The SQL query.
 */
const char * db_drop_jelines_table_sql(void);

/*!
 * \brief           Returns the SQL query to run the "list JE lines"
 * report.
 * \returns         The SQL query.
 */
const char * db_list_jelines_report_sql(void);

/*!
 * \brief           Returns the SQL query to run the "current TB"
 * report.
 * \returns         The SQL query.
 */
const char * db_current_trial_balance_report_sql(void);

/*!
 * \brief           Returns the SQL query to run the "current TB" by entity.
 * report.
 * \returns         The SQL query.
 */
const char * db_current_trial_balance_entity_report_sql(void);

/*!
 * \brief           Returns the SQL query to create the JE sources table.
 * \returns         The SQL query.
 */
const char * db_create_jesrcs_table_sql(void);

/*!
 * \brief           Returns the SQL query to drop the JE sources table.
 * \returns         The SQL query.
 */
const char * db_drop_jesrcs_table_sql(void);

/*!
 * \brief           Returns the SQL query to run the "list JE sources"
 * report.
 * \returns         The SQL query.
 */
const char * db_list_jesrcs_report_sql(void);

/*!
 * \brief           Returns the SQL query to create the standing data table.
 * \returns         The SQL query.
 */
const char * db_create_standingdata_table_sql(void);

/*!
 * \brief           Returns the SQL query to drop the standing data table.
 * \returns         The SQL query.
 */
const char * db_drop_standingdata_table_sql(void);

/*!
 * \brief           Returns the SQL query to run the "show standing data"
 * report.
 * \returns         The SQL query.
 */
const char * db_show_standingdata_report_sql(void);

/*!
 * \brief           Returns the SQL query to create the current TB view.
 * \returns         The SQL query.
 */
const char * db_create_current_trial_balance_view_sql(void);

/*!
 * \brief           Returns the SQL query to drop the current TB view.
 * \returns         The SQL query.
 */
const char * db_drop_current_trial_balance_view_sql(void);

/*!
 * \brief           Returns the SQL query to create the check total view.
 * \returns         The SQL query.
 */
const char * db_create_check_total_view_sql(void);

/*!
 * \brief           Returns the SQL query to drop the check total view.
 * \returns         The SQL query.
 */
const char * db_drop_check_total_view_sql(void);

/*!
 * \brief           Returns the SQL query to run the "check total"
 * report.
 * \returns         The SQL query.
 */
const char * db_check_total_report_sql(void);

/*!
 * \brief           Returns the SQL query to run the "check total" by entity.
 * report.
 * \returns         The SQL query.
 */
const char * db_check_total_entity_report_sql(void);

/*!
 * \brief           Returns the SQL query to create the all JEs view.
 * \returns         The SQL query.
 */
const char * db_create_all_jes_view_sql(void);

/*!
 * \brief           Returns the SQL query to drop the all JEs view.
 * \returns         The SQL query.
 */
const char * db_drop_all_jes_view_sql(void);

/*!
 * \brief           Returns the SQL query to run the "all JEs"
 * report.
 * \returns         The SQL query.
 */
const char * db_all_jes_report_sql(void);

/*!
 * \brief           Returns the SQL query to run the "JE by number"
 * report.
 * \returns         The SQL query.
 */
const char * db_all_jes_number_report_sql(void);

/*!\
 * \brief           Returns the SQL query to get an entity name from its ID.
 * \returns         The SQL query.
 */
const char * db_get_entity_name_from_id_sql(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_SQL_H  */

