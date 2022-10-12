/*
 *
 * Name:       c_budget_crud_operations.c
 *
 * Purpose:    Contains functions for adding, displaying, updating,
 *	       or removing a budget transaction.
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
#include "c_budget_crud_operations.h"
#include "boolean.h"
#include "c_budget_read_input.h"
#include "c_budget_validation.h"
#include "c_budget_menus.h"

char *build_transaction_string(const char *input, char *completed_transaction);
char *parse_transaction_string(char *transaction_field, char *complete_transaction_string);



int create_transaction(int *number_of_transactions, char **budget)
{
   FILE *fp;
   char complete_transaction_string[MAX_TRANSACTION_LENGTH + 1] = {0};
   char date_string[DATE_LENGTH + 1];
   char amount_string[AMOUNT_LENGTH + 1];
   char type_string[TYPE_LENGTH + 1];
   char description_string[DESCRIPTION_LENGTH + 1];
   
   char *p;
   char **c;
   
   BOOL valid_amount = FALSE, valid_description = FALSE;
   
   /*
    * Check for the existence of budget.txt
    * Terminate if can't open for appending.
    */
   fp = fopen(FILE_NAME, "a+");
   if(fp == NULL)
   {
      printf("\nFile error.\n\n");
      printf("Please ensure %s exists, and try again.\n\n", FILE_NAME);
      exit(EXIT_FAILURE);
   }
   
   /* Prompt for and validate date */
   do
   {
      printf("\nEnter the date of the transaction (mm/dd/yyyy). Enter \"b\" to go back: ");
      read_date_input(date_string);
      
      if(*date_string == 'b' || *date_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }
      
      if(!is_valid_date(date_string))
      {
         printf("\nThe date you entered was invalid. Please try again.\n");
      }
   } while(!is_valid_date(date_string));
   
   /* Prompt for and validate amount */
   do
   {
      printf("\nEnter the amount of the transaction. Enter \"b\" to go back: ");
      
      read_amount_input(amount_string);
      
      if(*amount_string == 'b' || *amount_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }

      valid_amount = is_valid_amount(amount_string);
      
      if(!valid_amount)
      {
         printf("\nThe amount you entered was invalid. Please try again.\n");
      }
   } while(!valid_amount);
   
   /* Prompt for and validate type (credit or debit) */
   do
   {
      printf("\nEnter the type of the transaction (0 or 1): Enter \"b\" to go back: ");
      read_type_input(type_string);
      
      if(*type_string == 'b' || *type_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }

      if(!is_valid_type(type_string))
      {
         printf("\nThe type you entered was invalid. Please try again.\n");
      }
   } while(!is_valid_type(type_string));
   
   /* Prompt for and validate description */
   do
   {
      printf("\nEnter the description of the transaction Enter \"b\" to go back: ");
      read_description_input(description_string);
      
      if(*description_string == 'b' || *description_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }

      valid_description = is_valid_description(description_string);
      
      if(!valid_description)
      {
         printf("\nThe description you entered was invalid. Please try again.\n");
      }
   } while(!valid_description);
   
   strcpy(complete_transaction_string, date_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, amount_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, type_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, description_string);
   strcat(complete_transaction_string, "|");
   
   /* Allocate memory for our new transaction */
   p = malloc(strlen(complete_transaction_string) + 1);
      
   if(p == NULL)
   {
      printf("\nMemory allocation error.\n");
      return EXIT_FAILURE;
   }
      
   strcpy(p, complete_transaction_string);
   
   /* Store the pointer to our new transaction in our budget array */
   c = budget + *number_of_transactions;
   *c = p;
   
   /* Write record to budget.txt */
   fprintf(fp, "%s", complete_transaction_string);
   fclose(fp);
   
   printf("\nRecord was successfully added.\n");
   
   (*number_of_transactions)++;
   return *number_of_transactions;
}



int read_transactions(int *number_of_transactions, char **budget)
{
   char date_string[DATE_LENGTH + 1];
   char amount_string[AMOUNT_LENGTH + 1];
   char type_string[TYPE_LENGTH + 1];
   char description_string[DESCRIPTION_LENGTH + 1];
   char *transaction_string_index;
   int i;
   
   printf("%-10s\t%-11s\t%-10s\t%-5s\t%-50s\n", "Id", "Date", "Amount", "Type", "Description");
   printf("%10s\t%-11s\t%-10s\t%-5s\t%-50s\n", "----------", "-----------", "----------", "-----",
          "--------------------------------------------------");
   
   /* Print out the transactions from the 2d array */
   for(i = 0; i < *number_of_transactions; i++)
   {
      /* Keep track of our position as we read from the complete_transaction_string array */
      transaction_string_index = *(budget + i);
   
      transaction_string_index = parse_transaction_string(date_string, transaction_string_index);
      transaction_string_index = parse_transaction_string(amount_string, transaction_string_index);
      transaction_string_index = parse_transaction_string(type_string, transaction_string_index);
      transaction_string_index = parse_transaction_string(description_string, transaction_string_index);
      
      printf("%10d\t%-11s\t%10s\t%5s\t%-50s\n", i + 1, date_string,
         amount_string, type_string, description_string);
   }
   
   return *number_of_transactions;
}



