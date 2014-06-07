/*!
 * \file            db_connection.h
 * \brief           Interface to database connection functionality.
 * \details         Function implementations are provided by the individual
 * database components.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DATABASE_DB_CONNECTION_H
#define PG_GENERAL_LEDGER_DATABASE_DB_CONNECTION_H

#include <stdbool.h>

/*!
 * \brief           Connects to a database.
 * \param host      The hostname.
 * \param database  The database name.
 * \param username  The username with which to connect.
 * \param password  The password for the specified user.
 * \returns         `true` if the connection was successfully made,
 * `false` otherwise.
 */
bool db_connect(const char * host, const char * database,
                const char * username, const char * password);

/*!
 * \brief           Disconnects from a database.
 */
void db_close(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_DB_CONNECTION_H  */

