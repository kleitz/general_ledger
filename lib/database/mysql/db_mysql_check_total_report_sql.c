/*!
 * \file            db_mysql_check_total_report_sql.c
 * \brief           Returns MYSQL SQL query to create check total report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_check_total_report_sql(void) {
    static const char * query = 
        "SELECT * FROM check_total";
    return query;
}

