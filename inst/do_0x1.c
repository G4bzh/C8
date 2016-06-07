/*
 * do_0x1
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0x1nnn : JP nnn
 *  The interpreter sets the program counter to nnn. 
 */ 

int do_0x1nnn(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  c8->PC = (uint16_t*)(c8->memory + nnn);
    
  return EXIT_SUCCESS;
}
