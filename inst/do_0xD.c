/*
 * do_0xD
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../error.h"
#include "../c8.h"
#include "do.h"


/*
 *  0xDxyn : Draw
 *  The interpreter reads n bytes from memory, starting at the address stored in I. 
 *  These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). 
 *  Sprites are XORed onto the existing screen. 
 *  If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. 
 *  If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around 
 *  to the opposite side of the screen.
 */ 

int do_0xDxyn(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  uint8_t* ptr;
  uint8_t byte, color, i, u, v;
  
  if (c8 == NULL)
    {
      return ERR_NULL;
    }

  if ( (x >= C8_REGISTERS) || (y >= C8_REGISTERS) )
    {
      return  ERR_REGOUTOFRANGE;
    }  

  
  for(ptr=c8->I, v=c8->V[y] ; ptr < c8->I+n ; ptr++, v++)
    {
      byte = *ptr; 
      for(i=0, u=c8->V[x]; i<sizeof(byte)*8; i++, u++, byte <<= 1 )
	{   
	  color =  byte & 0x80 ? 1 : 0 ;

	  /* Modulos ensure wrapping */
	  if ( !(c8->screen[(v%C8_SCREEN_HEIGHT)*C8_SCREEN_WIDTH+u%C8_SCREEN_WIDTH] ^ color) )
	    {
	      c8->V[0xF] = 1;
	    }

	  c8->screen[(v%C8_SCREEN_HEIGHT)*C8_SCREEN_WIDTH+u%C8_SCREEN_WIDTH] ^= color;
	}
    }

  
  /* Next */
  c8->PC++;
  
  return ERR_SUCCESS;
}
