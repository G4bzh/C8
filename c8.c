/*
 *  CHIP 8 Emulator
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "gfx.h"
#include "inst/do.h"
#include "c8.h"


/*
 *  Constants
 *
 */


#define C8_MEMORY_SIZE      4096 
#define C8_ROM_SIZE         512  

#define C8_FONTS            16
#define C8_FONT_WIDTH       8   /* pixels */
#define C8_FONT_HEIGHT      5   /* pixels */

#define C8_START_OFFSET     0x200
#define C8_START_OFFSET_ETI 0x600



/*
 * Hexa Font
 *
 */


uint8_t default_fonts[] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0,
  0x20, 0x60, 0x20, 0x20, 0x70,
  0xF0, 0x10, 0xF0, 0x80, 0xF0,
  0xF0, 0x10, 0xF0, 0x10, 0xF0,
  0x90, 0x90, 0xF0, 0x10, 0x10,
  0xF0, 0x80, 0xF0, 0x10, 0xF0,  
  0xF0, 0x80, 0xF0, 0x90, 0xF0,
  0xF0, 0x10, 0x20, 0x40, 0x40,
  0xF0, 0x90, 0xF0, 0x90, 0xF0,
  0xF0, 0x90, 0xF0, 0x10, 0xF0,
  0xF0, 0x90, 0xF0, 0x90, 0x90,
  0xE0, 0x90, 0xE0, 0x90, 0xE0,
  0xF0, 0x80, 0x80, 0x80, 0xF0,
  0xE0, 0x90, 0x90, 0x90, 0xE0,
  0xF0, 0x80, 0xF0, 0x80, 0xF0,
  0xF0, 0x80, 0xF0, 0x80, 0x80
};



/*
 * Emulator creation
 *
 */


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

  /* Allocate fonts */
  c8->fonts = (uint8_t*)malloc( C8_FONTS * C8_FONT_SIZE * sizeof(uint8_t));
  if (c8->fonts == NULL)
    {
      free(c8->memory);
      free(c8);
      return NULL;
    }
  
  /* Copy fonts */
  memcpy(c8->fonts, default_fonts, C8_FONTS * C8_FONT_SIZE);

  /* Set SP */
  c8->SP = C8_STACK_SIZE-1;
  
  return c8;  
}



/*
 * Emulator deletion
 *
 */


int c8_delete(C8* c8)
{
  if (c8 != NULL)
    {
      free(c8->fonts);
      free(c8->memory);
      free(c8);
      return EXIT_SUCCESS;
    }

  return EXIT_FAILURE;
}


/*
 * Load a ROM in RAM
 *
 */

int c8_load(C8* c8, const char* filename)
{
  FILE* f;
  long fsize;
    
  if (c8 == NULL || filename == NULL)
    {
      return EXIT_FAILURE;
    }

  f = fopen(filename,"r");
  if (f == NULL)
    {
      return EXIT_FAILURE;
    }

  /* Get file size */
  fseek(f, 0L, SEEK_END);
  fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  /* Check size */
  if ( fsize > (C8_MEMORY_SIZE - C8_START_OFFSET) )
    {
      fclose(f);
      return EXIT_FAILURE;
    }
  
  /* Load ROM in memory */
  if ( fread(c8->memory+C8_START_OFFSET,fsize,1,f) != 1 )
    {
      fclose(f);
      return EXIT_FAILURE;
    }

  /* Set PC */
  c8->PC = (uint16_t*)(c8->memory+C8_START_OFFSET);
  
  fclose(f);  
  
  return EXIT_SUCCESS;
}


/*
 * Do a cycle
 *
 */

