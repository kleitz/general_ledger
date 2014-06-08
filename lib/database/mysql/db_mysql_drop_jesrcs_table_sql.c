/*!
 * \file            db_mysql_drop_jesrcs_table_sql.c
 * \brief           Returns MYSQL SQL query to drop JE sources table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_drop_jesrcs_table_sql(void) {
    static const char * query = "DROP TABLE jesrcs";
    return query;
}

