/*
 *  CHIP 8 Emulator Header
 *
 */


#ifndef _C8_H_
#define _C8_H_

#include <stdint.h>

#define C8_STACK_SIZE       16
#define C8_SCREEN_SIZE      2048

#define C8_REGISTERS        16
#define C8_KEYS             16



typedef struct _C8
{
  uint8_t V[C8_REGISTERS];          /* General Purpose Registers (Vx) */
  uint16_t I;                       /* Memory Register */
  uint8_t delay;                    /* Delay Timer Register */
  uint8_t sound;                    /* Sound Timer Register */
  uint16_t PC;                      /* Progranm Counter */
  uint16_t stack[C8_STACK_SIZE];    /* Stack */
  uint8_t SP;                       /* Stack Pointer */
  uint8_t screen[C8_SCREEN_SIZE];   /* Display */
  uint8_t keyboard[C8_KEYS];        /* Keyboard */
  uint8_t* memory;                  /* RAM */
} C8;




#endif
