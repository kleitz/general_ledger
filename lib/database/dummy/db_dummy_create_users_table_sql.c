/*!
 * \file            db_dummy_create_users_table_sql.c
 * \brief           Returns dummy SQL query to create users table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_users_table_sql(void) {
    static const char * query = 
        "CREATE TABLE users ("
        "    id         INTEGER     NOT NULL AUTO_INCREMENT,"
        "    user_name  VARCHAR(30) NOT NULL UNIQUE,"
        "    first_name VARCHAR(30) NOT NULL,"
        "    last_name  VARCHAR(30) NOT NULL,"
        "    password   VARCHAR(30)          DEFAULT NULL,"
        "    enabled    BOOLEAN              DEFAULT FALSE,"
        "    created    TIMESTAMP   NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "  CONSTRAINT users_pk"
        "    PRIMARY KEY (id)"
        ");";
    return query;
}

