/*!
 * \file            db_mysql_current_trial_balance_report_sql.c
 * \brief           Returns MYSQL SQL query to create current TB report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_current_trial_balance_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  a.num AS 'Account',"
        "  a.description AS 'Description',"
        "  sum(l.amount) as 'Balance'"
        "  FROM nomaccts AS a"
        "  LEFT OUTER JOIN jelines AS l"
        "    ON a.num = l.account"
        "  INNER JOIN jes AS j"
        "    ON l.je = j.id"
        "  WHERE j.entity = 1"
        "  GROUP BY a.num";
    return query;
}

