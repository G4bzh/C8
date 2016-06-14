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
#include <ncurses.h>

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
  c8->SP = 0;
  
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
  int ret;
  
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

  printw("PC = 0x%x ;", htons(*c8->PC) );
  printw("z = 0x%x ;", z );
  printw("nnn = 0x%x ;", nnn );
  printw("n = 0x%x ;", n );
  printw("kk = 0x%x ;", kk );
  printw("y = 0x%x ;", y );
  printw("x = 0x%x \n", x );

  if (c8->I) {printw("I = 0x%x ;", htons(*c8->I));}
  printw("V0 = 0x%x ;", c8->V[0]);
  printw("V1 = 0x%x ;", c8->V[1] );
  printw("V2 = 0x%x ;", c8->V[2] );
  printw("v3 = 0x%x ;", c8->V[3] );
  printw("V4 = 0x%x ;", c8->V[4] );
  printw("V5 = 0x%x ;", c8->V[5] );
  printw("V6 = 0x%x ;", c8->V[6] );
  printw("V7 = 0x%x ;", c8->V[7]);
  printw("V8 = 0x%x ;", c8->V[8] );
  printw("V9 = 0x%x ;", c8->V[9] );
  printw("vA = 0x%x ;", c8->V[10] );
  printw("VB = 0x%x ;", c8->V[11] );
  printw("VC = 0x%x ;", c8->V[12] );
  printw("VD = 0x%x ;", c8->V[13] );
  printw("VE = 0x%x ;", c8->V[14] );
  printw("VF = 0x%x \n", c8->V[15] );

  
  switch(z)
    {
    case 0x0:
      {
	switch(nnn)
	  {
	  case 0x0E0:
	    {
	      /* CLS */
	      ret = do_0x00E0(c8,nnn,n,x,y,kk);

	      if (ret == EXIT_FAILURE)
		{
		  printw("0x00E0");
		  gfx_render();     
		  for(;;){}
		}

	      
	      break;
	    }
	  case 0x0EE:
	    {
	      /* RET */
	      ret = do_0x00EE(c8,nnn,n,x,y,kk);

	      if (ret == EXIT_FAILURE)
		{
		  printw("0x00EE");
		  gfx_render();     
		  for(;;){}
		}
	      
	      break;
	    }

	  default:
	    {
	      printw("Unknow 0x0 Instruction\n");
	      ret = EXIT_FAILURE;
	      break;
	    }	    
	  }
	break;
      }
    case 0x1:
      {
        /* JMP */
	ret = do_0x1nnn(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0x1");
	    gfx_render();     
	    for(;;){}
	  }

	
	break;
      }
    case 0x2:
      {
	/* CALL */
	ret = do_0x2nnn(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0x2");
	    gfx_render();     
	    for(;;){}
	  }

	
	break;
      }
    case 0x3:
      {
	/* SE */
	ret = do_0x3xkk(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0x3");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    case 0x4:
      {
	/* SNE */
	ret = do_0x4xkk(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0x4");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    case 0x5:
      {
	/* SE V */
	ret = do_0x5xy0(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0x5");
	    gfx_render();     
	    for(;;){}
	  }

	
	break;
      }
    case 0x6:
      {
	/* LD */
	ret = do_0x6xkk(c8,nnn,n,x,y,kk);


	if (ret == EXIT_FAILURE)
	  {
	    printw("0x6");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    case 0x7:
      {
	/* ADD */
	ret = do_0x7xkk(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0x7");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
     case 0x8:
      {
	/* Registers Ops */
	ret = do_0x8xyn(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0x8");
	    gfx_render();     
	    for(;;){}
	  }

	
	break;
      }
    case 0x9:
      {
	/* SNE Vx, Vy */
	ret = do_0x9xy0(c8,nnn,n,x,y,kk);


	if (ret == EXIT_FAILURE)
	  {
	    printw("0x9");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    case 0xA:
      {
	/* LD I, nnn */
	ret = do_0xAnnn(c8,nnn,n,x,y,kk);


	if (ret == EXIT_FAILURE)
	  {
	    printw("0xA");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    case 0xB:
      {
	/* JP V0+nnn */
	ret = do_0xBnnn(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0xB");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    case 0xC:
      {
	/* RND */
	ret = do_0xCxkk(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0xC");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    case 0xD:
      {
	/* DRW */
	ret = do_0xDxyn(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0xD");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    case 0xE:
      {
	switch(kk)
	  {
	  case 0x9E:
	    {
	      /* SKP  Keyboard,Vx */
	      ret = do_0xEx9E(c8,nnn,n,x,y,kk);

	      if (ret == EXIT_FAILURE)
		{
		  printw("0xE09E");
		  gfx_render();     
		  for(;;){}
		}
	      
	      break;
	    }
	    
	  case 0xA1:
	    {
	      /* SKNP  Keyboard,Vx */
	      ret = do_0xExA1(c8,nnn,n,x,y,kk);

	      if (ret == EXIT_FAILURE)
		{
		  printw("0xE0A1");
		  gfx_render();     
		  for(;;){}
		}
	      
	      break;
	    }

	  default:
	    {
	      printw("Unknow 0xE Instruction\n");
	      ret = EXIT_FAILURE;
	      break;
	    }
	    
	  }
	break;
      }
    case 0xF:
      {
	ret = do_0xFxkk(c8,nnn,n,x,y,kk);

	if (ret == EXIT_FAILURE)
	  {
	    printw("0xF");
	    gfx_render();     
	    for(;;){}
	  }
	
	break;
      }
    default:
      {
	printw("Unknow Instruction\n");
	ret = EXIT_FAILURE;
	break;
      }
    }
  
  
  if (ret == EXIT_FAILURE)
    {
      printw("0x00E0");
      gfx_render();     
      for(;;){}
    }
  
  return ret;
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



/*
 * Update Delay Timer
 *
 */

int c8_updateDT(C8* c8)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if (c8->DT)
    {
      c8->DT--;
    }
  
  return EXIT_SUCCESS;
}


/*
 * Update Sound Timer
 *
 */

int c8_updateST(C8* c8)
{
  if (c8 == NULL)
    {
      return EXIT_FAILURE;
    }

  if (c8->ST)
    {
      c8->ST--;

      /* Beep if we reach 0 */
      if (!(c8->ST--))
	{
	  gfx_beep(); 
	}
    }

  
  return EXIT_SUCCESS;
}
