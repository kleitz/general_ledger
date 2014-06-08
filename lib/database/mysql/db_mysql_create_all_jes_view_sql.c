/*!
 * \file            db_mysql_create_all_jes_view_sql.c
 * \brief           Returns MYSQL SQL query to create all_jes view.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_all_jes_view_sql(void) {
    static const char * query = 
        "CREATE VIEW all_jes AS"
        "  SELECT"
        "    l.je AS 'JE',"
        "    j.entity AS 'En',"
        "    l.account AS 'A/C No.',"
        "    a.description AS 'Description',"
        "    l.amount AS 'Amount'"
        "    FROM jelines AS l"
        "    INNER JOIN jes AS j"
        "      ON j.id = l.je"
        "    INNER JOIN nomaccts AS a"
        "      ON a.num = l.account"
        "    ORDER BY j.id ASC, l.account ASC";
    return query;
}

