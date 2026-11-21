/* c4accel.h -- c4sdl: Wolfenstein 3D's accelerators, c4/accel.mjs, from
   the game's side (c4's libjs/guest/accel.h, docs/accel.md). On a machine
   that has them, with the Control menu's Accelerated on, the host runs
   these in the game's own JavaScript, one instruction each; elsewhere, and
   in gcc's build, the C runs as before. wolf_accel is the first of the
   game's numbers (0 for none, -1 until asked: wl_draw.c); WOLF_ACCEL() asks
   once. The numbers are the module's operations in its order. */
#ifndef C4ACCEL_H
#define C4ACCEL_H

enum { WA_POST, WA_LINE, WA_SUM, WA_FIXMUL, WA_BLIT };

extern int wolf_accel;
int wolf_accel_base(void);
int wolf_accel_avail(void);      /* the machine has them */
void wolf_accel_set(int on);     /* the menu's switch */
extern int wolf_accel_on;        /* Accelerated, kept in the config */
#define WOLF_ACCEL() (wolf_accel >= 0 ? wolf_accel : wolf_accel_base())

#ifdef __c4_inttypes__
#include "accel.h"
#define WA_OP(op) (wolf_accel + (op))
/* wl_draw.c's ScalePost: wh is wallheight[postx], tsize TEXTURESIZE */
#define wolf_post(wh, vbuf, pitch, postx, centery, vh, src, tsize) \
	__c4_opcode((wh), (vbuf), (pitch), (postx), (centery), (vh), (src), (tsize), WA_OP(WA_POST))
/* wl_scale.c's ScaleLine, every segment of a sprite's column */
#define wolf_line(x, toppix, fracstep, linesrc, linecmds, vbuf, ylookup, pitch, vh) \
	__c4_opcode((x), (toppix), (fracstep), (linesrc), (linecmds), (vbuf), (ylookup), (pitch), (vh), WA_OP(WA_LINE))
/* c4sdl.c's checksum of a timedemo's frame and its colours, from sum */
#define wolf_sum(sum, pixels, w, h, pitch, pal) \
	__c4_opcode((sum), (pixels), (w), (h), (pitch), (pal), WA_OP(WA_SUM))
/* wl_utils.c's FixedMul */
#define wolf_fixmul(a, b) __c4_opcode((a), (b), WA_OP(WA_FIXMUL))
/* id_vl.c's VL_MemToScreenScaledCoord and VL_MemToScreenScaledCoord2 */
#define wolf_blit(source, origwidth, srcx, srcy, width, height, dest, ylookup, destx, desty, scale) \
	__c4_opcode((source), (origwidth), (srcx), (srcy), (width), (height), (dest), (ylookup), (destx), (desty), \
		(scale), WA_OP(WA_BLIT))
#else
#define accel_find(name) 0
#define wolf_post(wh, vbuf, pitch, postx, centery, vh, src, tsize) 0
#define wolf_line(x, toppix, fracstep, linesrc, linecmds, vbuf, ylookup, pitch, vh) 0
#define wolf_sum(sum, pixels, w, h, pitch, pal) 0
#define wolf_fixmul(a, b) 0
#define wolf_blit(source, origwidth, srcx, srcy, width, height, dest, ylookup, destx, desty, scale) 0
#endif

#endif
