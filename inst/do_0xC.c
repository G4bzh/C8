/*
 * do_0xC
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0x0Cxkk : RND
 *  The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. 
 *  The results are stored in Vx.
 */ 

int do_0xCxkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if (x >= C8_REGISTERS)
    {
      return EXIT_FAILURE;
    }  

 
  c8->V[x] = ((uint8_t)rand()) & kk;
 
  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;
}
