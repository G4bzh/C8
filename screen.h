/*
 * Screen Header
 *
 */

#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdint.h>

int screen_init(void);
int screen_end(void);
int screen_clear(void);
int screen_set(uint8_t, uint8_t);
int screen_unset(uint8_t, uint8_t);

#endif