int update_transaction(int *number_of_transactions, char **budget)
{
   FILE* temp_pointer;
   char complete_transaction_string[MAX_TRANSACTION_LENGTH + 1];
   char id_string[MENU_INPUT_LENGTH + 1];
   char menu_string[MENU_INPUT_LENGTH + 1];
   char date_string[DATE_LENGTH + 1];
   char amount_string[AMOUNT_LENGTH + 1];
   char type_string[TYPE_LENGTH + 1];
   char description_string[DESCRIPTION_LENGTH + 1];
   char *transaction_string_index;
   
   char *p;
   char **c;
   
   BOOL valid_id = FALSE;
   BOOL valid_date= FALSE;
   BOOL valid_amount = FALSE;
   BOOL valid_description = FALSE;
   
   int i, id = 0;
   
   (void) read_transactions(number_of_transactions, budget);
   
   do
   {
      printf("\nType the ID of the transaction you would like to edit. Enter \"b\" to go back: ");
      
      (void) read_id_input(id_string);
      
      if(*id_string == 'b' || *id_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }
      
      /* Convert the character id entered by the user to int */
      id = atoi(id_string);
      printf("\nYou entered: %d\n", id);
   
      if(id > *number_of_transactions || id < 1)
      {
         printf("\nThe id you entered is invalid. Please try again.\n\n");
      }
      else
      {
         valid_id = TRUE;
      }
   } while(!valid_id);
   
   /* Go through the file until we get to the transaction line
    * of the ID that the user gave. We will store this lilne
    * in the complete_transaction_string
    */
   strcpy(complete_transaction_string, *(budget + id - 1));
   
   /* Keep track of our position as we read from the complete_transaction_string array */
   transaction_string_index = complete_transaction_string;
   
   transaction_string_index = parse_transaction_string(date_string, transaction_string_index);
   transaction_string_index = parse_transaction_string(amount_string, transaction_string_index);
   transaction_string_index = parse_transaction_string(type_string, transaction_string_index);
   transaction_string_index = parse_transaction_string(description_string, transaction_string_index);
   
   /* Let the user choose which field they want to update */
   do
   {
      display_update_record_menu();
   
      read_menu_input(menu_string);
      
      if(!is_valid_update_menu_option(menu_string))
      {
         printf("\nYou entered an invalid menu option. Please try again.\n");
      }
   } while(!is_valid_update_menu_option(menu_string));
   
   if(*menu_string == '1')
   {
      /* Prompt for and validate date */
      do
      {
         printf("\nEnter the date of the transaction (mm/dd/yyyy). Enter \"b\" to go back: ");
         read_date_input(date_string);
      
         valid_date = is_valid_date(date_string);
      
         if(*date_string == 'b' || *date_string == 'B')
         {
            printf("\nTransaction has been successfully discarded.\n");
            return *number_of_transactions;
         }
      
         if(!valid_date)
         {
            printf("\nThe date you entered was invalid. Please try again.\n");
         }
         
      } while(!valid_date);
   }
   else if(*menu_string == '2')
   {
      /* Prompt for and validate amount */
      do
      {
         printf("\nEnter the amount of the transaction. Enter \"b\" to go back: ");
         read_amount_input(amount_string);
      
         if(*amount_string == 'b' || *amount_string == 'B')
         {
            printf("\nTransaction has been successfully discarded.\n");
            return *number_of_transactions;
         }
         
         valid_amount = is_valid_amount(amount_string);
      
         if(!valid_amount)
         {
            printf("\nThe amount you entered was invalid. Please try again.\n");
         }
      } while(!valid_amount);
   }
   else if(*menu_string == '3')
   {
      /* Prompt for and validate type (credit or debit) */
      do
      {
         printf("\nEnter the type of the transaction (0 or 1): Enter \"b\" to go back: ");
         (void) read_type_input(type_string);
      
         if(*type_string == 'b' || *type_string == 'B')
         {
            printf("\nTransaction has been successfully discarded.\n");
            return *number_of_transactions;
         }

         if(!is_valid_type(type_string))
         {
            printf("\nThe type you entered was invalid. Please try again.\n");
         }
      } while(!is_valid_type(type_string));
   }
   else if(*menu_string == '4')
   {
      /* Prompt for and validate description */
      do
      {
         printf("\nEnter the description of the transaction Enter \"b\" to go back: ");
         (void) read_description_input(description_string);
      
         if(*description_string == 'b' || *description_string == 'B')
         {
            printf("\nTransaction has been successfully discarded.\n");
            return *number_of_transactions;
         }
         
         valid_description = is_valid_description(description_string);

         if(!valid_description)
         {
            printf("\nThe description you entered was invalid. Please try again.\n");
         }
      } while(!valid_description);
   }
   else if(*menu_string == '5')
   {
      printf("\nChanges were successfully discarded.\n");
      return *number_of_transactions;
   }
   else
   {
         printf("\nInvalid option entered. Please try again.\n");
   }
   
   /* Rebuild the complete_transaction_string with any new data given
    * by the user
    */
    
   strcpy(complete_transaction_string, date_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, amount_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, type_string);
   strcat(complete_transaction_string, "|");
   strcat(complete_transaction_string, description_string);
   strcat(complete_transaction_string, "|");
   
   /* Allocate memory for our new transaction */
   p = malloc(strlen(complete_transaction_string) + 1);
      
   if(p == NULL)
   {
      printf("\nMemory allocation error.\n");
      return EXIT_FAILURE;
   }
      
   strcpy(p, complete_transaction_string);
   
   /* Store the pointer to our new transaction in our budget array */
   c = budget + id - 1;
   *c = p;
   
   /* Move the new data to a temp file
    * Remove the original file, and rename the temp file
    * containing the new data
    */
   temp_pointer = fopen(TEMP_FILE_NAME, "w");
   if(temp_pointer == NULL)
   {
      printf("\nFile error.\n\n");
      printf("Could not open %s for writing..\n\n", TEMP_FILE_NAME);
      exit(EXIT_FAILURE);
   }
   
   c = budget;
   for(i = 0; i < *number_of_transactions; i++)
   {
      fprintf(temp_pointer, "%s", *c);
      c++;
   }
   
   fclose(temp_pointer);
   remove(FILE_NAME);
   rename(TEMP_FILE_NAME, FILE_NAME);
   printf("\nRecord %d successfully updated!\n", id);
   
   return *number_of_transactions;
}



