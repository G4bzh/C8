/*
 * do_0xB
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0xBnnn : JP V0+nnn
 *  The program counter is set to nnn plus the value of V0.

 */ 

int do_0xBnnn(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  c8->PC = (uint16_t*)(c8->memory + c8->V[0]);

  return EXIT_SUCCESS;
}
