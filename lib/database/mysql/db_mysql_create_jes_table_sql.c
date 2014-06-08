/*!
 * \file            db_mysql_create_jes_table_sql.c
 * \brief           Returns MYSQL SQL query to create journal entries table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_jes_table_sql(void) {
    static const char * query = 
        "CREATE TABLE jes ("
        "    id         INTEGER         NOT NULL AUTO_INCREMENT,"
        "    user       INTEGER         NOT NULL,"
        "    period     INTEGER         NOT NULL,"
        "    year       INTEGER         NOT NULL,"
        "    source     VARCHAR(10)     NOT NULL,"
        "    entity     INTEGER         NOT NULL,"
        "    memo       VARCHAR(100)    NOT NULL,"
        "    posted     TIMESTAMP       NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "  CONSTRAINT jes_pk"
        "    PRIMARY KEY (id),"
        "  CONSTRAINT jes_user_fk"
        "    FOREIGN KEY (user)"
        "    REFERENCES users(id),"
        "  CONSTRAINT jes_entity_fk"
        "    FOREIGN KEY (entity)"
        "    REFERENCES entities(id),"
        "  CONSTRAINT jes_source_fk"
        "    FOREIGN KEY (source)"
        "    REFERENCES jesrcs(name)"
        ");";
    return query;
}

