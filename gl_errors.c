#include <stdio.h>
#include <stdlib.h>

#include "gl_general.h"

void gl_error_quit(const char * msg) {
    gl_log_msg("%s", msg);
    gl_log_msg("Exiting with error.");
    exit(EXIT_FAILURE);
}

