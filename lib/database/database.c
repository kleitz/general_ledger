#include "gl_general/gl_general.h"
#include "database/database.h"
#include "database/db_users.h"
#include "database/db_entities.h"

int db_create_database_structure(void) {
    int status = db_drop_users_table();
    status = db_create_users_table();
    status = db_drop_entities_table();
    status = db_create_entities_table();
    status = db_add_sample_users();
    db_list_users();
    return status;
}

