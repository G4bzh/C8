/*
 * Keyboard Management
 *
 */

#include <stdlib.h>
#include <ncurses.h>
#include "keyboard.h"

/*
 * Non blocking getkey 
 *
 */

int kb_getkey_nonblocking(C8* c8)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}



/*
 * Blocking getkey 
 *
 */


int kb_getkey_blocking(C8* c8)
{
  int ch;
  
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  while ((ch = getch()) == ERR)
    {
    }

  printw("OK");
  
  return EXIT_SUCCESS;  
}
