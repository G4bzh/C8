/*
 * GFX Header
 *
 */

#ifndef _GFX_H_
#define _GFX_H_

#include <stdint.h>

int gfx_init(void);
int gfx_end(void);
int gfx_clear(void);
int gfx_set(uint8_t, uint8_t);
int gfx_unset(uint8_t, uint8_t);
int gfx_render(void);
int gfx_beep(void);

#endif
