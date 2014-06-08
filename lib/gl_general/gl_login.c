/*!
 * \file            gl_login.c
 * \brief           Implementation of login functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>

#include "gl_general.h"

ds_str login(void) {
    ds_str passwd = ds_str_create("");

    printf("Enter password (*WILL BE VISIBLE*): ");
    fflush(stdout);

    if ( !ds_str_getline(passwd, 80, stdin) ) {
        ds_str_destroy(passwd);
        gl_log_msg("Couldn't get password.");
        return NULL;
    }

    return passwd;
}

