/*!
 * \file            db_mysql_drop_nomaccts_table_sql.c
 * \brief           Returns MYSQL SQL query to drop nominal accounts table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_drop_nomaccts_table_sql(void) {
    static const char * query = "DROP TABLE nomaccts";
    return query;
}

