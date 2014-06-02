#ifndef PG_GENERAL_LEDGER_DATABASE_H
#define PG_GENERAL_LEDGER_DATABASE_H

#include "datastruct/ds_result_set.h"

void db_connect(const char * host, const char * database,
                const char * username, const char * password);
void db_close(void);
int db_execute_query(const char * query);
int db_create_database_structure(void);
int db_list_users(void);
ds_result_set db_create_result_set_from_query(const char * query);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_H  */

