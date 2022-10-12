/*
 *
 * Name:       c_budget_validation.c
 *
 * Purpose:    Contains functions for validating user input.
 *
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
#include "c_budget_validation.h"



/*
 *
 * Checks if the user typed a valid option
 * from a menu
 *
 * Note that the menu input buffer can handle two characters,
 * so we can go up to 99 options
 */
BOOL is_valid_main_menu_option(const char *input)
{
   BOOL valid_input = FALSE;

   if( (atoi(input)) > 0 && (atoi(input)) < NUM_MAIN_MENU_OPTIONS)
   {
      valid_input = TRUE;
   }
   
   return valid_input;
}



/*
 *
 * Checks if the user typed a valid option
 * from the update record menu
 *
 * Note that the menu input buffer can handle two characters,
 * so we can go up to 99 options
 */
BOOL is_valid_update_menu_option(const char *input)
{
   BOOL valid_input = FALSE;

   if( (atoi(input)) > 0 && (atoi(input)) < NUM_UPDATE_MENU_OPTIONS)
   {
      valid_input = TRUE;
   }
   
   return valid_input;
}



/*
 *
 * Checks if the user typed a valid date
 *
 */
BOOL is_valid_date(char *date_string)
{
   BOOL valid_date = FALSE;
   BOOL valid_month = FALSE;
   BOOL valid_day = FALSE;
   BOOL valid_year = FALSE;
   char month_str[3];
   char day_str[3];
   char year_str[5];
   int month = 0, day = 0, year = 0;
   int counter = 0;
   int slash_indeces[2] = {0};
   char *p;
   int num_slashes = 0;
   int i, j;
   
   /* Count the slashes in the date string */
   p = date_string;
   while(*p)
   {
      if(*p == '/')
      {
         counter++;
      }
      
      p++;
   }
   
   /* If we don't have exactly two slashes in the date string,
    * the date is invalid */
   if(counter != 2)
   {
      return FALSE;
   }
   
   /* Get the index of each slash and store in array */
   p = date_string;
   counter = 0;
   num_slashes = 0;
   while(*p)
   {
      if(*p == '/')
      {
         slash_indeces[num_slashes] = counter;
         num_slashes++;
      }
      p++;
      counter++;
   }
   
   /* Check that the slashes are at the correct index in the
    * string. Either (1,3) (1,4) (2,4) or (2,5) */
   if( (*slash_indeces != 1 || *(slash_indeces + 1) != 3) &&
       (*slash_indeces != 1 || *(slash_indeces + 1) != 4) &&
       (*slash_indeces != 2 || *(slash_indeces + 1) != 4) &&
       (*slash_indeces != 2 || *(slash_indeces + 1) != 5)
     )
   {
      return FALSE;
   }   
   
   /* Fill the month_string array with the characters for the month */
   p = date_string;
   for(i = 0; i < slash_indeces[0]; i++)
   {
      *(month_str + i) = *p;
      p++;
   }
   *(month_str + i) = '\0';
   p++;
   
   /* Fill the day_string array with the characters for the day */
   for(j = 0, i = *slash_indeces + 1; i < *(slash_indeces + 1); i++)
   {
      *(day_str + j) = *p;
      j++;
      p++;
   }
   *(day_str + j) = '\0';
   p++;
   
   /* Fill the year_string array with the characters for the year */
   for(j = 0, i = *(slash_indeces + 1) + 1; i < *(slash_indeces + 1) + 5; i++)
   {
      *(year_str + j) = *p;
      j++;
      p++;
   }
   *(year_str + j) = '\0';
   p++;
   
   /* Convert month, day and year to integers for testing */
   month = atoi(month_str);
   day = atoi(day_str);
   year = atoi(year_str);
   
   /* Check that the month is between 1 and 12 (inclusive) */
   if(month >= 1 && month <= 12)
   {
      valid_month = TRUE;
   }
   
   /* Check that the days in February are between 1 and 28 (inclusive) */
   /* Leap years are handled last (see the last validation) */
   if( (day >= 1 && day <= 28)
      &&
       ((month == 2))
     )
   {
      valid_day = TRUE;
   }
   
   /* Check that the appropriate months have 30 days */
   if( (day >= 1 && day <= 30)
      &&
       ((month == 4) || (month == 6) || (month == 9) || (month == 11))
     )
   {
      valid_day = TRUE;
   }
   
   /* Check that the appropriate months have 31 days */
   if( (day >= 1 && day <= 31)
      &&
       ((month == 1) || (month == 3) || (month == 5)
      || 
       (month == 7) || (month == 8) || (month == 10)
      ||
       (month == 12))
     )
   {
      valid_day = TRUE;
   }
   
   /* Make sure we consider it a valid day if we find 29 days in February
    * on a leap year */
   if( (day == 29 && month == 2)
      &&
       ((year % 400 == 0) || (year % 4 == 00 && year % 100 != 0))
     )
   {
      valid_day = TRUE;
   }
   
   /* Check to make sure our years are within a reasonable range */
   if(year > 0 && year < MAX_YEAR)
   {
      valid_year = TRUE;
   }
   
   /* If all validation checks pass, we are good to go */
   if((valid_month == TRUE) && (valid_day == TRUE) && (valid_year == TRUE))
   {
      valid_date = TRUE;
   }
   
   /* null terminate the string in case it's shorter than the origan input */
   /* Otherwise, it will contain the new line from the original input */
   date_string[*(slash_indeces + 1) + 5] = '\0';
   
   return valid_date;
}



