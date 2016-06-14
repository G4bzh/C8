/*
 * do_0xE
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"

/*
 * 0xEx9E: SKP Vx
 * Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, 
 * PC is increased by 2.
 */


int do_0xEx9E(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if (x >= C8_REGISTERS) 
    {
      return EXIT_FAILURE;
    }

  if (c8->V[x] >= C8_KEYS) 
    {
      return EXIT_FAILURE;
    }

  /* Skip */
  if ( (c8->keyboard[c8->V[x]]) )
    {
      c8->PC++;
    }
  
  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;
}

/*
 * 0xExA1: SKNP Vx
 * Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, 
 * PC is increased by 2.
 */

int do_0xExA1(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if (x >= C8_REGISTERS) 
    {
      return EXIT_FAILURE;
    }

  if (c8->V[x] >= C8_KEYS) 
    {
      return EXIT_FAILURE;
    }  

  /* Skip */
  if ( !(c8->keyboard[c8->V[x]]) )
    {
      c8->PC++;
    }
  
  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;  
}
