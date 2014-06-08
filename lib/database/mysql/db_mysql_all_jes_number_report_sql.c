/*!
 * \file            db_mysql_all_jes_number_report_sql.c
 * \brief           Returns MYSQL SQL query to create JE by number report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_all_jes_number_report_sql(void) {
    static const char * query = 
        "SELECT * FROM all_jes"
        "  WHERE JE = %s";
    return query;
}

