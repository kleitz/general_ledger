#ifndef PG_GENERAL_LEDGER_DATABASE_SQL_H
#define PG_GENERAL_LEDGER_DATABASE_SQL_H

const char * db_create_users_table_sql(void);
const char * db_drop_users_table_sql(void);
char * db_add_user_sql(const char * first_name, const char * last_name);

#endif      /*  PG_GENERAL_LEDGER_DATABASE_SQL_H  */
