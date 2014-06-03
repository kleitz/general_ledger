#ifndef PG_GENERAL_LEDGER_DB_ENTITIES_H
#define PG_GENERAL_LEDGER_DB_ENTITIES_H

#include "datastruct/ds_str.h"

int db_create_entities_table(void);
int db_drop_entities_table(void);
ds_str db_list_entities_report(void);

#endif      /*  PG_GENERAL_LEDGER_DB_ENTITIES_H  */

