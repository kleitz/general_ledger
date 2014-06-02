#include <stdlib.h>

#include "database/database.h"
#include "database/database_sql.h"
#include "database/db_entities.h"

int db_create_entities_table(void) {
    return db_execute_query(db_create_entities_table_sql());
}

int db_drop_entities_table(void) {
    return db_execute_query(db_drop_entities_table_sql());
}

char * db_list_entities_report(void) {
    const char * query = db_list_entities_report_sql();
    ds_result_set results = db_create_result_set_from_query(query);
    char * report = ds_result_set_get_text_report(results);
    ds_result_set_destroy(results);
    return report;
}

