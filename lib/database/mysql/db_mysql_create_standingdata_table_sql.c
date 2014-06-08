/*!
 * \file            db_mysql_create_standingdata_table_sql.c
 * \brief           Returns MYSQL SQL query to create standing data table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_create_standingdata_table_sql(void) {
    static const char * query = 
        "CREATE TABLE standing_data ("
        "    organization   VARCHAR(100)    NOT NULL,"
        "    current_year   INTEGER         NOT NULL,"
        "    current_period INTEGER         NOT NULL,"
        "    num_periods    INTEGER         NOT NULL,"
        "  CONSTRAINT standing_data_pk"
        "    PRIMARY KEY (organization)"
        ");";
    return query;
}

