/*
 * Main
 *
 */

#include <stdlib.h>
#include <time.h>
#include "error.h"
#include "c8.h"
#include "gfx.h"
#include "keyboard.h"


int main()
{
  C8* c8;
  int ret;
  
  srand (time(NULL));
  
  c8 = c8_create();
  c8_load(c8,"roms/INVADERS");
  gfx_init();

  while ((ret=c8_cycle(c8)) == ERR_SUCCESS)
    {
      
      c8_render(c8);
      c8_updateDT(c8);
      c8_updateST(c8);
      kb_getkey(c8,0);
    }

  gfx_end();
  c8_delete(c8);

  err_tostr(ret);
  
  return 0;
}
