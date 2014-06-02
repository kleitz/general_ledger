#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * db_add_user_sql(const char * first_name, const char * last_name) {
    static const char * query = 
        "INSERT INTO users(first_name, last_name)"
        "  VALUES ('%s', '%s');";

    size_t length = strlen(query) + strlen(first_name) + strlen(last_name);
    char * result_buffer = malloc(length);
    if ( !result_buffer ) {
        return NULL;
    }

    sprintf(result_buffer, query, first_name, last_name);
    return result_buffer;
}

