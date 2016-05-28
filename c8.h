/*
 *  CHIP 8 Emulator Header
 *
 */


#ifndef _C8_H_
#define _C8_H_

#include <stdint.h>

#define MEMORY_SIZE      4096
#define ROM_SIZE         512
#define STACK_SIZE       16
#define SCREEN_SIZE      2048

#define SCREEN_WIDTH     64
#define SCREEN_HEIGHT    32

#define START_OFFSET     0x200
#define START_OFFSET_ETI 0x600
 
#define N_REGISTERS      16




typedef struct _C8
{
  uint8_t V[N_REGISTERS];      /* General Purpose Registers (Vx) */
  uint16_t I;                  /* Memory Register */
  uint8_t delay;               /* Delay Timer Register */
  uint8_t sound;               /* Sound Timer Register */
  uint16_t PC;                 /* Progranm Counter */
  uint16_t stack[STACK_SIZE];  /* Stack */
  uint8_t SP;                  /* Stack Pointer */
  uint8_t screen[SCREEN_SIZE]; /* Display */
} C8;




#endif
