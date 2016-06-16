/*
 * do_0xE
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../error.h"
#include "../c8.h"
#include "do.h"

/*
 * 0xEx9E: SKP Vx
 * Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, 
 * PC is increased by 2.
 */


int do_0xEx9E(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  uint8_t i;
  
  if (c8 == NULL)
    {
      return ERR_NULL;
    }

  if (x >= C8_REGISTERS) 
    {
      return ERR_REGOUTOFRANGE;
    }

  if (c8->V[x] >= C8_KEYS) 
    {
      return ERR_KEYOUTOFRANGE;
    }

  /* Skip */
  if ( (c8->keyboard[c8->V[x]]) )
    {
      c8->PC++;

      /* Keydown processed */
      c8->keydown = 0;

      /* Clear Keyboard */
      for(i=0; i < C8_KEYS; i++)
	{
	  c8->keyboard[i] = 0;
	}
    }
  
  /* Next */
  c8->PC++;
  
  return ERR_SUCCESS;
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
      return ERR_NULL;
    }

  if (x >= C8_REGISTERS) 
    {
      return ERR_REGOUTOFRANGE;
    }

  if (c8->V[x] >= C8_KEYS) 
    {
      return ERR_KEYOUTOFRANGE;
    }  

  /* Skip */
  if ( !(c8->keyboard[c8->V[x]]) )
    {
      c8->PC++; 
    }
  
  /* Next */
  c8->PC++;
  
  return ERR_SUCCESS;  
}
