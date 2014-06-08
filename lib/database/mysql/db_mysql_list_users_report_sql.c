/*!
 * \file            db_mysql_list_users_report_sql.c
 * \brief           Returns MYSQL SQL query to create list users report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_list_users_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  id AS 'User ID',"
        "  user_name AS 'Username',"
        "  first_name AS 'First Name',"
        "  last_name AS 'Last Name',"
        "  CASE enabled"
        "    WHEN TRUE"
        "      THEN 'Yes'"
        "    WHEN FALSE"
        "      THEN 'No'"
        "    ELSE 'Unknown'"
        "  END"
        "    AS 'Enabled?'"
        "  FROM users"
        "  ORDER BY id";
    return query;
}