/*
 *
 * Checks if the user typed a valid amount
 *
 */
BOOL is_valid_amount(char *amount_string)
{
   BOOL valid_input = FALSE;
   BOOL valid_decimal_count = FALSE;
   BOOL valid_leading_zero = TRUE;
   BOOL valid_digits = TRUE;
   char *p = amount_string;
   int decimal_count = 0;
   int decimal_index = 0;
   int counter = 0;

   /* Check for exactly one decimal point */
   while(*p++)
   {
      if(*p == '.')
      {
         decimal_count++;
      }
   }

   if(decimal_count == 1)
   {
      valid_decimal_count = TRUE;
   }
   
   /*
    * If there is only one decimal as required,
    * then find it's index
    */
   if(valid_decimal_count == TRUE)
   {
      p = amount_string;
      while(*p++)
      {
         decimal_index++;
         
         if(*p == '.')
         {
            break;
         }
      }
   }
   
   /* 
    * Ensure if the number starts with zero, then
    * the decimal follows the leading zero.
    * Prevents something like $01.00
    */
   if(*amount_string == '0' && *(amount_string + 1) != '.')
   {
      valid_leading_zero = FALSE;
   }
   
   /*
    * Make sure every digit that is NOT a decimal
    * is numerical
    */
   p = amount_string;
   counter = 0;
   while(*p)
   {
      if(counter != decimal_index)
      {
         if(
               *p != '0' && *p != '1'
            && *p != '2' && *p != '3'
            && *p != '4' && *p != '5'
            && *p != '6' && *p != '7'
            && *p != '8' && *p != '9'
           )
         {
             valid_digits = FALSE;
         }
      }
      
      if(counter == (decimal_index + 2))
      {
         break;
      }
      
      p++;
      counter++;
   }
   
   /* null terminate the string in case it's shorter than the origan input */
   /* Otherwise, it will contain the new line from the original input */
   amount_string[decimal_index + 3] = '\0';
   
   if(
      (valid_decimal_count == TRUE) && (valid_leading_zero == TRUE)
        && (valid_digits == TRUE)
     )
   {
      valid_input = TRUE;
   }
   
   return valid_input;
}



/*
 *
 * Checks if the user typed a valid type
 * (1 or 0) for credit or debit
 *
 */
BOOL is_valid_type(char *type_string)
{
   BOOL valid_input = FALSE;
   
   if(*type_string == '0' || *type_string == '1')
   {
      valid_input = TRUE;
   }
   
   /* null terminate the string in case it's shorter than the origan input */
   /* Otherwise, it will contain the new line from the original input */
   type_string[1] = '\0';
   
   return valid_input;
}



/*
 *
 * Puts '\0' at the end of the description because we don't care
 * what's in there, as long as it is terminated.
 *
 */
BOOL is_valid_description(char *description_string)
{
   BOOL valid_input = FALSE;
   char *p = description_string;
   int counter = 0;
   
   while(*p)
   {
      p++;
      counter++;
   }
   
   *(description_string + counter) = '\0';
   
   valid_input = TRUE;
   
   return valid_input;
}



