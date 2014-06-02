#ifndef PG_GENERAL_LEDGER_DB_ENTITIES_H
#define PG_GENERAL_LEDGER_DB_ENTITIES_H

int db_create_entities_table(void);
int db_drop_entities_table(void);
char * db_list_entities_report(void);

#endif      /*  PG_GENERAL_LEDGER_DB_ENTITIES_H  */

