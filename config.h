#ifndef PG_GENERAL_LEDGER_CONFIG_H
#define PG_GENERAL_LEDGER_CONFIG_H

#include <stdbool.h>

struct params {
    char * hostname;
    char * database;
    char * username;
    char * password;
    bool help;
    bool create;
    bool list_users;
};

int get_configuration(struct params * params);
struct params *params_init(void);
void params_free(struct params * params);
int get_cmdline_options(int argc, char ** argv, struct params * params);

#endif      /*  PG_GENERAL_LEDGER_CONFIG_H  */

