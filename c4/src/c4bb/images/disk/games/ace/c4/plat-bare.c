// plat-bare.c -- Ace on the bare machine and under C4DOS: the display is
// the game's to take. Under grin, C4DOS's graphical shell, the display is
// grin's, and grin publishes a table in C4DOS's slot 25 while it has it
// (c4's docs/grin-plan.md 3.6): then the game plays in a window of grin's,
// and grin's loop runs in its polls. As games/tyrian/tyr-bare.c does. A
// grin whose table is version 6 or later gives that window what C4IX's
// desktop gives one (plat-c4ix.c): any size, each new one ACE_EV_SIZE, and
// a menu bar (c4's docs/grin.md 3.5); and the table is fitted to it as
// plat-c4ix.c fits it.

#include <stdlib.h>
#include <string.h>
#define C4IX_SHARED 1
#include "gui.h"
#undef C4IX_SHARED
#include "plat.h"

// grin's table (c4's src/grin/gkit.h): its first nine words
struct grin_table {
	int magic, version, gen;
	void *env;
	void (*hello)(void);
	int  (*fwin_open)(char *title, int w, int h, int flags);
	void (*fwin_frame)(char *pixels, int w, int h, int pitch, int *pal);
	int  (*fwin_poll)(int *ev);
	int  (*fwin_ctl)(int op, int n, char *s);           // version 6
};
// fwin_open's flags (2: the game has the mouse, the pointer free, for cards
// to be clicked; 4, version 6: any size), fwin_ctl's ops, fwin_poll's
// events beyond gui.h's (which become plat.h's ACE_EV_MENU and ACE_EV_SIZE)
enum { FW_CLICK = 2, FW_RESIZE = 4, FWC_MENU = 1, FWC_ITEM = 2, FW_EV_MENU = 100, FW_EV_SIZE = 101 };
extern int *__c4dos_api;                // bare.c's: C4DOS's table, 0 on the bare machine

static struct grin_table *grin(void) {
	struct grin_table *t;
	if (!__c4dos_api || __c4dos_api[0] != 4404292 || __c4dos_api[5] < 4) return 0;
	t = (struct grin_table *) __c4dos_api[25];
	return t && t->magic == 1196575054 && t->version >= 2 ? t : 0;
}

static struct grin_table *g;
static int v6;

int  ace_take_display(void) { return !grin(); }
void ace_give_display(void) {}
// no desktop here: grin's window is had where ace_take_display says no
int  ace_win_here(void) { return 0; }

// In a window of any size (version 6), as plat-c4ix.c: grin stretches what
// it is given to the window, so the table goes in the middle of a frame the
// window's own shape, on the table's colour (index 0), and its cards keep
// theirs -- a frame of the window's size where the table fits, or a whole
// part of it where it fits that many times over (grin scales it up), or as
// big as the table needs where it does not (grin scales it down). Grin
// copies each frame at once, so it goes as soon as it is drawn.
static char *frame;
static int fr_w, fr_h, ox, oy;
static int canvas_w, canvas_h;          // the window's inside, as grin last said

static int frame_for(int w, int h) {
	int fw, fh, k;
	k = 1;
	while ((k + 1) * w <= canvas_w && (k + 1) * h <= canvas_h) k++;
	fw = canvas_w / k;
	fh = canvas_h / k;
	if (k == 1) {
		if (w > fw) fw = w;
		if (h * canvas_w > fw * canvas_h) fw = (h * canvas_w + canvas_h - 1) / canvas_h;
		fh = fw * canvas_h / canvas_w;
		if (fh < h) fh = h;
	}
	if (frame && fw == fr_w && fh == fr_h) return 1;
	if (frame) free(frame);
	if (!(frame = (char *) calloc(fw * fh, 1))) return 0;
	fr_w = fw; fr_h = fh;
	return 1;
}

// grin's window, the table's size to begin with
int  ace_win_open(char *title, int w, int h) {
	if (!(g = grin())) return 0;
	v6 = g->version >= 6;
	canvas_w = w; canvas_h = h;
	return g->fwin_open(title, w, h, v6 ? FW_CLICK | FW_RESIZE : FW_CLICK);
}
void ace_win_frame(char *pixels, int w, int h, int pitch, int *pal) {
	int y;
	if (!g) return;
	if (!v6 || !frame_for(w, h)) { g->fwin_frame(pixels, w, h, pitch, pal); ox = 0; oy = 0; return; }
	if (fr_w != w || fr_h != h) memset(frame, 0, fr_w * fr_h);
	ox = (fr_w - w) / 2;
	oy = (fr_h - h) / 2;
	for (y = 0; y < h; y++)
		memcpy(frame + (y + oy) * fr_w + ox, pixels + y * pitch, w);
	g->fwin_frame(frame, fr_w, fr_h, fr_w, pal);
}
// grin's events, the mouse in the table's pixels (grin gives the frame's);
// FW_EV_MENU and FW_EV_SIZE as ACE_EV_MENU and ACE_EV_SIZE
int  ace_win_poll(int *ev) {
	int k;
	if (!g) return 0;
	while (1) {
		if ((k = g->fwin_poll(ev)) <= 0) return k;
		if (ev[0] == FW_EV_MENU) { ev[0] = ACE_EV_MENU; return 1; }
		if (ev[0] == FW_EV_SIZE) {
			if (ev[1] <= 0 || ev[2] <= 0 || (ev[1] == canvas_w && ev[2] == canvas_h)) continue;
			canvas_w = ev[1]; canvas_h = ev[2];
			ev[0] = ACE_EV_SIZE;
			return 1;
		}
		if (ev[0] == GUI_EV_DOWN || ev[0] == GUI_EV_UP || ev[0] == GUI_EV_MOVE) { ev[1] = ev[1] - ox; ev[2] = ev[2] - oy; }
		return 1;
	}
}
void ace_win_close(void) {}
// grin's window's menu bar (version 6)
void ace_win_menu(int n, char *title) { if (g && v6) g->fwin_ctl(FWC_MENU, n, title); }
void ace_win_item(int n, char *label) { if (g && v6) g->fwin_ctl(FWC_ITEM, n, label); }

int  ace_plat_ms(void) { return __time(); }
void ace_plat_sleep(int ms) { if (ms) __c4_usleep(ms * 1000); }
void ace_wait(int ms, int *ring) { (void) ring; __c4_usleep(ms * 1000); }
