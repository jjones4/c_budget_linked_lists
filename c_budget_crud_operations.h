/*
 *
 * Function Prototypes
 *
 */



#ifndef CRUD_OPERATIONS_H
#define CRUD_OPERATIONS_H
#include <stdio.h>
#include "c_budget_read_input.h"

int create_transaction(int *number_of_transactions, char **budget);
int read_transactions(int *number_of_transactions, char **budget);
int update_transaction(int *number_of_transactions, char **budget);
int delete_transaction(int *number_of_transactions, char **budget);

#endif



