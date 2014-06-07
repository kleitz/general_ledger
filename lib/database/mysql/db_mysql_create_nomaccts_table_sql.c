/*!
 * \file            db_mysql_create_nomaccts_table_sql.c
 * \brief           Returns MYSQL SQL query to create nominal accounts table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_nomaccts_table_sql(void) {
    static const char * query = 
        "CREATE TABLE nomaccts ("
        "    num            VARCHAR(20)     NOT NULL,"
        "    description    VARCHAR(100)    NOT NULL,"
        "    enabled        BOOLEAN         NOT NULL DEFAULT TRUE,"
        "  CONSTRAINT nomaccts"
        "    PRIMARY KEY (num)"
        ");";
    return query;
}

