/*
 *
 * Name:       c_budget_read_input.h
 *
 * Purpose:    Define macros and function prototypes for data input.
 *
 * Author:     jjones4
 *
 * Copyright (c) 2022 Jerad Jones
 * This file is part of c_budget_dynamic_strings.  c_budget_dynamic_strings
 * may be freely distributed under the MIT license.  For all details and
 * documentation, see
 *
 * https://github.com/jjones4/c_budget_dynamic_strings
 *
 */



/*
 *
 * Function Prototypes
 *
 */



#ifndef READ_INPUT_H
#define READ_INPUT_H



#include <stdio.h>
#include <string.h>



#define FILE_NAME "budget.txt"
#define TEMP_FILE_NAME "temp_budget.txt"

#define MAX_TRANSACTIONS 10
#define MAX_YEAR 3000

/* Set lengths for a transaction and for each part of a transaction */
#define MAX_TRANSACTION_LENGTH 250
#define DATE_LENGTH 10
#define AMOUNT_LENGTH 10
#define TYPE_LENGTH 2
#define DESCRIPTION_LENGTH 220

/* Don't allow Ids greater than 999,999 (six digits) */
#define ID_INPUT_LENGTH 6

#define MENU_INPUT_LENGTH 2
#define NUM_MAIN_MENU_OPTIONS 6
#define NUM_UPDATE_MENU_OPTIONS 6

/* Define an integer for file operation errors */
#define FILE_OPS_ERROR -10

int read_menu_input(char *menu_string);
int read_id_input(char *id_string);
int read_date_input(char *date_string);
int read_amount_input(char *amount_string);
int read_type_input(char *type_string);
int read_description_input(char *description_string);



#endif



