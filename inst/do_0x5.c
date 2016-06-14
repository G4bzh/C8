/*
 * do_0x5
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../error.h"
#include "../c8.h"
#include "do.h"


/*
 *  0x05xy0 : SE Vx, Vy
 *  The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
 */ 

int do_0x5xy0(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return ERR_NULL;
    }

  if ( (x >= C8_REGISTERS) || (y >= C8_REGISTERS) )
    {
      return ERR_REGOUTOFRANGE;
    }  

  /* Skip */
  if (c8->V[x] == c8->V[y])
    {
      c8->PC++;
    }

  /* Next */
  c8->PC++;
  
  return ERR_SUCCESS;
}
