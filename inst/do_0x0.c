/*
 * do_0x0
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0x00E0 : CLS
 *  Clear the display.
 */

int do_0x00E0(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  uint16_t i;
  
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  for( i=0 ; i<C8_SCREEN_SIZE ; i++ )
    {
      c8->screen[i] = 0;
    }

  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;
  
}


/*
 *  0x00EE : RET
 *  The interpreter sets the program counter to the address at the top of the stack, 
 *  then subtracts 1 from the stack pointer.
 */

int do_0x00EE(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if ( !(c8->SP) )
    {
      return EXIT_FAILURE;
    }

  c8->SP--;
  c8->PC = c8->stack[c8->SP];


   return EXIT_SUCCESS;
}
