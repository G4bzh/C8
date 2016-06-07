/*
 * do_0x8
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0x8xyn
 *  Registers Operations
 */ 

int do_0x8xyn(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if ( (x >= C8_REGISTERS) || (y >= C8_REGISTERS) )
    {
      return EXIT_FAILURE;
    }  

  switch(n)
    {
    case 0x0:
      {
	/* LD Vx, Vy 
	 * Stores the value of register Vy in register Vx.
	 */
	c8->V[x] = c8->V[y];
	break;
      }

    case 0x1:
      {
	/* OR Vx, Vy 
	 * Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx.
	 */
	c8->V[x] |= c8->V[y];
	break;
      }

    case 0x2:
      {
        /* AND Vx, Vy
	 * Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx.
	 */
	c8->V[x] &= c8->V[y];
	break;
      }	    

    case 0x3:
      {
	/* XOR Vx, Vy 
	 * Performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx.
	 */
	c8->V[x] ^= c8->V[y];
	break;
      }

    case 0x4:
      {
	/* ADD Vx, Vy
	 * The values of Vx and Vy are added together
	 * If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0
	 * Only the lowest 8 bits of the result are kept, and stored in Vx
	 */

	uint16_t sum;

	sum = c8->V[x] + c8->V[y];
	c8->V[0xF] = (sum > 255) ? 1 : 0 ;
	c8->V[x] = (uint8_t)sum;	

	break;
      }	    

    case 0x5:
      {
	/* SUB Vx, Vy
	 * If Vx > Vy, then VF is set to 1, otherwise 0.
	 * Then Vy is subtracted from Vx, and the results stored in Vx.
	 */
	c8->V[0xF] = (c8->V[x] > c8->V[y]) ? 1 : 0 ;
	c8->V[x] -= c8->V[y];	
	
	break;
      }

    case 0x6:
      {
	/* SHR Vx, 1
	 * If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0
	 * Then Vx is divided by 2.
	 */

	c8->V[0xF] = (c8->V[x] & 0x01) ? 1 : 0 ;
	c8->V[x] >>= 1;
		
	break;
      }	   

    case 0x7:
      {
	/* SUBN Vx, Vy
	 * If Vy > Vx, then VF is set to 1, otherwise 0.
	 * Then Vx is subtracted from Vy, and the results stored in Vx.
	 */
	c8->V[0xF] = (c8->V[y] > c8->V[x]) ? 1 : 0 ;
	c8->V[x] = c8->V[y] - c8->V[x];	
		
	break;
      }

    case 0xE:
      {
	/* SHL Vx, 1
	 * If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0.
	 * Then Vx is multiplied by 2.
	 */
	c8->V[0xF] = (c8->V[x] & 0x80) ? 1 : 0 ;
	c8->V[x] <<= 1;

	break;
      }

    default:
      {
	return EXIT_FAILURE;
	break;
      }	    
	    
    }
  

  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;
}
