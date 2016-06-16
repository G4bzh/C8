/*
 * do_0x6
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../error.h"
#include "../c8.h"
#include "do.h"


/*
 *  0x6xkk : LD Vx, kk
 *  The interpreter puts the value kk into register Vx.
 */ 

int do_0x6xkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return ERR_NULL;
    }

  if (x >= C8_REGISTERS) 
    {
      return ERR_REGOUTOFRANGE;
    }  

 
  c8->V[x] = kk;
 
  /* Next */
  c8->PC++;
  
  return ERR_SUCCESS;
}
