#ifndef PG_GENERAL_LEDGER_DB_USERS_H
#define PG_GENERAL_LEDGER_DB_USERS_H

int db_create_users_table(void);
int db_drop_users_table(void);
int db_add_user(const char * first_name, const char * last_name);
int db_add_sample_users(void);
char * db_list_users_report(void);

#endif      /*  PG_GENERAL_LEDGER_DB_USERS_H  */

