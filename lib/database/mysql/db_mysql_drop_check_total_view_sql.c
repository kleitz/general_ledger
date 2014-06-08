/*!
 * \file            db_mysql_drop_check_total_view_sql.c
 * \brief           Returns MYSQL SQL query to drop check total view.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

const char * db_drop_check_total_view_sql(void) {
    static const char * query = 
        "DROP VIEW check_total";
    return query;
}

