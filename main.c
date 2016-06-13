/*
 * Main
 *
 */

#include <stdlib.h>
#include <time.h>
#include "c8.h"
#include "gfx.h"
#include "keyboard.h"



int main()
{
  C8* c8;
 
  srand (time(NULL));

  
  c8 = c8_create();


  
  c8_load(c8,"roms/LOGO");
  gfx_init();

  gfx_clear();

  c8_cycle(c8);

  c8_render(c8);

  kb_getkey(c8,1);

  
  gfx_end();
  c8_delete(c8);
  
  return 0;
}
