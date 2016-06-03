/*
 * do_0x4
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0x04xkk : SNE Vx, kk
 *  The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
 */ 

int do_0x4xkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if (x >= C8_REGISTERS)
    {
      return EXIT_FAILURE;
    }  

  /* Skip */
  if (c8->V[x] != kk)
    {
      c8->PC++;
    }

  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;
}
