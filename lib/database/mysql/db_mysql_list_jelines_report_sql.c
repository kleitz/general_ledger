/*!
 * \file            db_mysql_list_jelines_report_sql.c
 * \brief           Returns MYSQL SQL query to create JE lines report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_list_jelines_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  id AS 'ID',"
        "  je AS 'JE',"
        "  account AS 'Account Number',"
        "  amount AS 'Amount'"
        "  FROM jelines"
        "  ORDER BY id";
    return query;
}

