/*!
 * \file            db_mysql_list_jes_report_sql.c
 * \brief           Returns MYSQL SQL query to create journal entries report.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_list_jes_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  j.id AS 'JE',"
        "  e.shortname AS 'Entity',"
        "  j.memo AS 'Memo',"
        "  j.posted AS 'Posting Time'"
        "  FROM jes j"
        "  INNER JOIN entities e"
        "    ON j.entity = e.id"
        "  ORDER BY j.id";
    return query;
}

