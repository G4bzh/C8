/*
 * Keyboard Management
 *
 */

#include <stdlib.h>
#include <ncurses.h>
#include "error.h"
#include "c8.h"
#include "keyboard.h"




/*
 * Mapping
 * 
 * Original Layout :   +---+---+---+---+
 *                     | 1 | 2 | 3 | C |
 *                     +---+---+---+---+
 *                     | 4 | 5 | 6 | D |
 *                     +---+---+---+---+
 *                     | 7 | 8 | 9 | E |
 *                     +---+---+---+---+
 *                     | A | 0 | B | F |
 *                     +---+---+---+---+
 *
 */

const char mapping[] = {
  'v',              /* 0 */
  '"', '\'','(',    /* 1 2 3 */
  'e', 'r', 't',    /* 4 5 6 */
  'd', 'f', 'g',    /* 7 8 9 */
  'c', 'b',         /* A B */
  '-',              /* C */
  'y',              /* D */
  'h',              /* E */
  'n'               /* F */
};


/*
 * Getkey 
 *
 */


int kb_getkey(C8* c8, uint8_t block)
{
  int ch, i;
  
  if (c8 == NULL)
    {
      return ERR_NULL;
    }

  /* Clear keyboard */
  for(i=0; i < C8_KEYS; i++)
    {
      c8->keyboard[i] = 0;
    }


  timeout( block ? -1 : 5 );
  ch = getch();

  /* Search index in mapping array */
  for( i=0; ( ((char)ch != mapping[i]) && (i < C8_KEYS) ) ; i++ )
    {}

  /* Update C8 Keyboard */
  if (i<C8_KEYS)
    {
      c8->keyboard[i] = 1;
    }

  
  return ERR_SUCCESS;  
}
