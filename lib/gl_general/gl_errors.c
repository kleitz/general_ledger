/*!
 * \file            gl_errors.c
 * \brief           Implementation of error functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdlib.h>

#include "gl_general.h"

void gl_error_quit(const char * msg) {
    gl_log_msg("%s", msg);
    gl_log_msg("Exiting with error.");
    exit(EXIT_FAILURE);
}

