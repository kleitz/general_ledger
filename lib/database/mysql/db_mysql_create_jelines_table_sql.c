/*!
 * \file            db_mysql_create_jelines_table_sql.c
 * \brief           Returns MYSQL SQL query to create journal entry lines table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_jelines_table_sql(void) {
    static const char * query = 
        "CREATE TABLE jelines ("
        "    id         INTEGER         NOT NULL AUTO_INCREMENT,"
        "    je         INTEGER         NOT NULL,"
        "    account    VARCHAR(20)     NOT NULL,"
        "    amount     DECIMAL(20,2)   NOT NULL,"
        "  CONSTRAINT jelines_pk"
        "    PRIMARY KEY (id),"
        "  CONSTRAINT jes_je_fk"
        "    FOREIGN KEY (je)"
        "    REFERENCES jes(id),"
        "  CONSTRAINT jes_account_fk"
        "    FOREIGN KEY (account)"
        "    REFERENCES nomaccts(num)"
        ");";
    return query;
}

