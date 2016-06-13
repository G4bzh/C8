/*
 * do_0xF
 *
 */


#include <stdint.h>
#include <stdlib.h>
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
      return EXIT_FAILURE;
    }

  if (x >= C8_REGISTERS) 
    {
      return EXIT_FAILURE;
    }

  switch(kk)
    {
    case 0x07:
      {
	/* LD  Vx, DT */
	c8->V[x] = c8->DT;
	break;
      }

    case 0x0A:
      {
	/* LD  Vx, K */

	int i;

	/* Getkey, blocking mode */
	if ( kb_getkey(c8, 1) == EXIT_FAILURE )
	  {
	    return EXIT_FAILURE;
	  }
	
	/* Look for the key */
	for(i=0; (c8->keyboard[i] == 0) && (i < C8_KEYS); i++)
	  {}
	
	if (i >= C8_KEYS)
	  {
	    return EXIT_FAILURE;
	  }
	else
	  {
	    c8->V[x] = i;	    
	  }
	
	break;
      }

    case 0x15:
      {
	/* LD  DT, Vx */
	c8->DT = c8->V[x];
	break;
      }
	    
    case 0x18:
      {
	/* LD  ST,Vx */
	break;
      }

    case 0x1E:
      {
	/* ADD I, Vx */
	break;
      }

    case 0x29:
      {
	/* LD F, Vx */
	break;
      }

    case 0x33:
      {
	/* LD B, Vx */
	break;
      }

    case 0x55:
      {
	/* LD [I], Vx */
	break;
      }	    

    case 0x65:
      {
	/* LD Vx, [I] */
	break;
      }

    default:
      {
	return EXIT_FAILURE;
	break;
      }
	    
    }  
  
  return EXIT_SUCCESS;
}
