/*
 * Main
 *
 */

#include <stdlib.h>
#include <time.h>
#include "c8.h"
#include "gfx.h"
#include "keyboard.h"

#include <ncurses.h>

int main()
{
  C8* c8;
 
  srand (time(NULL));
  
  c8 = c8_create();
  c8_load(c8,"roms/INVADERS");
  gfx_init();

  while (c8_cycle(c8) == EXIT_SUCCESS)
    {
      
      c8_render(c8);
      c8_updateDT(c8);
      c8_updateST(c8);
      kb_getkey(c8,0);
    }

  gfx_end();
  c8_delete(c8);
  
  return 0;
}
