/*!
 * \file            db_query.h
 * \brief           Interface to database query functionality.
 * \details         Function implementations are provided by the individual
 * database components.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_QUERY_H
#define PG_GENERAL_LEDGER_DATABASE_DB_QUERY_H

#include <stdbool.h>

/*!
 * \brief           Executes an SQL query on the database.
 * \param query     The query to execute.
 * \returns         `true` if the query was successfully executed,
 * `false` otherwise.
 */
bool db_execute_query(const char * query);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_QUERY_H  */

