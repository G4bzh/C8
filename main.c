/*
 * Main
 *
 */


#include "c8.h"
#include "gfx.h"



int main()
{
  gfx_init();
  gfx_clear();
  gfx_set(63,31);
  gfx_unset(63,31);
  gfx_end();
  return 0;
}
