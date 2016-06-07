/*
 * do_0x2
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0x2nnn : CALL nnn
 *  The interpreter increments the stack pointer, then puts the current PC on the top of the stack. 
 *  The PC is then set to nnn.
 */ 

int do_0x2nnn(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if (c8->SP >= C8_STACK_SIZE - 1)
     {
      return EXIT_FAILURE;
    }

  c8->SP++;
  c8->stack[c8->SP] = c8->PC;
  c8->PC = (uint16_t*)(c8->memory + nnn);
    
  return EXIT_SUCCESS;
}
