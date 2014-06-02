#include <stdlib.h>

#include "database/database.h"
#include "database/database_sql.h"
#include "database/db_users.h"

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
    db_add_user("John", "Doe");
    db_add_user("Phillipa", "Nurfler");
    db_add_user("Algernon", "Fox");
    db_add_user("Jenny", "Minx");

    return 0;
}

