#include <stdlib.h>

#include "database/database.h"
#include "database/database_sql.h"
#include "database/db_users.h"
#include "delim_file_read/delim_file_read.h"
#include "datastruct/ds_result_set.h"

int db_create_users_table(void) {
    return db_execute_query(db_create_users_table_sql());
}

int db_drop_users_table(void) {
    return db_execute_query(db_drop_users_table_sql());
}

int db_add_user(const char * first_name, const char * last_name) {
    char * query = db_add_user_sql(first_name, last_name);
    int status = db_execute_query(query);
    free(query);
    return status;
}

int db_add_sample_users(void) {
    return db_add_sample_data("users", "sample_data/users");
}

char * db_list_users_report(void) {
    const char * query = db_list_users_report_sql();
    ds_result_set results = db_create_result_set_from_query(query);
    char * report = ds_result_set_get_text_report(results);
    ds_result_set_destroy(results);
    return report;
}

