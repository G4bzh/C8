/*
 * Screen
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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
 * De-initialisation
 *
 */

int screen_end(void)
{
  endwin();
  return EXIT_SUCCESS;
}


/*
 * Clear screen
 *
 */

int screen_clear(void)
{
  clear();
  return EXIT_SUCCESS;
}


/*
 * Set a pixel on screen
 *
 */

int screen_set(uint8_t x, uint8_t y)
{
  if ( (x >= C8_SCREEN_WIDTH) || (y >= C8_SCREEN_HEIGHT) )
    {
      return EXIT_FAILURE;
    }

  mvaddch(y,x,' '|A_REVERSE);

  return EXIT_SUCCESS;				   
}


/*
 * Unset a pixel on screen
 *
 */

int screen_unset(uint8_t x, uint8_t y)
{
  if ( (x >= C8_SCREEN_WIDTH) || (y >= C8_SCREEN_HEIGHT) )
    {
      return EXIT_FAILURE;
    }

  mvaddch(y,x,' ');

  return EXIT_SUCCESS;				   
}
