/*
 * do_0xA
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0xAnnn : LD I, nnn
 *  The value of register I is set to nnn.
 */ 

int do_0xAnnn(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  c8->I = (uint16_t*)(c8->memory + nnn);

  /* Next */
  c8->PC++;
  
    
  return EXIT_SUCCESS;
}