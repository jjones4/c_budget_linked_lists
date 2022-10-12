/*
 *
 * Name:       c_budget_read_input.c
 *
 * Purpose:    Contains functions for reading user input.
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
 * Preprocessing directives
 *
 */
#include "c_budget_read_input.h"



/*
 *
 * I'm declaring clear_buffer here instead of in a
 * header file because it is only used here (for now)
 *
 */
void clear_buffer(char *buff);



/*
 *
 * IMPORTANT NOTE:
 *
 * I have created separate functions for
 * each type of user input (menu, date, amount,
 * type of transaction, and description).
 *
 * This is because I want a different buffer size for each
 * function, and c89 does not allow variable length arrays.
 *
 */
 


/*
 *
 * Reads menu input
 *
 */
int read_menu_input(char *input_string)
{
   char buff[MENU_INPUT_LENGTH + 1];
   char *p;
   
   if (fgets(buff, MENU_INPUT_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      /*
       * If fgets left a new line in the string (because it reached a
       * new line before the maximum buffer length was reached)
       * replace the new line character with the null character.
       */
      p = input_string;
      while(*p)
      {
         if(*p == '\n')
         {
            *p = '\0';
         }
         
         p++;
      }
      
      clear_buffer(buff);
      
      return 0;
   }
   else
   {
      clear_buffer(buff);
      
      return -10;
   }
}



/*
 *
 * Reads input for the ID of a transaction
 *
 */
int read_id_input(char *input_string)
{
   char buff[ID_INPUT_LENGTH + 1];
   char *p;
   
   if (fgets(buff, ID_INPUT_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      /*
       * If fgets left a new line in the string (because it reached a
       * new line before the maximum buffer length was reached)
       * replace the new line character with the null character.
       */
      p = input_string;
      while(*p)
      {
         if(*p == '\n')
         {
            *p = '\0';
         }
         
         p++;
      }
      
      clear_buffer(buff);
      
      return 0;
   }
   else
   {
      clear_buffer(buff);
      
      return -10;
   }
}



/*
 *
 * Reads input for the date
 *
 */
int read_date_input(char *input_string)
{
   char buff[DATE_LENGTH + 1];
   char *p;
   
   if (fgets(buff, DATE_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      /*
       * If fgets left a new line in the string (because it reached a
       * new line before the maximum buffer length was reached)
       * replace the new line character with the null character.
       */
      p = input_string;
      while(*p)
      {
         if(*p == '\n')
         {
            *p = '\0';
         }
         
         p++;
      }
      
      clear_buffer(buff);
      
      return 0;
   }
   else
   {
      clear_buffer(buff);
      
      return -10;
   }
}



/*
 *
 * Reads input for the amount
 *
 */
int read_amount_input(char *input_string)
{
   char buff[AMOUNT_LENGTH + 1];
   char *p;
   
   if (fgets(buff, AMOUNT_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      /*
       * If fgets left a new line in the string (because it reached a
       * new line before the maximum buffer length was reached)
       * replace the new line character with the null character.
       */
      p = input_string;
      while(*p)
      {
         if(*p == '\n')
         {
            *p = '\0';
         }
         
         p++;
      }
      
      clear_buffer(buff);
      
      return 0;
   }
   else
   {
      clear_buffer(buff);
      
      return -10;
   }
}



/*
 *
 * Reads input for the type (credit or debit)
 *
 */
int read_type_input(char *input_string)
{
   char buff[TYPE_LENGTH + 1];
   char *p;
   
   if (fgets(buff, TYPE_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      /*
       * If fgets left a new line in the string (because it reached a
       * new line before the maximum buffer length was reached)
       * replace the new line character with the null character.
       */
      p = input_string;
      while(*p)
      {
         if(*p == '\n')
         {
            *p = '\0';
         }
         
         p++;
      }
      
      clear_buffer(buff);
      
      return 0;
   }
   else
   {
      clear_buffer(buff);
      
      return -10;
   }
}



/*
 *
 * Reads input for the description
 *
 */
int read_description_input(char *input_string)
{
   char buff[DESCRIPTION_LENGTH + 1];
   char *p;
   
   if (fgets(buff, DESCRIPTION_LENGTH + 1, stdin))
   {
      strcpy(input_string, buff);
      
      /*
       * If fgets left a new line in the string (because it reached a
       * new line before the maximum buffer length was reached)
       * replace the new line character with the null character.
       */
      p = input_string;
      while(*p)
      {
         if(*p == '\n')
         {
            *p = '\0';
         }
         
         p++;
      }
      
      clear_buffer(buff);
      
      return 0;
   }
   else
   {
      clear_buffer(buff);
      
      return -10;
   }
}



void clear_buffer(char *buff)
{
   char ch;
   char *p = &ch;
   /* Clear the input buffer */
   if((p = strchr(buff, '\n')))
   {
      /* Check if new line exists */
      *p = 0;
   }
   else
   {
      /* Clear up to new line */
      scanf("%*[^\n]");
      scanf("%*c");
   }
}



