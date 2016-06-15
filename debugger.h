/*
 * Debugger Header
 *
 */


#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include <stdint.h>
#include "c8.h"


int dbg_init(void);
void dbg_run(C8*, uint8_t);


#endif