int c8_cycle(C8* c8)
{
  uint16_t nnn;
  uint8_t n,x,y,z,kk;
  
  if (c8==NULL)
    {
      return EXIT_FAILURE;
    }

  /* DEBUG
  *(c8->PC) = (uint16_t)0x25D5;
  c8->I = (uint16_t*)(c8->fonts+0xF*C8_FONT_SIZE);
  c8->V[5] = 63;
  c8->V[2] = 30;
  */
  
  z = (uint8_t)((htons(*c8->PC) & 0xF000)>>12);
  nnn = htons(*c8->PC) & 0x0FFF;
  n = (uint8_t)(nnn & 0x000F);
  kk = (uint8_t)(nnn & 0x00FF);
  y = ((kk & 0xF0)>>4);
  x = (uint8_t)((nnn & 0x0F00)>>8);

   switch(z)
    {
    case 0x0:
      {
	switch(nnn)
	  {
	  case 0x0E0:
	    {
	      /* CLS */
	      do_0x00E0(c8,nnn,n,x,y,kk);
	      break;
	    }
	  case 0x0EE:
	    {
	      /* RET */
	      do_0x00EE(c8,nnn,n,x,y,kk);
	      break;
	    }

	  default:
	    {
	      printf("Unknow 0x0 Instruction\n");
	      break;
	    }	    
	  }
	break;
      }
    case 0x1:
      {
        /* JMP */
	do_0x1nnn(c8,nnn,n,x,y,kk);
	break;
      }
    case 0x2:
      {
	/* CALL */
	do_0x2nnn(c8,nnn,n,x,y,kk);
	break;
      }
    case 0x3:
      {
	/* SE */
	do_0x3xkk(c8,nnn,n,x,y,kk);
	break;
      }
    case 0x4:
      {
	/* SNE */
	do_0x4xkk(c8,nnn,n,x,y,kk);
	break;
      }
    case 0x5:
      {
	/* SE V */
	do_0x5xy0(c8,nnn,n,x,y,kk);
	break;
      }
    case 0x6:
      {
	/* LD */
	do_0x6xkk(c8,nnn,n,x,y,kk);
	break;
      }
    case 0x7:
      {
	/* ADD */
	do_0x7xkk(c8,nnn,n,x,y,kk);
	break;
      }
     case 0x8:
      {
	/* Registers Ops */
	do_0x8xyn(c8,nnn,n,x,y,kk);
	break;
      }
    case 0x9:
      {
	/* SNE Vx, Vy */
	do_0x9xy0(c8,nnn,n,x,y,kk);
	break;
      }
    case 0xA:
      {
	/* LD I, nnn */
	do_0xAnnn(c8,nnn,n,x,y,kk);	
	break;
      }
    case 0xB:
      {
	/* JP V0+nnn */
	do_0xBnnn(c8,nnn,n,x,y,kk);
	break;
      }
    case 0xC:
      {
	/* RND */
	do_0xCxkk(c8,nnn,n,x,y,kk);
	break;
      }
    case 0xD:
      {
	/* DRW */
	do_0xDxyn(c8,nnn,n,x,y,kk);
	break;
      }
    case 0xE:
      {
	switch(kk)
	  {
	  case 0x9E:
	    {
	      /* SKP  Keyboard,Vx */
	      do_0xEx9E(c8,nnn,n,x,y,kk);
	      break;
	    }
	    
	  case 0xA1:
	    {
	      /* SKNP  Keyboard,Vx */
	      do_0xExA1(c8,nnn,n,x,y,kk);
	      break;
	    }

	  default:
	    {
	      printf("Unknow 0xE Instruction\n");
	      break;
	    }
	    
	  }
	break;
      }
    case 0xF:
      {
	do_0xFxkk(c8,nnn,n,x,y,kk);
	break;
      }
    default:
      {
	printf("Unknow Instruction\n");
	break;
      }
    }

  return EXIT_SUCCESS;
}


/*
 * Render screen
 *
 */

int c8_render(C8* c8)
{
  unsigned int x,y;
  
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  for( x=0 ; x<C8_SCREEN_WIDTH ; x++ )
    {
      for( y=0 ; y<C8_SCREEN_HEIGHT ; y++ )
	{
	  c8->screen[y*C8_SCREEN_WIDTH+x%C8_SCREEN_WIDTH] ? gfx_set(x,y) : gfx_unset(x,y);
	}
    }

  return gfx_render();
 
}
