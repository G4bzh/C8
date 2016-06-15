/*
 * Debugger 
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
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

  mvprintw(Y_OFFSET, X_OFFSET+10,"PC: 0x%x",(uint32_t)((uint8_t*)c8->PC - c8->memory));
  mvprintw(Y_OFFSET+1, X_OFFSET+10,"[PC]: 0x%x",htons(*c8->PC) );

  mvprintw(Y_OFFSET+3, X_OFFSET+10,"I: 0x%x",(c8->I ? (uint32_t)((uint8_t*)c8->I - c8->memory) : 0) );
  mvprintw(Y_OFFSET+4, X_OFFSET+10,"[I]: 0x%x",(c8->I ? htons(*c8->I) : 0) );

   mvprintw(Y_OFFSET+6, X_OFFSET+10,"DT: %d",c8->DT ); 
   mvprintw(Y_OFFSET+7, X_OFFSET+10,"ST: %d",c8->DT );

   mvprintw(Y_OFFSET+9, X_OFFSET+10,"SP: %d",c8->SP );

   for(i=0; i<C8_STACK_SIZE; i++)
     {
       mvprintw(Y_OFFSET+i, X_OFFSET+25,"STACK[%d]: 0x%x",C8_STACK_SIZE-1-i,(uint16_t)((uint8_t*)c8->stack[C8_STACK_SIZE-1-i] - c8->memory) );
     }

   if (step)
     {
       while(getch()==ERR)
	 {}
     }
   
  return;
}
