/*!
 * \file            db_mysql_drop_current_trial_balance_view_sql.c
 * \brief           Returns MYSQL SQL query to drop trial balance view.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_drop_current_trial_balance_view_sql(void) {
    static const char * query = 
        "DROP VIEW current_trial_balance";
    return query;
}

