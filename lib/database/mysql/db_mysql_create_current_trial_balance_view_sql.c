/*!
 * \file            db_mysql_create_current_trial_balance_view_sql.c
 * \brief           Returns MYSQL SQL query to create trial balance view.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_current_trial_balance_view_sql(void) {
    static const char * query = 
        "CREATE VIEW current_trial_balance AS"
        "  SELECT"
        "    j.entity AS 'Entity',"
        "    a.description AS 'Description',"
        "    sum(l.amount) as 'Balance'"
        "    FROM nomaccts AS a"
        "    LEFT OUTER JOIN jelines AS l"
        "      ON a.num = l.account"
        "    INNER JOIN jes AS j"
        "      ON l.je = j.id"
        "    GROUP BY j.entity, a.num"
        "    ORDER BY j.entity ASC, l.account ASC";
    return query;
}

