/*!
 * \file            db_mysql_drop_all_jes_view_sql.c
 * \brief           Returns MYSQL SQL query to drop all JES view.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_drop_all_jes_view_sql(void) {
    static const char * query = 
        "DROP VIEW all_jes";
    return query;
}

