/*
 *
 * Function Prototypes
 *
 */



#ifndef C_BUDGET_VALIDATION_H
#define C_BUDGET_VALIDATION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"

BOOL is_valid_main_menu_option(const char *input);
BOOL is_valid_update_menu_option(const char *input);
BOOL is_valid_date(char *input);
BOOL is_valid_amount(char *input);
BOOL is_valid_type(char *input);
BOOL is_valid_description(char *input);

#endif



