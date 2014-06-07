#ifndef PG_GENERAL_LEDGER_DATABASE_H
#define PG_GENERAL_LEDGER_DATABASE_H

#include "database/db_users.h"
#include "database/db_entities.h"
#include "datastruct/ds_recordset.h"

void db_connect(const char * host, const char * database,
                const char * username, const char * password);
void db_close(void);
int db_execute_query(const char * query);
int db_create_database_structure(void);
int db_delete_database_structure(void);
int db_load_sample_data(void);
int db_add_sample_data(const char * table, const char * filename);
ds_str db_create_report_from_query(const char * query);
ds_recordset db_create_recordset_from_query(const char * query);
int db_add_sample_data(const char * table, const char * filename);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_H  */

