/*
 *
 * Name:       c_budget_crud_operations.h
 *
 * Purpose:    Contains function prototypes for adding,
 *             displaying, updating, or removing a budget
 *	       transaction.
 *
 *
 * Author:     jjones4
 *
 * Copyright (c) 2022 Jerad Jones
 * This file is part of c_budget_linked_lists.  c_budget_linked_lists
 * may be freely distributed under the MIT license.  For all details and
 * documentation, see
 
 * https://github.com/jjones4/c_budget_linked_lists
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



