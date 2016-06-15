/*
 * Debugger 
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include "error.h"
#include "c8.h"
#include "debugger.h"


#define X_OFFSET    C8_SCREEN_WIDTH+1
#define Y_OFFSET    0



/*
 * Debugger initialization
 *
 */

int dbg_init(void)
{
  int width, height;

  getmaxyx(stdscr, height, width);	
  if ( (width <  C8_SCREEN_WIDTH + 40) || (height <  C8_SCREEN_HEIGHT) )
    {
      endwin();
      return ERR_BADDISPLAY;
    }

  return ERR_SUCCESS;
}


/*
 * Debugger
 *
 */

void dbg_run(C8* c8, uint8_t step)
{
  int i;
  
  if (c8 == NULL)
    {
      return;
    }

  for (i=0; i<C8_REGISTERS; i++)
    {
      mvprintw(Y_OFFSET+i, X_OFFSET,"V%x: 0x%x",i,c8->V[i] );
    }
  
  return;
}
