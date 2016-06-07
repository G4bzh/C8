/*
 * do_0x7
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0x7xkk : ADD Vx, kk
 *  Adds the value kk to the value of register Vx, then stores the result in Vx.
 */ 

int do_0x7xkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if (x >= C8_REGISTERS) 
    {
      return EXIT_FAILURE;
    }  

  
  c8->V[x] += kk;
  

  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;
}
