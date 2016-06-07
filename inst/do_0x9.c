/*
 * do_0x9
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0x09xy0 : SNE Vx, Vy
 *  The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
 */ 

int do_0x9xy0(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if ( (x >= C8_REGISTERS) || (y >= C8_REGISTERS) )
    {
      return EXIT_FAILURE;
    }  

  /* Skip */
  if (c8->V[x] != c8->V[y])
    {
      c8->PC++;
    }

  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;
}
