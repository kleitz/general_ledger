/*!
 * \file            gl_logging.h
 * \brief           Interface to logging functionality.
 * \details         Interface to logging functionality. Enables debugging
 * and other system messages to be recorded to a log file.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_GL_LOGGING_H
#define PG_GENERAL_LEDGER_GL_LOGGING_H

#include <stdbool.h>

/*!
 * \brief           Turns logging on or off.
 * \details         Turns logging on or off.
 * \param status    `true` to turn logging on, `false` to turn logging off.
 */
void gl_set_logging(const bool status);

/*!
 * \brief           Logs a message to the log file.
 * \details         Logs a message to the log file.
 * \param format    Format string, in same format as `printf()`.
 * \param ...       Variable arguments as specified by format string.
 */
void gl_log_msg(const char * format, ...);

#endif      /*  PG_GENERAL_LEDGER_GL_LOGGING_H  */

