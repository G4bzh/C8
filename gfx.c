/*
 * GFX
 *
 */

#include <stdint.h>
#include <ncurses.h>
#include "error.h"
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
      return ERR_BADDISPLAY;
    }
  
  noecho();
  cbreak();
  curs_set(0);


  return ERR_SUCCESS;
}


/*
 * De-initialisation
 *
 */

int gfx_end(void)
{
  endwin();
  return ERR_SUCCESS;
}


/*
 * Clear screen
 *
 */

int gfx_clear(void)
{
  clear();
  return ERR_SUCCESS;
}


/*
 * Set a pixel on screen
 *
 */

int gfx_set(uint8_t x, uint8_t y)
{
  if ( (x >= C8_SCREEN_WIDTH) || (y >= C8_SCREEN_HEIGHT) )
    {
      return ERR_COORDOUTOFRANGE;
    }

  mvaddch(y,x,' '|A_REVERSE);

  return ERR_SUCCESS;				   
}


/*
 * Unset a pixel on screen
 *
 */

int gfx_unset(uint8_t x, uint8_t y)
{
  if ( (x >= C8_SCREEN_WIDTH) || (y >= C8_SCREEN_HEIGHT) )
    {
      return ERR_COORDOUTOFRANGE;
    }

  mvaddch(y,x,' ');

  return ERR_SUCCESS;				   
}


/*
 * Render
 *
 */

int gfx_render(void)
{
  refresh();
  return ERR_SUCCESS;
}


/*
 * Beep
 *
 */

int gfx_beep(void)
{
  beep();
  return ERR_SUCCESS;
}