int delete_transaction(int *number_of_transactions, char **budget)
{
   FILE* temp_pointer;
   char id_string[MENU_INPUT_LENGTH + 1];
   char menu_string[MENU_INPUT_LENGTH + 1];
   
   char **p;
   
   BOOL valid_id = FALSE;
   BOOL valid_yes_no = FALSE;
   
   int i, id = 0;
   
   (void) read_transactions(number_of_transactions, budget);
   
   do
   {
      printf("\nType the ID of the transaction you would like to delete. Enter \"b\" to go back: ");
      
      (void) read_id_input(id_string);
      
      if(*id_string == 'b' || *id_string == 'B')
      {
         printf("\nTransaction has been successfully discarded.\n");
         return *number_of_transactions;
      }
      
      /* Convert the character id entered by the user to int */
      id = atoi(id_string);
      printf("\nYou entered: %d\n", id);
   
      if(id > *number_of_transactions || id < 1)
      {
         printf("\nThe id you entered is invalid. Please try again.\n\n");
      }
      else
      {
         valid_id = TRUE;
      }
   } while(!valid_id);
   
   do
   {
      printf("\nAre you sure you want to delete record %d (Y/y or N/n): ", id);
      
      read_menu_input(menu_string);
      
      if(
         (*menu_string != 'y' && *menu_string != 'Y')
            &&
         (*menu_string != 'n' && *menu_string != 'N')
        )
      {
         printf("\nYou entered an invalid option. Please try again.\n");
      }
      else
      {
         valid_yes_no = TRUE;
      }
      
   } while(!valid_yes_no);
   
   if(*menu_string == 'y' || *menu_string == 'Y')
   {
      /* Move the new data to a temp file
       * Remove the original file, and rename the temp file
       * containing the new data
       */
    
      /* Open temp file stream for budget data text file */
      temp_pointer = fopen(TEMP_FILE_NAME, "w");
      if(temp_pointer == NULL)
      {
         fclose(temp_pointer);
         printf("Can't open %s\n", TEMP_FILE_NAME);
         exit(EXIT_FAILURE);
      }
      
      /* Remove the deleted transaction's pointer from array */
      p = budget;
      for(i = 0; i < *number_of_transactions; i++)
      {
         if(i >= *number_of_transactions)
         {
            p = p + 1;
         }
         
         p++;
      }
      
      p = budget;
      for(i = 0; i < *number_of_transactions - 1; i++)
      {
         fprintf(temp_pointer, "%s", *p);
         p++;
      }
   
      fclose(temp_pointer);
      remove(FILE_NAME);
      rename(TEMP_FILE_NAME, FILE_NAME);
      printf("\nRecord %d successfully deleted!\n", id);
   }
   else
   {
      printf("\nTransaction will not be deleted.\n");
      return *number_of_transactions;
   }
   
   (*number_of_transactions)--;
   return *number_of_transactions;
}



/* Separate a full transaction line from the budget file
 * into its component parts (i.e., date, amount, type,
 * and descirption
 */
char *parse_transaction_string(char *transaction_field, char *complete_transaction_string)
{
   char *p;
   p = transaction_field;
   
   while((*complete_transaction_string != '|') && (*complete_transaction_string))
   {
      *p = *complete_transaction_string++;
      p++;
   }
   
   *p = '\0';
   p = ++complete_transaction_string;
   
   return p;
}



