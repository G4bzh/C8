/*
 * do_0xF
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../error.h"
#include "../c8.h"
#include "../keyboard.h"
#include "do.h"


/*
 * 0xFxkk
 * DT, ST and I register operations
 */


int do_0xFxkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return ERR_NULL;
    }

  if (x >= C8_REGISTERS) 
    {
      return  ERR_REGOUTOFRANGE;
    }

  switch(kk)
    {
    case 0x07:
      {
	/* LD  Vx, DT 
	* The value of DT is placed into Vx.
	*/
	
	c8->V[x] = c8->DT;
	break;
      }

    case 0x0A:
      {
	/* LD  Vx, K 
	* All execution stops until a key is pressed, then the value of that key is stored in Vx.
	*/

	int i,ret;

	/* Getkey, blocking mode */
	if ( (ret=kb_getkey(c8, 1)) != ERR_SUCCESS )
	  {
	    return ret;
	  }
	
	/* Look for the key */
	for(i=0; (c8->keyboard[i] == 0) && (i < C8_KEYS); i++)
	  {}
	
	if (i >= C8_KEYS)
	  {
	    return ERR_KEYOUTOFRANGE;
	  }
	else
	  {
	    c8->V[x] = i;	    
	  }
	
	break;
      }

    case 0x15:
      {
	/* LD  DT, Vx 
	 * DT is set equal to the value of Vx.
	 */
	
	c8->DT = c8->V[x];
	break;
      }
	    
    case 0x18:
      {
	/* LD  ST,Vx 
	 * ST is set equal to the value of Vx
	 */
	
	c8->ST = c8->V[x];
	break;
      }

    case 0x1E:
      {
	/* ADD I, Vx 
	 * The values of I and Vx are added, and the results are stored in I.
	 */
	
	c8->I = (uint16_t*)((uint8_t*)c8->I + c8->V[x]);
	break;
      }

    case 0x29:
      {
	/* LD F, Vx 
	 * The value of I is set to the location for the hexadecimal font sprite corresponding to the value of Vx.
	 */
	
	c8->I = (uint16_t*)(c8->fonts+c8->V[x]*C8_FONT_SIZE);
	break;
      }

    case 0x33:
      {
	/* LD B, Vx 
	 * he interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, 
	 * the tens digit at location I+1, and the ones digit at location I+2. 
	 */
	  
	uint8_t tmp;
	
	tmp = c8->V[x]%100;

	*((uint8_t*)c8->I) = c8->V[x]/100;
	*((uint8_t*)c8->I+1) = tmp/10;
	*((uint8_t*)c8->I+2) = tmp % 10;
	
	break;
      }

    case 0x55:
      {
	/* LD [I], Vx 
	 * The interpreter copies the values of registers V0 through Vx into memory, 
	 * starting at the address in I.
	 */

	uint8_t i;

	for( i=0; i<x; i++)
	  {
	    *((uint8_t*)c8->I+i) = c8->V[i];
	  }
	
	break;
      }	    

    case 0x65:
      {
	/* LD Vx, [I]
	 * The interpreter reads values from memory starting at location I into registers V0 through Vx.
	 */

	uint8_t i;

	for( i=0; i<x; i++)
	  {
	    c8->V[i] = *((uint8_t*)c8->I+i);
	  }
	
	break;
      }

    default:
      {
	return  ERR_BADINST;
	break;
      }	    
    }

  /* Next */
  c8->PC++;
  
  return ERR_SUCCESS;
}
