/*!
 * \file            db_mysql_create_check_total_view_sql.c
 * \brief           Returns MYSQL SQL query to create check total view.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_check_total_view_sql(void) {
    static const char * query = 
        "CREATE VIEW check_total AS"
        "  SELECT"
        "    Entity,"
        "    sum(Balance) AS 'Check Total'"
        "    FROM current_trial_balance"
        "    GROUP BY Entity"
        "    ORDER BY Entity ASC";
    return query;
}

