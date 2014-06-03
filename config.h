#ifndef PG_GENERAL_LEDGER_CONFIG_H
#define PG_GENERAL_LEDGER_CONFIG_H

#include <stdbool.h>
#include "datastruct/ds_str.h"

struct params {
    ds_str hostname;
    ds_str database;
    ds_str username;
    ds_str password;
    bool help;
    bool version;
    bool create;
    bool delete_data;
    bool sample;
    bool list_users;
    bool list_entities;
};

int get_configuration(struct params * params);
struct params *params_init(void);
void params_free(struct params * params);
int get_cmdline_options(int argc, char ** argv, struct params * params);

#endif      /*  PG_GENERAL_LEDGER_CONFIG_H  */

