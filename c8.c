/*
 *  CHIP 8 Emulator
 *
 */


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
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
	      printf("CLS\n");
	      break;
	    }
	  case 0x0EE:
	    {
	      printf("RET\n");
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
	printf("JMP 0x%04x\n",nnn);
	break;
      }
    case 0x2:
      {
	printf("CALL 0x%04x\n",nnn);
	break;
      }
    case 0x3:
      {
	printf("SE V[0x%02x], 0x%02x\n",x,kk);
	break;
      }
    case 0x4:
      {
	printf("SNE V[0x%02x], 0x%02x\n",x,kk);
	break;
      }
    case 0x5:
      {
	printf("SE V[0x%02x], V[0x%02x]\n",x,y);
	break;
      }
    case 0x6:
      {
	printf("LD V[0x%02x], 0x%02x\n",x,kk);
	break;
      }
    case 0x7:
      {
	printf("ADD V[0x%02x], 0x%02x\n",x,kk);
	break;
      }
     case 0x8:
      {
	switch(n)
	  {
	  case 0x0:
	    {
	      printf("LD V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }

	  case 0x1:
	    {
	      printf("OR V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }

	  case 0x2:
	    {
	      printf("AND V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }	    

	  case 0x3:
	    {
	      printf("XOR V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }

	  case 0x4:
	    {
	      printf("ADD V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }	    

	  case 0x5:
	    {
	      printf("SUB V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }

	  case 0x6:
	    {
	      printf("SHR V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }	   

	  case 0x7:
	    {
	      printf("SUBN V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }

	  case 0xE:
	    {
	      printf("SHL V[0x%02x], V[0x%02x]\n",x,y);
	      break;
	    }

	  default:
	    {
	      printf("Unknow 0x8 Instruction\n");
	      break;
	    }	    
	    
	  }
	break;
      }
    case 0x9:
      {
	printf("SNE V[0x%02x], V[0x%02x]\n",x,y);
	break;
      }
    case 0xA:
      {
	printf("LD I, 0x%04x\n",nnn);
	break;
      }
    case 0xB:
      {
	printf("JP V[0], 0x%04x\n",nnn);	
	break;
      }
    case 0xC:
      {
	printf("RND V[0x%02x], 0x%02x\n",x,kk); 
	break;
      }
    case 0xD:
      {
	printf("DRW  V[0x%02x],  V[0x%02x], 0x%02x\n",x,y,n);
	break;
      }
    case 0xE:
      {
	switch(kk)
	  {
	  case 0x9E:
	    {
	      printf("SKP  V[0x%02x]\n",x);
	      break;
	    }
	    
	  case 0xA1:
	    {
	      printf("SKNP  V[0x%02x]\n",x);
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
	switch(kk)
	  {
	  case 0x07:
	    {
	      printf("LD  V[0x%02x], DT\n",x);
	      break;
	    }

	  case 0x0A:
	    {
	      printf("LD  V[0x%02x], K\n",x);
	      break;
	    }

	  case 0x15:
	    {
	      printf("LD  DT, V[0x%02x]\n",x);
	      break;
	    }
	    
	  case 0x18:
	    {
	      printf("LD  ST,V[0x%02x]\n",x);
	      break;
	    }

	  case 0x1E:
	    {
	      printf("ADD I, V[0x%02x]\n",x);
	      break;
	    }

	  case 0x29:
	    {
	      printf("LD F, V[0x%02x]\n",x);
	      break;
	    }

	  case 0x33:
	    {
	      printf("LD B, V[0x%02x]\n",x);
	      break;
	    }

	  case 0x55:
	    {
	      printf("LD [I], V[0x%02x]\n",x);
	      break;
	    }	    

	  case 0x65:
	    {
	      printf("LD V[0x%02x], [I]\n",x);
	      break;
	    }

	  default:
	    {
	      printf("Unknow 0xF Instruction\n");
	      break;
	    }
	    
	  }
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

