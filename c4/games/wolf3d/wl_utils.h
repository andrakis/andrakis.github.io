// WL_UTILS.H

#ifndef __WL_UTILS_H_
#define __WL_UTILS_H_

#include "wl_def.h"

#define SafeMalloc(s)    safe_malloc ((s),__FILE__,__LINE__)
#define FRACBITS         16

void     *safe_malloc (size_t size, const char *fname, uint32_t line);
fixed    FixedMul (fixed a, fixed b);
fixed    FixedDiv (fixed a, fixed b);

#if defined(C4IX) && defined(__c4_inttypes__)
// c4sdl: FixedMul is the game's hottest multiply; where the machine has
// the game's accelerators (c4/c4accel.h) it is one instruction, chosen
// where it stands. wl_utils.c's function, c4_FixedMul, is there for every
// other machine and until the game asks.
#include "c4/c4accel.h"
fixed    c4_FixedMul (fixed a, fixed b);
#define FixedMul(a, b) (WOLF_ACCEL() ? wolf_fixmul((a), (b)) : c4_FixedMul((a), (b)))
#endif

uint16_t ReadShort (void *ptr);
uint32_t ReadLong (void *ptr);

void     Error (const char *string);
void     Help (const char *string);

#endif
