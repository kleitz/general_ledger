/*!
 * \file            gl_login.h
 * \brief           Interface to login functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_GL_LOGIN_H
#define PG_GENERAL_LEDGER_GL_LOGIN_H

#include "datastruct/data_structures.h"

/*!
 * \brief           Gets a password from the user.
 * \returns         The password, or `NULL` on failure.
 */
ds_str login(void);

#endif      /*  PG_GENERAL_LEDGER_GL_LOGIN_H  */

