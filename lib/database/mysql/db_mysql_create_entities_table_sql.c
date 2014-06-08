/*!
 * \file            db_mysql_create_entities_table_sql.c
 * \brief           Returns MYSQL SQL query to create entities table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_entities_table_sql(void) {
    static const char * query = 
        "CREATE TABLE entities ("
        "    id         INTEGER         NOT NULL AUTO_INCREMENT,"
        "    name       VARCHAR(100)    NOT NULL,"
        "    shortname  VARCHAR(10)     NOT NULL,"
        "    currency   CHAR(30)        NOT NULL DEFAULT 'USD',"
        "    parent     INT             NOT NULL,"
        "    aggregate  BOOLEAN         NOT NULL DEFAULT FALSE,"
        "    enabled    BOOLEAN         NOT NULL DEFAULT TRUE,"
        "  CONSTRAINT entities_pk"
        "    PRIMARY KEY (id),"
        "  CONSTRAINT entities_parent_fk"
        "    FOREIGN KEY (parent)"
        "    REFERENCES entities(id)"
        ");";
    return query;
}

