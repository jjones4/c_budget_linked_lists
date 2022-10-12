/*
 *
 * Name:       c_budget_menus.c
 *
 * Purpose:    Contains functions for showing c_budget_dynamic_strings's
 * menus to the user.
 *

 * Author:     jjones4
 *
 * Copyright (c) 2022 Jerad Jones
 * This file is part of c_budget_dynamic_strings.  c_budget_dynamic_strings
 * may be freely distributed under the MIT license.  For all details and
 * documentation, see
 
 * https://github.com/jjones4/c_budget_dynamic_strings
 *
 */



/*
 *
 * Preprocessing directives
 *
 */
#include "c_budget_menus.h"



/*
 *
 * Displays c_budget_dynamic_strings's main (initial) menu
 *
 */
void display_main_menu(void)
{
   printf("\n\n  --------------\n");
   printf("  |  C_BUDGET  |\n");
   printf("  --------------\n\n");
   printf("    Main Menu\n");
   printf("\n    Choose from the following options:\n\n");
   printf("\t(1) Create a New Record\n");
   printf("\t(2) Display Your Budget\n");
   printf("\t(3) Update an Existing Record\n");
   printf("\t(4) Delete a Record\n");
   printf("\t(5) Save and Quit\n");
   printf("\n    Type your option: ");
}



/*
 *
 * Displays c_budget_dynamic_strings's menu for updating a budget record
 *
 */
void display_update_record_menu(void)
{
   printf("\nChoose from the following options:\n\n");
   printf("\t(1) Change the date\n");
   printf("\t(2) Change the amount\n");
   printf("\t(3) Change the type\n");
   printf("\t(4) Change the description\n");
   printf("\t(5) Back\n");
   printf("\nType your option: ");
}



