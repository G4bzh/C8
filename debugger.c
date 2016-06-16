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
  uint16_t nnn;
  uint8_t n,x,y,z,kk, PC0,PC1;

  if (c8 == NULL)
    {
      return;
    }

  for (i=0; i<C8_REGISTERS; i++)
    {
      mvprintw(Y_OFFSET+i, X_OFFSET,"V%x: 0x%02x",i,c8->V[i] );
    }

  PC0 = *((uint8_t*)(c8->PC));
  PC1 = *((uint8_t*)(c8->PC)+1);
  
  z = (PC0 >> 4) & 0xF;
  nnn = ( (uint16_t)PC0 << 8 | (uint16_t)PC1 )  & (uint16_t)0xFFF;
  n = PC1 & 0x0F;
  kk = PC1 & 0xFF;
  y = (PC1 >> 4) &0xF;
  x = PC0 & 0x0F;

  mvprintw(Y_OFFSET, X_OFFSET+10,"PC: 0x%x",(uint32_t)((uint8_t*)c8->PC - c8->memory));
  
  mvprintw(Y_OFFSET+1, X_OFFSET+10,"[PC]: 0x%x (0x%04x)",( (uint16_t)PC0 << 8 | (uint16_t)PC1 ),*c8->PC );

  mvprintw(Y_OFFSET+3, X_OFFSET+10,"I: 0x%x",(c8->I ? (uint32_t)((uint8_t*)c8->I - c8->memory) : 0) );
  mvprintw(Y_OFFSET+4, X_OFFSET+10,"[I]: 0x%x",(c8->I ? *c8->I : 0) );

   mvprintw(Y_OFFSET+6, X_OFFSET+10,"DT: %d",c8->DT ); 
   mvprintw(Y_OFFSET+7, X_OFFSET+10,"ST: %d",c8->DT );

   mvprintw(Y_OFFSET+9, X_OFFSET+10,"SP: %d",c8->SP );

   mvprintw(Y_OFFSET+11, X_OFFSET+10,"z: 0x%x",z);  
   mvprintw(Y_OFFSET+12, X_OFFSET+10,"nnn: 0x%x",nnn);
   mvprintw(Y_OFFSET+13, X_OFFSET+10,"n: 0x%x",n );
   mvprintw(Y_OFFSET+14, X_OFFSET+10,"kk:0x%x",kk );
   mvprintw(Y_OFFSET+15, X_OFFSET+10,"x: 0x%x",x );
   mvprintw(Y_OFFSET+16, X_OFFSET+10,"y: 0x%x",y );

    
   for(i=0; i<C8_STACK_SIZE; i++)
     {
       mvprintw(Y_OFFSET+i, X_OFFSET+35,"STACK[%d]: 0x%x",C8_STACK_SIZE-1-i,(uint16_t)((uint8_t*)c8->stack[C8_STACK_SIZE-1-i] - c8->memory) );
     }

   if (step)
     {
       while(getch()==ERR)
	 {}
     }
   
  return;
}
