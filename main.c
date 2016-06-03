/*
 * Main
 *
 */


#include "c8.h"
#include "gfx.h"



int main()
{
  C8* c8;
  int i;
  
  c8 = c8_create();
  
  gfx_init();
  gfx_clear();

  for(i=0;i<C8_SCREEN_SIZE;i++)
    {
      c8->screen[i] = i%2?1:0;
    }
  c8_render(c8);
  
  gfx_end();
  return 0;
}
