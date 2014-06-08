/*!
 * \file            db_mysql_create_jesrcs_table_sql.c
 * \brief           Returns MYSQL SQL query to create JE sources table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_jesrcs_table_sql(void) {
    static const char * query = 
        "CREATE TABLE jesrcs ("
        "    name           VARCHAR(10)     NOT NULL,"
        "    description    VARCHAR(100)    NOT NULL,"
        "  CONSTRAINT jesrcs_pk"
        "    PRIMARY KEY (name)"
        ");";
    return query;
}

