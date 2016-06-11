/*
 * Keyboard Header
 *
 */

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "c8.h"

int kb_getkey_nonblocking(C8*);
int kb_getkey_blocking(C8*);

#endif
