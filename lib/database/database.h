#ifndef PG_GENERAL_LEDGER_DATABASE_H
#define PG_GENERAL_LEDGER_DATABASE_H

void db_connect(const char * host, const char * database,
                const char * username, const char * password);
void db_close(void);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_H  */

