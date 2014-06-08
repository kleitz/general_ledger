/*!
 * \file            db_mysql_current_trial_balance_entity_report_sql.c
 * \brief           Returns MYSQL SQL query to create current TB by entity
 * report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_current_trial_balance_entity_report_sql(void) {
    static const char * query = 
        "SELECT * FROM current_trial_balance"
        "  WHERE Entity = %s";
    return query;
}

