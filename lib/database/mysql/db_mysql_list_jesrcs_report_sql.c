/*!
 * \file            db_mysql_list_jesrcs_report_sql.c
 * \brief           Returns MYSQL SQL query to create JE sources report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_list_jesrcs_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  name AS 'Name',"
        "  description as 'Description'"
        "  FROM jesrcs"
        "  ORDER BY name";
    return query;
}

