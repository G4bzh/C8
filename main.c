/*
 * Main
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "error.h"
#include "c8.h"
#include "gfx.h"
#include "keyboard.h"
#include "debugger.h"



#define C8_OPBYCYCLE   5



int main(int argc, char* argv[])
{
  C8* c8;
  int ret, op;
  uint8_t debug= 0;
  
  if (argc < 2) 
    {
      printf("Usage %s rom \n",argv[0]);
      return 0;
    }

  if ( (argc == 3) && (argv[2][0] == '-') && (argv[2][1] == 'd') )
    {
      debug = 1;
    }

  srand (time(NULL));
  
  c8 = c8_create();
  if (c8 == NULL)
    {
      printf("Fail to create emulator \n");
      return -1;
    }
  
  if ( (ret=c8_load(c8,argv[1])) != ERR_SUCCESS )
    {
      goto err0;
    }

  if ( (ret=gfx_init()) != ERR_SUCCESS )
    {
      goto err0;
    }

  if (debug)
    {
      if ( (ret=dbg_init()) != ERR_SUCCESS )
	{
	  goto err1;
	}
    }

  op=0;
  while ((ret=c8_cycle(c8)) == ERR_SUCCESS)
    {
      if (debug)
	{
	  dbg_run(c8,0);
	}
      
      if (c8->draw)
	{
	  c8_render(c8);
	  c8->draw = 0;
	}

      op ++;
      if (op > C8_OPBYCYCLE)
	{
	  c8_updateDT(c8);
	  c8_updateST(c8);
	  op=0;
	}
      
      kb_getkey(c8,0);
    }


 err1:
  
  gfx_end();

 err0:
  
  c8_delete(c8);
  
  err_tostr(ret);
  
  return (ret == ERR_SUCCESS);
}
