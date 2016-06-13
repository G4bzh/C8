/*
 *  CHIP 8 Emulator Header
 *
 */


#ifndef _C8_H_
#define _C8_H_

#include <stdint.h>

#define C8_STACK_SIZE       16
#define C8_SCREEN_SIZE      2048
#define C8_SCREEN_WIDTH     64   /* pixels */
#define C8_SCREEN_HEIGHT    32   /* pixels */

#define C8_REGISTERS        16
#define C8_KEYS             16



typedef struct _C8
{
  uint8_t V[C8_REGISTERS];          /* General Purpose Registers (Vx) */
  uint16_t* I;                      /* Memory Register */
  uint8_t DT;                       /* Delay Timer Register */
  uint8_t ST;                       /* Sound Timer Register */
  uint16_t* PC;                     /* Program Counter */
  uint16_t* stack[C8_STACK_SIZE];   /* Stack */
  uint8_t SP;                       /* Stack Pointer */
  uint8_t screen[C8_SCREEN_SIZE];   /* Display */
  uint8_t keyboard[C8_KEYS];        /* Keyboard */
  uint8_t* fonts;                   /* Hexa fonts */
  uint8_t* memory;                  /* RAM */
} C8;


C8* c8_create(void);
int c8_delete(C8*);
int c8_load(C8*, const char*);
int c8_cycle(C8*);
int c8_render(C8*);

#endif
