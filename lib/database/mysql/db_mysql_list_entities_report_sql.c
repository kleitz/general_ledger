/*!
 * \file            db_mysql_list_entities_report_sql.c
 * \brief           Returns MYSQL SQL query to create list entities report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_list_entities_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  id AS 'ID',"
        "  shortname AS 'Short',"
        "  name AS 'Entity Name',"
        "  currency AS 'Curr.',"
        "  parent AS 'Parent'"
        "  FROM entities"
        "  ORDER BY id";
    return query;
}

