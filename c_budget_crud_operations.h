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

struct transaction
{
   char *date;
   char *amount;
   char *type;
   char *description;
      
   struct transaction *next;
};

/* For the Create function, we are using a pointer to a pointer to a budget
 * transaction node. This is because we need to modify the address of the
 * first node in the list when we create a new node.
 */
int create_transaction(int *number_of_transactions, struct transaction **ptr_budget);

int read_transactions(int *number_of_transactions, struct transaction *budget);
int update_transaction(int *number_of_transactions, struct transaction *budget);
int delete_transaction(int *number_of_transactions, struct transaction *budget);

#endif



