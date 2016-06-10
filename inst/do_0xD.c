/*
 * do_0xD
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include "../c8.h"
#include "do.h"


/*
 *  0xDxyn
 *  The interpreter reads n bytes from memory, starting at the address stored in I. 
 *  These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). 
 *  Sprites are XORed onto the existing screen. 
 *  If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. 
 *  If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around 
 *  to the opposite side of the screen.
 */ 

int do_0xDxyn(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk)
{
  uint16_t* ptr;
  
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if ( (x >= C8_REGISTERS) || (y >= C8_REGISTERS) )
    {
      return EXIT_FAILURE;
    }  

#include <stdio.h>
  
  for(ptr=c8->I; ptr < (uint16_t*)((uint8_t*)c8->I+n); ptr = (uint16_t*)((uint8_t*)ptr+1))
    {
      printf("0x%x: 0x%x\n",(uint32_t)ptr,(uint32_t)*((uint8_t*)ptr));
    }

  
  /* Next */
  c8->PC++;
  
  return EXIT_SUCCESS;
}
