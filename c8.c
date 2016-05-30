/*
 *  CHIP 8 Emulator
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "c8.h"


/*
 *  Constants
 *
 */


#define C8_MEMORY_SIZE      4096 
#define C8_ROM_SIZE         512  

#define C8_SCREEN_WIDTH     64   /* pixels */
#define C8_SCREEN_HEIGHT    32   /* pixels */

#define C8_FONTS            16
#define C8_FONT_SIZE        5   /* bytes */
#define C8_FONT_WIDTH       8   /* pixels */
#define C8_FONT_HEIGHT      5   /* pixels */

#define C8_START_OFFSET     0x200
#define C8_START_OFFSET_ETI 0x600
#define C8_FONT_OFFSET      0x0



/*
 * Hexa Font
 *
 */


uint8_t fonts[C8_FONTS][C8_FONT_SIZE] = {
  {0xF0, 0x90, 0x90, 0x90, 0xF0},
  {0x20, 0x60, 0x20, 0x20, 0x70},
  {0xF0, 0x10, 0xF0, 0x80, 0xF0},
  {0xF0, 0x10, 0xF0, 0x10, 0xF0},
  {0x90, 0x90, 0xF0, 0x10, 0x10},
  {0xF0, 0x80, 0xF0, 0x10, 0xF0},  
  {0xF0, 0x80, 0xF0, 0x90, 0xF0},
  {0xF0, 0x10, 0x20, 0x40, 0x40},
  {0xF0, 0x90, 0xF0, 0x90, 0xF0},
  {0xF0, 0x90, 0xF0, 0x10, 0xF0},
  {0xF0, 0x90, 0xF0, 0x90, 0x90},
  {0xE0, 0x90, 0xE0, 0x90, 0xE0},
  {0xF0, 0x80, 0x80, 0x80, 0xF0},
  {0xE0, 0x90, 0x90, 0x90, 0xE0},
  {0xF0, 0x80, 0xF0, 0x80, 0xF0},
  {0xF0, 0x80, 0xF0, 0x80, 0x80}
};



C8* c8_create(void)
{
  C8* c8;

  /* Allocate structure */
  c8 = (C8*)malloc(sizeof(C8));
  if (c8 == NULL)
    {
      return NULL;
    }

  /* Allocate RAM */
  c8->memory = (uint8_t*)malloc(C8_MEMORY_SIZE*sizeof(uint8_t));
  if (c8->memory == NULL)
    {
      free(c8);
      return NULL;
    }

  
  /* Copy fonts */
  memcpy(c8->memory+C8_FONT_OFFSET, fonts, C8_FONTS * C8_FONT_SIZE);

  return c8;
  
}


int c8_delete(C8* c8)
{
  if (c8 != NULL)
    {
      free(c8->memory);
      free(c8);
      return EXIT_SUCCESS;
    }

  return EXIT_FAILURE;
}


void print_font(C8* c8, uint8_t n)
{
  int j,k;
  
  if (n>0xF)
    {
      return;
    }
  
  for(j=0;j<C8_FONT_SIZE;j++)
    {
      for(k=0;k<C8_FONT_HEIGHT;k++)
	{
	  printf("%c", *(c8->memory+C8_FONT_OFFSET+n*C8_FONT_SIZE+j) & (((uint8_t)1)<<(7-k)) ? '*' : ' ');
	}
      printf("\n");
      
    }
  
}

int main()
{
  C8* c8;
 
  c8 = c8_create();

  print_font(c8, 0xD); 
  
  c8_delete(c8);
  
  return 0;
}
