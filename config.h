#ifndef PG_GENERAL_LEDGER_CONFIG_H
#define PG_GENERAL_LEDGER_CONFIG_H

struct params {
    char * hostname;
    char * database;
    char * username;
    char * password;
};

struct params * get_configuration(char * passwd);
void params_free(struct params * params);

#endif      /*  PG_GENERAL_LEDGER_CONFIG_H  */

