/*!
 * \file            db_mysql_list_nomaccts_report_sql.c
 * \brief           Returns MYSQL SQL query to create list nominal accounts
 * report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_list_nomaccts_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  num AS 'A/C Number',"
        "  description AS 'Description',"
        "  enabled AS 'Enabled?'"
        "  FROM nomaccts"
        "  ORDER BY num";
    return query;
}

