/*
 * Main
 *
 */

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "error.h"
#include "c8.h"
#include "gfx.h"
#include "keyboard.h"
#include "debugger.h"

#define C8_OPBYCYCLE   5

int main()
{
  C8* c8;
  int ret, op;
  
  srand (time(NULL));
  
  c8 = c8_create();
  c8_load(c8,"roms/INVADERS");

  if ( (ret=gfx_init()) != ERR_SUCCESS )
    {
      c8_delete(c8);
      err_tostr(ret);
      return -1;
    }
  
  if ( (ret=dbg_init()) != ERR_SUCCESS )
    {
      err_tostr(ret);
      c8_delete(c8);
      return -1;     
    }

  op=0;
  while ((ret=c8_cycle(c8)) == ERR_SUCCESS)
    {
      // dbg_run(c8,0);
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
  
  gfx_end();
  c8_delete(c8);
  
  err_tostr(ret);
  
  return 0;
}
