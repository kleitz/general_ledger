#include <stdlib.h>

#include "database/database.h"
#include "database/database_sql.h"
#include "database/db_entities.h"
#include "datastruct/ds_recordset.h"
#include "datastruct/ds_str.h"

int db_create_entities_table(void) {
    return db_execute_query(db_create_entities_table_sql());
}

int db_drop_entities_table(void) {
    return db_execute_query(db_drop_entities_table_sql());
}

ds_str db_list_entities_report(void) {
    const char * query = db_list_entities_report_sql();
    return db_create_report_from_query(query);
}

