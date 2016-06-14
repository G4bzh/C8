/*
 * do_0x3
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../error.h"
#include "../c8.h"
#include "do.h"


/*
 *  0x03xkk : SE Vx, kk
 *  The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
 */ 

int do_0x3xkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return ERR_NULL;
    }

  if (x >= C8_REGISTERS)
    {
      return ERR_REGOUTOFRANGE;
    }  

  /* Skip */
  if (c8->V[x] == kk)
    {
      c8->PC++;
    }

  /* Next */
  c8->PC++;

  return ERR_SUCCESS;
}
