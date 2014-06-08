/*!
 * \file            db_mysql_show_standingdata_report_sql.c
 * \brief           Returns MYSQL SQL query to create show standing data report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_show_standingdata_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  organization AS 'Organization',"
        "  current_year AS 'Current Year',"
        "  current_period AS 'Current Period',"
        "  num_periods AS 'Number Periods'"
        "  FROM standing_data"
        "  ORDER BY organization";
    return query;
}

