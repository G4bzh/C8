/*
 * Screen
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "c8.h"
#include "screen.h"


/*
 * Initialisation
 *
 */


int screen_init(void)
{
  int width, height;
  
  initscr();

  getmaxyx(stdscr, height, width);	
  if ( (width <  C8_SCREEN_WIDTH) || (height <  C8_SCREEN_HEIGHT) )
    {
      endwin();
      printf("Need a %dx%d screen\n",C8_SCREEN_WIDTH,C8_SCREEN_HEIGHT);
      return EXIT_FAILURE;
    }
  
  noecho();
  
  return EXIT_SUCCESS;
}


/*
 * Screen End
 *
 */

int screen_end(void)
{
  endwin();

  return EXIT_SUCCESS;
}
  
