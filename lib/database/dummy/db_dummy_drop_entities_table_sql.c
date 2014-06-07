/*!
 * \file            db_dummy_drop_entities_table_sql.c
 * \brief           Returns dummy SQL query to drop entities table.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_drop_entities_table_sql(void) {
    static const char * query = "DROP TABLE entities";
    return query;
}

