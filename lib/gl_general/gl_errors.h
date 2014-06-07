/*!
 * \file            gl_errors.h
 * \brief           Interface to error functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_GL_ERRORS_H
#define PG_GENERAL_LEDGER_GL_ERRORS_H

/*!
 * \brief           Logs an error message and quits program.
 * \param msg       The error message to log.
 */
void gl_error_quit(const char * msg);

#endif      /*  PG_GENERAL_LEDGER_GL_ERRORS_H  */

