/*
 * Error handling
 *
 */

#include <stdio.h>


#define ERR_ERRORS       11



const char* err_str[ERR_ERRORS] = {
  "Success",
  "Object is NULL",
  "Value is 0",
  "Stack Overflow",
  "Register number is out of range",
  "Unknown instruction",
  "Keyboard key is out of range",
  "Display must be 64x32",
  "Screen coordinates are out of range",
  "File is too big",
  "Error reading file"
};



/*
 * Human readable erro
 *
 */

void err_tostr(int n)
{
  if (n < ERR_ERRORS)
    {
      printf("ERROR %d : %s \n",n,err_str[n]);
    }
  
  return;
}

