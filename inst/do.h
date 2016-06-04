/*
 * Instructions Header
 *
 */


#ifndef _DO_H_
#define _DO_H_


#include <stdint.h>
#include "../c8.h"

int do_0x00E0(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk);
int do_0x00EE(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk);
int do_0x1nnn(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk);
int do_0x3xkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk);
int do_0x4xkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk);
int do_0x5xy0(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk);
int do_0x6xkk(C8* c8, uint16_t nnn,  uint8_t n, uint8_t  x, uint8_t y, uint8_t kk);

#endif
