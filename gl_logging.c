/*!
 * \file            gl_logging.c
 * \brief           Implementation of logging functionality.
 * \details         Implementation of logging functionality. Enables debugging
 * and other system messages to be recorded to a log file.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "gl_logging.h"

/*!  File scope variable for log file name  */
//static const char * log_file_name = "gl.log";
static const char * log_file_name = NULL;

/*!  File scope variable for log file pointer  */
static FILE * log_file = NULL;

/*!  File scope variable for current status of logging functionality  */
static bool logging_on = false;

/*!  File scope variable for program name  */
static const char * gl_program_name = "general_ledger";

void gl_set_logging(const bool status) {
    if ( status && !logging_on ) {
        if ( log_file_name ) {
            log_file = fopen(log_file_name, "w");
            if ( !log_file ) {
                fprintf(stderr, "%s: couldn't open log file: %s\n",
                        gl_program_name, strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        else {
            log_file = stderr;
        }

        logging_on = true;
        gl_log_msg("Starting to log...");
    }
    else if ( !status && logging_on ) {
        gl_log_msg("Ending logging...");
        if ( log_file != stderr ) {
            fclose(log_file);
        }
        logging_on = false;
    }
}

void gl_log_msg(const char * format, ...) {
    if ( logging_on ) {
        va_list ap;
        va_start(ap, format);
        fprintf(log_file, "%s: ", gl_program_name);
        vfprintf(log_file, format, ap);
        fprintf(log_file, "\n");
        va_end(ap);
    }
}
