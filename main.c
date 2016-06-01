/*
 * Main
 *
 */


#include "c8.h"
#include "screen.h"



int main()
{
  screen_init();
  screen_clear();
  screen_set(63,31);
  screen_unset(63,31);
  screen_end();
  return 0;
}
