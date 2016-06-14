/*
 * Error Header
 *
 */

#ifndef _ERROR_H_
#define _ERROR_H_

#define ERR_SUCCESS          0
#define ERR_NULL             1
#define ERR_NIL              2
#define ERR_STACKOVERFLOW    3
#define ERR_REGOUTOFRANGE    4
#define ERR_BADINST          5
#define ERR_KEYOUTOFRANGE    6
#define ERR_BADDISPLAY       7
#define ERR_COORDOUTOFRANGE  8
#define ERR_TOOBIG           9
#define ERR_READFILE         10

void err_tostr(int);


#endif
