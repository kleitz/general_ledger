/*!
 * \file            db_mysql_entity_name_from_id_sql.c
 * \brief           Returns MYSQL SQL query to fetch an entity name from its
 * ID.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_get_entity_name_from_id_sql(void) {
    static const char * query = 
        "SELECT name FROM entities"
        "  WHERE id = %s";
    return query;
}

