/*
 * GFX
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>
#include "c8.h"
#include "gfx.h"


/*
 * Initialisation
 *
 */


int gfx_init(void)
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
  cbreak();
  nodelay(stdscr,TRUE);
  
  return EXIT_SUCCESS;
}


/*
 * De-initialisation
 *
 */

int gfx_end(void)
{
  endwin();
  return EXIT_SUCCESS;
}


/*
 * Clear screen
 *
 */

int gfx_clear(void)
{
  clear();
  return EXIT_SUCCESS;
}


/*
 * Set a pixel on screen
 *
 */

int gfx_set(uint8_t x, uint8_t y)
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

int gfx_unset(uint8_t x, uint8_t y)
{
  if ( (x >= C8_SCREEN_WIDTH) || (y >= C8_SCREEN_HEIGHT) )
    {
      return EXIT_FAILURE;
    }

  mvaddch(y,x,' ');

  return EXIT_SUCCESS;				   
}


/*
 * Render
 *
 */

int gfx_render(void)
{
  refresh();
  return EXIT_SUCCESS;
}


/*
 * Beep
 *
 */

int gfx_beep(void)
{
  beep();
  return EXIT_SUCCESS;
}
