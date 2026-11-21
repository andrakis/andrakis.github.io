// winkit.h -- the window kit: windows, their chrome, widgets and the
// accessories, written once and built into C4IX's desktop and into grin
// (docs/grin-plan.md, 3.4 and 3.5).
//
//   draw.c      the d_* drawing layer over gui.h: the origin and clip of
//               what is being drawn, damage, colour schemes, bevels, icons
//   ui.c        widgets, stateless, drawn through d_*
//   wmcore.c    windows: the list, z-order, focus, modality, dragging and
//               sizing, menu bars and drop-downs, timers, the clipboard,
//               events, and each window's class called for what is its
//   dialog.c    message, input and file boxes
//   look95.c    window chrome: the Flat and Classic looks
//   look31.c    window chrome: the Windows 3.1 look
//   textgrid.c  a VT100 text grid, its scrollback and line editor (textgrid.h)
//   savers.c    screen savers
//   calc.c, notepad.c, clock.c   the accessories, each a class
//
// A shell (C4IX's desktop/, grin) owns the display and the main loop. It
// attaches the display, calls wk_init, then each pass hands every event
// to wk_event, calls wk_tick and wk_redraw. What the shell draws itself --
// the desktop under the windows, a taskbar over them -- it gives the kit
// as hooks (struct wk_shell). Windows are numbered (int handles that are
// never reused), and each belongs to a class: a table of what to call
// for drawing, the mouse, keys, menus, timers and dialog answers.
//
// Everything here compiles under c4lc on the host and c4sc inside C4IX:
// function-pointer tables, designated initialisers, and no sizeof(struct)
// in a constant (a class's size is set at run time).

#ifndef WINKIT_H
#define WINKIT_H 1

// the largest screen the kit lays out for (arrays sized by it), a path,
// and the window chrome's measures, which every look shares
enum { WK_MAX_W = 1280, WK_MAX_H = 1024, WK_PATH = 256, WK_NAME = 64 };
enum { BORDER = 4, TITLE_H = 18, MENU_H = 20 };

// ---- what the kit and its windows share -----------------------------------
//
// The screen's size, the area windows keep to, the look, the modifiers
// held, and the colour scheme. One struct, so that grin's applications,
// which reach the kit through a table (3.4), can find it through one
// pointer.
struct wk_env {
    int sw, sh;                       // the screen now (gui_size, GUI_EV_RESIZE)
    int ax, ay, aw, ah;               // where windows go: the screen less a taskbar
    int style;                        // the look: S_FLAT, S_CLASSIC, S_WIN31
    int mods;                         // Shift, Ctrl, Alt as the last key left them
    int desk, face, light, shadow;    // the scheme's colours (Settings)
    int title, title2, ititle, ititle2, sel;
    int fsans, fbold, fsize;          // the interface's font (wk_font_use): F_SANS's, F_BOLD's, a size step
};
// A grin application (compiled with -D WK_IMPORT, src/grin/import.c) has
// no wk of its own: it reads grin's, through the pointer grin publishes
// in its table, so that every C_FACE below is a load through it.
#ifdef WK_IMPORT
extern struct wk_env *wk_import_env;
#define wk (*wk_import_env)
#else
extern struct wk_env wk;
#endif

// colours: these never change...
enum { C_DARK = 0x000000, C_WHITE = 0xffffff, C_GREEN = 0x00ff00 };
// ... and these are the scheme's
#define C_DESK    (wk.desk)
#define C_FACE    (wk.face)
#define C_LIGHT   (wk.light)
#define C_SHADOW  (wk.shadow)
#define C_TITLE   (wk.title)
#define C_TITLE2  (wk.title2)
#define C_ITITLE  (wk.ititle)
#define C_ITITLE2 (wk.ititle2)
#define C_SEL     (wk.sel)

// the looks: flat outlines and solid title bars, bevels and gradients,
// or Windows 3.1's chrome (with Classic's bevels)
enum { S_FLAT = 0, S_CLASSIC = 1, S_WIN31 = 2, N_STYLES = 3 };
#define ui_style (wk.style)

// fonts: monospace, a UI face, and its bold; then the display's other
// faces (gui.h's GUI_* fonts), for a choice of them
enum { F_MONO = 0, F_SANS = 1, F_BOLD = 2, F_COURIER = 3, F_LUCIDA = 4,
       F_VERDANA = 5, F_VERDANA_B = 6, F_SERIF = 7, F_SERIF_B = 8 };
// The choices offered (draw.c): faces for the interface, which d_text and
// d_textn then draw F_SANS and F_BOLD in; fixed-width faces for an
// editor; and sizes, Small, Normal and Large. The interface's size moves
// F_SANS and F_BOLD a pixel down or up; an editor's is a text grid's.
enum { WK_FACES = 3, WK_SIZES = 3 };
char *wk_face_name(int i);            // the interface's faces: "Tahoma", "Verdana", "Georgia"
char *wk_mono_name(int i);            // the fixed-width faces: "Consolas", "Courier New", "Lucida Console"
int   wk_mono_font(int i);            // ... as a font for d_textn
char *wk_size_name(int i);
void  wk_font_use(int face, int size);  // the interface's face and size, from now on
void  wk_grid(int size, int *font_size, int *cw, int *ch);   // a text grid's: its font's size, a cell
// bevel styles
enum { B_RAISED = 1, B_SUNKEN = 2, B_FIELD = 3, B_PRESSED = 4, B_ETCHED = 5 };
// mouse events, in client coordinates
enum { E_DOWN = 1, E_UP = 2, E_MOVE = 3, E_DBL = 4, E_WHEEL = 5 };
// keys (browser keyCodes) and modifiers
enum { KEY_BACK = 8, KEY_TAB = 9, KEY_ENTER = 13, KEY_ESC = 27, KEY_PGUP = 33, KEY_PGDN = 34,
       KEY_END = 35, KEY_HOME = 36, KEY_LEFT = 37, KEY_UP = 38, KEY_RIGHT = 39, KEY_DOWN = 40,
       KEY_INS = 45, KEY_DEL = 46, KEY_F2 = 113, KEY_F3 = 114, KEY_F4 = 115, KEY_F5 = 116 };
enum { M_SHIFT = 1, M_CTRL = 2, M_ALT = 4 };
// pointer shapes, GUI_PTR_*'s numbers (PTR_COLS: a splitter's, left and right;
// PTR_LOCK: "click to capture", the mouse locked to the display at a click)
enum { PTR_ARROW = 0, PTR_TEXT = 1, PTR_RESIZE = 2, PTR_LOCK = 8, PTR_COLS = 9 };
// 16x16 icons (d_icon), which a class names by its kind; the numbers are
// the C4IX desktop's window kinds
enum { ICON_TERM = 1, ICON_INFO = 2, ICON_FILES = 3, ICON_TASKS = 4, ICON_NOTE = 5,
       ICON_CALC = 6, ICON_MSG = 7, ICON_INPUT = 8, ICON_EDIT = 9, ICON_SETTINGS = 10,
       ICON_CLOCK = 11, ICON_FILEBOX = 12 };          // (the dialogs are drawn with none)

// ---- classes ----------------------------------------------------------------
//
// What a window's code sees. Every hook may be 0, and the kit checks
// before calling. Coordinates are the client area's.
struct wk_class {
    int size;                         // bytes of per-window state, zeroed (set at run time)
    int kind;                         // the shell's number for the class, and its icon
    int pointer_shape;                // PTR_* over the client area, unless pointer says
    void (*open)(int w, char *arg);   // just opened (wk_open's arg)
    void (*draw)(int w, int cw, int ch, int focused);
    void (*mouse)(int w, int ev, int x, int y, int button);   // E_WHEEL: button is the steps
    void (*key)(int w, int down, int code, int ch, int mods);
    void (*command)(int w, int id);                           // a menu item: WK_CMD(menu, item)
    void (*timer)(int w, int id);
    void (*answer)(int w, int dialog, int result);            // a dialog it asked closed
    int  (*close)(int w);             // asked to close (its close box, Alt+F4): 0 vetoes
    void (*destroy)(int w);           // closing: free what it holds
    int  (*pointer)(int w, int x, int y);                     // PTR_* there
    void (*idle)(int w);              // every pass of the loop (a pipe to read)
    void (*drawn)(int w);             // a frame with it in has been shown
};

// a menu bar: titles, and for each an array of items ending in 0 ("-" a
// separator); an item chosen reaches command as WK_CMD(menu, item)
struct wk_menu { char *title; char **items; };
// an item whose first byte is WK_CHECKED is drawn with a check mark beside
// it, and without that byte ("-" is a separator)
enum { WK_CHECKED = 1 };
enum { WK_CMD_STEP = 256, WK_POPUP = 200 };
#define WK_CMD(m, i) ((m) * WK_CMD_STEP + (i))

// wk_open's flags
enum { WK_FIXED = 1,                  // not resizable
       WK_DIALOG = 2,                 // a dialog's chrome (no icon, no minimise); modal
       WK_CENTER = 4 };               // centred on the screen, a little high
// message box buttons, and what an answer's result means
enum { WK_OK = 0, WK_YESNO = 1, WK_OKCANCEL = 2 };
enum { WK_NO = 0, WK_YES = 1 };       // also Cancel and OK

// ---- windows ----------------------------------------------------------------
int   wk_open(struct wk_class *c, char *title, int w, int h, int flags, char *arg);  // -1: no memory
void  wk_close(int w);                // at once (destroy), whatever close would say
void  wk_ask_close(int w);            // as the close box does: close may veto
void *wk_state(int w);                // its class's state, or 0 for a window gone
int   wk_alive(int w);
void  wk_title(int w, char *s);
char *wk_get_title(int w);
void  wk_invalidate(int w, int x, int y, int ww, int hh);   // ww = 0: all of it
void  wk_invalidate_covered(int w, int x, int y, int ww, int hh);
                                      // ... part of it that its draw paints every pixel of (a
                                      // program's frame): when nothing else changed, only it is
                                      // drawn there, not what is under it or its own frame
void  wk_menu(int w, struct wk_menu *m, int n);
void  wk_popup(int w, int x, int y, char **items);          // a menu of its own at (x, y) in the
                                      // client area (a right click's): ITEMS as a menu bar's, the
                                      // one chosen reaching command as WK_CMD(WK_POPUP, item)
int   wk_timer(int w, int id, int ms);                      // every ms (0 stops it); 1 if set
void  wk_raise(int w);
int   wk_focus();                     // the window with the keyboard, or 0
void  wk_size(int w, int *cw, int *ch);                     // its client area now
void  wk_place(int w, int x, int y, int ww, int hh);        // the whole window's rectangle
int   wk_find(struct wk_class *c);    // the first window of the class, or 0
int   wk_next(int w);                 // the windows in the order they opened: 0 starts, 0 ends
struct wk_class *wk_class_of(int w);
int   wk_modal();                     // a dialog holding the input, or 0
void  wk_redraw_all();                // the whole scene drawn again
int   wk_now();                       // milliseconds of machine time

// dialogs: the answer reaches the owner's class, or the shell's for 0
void  wk_msgbox(int owner, int dialog, char *title, char *text, int buttons);
void  wk_inputbox(int owner, int dialog, char *title, char *prompt, char *buf, int max);
void  wk_filebox(int owner, int dialog, int save, char *pattern, char *buf, int max);
                                      // buf: the start folder or name in, the path chosen out;
                                      // pattern: "*", "*.c;*.h", or types and their patterns,
                                      // "C Source (*.c)|*.c|All Files (*)|*", the first shown first

// the clipboard: text, copied in. One for every window: in grin the
// kit's own memory, so a paste after the copier has gone still has it
int   wk_clip_set(char *s, int n);    // 1 if it took it
char *wk_clip_get(int *n);

// ---- drawing (draw.c), only inside draw(): client-relative and clipped -----
void d_rect(int x, int y, int w, int h, int rgb);
void d_recto(int x, int y, int w, int h, int rgb);
void d_line(int x0, int y0, int x1, int y1, int rgb);
void d_disc(int x, int y, int r, int rgb);
void d_text(int x, int y, int rgb, int font, char *s);
void d_textn(int x, int y, int rgb, int size, int font, int advance, char *s, int n);
void d_bevel(int x, int y, int w, int h, int style);
void d_icon(int kind, int x, int y);
void d_clip(int x, int y, int w, int h);  // narrower than the client area, until d_clip_end
void d_clip_end();
void d_imgdef(int id, int w, int h, int *px);
void d_image(int id, int x, int y);
// w x h 8-bit pixels at src through 256 colours at pal, scaled to dw x dh
void d_blit8(int x, int y, int w, int h, char *src, int pitch, int *pal, int dw, int dh);
int  d_damage_within(int x, int y, int w, int h);   // 1 if all that is being redrawn is inside
int  ui_mix(int a, int b, int t, int n);   // a colour T/N of the way from A to B

// colour schemes (draw.c)
int   wk_scheme_count();
char *wk_scheme_name(int i);
void  wk_scheme_use(int i, int desk);      // desk: the desktop's colour, or -1 for the scheme's

// ---- widgets (ui.c): stateless, so the window owns the state --------------
void ui_button(int x, int y, int w, int h, char *label, int pressed, int deflt);
int  ui_hit(int px, int py, int x, int y, int w, int h);
void ui_scrollbar(int x, int y, int h, int total, int visible, int top);
int  ui_scroll_click(int px, int py, int x, int y, int h, int total, int visible, int top);
int  ui_scroll_drag(int x, int y, int py);     // the top line while the bar at x,y is dragged, or -1
void ui_hscrollbar(int x, int y, int w, int total, int visible, int left);
int  ui_hscroll_click(int px, int py, int x, int y, int w, int total, int visible, int left);
                                               // ... and a bar across: ui_scroll_drag(x, y, px)
int  ui_scroll_active();
int  ui_scroll_repeat();                        // the last press was an arrow's or the track's: the desktop repeats it
void ui_scroll_end();
void ui_field(int x, int y, int w, char *text, int caret, int focused);
int  ui_field_key(char *text, int max, int *caret, int code, int ch, int mods);
                                               // ... Ctrl+C copies the whole field, Ctrl+X cuts it,
                                               // Ctrl+V pastes at the caret (the clipboard's first line)
// the clipboard's keys, CUA's beside the letters, as Windows 3.1 took
// both: copy Ctrl+C or Ctrl+Ins, cut Ctrl+X or Shift+Del, paste Ctrl+V
// or Shift+Ins
int  ui_key_copy(int code, int ch, int mods);
int  ui_key_cut(int code, int ch, int mods);
int  ui_key_paste(int code, int ch, int mods);
int  ui_field_hit(int px, int x, int w, char *text, int caret);   // the caret for a click
void ui_check(int x, int y, char *label, int on);  // a check box and its label
// a splitter: the bar between two panes side by side, dragged across
void ui_splitter(int x, int y, int w, int h);
int  ui_split_click(int px, int py, int x, int y, int w, int h, int pos);   // 1: pressed, a drag from POS begun
int  ui_split_drag(int px);                    // POS as the pointer has moved it, or -1 for no drag
int  ui_split_active();
// A find bar, under an editor's text (ui.c): the editor keeps one and does
// the looking, the bar says what was asked for -- UF_NEXT, UF_PREV,
// UF_TYPED (the text changed), UF_CLOSE -- and keeps a note of what the
// last look found.
enum { UI_FIND_H = 30, UI_FIND_MAX = 64 };
enum { UF_NONE = 0, UF_NEXT = 1, UF_PREV = 2, UF_TYPED = 3, UF_CLOSE = 4 };
struct ui_find {
    char text[UI_FIND_MAX];           // what to find
    int caret;
    int on;                           // shown
    int keys;                         // it has the keyboard, not the text
    int mcase;                        // Match case
    char note[64];                    // what the last look found
    int bad;                          // ... and it was nothing (drawn in red)
};
void ui_find_open(struct ui_find *f, char *seed, int n);   // shown, with the keys; SEED (a selection) to find
void ui_find_draw(struct ui_find *f, int x, int y, int w, int focused);
int  ui_find_mouse(struct ui_find *f, int ev, int px, int py, int x, int y, int w);   // UF_*, or -1 off it
int  ui_find_key(struct ui_find *f, int code, int ch, int mods);                      // UF_*
void ui_find_say(struct ui_find *f, char *note, int bad);
int  ui_find_at(struct ui_find *f, char *s, int n);       // 1 if what F finds starts at S (N characters there)
void ui_tabs(int x, int y, char **labels, int n, int sel);
int  ui_tab_hit(int px, int py, int x, int y, char **labels, int n);
void ui_group(int x, int y, int w, int h, char *label);
void ui_radio(int x, int y, char *label, int on);
void ui_header(int x, int y, int *widths, char **labels, int n);
char *ui_num(char *buf, int v);                // decimal
char *ui_num_commas(char *buf, int v);         // 1,234,567
int  ui_len(char *s);
void ui_cpy(char *d, char *s);
void ui_cat(char *d, char *s);
int  ui_ncpy(char *d, char *s, int n);         // at most n - 1 bytes and a 0; 1 if all of s fit
int  ui_ncat(char *d, char *s, int n);         // ... onto the end of d, n its whole size
int  ui_join(char *out, char *dir, char *name, int n);   // dir/name, bounded; 1 if it fit
char *ui_base(char *path);                     // what follows the last '/'
int  ui_eq(char *a, char *b);
int  ui_ends(char *s, char *suffix);

// ---- the shell -------------------------------------------------------------
//
// What the shell draws and handles itself. Every hook may be 0.
struct wk_shell {
    void (*desktop)(int x, int y, int w, int h);  // under the windows, in this rectangle
    void (*front)();                  // over the windows (a taskbar, a menu of its own)
    int  (*popup)();                  // 1 while it has a menu open over everything
    int  (*mouse_front)(int ev, int x, int y, int button);  // before the windows: 1 took it
    void (*mouse_desk)(int ev, int x, int y, int button);   // where no window is
    int  (*key)(int down, int code, int ch, int mods);      // before the focused window: 1 took it
    int  (*pointer)(int x, int y);    // PTR_* there, or -1 for the kit's
    void (*answer)(int dialog, int result);                 // a dialog with no owner
    void (*resized)();                // the screen changed size: set the area, relayout
};

void wk_init(struct wk_shell *s);     // after gui_attach: the screen's size from the display
void wk_event(int *ev);               // one event from gui_poll
void wk_tick();                       // every pass: sweep closed windows, idle hooks, timers
int  wk_redraw(int force);            // draw what needs it (all of it if force); 1 if it drew
int  wk_dirty();                      // 1 if anything waits to be drawn
int  wk_next_timer();                 // ms until a timer is due, or -1 for none
void wk_drawn();                      // after the frame was shown: drawn hooks
void wk_repoint();                    // the display's pointer is an arrow again (it was away)
int  wk_menu_open();                  // 1 while a drop-down menu is open
void wk_screen(int w, int h);         // ask for a new screen size (gui_size) and relayout
void wk_set_area(int x, int y, int w, int h);
void wk_close_all();                  // every window, at once (shutting down)
void wk_min_icons(int on);            // minimised windows as icons along the bottom of the
                                      // area (Windows 3.1's), not only hidden
void wk_minimize(int w);
void wk_arrange_icons();              // the icons packed along the bottom again, in order
void wk_dirty_rect(int x, int y, int w, int h);   // screen coordinates
int  wk_in_damage(int x, int y, int w, int h);    // while drawing: 1 if this is being redrawn
void wk_clip_screen(int x, int y, int w, int h);  // the shell's own clip, inside the damage
void wk_noclip();

// ---- the host: what the shell provides the kit (desktop/host.c, grin's own)
char *wk_alloc(int n);                // zeroed, or 0
void  wk_free(char *p);
int   wk_fopen(char *path, int write);   // to read, or created/truncated to write; -1 if not
int   wk_fread(int fd, char *buf, int n);
int   wk_fwrite(int fd, char *buf, int n);
void  wk_fclose(int fd);
int   wk_readdir(char *dir, int i, char *name);   // entry i: 1 a folder, 0 a file, -1 no more
                                                  // (name holds WK_NAME bytes)

// ---- the accessories --------------------------------------------------------
extern struct wk_class calc_class;
extern struct wk_class notepad_class;
extern struct wk_class clock_class;
int  calc_open();
int  notepad_open(char *path);        // 0: a new document
int  clock_open();
extern char *notepad_name;            // in its titles ("Notepad"; the desktop's "Text Editor")
extern char *notepad_about;           // its Help > About line
extern char *notepad_home;            // where Open starts
extern char *notepad_untitled;        // where Save As offers to put a new document
extern int notepad_filebox;           // 1: Open and Save As are file boxes; 0: typed paths
extern char *notepad_filter;          // the types the file box offers ("*"; wk_filebox)
extern char *notepad_cfg;             // where Format's choices are kept (wk_fopen), or 0 for nowhere
int  wk_clock();                      // the host's time of day, in seconds since midnight

// ---- screen savers (savers.c) ----------------------------------------------
enum { SAVER_MS = 33 };
int  saver_count();
char *saver_name(int i);
int  saver_active();
void saver_start(int which);
void saver_frame();
void saver_stop();
int  saver_frames();
extern char *saver_marquee;          // what Marquee says (the C4IX desktop's line unless the shell says)

#endif // WINKIT_H
// wkwin.h -- inside the window kit: the window record, and what its
// modules share. A shell may include it to look at its windows (C4IX's
// desktop does, for the tools written before the kit); an application
// never does.

#ifndef WKWIN_H
#define WKWIN_H 1
#include "winkit.h"

// Each window is its own allocation, so there are as many as memory
// allows. Its number is never reused, so a number kept for a window that
// has since closed finds nothing. A window closed is off the z-order at
// once and freed at the next wk_tick (sweep): whoever closed it, or is
// walking the list, may still be holding it.
enum { WK_TIMERS = 4 };
struct win {
    int id;                       // its number (1 up)
    struct win *next;             // the next window, in the order they opened
    struct win *above, *below;    // z-order
    struct wk_class *cls;
    int slot;                     // where it cascaded to when it opened
    int used, kind, x, y, w, h;   // kind: its class's
    int min, max, rx, ry, rw, rh;
    int resizable, dialog;
    char title[48];
    char *st;                     // its class's state: cls->size bytes
    struct wk_menu *menus;        // its menu bar, nmenus of them
    int nmenus;
    int owner, action;            // a dialog: which window asked, and what for
    int tid[WK_TIMERS], tms[WK_TIMERS], tnext[WK_TIMERS];   // timers: id, period, when due
    int islot;                    // minimised as an icon (wk_min_icons): its place, 1 up; 0 none yet
};

struct win *win_get(int i);       // the window with this number, or 0
int  win_index(struct win *w);    // ... and a window's number (-1 for none)
struct win *win_first();          // the windows in the order they opened (closed ones still on it, used 0)

// the client area of a window, on the screen
int  wk_client_x(struct win *w);
int  wk_client_y(struct win *w);
int  wk_client_w(struct win *w);
int  wk_client_h(struct win *w);

// ---- draw.c's state, which wmcore.c and the looks drive ----
extern int wk_full;               // the whole scene is to be drawn
extern int wk_part;               // drawing only the damage
extern int wk_dmg, wk_dmg_x0, wk_dmg_y0, wk_dmg_x1, wk_dmg_y1;
void wk_origin(int x, int y);     // where d_* draw from (a client area, or 0, 0)
void wk_client_clip(int x, int y, int w, int h);   // the client area d_clip keeps inside

// ---- the looks (look95.c, look31.c) ----
// What a point on a window is: the chrome's parts, or the client area.
enum { HT_NONE = 0, HT_CLIENT = 1, HT_CAPTION = 2, HT_CLOSE = 3, HT_MAX = 4, HT_MIN = 5,
       HT_SYSMENU = 6, HT_MENUBAR = 7, HT_SIZE = 8 };
// HT_SIZE + edges: which edges a drag at that point moves
enum { SZ_L = 1, SZ_R = 2, SZ_T = 4, SZ_B = 8 };
struct wk_look {
    void (*frame)(struct win *w, int focused);         // the chrome, all but the menu bar
    void (*menubar)(struct win *w, int focused, int open, int hot);   // open: the menu shown, or -1
    int  (*hit)(struct win *w, int x, int y);          // HT_*, or HT_SIZE + SZ_* bits
    void (*grip)(struct win *w);                       // drawn over the client area's corner
    int  title_centred;
};
extern struct wk_look look_flat, look_classic, look_win31;
struct wk_look *wk_look();        // the one in use (wk.style)
void wk_gradient(int x, int y, int w, int h, int a, int b);
int  wk_ink(int bg);              // white on a dark bar, the scheme's dark on a light one
int  wk_menu_x(struct win *w, int k);   // where menu k of a menu bar starts on the screen
int  wk_menu_w(struct win *w, int k);
// minimised windows as icons along the bottom of the area (look31.c),
// when the shell asked for them (wk_min_icons)
extern int wk_icons_on;
extern int wk_icon_sel;           // the icon last clicked: its label is highlighted
void wk_icon_place(struct win *w);              // the first free place, as it is minimised
void wk_icon_xy(struct win *w, int *x, int *y); // where its picture is
struct win *wk_icon_hit(int x, int y);          // the icon there, or 0
void wk_icons_draw();             // the icons in the damage, under the windows

// ---- dialog.c, for wmcore.c ----
void wk_dialog_answer(struct win *d, int yes);   // close a dialog with this answer
extern struct wk_class wk_msg_class;
extern struct wk_class wk_input_class;
extern struct wk_class wk_file_class;

// ---- the file box: dialog.c's, drawn by the look in use (Windows 3.1's
// there, Windows 95's in look95.c) ----
enum { FB_MAX = 256, FB_ROWS = 12, FB_ROW = 16 };
struct fdlg {
    char *buf;                    // as a message box's (dialog.c)
    int max;
    char out[WK_PATH];            // the name typed, then the path chosen
    int caret;
    int save;
    int n, top, sel;              // the folder's entries, the first shown, the one picked
    char dir[WK_PATH];
    char filter[WK_PATH];         // the types offered: "label|patterns|label|patterns..."
    char pattern[WK_NAME];        // the patterns of the one in use, ';' between them
    int ftype;                    // ... which that is
    int drop;                     // a drop-down list open (look95.c): 1 the folders, 2 the types
    int up;                       // the look has an Up button: no ".." among the entries
    int isdir[FB_MAX];
    int order[FB_MAX];
    char names[FB_MAX * WK_NAME];
};
char *wk_fb_name(struct fdlg *f, int k);        // the k'th entry shown, folders first
void wk_fb_list(struct fdlg *f);                // the folder's entries read again
void wk_fb_enter(struct fdlg *f, char *name);   // into a folder of the one shown, ".." up
void wk_fb_ok(struct win *d, struct fdlg *f);   // Open or Save: the name typed, or a folder entered
int  wk_fb_types(struct fdlg *f);               // how many types the filter offers
void wk_fb_label(struct fdlg *f, int i, char *out, int n);   // type i's label
void wk_fb_type(struct fdlg *f, int i);         // type i the one shown
extern struct wk_class wk_file95_class;
void wk_answer_owner(int owner, int dialog, int result);   // wmcore.c: to the window, or the shell
#endif
// textgrid.h -- a VT100 text grid for a window (textgrid.c): what the C4IX
// desktop's Terminal draws, and grin's DOS Prompt will. No pipes: the
// window's code feeds it output and sends on the lines it edits.

enum { TG_COLS = 80, TG_ROWS = 25, TG_CW = 8, TG_CH = 16, TG_FONT = 14, TG_LINE = 250,
       TG_RUNMAX = 24, TG_HIST = 16, TG_HIST_W = 256, TG_SB_ROWS = 300, TG_SB_W = 16,
       TG_APC = 300 };
// the grid's size on the screen, inside its sunken edge, and with its scroll bar
enum { TG_W = TG_COLS * TG_CW + 4, TG_H = TG_ROWS * TG_CH + 4 };

struct tgrid {
    int win;                          // the window it is drawn in
    int cx, cy, wrap, fg, bg, bold, rev, cursor;
    int esc, np, param[8], priv;
    int alen;
    char abuf[TG_APC + 4];            // an ESC _ ... ESC \ command being read
    void (*apc)(char *ctx, char *s, int n);   // what one is for (0: dropped)
    char *ctx;
    int cell[TG_ROWS * TG_COLS];      // ch | fg << 8 | bg << 16, xterm-256 indices
    // The row cache (row_build): each row's background rectangles and
    // runs of text, as [first column, columns, kind << 8 | colour] with
    // kind 0 a rectangle and 1 text. rowok[r] is 0 until it is built, and
    // again whenever a cell of the row changes; rowk[r] is its run count,
    // or -1 for a row with more than TG_RUNMAX, drawn from the cells.
    int rowok[TG_ROWS], rowk[TG_ROWS];
    int runs[TG_ROWS * TG_RUNMAX * 3];
    // Line editing (tg_key): the line being typed, the cursor's place in
    // it, and where on the grid it starts (erow may go above the top as
    // the line scrolls). The history: hn lines, oldest first; hpos is the
    // one shown, hn for the line being typed, kept in saved meanwhile.
    int llen, lpos, erow, ecol;
    char line[TG_HIST_W];
    int hn, hpos, slen;
    char hist[TG_HIST * TG_HIST_W];
    char saved[TG_HIST_W];
    // The scrollback: a ring of rows that scrolled off the top, sbn of
    // them, the next going in at sbhead; view is how many rows back the
    // window shows (0, the live grid).
    int *sb;
    int sbn, sbhead, view;
    // A selection (tg_select): from a line and column to a line and column,
    // the lines numbered from the grid's first (nscr: the rows scrolled off
    // so far), so it stays on its text as more arrives. sel is 0 for none,
    // 1 a run of lines, 2 a block.
    int nscr, sel, sl0, sc0, sl1, sc1, selecting;
};

extern int tg_pal[256];               // xterm's 256 colours

struct tgrid *tg_new(int win);        // a cleared grid with its scrollback, or 0 for no memory
void tg_free(struct tgrid *g);
void tg_feed(struct tgrid *g, char *buf, int n);   // output: text and VT100 sequences
void tg_say(struct tgrid *g, char *s);
void tg_echo(struct tgrid *g, int c);
int  tg_key(struct tgrid *g, int code, int ch, int mods);
        // a key typed: the line editor, and PgUp/PgDn for the scrollback.
        // The length of a line Enter finished (with its newline, in
        // g->line), or 0
void tg_interrupt(struct tgrid *g);   // ^C: the line typed so far dropped
void tg_clear_screen(struct tgrid *g);   // Ctrl+L
void tg_scroll(struct tgrid *g, int rows);   // the scrollback: rows further back (negative: forward)
void tg_draw(struct tgrid *g, int x, int y, int focused);   // the grid at x, y and its scroll bar
void tg_mouse(struct tgrid *g, int ev, int x, int y);       // its scroll bar (E_WHEEL: y the steps)
// The selection, made with the mouse on the grid (x, y inside its sunken
// edge): a press starts one, a drag takes it on, and with block it is a
// rectangle rather than a run of lines. A click with no drag drops it.
void tg_select(struct tgrid *g, int ev, int x, int y, int block);
void tg_select_all(struct tgrid *g);  // the scrollback and the screen
void tg_unselect(struct tgrid *g);
int  tg_copy(struct tgrid *g, int all);   // the selection (or, all, everything) onto the
                                          // clipboard, a line a row; 0 if nothing was
// desktop.h -- what the desktop's modules share. docs/c4ix-desktop.md.
//
// The desktop is one C4IX task, the C4IX shell over the window kit
// (src/winkit, winkit.h): the kit has the windows, their chrome, the
// widgets, dialogs, the text grid, the screen savers and the Calculator
// and Text Editor (the kit's Notepad); these modules are C4IX's own:
//   shell.c     the display, the main loop, the desktop's icons and
//               picture, the taskbar and Go menu, Settings' choices kept
//   tools.c     each window kind's class (its hooks, below), and the
//               calls the tools were written against, over the kit's
//   host.c      what the kit asks of its host: memory and files
//   term.c      Terminal: a terminal running c4ix-sh over pipes
//   files.c     Files
//   taskmgr.c   System Monitor
//   apps.c      About and Settings
//   edit.c      Editor: the IDE, a VIM-mode editor that builds with b4ke
//   hl.c        the IDE's syntax colouring
//   explore.c   the IDE's Code tab: the code a C file compiles to, or a
//               compiled file's, with its source
//   wall.c      the desktop's picture
//
// Only the kit and shell.c touch the display. Everything else draws
// through the kit's d_* functions, which draw from the window's corner
// (the tools here are handed ox, oy = 0), clipped to it, and receives
// events in its own client coordinates.

#include "c4ix_user.h"
#include "wkwin.h"

enum { TASK_H = 30, SIGINT = 2, SIGTERM = 15 };

// window kinds (the kit's icons have the same numbers)
enum { K_TERM = 1, K_ABOUT = 2, K_FILES = 3, K_TASKS = 4, K_NOTE = 5, K_CALC = 6,
       K_MSG = 7, K_INPUT = 8, K_EDIT = 9, K_SETTINGS = 10, K_CLOCK = 11, N_KINDS = 12 };

// dialog results reach the window that asked through its answer hook
enum { A_NONE = 0, A_DELETE = 1, A_RENAME = 2, A_NEWDIR = 3, A_OPEN = 4, A_SAVEAS = 5,
       A_RUN = 6, A_ENDPROC = 7 };

#define wm_mods (wk.mods)     // the modifiers held now, for a click
extern int wm_button;         // the button of the last press: 0 the left, 2 the right (tools.c)

// ---- tools.c: windows as the tools see them (struct win, wkwin.h) ----
int  win_open(int kind, char *title, int w, int h, int size);   // size: the tool's state
void win_close(int i);
void win_title(struct win *w, char *s);
void win_raise(int i);
int  win_focused();
void mark_dirty();                    // the whole scene is to be drawn again
void mark_win_dirty(struct win *w);   // only this window's contents changed
void mark_frame();                    // a program's framebuffer frame waits: drawn at once (shell.c)
int  now_ms();
void msgbox(struct win *owner, char *title, char *text, int yesno, int action);
void inputbox(struct win *owner, char *title, char *prompt, char *initial, int action);
char *dialog_text();                  // the text an input dialog was answered with
void run_command(char *cmd);          // a new Terminal running cmd, or a window game's own window
void desk_window_app(char *cmd);      // cmd's program is a game that plays in a window of its own
int  desk_which(char *cmd, char *path);   // the path of cmd's program, as the shell finds it; 0 none
void launch(int kind);                // a new window of that kind (the Go menu, the icons)
struct wk_class *kind_class(int kind);

// ---- the tools: each window kind's hooks (tools.c calls these) ----
int  term_open(char *cmd);
int  term_run(char *cmd);             // cmd in a window that is only its canvas, no shell
void term_draw(struct win *w, int ox, int oy, int cw, int ch, int focused);
void term_key(struct win *w, int code, int ch, int mods);
void term_keyup(struct win *w, int code, int ch, int mods);
void term_drawn(struct win *w);
void term_tick(struct win *w);
void term_close(struct win *w);
void term_mouse(struct win *w, int ev, int x, int y, int cw, int ch);
int  term_pointer(struct win *w, int x, int y, int cw, int ch);   // PTR_LOCK over a canvas that asked (L 1)
int  term_lock_event(int *ev);        // a display event the locked mouse's (shell.c, before the kit): 1 taken
void term_lock_tick();                // each pass: the lock let go once its canvas no longer has it
void desk_unlock();                   // shell.c: the display lets the mouse go, the pointer an arrow
void term_command(struct win *w, int menu, int item);   // Edit: Copy, Paste, Select All, Copy All

int  files_open(char *path);
void files_draw(struct win *w, int ox, int oy, int cw, int ch, int focused);
void files_mouse(struct win *w, int ev, int x, int y, int cw, int ch);
void files_key(struct win *w, int code, int ch, int mods);
void files_command(struct win *w, int menu, int item);
void files_answer(struct win *w, int action, int yes);
int  files_pointer(struct win *w, int x, int y, int cw, int ch);   // PTR_COLS over the tree's splitter

int  tasks_open();
int  tasks_open_perf();           // System Monitor on its Performance tab
int  tasks_cpu_usage();           // the machine's CPU use now, in percent (the taskbar's meter)
void tasks_draw(struct win *w, int ox, int oy, int cw, int ch, int focused);
void tasks_mouse(struct win *w, int ev, int x, int y, int cw, int ch);
void tasks_key(struct win *w, int code, int ch, int mods);
void tasks_tick(struct win *w);
void tasks_answer(struct win *w, int action, int yes);

int  note_open(char *path);       // the kit's Notepad, as the Text Editor

int  edit_pointer(struct win *w, int x, int y, int cw, int ch);   // PTR_* for the pointer there
int  edit_open(char *path);
void edit_draw(struct win *w, int ox, int oy, int cw, int ch, int focused);
void edit_mouse(struct win *w, int ev, int x, int y, int cw, int ch);
void edit_key(struct win *w, int code, int ch, int mods);
void edit_command(struct win *w, int menu, int item);
void edit_answer(struct win *w, int action, int yes);
void edit_tick(struct win *w);
void edit_close(struct win *w);

// edit.c's text grid, from IDE Settings' font: a cell's width and height,
// the font's size and face (the Code tab draws in it too)
extern int ide_cw, ide_ch, ide_fs, ide_face;

// hl.c: the IDE's syntax colouring. The languages, and what a character is.
enum { L_TEXT = 0, L_C = 1, L_JS = 2, L_LISP = 3, L_FORTH = 4, L_SH = 5, L_B4K = 6, HL_MAX = 1024 };
enum { HC_TEXT = 0, HC_KW = 1, HC_TYPE = 2, HC_STR = 3, HC_COM = 4, HC_NUM = 5, HC_PRE = 6 };
int  hl_lang(char *path);                        // L_* by the file's name
int  hl_inwords(char *s, int n, char *list);     // S[0..N) one of LIST's words (" a b ")
int  hl_line(char *s, int n, int st, int lang);  // colour a line; the C comment state after it
int  hl_at(int i);                               // HC_* of the line's character I

// explore.c: the IDE's Code tab, which edit.c holds as an opaque int *
int *xp_new();
void xp_free(int *x);
int  xp_compile(int *x, char *path, char *dir);   // cc -g -c PATH in the background; 0 if it cannot
int  xp_load(int *x, char *path, char *dir);      // the compiled file PATH itself; 0 if it is not one
int  xp_tick(int *x);                            // 1 when the compile ended and the tab changed
int  xp_busy(int *x);
int  xp_opt(int *x);                             // 1 if it compiles with -O
void xp_cursor(int *x, int line);                // the cursor on LINE (1-based): its function
int  xp_band(int *x, int line);                  // the band beside LINE, or -1
void xp_draw(int *x, int ox, int oy, int cw, int ch, int *cols, int modified, int focused);
int  xp_mouse(int *x, int ev, int px, int py, int cw, int ch);   // 1 used, 0 not, 2 a line (xp_goto), -1, -2
int  xp_key(int *x, int code, int ch, int mods);                 // 1 used, 0 not, 2 a line (xp_goto)
int  xp_goto(int *x, char *path);                // the line asked for, its file into PATH (128)

void about_open();
void about_draw(struct win *w, int ox, int oy, int cw, int ch, int focused);

int  settings_open();
void settings_draw(struct win *w, int ox, int oy, int cw, int ch, int focused);
void settings_mouse(struct win *w, int ev, int x, int y, int cw, int ch);
void settings_key(struct win *w, int code, int ch, int mods);

// ---- shell.c: the colour scheme, the look, the picture and the saver ----
// each choice used at once, redrawn, and remembered in /etc/desktop.cfg
int  theme_count();
char *theme_name(int i);
int  theme_scheme();               // the scheme in use
int  theme_bg();                   // the desktop's own colour, or -1 for the scheme's
void theme_set(int scheme, int bg); // the picture off
void theme_set_wall(int on);        // the picture (wall.c) on or off
int  theme_wall();
int  theme_saver();
int  theme_wait();
void theme_set_saver(int which, int wait);   // the screen saver and its minutes
void theme_set_style(int style);   // S_FLAT, S_CLASSIC or S_WIN31
void saver_preview();              // the chosen saver now (Settings)
int  theme_swatch(int i);          // the desktop colours Settings offers, 0..7
// Files' order: by one of these, SORT_* * 2, plus 1 for descending; folders first either way
enum { SORT_NAME = 0, SORT_TYPE = 1, SORT_SIZE = 2, SORT_DATE = 3, N_SORTS = 4 };
int  theme_sort();
void theme_set_sort(int sort);
// Files' folder tree: its width, as its splitter was last left
int  theme_tree();
void theme_set_tree(int w);
// the interface's font: one of the kit's faces and sizes (WK_FACES, WK_SIZES)
int  theme_font();
int  theme_fsize();
void theme_set_font(int face, int size);

// the screen's size (Settings): one of the sizes offered, asked of the
// display at once and when the desktop starts, and remembered with the rest
int  display_count();
char *display_name(int i);         // "800x600"
int  display_cur();                // the one in use
void display_set(int i);

// ---- wall.c: the desktop's picture ----
int  wall_load(char *path);
int  wall_draw(int x, int y, int w, int h);   // 0: no picture, fill with C_DESK
int  wall_shown();
void wall_resize();                           // the screen changed size: the tiles again
// apps.c -- About and Settings. docs/c4ix-desktop.md. (The Calculator and the
// Text Editor are the window kit's: calc.c and notepad.c in src/winkit.)

#include "desktop.h"
#include "c4ix_accel.h"

// ---- About ---------------------------------------------------------------------------------

void about_open() {
    int i, k;
    struct win *w;
    w = win_first();
    while (w) { if (w->used && w->kind == K_ABOUT) { win_raise(w->id); return; } w = w->next; }
    i = win_open(K_ABOUT, "About C4IX", 440, 180, 0);
    if (i < 0) return;
    w = win_get(i);
    w->resizable = 0;
    w->x = (wk.sw - 440) / 2; w->y = (wk.sh - 180) / 2 - 60;
}

void about_draw(struct win *w, int ox, int oy, int cw, int ch, int focused) {
    d_rect(ox, oy, cw, ch, C_FACE);
    d_rect(ox + 16, oy + 16, 36, 36, C_TITLE);
    d_rect(ox + 20, oy + 20, 13, 13, 0xff2020); d_rect(ox + 35, oy + 20, 13, 13, 0x20c020);
    d_rect(ox + 20, oy + 35, 13, 13, 0x2040ff); d_rect(ox + 35, oy + 35, 13, 13, 0xffd020);
    d_text(ox + 68, oy + 16, C_DARK, F_BOLD, "C4IX Desktop");
    d_text(ox + 68, oy + 36, C_DARK, F_SANS, "Running on c4m.js: the c4m virtual machine in");
    d_text(ox + 68, oy + 52, C_DARK, F_SANS, "JavaScript, in a Web Worker.");
    d_text(ox + 68, oy + 76, C_DARK, F_SANS, "Every Terminal is a real c4ix-sh task; its");
    d_text(ox + 68, oy + 92, C_DARK, F_SANS, "stdin and stdout are pipes the desktop holds.");
    d_text(ox + 68, oy + 116, C_SHADOW, F_SANS, "Enter or Esc closes this window.");
}

// ---- Settings: the scheme, the desktop, the screen's size, the saver, the look, the font ----
//
// Display Properties, cut down: a list of schemes and a row of desktop
// colours, each applied at once (theme_set, which also remembers them in
// /etc/desktop.cfg), beside a preview drawn in the colours in use. The
// screen's size too, which the display takes at once (display_set). And
// in a third column the interface's font, its face and size, with a
// sample: every window's titles, menus and dialogs are drawn in it.
// Under it, C4IX's accelerators (c4ix_accel.h): the machine's switch for
// them, turned at once; the page keeps what it was turned to for its
// next boot (libjs/web/app.js), and a machine without them says so.

static char *dflt_label;
static char sbuf[16];
// the second column's width, and where the third starts and how wide it is
// and where the accelerators' group is, under the font's sample
enum { SET_COL = 222, SET_X3 = 432, SET_COL3 = 146, SET_ACC = 250 };

int settings_open() {
    int k;
    struct win *w;
    w = win_first();
    while (w) { if (w->used && w->kind == K_SETTINGS) { win_raise(w->id); return w->id; } w = w->next; }
    dflt_label = "Defaults";
    return win_open(K_SETTINGS, "Settings", 590, 450, 0);
}

void settings_draw(struct win *w, int ox, int oy, int cw, int ch, int focused) {
    int i, x, y, sel, n;
    d_rect(ox, oy, cw, ch, C_FACE);
    // the schemes
    n = theme_count();
    ui_group(ox + 8, oy + 8, 180, 20 + n * 20, "Color scheme");
    sel = theme_scheme();
    i = 0;
    while (i < n) { ui_radio(ox + 18, oy + 26 + i * 20, theme_name(i), i == sel); ++i; }
    // the desktop: the picture, the scheme's colour, or one of eight
    y = oy + 36 + n * 20;
    ui_group(ox + 8, y, 180, 94, "Desktop");
    ui_radio(ox + 18, y + 16, "Picture: C4IX", theme_wall());
    ui_radio(ox + 18, y + 36, "The scheme's colour", !theme_wall() && theme_bg() < 0);
    i = 0;
    while (i < 8) {
        x = ox + 18 + i * 20;
        sel = !theme_wall() && theme_bg() == theme_swatch(i);
        d_rect(x, y + 60, 16, 16, theme_swatch(i));
        d_recto(x - 1, y + 59, 18, 18, sel ? C_DARK : C_SHADOW);
        if (sel) d_recto(x - 2, y + 58, 20, 20, C_DARK);
        ++i;
    }
    // the screen's size: two to a row
    y = y + 102;
    ui_group(ox + 8, y, 180, 60, "Screen size");
    i = 0;
    while (i < display_count()) { ui_radio(ox + 18 + (i % 2) * 84, y + 16 + (i / 2) * 20, display_name(i), i == display_cur()); ++i; }
    // the preview: the desktop, an inactive window, an active one
    x = ox + 200; y = oy + 14;
    d_rect(x, y, SET_COL, 170, C_DESK);
    d_bevel(x, y, SET_COL, 170, B_SUNKEN);
    d_rect(x + 12, y + 14, 150, 70, C_FACE); d_bevel(x + 12, y + 14, 150, 70, B_RAISED);
    d_rect(x + 15, y + 17, 144, 16, C_ITITLE);
    // its title in the scheme's dark when the bar is light, as the windows' (wm.c)
    i = ((C_ITITLE >> 16) & 255) + ((C_ITITLE >> 8) & 255) + (C_ITITLE & 255);
    d_text(x + 19, y + 19, ui_style == S_FLAT && i >= 384 ? 0x404850 : C_FACE, F_BOLD, "Inactive Window");
    d_rect(x + 28, y + 50, 170, 100, C_FACE); d_bevel(x + 28, y + 50, 170, 100, B_RAISED);
    d_rect(x + 31, y + 53, 164, 16, C_TITLE);
    d_text(x + 35, y + 55, C_LIGHT, F_BOLD, "Active Window");
    d_rect(x + 36, y + 76, 150, 40, C_WHITE); d_bevel(x + 36, y + 76, 150, 40, B_SUNKEN);
    d_text(x + 42, y + 80, C_DARK, F_SANS, "Normal");
    d_rect(x + 40, y + 96, 60, 15, C_SEL);
    d_text(x + 42, y + 97, C_WHITE, F_SANS, "Selected");
    ui_button(x + 110, y + 122, 76, 22, "OK", 0, 1);
    // the screen saver: which, after how long, and a look at it now
    x = ox + 200; y = oy + 192;
    n = saver_count();
    ui_group(x, y, SET_COL, 26 + n * 18, "Screen saver");
    sel = theme_saver();
    i = 0;
    while (i < n) { ui_radio(x + 10, y + 16 + i * 18, saver_name(i), i == sel); ++i; }
    ui_button(x + 130, y + 14, 70, 22, "Preview", 0, 0);
    ui_num(sbuf, theme_wait());
    ui_cat(sbuf, " min");
    d_text(x + 130, y + 46, C_DARK, F_SANS, "Wait:");
    ui_button(x + 130, y + 62, 22, 20, "-", 0, 0);
    d_text(x + 156, y + 66, C_DARK, F_SANS, sbuf);
    ui_button(x + 192, y + 62, 22, 20, "+", 0, 0);
    // the look
    y = oy + 192 + 26 + n * 18 + 8;
    ui_group(x, y, SET_COL, 44, "Look");
    ui_radio(x + 10, y + 18, "Flat", ui_style == S_FLAT);
    ui_radio(x + 70, y + 18, "Classic", ui_style == S_CLASSIC);
    ui_radio(x + 140, y + 18, "Windows 3.1", ui_style == S_WIN31);
    // the font: its face, its size, and a sample in it
    x = ox + SET_X3; y = oy + 8;
    ui_group(x, y, SET_COL3, 20 + WK_FACES * 20, "Font");
    i = 0;
    while (i < WK_FACES) { ui_radio(x + 10, y + 18 + i * 20, wk_face_name(i), i == theme_font()); ++i; }
    y = y + 28 + WK_FACES * 20;
    ui_group(x, y, SET_COL3, 20 + WK_SIZES * 20, "Font size");
    i = 0;
    while (i < WK_SIZES) { ui_radio(x + 10, y + 18 + i * 20, wk_size_name(i), i == theme_fsize()); ++i; }
    y = y + 28 + WK_SIZES * 20;
    d_rect(x, y, SET_COL3, 56, C_WHITE);
    d_bevel(x, y, SET_COL3, 56, B_SUNKEN);
    d_text(x + 8, y + 8, C_DARK, F_BOLD, "Window Title");
    d_text(x + 8, y + 30, C_DARK, F_SANS, "The quick brown fox");
    // the accelerators
    y = oy + SET_ACC;
    n = cx_os(0 - 1);
    ui_group(x, y, SET_COL3, 64, "Accelerators");
    if (n & 2) {
        ui_radio(x + 10, y + 18, "On", n & 1);
        ui_radio(x + 70, y + 18, "Off", !(n & 1));
        d_text(x + 10, y + 40, C_SHADOW, F_SANS, "unpacking and CRC");
    } else d_text(x + 10, y + 24, C_SHADOW, F_SANS, "Not on this machine");
    ui_button(ox + 8, oy + ch - 34, 86, 24, dflt_label, 0, 0);
}

void settings_mouse(struct win *w, int ev, int x, int y, int cw, int ch) {
    int n, i, sy, k;
    if (ev != E_DOWN) return;
    n = theme_count();
    i = 0;
    while (i < n) {
        if (ui_hit(x, y, 14, 24 + i * 20, 170, 18)) { k = theme_wall(); theme_set(i, theme_bg()); theme_set_wall(k); return; }
        ++i;
    }
    sy = 36 + n * 20;
    if (ui_hit(x, y, 14, sy + 14, 170, 18)) { theme_set_wall(1); return; }
    if (ui_hit(x, y, 14, sy + 34, 170, 18)) { theme_set(theme_scheme(), 0 - 1); return; }
    i = 0;
    while (i < 8) {
        if (ui_hit(x, y, 16 + i * 20, sy + 58, 20, 20)) { theme_set(theme_scheme(), theme_swatch(i)); return; }
        ++i;
    }
    // the screen's size (settings_draw)
    i = 0;
    while (i < display_count()) {
        if (ui_hit(x, y, 14 + (i % 2) * 84, sy + 102 + 14 + (i / 2) * 20, 80, 18)) { display_set(i); return; }
        ++i;
    }
    // the screen saver group (settings_draw)
    i = 0;
    while (i < saver_count()) {
        if (ui_hit(x, y, 206, 206 + i * 18, 120, 16)) { theme_set_saver(i, theme_wait()); return; }
        ++i;
    }
    if (ui_hit(x, y, 330, 206, 70, 22)) { saver_preview(); return; }
    if (ui_hit(x, y, 330, 254, 22, 20)) { theme_set_saver(theme_saver(), theme_wait() - 1); return; }
    if (ui_hit(x, y, 392, 254, 22, 20)) { theme_set_saver(theme_saver(), theme_wait() + 1); return; }
    // the look group (settings_draw): under the savers
    sy = 192 + 26 + saver_count() * 18 + 8 + 18;
    if (ui_hit(x, y, 206, sy - 2, 60, 16)) { theme_set_style(S_FLAT); return; }
    if (ui_hit(x, y, 266, sy - 2, 66, 16)) { theme_set_style(S_CLASSIC); return; }
    if (ui_hit(x, y, 336, sy - 2, 90, 16)) { theme_set_style(S_WIN31); return; }
    // the font's face and size (settings_draw): the third column
    i = 0;
    while (i < WK_FACES) { if (ui_hit(x, y, SET_X3 + 4, 24 + i * 20, SET_COL3 - 8, 18)) { theme_set_font(i, theme_fsize()); return; } ++i; }
    sy = 8 + 28 + WK_FACES * 20;
    i = 0;
    while (i < WK_SIZES) { if (ui_hit(x, y, SET_X3 + 4, sy + 16 + i * 20, SET_COL3 - 8, 18)) { theme_set_font(theme_font(), i); return; } ++i; }
    // the accelerators (settings_draw), where the machine has them
    if (cx_os(0 - 1) & 2) {
        if (ui_hit(x, y, SET_X3 + 6, SET_ACC + 16, 56, 18)) { cx_os(1); mark_win_dirty(w); return; }
        if (ui_hit(x, y, SET_X3 + 66, SET_ACC + 16, 60, 18)) { cx_os(0); mark_win_dirty(w); return; }
    }
    if (ui_hit(x, y, 8, ch - 34, 86, 24)) { theme_set(theme_count() - 1, 0 - 1); theme_set_wall(1); theme_set_style(S_FLAT); theme_set_font(0, 1); }
}

// Up and Down walk the schemes; Esc or Enter closes
void settings_key(struct win *w, int code, int ch, int mods) {
    int s, w2;
    s = theme_scheme();
    w2 = theme_wall();
    if (code == KEY_UP && s > 0) { theme_set(s - 1, theme_bg()); theme_set_wall(w2); }
    else if (code == KEY_DOWN && s < theme_count() - 1) { theme_set(s + 1, theme_bg()); theme_set_wall(w2); }
    else if (code == KEY_ESC || code == KEY_ENTER) win_close(win_index(w));
}
// edit.c -- the IDE: a text editor, modeless or with VIM's modes, that
// builds what it edits. docs/c4ix-desktop.md.
//
// The text is an array of lines, each its own allocation, so a file is
// as big as memory allows and an edit moves one line, not the file.
// Everything that changes text goes through four primitives -- insert a
// line, delete a line, insert text at a position, delete a range -- and
// undo is a snapshot of the whole text before each change, which is
// simple and, for the files this machine holds, cheap.
//
// Two ways of typing, chosen in its Settings (View > Settings, kept in
// /etc/ide.cfg with the colour scheme and the font). Traditional, the default, is Text
// Editor's: typing always types, Shift with the moving keys or a drag of
// the mouse selects, and typing replaces the selection; Ctrl+X, C and V
// (and Shift+Del, Ctrl+Ins, Shift+Ins) cut, copy and paste, Ctrl+A selects
// everything, Ctrl+Z and Ctrl+Y undo and redo, and Esc opens the command
// line below (:w, :make and the rest). VIM mode (":set vim" for one
// window, ":set novim" back):
//   Normal   h j k l w b e W B E 0 ^ $ gg G { } % f t F T ; ,  with counts
//            i a I A o O  x X D C s S r J ~  p P  u Ctrl-R  .  n N *
//            d c y > <  with any motion, doubled for lines, and iw aw
//            i( a( i{ a{ i" a" as text objects;  v V for Visual
//   Insert   typing, Enter (keeping the indent), Backspace, Tab, Esc
//   Command  :w :q :q! :wq :x :e FILE :N :$ :s/a/b/ :%s/a/b/g
//            :make :run [CMD] :cn :cp :copen :cclose :set nu|nonu|vim|novim
//            /text ?text
// Arrow keys, Home/End, PgUp/PgDn, Ctrl+Home/End and Ctrl+Left/Right
// work in every mode, Insert included; Shift+arrows extend a Visual
// selection. Ctrl+S saves from any mode.
//
// Building. :make (or F5) writes the file and runs b4ke over pipes into
// the pane at the bottom: on the nearest BUILD.B4K above the file if
// there is one, or else, for a .c file, a build file of its own that
// compiles it with c4sc and links it with libc4ix into /tmp. Lines that
// name a place -- "FILE:N:", c4lc's "line N:", c4cc's "N:" -- are errors:
// :cn and :cp (F8, Shift+F8), or a double click, go to them. :run (F6)
// runs what was built in a new Terminal: the .c file's image, or
// the command a BUILD.B4K names with "SET RUN command".
//
// Long lines fold onto the rows below (Word Wrap, on to start with), or,
// with :set nowrap (View > Word Wrap), scroll across under a bar; j and k
// move by line either way. The
// build pane scrolls both ways, and its Cancel button (or Build > Cancel)
// stops a build: what b4ke is running first, then b4ke.
//
// Files. A pane down the left is the disk as a tree, closed folders to
// start with: a click opens or closes a folder, and opens a file in the
// editor. Opening a file opens the folders on the way to it. Ctrl+B,
// View > Files or :Ex shows and hides it. The bar on its right is a
// splitter: dragged, it sizes the pane, a size every IDE window opens
// with after that (kept in /etc/ide.cfg).
//
// Find. Ctrl+F (Edit > Find..., in either way of typing) opens the kit's
// find bar under the text: Enter, F3 or Next finds the next match after
// the selection, Shift+Enter, Shift+F3 or Previous the one before, round
// past the end or the top with a note that it went round; the match is
// selected (VIM's Visual, in VIM mode) and scrolled to. Match case or not.
//
// Scrolling. The wheel and the scroll bar move the view by lines, and the
// cursor with it when it would leave the view; the last line comes to the
// bottom however its lines wrap. The colouring's state at each line's
// start is kept as far as it was worked out, so the view moves up as
// cheaply as down.
//
// Code. View > Code (F7, :code) opens a Code tab beside the text's, in
// the text's place: explore.c, a cut-down Code Explorer, with the
// functions down its left and the code a .c file compiles to, its source
// lines between the instructions. It compiles the saved file with cc -g,
// again at each save, and shows the function the cursor is in; typing
// finds another by name, a double click on a call goes to the callee and
// on a line back to it in the text, and Esc or F7 goes back to the text
// (whose gutter is banded where that function has code). Its -O button
// compiles with and without -O. A compiled file -- anything with C4R's
// header, a program, an object or a library -- opens in the Code tab
// alone, as it is, its sources read where its map says they are; F6 runs
// a program.
//
// Colours. The text is coloured by what the file's name says it is: C and
// headers, JavaScript, Lisp, Forth, shell scripts and Makefiles, and B4KE
// build files. :syntax off (or View > Syntax Colouring) turns it off. The
// colours are a scheme's, chosen in Settings: Blue, after VIM's `blue`
// (the default), or Classic, black on white.
//
// Edit's Cut, Copy and Paste go through the desktop's clipboard (the
// kit's, which every window shares): in VIM mode they take a Visual
// selection. Any other file that looks binary -- by its name (.wad, .tgz
// and the like) or a NUL in its first bytes -- is opened only once asked.

#include "desktop.h"

enum { UNDO_MAX = 32, BROWS = 8, BLOG_MAX = 300,
       ERR_MAX = 100, REC_MAX = 3000, KEY_F4 = 115, KEY_F6 = 117, KEY_F7 = 118, KEY_F8 = 119 };
// The text grid: a cell's width and height, the font's size and face.
// Settings' font sets them (the kit's grids, wk_grid), for every IDE
// window and its Code tab (explore.c)
int ide_cw = 7;
int ide_ch = 15;
int ide_fs = 12;
int ide_face = F_MONO;
#define ECW ide_cw
#define ECH ide_ch
#define EFONT ide_fs
#define EFACE ide_face
// the tabs over the text, when the Code tab is open: their height
enum { TABH = 24 };
// the file pane: its width, its header, a row; a node's flags; how many
// entries of one folder it lists
enum { FW = 180, SPW = 5, FMIN = 100, FHDR = 20, FROW = 16, F_DIR = 1, F_OPEN = 2, F_KIDS = 400, FNAME = 64 };
// the languages it colours, and what each character is (desktop.h, hl.c):
// the scheme's colour for it is ec[that] (below)
enum { M_NORMAL = 0, M_INSERT = 1, M_VISUAL = 2, M_VLINE = 3, M_CMD = 4 };
// Edit's items, and the answer this window asks for itself
enum { E_CUT = 0, E_COPY = 1, E_PASTE = 2, E_ALL = 4, E_FIND = 6, E_FNEXT = 7, E_FPREV = 8 };
enum { A_BINARY = 40 };

// The colour schemes: the text's colours by HC_*, then the rest. A gutter
// number colour of SHADOW is the desktop scheme's shadow.
enum { SC_BG = 7, SC_GUT = 8, SC_GUTFG = 9, SC_SEL = 10, SC_TILDE = 11, SC_CUR = 12, SC_CURFG = 13, SC_N = 14,
       N_SCHEMES = 2, SHADOW = 0x1000000 };
static char *scheme_names[N_SCHEMES] = { "Blue (after VIM's blue)", "Classic (black on white)" };
static int scheme_cols[N_SCHEMES * SC_N] = {
    // Blue: VIM's `blue`, gold on dark blue
    0xffd700, 0xffffff, 0x87d7ff, 0x87ffaf, 0xd7d7af, 0xff87af, 0x87ffff,
    0x000087, 0x00005f, 0xffff87, 0x5f87d7, 0x5f87ff, 0xffd700, 0x000087,
    // Classic: the IDE's first colours
    0x000000, 0x0000b0, 0x007878, 0xa01818, 0x2a8a2a, 0x905000, 0x8020a0,
    0xffffff, 0xe8e8e8, SHADOW, 0xa8c8ff, 0x6060c0, 0x000000, 0xffffff };
// Settings: the scheme, the input mode (VIM's or not) and the font's
// face and size, for every IDE window, kept in /etc/ide.cfg
static int ide_scheme, ide_vim, ide_loaded, ide_mono;
static int ide_size = 1;
static int ide_fw = FW;                // the file pane's width (its splitter), for each window opened
static int *ec;                       // the scheme in use: ec[HC_KW] and the rest

struct edit {
    char path[128];
    char **ln; int *len; int *cap; int nl, maxl;   // the text
    int cy, cx, want, top, left;                   // the cursor, its column to keep, the view
    int mode, vim, nu, modified;
    int vy, vx;                                    // where a Visual selection started
    char cmd[160]; int cmdn, cmdkind;              // the : / ? line being typed
    int count, op, opcount, pre;                   // a Normal command half typed
    char msg[120];
    char search[64]; int sdir;
    int fch, fkind;                                // the last f t F T, for ; and ,
    char *reg; int regn, regline;                  // the one register
    char **utext; int *ulen; int *ucy; int *ucx; int un;   // undo
    char **rtext; int *rlen; int *rcy; int *rcx; int rn;   // redo
    int *rec; int recn, recording, changed;        // the keys of the change being made
    int *dot; int dotn, replaying;                 // ... and of the last one, for '.'
    int pid, out_r, building, bstatus, bshown, btop, bsel;   // the build
    char **blog; int blogn;
    char bpart[256]; int bpartn;
    char bctx[128];                                // the source file the last command named
    char **epath; int *eline; int *elog; int en, ecur;
    char bdir[128]; char runcmd[160];
    int rows, cols, gw;                            // the view's size, as last drawn
    char **fpath; int *fdepth; int *fflag;         // the file pane: a node's path, depth, F_ flags
    int fn, fcap, ftop, fshown, ffollow;
    int hver, nosyn;                               // a count of changes; colouring off
    int *hls; int hlsn, hlscap, hl_lang;           // the colouring's state at each line's start, known for the first hlsn
    int wrap;                                      // long lines fold onto the rows below
    int lcx, lcy;                                  // the cursor at the last draw: the view follows it when it moves
    int tah, ph, hb, maxw;                         // the text area's height, the build pane's, a bar across, the longest line
    int bleft, bmaxw, bcols, bcancel;              // the build pane across; a build being cancelled
    int fleft;                                     // the file pane across, in 6-pixel steps
    int tsel, tlast;                               // Traditional: a selection from (vy, vx); the last key typed text
    int drag;                                      // the mouse is selecting
    char ask[WK_PATH];                             // a file box's path, in and out
    char pend[128];                                // a binary file waiting to be opened, once asked
    int *xp; int xshown, xtab, xobj;               // the Code tab (explore.c): open, in front; a compiled file, shown alone
    int fw, fwx, fdrag;                            // the file pane's width: chosen, as drawn; its splitter dragged
    int vis;                                       // the scroll bar's lines at once: the text's less the last top line
    int fh;                                        // the find bar's height as drawn (0: closed)
    struct ui_find fb;                             // the find bar
};

static struct edit *E(struct win *w) { return (struct edit *)w->st; }
static char sb[512];
static struct wk_menu edit_menus[5];
static char *edit_file_items[7];
static char *edit_edit_items[10];
static char *edit_build_items[7];
static char *edit_view_items[7];
static char *edit_help_items[2];
// what Open and Save As offer: the file box's types
static char *ide_filter = "All Files (*)|*|C Source (*.c;*.h)|*.c;*.h|Build Files (*.b4k)|*.b4k|Scripts (*.sh;*.js;*.lisp;*.fs)|*.sh;*.js;*.mjs;*.lisp;*.scm;*.fs;*.f;*.4th|Text (*.txt;*.md)|*.txt;*.md";

static int e_isspace(int c) { return c == ' ' || c == 9 || c == 10 || c == 13; }
static int e_isword(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}
// 0 space, 1 word, 2 punctuation; WORD motions count punctuation as word
static int e_class(int c, int big) {
    if (e_isspace(c)) return 0;
    if (big || e_isword(c)) return 1;
    return 2;
}

static void e_say(struct edit *e, char *s) { ui_cpy(e->msg, s); }

// ---- lines -------------------------------------------------------------------------

// Line Y changed: the file is modified, and the colouring's state after
// Y has to be worked out again
static void e_touched(struct edit *e, int y) {
    e->modified = 1; e->changed = 1; ++e->hver;
    if (y < 0) y = 0;
    if (e->hlsn > y + 1) e->hlsn = y + 1;
}

static void e_lines_reserve(struct edit *e, int need) {
    char **nln;
    int *nlen, *ncap;
    int m, i;
    if (need <= e->maxl) return;
    m = e->maxl ? e->maxl : 64;
    while (m < need) m = m * 2;
    nln = (char **)ualloc(m * sizeof(int));
    nlen = (int *)ualloc(m * sizeof(int));
    ncap = (int *)ualloc(m * sizeof(int));
    i = 0;
    while (i < e->nl) { nln[i] = e->ln[i]; nlen[i] = e->len[i]; ncap[i] = e->cap[i]; ++i; }
    if (e->ln) { free(e->ln); free(e->len); free(e->cap); }
    e->ln = nln; e->len = nlen; e->cap = ncap; e->maxl = m;
}

// room in line Y for NEED characters
static void e_reserve(struct edit *e, int y, int need) {
    char *nb;
    int c;
    if (e->cap[y] >= need + 1) return;
    c = e->cap[y] * 2;
    if (c < 16) c = 16;
    while (c < need + 1) c = c * 2;
    nb = (char *)ualloc(c);
    if (e->len[y] > 0) memcpy(nb, e->ln[y], e->len[y]);
    free(e->ln[y]);
    e->ln[y] = nb;
    e->cap[y] = c;
}

static void e_insline(struct edit *e, int at, char *s, int n) {
    int i, c;
    e_lines_reserve(e, e->nl + 1);
    i = e->nl;
    while (i > at) { e->ln[i] = e->ln[i - 1]; e->len[i] = e->len[i - 1]; e->cap[i] = e->cap[i - 1]; --i; }
    c = n + 1 < 16 ? 16 : n + 1;
    e->ln[at] = (char *)ualloc(c);
    if (n > 0) memcpy(e->ln[at], s, n);
    e->len[at] = n;
    e->cap[at] = c;
    ++e->nl;
    e_touched(e, at);
}

static void e_delline(struct edit *e, int at) {
    int i;
    if (at < 0 || at >= e->nl) return;
    free(e->ln[at]);
    i = at;
    while (i < e->nl - 1) { e->ln[i] = e->ln[i + 1]; e->len[i] = e->len[i + 1]; e->cap[i] = e->cap[i + 1]; ++i; }
    --e->nl;
    if (e->nl == 0) e_insline(e, 0, "", 0);
    e_touched(e, at);
}

static void e_clear(struct edit *e) {
    int i;
    i = 0;
    while (i < e->nl) { free(e->ln[i]); ++i; }
    e->nl = 0;
    e->hlsn = 0;
}

// The text, split into lines; a final newline makes no empty line after it.
static void e_settext(struct edit *e, char *s, int n) {
    int i, start;
    e_clear(e);
    start = 0;
    i = 0;
    while (i < n) {
        if (s[i] == 10) { e_insline(e, e->nl, s + start, i - start); start = i + 1; }
        ++i;
    }
    if (start < n) e_insline(e, e->nl, s + start, n - start);
    if (e->nl == 0) e_insline(e, 0, "", 0);
}

// The text as one buffer, a newline after every line; *PN its length.
static char *e_gettext(struct edit *e, int *pn) {
    char *b;
    int i, n, o;
    n = 0;
    i = 0;
    while (i < e->nl) { n = n + e->len[i] + 1; ++i; }
    b = (char *)ualloc(n + 1);
    o = 0;
    i = 0;
    while (i < e->nl) {
        if (e->len[i] > 0) memcpy(b + o, e->ln[i], e->len[i]);
        o = o + e->len[i];
        b[o++] = 10;
        ++i;
    }
    if (e->nl == 1 && e->len[0] == 0) o = 0;    // one empty line is an empty file
    b[o] = 0;
    *pn = o;
    return b;
}

// the character at (Y,X); the end of a line is its newline
static int e_char(struct edit *e, int y, int x) {
    if (y < 0 || y >= e->nl) return 10;
    return x < e->len[y] ? e->ln[y][x] & 255 : 10;
}

// The text from (Y0,X0) up to, not including, (Y1,X1).
static char *e_range(struct edit *e, int y0, int x0, int y1, int x1, int *pn) {
    char *b;
    int n, y, o, a, z;
    n = 0;
    y = y0;
    while (y <= y1) {
        a = y == y0 ? x0 : 0;
        z = y == y1 ? x1 : e->len[y] + 1;
        if (z > a) n = n + z - a;
        ++y;
    }
    b = (char *)ualloc(n + 1);
    o = 0;
    y = y0;
    while (y <= y1) {
        a = y == y0 ? x0 : 0;
        z = y == y1 ? x1 : e->len[y] + 1;
        while (a < z) { b[o++] = a < e->len[y] ? e->ln[y][a] : 10; ++a; }
        ++y;
    }
    b[o] = 0;
    *pn = o;
    return b;
}

// Delete from (Y0,X0) up to, not including, (Y1,X1). X1 past the end of
// its line takes the newline too.
static void e_delrange(struct edit *e, int y0, int x0, int y1, int x1) {
    int tail, k;
    if (y1 >= e->nl) { y1 = e->nl - 1; x1 = e->len[y1]; }
    if (x1 > e->len[y1]) {
        if (y1 + 1 < e->nl) { ++y1; x1 = 0; } else x1 = e->len[y1];
    }
    if (x0 > e->len[y0]) x0 = e->len[y0];
    tail = e->len[y1] - x1;
    e_reserve(e, y0, x0 + tail);
    // within one line this copies leftwards, which a forward copy does safely
    k = 0;
    while (k < tail) { e->ln[y0][x0 + k] = e->ln[y1][x1 + k]; ++k; }
    e->len[y0] = x0 + tail;
    k = y1;
    while (k > y0) { e_delline(e, y0 + 1); --k; }
    e_touched(e, y0);
}

static int e_ry, e_rx;    // where e_instext left off

// Insert S (N bytes, newlines splitting lines) at (Y,X).
static void e_instext(struct edit *e, int y, int x, char *s, int n) {
    int i, start, tail;
    char *t;
    e_touched(e, y);
    if (x > e->len[y]) x = e->len[y];
    // cut the rest of the line off, append the pieces, put it back
    tail = e->len[y] - x;
    t = (char *)ualloc(tail + 1);
    if (tail > 0) memcpy(t, e->ln[y] + x, tail);
    e->len[y] = x;
    start = 0;
    i = 0;
    while (i <= n) {
        if (i == n || s[i] == 10) {
            e_reserve(e, y, e->len[y] + i - start);
            if (i > start) memcpy(e->ln[y] + e->len[y], s + start, i - start);
            e->len[y] = e->len[y] + i - start;
            if (i < n) { ++y; e_insline(e, y, "", 0); }
            start = i + 1;
        }
        ++i;
    }
    e_ry = y; e_rx = e->len[y];
    e_reserve(e, y, e->len[y] + tail);
    if (tail > 0) memcpy(e->ln[y] + e->len[y], t, tail);
    e->len[y] = e->len[y] + tail;
    free(t);
}

static void e_inschar(struct edit *e, int c) {
    char one[2];
    one[0] = c; one[1] = 0;
    e_instext(e, e->cy, e->cx, one, 1);
    e->cy = e_ry; e->cx = e_rx;
}

// ---- undo ---------------------------------------------------------------------------

static void e_snap_push(char **text, int *len, int *cy, int *cx, int *n, char *t, int tn, int y, int x) {
    int i;
    if (*n == UNDO_MAX) {
        free(text[0]);
        i = 0;
        while (i < UNDO_MAX - 1) { text[i] = text[i + 1]; len[i] = len[i + 1]; cy[i] = cy[i + 1]; cx[i] = cx[i + 1]; ++i; }
        --*n;
    }
    text[*n] = t; len[*n] = tn; cy[*n] = y; cx[*n] = x;
    ++*n;
}

static void e_redo_clear(struct edit *e) {
    while (e->rn > 0) { --e->rn; free(e->rtext[e->rn]); }
}

// Before a change: remember the text as it is.
static void e_save_undo(struct edit *e) {
    char *t;
    int n;
    t = e_gettext(e, &n);
    e_snap_push(e->utext, e->ulen, e->ucy, e->ucx, &e->un, t, n, e->cy, e->cx);
    e_redo_clear(e);
}

static void e_undo(struct edit *e, int redo) {
    char *t;
    int n;
    if (redo ? e->rn == 0 : e->un == 0) { e_say(e, redo ? "Already at newest change" : "Already at oldest change"); return; }
    t = e_gettext(e, &n);
    if (redo) {
        e_snap_push(e->utext, e->ulen, e->ucy, e->ucx, &e->un, t, n, e->cy, e->cx);
        --e->rn;
        e_settext(e, e->rtext[e->rn], e->rlen[e->rn]);
        e->cy = e->rcy[e->rn]; e->cx = e->rcx[e->rn];
        free(e->rtext[e->rn]);
    } else {
        e_snap_push(e->rtext, e->rlen, e->rcy, e->rcx, &e->rn, t, n, e->cy, e->cx);
        --e->un;
        e_settext(e, e->utext[e->un], e->ulen[e->un]);
        e->cy = e->ucy[e->un]; e->cx = e->ucx[e->un];
        free(e->utext[e->un]);
    }
    e->modified = 1;
    e_say(e, redo ? "redone" : "undone");
}

// ---- files ---------------------------------------------------------------------------

static void f_reveal(struct edit *e, char *path);
static void e_findbar(struct win *w, int dir, int here);
static void e_find_open(struct win *w);
static void e_find_act(struct win *w, int a);
static void ide_save();
static void x_compile(struct edit *e);
static void f_add(struct edit *e, char *path);
static void e_dirname(char *path, char *out);

static void e_retitle(struct win *w) {
    struct edit *e;
    int k;
    e = E(w);
    if (e->path[0]) {
        k = ui_len(e->path);
        while (k > 0 && e->path[k - 1] != '/') --k;
        ui_cpy(sb, e->path + k);
    } else ui_cpy(sb, "Untitled");
    if (e->modified) ui_cat(sb, " *");
    ui_cat(sb, " - IDE");
    win_title(w, sb);
}

static int e_load(struct edit *e, char *path) {
    int fd, r, n, cap, st[4];
    char *b, *nb;
    if ((fd = uopen(path, O_RD)) < 0) return 0;
    cap = (ustat(path, st) == 0 && st[1] > 0) ? st[1] + 1 : 4096;
    b = (char *)ualloc(cap + 1);
    n = 0;
    while (1) {
        if (n == cap) { nb = (char *)ualloc(cap * 2 + 1); memcpy(nb, b, n); free(b); b = nb; cap = cap * 2; }
        r = uread(fd, b + n, cap - n);
        if (r <= 0) break;
        n = n + r;
    }
    uclose(fd);
    e_settext(e, b, n);
    free(b);
    if (e->xobj) { e->xobj = 0; e->xshown = 0; e->xtab = 0; }   // text again, after a compiled file
    ui_ncpy(e->path, path, 128);
    e->cy = 0; e->cx = 0; e->want = 0; e->top = 0; e->left = 0;
    e->modified = 0;
    while (e->un > 0) { --e->un; free(e->utext[e->un]); }
    e_redo_clear(e);
    f_reveal(e, e->path);
    return 1;
}

static int e_save(struct edit *e, char *path) {
    int fd, r, n;
    char *t;
    if (!path[0]) { e_say(e, "No file name"); return 0; }
    if (e->xobj) { e_say(e, "A compiled file is shown, not text: there is nothing to save"); return 0; }
    if ((fd = uopen(path, O_WR + O_CREATE + O_TRUNCATE)) < 0) { e_say(e, "Cannot write that file"); return 0; }
    t = e_gettext(e, &n);
    r = n > 0 ? write(fd, t, n) : 0;
    uclose(fd);
    free(t);
    if (r != n) { e_say(e, "Write failed"); return 0; }
    if (path != e->path) ui_ncpy(e->path, path, 128);
    e->modified = 0;
    ui_cpy(e->msg, "\"");
    ui_cat(e->msg, path);
    ui_cat(e->msg, "\" written, ");
    ui_num(e->msg + ui_len(e->msg), e->nl);
    ui_cat(e->msg, " lines");
    f_add(e, e->path);
    f_reveal(e, e->path);
    x_compile(e);
    return 1;
}

// Binary files, by their names' ends; then any file with a NUL in its
// first bytes, which text never has.
static char *bin_ext = " .c4r .c4o .c4l .c4s .c4m .tgz .tar .gz .zip .z .wad .wl1 .wl6 .sod .rtl .rts .grp .pak .bin .img .vfs .png .jpg .gif .bmp .ico .wav .mp3 .ogg .mid .voc .exe .com .o .a .so ";
static int e_binary(char *p) {
    int i, k, fd, n;
    char ext[12];
    k = ui_len(p);
    i = k;
    while (i > 0 && p[i - 1] != '.' && p[i - 1] != '/') --i;
    if (i > 0 && p[i - 1] == '.' && k - i + 1 < 12) {
        n = 0;
        while (i - 1 + n < k) { ext[n] = p[i - 1 + n]; if (ext[n] >= 'A' && ext[n] <= 'Z') ext[n] = ext[n] + 32; ++n; }
        if (hl_inwords(ext, n, bin_ext)) return 1;
    }
    if ((fd = uopen(p, O_RD)) < 0) return 0;
    n = uread(fd, sb, 512);
    uclose(fd);
    i = 0;
    while (i < n) { if (!sb[i]) return 1; ++i; }
    return 0;
}

// A compiled file: C4R's header, whatever its name
static int e_isobj(char *p) {
    int fd, n;
    if ((fd = uopen(p, O_RD)) < 0) return 0;
    n = uread(fd, sb, 4);
    uclose(fd);
    return n == 4 && sb[0] == 'C' && sb[1] == '4' && sb[2] == 'R';
}
// ... into the Code tab alone, as it is: the text is put away
static int e_open_obj(struct win *w, char *path) {
    struct edit *e;
    char dir[128];
    e = E(w);
    if (!e->xp) e->xp = xp_new();
    e_settext(e, "", 0);
    while (e->un > 0) { --e->un; free(e->utext[e->un]); }
    e_redo_clear(e);
    ui_ncpy(e->path, path, 128);
    e->cy = 0; e->cx = 0; e->want = 0; e->top = 0; e->left = 0; e->modified = 0; e->tsel = 0;
    e->xobj = 1; e->xshown = 1; e->xtab = 1;
    e_dirname(path, dir);
    xp_load(e->xp, path, dir);
    f_reveal(e, e->path);
    return 1;
}

// A file into the editor: 1 opened, 0 cannot, 2 asked first (a binary
// file, which A_BINARY's answer opens). A compiled file opens in the Code
// tab.
static int e_open(struct win *w, char *path, int force) {
    struct edit *e;
    e = E(w);
    if (!force && e_isobj(path)) return e_open_obj(w, path);
    if (!force && e_binary(path)) {
        ui_ncpy(e->pend, path, 128);
        ui_cpy(sb, "'");
        ui_ncat(sb, ui_base(path), 200);
        ui_cat(sb, "' does not look like text: it is a binary file, which the IDE cannot show, and would spoil if it saved it. Open it anyway?");
        wk_msgbox(w->id, A_BINARY, "IDE", sb, WK_OKCANCEL);
        return 2;
    }
    if (!e_load(e, path)) return 0;
    x_compile(e);
    return 1;
}

// ---- the cursor ------------------------------------------------------------------------

static void e_clamp(struct edit *e) {
    int max;
    if (e->cy >= e->nl) e->cy = e->nl - 1;
    if (e->cy < 0) e->cy = 0;
    max = e->len[e->cy];
    // Normal mode sits ON a character; Insert can sit after the last
    if (e->vim && e->mode != M_INSERT && max > 0) max = max - 1;
    if (e->cx > max) e->cx = max;
    if (e->cx < 0) e->cx = 0;
}

static int e_firstnb(struct edit *e, int y) {
    int x;
    x = 0;
    while (x < e->len[y] && (e->ln[y][x] == ' ' || e->ln[y][x] == 9)) ++x;
    return x;
}

// Step one position forward (dir 1) or back (-1) over the text, the
// newline at each line's end included. 0 at either end of the text.
static int e_step(struct edit *e, int *y, int *x, int dir) {
    if (dir > 0) {
        if (*x < e->len[*y]) { ++*x; return 1; }
        if (*y + 1 >= e->nl) return 0;
        ++*y; *x = 0; return 1;
    }
    if (*x > 0) { --*x; return 1; }
    if (*y == 0) return 0;
    --*y; *x = e->len[*y]; return 1;
}

// w / W: the start of the next word
static void e_word_fwd(struct edit *e, int *y, int *x, int big) {
    int c, sy;
    c = e_class(e_char(e, *y, *x), big);
    if (c) while (e_class(e_char(e, *y, *x), big) == c) { if (!e_step(e, y, x, 1)) return; }
    sy = *y;
    while (e_class(e_char(e, *y, *x), big) == 0) {
        // an empty line is a word of its own
        if (*y != sy && e->len[*y] == 0) return;
        if (!e_step(e, y, x, 1)) return;
    }
}

// e / E: the end of this word or the next
static void e_word_end(struct edit *e, int *y, int *x, int big) {
    int c, ny, nx;
    if (!e_step(e, y, x, 1)) return;
    while (e_class(e_char(e, *y, *x), big) == 0) { if (!e_step(e, y, x, 1)) return; }
    c = e_class(e_char(e, *y, *x), big);
    while (1) {
        ny = *y; nx = *x;
        if (!e_step(e, &ny, &nx, 1)) return;
        if (e_class(e_char(e, ny, nx), big) != c) return;
        *y = ny; *x = nx;
    }
}

// b / B: the start of this word or the previous one
static void e_word_back(struct edit *e, int *y, int *x, int big) {
    int c, py, px;
    if (!e_step(e, y, x, 0 - 1)) return;
    while (e_class(e_char(e, *y, *x), big) == 0) {
        if (e->len[*y] == 0 && *x == 0) return;
        if (!e_step(e, y, x, 0 - 1)) return;
    }
    c = e_class(e_char(e, *y, *x), big);
    while (1) {
        py = *y; px = *x;
        if (!e_step(e, &py, &px, 0 - 1)) return;
        if (e_class(e_char(e, py, px), big) != c) return;
        *y = py; *x = px;
    }
}

// %: the bracket matching the one at or after the cursor on this line
static int e_match(struct edit *e, int *y, int *x) {
    int c, open, close, dir, depth, ty, tx, k;
    k = *x;
    while (k < e->len[*y]) {
        c = e->ln[*y][k];
        if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') break;
        ++k;
    }
    if (k >= e->len[*y]) return 0;
    c = e->ln[*y][k];
    if (c == '(' || c == ')') { open = '('; close = ')'; }
    else if (c == '[' || c == ']') { open = '['; close = ']'; }
    else { open = '{'; close = '}'; }
    dir = (c == open) ? 1 : 0 - 1;
    ty = *y; tx = k; depth = 0;
    while (1) {
        c = e_char(e, ty, tx);
        if (c == open) depth = depth + dir;
        else if (c == close) depth = depth - dir;
        if (depth == 0) { *y = ty; *x = tx; return 1; }
        if (!e_step(e, &ty, &tx, dir)) return 0;
    }
    return 0;
}

// search for the literal S from just past (or before) the cursor, wrapping
static int e_find(struct edit *e, char *s, int dir, int *py, int *px) {
    int y, x, n, k, tries;
    n = ui_len(s);
    if (!n) return 0;
    y = *py; x = *px;
    tries = 0;
    while (tries <= e->nl + 1) {
        if (dir > 0) {
            ++x;
            if (x > e->len[y] - n) { y = (y + 1) % e->nl; x = 0 - 1; ++tries; continue; }
        } else {
            --x;
            if (x < 0) { y = (y + e->nl - 1) % e->nl; x = e->len[y] - n + 1; ++tries; continue; }
        }
        if (x < 0) continue;
        k = 0;
        while (k < n && e->ln[y][x + k] == s[k]) ++k;
        if (k == n) { *py = y; *px = x; return 1; }
    }
    return 0;
}

// ---- the build pane --------------------------------------------------------------------

static int e_digits(char *s, int *pv) {
    int n, v;
    n = 0; v = 0;
    while (s[n] >= '0' && s[n] <= '9') { v = v * 10 + (s[n] - '0'); ++n; }
    *pv = v;
    return n;
}

// does the file exist? then it is a place an error can point at
static int e_exists(char *p) {
    int st[4];
    return ustat(p, st) == 0 && st[0] == 2;
}

// An error's file: as written if it is there, else against the build's
// directory, the edited file's, or the top of the source tree.
static void e_resolve(struct edit *e, char *p, char *out) {
    int k;
    if (p[0] == '/' || e_exists(p)) { ui_cpy(out, p); return; }
    ui_cpy(out, e->bdir); ui_cat(out, "/"); ui_cat(out, p);
    if (e_exists(out)) return;
    ui_cpy(out, e->path);
    k = ui_len(out);
    while (k > 0 && out[k - 1] != '/') --k;
    out[k] = 0;
    ui_cat(out, p);
    if (e_exists(out)) return;
    ui_cpy(out, "/usr/"); ui_cat(out, p);
    if (e_exists(out)) return;
    ui_cpy(out, p);
}

static void e_add_error(struct edit *e, char *file, int fn, int line, int logline) {
    char name[128];
    if (e->en >= ERR_MAX || fn <= 0 || fn > 120 || line <= 0) return;
    memcpy(name, file, fn);
    name[fn] = 0;
    e->epath[e->en] = (char *)ualloc(128);
    e_resolve(e, name, e->epath[e->en]);
    e->eline[e->en] = line;
    e->elog[e->en] = logline;
    ++e->en;
}

// What a line of build output says: a command b4ke ran (remember the
// source it names), or an error.
static void e_parse(struct edit *e, char *s, int logline) {
    int i, j, k, n, v;
    if (s[0] == '+' && s[1] == ' ') {
        // "+ c4sc ... src/x.c out.c4o": the last word naming a source
        i = 2;
        while (s[i]) {
            while (s[i] == ' ') ++i;
            j = i;
            while (s[j] && s[j] != ' ') ++j;
            if (j - i > 2 && s[j - 2] == '.' && (s[j - 1] == 'c' || s[j - 1] == 'h') && j - i < 120) {
                memcpy(e->bctx, s + i, j - i);
                e->bctx[j - i] = 0;
            }
            i = j;
        }
        return;
    }
    // b4ke's "did not make" and "exited" follow from an error already
    // listed; only when nothing said why are they the error to see
    if (e->en > 0 && s[0] == 'b' && s[1] == '4' && s[2] == 'k' && s[3] == 'e' && s[4] == ':') return;
    // "FILE:N:" anywhere
    i = 0;
    while (s[i]) {
        if (s[i] == ':' && (n = e_digits(s + i + 1, &v)) > 0 && s[i + 1 + n] == ':') {
            j = i;
            while (j > 0 && s[j - 1] != ' ' && s[j - 1] != 9) --j;
            if (i > j) { e_add_error(e, s + j, i - j, v, logline); return; }
        }
        ++i;
    }
    // c4lc's "line N:", against the source the last command named
    i = 0;
    while (s[i]) {
        if (s[i] == 'l' && s[i + 1] == 'i' && s[i + 2] == 'n' && s[i + 3] == 'e' && s[i + 4] == ' ' &&
            (n = e_digits(s + i + 5, &v)) > 0 && e->bctx[0]) {
            e_add_error(e, e->bctx, ui_len(e->bctx), v, logline);
            return;
        }
        ++i;
    }
    // c4cc's "N: WARNING ..." / "N: error ..."
    if ((n = e_digits(s, &v)) > 0 && s[n] == ':' && e->bctx[0]) {
        k = ui_len(e->bctx);
        e_add_error(e, e->bctx, k, v, logline);
    }
}

static void e_logline(struct edit *e, char *s, int n) {
    int i;
    if (e->blogn == BLOG_MAX) {
        // the oldest line goes, and errors pointing into the log move up
        free(e->blog[0]);
        i = 0;
        while (i < BLOG_MAX - 1) { e->blog[i] = e->blog[i + 1]; ++i; }
        --e->blogn;
        i = 0;
        while (i < e->en) { --e->elog[i]; ++i; }
    }
    e->blog[e->blogn] = (char *)ualloc(n + 1);
    memcpy(e->blog[e->blogn], s, n);
    e->blog[e->blogn][n] = 0;
    e_parse(e, e->blog[e->blogn], e->blogn);
    ++e->blogn;
    // the end stays in view, unless the pane was scrolled up to read
    if (e->blogn > BROWS && e->btop >= e->blogn - 1 - BROWS) e->btop = e->blogn - BROWS;
}

static void e_build_clear(struct edit *e) {
    while (e->blogn > 0) { --e->blogn; free(e->blog[e->blogn]); }
    while (e->en > 0) { --e->en; free(e->epath[e->en]); }
    e->ecur = 0 - 1; e->btop = 0; e->bsel = 0 - 1; e->bpartn = 0; e->bctx[0] = 0; e->bleft = 0;
}

// the directory of PATH, into OUT ("/" for a file at the root)
static void e_dirname(char *path, char *out) {
    int k;
    ui_cpy(out, path);
    k = ui_len(out);
    while (k > 0 && out[k - 1] != '/') --k;
    if (k <= 1) { out[0] = '/'; out[1] = 0; return; }
    out[k - 1] = 0;
}

static int e_namech(int c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'; }

// Does the build file P name the file BASE (as a word: "mandel.c" but
// not "mandel.c4o" or "xmandel.c")?
static int e_names(char *p, char *base) {
    char *t;
    int fd, n, i, m, j, hit;
    if ((fd = uopen(p, O_RD)) < 0) return 0;
    t = (char *)ualloc(65537);
    n = uread(fd, t, 65536);
    uclose(fd);
    if (n < 0) n = 0;
    t[n] = 0;
    m = ui_len(base);
    hit = 0;
    i = 0;
    while (!hit && i + m <= n) {
        j = 0;
        while (j < m && t[i + j] == base[j]) ++j;
        if (j == m && (i == 0 || !e_namech(t[i - 1])) && !e_namech(t[i + m]) && t[i + m] != '.') hit = 1;
        ++i;
    }
    free(t);
    return hit;
}

// The BUILD.B4K that builds PATH, looking up from DIR: its directory
// into OUT. 2: the nearest one that names the file. 1: none does, and
// OUT is the nearest there is -- /usr's own builds the tree, not
// src/tests/mandel.c, so a lone .c file is better built alone (e_make).
// 0: there is none.
static int e_find_build(char *dir, char *path, char *out) {
    char p[160], near[128], *base;
    int k, found;
    base = path + ui_len(path);
    while (base > path && base[0 - 1] != '/') --base;
    ui_cpy(out, dir);
    found = 0;
    while (1) {
        ui_cpy(p, out);
        if (!(p[0] == '/' && p[1] == 0)) ui_cat(p, "/");
        ui_cat(p, "BUILD.B4K");
        if (e_exists(p)) {
            if (e_names(p, base)) return 2;
            if (!found) { ui_cpy(near, out); found = 1; }
        }
        if (out[0] == '/' && out[1] == 0) break;
        k = ui_len(out);
        while (k > 0 && out[k - 1] != '/') --k;
        if (k <= 1) { out[0] = '/'; out[1] = 0; }
        else out[k - 1] = 0;
    }
    if (found) ui_cpy(out, near);
    return found;
}

// A BUILD.B4K may say what to run: "SET RUN command".
static void e_find_run(struct edit *e, char *dir) {
    char p[160];
    char *t;
    int fd, n, i, k;
    e->runcmd[0] = 0;
    ui_cpy(p, dir);
    if (!(p[0] == '/' && p[1] == 0)) ui_cat(p, "/");
    ui_cat(p, "BUILD.B4K");
    if ((fd = uopen(p, O_RD)) < 0) return;
    t = (char *)ualloc(16385);
    n = uread(fd, t, 16384);
    uclose(fd);
    if (n < 0) n = 0;
    t[n] = 0;
    i = 0;
    while (i < n) {
        if ((i == 0 || t[i - 1] == 10) && t[i] == 'S' && t[i + 1] == 'E' && t[i + 2] == 'T' && t[i + 3] == ' ' &&
            t[i + 4] == 'R' && t[i + 5] == 'U' && t[i + 6] == 'N' && t[i + 7] == ' ') {
            k = 0;
            i = i + 8;
            while (i < n && t[i] != 10 && k < 158) { e->runcmd[k++] = t[i]; ++i; }
            e->runcmd[k] = 0;
            break;
        }
        ++i;
    }
    free(t);
}

static void e_make(struct win *w) {
    struct edit *e;
    char dir[128];
    char name[64];
    char **argv;
    int pin[2], pout[2], s0, s1, s2, k, j, fd, n;
    char *bf;
    int bk;
    e = E(w);
    if (e->building) { e_say(e, "A build is already running"); return; }
    if (e->xobj) return;                          // a compiled file: already built
    if (!e->path[0]) { e_say(e, "Save the file first (:w FILE)"); return; }
    if (e->modified && !e_save(e, e->path)) return;
    e_retitle(w);
    e_dirname(e->path, dir);
    argv = (char **)ualloc(8 * sizeof(int));
    argv[0] = "b4ke";
    bk = e_find_build(dir, e->path, e->bdir);
    if (bk == 2 || (bk == 1 && !ui_ends(e->path, ".c"))) {
        argv[1] = "-C"; argv[2] = e->bdir; argv[3] = 0;
        e_find_run(e, e->bdir);
        k = 3;
    } else if (ui_ends(e->path, ".c")) {
        // no build file names it: a build file of its own, which has cc
        // compile this one file and link it with libc4ix
        k = ui_len(e->path);
        j = k;
        while (j > 0 && e->path[j - 1] != '/') --j;
        memcpy(name, e->path + j, k - j - 2);
        name[k - j - 2] = 0;
        bf = (char *)ualloc(1024);
        ui_cpy(bf, "B4KE2\nDEPS /tmp/"); ui_cat(bf, name); ui_cat(bf, ".c4r : "); ui_cat(bf, e->path);
        ui_cat(bf, "\nRUN cc -O -l c4ix -I "); ui_cat(bf, dir); ui_cat(bf, " -o /tmp/"); ui_cat(bf, name);
        ui_cat(bf, ".c4r "); ui_cat(bf, e->path); ui_cat(bf, "\n");
        n = ui_len(bf);
        fd = uopen("/tmp/edit.b4k", O_WR + O_CREATE + O_TRUNCATE);
        if (fd < 0 || write(fd, bf, n) != n) { if (fd >= 0) uclose(fd); free(bf); e_say(e, "Cannot write /tmp/edit.b4k"); return; }
        uclose(fd);
        free(bf);
        ui_cpy(e->bdir, dir);
        argv[1] = "-C"; argv[2] = e->bdir; argv[3] = "-f"; argv[4] = "/tmp/edit.b4k"; argv[5] = 0;
        ui_cpy(e->runcmd, "/tmp/"); ui_cat(e->runcmd, name); ui_cat(e->runcmd, ".c4r");
        k = 5;
    } else {
        e_say(e, "Nothing to build: no BUILD.B4K above this file, and it is not a .c file");
        return;
    }

    // b4ke on pipes, as the Terminal runs its shell (term.c): our
    // ends are close-on-spawn, its stdin is a pipe nobody writes. Every
    // step is checked, as there: with the table full, a desktop that
    // went on would keep the build's pipe as its stdout for good.
    if (upipe(pin) < 0) { e_say(e, "No pipe for the build"); return; }
    if (upipe(pout) < 0) { uclose(pin[0]); uclose(pin[1]); e_say(e, "No pipe for the build"); return; }
    s0 = udup(STDIN); s1 = udup(STDOUT); s2 = udup(STDERR);
    e->pid = 0 - 1;
    if (s0 >= 0 && s1 >= 0 && s2 >= 0) {
        ucloexec(pin[1], 1); ucloexec(pout[0], 1);
        ucloexec(s0, 1); ucloexec(s1, 1); ucloexec(s2, 1);
        if (udup2(pin[0], STDIN) >= 0 && udup2(pout[1], STDOUT) >= 0 && udup2(pout[1], STDERR) >= 0)
            e->pid = spawn("/bin/b4ke", k, argv);
        // s0, s1 and s2 are open, so these cannot fail
        udup2(s0, STDIN); udup2(s1, STDOUT); udup2(s2, STDERR);
    }
    uclose(pin[0]); uclose(pout[1]); uclose(pin[1]);
    if (e->pid < 0) {
        uclose(pout[0]);
        e_say(e, s0 >= 0 && s1 >= 0 && s2 >= 0 ? "Cannot start b4ke" : "No descriptors for the build");
        uclose(s0); uclose(s1); uclose(s2);   // one that is -1 closes nothing
        return;
    }
    uclose(s0); uclose(s1); uclose(s2);
    e->out_r = pout[0];
    e_build_clear(e);
    e->building = 1; e->bshown = 1; e->bcancel = 0;
    ui_cpy(sb, "b4ke"); j = 1;
    while (j < k) { ui_cat(sb, " "); ui_cat(sb, argv[j]); ++j; }
    e_logline(e, sb, ui_len(sb));
    e_say(e, "Building...");
}

static void e_goto_error(struct win *w, int i);

// The Code tab's compile, of the saved file, when the tab is open
static void x_compile(struct edit *e) {
    char dir[128];
    if (!e->xshown || !e->xp || !e->path[0] || e->xobj) return;
    e_dirname(e->path, dir);
    xp_compile(e->xp, e->path, dir);
}
// F7: the Code tab, opened the first time; then from one tab to the other
static void e_code(struct win *w) {
    struct edit *e;
    e = E(w);
    if (e->xobj) return;
    if (!e->xp) e->xp = xp_new();
    if (e->xshown) { e->xtab = !e->xtab; return; }
    e->xshown = 1; e->xtab = 1;
    x_compile(e);
}
// the Code tab closed
static void x_close(struct edit *e) { e->xshown = 0; e->xtab = 0; }

// A line the Code tab asked for: in this text, or another file's in a
// window of its own
static void x_goto(struct win *w) {
    struct edit *e, *o;
    struct win *ow;
    char p[128];
    int line, i;
    e = E(w);
    line = xp_goto(e->xp, p);
    if (line <= 0) return;
    if (!e->xobj && ui_eq(p, e->path)) {
        e->xtab = 0;
        e->cy = line - 1; e_clamp(e); e->cx = e_firstnb(e, e->cy); e->want = e->cx; e->tsel = 0;
        if (e->vim && e->mode != M_INSERT) e->mode = M_NORMAL;
        return;
    }
    i = edit_open(p);
    if (i < 0 || !(ow = win_get(i)) || ow->kind != K_EDIT) return;
    o = E(ow);
    o->cy = line - 1; e_clamp(o); o->cx = e_firstnb(o, o->cy); o->want = o->cx;
}

// Output waiting in the build's pipe, and the Code pane's compile; never
// blocks (wm.c's loop calls this).
void edit_tick(struct win *w) {
    struct edit *e;
    char buf[512];
    int n, i;
    e = E(w);
    if (e->xp && xp_tick(e->xp)) mark_win_dirty(w);
    if (!e->building) return;
    while ((n = uavail(e->out_r)) > 0) {
        if (n > 512) n = 512;
        n = uread(e->out_r, buf, n);
        if (n <= 0) break;
        i = 0;
        while (i < n) {
            if (buf[i] == 10 || e->bpartn >= 250) { e_logline(e, e->bpart, e->bpartn); e->bpartn = 0; }
            if (buf[i] != 10 && buf[i] != 13) e->bpart[e->bpartn++] = buf[i];
            ++i;
        }
        mark_win_dirty(w);   // only the build pane moved
    }
    if (n < 0) {
        // every writer has gone: the build is over
        if (e->bpartn) { e_logline(e, e->bpart, e->bpartn); e->bpartn = 0; }
        uclose(e->out_r);
        e->bstatus = uwait(e->pid);
        e->building = 0;
        if (e->bstatus == 0) ui_cpy(e->msg, "Build finished");
        else if (e->bcancel) ui_cpy(e->msg, "Build cancelled");
        else {
            ui_cpy(e->msg, "Build failed: ");
            ui_num(e->msg + ui_len(e->msg), e->en);
            ui_cat(e->msg, e->en == 1 ? " error" : " errors");
            if (e->en > 0) e_goto_error(w, 0);
        }
        mark_dirty();
    }
}

// Stop the build: what b4ke is running first -- a compiler it is waiting
// on would run on without it, and nobody would wait for it -- then b4ke.
// Every one is waited for, so none is left a zombie.
static int binfo[32];
static void e_stop_build(struct edit *e) {
    int kids[8], nk, i;
    if (!e->building) return;
    nk = 0; i = 0;
    while (nk < 8 && utaskinfo(i, binfo)) { if (binfo[1] == e->pid) { kids[nk] = binfo[0]; ++nk; } ++i; }
    i = 0;
    while (i < nk) { uintr(kids[i]); ukill(kids[i], SIGTERM); ++i; }
    ukill(e->pid, SIGTERM);
    uclose(e->out_r);
    i = 0;
    while (i < nk) { uwait(kids[i]); ++i; }
    e->bstatus = uwait(e->pid);
    e->building = 0;
}
static void e_cancel(struct win *w) {
    struct edit *e;
    e = E(w);
    if (!e->building) { e_say(e, "No build is running"); return; }
    e_stop_build(e);
    e->bcancel = 1;
    if (e->bpartn) { e_logline(e, e->bpart, e->bpartn); e->bpartn = 0; }
    e_logline(e, "-- cancelled --", 15);
    ui_cpy(e->msg, "Build cancelled");
    mark_dirty();
}

void edit_close(struct win *w) {
    struct edit *e;
    int i;
    e = E(w);
    e_stop_build(e);
    if (e->xp) { xp_free(e->xp); e->xp = 0; }
    i = 0;
    while (i < e->fn) { free(e->fpath[i]); ++i; }
    if (e->fpath) { free((char *)e->fpath); free((char *)e->fdepth); free((char *)e->fflag); }
    e->fpath = 0; e->fn = 0;
}

// ---- changes -----------------------------------------------------------------------------

static void e_yank(struct edit *e, int y0, int x0, int y1, int x1, int linewise) {
    if (e->reg) free(e->reg);
    if (linewise) e->reg = e_range(e, y0, 0, y1, e->len[y1] + 1, &e->regn);
    else e->reg = e_range(e, y0, x0, y1, x1, &e->regn);
    e->regline = linewise;
}

static void e_indent(struct edit *e, int y0, int y1, int more) {
    int y, k;
    y = y0;
    while (y <= y1) {
        if (more) { if (e->len[y] > 0) e_instext(e, y, 0, "    ", 4); }
        else {
            k = 0;
            while (k < 4 && k < e->len[y] && e->ln[y][k] == ' ') ++k;
            if (k) e_delrange(e, y, 0, y, k);
        }
        ++y;
    }
}

// OP over a range. LINEWISE: whole lines Y0..Y1. Otherwise (Y0,X0) up
// to (Y1,X1), including X1 when INCL.
static void e_apply(struct edit *e, int op, int y0, int x0, int y1, int x1, int linewise, int incl) {
    int t, ind;
    if (y1 < y0 || (y1 == y0 && x1 < x0)) { t = y0; y0 = y1; y1 = t; t = x0; x0 = x1; x1 = t; }
    if (!linewise && incl) ++x1;
    if (op == 'y') {
        e_yank(e, y0, x0, y1, x1, linewise);
        e->cy = y0; e->cx = linewise ? e->cx : x0;
        return;
    }
    e_save_undo(e);
    if (op == '>' || op == '<') { e_indent(e, y0, y1, op == '>'); e->cy = y0; e->cx = e_firstnb(e, y0); return; }
    e_yank(e, y0, x0, y1, x1, linewise);
    if (linewise) {
        if (op == 'c') {
            ind = e_firstnb(e, y0);
            e_delrange(e, y0, ind, y1, e->len[y1]);
            e->cy = y0; e->cx = ind;
            e->mode = M_INSERT;
            return;
        }
        t = y1 - y0 + 1;
        while (t > 0) { e_delline(e, y0); --t; }
        e->cy = y0;
        e_clamp(e);
        e->cx = e_firstnb(e, e->cy);
        return;
    }
    e_delrange(e, y0, x0, y1, x1);
    e->cy = y0; e->cx = x0;
    if (op == 'c') e->mode = M_INSERT;
}

static void e_put(struct edit *e, int before) {
    int y;
    if (!e->reg || !e->regn) { e_say(e, "Nothing to put"); return; }
    e_save_undo(e);
    if (e->regline) {
        y = before ? e->cy : e->cy + 1;
        if (y >= e->nl) {
            // after the last line: start a new one, then fill it
            e_insline(e, e->nl, "", 0);
            e_instext(e, y, 0, e->reg, e->regn - 1);
        } else {
            e_insline(e, y, "", 0);
            e_instext(e, y, 0, e->reg, e->regn - 1);
        }
        e->cy = y; e->cx = e_firstnb(e, y);
        return;
    }
    e_instext(e, e->cy, before || e->len[e->cy] == 0 ? e->cx : e->cx + 1, e->reg, e->regn);
    e->cy = e_ry; e->cx = e_rx > 0 ? e_rx - 1 : 0;
}

static void e_join(struct edit *e, int n) {
    int x, k;
    e_save_undo(e);
    while (n > 0 && e->cy + 1 < e->nl) {
        x = e->len[e->cy];
        k = e_firstnb(e, e->cy + 1);
        e_delrange(e, e->cy + 1, 0, e->cy + 1, k);
        e_delrange(e, e->cy, x, e->cy + 1, 0);
        if (x > 0 && e->len[e->cy] > x) e_instext(e, e->cy, x, " ", 1);
        e->cx = x;
        --n;
    }
}

// Enter in Insert: split the line, keeping the indent
static void e_newline(struct edit *e) {
    int ind;
    char spaces[64];
    ind = e_firstnb(e, e->cy);
    if (ind > e->cx) ind = e->cx;
    if (ind > 60) ind = 60;
    memset(spaces, ' ', ind);
    e_instext(e, e->cy, e->cx, "\n", 1);
    e->cy = e_ry; e->cx = 0;
    if (ind) { e_instext(e, e->cy, 0, spaces, ind); e->cx = ind; }
}

static void e_open_line(struct edit *e, int above) {
    int ind, y;
    char spaces[64];
    e_save_undo(e);
    ind = e_firstnb(e, e->cy);
    if (ind > 60) ind = 60;
    memset(spaces, ' ', ind);
    y = above ? e->cy : e->cy + 1;
    e_insline(e, y, spaces, ind);
    e->cy = y; e->cx = ind;
    e->mode = M_INSERT;
}

// ---- motions ----------------------------------------------------------------------------

// f t F T: to (or just before) the Nth C on this line
static int e_motion_find(struct edit *e, int kind, int c, int n, int *ty, int *tx, int *incl) {
    int x, dir;
    x = e->cx;
    dir = (kind == 'f' || kind == 't') ? 1 : 0 - 1;
    // repeating t or T from just before a match must not find it again
    if ((kind == 't' || kind == 'T') && x + dir >= 0 && x + dir < e->len[e->cy] && e->ln[e->cy][x + dir] == c) x = x + dir;
    while (n > 0) {
        x = x + dir;
        while (x >= 0 && x < e->len[e->cy] && e->ln[e->cy][x] != c) x = x + dir;
        if (x < 0 || x >= e->len[e->cy]) return 0;
        --n;
    }
    if (kind == 't') --x;
    if (kind == 'T') ++x;
    *ty = e->cy; *tx = x;
    *incl = dir > 0;
    return 1;
}

// The motion a key names, from the cursor, N times. Returns 1 with
// (*ty,*tx) and how an operator takes it; 0 if the key is no motion;
// -1 if it begins one (g, f, t, ...) whose rest is still to come.
static int e_motion(struct edit *e, int code, int ch, int mods, int n,
                    int *ty, int *tx, int *lw, int *incl) {
    int y, x, k, c;
    y = e->cy; x = e->cx;
    *lw = 0; *incl = 0;
    if (mods & M_CTRL) {
        if (code == KEY_HOME) { *ty = 0; *tx = 0; *lw = 1; return 1; }
        if (code == KEY_END) { *ty = e->nl - 1; *tx = 0; *lw = 1; return 1; }
        if (code == KEY_LEFT) { k = n; while (k--) e_word_back(e, &y, &x, 0); *ty = y; *tx = x; return 1; }
        if (code == KEY_RIGHT) { k = n; while (k--) e_word_fwd(e, &y, &x, 0); *ty = y; *tx = x; return 1; }
        if (code == 68 || code == 85) {              // Ctrl-D, Ctrl-U: half a page
            k = e->rows / 2; if (k < 1) k = 1;
            *ty = code == 68 ? y + k : y - k; *tx = x; *lw = 1; return 1;
        }
        return 0;
    }
    if (code == KEY_LEFT || ch == 'h' || code == KEY_BACK) { *ty = y; *tx = x - n < 0 ? 0 : x - n; return 1; }
    if (code == KEY_RIGHT || ch == 'l' || ch == ' ') { *ty = y; *tx = x + n; return 1; }
    if (code == KEY_UP || ch == 'k') { *ty = y - n; *tx = e->want; *lw = 1; return 1; }
    if (code == KEY_DOWN || ch == 'j') { *ty = y + n; *tx = e->want; *lw = 1; return 1; }
    if (code == KEY_PGUP) { k = e->rows > 1 ? e->rows - 1 : 1; *ty = y - k * n; *tx = e->want; *lw = 1; return 1; }
    if (code == KEY_PGDN) { k = e->rows > 1 ? e->rows - 1 : 1; *ty = y + k * n; *tx = e->want; *lw = 1; return 1; }
    if (code == KEY_HOME || ch == '0') { *ty = y; *tx = 0; return 1; }
    if (ch == '^') { *ty = y; *tx = e_firstnb(e, y); return 1; }
    if (code == KEY_END || ch == '$') {
        *ty = y + n - 1; if (*ty >= e->nl) *ty = e->nl - 1;
        *tx = e->len[*ty] > 0 ? e->len[*ty] - 1 : 0; *incl = 1; e->want = 100000; return 1;
    }
    if (ch == 'w' || ch == 'W') { k = n; while (k--) e_word_fwd(e, &y, &x, ch == 'W'); *ty = y; *tx = x; return 1; }
    if (ch == 'b' || ch == 'B') { k = n; while (k--) e_word_back(e, &y, &x, ch == 'B'); *ty = y; *tx = x; return 1; }
    if (ch == 'e' || ch == 'E') { k = n; while (k--) e_word_end(e, &y, &x, ch == 'E'); *ty = y; *tx = x; *incl = 1; return 1; }
    if (ch == 'G') { *ty = e->count ? e->count - 1 : e->nl - 1; *tx = 0; *lw = 1; return 1; }
    if (ch == '}' || ch == '{') {
        k = n;
        while (k--) {
            c = ch == '}' ? 1 : 0 - 1;
            y = y + c;
            while (y > 0 && y < e->nl - 1 && e->len[y] != 0) y = y + c;
        }
        if (y < 0) y = 0;
        if (y >= e->nl) y = e->nl - 1;
        *ty = y; *tx = 0; return 1;
    }
    if (ch == '%') { if (!e_match(e, &y, &x)) return 0; *ty = y; *tx = x; *incl = 1; return 1; }
    if (ch == 'n' || ch == 'N') {
        if (!e->search[0]) { e_say(e, "No previous search"); return 0; }
        k = (ch == 'n') ? e->sdir : 0 - e->sdir;
        if (!e_find(e, e->search, k, &y, &x)) { e_say(e, "Pattern not found"); return 0; }
        *ty = y; *tx = x; return 1;
    }
    if (ch == ';' || ch == ',') {
        if (!e->fkind) return 0;
        k = e->fkind;
        if (ch == ',') k = (k == 'f') ? 'F' : (k == 'F') ? 'f' : (k == 't') ? 'T' : 't';
        return e_motion_find(e, k, e->fch, n, ty, tx, incl);
    }
    if (ch == 'g' || ch == 'f' || ch == 't' || ch == 'F' || ch == 'T') { e->pre = ch; return 0 - 1; }
    return 0;
}

// iw aw i( a( i{ a{ i" a" i' a': the range a text object covers
static int e_textobj(struct edit *e, int inner, int c, int *y0, int *x0, int *y1, int *x1) {
    int y, x, k, open, close, depth, cls, sy, sx;
    y = e->cy; x = e->cx;
    if (c == 'w' || c == 'W') {
        if (e->len[y] == 0) return 0;
        cls = e_class(e_char(e, y, x), c == 'W');
        sx = x;
        while (sx > 0 && e_class(e->ln[y][sx - 1], c == 'W') == cls) --sx;
        k = x;
        while (k + 1 < e->len[y] && e_class(e->ln[y][k + 1], c == 'W') == cls) ++k;
        if (!inner) { while (k + 1 < e->len[y] && e_isspace(e->ln[y][k + 1])) ++k; }
        *y0 = y; *x0 = sx; *y1 = y; *x1 = k;
        return 1;
    }
    if (c == '"' || c == 39) {
        sx = x;
        while (sx >= 0 && e->ln[y][sx] != c) --sx;
        if (sx < 0) return 0;
        k = sx + 1;
        while (k < e->len[y] && e->ln[y][k] != c) ++k;
        if (k >= e->len[y]) return 0;
        if (inner) { *x0 = sx + 1; *x1 = k - 1; } else { *x0 = sx; *x1 = k; }
        *y0 = y; *y1 = y;
        return *x1 >= *x0;
    }
    if (c == '(' || c == ')' || c == 'b') { open = '('; close = ')'; }
    else if (c == '{' || c == '}' || c == 'B') { open = '{'; close = '}'; }
    else if (c == '[' || c == ']') { open = '['; close = ']'; }
    else return 0;
    // out to the enclosing OPEN, then on to its CLOSE
    sy = y; sx = x; depth = 0;
    while (1) {
        k = e_char(e, sy, sx);
        if (k == close && !(sy == y && sx == x)) ++depth;
        else if (k == open) { if (depth == 0) break; --depth; }
        if (!e_step(e, &sy, &sx, 0 - 1)) return 0;
    }
    *y0 = sy; *x0 = sx;
    if (!e_match(e, &sy, &sx)) return 0;
    *y1 = sy; *x1 = sx;
    if (inner) {
        if (!e_step(e, y0, x0, 1)) return 0;
        if (!e_step(e, y1, x1, 0 - 1)) return 0;
    }
    return 1;
}

// ---- the command line ----------------------------------------------------------------

// append S to D, as much as fits in a status line
static void k_copy_tail(char *d, char *s) {
    int n, k;
    n = ui_len(d);
    k = 0;
    while (s[k] && n < 110) { d[n++] = s[k++]; }
    d[n] = 0;
}

static void e_goto_error(struct win *w, int i) {
    struct edit *e;
    e = E(w);
    if (i < 0 || i >= e->en) { e_say(e, "No more errors"); return; }
    e->ecur = i;
    e->bsel = e->elog[i];
    if (e->bsel < e->btop) e->btop = e->bsel;
    if (e->bsel >= e->btop + BROWS) e->btop = e->bsel - BROWS + 1;
    if (!ui_eq(e->epath[i], e->path)) {
        if (e->modified && !e_save(e, e->path)) return;
        if (!e_load(e, e->epath[i])) { e_say(e, "Cannot open the file the error names"); return; }
        e_retitle(w);
    }
    e->cy = e->eline[i] - 1;
    e->cx = 0;
    e_clamp(e);
    e->cx = e_firstnb(e, e->cy);
    e->want = e->cx;
    ui_cpy(e->msg, "(");
    ui_num(e->msg + 1, i + 1);
    ui_cat(e->msg, " of ");
    ui_num(e->msg + ui_len(e->msg), e->en);
    ui_cat(e->msg, ") ");
    k_copy_tail(e->msg, e->blog[e->elog[i]]);
}

// :s/old/new/ and :%s/old/new/g, literal text
static void e_subst(struct edit *e, char *a, int all) {
    char pat[64], rep[64];
    int n, k, y, y0, y1, x, global, pn, rn, count;
    if (*a != '/') { e_say(e, "Usage: s/old/new/[g]"); return; }
    ++a;
    n = 0; while (*a && *a != '/' && n < 63) pat[n++] = *a++;
    pat[n] = 0; pn = n;
    if (*a == '/') ++a;
    n = 0; while (*a && *a != '/' && n < 63) rep[n++] = *a++;
    rep[n] = 0; rn = n;
    if (*a == '/') ++a;
    global = *a == 'g';
    if (!pn) { e_say(e, "Empty pattern"); return; }
    e_save_undo(e);
    y0 = all ? 0 : e->cy; y1 = all ? e->nl - 1 : e->cy;
    count = 0;
    y = y0;
    while (y <= y1) {
        x = 0;
        while (x + pn <= e->len[y]) {
            k = 0;
            while (k < pn && e->ln[y][x + k] == pat[k]) ++k;
            if (k == pn) {
                e_delrange(e, y, x, y, x + pn);
                if (rn) e_instext(e, y, x, rep, rn);
                x = x + rn;
                ++count;
                if (!global) break;
            } else ++x;
        }
        ++y;
    }
    ui_num(e->msg, count);
    ui_cat(e->msg, count == 1 ? " substitution" : " substitutions");
}

static void e_ex(struct win *w, char *c) {
    struct edit *e;
    int v, n;
    e = E(w);
    while (*c == ' ') ++c;
    if (!*c) return;
    if ((n = e_digits(c, &v)) > 0 && !c[n]) { e->cy = v - 1; e_clamp(e); e->cx = e_firstnb(e, e->cy); return; }
    if (ui_eq(c, "$")) { e->cy = e->nl - 1; e->cx = e_firstnb(e, e->cy); return; }
    if (ui_eq(c, "w")) { e_save(e, e->path); e_retitle(w); return; }
    if (c[0] == 'w' && c[1] == ' ') { e_save(e, c + 2); e_retitle(w); return; }
    if (ui_eq(c, "q")) {
        if (e->modified) { e_say(e, "No write since last change (add ! to override)"); return; }
        win_close(win_index(w)); return;
    }
    if (ui_eq(c, "q!")) { win_close(win_index(w)); return; }
    if (ui_eq(c, "wq") || ui_eq(c, "x")) { if (e_save(e, e->path)) win_close(win_index(w)); return; }
    if (c[0] == 'e' && (c[1] == ' ' || (c[1] == '!' && c[2] == ' '))) {
        if (c[1] != '!' && e->modified) { e_say(e, "No write since last change (add ! to override)"); return; }
        c = c + (c[1] == '!' ? 3 : 2);
        if (!e_open(w, c, 0)) { e_settext(e, "", 0); ui_ncpy(e->path, c, 128); e->modified = 0; e->cy = 0; e->cx = 0; e_say(e, "New file"); }
        e_retitle(w);
        return;
    }
    if (ui_eq(c, "make")) { e_make(w); return; }
    if (ui_eq(c, "code")) { e_code(w); return; }
    if (ui_eq(c, "Ex") || ui_eq(c, "Explore") || ui_eq(c, "Lex") || ui_eq(c, "files")) { e->fshown = !e->fshown; return; }
    if (ui_eq(c, "syntax off") || ui_eq(c, "syn off")) { e->nosyn = 1; return; }
    if (ui_eq(c, "syntax on") || ui_eq(c, "syn on")) { e->nosyn = 0; return; }
    if (ui_eq(c, "set wrap")) { e->wrap = 1; e->left = 0; return; }
    if (ui_eq(c, "set nowrap")) { e->wrap = 0; return; }
    if (ui_eq(c, "cancel")) { e_cancel(w); return; }
    if (ui_eq(c, "run") || (c[0] == 'r' && c[1] == 'u' && c[2] == 'n' && c[3] == ' ')) {
        if (c[3] == ' ') ui_cpy(e->runcmd, c + 4);
        if (!e->runcmd[0]) { e_say(e, "Nothing to run yet: :make first, or :run COMMAND"); return; }
        run_command(e->runcmd);
        return;
    }
    if (ui_eq(c, "cn") || ui_eq(c, "cnext")) { e_goto_error(w, e->ecur + 1); return; }
    if (ui_eq(c, "cp") || ui_eq(c, "cprev")) { e_goto_error(w, e->ecur - 1); return; }
    if (ui_eq(c, "copen")) { e->bshown = 1; return; }
    if (ui_eq(c, "cclose")) { e->bshown = 0; return; }
    if (ui_eq(c, "set nu") || ui_eq(c, "set number")) { e->nu = 1; return; }
    if (ui_eq(c, "set nonu") || ui_eq(c, "set nonumber")) { e->nu = 0; return; }
    if (ui_eq(c, "set vim")) { e->vim = 1; e->tsel = 0; e->mode = M_NORMAL; e_clamp(e); return; }
    if (ui_eq(c, "set novim")) { e->vim = 0; e->mode = M_INSERT; e_say(e, "VIM mode off: type to edit; Esc for a command (set vim to come back)"); return; }
    if (c[0] == 's' && c[1] == '/') { e_subst(e, c + 1, 0); return; }
    if (c[0] == '%' && c[1] == 's' && c[2] == '/') { e_subst(e, c + 2, 1); return; }
    ui_cpy(e->msg, "Not an editor command: ");
    k_copy_tail(e->msg, c);
}

static void e_cmdline_key(struct win *w, int code, int ch) {
    struct edit *e;
    int y, x;
    e = E(w);
    if (code == KEY_ESC) { e->mode = M_NORMAL; e->cmdn = 0; return; }
    if (code == KEY_BACK) {
        if (e->cmdn == 0) { e->mode = M_NORMAL; return; }
        --e->cmdn; e->cmd[e->cmdn] = 0; return;
    }
    if (code == KEY_ENTER) {
        e->cmd[e->cmdn] = 0;
        e->mode = M_NORMAL;
        if (e->cmdkind == ':') e_ex(w, e->cmd);
        else if (e->cmdn > 0) {
            ui_cpy(e->search, e->cmd);
            e->sdir = e->cmdkind == '/' ? 1 : 0 - 1;
            y = e->cy; x = e->cx;
            if (e_find(e, e->search, e->sdir, &y, &x)) { e->cy = y; e->cx = x; e->want = x; }
            else e_say(e, "Pattern not found");
        }
        e->cmdn = 0;
        return;
    }
    if (ch >= 32 && ch < 127 && e->cmdn < 150) { e->cmd[e->cmdn++] = ch; e->cmd[e->cmdn] = 0; }
}

// ---- keys --------------------------------------------------------------------------------

// Arrows and the rest, in Insert (and with VIM mode off). 1 if handled.
static int e_nav_insert(struct edit *e, int code, int mods) {
    int ty, tx, lw, incl;
    if (!(code == KEY_LEFT || code == KEY_RIGHT || code == KEY_UP || code == KEY_DOWN || code == KEY_HOME ||
          code == KEY_END || code == KEY_PGUP || code == KEY_PGDN)) return 0;
    if (code == KEY_RIGHT && !(mods & M_CTRL)) { if (e->cx < e->len[e->cy]) ++e->cx; else if (e->cy + 1 < e->nl) { ++e->cy; e->cx = 0; } e->want = e->cx; return 1; }
    if (code == KEY_LEFT && !(mods & M_CTRL)) { if (e->cx > 0) --e->cx; else if (e->cy > 0) { --e->cy; e->cx = e->len[e->cy]; } e->want = e->cx; return 1; }
    if (code == KEY_END && !(mods & M_CTRL)) { e->cx = e->len[e->cy]; e->want = 100000; return 1; }
    if (!e_motion(e, code, 0, mods, 1, &ty, &tx, &lw, &incl)) return 0;
    e->cy = ty; e->cx = tx;
    if (e->cy < 0) e->cy = 0;
    if (e->cy >= e->nl) e->cy = e->nl - 1;
    if (e->cx > e->len[e->cy]) e->cx = e->len[e->cy];
    if (!lw) e->want = e->cx;
    return 1;
}

static void e_insert_key(struct edit *e, int code, int ch, int mods) {
    if (e_nav_insert(e, code, mods)) return;
    if (code == KEY_ESC) {
        if (!e->vim) return;
        e->mode = M_NORMAL;
        if (e->cx > 0) --e->cx;
        e_clamp(e);
        return;
    }
    if (code == KEY_ENTER) { e_newline(e); e->want = e->cx; return; }
    if (code == KEY_BACK) {
        if (e->cx > 0) { e_delrange(e, e->cy, e->cx - 1, e->cy, e->cx); --e->cx; }
        else if (e->cy > 0) { e->cx = e->len[e->cy - 1]; --e->cy; e_delrange(e, e->cy, e->cx, e->cy + 1, 0); }
        e->want = e->cx;
        return;
    }
    if (code == KEY_DEL) {
        if (e->cx < e->len[e->cy]) e_delrange(e, e->cy, e->cx, e->cy, e->cx + 1);
        else if (e->cy + 1 < e->nl) e_delrange(e, e->cy, e->cx, e->cy + 1, 0);
        return;
    }
    if (code == KEY_TAB) { e_instext(e, e->cy, e->cx, "    ", 4); e->cx = e->cx + 4; e->want = e->cx; return; }
    if (mods & M_CTRL) return;
    if (ch >= 32 && ch < 127) { e_inschar(e, ch); e->want = e->cx; }
}

static void e_visual_key(struct win *w, int code, int ch, int mods) {
    struct edit *e;
    int ty, tx, lw, incl, r, n, t;
    e = E(w);
    if (code == KEY_ESC || (ch == 'v' && e->mode == M_VISUAL) || (ch == 'V' && e->mode == M_VLINE)) { e->mode = M_NORMAL; e_clamp(e); return; }
    if (ch == 'v') { e->mode = M_VISUAL; return; }
    if (ch == 'V') { e->mode = M_VLINE; return; }
    if (ch == 'o') { t = e->cy; e->cy = e->vy; e->vy = t; t = e->cx; e->cx = e->vx; e->vx = t; return; }
    if (ch == 'd' || ch == 'x' || ch == 'y' || ch == 'c' || ch == '>' || ch == '<' || ch == 'D' || ch == 'X' || ch == 'Y') {
        r = ch == 'x' ? 'd' : (ch == 'D' || ch == 'X') ? 'd' : ch == 'Y' ? 'y' : ch;
        e_apply(e, r, e->vy, e->vx, e->cy, e->cx, e->mode == M_VLINE || ch == 'D' || ch == 'X' || ch == 'Y' || ch == '>' || ch == '<', 1);
        if (e->mode != M_INSERT) e->mode = M_NORMAL;
        e_clamp(e);
        return;
    }
    if (ch == 'J') { e->cy = e->vy < e->cy ? e->vy : e->cy; e_join(e, (e->vy > e->cy ? e->vy - e->cy : 1)); e->mode = M_NORMAL; return; }
    if (ch >= '1' && ch <= '9') { e->count = e->count * 10 + (ch - '0'); return; }
    n = e->count ? e->count : 1;
    r = e_motion(e, code, ch, mods & M_CTRL, n, &ty, &tx, &lw, &incl);
    e->count = 0;
    if (r == 1) { e->cy = ty; e->cx = tx; e_clamp(e); if (!lw) e->want = e->cx; }
}

// What a Normal-mode command does once its keys are all in.
static void e_normal_key(struct win *w, int code, int ch, int mods) {
    struct edit *e;
    int n, r, ty, tx, lw, incl, y0, x0, y1, x1, op;
    e = E(w);

    // the second key of a two-key command
    if (e->pre) {
        r = e->pre; e->pre = 0;
        n = e->count ? e->count : 1;
        if (r == 'g') {
            if (ch != 'g') { e->count = 0; e->op = 0; return; }
            ty = e->count ? e->count - 1 : 0;
            e->count = 0;
            if (ty >= e->nl) ty = e->nl - 1;
            if (e->op) { op = e->op; e->op = 0; e_apply(e, op, e->cy, 0, ty, 0, 1, 0); e_clamp(e); return; }
            e->cy = ty; e_clamp(e); e->cx = e_firstnb(e, e->cy);
            return;
        }
        if (r == 'r') {
            e->count = 0;
            if (ch < 32 || ch >= 127 || e->len[e->cy] == 0) return;
            e_save_undo(e);
            while (n > 0 && e->cx < e->len[e->cy]) { e->ln[e->cy][e->cx] = ch; ++e->cx; --n; }
            --e->cx;
            e_touched(e, e->cy);
            return;
        }
        if (r == 'i' || r == 'a') {
            op = e->op; e->op = 0; e->count = 0;
            if (!e_textobj(e, r == 'i', ch, &y0, &x0, &y1, &x1)) return;
            e_apply(e, op, y0, x0, y1, x1, 0, 1);
            e_clamp(e);
            return;
        }
        if (r == 'Z') { e->count = 0; if (ch == 'Z') e_ex(w, "x"); else if (ch == 'Q') e_ex(w, "q!"); return; }
        // f t F T
        if (ch < 32 || ch >= 127) { e->count = 0; e->op = 0; return; }
        e->fkind = r; e->fch = ch;
        if (!e_motion_find(e, r, ch, n, &ty, &tx, &incl)) { e->count = 0; e->op = 0; return; }
        lw = 0;
        e->count = 0;
        if (e->op) { e_apply(e, e->op, e->cy, e->cx, ty, tx, 0, incl); e->op = 0; e_clamp(e); return; }
        e->cx = tx; e->want = tx;
        return;
    }

    if ((ch >= '1' && ch <= '9') || (ch == '0' && e->count > 0)) { e->count = e->count * 10 + (ch - '0'); return; }
    n = e->count ? e->count : 1;

    if (e->op) {
        op = e->op;
        // dd cc yy >> <<: lines
        if (ch == op) {
            y1 = e->cy + n - 1;
            if (y1 >= e->nl) y1 = e->nl - 1;
            e->op = 0; e->count = 0;
            e_apply(e, op, e->cy, 0, y1, 0, 1, 0);
            e_clamp(e);
            return;
        }
        if (ch == 'i' || ch == 'a') { e->pre = ch; return; }
        r = e_motion(e, code, ch, mods, n, &ty, &tx, &lw, &incl);
        if (r < 0) return;                      // f/t/g: wait for the next key
        e->op = 0; e->count = 0;
        if (r == 0 || code == KEY_ESC) return;
        if (ty < 0) ty = 0;
        if (ty >= e->nl) ty = e->nl - 1;
        // cw is ce; and dw on a line's last word stops at its end
        if ((ch == 'w' || ch == 'W') && op == 'c') {
            ty = e->cy; tx = e->cx; r = n;
            if (e_class(e_char(e, ty, tx), ch == 'W') != 0) { while (r--) e_word_end(e, &ty, &tx, ch == 'W'); incl = 1; }
        } else if ((ch == 'w' || ch == 'W') && ty > e->cy) { ty = e->cy; tx = e->len[e->cy]; }
        e_apply(e, op, e->cy, e->cx, ty, tx, lw, incl);
        e_clamp(e);
        return;
    }

    r = e_motion(e, code, ch, mods, n, &ty, &tx, &lw, &incl);
    if (r < 0) return;
    if (r > 0) {
        e->count = 0;
        // Shift+arrows select
        if ((mods & M_SHIFT) && (code == KEY_UP || code == KEY_DOWN || code == KEY_LEFT || code == KEY_RIGHT)) {
            e->vy = e->cy; e->vx = e->cx;
            e->mode = (code == KEY_UP || code == KEY_DOWN) ? M_VLINE : M_VISUAL;
        }
        e->cy = ty; e->cx = tx;
        e_clamp(e);
        if (!lw) e->want = e->cx;
        if (ch == 'G' || (mods & M_CTRL && (code == KEY_HOME || code == KEY_END))) e->cx = e_firstnb(e, e->cy);
        return;
    }
    e->count = 0;
    if (code == KEY_ESC) { e->op = 0; return; }
    if (code == KEY_DEL) ch = 'x';
    if (mods & M_CTRL) {
        if (code == 82) e_undo(e, 1);              // Ctrl-R
        return;
    }
    if (ch == 'd' || ch == 'c' || ch == 'y' || ch == '>' || ch == '<') { e->op = ch; e->count = n > 1 ? n : 0; return; }
    if (ch == 'r' || ch == 'Z') { e->pre = ch; e->count = n > 1 ? n : 0; return; }
    if (ch == 'i') { e_save_undo(e); e->mode = M_INSERT; return; }
    if (ch == 'a') { e_save_undo(e); e->mode = M_INSERT; if (e->len[e->cy] > 0) ++e->cx; return; }
    if (ch == 'I') { e_save_undo(e); e->mode = M_INSERT; e->cx = e_firstnb(e, e->cy); return; }
    if (ch == 'A') { e_save_undo(e); e->mode = M_INSERT; e->cx = e->len[e->cy]; return; }
    if (ch == 'o' || ch == 'O') { e_open_line(e, ch == 'O'); return; }
    if (ch == 'x' || ch == 'X') {
        if (e->len[e->cy] == 0) return;
        if (ch == 'X' && e->cx == 0) return;
        if (ch == 'X') { e_apply(e, 'd', e->cy, e->cx - n < 0 ? 0 : e->cx - n, e->cy, e->cx, 0, 0); return; }
        x1 = e->cx + n; if (x1 > e->len[e->cy]) x1 = e->len[e->cy];
        e_apply(e, 'd', e->cy, e->cx, e->cy, x1, 0, 0);
        e_clamp(e);
        return;
    }
    if (ch == 'D' || ch == 'C') { e_apply(e, ch == 'D' ? 'd' : 'c', e->cy, e->cx, e->cy, e->len[e->cy], 0, 0); e_clamp(e); return; }
    if (ch == 's') { x1 = e->cx + n; if (x1 > e->len[e->cy]) x1 = e->len[e->cy]; e_apply(e, 'c', e->cy, e->cx, e->cy, x1, 0, 0); return; }
    if (ch == 'S') { y1 = e->cy + n - 1; if (y1 >= e->nl) y1 = e->nl - 1; e_apply(e, 'c', e->cy, 0, y1, 0, 1, 0); return; }
    if (ch == 'Y') { y1 = e->cy + n - 1; if (y1 >= e->nl) y1 = e->nl - 1; e_yank(e, e->cy, 0, y1, 0, 1); return; }
    if (ch == 'p' || ch == 'P') { while (n--) e_put(e, ch == 'P'); return; }
    if (ch == 'J') { e_join(e, n > 1 ? n - 1 : 1); return; }
    if (ch == '~') {
        if (e->len[e->cy] == 0) return;
        e_save_undo(e);
        while (n-- > 0 && e->cx < e->len[e->cy]) {
            r = e->ln[e->cy][e->cx];
            if (r >= 'a' && r <= 'z') r = r - 32; else if (r >= 'A' && r <= 'Z') r = r + 32;
            e->ln[e->cy][e->cx] = r; ++e->cx;
        }
        e_touched(e, e->cy);
        e_clamp(e);
        return;
    }
    if (ch == 'u') { e_undo(e, 0); e_clamp(e); return; }
    if (ch == 'v' || ch == 'V') { e->vy = e->cy; e->vx = e->cx; e->mode = ch == 'v' ? M_VISUAL : M_VLINE; return; }
    if (ch == ':' || ch == '/' || ch == '?') { e->mode = M_CMD; e->cmdkind = ch; e->cmdn = 0; e->cmd[0] = 0; return; }
    if (ch == '*') {
        // the word under the cursor, searched forward
        if (!e_isword(e_char(e, e->cy, e->cx))) return;
        x0 = e->cx; while (x0 > 0 && e_isword(e->ln[e->cy][x0 - 1])) --x0;
        x1 = e->cx; while (x1 < e->len[e->cy] && e_isword(e->ln[e->cy][x1])) ++x1;
        if (x1 - x0 > 62) x1 = x0 + 62;
        memcpy(e->search, e->ln[e->cy] + x0, x1 - x0);
        e->search[x1 - x0] = 0;
        e->sdir = 1;
        ty = e->cy; tx = e->cx;
        if (e_find(e, e->search, 1, &ty, &tx)) { e->cy = ty; e->cx = tx; e->want = tx; }
        return;
    }
}

// ---- the selection and the clipboard -----------------------------------------------------
//
// A selection is VIM's Visual one, or Traditional's (tsel), from (vy, vx)
// to the cursor. As a range it runs up to, not including, (y1, x1): a
// Visual one takes the character under the cursor too, and a line-wise one
// whole lines with their newlines.

static int e_sel_on(struct edit *e) { return e->vim ? e->mode == M_VISUAL || e->mode == M_VLINE : e->tsel; }

static int e_sel_range(struct edit *e, int *y0, int *x0, int *y1, int *x1) {
    int t;
    if (!e_sel_on(e)) return 0;
    *y0 = e->vy; *x0 = e->vx; *y1 = e->cy; *x1 = e->cx;
    if (*y1 < *y0 || (*y1 == *y0 && *x1 < *x0)) { t = *y0; *y0 = *y1; *y1 = t; t = *x0; *x0 = *x1; *x1 = t; }
    if (*y0 < 0) *y0 = 0;
    if (*y1 >= e->nl) { *y1 = e->nl - 1; *x1 = e->len[*y1]; }
    if (e->vim && e->mode == M_VLINE) { *x0 = 0; *x1 = e->len[*y1] + 1; }
    else if (e->vim) *x1 = *x1 + 1;
    return *y1 > *y0 || *x1 > *x0;
}

// the selection gone: VIM back to Normal, Traditional to none
static void e_sel_end(struct edit *e) {
    e->tsel = 0;
    if (e->vim && (e->mode == M_VISUAL || e->mode == M_VLINE)) { e->mode = M_NORMAL; e_clamp(e); }
}

static void e_copy(struct edit *e) {
    char *t;
    int n, y0, x0, y1, x1;
    if (!e_sel_range(e, &y0, &x0, &y1, &x1)) return;
    t = e_range(e, y0, x0, y1, x1, &n);
    wk_clip_set(t, n);
    free(t);
}

// the selection taken out of the text, the cursor where it began: 1 if there was one
static int e_cut(struct edit *e) {
    int y0, x0, y1, x1;
    if (!e_sel_range(e, &y0, &x0, &y1, &x1)) { e_sel_end(e); return 0; }
    e_delrange(e, y0, x0, y1, x1);
    e->cy = y0; e->cx = x0; e->want = x0;
    e_sel_end(e);
    e_clamp(e);
    return 1;
}

// the clipboard's text at the cursor, in place of the selection (its
// carriage returns left out: a line ends in a newline here)
static void e_paste(struct edit *e) {
    char *c, *t;
    int n, k, m;
    c = wk_clip_get(&n);
    if (n <= 0) return;
    e_save_undo(e);
    e_cut(e);
    t = (char *)ualloc(n + 1);
    m = 0; k = 0;
    while (k < n) { if (c[k] != 13 && c[k]) { t[m] = c[k]; ++m; } ++k; }
    e_instext(e, e->cy, e->cx, t, m);
    free(t);
    e->cy = e_ry; e->cx = e_rx; e->want = e->cx;
    e_clamp(e);
}

static void e_edit(struct win *w, int item) {
    struct edit *e;
    e = E(w);
    if (item == E_FIND) { e_find_open(w); return; }
    if (item == E_FNEXT || item == E_FPREV) { e_findbar(w, item == E_FNEXT ? 1 : 0 - 1, 0); return; }
    if (e->mode == M_CMD) e->mode = e->vim ? M_NORMAL : M_INSERT;
    if (item == E_COPY) e_copy(e);
    else if (item == E_CUT) {
        if (!e_sel_on(e)) return;
        e_save_undo(e);
        e_copy(e);
        e_cut(e);
    }
    else if (item == E_PASTE) e_paste(e);
    else if (item == E_ALL) {
        e->vy = 0; e->vx = 0;
        e->cy = e->nl - 1; e->cx = e->len[e->cy];
        if (e->vim) { e->mode = M_VISUAL; if (e->cx > 0) --e->cx; }
        else e->tsel = e->nl > 1 || e->cx > 0;
    }
    e->tlast = 0;
    e_retitle(w);
}

// ---- Find -----------------------------------------------------------------------------

// The match after the selection's start (DIR 1; from that start itself
// when HERE, as the text to find is typed) or the one before it (-1),
// round past the end or the top, selected -- Traditional's selection, or
// VIM's Visual -- and so scrolled to; or the bar says there is none.
static void e_findbar(struct win *w, int dir, int here) {
    struct edit *e;
    int m, y, x, y0, x0, y1, x1, k, sel;
    e = E(w);
    if (e->xobj) { e_say(e, "A compiled file: its Code tab finds a function by its name, typed"); return; }
    m = ui_len(e->fb.text);
    if (!m) { ui_find_open(&e->fb, 0, 0); return; }        // nothing to look for yet: ask
    e->xtab = 0;                                           // the text in front, not its Code tab
    if (e->mode == M_CMD) e->mode = e->vim ? M_NORMAL : M_INSERT;
    sel = e_sel_range(e, &y0, &x0, &y1, &x1);
    if (sel) { y = y0; x = x0; } else { y = e->cy; x = e->cx; }
    if (dir > 0) { if (sel && !here) ++x; }
    else --x;
    e->fb.note[0] = 0; e->fb.bad = 0;
    k = 0;
    while (k <= e->nl + 1) {
        if (dir > 0) {
            while (x + m <= e->len[y]) { if (ui_find_at(&e->fb, e->ln[y] + x, e->len[y] - x)) break; ++x; }
            if (x + m <= e->len[y]) break;
            ++y; x = 0;
            if (y >= e->nl) { y = 0; ui_find_say(&e->fb, "Wrapped to the top", 0); }
        } else {
            if (x > e->len[y] - m) x = e->len[y] - m;
            while (x >= 0) { if (ui_find_at(&e->fb, e->ln[y] + x, e->len[y] - x)) break; --x; }
            if (x >= 0) break;
            --y;
            if (y < 0) { y = e->nl - 1; ui_find_say(&e->fb, "Wrapped to the bottom", 0); }
            x = e->len[y];
        }
        ++k;
    }
    if (k > e->nl + 1) { ui_find_say(&e->fb, "Not found", 1); return; }
    e->vy = y; e->vx = x; e->cy = y; e->tlast = 0;
    if (e->vim) { e->mode = M_VISUAL; e->cx = x + m - 1; }
    else { e->cx = x + m; e->tsel = 1; }
    e->want = e->cx;
}

// what the find bar asked for
static void e_find_act(struct win *w, int a) {
    if (a == UF_NEXT) e_findbar(w, 1, 0);
    else if (a == UF_PREV) e_findbar(w, 0 - 1, 0);
    else if (a == UF_TYPED) e_findbar(w, 1, 1);
}

// Find: the bar, with the selection to look for if it is on one line
static void e_find_open(struct win *w) {
    struct edit *e;
    char *t;
    int n, y0, x0, y1, x1;
    e = E(w);
    if (e->xobj) { e_say(e, "A compiled file: its Code tab finds a function by its name, typed"); return; }
    e->xtab = 0;
    if (e->mode == M_CMD) e->mode = e->vim ? M_NORMAL : M_INSERT;
    if (e_sel_range(e, &y0, &x0, &y1, &x1) && y0 == y1 && x1 - x0 < UI_FIND_MAX) {
        t = e_range(e, y0, x0, y1, x1, &n);
        ui_find_open(&e->fb, t, n);
        free(t);
    } else ui_find_open(&e->fb, 0, 0);
}

static int e_ctrl(int code, int ch, int mods, int c) { return (mods & M_CTRL) && (code == c || ch == c || ch == c + 32); }

// Traditional: Text Editor's keys. The moving keys with Shift select; the
// typing keys replace a selection; a run of characters typed is undone
// as one.
static void e_trad_key(struct win *w, int code, int ch, int mods) {
    struct edit *e;
    int typing, y0, x0, y1, x1;
    e = E(w);
    if (code == 16 || code == 17 || code == 18) return;       // Shift, Ctrl or Alt alone
    if (ui_key_copy(code, ch, mods)) { e_edit(w, E_COPY); return; }
    if (ui_key_cut(code, ch, mods)) { e_edit(w, E_CUT); return; }
    if (ui_key_paste(code, ch, mods)) { e_edit(w, E_PASTE); return; }
    if (e_ctrl(code, ch, mods, 'A')) { e_edit(w, E_ALL); return; }
    if (e_ctrl(code, ch, mods, 'Z')) { e_undo(e, 0); e->tsel = 0; e->tlast = 0; e_clamp(e); return; }
    if (e_ctrl(code, ch, mods, 'Y')) { e_undo(e, 1); e->tsel = 0; e->tlast = 0; e_clamp(e); return; }
    if (e_ctrl(code, ch, mods, 'O')) { edit_command(w, 0, 1); return; }
    if (e_ctrl(code, ch, mods, 'N')) { edit_command(w, 0, 0); return; }
    if (code == KEY_ESC) {
        if (e->tsel) { e->tsel = 0; return; }
        e->mode = M_CMD; e->cmdkind = ':'; e->cmdn = 0; e->cmd[0] = 0;
        return;
    }
    if (code == KEY_LEFT || code == KEY_RIGHT || code == KEY_UP || code == KEY_DOWN || code == KEY_HOME ||
        code == KEY_END || code == KEY_PGUP || code == KEY_PGDN) {
        e->tlast = 0;
        if (mods & M_SHIFT) {
            if (!e->tsel) { e->vy = e->cy; e->vx = e->cx; }
            e_nav_insert(e, code, mods);
            e->tsel = e->vy != e->cy || e->vx != e->cx;
            return;
        }
        // Left and Right with a selection go to its ends
        if (e->tsel && !(mods & M_CTRL) && (code == KEY_LEFT || code == KEY_RIGHT) && e_sel_range(e, &y0, &x0, &y1, &x1)) {
            if (code == KEY_LEFT) { e->cy = y0; e->cx = x0; } else { e->cy = y1; e->cx = x1; }
            e->want = e->cx; e->tsel = 0;
            return;
        }
        e->tsel = 0;
        e_nav_insert(e, code, mods);
        return;
    }
    typing = ch >= 32 && ch < 127 && !(mods & M_CTRL);
    if (!typing && code != KEY_ENTER && code != KEY_BACK && code != KEY_DEL && code != KEY_TAB) return;
    if (!typing || !e->tlast || e->tsel) e_save_undo(e);
    e->tlast = typing;
    if (e->tsel) {
        e_cut(e);
        if (code == KEY_BACK || code == KEY_DEL) return;
    }
    e_insert_key(e, code, ch, mods);
}

// Run (F6): what was built; a compiled file shown, if it is a program
static void e_run(struct win *w) {
    struct edit *e;
    e = E(w);
    if (!e->xobj) { e_ex(w, "run"); return; }
    if (ui_ends(e->path, ".c4r")) run_command(e->path);
}

// The way in for every key. It records the keys of a change as it is
// made, so '.' can type them again.
static void e_key(struct win *w, int code, int ch, int mods) {
    struct edit *e;
    int was_normal, k;
    e = E(w);
    e->msg[0] = 0;
    // Ctrl+S saves, whatever the mode
    if ((mods & M_CTRL) && (code == 83 || ch == 's' || ch == 'S')) { e_save(e, e->path); e_retitle(w); return; }
    // Ctrl+B: the file pane, as IDEs have it (VIM's page back is not here)
    if ((mods & M_CTRL) && (code == 66 || ch == 'b' || ch == 'B')) { e->fshown = !e->fshown; return; }
    // Ctrl+F: Find, in either way of typing (VIM's page forward is not here
    // either); F3 and Shift+F3 the next and the one before
    if ((mods & M_CTRL) && (code == 70 || ch == 'f' || ch == 'F')) { e_find_open(w); return; }
    if (code == KEY_F3) { if (!e->fb.text[0]) e_find_open(w); else e_findbar(w, (mods & M_SHIFT) ? 0 - 1 : 1, 0); return; }
    if (code == KEY_F5) { e_make(w); return; }
    if (code == KEY_F6) { e_run(w); return; }
    if (code == KEY_F8) { e_goto_error(w, (mods & M_SHIFT) ? e->ecur - 1 : e->ecur + 1); return; }
    if (code == KEY_F4) { e->bshown = !e->bshown; return; }
    if (code == KEY_F7) { e_code(w); return; }
    // the find bar's keys while it has them (the text's Code tab not in front)
    if (e->fb.on && e->fb.keys && !(e->xshown && e->xtab && e->xp)) { e_find_act(w, ui_find_key(&e->fb, code, ch, mods)); return; }
    // the Code tab in front: its keys, and Esc back to the text
    if (e->xshown && e->xtab && e->xp) {
        k = xp_key(e->xp, code, ch, mods);
        if (k == 2) x_goto(w);
        else if (k == 0 && code == KEY_ESC && !e->xobj) e->xtab = 0;
        return;
    }
    if (e->mode == M_CMD) {
        e_cmdline_key(w, code, ch);
        // without VIM mode there is no Normal to come back to
        if (!e->vim && e->mode == M_NORMAL) e->mode = M_INSERT;
        return;
    }
    if (!e->vim) {
        // Traditional: always typing; Esc is the way to a command
        e_trad_key(w, code, ch, mods);
        e_retitle(w);
        return;
    }

    // '.': the last change, again
    if (e->mode == M_NORMAL && !e->op && !e->pre && ch == '.' && !(mods & M_CTRL)) {
        if (!e->dotn) return;
        e->replaying = 1;
        k = 0;
        while (k < e->dotn) { e_key(w, e->dot[k * 3], e->dot[k * 3 + 1], e->dot[k * 3 + 2]); k = k + 1; }
        e->replaying = 0;
        return;
    }
    was_normal = e->mode == M_NORMAL && !e->op && !e->pre && !e->count;
    if (was_normal && !e->replaying) { e->recn = 0; e->recording = 1; e->changed = 0; }
    if (e->recording && !e->replaying && e->recn < REC_MAX) {
        e->rec[e->recn * 3] = code; e->rec[e->recn * 3 + 1] = ch; e->rec[e->recn * 3 + 2] = mods;
        ++e->recn;
    }

    if (e->mode == M_INSERT) e_insert_key(e, code, ch, mods);
    else if (e->mode == M_VISUAL || e->mode == M_VLINE) e_visual_key(w, code, ch, mods);
    else e_normal_key(w, code, ch, mods);

    // a change is done when Normal mode has nothing half typed
    if (e->recording && e->mode == M_NORMAL && !e->op && !e->pre && !e->count) {
        if (e->changed && !e->replaying && e->recn) {
            memcpy(e->dot, e->rec, e->recn * 3 * sizeof(int));
            e->dotn = e->recn;
        }
        e->recording = 0;
    }
    e_retitle(w);
}

void edit_key(struct win *w, int code, int ch, int mods) { e_key(w, code, ch, mods); }

// ---- syntax colours ---------------------------------------------------------------------
//
// hl.c colours a line; what is kept here is the state the colouring is in
// at the start of each line, as far down as it has been worked out (a
// change cuts it back to the line changed: e_touched), so neither
// scrolling down nor up reads the file from its start again.

static int e_hcol(int i) { return ec[hl_at(i)]; }

// Colour line Y (hl.c); ST is the state at its start, and the state at
// its end comes back
static int e_hl(struct edit *e, int y, int st, int lang) { return hl_line(e->ln[y], e->len[y], st, lang); }

// the state at the start of line LINE
static int e_hlstate(struct edit *e, int line, int lang) {
    int y, st, m, *n;
    if (lang != L_C && lang != L_JS) return 0;
    if (line >= e->nl) line = e->nl - 1;
    if (line < 0) line = 0;
    if (e->hl_lang != lang) { e->hlsn = 0; e->hl_lang = lang; }
    if (line + 1 > e->hlscap) {
        m = e->hlscap ? e->hlscap : 256;
        while (m < line + 1) m = m * 2;
        n = (int *)ualloc(m * sizeof(int));
        if (e->hlsn > 0) memcpy(n, e->hls, e->hlsn * sizeof(int));
        if (e->hls) free((char *)e->hls);
        e->hls = n; e->hlscap = m;
    }
    if (e->hlsn == 0) { e->hls[0] = 0; e->hlsn = 1; }
    if (line < e->hlsn) return e->hls[line];
    y = e->hlsn - 1; st = e->hls[y];
    while (y < line) { st = e_hl(e, y, st, lang); ++y; e->hls[y] = st; }
    e->hlsn = line + 1;
    return st;
}

// ---- the file pane ---------------------------------------------------------------------

static void f_reserve(struct edit *e, int need) {
    char **np;
    int *nd, *nf, m, i;
    if (need <= e->fcap) return;
    m = e->fcap ? e->fcap * 2 : 128;
    while (m < need) m = m * 2;
    np = (char **)ualloc(m * sizeof(int));
    nd = (int *)ualloc(m * sizeof(int));
    nf = (int *)ualloc(m * sizeof(int));
    i = 0;
    while (i < e->fn) { np[i] = e->fpath[i]; nd[i] = e->fdepth[i]; nf[i] = e->fflag[i]; ++i; }
    if (e->fpath) { free((char *)e->fpath); free((char *)e->fdepth); free((char *)e->fflag); }
    e->fpath = np; e->fdepth = nd; e->fflag = nf; e->fcap = m;
}

static void f_ins(struct edit *e, int at, char *path, int depth, int flag) {
    int i;
    f_reserve(e, e->fn + 1);
    i = e->fn;
    while (i > at) { e->fpath[i] = e->fpath[i - 1]; e->fdepth[i] = e->fdepth[i - 1]; e->fflag[i] = e->fflag[i - 1]; --i; }
    e->fpath[at] = (char *)ualloc(ui_len(path) + 1);
    ui_cpy(e->fpath[at], path);
    e->fdepth[at] = depth;
    e->fflag[at] = flag;
    ++e->fn;
}

static void f_del(struct edit *e, int at) {
    int i;
    free(e->fpath[at]);
    i = at;
    while (i < e->fn - 1) { e->fpath[i] = e->fpath[i + 1]; e->fdepth[i] = e->fdepth[i + 1]; e->fflag[i] = e->fflag[i + 1]; ++i; }
    --e->fn;
}

static void f_join(char *out, char *dir, char *nm) {
    ui_cpy(out, dir);
    if (!(dir[0] == '/' && dir[1] == 0)) ui_cat(out, "/");
    ui_cat(out, nm);
}
static int f_before(char *a, char *b) {
    while (*a && *a == *b) { ++a; ++b; }
    return (*a & 255) < (*b & 255);
}

// Folder I's contents below it -- I -1 is the root, whose contents are
// the top of the tree -- folders first, each lot by name.
static void f_open_dir(struct edit *e, int i) {
    char *dir, *names, nm[FNAME];
    int *dirs, depth, n, k, j, r;
    dir = i < 0 ? "/" : e->fpath[i];
    depth = i < 0 ? 0 : e->fdepth[i] + 1;
    names = (char *)ualloc(F_KIDS * FNAME);
    dirs = (int *)ualloc(F_KIDS * sizeof(int));
    n = 0; k = 0;
    while (n < F_KIDS) {
        r = ureaddir(dir, k, nm);
        if (r < 0) break;
        ui_cpy(names + n * FNAME, nm);
        dirs[n] = r == 1;
        ++n; ++k;
    }
    k = 1;
    while (k < n) {
        j = k;
        while (j > 0 && (dirs[j] > dirs[j - 1] || (dirs[j] == dirs[j - 1] && f_before(names + j * FNAME, names + (j - 1) * FNAME)))) {
            ui_cpy(nm, names + j * FNAME); ui_cpy(names + j * FNAME, names + (j - 1) * FNAME); ui_cpy(names + (j - 1) * FNAME, nm);
            r = dirs[j]; dirs[j] = dirs[j - 1]; dirs[j - 1] = r;
            --j;
        }
        ++k;
    }
    j = 0;
    while (j < n) {
        f_join(sb, dir, names + j * FNAME);
        f_ins(e, i + 1 + j, sb, depth, dirs[j] ? F_DIR : 0);
        ++j;
    }
    if (i >= 0) e->fflag[i] = e->fflag[i] | F_OPEN;
    free(names); free((char *)dirs);
}

static void f_close_dir(struct edit *e, int i) {
    while (i + 1 < e->fn && e->fdepth[i + 1] > e->fdepth[i]) f_del(e, i + 1);
    e->fflag[i] = e->fflag[i] & F_DIR;
}

static int f_find(struct edit *e, char *p) {
    int i;
    i = 0;
    while (i < e->fn) { if (ui_eq(e->fpath[i], p)) return i; ++i; }
    return 0 - 1;
}

// open every folder above PATH, so that it is in the tree to be seen
static void f_reveal(struct edit *e, char *path) {
    char part[128];
    int k, i;
    if (!e->fpath || path[0] != '/') return;
    k = 1;
    while (path[k] && k < 127) {
        if (path[k] == '/') {
            memcpy(part, path, k); part[k] = 0;
            i = f_find(e, part);
            if (i >= 0 && (e->fflag[i] & F_DIR) && !(e->fflag[i] & F_OPEN)) f_open_dir(e, i);
        }
        ++k;
    }
    e->ffollow = 1;
}

// A file just written: into the tree, in its place among its folder's
// files, if that folder is open and it is not there yet.
static void f_add(struct edit *e, char *path) {
    char dir[128];
    int p, d, i, k;
    if (!e->fpath || path[0] != '/' || f_find(e, path) >= 0) return;
    k = ui_len(path);
    while (k > 0 && path[k - 1] != '/') --k;
    if (k <= 1) { p = 0 - 1; d = 0; }
    else {
        if (k > 127) return;
        memcpy(dir, path, k - 1); dir[k - 1] = 0;
        p = f_find(e, dir);
        if (p < 0 || !(e->fflag[p] & F_OPEN)) return;
        d = e->fdepth[p] + 1;
    }
    i = p + 1;
    while (i < e->fn && e->fdepth[i] >= d) {
        if (e->fdepth[i] == d && !(e->fflag[i] & F_DIR) && f_before(path + k, e->fpath[i] + k)) break;
        ++i;
    }
    f_ins(e, i, path, d, 0);
}

// The pane's widest row, in 6-pixel steps; wider than the pane, it gets a
// bar across, which takes a row.
static int f_maxw(struct edit *e) {
    int i, k, w, mx;
    char *p;
    mx = 0; i = 0;
    while (i < e->fn) {
        p = e->fpath[i];
        k = ui_len(p);
        w = k;
        while (w > 0 && p[w - 1] != '/') --w;
        w = (4 + e->fdepth[i] * 12 + 28) / 6 + (k - w) + 1;
        if (w > mx) mx = w;
        ++i;
    }
    return mx;
}
static int f_hvis(struct edit *e) { return (e->fwx - 17) / 6; }
static int f_hbar(struct edit *e) { return f_maxw(e) > f_hvis(e); }
static int f_rows(struct edit *e, int ch) { return (ch - FHDR - 2 - (f_hbar(e) ? 16 : 0)) / FROW; }
static void f_clamp(struct edit *e, int rows) {
    int max;
    if (e->ftop > e->fn - rows) e->ftop = e->fn - rows;
    if (e->ftop < 0) e->ftop = 0;
    max = f_maxw(e) - f_hvis(e);
    if (max < 0) max = 0;
    if (e->fleft > max) e->fleft = max;
    if (e->fleft < 0) e->fleft = 0;
}
// the pane is drawn only where the text keeps some room
static int f_on(struct edit *e, int cw) { return e->fshown && e->fpath && cw >= FMIN + SPW + 200; }
// the pane's width in a window CW wide: the one chosen, as far as the text keeps 220 pixels
static int f_width(struct edit *e, int cw) {
    int w;
    w = e->fw;
    if (w > cw - SPW - 220) w = cw - SPW - 220;
    if (w < FMIN) w = FMIN;
    return w;
}

static void f_draw(struct edit *e, int ox, int oy, int ch) {
    int rows, i, y, x, cur, k, hb, vb, dx;
    char *p;
    rows = f_rows(e, ch);
    hb = f_hbar(e);
    vb = e->fn > rows;
    cur = f_find(e, e->path);
    if (e->ffollow && cur >= 0) {
        if (cur < e->ftop) e->ftop = cur;
        if (cur >= e->ftop + rows) e->ftop = cur - rows / 2;
    }
    e->ffollow = 0;
    f_clamp(e, rows);
    dx = e->fleft * 6;
    d_rect(ox, oy, e->fwx, ch, 0xf4f4f4);
    d_rect(ox, oy, e->fwx, FHDR, C_FACE);
    d_bevel(ox, oy, e->fwx, FHDR, B_RAISED);
    d_text(ox + 6, oy + 4, C_DARK, F_BOLD, "Files");
    d_clip(ox, oy + FHDR, e->fwx - (vb ? 17 : 0), ch - FHDR - (hb ? 16 : 0));
    i = e->ftop;
    y = oy + FHDR + 2;
    while (i < e->fn && i < e->ftop + rows) {
        x = ox + 4 + e->fdepth[i] * 12 - dx;
        if (i == cur) d_rect(ox, y, e->fwx, FROW, 0xc8dcff);
        if (e->fflag[i] & F_DIR) {
            if (e->fflag[i] & F_OPEN) { d_line(x, y + 6, x + 4, y + 10, C_DARK); d_line(x + 4, y + 10, x + 8, y + 6, C_DARK); }
            else { d_line(x + 2, y + 4, x + 6, y + 8, C_DARK); d_line(x + 6, y + 8, x + 2, y + 12, C_DARK); }
            d_rect(x + 11, y + 3, 5, 2, 0xc8a000);
            d_rect(x + 11, y + 5, 13, 8, 0xffd84a);
        } else {
            d_rect(x + 13, y + 2, 9, 12, C_WHITE);
            d_recto(x + 13, y + 2, 9, 12, C_SHADOW);
        }
        p = e->fpath[i];
        k = ui_len(p);
        while (k > 0 && p[k - 1] != '/') --k;
        d_text(x + 28, y + 2, C_DARK, F_SANS, p + k);
        y = y + FROW;
        ++i;
    }
    d_clip_end();
    if (vb) ui_scrollbar(ox + e->fwx - 17, oy + FHDR, ch - FHDR - (hb ? 16 : 0), e->fn, rows, e->ftop);
    if (hb) ui_hscrollbar(ox, oy + ch - 16, e->fwx - 17, f_maxw(e), f_hvis(e), e->fleft);
}

// a file picked in the pane: into the editor, unless that loses changes
static void f_pick(struct win *w, int i) {
    struct edit *e;
    char p[128];
    e = E(w);
    if (ui_eq(e->fpath[i], e->path)) return;
    if (e->modified) { e_say(e, "No write since last change: :w first, or :e! FILE"); return; }
    ui_cpy(p, e->fpath[i]);
    if (!e_open(w, p, 0)) e_say(e, "Cannot open that file");
    e_retitle(w);
}

static void f_mouse(struct win *w, int ev, int x, int y, int ch) {
    struct edit *e;
    int rows, t, i, hb;
    e = E(w);
    rows = f_rows(e, ch);
    hb = f_hbar(e);
    if (ev == E_WHEEL) { e->ftop = e->ftop + y * 3; f_clamp(e, rows); return; }
    if (ev != E_DOWN) return;
    if (e->fn > rows && x >= e->fwx - 17) {
        t = ui_scroll_click(x, y, e->fwx - 17, FHDR, ch - FHDR - (hb ? 16 : 0), e->fn, rows, e->ftop);
        if (t >= 0) { e->ftop = t; return; }
    }
    if (hb && y >= ch - 16) {
        t = ui_hscroll_click(x, y, 0, ch - 16, e->fwx - 17, f_maxw(e), f_hvis(e), e->fleft);
        if (t >= 0) e->fleft = t;
        return;
    }
    if (y < FHDR + 2 || x >= e->fwx) return;
    i = e->ftop + (y - FHDR - 2) / FROW;
    if (i < 0 || i >= e->fn || i >= e->ftop + rows) return;
    if (e->fflag[i] & F_DIR) { if (e->fflag[i] & F_OPEN) f_close_dir(e, i); else f_open_dir(e, i); }
    else f_pick(w, i);
}

// ---- drawing ------------------------------------------------------------------------------

static int e_selected(struct edit *e, int y, int x) {
    int y0, x0, y1, x1;
    if (!e_sel_range(e, &y0, &x0, &y1, &x1)) return 0;
    if (y < y0 || y > y1) return 0;
    if (y == y0 && x < x0) return 0;
    if (y == y1 && x >= x1) return 0;
    return 1;
}

// Rows line Y takes when wrapped at COLS: one at least
static int e_wh(struct edit *e, int y, int cols) {
    int h;
    h = (e->len[y] + cols - 1) / cols;
    return h < 1 ? 1 : h;
}
// the wrapped row of line Y the cursor's column falls in
static int e_wseg(struct edit *e, int y, int x, int cols) {
    int s, h;
    s = x / cols;
    h = e_wh(e, y, cols);
    return s < h ? s : h - 1;
}

// The top line that brings the last line to the bottom: wrapped, the
// rows of the lines from it to the end fill the view (as last drawn)
static int e_maxtop(struct edit *e) {
    int t, used, h;
    if (!e->wrap) return e->nl > e->rows ? e->nl - e->rows : 0;
    t = e->nl; used = 0;
    while (t > 0) {
        h = e_wh(e, t - 1, e->cols);
        if (used + h > e->rows) break;
        used = used + h; --t;
    }
    return t < e->nl ? t : e->nl - 1;           // (the last line alone taller than the view)
}
// the last line every row of which shows with line T at the top (T, if it
// alone is taller than the view)
static int e_lastfull(struct edit *e, int t) {
    int l, used, h;
    if (!e->wrap) return t + e->rows - 1 < e->nl ? t + e->rows - 1 : e->nl - 1;
    l = t; used = 0;
    while (l < e->nl) {
        h = e_wh(e, l, e->cols);
        if (used + h > e->rows) break;
        used = used + h; ++l;
    }
    return l > t ? l - 1 : t;
}

// the build pane: its header (a line of the interface's text), its log (BROWS of the grid's)
enum { BHDR = 17 };
#define BLOG_H (BROWS * ECH + 2)
#define BPANE (BHDR + BLOG_H + 16)

static void e_draw_text(struct win *w, int ox, int oy, int cw, int ch, int focused) {
    struct edit *e;
    int rows, cols, gw, y, line, x, n, sx, ph, sy, k, i, c, endsel, lang, st, tah, hb, h, seg, a, cseg, r, used, l, by, fh;
    char num[16];
    e = E(w);
    ec = scheme_cols + ide_scheme * SC_N;
    ph = e->bshown ? BPANE : 0;
    fh = e->fb.on ? UI_FIND_H : 0;                // the find bar, under the text
    sy = oy + ch - ECH - 4;                       // the status line
    tah = ch - ECH - 4 - ph - fh;                 // the text's area, its bars included
    hb = !e->wrap;
    rows = (tah - 6 - (hb ? 16 : 0)) / ECH;
    if (rows < 1) rows = 1;
    gw = e->nu ? 5 * ECW : 0;
    cols = (cw - 8 - gw - 17) / ECW;
    if (cols < 1) cols = 1;
    e->rows = rows; e->cols = cols; e->gw = gw; e->tah = tah; e->ph = ph; e->hb = hb; e->fh = fh;
    // the scroll bar's lines at once: what makes its end the last top line
    e->vis = e->nl - e_maxtop(e);
    if (e->vis < 1) e->vis = 1;
    e->maxw = 0;
    i = 0;
    while (i < e->nl) { if (e->len[i] > e->maxw) e->maxw = e->len[i]; ++i; }
    if (e->cy < e->top) e->top = e->cy;
    if (!e->wrap) {
        if (e->cy >= e->top + rows) e->top = e->cy - rows + 1;
        // across, the view follows the cursor only when it has moved, so the
        // bar can be scrolled away from it
        if (e->cx != e->lcx || e->cy != e->lcy) {
            if (e->cx < e->left) e->left = e->cx;
            if (e->cx >= e->left + cols) e->left = e->cx - cols + 1;
        }
        if (e->left > e->maxw + 1 - cols) e->left = e->maxw + 1 - cols;
        if (e->left < 0) e->left = 0;
    } else {
        e->left = 0;
        // down: the rows from the top line to the cursor's must fit
        while (e->top < e->cy) {
            used = 0; l = e->top;
            while (l < e->cy && used <= rows) { used = used + e_wh(e, l, cols); ++l; }
            used = used + e_wseg(e, e->cy, e->cx, cols) + 1;
            if (used <= rows) break;
            ++e->top;
        }
    }
    e->lcx = e->cx; e->lcy = e->cy;

    d_rect(ox, oy, cw, tah, ec[SC_BG]);
    if (gw) d_rect(ox, oy, gw + 2, tah, ec[SC_GUT]);
    line = e->top;
    r = 0;
    y = oy + 3;
    lang = e->nosyn ? L_TEXT : hl_lang(e->path);
    st = e_hlstate(e, e->top, lang);
    sx = ox + 4 + gw;
    while (line < e->nl && r < rows) {
        // the colours for the whole line, which also say what the next starts in
        st = e_hl(e, line, st, lang);
        h = e->wrap ? e_wh(e, line, cols) : 1;
        cseg = e->wrap ? e_wseg(e, line, e->cx, cols) : 0;
        seg = 0;
        while (seg < h && r < rows) {
            a = e->wrap ? seg * cols : e->left;   // the first column this row shows
            // a band where the Code pane's function has code from this line
            if (seg == 0 && e->xshown && e->xp && (c = xp_band(e->xp, line + 1)) >= 0) d_rect(ox, y, 3, ECH, c);
            if (gw && seg == 0) {
                ui_num(num, line + 1);
                k = ui_len(num);
                d_textn(ox + 2 + (4 - k) * ECW, y, ec[SC_GUTFG] == SHADOW ? C_SHADOW : ec[SC_GUTFG], EFONT, EFACE, ECW, num, k);
            }
            // the selection behind the text
            if (e_sel_on(e)) {
                x = a;
                endsel = e->len[line] > a + cols ? a + cols : e->len[line];
                while (x <= endsel && x < a + cols) {
                    if (e_selected(e, line, x)) d_rect(sx + (x - a) * ECW, y, ECW, ECH, ec[SC_SEL]);
                    ++x;
                }
            }
            n = e->len[line] - a;
            if (n > cols) n = cols;
            x = 0;
            while (x < n) {
                c = e_hcol(a + x);
                k = x + 1;
                while (k < n && e_hcol(a + k) == c) ++k;
                d_textn(sx + x * ECW, y, c, EFONT, EFACE, ECW, e->ln[line] + a + x, k - x);
                x = k;
            }
            // the cursor: a block in Normal, a bar in Insert
            if (focused && !e->fb.keys && line == e->cy && seg == cseg && e->mode != M_CMD) {
                x = sx + (e->cx - a) * ECW;
                if (e->vim && e->mode != M_INSERT) {
                    d_rect(x, y, ECW, ECH, ec[SC_CUR]);
                    c = e_char(e, line, e->cx);
                    if (c != 10) { num[0] = c; d_textn(x, y, ec[SC_CURFG], EFONT, EFACE, ECW, num, 1); }
                } else d_rect(x, y, 2, ECH - 1, ec[SC_CUR]);
            }
            y = y + ECH;
            ++r; ++seg;
        }
        ++line;
    }
    while (r < rows) { d_textn(sx, y, ec[SC_TILDE], EFONT, EFACE, ECW, "~", 1); y = y + ECH; ++r; }
    ui_scrollbar(ox + cw - 17, oy, tah - (hb ? 16 : 0), e->nl, e->vis, e->top);
    if (hb) {
        ui_hscrollbar(ox, oy + tah - 16, cw - 17, e->maxw + 1, cols, e->left);
        d_rect(ox + cw - 17, oy + tah - 16, 17, 16, C_FACE);
    }

    if (fh) ui_find_draw(&e->fb, ox, oy + tah, cw, focused);

    // the build pane: a header with Cancel while it runs, the log, its bars
    if (e->bshown) {
        y = oy + tah + fh;
        d_rect(ox, y, cw, BHDR, C_FACE);
        d_bevel(ox, y, cw, BHDR, B_RAISED);
        ui_cpy(sb, e->building ? "Build: running" : (e->blogn == 0 ? "Build" : (e->bcancel ? "Build: cancelled" : (e->bstatus == 0 ? "Build: finished" : "Build: failed"))));
        if (e->en) { ui_cat(sb, " - "); ui_num(sb + ui_len(sb), e->en); ui_cat(sb, e->en == 1 ? " error (F8)" : " errors (F8)"); }
        d_text(ox + 6, y + 2, C_DARK, F_SANS, sb);
        if (e->building) ui_button(ox + cw - 72, y + 1, 66, BHDR - 2, "Cancel", 0, 0);
        by = y + BHDR;
        e->bcols = (cw - 8 - 17) / ECW;
        if (e->bcols < 1) e->bcols = 1;
        e->bmaxw = 0;
        i = 0;
        while (i < e->blogn) { k = ui_len(e->blog[i]); if (k > e->bmaxw) e->bmaxw = k; ++i; }
        if (e->bleft > e->bmaxw - e->bcols) e->bleft = e->bmaxw - e->bcols;
        if (e->bleft < 0) e->bleft = 0;
        if (e->btop > e->blogn - BROWS) e->btop = e->blogn - BROWS;
        if (e->btop < 0) e->btop = 0;
        d_rect(ox, by, cw - 17, BLOG_H, 0x101010);
        i = e->btop;
        k = 0;
        while (k < BROWS && i < e->blogn) {
            c = 0xc0c0c0;
            n = 0;
            while (n < e->en) { if (e->elog[n] == i) { c = 0xff8080; n = e->en; } ++n; }
            if (i == e->bsel) { d_rect(ox, by + 1 + k * ECH, cw - 17, ECH, 0x304070); c = C_WHITE; }
            n = ui_len(e->blog[i]) - e->bleft;
            if (n > e->bcols) n = e->bcols;
            if (n > 0) d_textn(ox + 4, by + 1 + k * ECH, c, EFONT, EFACE, ECW, e->blog[i] + e->bleft, n);
            ++k; ++i;
        }
        ui_scrollbar(ox + cw - 17, by, BLOG_H, e->blogn, BROWS, e->btop);
        ui_hscrollbar(ox, by + BLOG_H, cw - 17, e->bmaxw, e->bcols, e->bleft);
        d_rect(ox + cw - 17, by + BLOG_H, 17, 16, C_FACE);
    }

    // the status line: the mode or the command being typed, then where we are
    d_rect(ox, sy, cw, ECH + 4, C_FACE);
    d_bevel(ox, sy, cw, ECH + 4, B_SUNKEN);
    if (e->mode == M_CMD) {
        sb[0] = e->cmdkind; sb[1] = 0;
        ui_cat(sb, e->cmd);
        d_textn(ox + 4, sy + 2, C_DARK, EFONT, EFACE, ECW, sb, ui_len(sb));
        if (focused) d_rect(ox + 4 + ui_len(sb) * ECW, sy + 2, 2, ECH - 1, C_DARK);
    } else {
        if (e->msg[0]) ui_cpy(sb, e->msg);
        else if (!e->vim) ui_cpy(sb, "-- EDIT --  (Esc for a command: w, make, e FILE; Ctrl+S saves)");
        else if (e->mode == M_INSERT) ui_cpy(sb, "-- INSERT --");
        else if (e->mode == M_VISUAL) ui_cpy(sb, "-- VISUAL --");
        else if (e->mode == M_VLINE) ui_cpy(sb, "-- VISUAL LINE --");
        else sb[0] = 0;
        d_clip(ox, sy, cw - 20 - 9 * ECW, ECH + 4);
        d_text(ox + 4, sy + 3, C_DARK, F_SANS, sb);
        d_clip_end();
    }
    ui_num(sb, e->cy + 1);
    ui_cat(sb, ",");
    ui_num(sb + ui_len(sb), e->cx + 1);
    k = ui_len(sb);
    d_textn(ox + cw - 12 - k * ECW, sy + 2, C_DARK, EFONT, EFACE, ECW, sb, k);
}

// The view moved to T, no further than brings the last line to the
// bottom: the cursor comes along onto a line wholly in view, as the
// redraw keeps it in view (it would move the view back for a cursor on a
// line whose rows run off the bottom).
static void e_scrolled(struct edit *e, int t) {
    int last;
    last = e_maxtop(e);
    if (t > last) t = last;
    if (t < 0) t = 0;
    e->top = t;
    last = e_lastfull(e, t);
    if (e->cy < t) e->cy = t;
    if (e->cy > last) e->cy = last;
    e_clamp(e);
}

// The line and column at (x, y) in the text (as the last draw laid it
// out), clamped to the text
static void e_pos_at(struct edit *e, int x, int y, int *py, int *px) {
    int r, l, h;
    r = (y - 3) / ECH;
    if (y < 3 || r < 0) r = 0;
    if (!e->wrap) {
        l = e->top + r;
        if (l >= e->nl) l = e->nl - 1;
        if (l < 0) l = 0;
        *py = l;
        *px = e->left + (x - 4 - e->gw + ECW / 2) / ECW;
    } else {
        // the row's line, and which of its wrapped rows
        l = e->top;
        while (l < e->nl - 1) { h = e_wh(e, l, e->cols); if (r < h) break; r = r - h; ++l; }
        h = e_wh(e, l, e->cols);
        if (r >= h) r = h - 1;
        *py = l;
        *px = r * e->cols + (x - 4 - e->gw + ECW / 2) / ECW;
    }
    if (x - 4 - e->gw + ECW / 2 < 0) *px = e->wrap ? r * e->cols : e->left;
    if (*px > e->len[*py]) *px = e->len[*py];
    if (*px < 0) *px = 0;
}

// Where things are, in the text's own coordinates (as the last draw left
// them): the text's bars, then the build pane's header, log and bars.
static void e_mouse_text(struct win *w, int ev, int x, int y, int cw, int ch) {
    struct edit *e;
    int row, line, t, by, r, l, h;
    e = E(w);
    by = e->tah + e->fh + BHDR;                    // the build log's top
    if (ev == E_WHEEL) { e_scrolled(e, e->top + y * 3); return; }
    if (ev == E_MOVE) {
        t = ui_scroll_drag(cw - 17, 0, y);
        if (t >= 0) { e_scrolled(e, t); return; }
        t = ui_scroll_drag(0, e->tah - 16, x);
        if (t >= 0) { e->left = t; return; }
        t = ui_scroll_drag(cw - 17, by, y);
        if (t >= 0) { e->btop = t; return; }
        t = ui_scroll_drag(0, by + BLOG_H, x);
        if (t >= 0) { e->bleft = t; return; }
        // a selection being dragged out: Traditional's, or VIM's Visual
        if (e->drag) {
            e_pos_at(e, x, y, &row, &line);
            if (row == e->cy && line == e->cx) return;
            e->cy = row; e->cx = line; e->want = line;
            if (!e->vim) e->tsel = e->vy != e->cy || e->vx != e->cx;
            else { if (e->mode != M_VISUAL) e->mode = M_VISUAL; e_clamp(e); }
            wk_invalidate(w->id, 0, 0, 0, 0);
        }
        return;
    }
    if (ev != E_DOWN && ev != E_DBL) return;
    if (e->fh && y >= e->tah && y < e->tah + e->fh) {
        e->drag = 0;
        e_find_act(w, ui_find_mouse(&e->fb, ev, x, y, 0, e->tah, cw));
        return;
    }
    if (e->bshown && y >= e->tah + e->fh && y < e->tah + e->fh + e->ph) {
        if (ev != E_DOWN && y < by) return;
        if (y < by) {
            if (e->building && ui_hit(x, y, cw - 72, e->tah + e->fh + 1, 66, BHDR - 2)) e_cancel(w);
            return;
        }
        if (y >= by + BLOG_H) {
            if (ev != E_DOWN) return;
            t = ui_hscroll_click(x, y, 0, by + BLOG_H, cw - 17, e->bmaxw, e->bcols, e->bleft);
            if (t >= 0) e->bleft = t;
            return;
        }
        if (x >= cw - 17) {
            if (ev != E_DOWN) return;
            t = ui_scroll_click(x, y, cw - 17, by, BLOG_H, e->blogn, BROWS, e->btop);
            if (t >= 0) e->btop = t;
            return;
        }
        row = e->btop + (y - by - 1) / ECH;
        if (row < 0 || row >= e->blogn) return;
        e->bsel = row;
        if (ev == E_DBL) {
            t = 0;
            while (t < e->en) { if (e->elog[t] == row) { e_goto_error(w, t); return; } ++t; }
        }
        return;
    }
    if (y >= e->tah) return;
    t = ui_scroll_click(x, y, cw - 17, 0, e->tah - (e->hb ? 16 : 0), e->nl, e->vis, e->top);
    if (t >= 0) { e_scrolled(e, t); return; }
    if (e->hb && y >= e->tah - 16) {
        t = ui_hscroll_click(x, y, 0, e->tah - 16, cw - 17, e->maxw + 1, e->cols, e->left);
        if (t >= 0) e->left = t;
        return;
    }
    if (e->mode == M_VISUAL || e->mode == M_VLINE || e->mode == M_CMD) e->mode = e->vim ? M_NORMAL : M_INSERT;
    e->tlast = 0;
    e->fb.keys = 0;                                // a click in the text: the keys are the text's again
    // Shift+click: Traditional's selection runs from where the cursor was
    if (!e->vim && (wk.mods & M_SHIFT) && ev == E_DOWN) { if (!e->tsel) { e->vy = e->cy; e->vx = e->cx; } }
    else e->tsel = 0;
    e_pos_at(e, x, y, &e->cy, &e->cx);
    if (e->vim) e_clamp(e);
    e->want = e->cx;
    if (!e->vim && (wk.mods & M_SHIFT) && ev == E_DOWN) { e->tsel = e->vy != e->cy || e->vx != e->cx; e->drag = 1; return; }
    // a double click takes a word (Traditional); a press starts a selection a drag makes
    if (!e->vim && ev == E_DBL && e_isword(e_char(e, e->cy, e->cx))) {
        r = e->cx; while (r > 0 && e_isword(e->ln[e->cy][r - 1])) --r;
        l = e->cx; while (l < e->len[e->cy] && e_isword(e->ln[e->cy][l])) ++l;
        e->vy = e->cy; e->vx = r; e->cx = l; e->tsel = l > r;
        return;
    }
    e->vy = e->cy; e->vx = e->cx;
    e->drag = ev == E_DOWN;
}

// The tabs over the text, while the Code tab is open (a compiled file's
// window has none: it is all Code tab); the Code tab in front
static int x_tabs(struct edit *e) { return e->xshown && e->xp && !e->xobj; }
static int x_front(struct edit *e) { return e->xshown && e->xtab && e->xp; }
static char *x_labels[2];
static void x_tab_labels(struct edit *e) {
    x_labels[0] = e->path[0] ? ui_base(e->path) : "Untitled";
    x_labels[1] = "Code";
}

// The pointer over the window: a text beam over the text, an arrow over
// the tabs, the Code tab, the bars and the build log (as the last draw
// laid them out)
int edit_pointer(struct win *w, int x, int y, int cw, int ch) {
    struct edit *e;
    e = E(w);
    if (f_on(e, cw)) {
        e->fwx = f_width(e, cw);
        if (x >= e->fwx && x < e->fwx + SPW) return PTR_COLS;
        if (x < e->fwx) return PTR_ARROW;
        x = x - e->fwx - SPW; cw = cw - e->fwx - SPW;
    }
    if (x_tabs(e)) { if (y < TABH) return PTR_ARROW; y = y - TABH; }
    if (x_front(e)) return PTR_ARROW;
    if (y < e->tah - (e->hb ? 16 : 0) && x < cw - 17) return PTR_TEXT;
    return PTR_ARROW;
}

// The file pane on the left when it is shown, and beside it the text, or
// the Code tab in its place, under their tabs
void edit_draw(struct win *w, int ox, int oy, int cw, int ch, int focused) {
    struct edit *e;
    e = E(w);
    ec = scheme_cols + ide_scheme * SC_N;
    if (f_on(e, cw)) {
        e->fwx = f_width(e, cw);
        f_draw(e, ox, oy, ch);
        ui_splitter(ox + e->fwx, oy, SPW, ch);
        ox = ox + e->fwx + SPW; cw = cw - e->fwx - SPW;
    }
    if (x_tabs(e)) {
        x_tab_labels(e);
        d_rect(ox, oy, cw, TABH, C_FACE);
        ui_tabs(ox + 4, oy + 2, x_labels, 2, e->xtab);
        ui_button(ox + cw - 24, oy + 3, 20, 18, "x", 0, 0);   // closes the Code tab
        oy = oy + TABH; ch = ch - TABH;
    }
    // the function at the cursor: the Code tab's, and the gutter's bands
    if (e->xshown && e->xp && !e->xobj) xp_cursor(e->xp, e->cy + 1);
    d_clip(ox, oy, cw, ch);
    if (x_front(e)) xp_draw(e->xp, ox, oy, cw, ch, ec, e->modified, focused);
    else e_draw_text(w, ox, oy, cw, ch, focused);
    d_clip_end();
}

void edit_mouse(struct win *w, int ev, int x, int y, int cw, int ch) {
    struct edit *e;
    int t;
    e = E(w);
    // the splitter let go: its width kept, for the IDE windows opened after
    if (ev == E_UP) { e->drag = 0; if (e->fdrag) { e->fdrag = 0; ide_fw = e->fw; ide_save(); } return; }
    if (f_on(e, cw)) {
        e->fwx = f_width(e, cw);
        if (ev == E_MOVE) {
            if (e->fdrag && (t = ui_split_drag(x)) >= 0) {
                e->fw = t;
                if (e->fw > cw - SPW - 220) e->fw = cw - SPW - 220;
                if (e->fw < FMIN) e->fw = FMIN;
                return;
            }
            t = ui_scroll_drag(e->fwx - 17, FHDR, y);
            if (t >= 0) { e->ftop = t; return; }
            t = ui_scroll_drag(0, ch - 16, x);
            if (t >= 0) { e->fleft = t; return; }
        } else if (ev == E_DOWN && ui_split_click(x, y, e->fwx, 0, SPW, ch, e->fwx)) { e->drag = 0; e->fdrag = 1; return; }
        else if (x < e->fwx + SPW) { e->drag = 0; if (x < e->fwx) f_mouse(w, ev, x, y, ch); return; }
        x = x - e->fwx - SPW; cw = cw - e->fwx - SPW;
    }
    if (x_tabs(e)) {
        // a tab picked, or the Code tab closed (a wheel's y is how far, not where)
        if (ev != E_WHEEL && ev != E_MOVE && y < TABH) {
            e->drag = 0;
            if (ev != E_DOWN) return;
            x_tab_labels(e);
            if (ui_hit(x, y, cw - 24, 3, 20, 18)) { x_close(e); mark_dirty(); return; }
            t = ui_tab_hit(x, y, 4, 2, x_labels, 2);
            if (t >= 0) { e->xtab = t; mark_dirty(); }
            return;
        }
        if (ev != E_WHEEL) y = y - TABH;
        ch = ch - TABH;
    }
    if (x_front(e)) {
        e->drag = 0;
        t = xp_mouse(e->xp, ev, x, y, cw, ch);
        if (t == 2) { x_goto(w); mark_dirty(); return; }
        if (t != 0) mark_win_dirty(w);
        return;
    }
    e_mouse_text(w, ev, x, y, cw, ch);
}

// ---- Settings: the colour scheme, the input mode and the font --------------------------------
//
// One page for every IDE window, a window of its own: each choice is used
// at once, in every IDE window open, and kept in /etc/ide.cfg as
// "scheme N input M font F size S pane P" (M 1 for VIM; F and S the kit's
// fixed-width faces and sizes; P the file pane's width), as Settings keeps
// the desktop's in /etc/desktop.cfg.

static char icfg[64];

// the grid the font makes
static void ide_grid() {
    ide_face = wk_mono_font(ide_mono);
    wk_grid(ide_size, &ide_fs, &ide_cw, &ide_ch);
}

static void ide_load() {
    int fd, n, i, v;
    ide_loaded = 1;
    n = 0;
    if ((fd = uopen("/etc/ide.cfg", O_RD)) >= 0) { n = uread(fd, icfg, 60); uclose(fd); }
    if (n < 0) n = 0;
    icfg[n] = 0;
    i = 0;
    while (i < n) {
        if (icfg[i] == 's' && icfg[i + 1] == 'c' && icfg[i + 6] == ' ' && e_digits(icfg + i + 7, &v) > 0 && v < N_SCHEMES) ide_scheme = v;
        if (icfg[i] == 'i' && icfg[i + 1] == 'n' && icfg[i + 5] == ' ' && e_digits(icfg + i + 6, &v) > 0) ide_vim = v != 0;
        if (icfg[i] == 'f' && icfg[i + 1] == 'o' && icfg[i + 4] == ' ' && e_digits(icfg + i + 5, &v) > 0 && v < WK_FACES) ide_mono = v;
        if (icfg[i] == 's' && icfg[i + 1] == 'i' && icfg[i + 4] == ' ' && e_digits(icfg + i + 5, &v) > 0 && v < WK_SIZES) ide_size = v;
        if (icfg[i] == 'p' && icfg[i + 1] == 'a' && icfg[i + 4] == ' ' && e_digits(icfg + i + 5, &v) > 0 && v >= FMIN && v < 2000) ide_fw = v;
        ++i;
    }
    ide_grid();
}

static void ide_save() {
    int fd;
    if ((fd = uopen("/etc/ide.cfg", O_WR + O_CREATE + O_TRUNCATE)) < 0) return;
    ui_cpy(icfg, "scheme ");
    ui_num(icfg + ui_len(icfg), ide_scheme);
    ui_cat(icfg, ide_vim ? " input 1 font " : " input 0 font ");
    ui_num(icfg + ui_len(icfg), ide_mono);
    ui_cat(icfg, " size ");
    ui_num(icfg + ui_len(icfg), ide_size);
    ui_cat(icfg, " pane ");
    ui_num(icfg + ui_len(icfg), ide_fw);
    ui_cat(icfg, "\n");
    write(fd, icfg, ui_len(icfg));
    uclose(fd);
}

// a choice made: into every IDE window, and kept
static void ide_set(int scheme, int vim) {
    struct win *w;
    struct edit *e;
    ide_scheme = scheme; ide_vim = vim;
    ide_save();
    w = win_first();
    while (w) {
        if (w->used && w->kind == K_EDIT && (e = E(w)) && e->vim != vim) {
            e->vim = vim; e->tsel = 0; e->op = 0; e->pre = 0; e->count = 0;
            e->mode = vim ? M_NORMAL : M_INSERT;
            e_clamp(e);
            e_say(e, vim ? "VIM mode: Esc for Normal, i to type" : "Traditional: type to edit; Esc for a command");
        }
        w = w->next;
    }
    mark_dirty();
}

// the font chosen: every IDE window, and its Code tab, laid out again in it
static void ide_set_font(int face, int size) {
    ide_mono = face; ide_size = size;
    ide_grid();
    ide_save();
    mark_dirty();
}

// a piece of the preview: n characters of s in colour hc, along from *x
static void iset_piece(int *x, int y, int hc, char *s) {
    d_textn(*x, y, ec[hc], EFONT, EFACE, ECW, s, ui_len(s));
    *x = *x + ui_len(s) * ECW;
}

// the font group's columns: a face, or a size, in each
static int iset_col[3] = { 18, 112, 222 };

static void iset_draw(int w, int cw, int ch, int focused) {
    int i, x, y;
    d_rect(0, 0, cw, ch, C_FACE);
    ui_group(8, 8, cw - 16, 66, "Colour scheme");
    i = 0;
    while (i < N_SCHEMES) { ui_radio(18, 28 + i * 20, scheme_names[i], i == ide_scheme); ++i; }
    ui_group(8, 82, cw - 16, 66, "Input mode");
    ui_radio(18, 102, "Traditional: type at once, as in Text Editor", !ide_vim);
    ui_radio(18, 122, "VIM: Normal, Insert and Visual modes", ide_vim);
    ui_group(8, 156, cw - 16, 66, "Font");
    i = 0;
    while (i < WK_FACES) { ui_radio(iset_col[i], 174, wk_mono_name(i), i == ide_mono); ++i; }
    i = 0;
    while (i < WK_SIZES) { ui_radio(iset_col[i], 196, wk_size_name(i), i == ide_size); ++i; }
    // the preview, in the scheme and the font chosen
    ec = scheme_cols + ide_scheme * SC_N;
    y = 230;
    d_rect(8, y, cw - 16, 3 * ECH + 8, ec[SC_BG]);
    d_bevel(8, y, cw - 16, 3 * ECH + 8, B_SUNKEN);
    x = 14; iset_piece(&x, y + 4, HC_PRE, "#include"); iset_piece(&x, y + 4, HC_TEXT, " "); iset_piece(&x, y + 4, HC_STR, "\"c4ix.h\"");
    x = 14; iset_piece(&x, y + 4 + ECH, HC_TYPE, "int"); iset_piece(&x, y + 4 + ECH, HC_TEXT, " main() { ");
    iset_piece(&x, y + 4 + ECH, HC_KW, "return"); iset_piece(&x, y + 4 + ECH, HC_TEXT, " "); iset_piece(&x, y + 4 + ECH, HC_NUM, "0");
    iset_piece(&x, y + 4 + ECH, HC_TEXT, "; }");
    x = 14; iset_piece(&x, y + 4 + 2 * ECH, HC_COM, "// the IDE's colours");
    ui_button(cw - 88, ch - 34, 76, 24, "OK", 0, 1);
}

static void iset_mouse(int w, int ev, int x, int y, int b) {
    int cw, ch, i;
    if (ev != E_DOWN) return;
    wk_size(w, &cw, &ch);
    i = 0;
    while (i < N_SCHEMES) { if (ui_hit(x, y, 14, 26 + i * 20, cw - 28, 18)) { ide_set(i, ide_vim); return; } ++i; }
    if (ui_hit(x, y, 14, 100, cw - 28, 18)) { ide_set(ide_scheme, 0); return; }
    if (ui_hit(x, y, 14, 120, cw - 28, 18)) { ide_set(ide_scheme, 1); return; }
    i = 0;
    while (i < 3) {
        if (i < WK_FACES && ui_hit(x, y, iset_col[i] - 4, 172, 100, 18)) { ide_set_font(i, ide_size); return; }
        if (i < WK_SIZES && ui_hit(x, y, iset_col[i] - 4, 194, 100, 18)) { ide_set_font(ide_mono, i); return; }
        ++i;
    }
    if (ui_hit(x, y, cw - 88, ch - 34, 76, 24)) wk_close(w);
}

static void iset_key(int w, int down, int code, int ch, int mods) {
    if (!down) return;
    if (code == KEY_ESC || code == KEY_ENTER) wk_close(w);
    else if (code == KEY_UP && ide_scheme > 0) ide_set(ide_scheme - 1, ide_vim);
    else if (code == KEY_DOWN && ide_scheme < N_SCHEMES - 1) ide_set(ide_scheme + 1, ide_vim);
}

static struct wk_class iset_class = { .kind = K_SETTINGS, .draw = iset_draw, .mouse = iset_mouse, .key = iset_key };

static void ide_settings() {
    int i;
    if ((i = wk_find(&iset_class))) { wk_raise(i); return; }
    iset_class.size = 16;
    wk_open(&iset_class, "IDE Settings", 380, 370, WK_FIXED | WK_CENTER, 0);
}

// ---- the window -----------------------------------------------------------------------------

int edit_open(char *path) {
    int i;
    struct win *w;
    struct edit *e;
    if (!ide_loaded) ide_load();
    i = win_open(K_EDIT, "Untitled - IDE", 760, 500, sizeof(struct edit));
    if (i < 0) return i;
    w = win_get(i);
    e = E(w);
    edit_menus[0].title = "File"; edit_menus[1].title = "Edit"; edit_menus[2].title = "Build";
    edit_menus[3].title = "View"; edit_menus[4].title = "Help";
    edit_file_items[0] = "New"; edit_file_items[1] = "Open..."; edit_file_items[2] = "Save";
    edit_file_items[3] = "Save As..."; edit_file_items[4] = "-"; edit_file_items[5] = "Close"; edit_file_items[6] = 0;
    edit_edit_items[E_CUT] = "Cut   Ctrl+X"; edit_edit_items[E_COPY] = "Copy   Ctrl+C"; edit_edit_items[E_PASTE] = "Paste   Ctrl+V";
    edit_edit_items[3] = "-"; edit_edit_items[E_ALL] = "Select All   Ctrl+A"; edit_edit_items[5] = "-";
    edit_edit_items[E_FIND] = "Find...   Ctrl+F"; edit_edit_items[E_FNEXT] = "Find Next   F3";
    edit_edit_items[E_FPREV] = "Find Previous  Shift+F3"; edit_edit_items[9] = 0;
    edit_build_items[0] = "Build   F5"; edit_build_items[1] = "Run   F6"; edit_build_items[2] = "Next Error   F8";
    edit_build_items[3] = "Previous Error"; edit_build_items[4] = "Show Output   F4";
    edit_build_items[5] = "Cancel Build"; edit_build_items[6] = 0;
    edit_view_items[0] = "Files   Ctrl+B"; edit_view_items[1] = "Syntax Colouring";
    edit_view_items[2] = "Word Wrap"; edit_view_items[3] = "Code   F7"; edit_view_items[4] = "-";
    edit_view_items[5] = "Settings..."; edit_view_items[6] = 0;
    edit_help_items[0] = "Keys"; edit_help_items[1] = 0;
    edit_menus[0].items = edit_file_items; edit_menus[1].items = edit_edit_items; edit_menus[2].items = edit_build_items;
    edit_menus[3].items = edit_view_items; edit_menus[4].items = edit_help_items;
    wk_menu(i, edit_menus, 5);
    e->utext = (char **)ualloc(UNDO_MAX * sizeof(int)); e->ulen = (int *)ualloc(UNDO_MAX * sizeof(int));
    e->ucy = (int *)ualloc(UNDO_MAX * sizeof(int)); e->ucx = (int *)ualloc(UNDO_MAX * sizeof(int));
    e->rtext = (char **)ualloc(UNDO_MAX * sizeof(int)); e->rlen = (int *)ualloc(UNDO_MAX * sizeof(int));
    e->rcy = (int *)ualloc(UNDO_MAX * sizeof(int)); e->rcx = (int *)ualloc(UNDO_MAX * sizeof(int));
    e->rec = (int *)ualloc(REC_MAX * 3 * sizeof(int));
    e->dot = (int *)ualloc(REC_MAX * 3 * sizeof(int));
    e->blog = (char **)ualloc(BLOG_MAX * sizeof(int));
    e->epath = (char **)ualloc(ERR_MAX * sizeof(int));
    e->eline = (int *)ualloc(ERR_MAX * sizeof(int));
    e->elog = (int *)ualloc(ERR_MAX * sizeof(int));
    e->vim = ide_vim; e->nu = 1; e->mode = ide_vim ? M_NORMAL : M_INSERT; e->ecur = 0 - 1; e->bsel = 0 - 1;
    e->wrap = 1;
    e->hl_lang = 0 - 1;
    e->fw = ide_fw;
    e->lcx = 0 - 1; e->lcy = 0 - 1;
    e_insline(e, 0, "", 0);
    // the file pane: the top of the disk, every folder closed
    e->fshown = 1;
    f_reserve(e, 64);
    f_open_dir(e, 0 - 1);
    if (path && path[0]) {
        if (!e_open(w, path, 0)) { ui_ncpy(e->path, path, 128); e_say(e, "New file"); }
    }
    e->modified = 0;
    if (!e->msg[0] && e->vim) e_say(e, "VIM keys: i to type, Esc, :w to save, :make (F5) to build, :help is the Help menu");
    if (!e->msg[0]) e_say(e, "Type to edit; Esc for a command (w, make, e FILE); F5 builds; View > Settings for colours and VIM");
    e_retitle(w);
    return i;
}

// Open and Save As: the kit's file box, starting at the file's own folder
static void e_filebox(struct win *w, int save) {
    struct edit *e;
    e = E(w);
    ui_ncpy(e->ask, e->path[0] ? e->path : (save ? "/tmp/untitled.c" : "/usr"), WK_PATH);
    if (!e->path[0] && !save) ui_cat(e->ask, "/");
    wk_filebox(w->id, save ? A_SAVEAS : A_OPEN, save, ide_filter, e->ask, WK_PATH);
}

void edit_command(struct win *w, int menu, int item) {
    struct edit *e;
    e = E(w);
    if (menu == 0) {
        if (item == 0) {
            if (e->modified) { msgbox(w, "IDE", "Save the changes first (Ctrl+S, or :w), or :q! to drop them.", 0, A_NONE); return; }
            if (e->xobj) { e->xobj = 0; x_close(e); }
            e_settext(e, "", 0); e->path[0] = 0; e->modified = 0; e->cy = 0; e->cx = 0; e->tsel = 0; e_retitle(w);
        }
        else if (item == 1) e_filebox(w, 0);
        else if (item == 2) {
            if (!e->path[0]) e_filebox(w, 1);
            else { e_save(e, e->path); e_retitle(w); }
        }
        else if (item == 3) e_filebox(w, 1);
        else if (item == 5) win_close(win_index(w));
        return;
    }
    if (menu == 1) { e_edit(w, item); return; }
    if (menu == 2) {
        if (item == 0) e_make(w);
        else if (item == 1) e_run(w);
        else if (item == 2) e_goto_error(w, e->ecur + 1);
        else if (item == 3) e_goto_error(w, e->ecur - 1);
        else if (item == 4) e->bshown = !e->bshown;
        else if (item == 5) e_cancel(w);
        return;
    }
    if (menu == 3) {
        if (item == 0) e->fshown = !e->fshown;
        else if (item == 1) e->nosyn = !e->nosyn;
        else if (item == 2) { e->wrap = !e->wrap; e->left = 0; }
        else if (item == 3) e_code(w);
        else if (item == 5) ide_settings();
        return;
    }
    if (e->vim) msgbox(w, "IDE keys",
           "Esc for Normal mode, i to insert. hjkl or arrows move; w b e words; dd yy p; u undo; . repeat. :w save, :make or F5 build, F8 next error, F6 run, F7 the code it compiles to, Ctrl+B the file pane, :syntax off, :set novim for a plain editor; View > Settings for Traditional typing.",
           0, A_NONE);
    else msgbox(w, "IDE keys",
           "Type to edit; Shift with the arrows selects; Ctrl+X, C, V cut, copy and paste; Ctrl+A all; Ctrl+Z undo, Ctrl+Y redo; Ctrl+S saves. Esc for a command: w, make, run, e FILE, set nowrap. F5 builds, F6 runs, F7 shows the code it compiles to, F8 the next error, Ctrl+B the file pane; View > Settings for VIM mode, colours and the font.",
           0, A_NONE);
}

void edit_answer(struct win *w, int action, int yes) {
    struct edit *e;
    e = E(w);
    if (!yes) return;
    if (action == A_OPEN) {
        if (e->modified) { e_say(e, "No write since last change: save first (Ctrl+S, or :w)"); return; }
        if (!e_open(w, e->ask, 0)) { ui_ncpy(e->path, e->ask, 128); e_settext(e, "", 0); e->modified = 0; e_say(e, "New file"); }
    } else if (action == A_SAVEAS) e_save(e, e->ask);
    else if (action == A_BINARY && !e_load(e, e->pend)) e_say(e, "Cannot open that file");
    e->tsel = 0;
    e_retitle(w);
}
// explore.c -- the IDE's Code tab: the C4 code a C file compiles to, or a
// compiled file's own, a function at a time, with the C source it came
// from between the instructions. A cut-down Code Explorer
// (docs/c4-explorer.md, track E), after the web page's
// (libjs/web/explore.html): the functions down the left, found by typing
// part of a name, and the code of the one picked beside them, each line
// of source the map names shown above the instructions it made, long
// lines folded (or, with Wrap off, scrolled across). It takes the
// editor's place in the window, as a tab beside the text, since at
// 800x600 and below there is no room for both side by side.
//
// Two ways in. For a .c file being edited, it compiles the saved file
// with cc -g -c (c4sc's source map, the SMAP trailer of
// docs/c4-explorer.md 2.2) into /tmp, on a pipe of its own, apart from
// the build; again after every save, and when its -O is turned on or
// off; the editor's cursor picks the function. A compiled file -- a
// program, an object or a library: anything with C4R's header, and every
// one C4IX ships carries a map -- opens in it as it is (edit.c, when it
// opens one), its sources found by the map's paths: as they are, under
// /usr (the root archive's /usr is the repository, so its src/ is
// /usr/src), or beside the file. A program linked against shared
// libraries brings them too, as the loader would (loader.c: a static
// global __c4_needed names each one): their functions follow the
// program's in the list, in a colour of their own, and a call into one
// goes there.
//
// It reads each object itself (a module): the code, the patches that
// say what each operand refers to, the symbols, and the map's files,
// functions and rows. Each operand is named as libjs/c4r.js's insnText
// names it (a function, a global, a string, a label, [bp+n]). A click on
// a row lights every row of its line; a double click (or Enter) on a
// call goes to the callee, and Back (Alt+Left, or Backspace) comes back;
// a double click on any other row opens its line in the editor. Without
// a map the functions come from the symbols, with no source to show.
//
// c4lc splices the helpers it calls (<udiv>, <umod>, the soft float
// __c4d_ and long long __c4ll_ ones) into each unit that uses them, so a
// program has as many copies as units that needed one; the list names
// each copy's unit beside it.
//
// The opcode names are the machine's (src/c4bb/sim/devices.js, OPNAMES);
// libjs/tests/test-desktop.mjs checks the copy here against them.

#include "desktop.h"

// the IDE's text grid (edit.c's, IDE Settings' font), and the tab's parts:
// its headers (a field's height), its footer, how long a name is kept, the
// source lines with no code shown between two that have, how far back
// Back goes, the modules one tab holds (a program and the libraries it
// loads: loader.c's LIB_MAX and one), and the longest source line drawn;
// then how far the listing looks for a row's lines (xp_lay): the lines a
// statement may go on to, the labels and braces above one, and the head
// of a function, shown whole up to this long
#define XCW ide_cw
#define XCH ide_ch
#define XFONT ide_fs
#define XFACE ide_face
#define XFOOT (XCH + 4)
enum { XHDR = 22, XGAP = 3, XHIST = 16, XFILT = 30, XMODS = 9, XSRC = 480,
       XCONT = 24, XLEAD = 12, XHEAD = 80 };
// the opcodes it treats apart (OPNAMES' order)
enum { O_LEA = 0, O_IMM = 1, O_JMP = 2, O_JSR = 3, O_BZ = 4, O_BNZ = 5, O_ADJ = 7, O_JSRI = 61, O_JSRS = 62, O_JMPA = 63,
       O_LDL = 79, O_PSHL = 81, O_LEAP = 83, O_IMMP = 84, O_STL = 87, O_N = 95 };
// patch types (load-c4r.c), and symbol classes and attributes (c4r.js)
enum { P_CODE = -1, P_DATA = -2, S_FUN = 129, S_GLO = 131, S_EXTERN = 16 };
// the colours, from the IDE's scheme as edit.c passes it (HC_* then SC_*)
enum { XC_TEXT = 0, XC_KW = 1, XC_TYPE = 2, XC_STR = 3, XC_COM = 4, XC_NUM = 5, XC_PRE = 6,
       XC_BG = 7, XC_GUT = 8, XC_SEL = 10 };

static char *opnames =
    "LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
    "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
    "OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"
    "PUTC,PUTS,RALC,MCPY,STRC,ITH ,_OPC,_BLT,_TRP,OPCD,"
    "_JMP,_ADJ,C4CF,C4CY,TIME,SIGH,SIGI,USLP,INFO,OPSL,"
    "C4IV,FLT ,JSRI,JSRS,JMPA,TLEV,DBG ,"
    "CPUI,CPUN,CPUS,CPUH,"
    "CAS ,XCHG,FADD,CWAI,CWAK,IPI ,"
    "LXI ,SXI ,TRAW,"
    "LDL ,LDG ,PSHL,PSHG,LEAP,IMMP,LIP ,ADDL,STL ,POPA,"
    "FPU ,"
    "LH  ,LHU ,SH  ,LSR ,LCU ,";

// a line's colour: a small palette, cycled by line
static int bands[8] = { 0x5fd7ff, 0xffaf5f, 0x87ff87, 0xff87d7, 0xd7d75f, 0xaf87ff, 0x5fffd7, 0xff8787 };

// One object read: the program shown, or a library it loads
struct xmod {
    char path[128];
    char *buf; int bufn, W;
    int *code; int ncode; char *data; int ndata, memsz;
    int *ptype; int *pval;                // per code word: the patch on it, 0 none
    int nsym; int *sid; int *scls; int *sattr; int *sval; char **sname;
    int nfile; char **fpath; int *fsize;  // the map's files, their sizes compiled
    // each file's source, once looked for: its text, where its lines start and how many,
    // and 1 found, 2 found but not the size it was compiled at, -1 not found
    // -- and for the compiler's own, the line of the file holding them before their first
    char **stext; int **sline; int *snl; int *sst; char **spath; int *soff;
    int nfn; int *fstart; int *flen; int *ffile; int *fline; char **fname;
    int *funit;                           // the unit each function came with (a helper: the one before it), or -1
    int nrow; int *roff; int *rfile; int *rline;
    int fn0;                              // its first function's number among all the tab's
};

struct xp {
    // what is shown: a compile of PATH (a .c file), or the compiled file PATH itself
    char path[128], dir[128], obj[48];
    int objmode;
    int pid, out_r, busy, opt, ok, failed;
    char err0[96], err1[96]; int errn;    // the compiler's last two lines, when it failed
    char part[96]; int partn;
    struct xmod *mods[XMODS]; int nmod;   // the program (0), then the libraries it loads
    int here;                             // module 0's file being edited, or -1
    // every function, numbered: its module and its number there; one of a name shared in its module
    int nall; int *gmod; int *gidx; int *gdup;
    // the function list: all of them in order, and the ones the filter keeps
    int *lord; int *lvis; int nvis, ltop, lrows, byname, lfollow;
    char filt[XFILT + 2]; int filtc;
    // the function shown (a number among all), its module, decoded
    int cur; struct xmod *cm; int nins; int *ioff; int *iop; int *iarg; int *ilab; int *irow;
    int lmin, lmax; int *lband;           // its lines in the file edited: a band's colour, or -1
    // the listing: row i is instruction dins[i], or (dins[i] < 0) piece dseg[i] of line dline[i] of file dfile[i]
    int *dins; int *dfile; int *dline; int *dseg; int nd, laycols, maxw;
    int top, left, wrap, sel, rows, cols, lastline, hmod, hfile, hline;   // the view; the row picked; the line lit
    int hist[XHIST]; int nhist;
    char gopath[128]; int goline;         // a line asked for in the editor
    char msg[96], note[160];
};

static struct xp *X(int *x) { return (struct xp *)x; }
static char xb[320], xo[XSRC + 8];
static char *hexd = "0123456789abcdef";

// ---- reading an object -----------------------------------------------------------------------

static int xm_word(struct xmod *m, int p) {
    char *b;
    int v;
    b = m->buf + p;
    v = (b[0] & 255) | ((b[1] & 255) << 8) | ((b[2] & 255) << 16) | ((b[3] & 255) << 24);
    if (b[3] & 128) v = v | (-1 << 31);   // a negative word, at either size
    return v;
}
static int up;                            // the map's reading position
static int xp_u(char *b) {
    int v, s, c;
    v = 0; s = 0;
    c = 128;
    while (c & 128) { c = b[up] & 255; ++up; if (s < 31) v = v + ((c & 127) << s); s = s + 7; }
    return v;
}
static int xp_s(char *b) {
    int v, s, c;
    v = 0; s = 0;
    c = 128;
    while (c & 128) { c = b[up] & 255; ++up; if (s < 31) v = v + ((c & 127) << s); s = s + 7; }
    if ((c & 64) && s < 31) v = v - (1 << s);
    return v;
}
static char *xp_str(char *b, int n) {
    char *s;
    s = (char *)ualloc(n + 1);
    memcpy(s, b + up, n);
    s[n] = 0;
    up = up + n;
    return s;
}
static int *xp_ints(int n) { return (int *)ualloc((n + 1) * sizeof(int)); }
static int *xp_zeros(int n) { int *p; p = xp_ints(n); memset((char *)p, 0, (n + 1) * sizeof(int)); return p; }

static void xm_free(struct xmod *m) {
    int i;
    if (m->buf) free(m->buf);
    if (m->code) { free((char *)m->code); free((char *)m->ptype); free((char *)m->pval); }
    i = 0; while (i < m->nsym) { free(m->sname[i]); ++i; }
    if (m->sid) { free((char *)m->sid); free((char *)m->scls); free((char *)m->sattr); free((char *)m->sval); free((char *)m->sname); }
    i = 0;
    while (i < m->nfile) {
        free(m->fpath[i]);
        if (m->stext && m->stext[i]) { free(m->stext[i]); free((char *)m->sline[i]); free(m->spath[i]); }
        ++i;
    }
    if (m->fpath) { free((char *)m->fpath); free((char *)m->fsize); }
    if (m->stext) { free((char *)m->stext); free((char *)m->sline); free((char *)m->snl); free((char *)m->sst); free((char *)m->spath); free((char *)m->soff); }
    i = 0; while (i < m->nfn) { free(m->fname[i]); ++i; }
    if (m->fstart) { free((char *)m->fstart); free((char *)m->flen); free((char *)m->ffile); free((char *)m->fline); free((char *)m->fname); }
    if (m->funit) free((char *)m->funit);
    if (m->roff) { free((char *)m->roff); free((char *)m->rfile); free((char *)m->rline); }
    free((char *)m);
}

// The SMAP chunk: files, functions and rows (docs/c4-explorer.md 2.2)
static int xm_smap(struct xmod *m, char *b, int n) {
    int flags, i, k, start, off, file, line, d;
    up = 0;
    if ((b[0] & 255) != 1) return 0;
    flags = b[1] & 255;
    up = 2;
    m->nfile = xp_u(b);
    m->fpath = (char **)xp_ints(m->nfile);
    m->fsize = xp_ints(m->nfile);
    i = 0;
    while (i < m->nfile) {
        k = xp_u(b);
        m->fpath[i] = xp_str(b, k);
        m->fsize[i] = xp_u(b);                // its size, then its CRC
        if (flags & 1) up = up + 4;
        ++i;
    }
    m->nfn = xp_u(b);
    m->fstart = xp_ints(m->nfn); m->flen = xp_ints(m->nfn);
    m->ffile = xp_ints(m->nfn); m->fline = xp_ints(m->nfn);
    m->fname = (char **)xp_ints(m->nfn);
    start = 0; i = 0;
    while (i < m->nfn) {
        start = start + xp_u(b);
        m->fstart[i] = start;
        m->flen[i] = xp_u(b);
        k = xp_u(b);
        m->fname[i] = xp_str(b, k);
        m->ffile[i] = xp_u(b);
        m->fline[i] = xp_u(b);
        ++i;
    }
    m->nrow = xp_u(b);
    m->roff = xp_ints(m->nrow); m->rfile = xp_ints(m->nrow); m->rline = xp_ints(m->nrow);
    off = 0; file = 0; line = 0; i = 0;
    while (i < m->nrow && up < n) {
        d = xp_u(b);
        off = off + (d >> 1);
        if (d & 1) file = xp_u(b);
        line = line + xp_s(b);
        m->roff[i] = off; m->rfile[i] = file; m->rline[i] = line;
        ++i;
    }
    m->nrow = i;
    return 1;
}

// With no map, the functions are the symbols' own, in address order, each
// up to the next
static void xm_symfuncs(struct xmod *m) {
    int i, n, gap, j, t, *v;
    n = 0; i = 0;
    while (i < m->nsym) { if (m->scls[i] == S_FUN && !(m->sattr[i] & S_EXTERN) && m->sval[i] >= 0 && m->sval[i] < m->ncode) ++n; ++i; }
    if (!n) return;
    v = xp_ints(n);
    n = 0; i = 0;
    while (i < m->nsym) { if (m->scls[i] == S_FUN && !(m->sattr[i] & S_EXTERN) && m->sval[i] >= 0 && m->sval[i] < m->ncode) { v[n] = i; ++n; } ++i; }
    gap = n / 2;
    while (gap > 0) {
        i = gap;
        while (i < n) {
            t = v[i]; j = i;
            while (j >= gap && m->sval[v[j - gap]] > m->sval[t]) { v[j] = v[j - gap]; j = j - gap; }
            v[j] = t;
            ++i;
        }
        gap = gap / 2;
    }
    m->nfn = n;
    m->fstart = xp_ints(n); m->flen = xp_ints(n); m->ffile = xp_ints(n); m->fline = xp_ints(n);
    m->fname = (char **)xp_ints(n);
    i = 0;
    while (i < n) {
        m->fstart[i] = m->sval[v[i]];
        m->flen[i] = (i + 1 < n ? m->sval[v[i + 1]] : m->ncode) - m->fstart[i];
        m->ffile[i] = 0 - 1; m->fline[i] = 0;
        m->fname[i] = (char *)ualloc(ui_len(m->sname[v[i]]) + 1);
        ui_cpy(m->fname[i], m->sname[v[i]]);
        ++i;
    }
    free((char *)v);
}

// A map file of the compiler's own, as "<c4lc softfp>"
static int xm_own(struct xmod *m, int f) { return f < 0 || f >= m->nfile || m->fpath[f][0] == '<' || !m->fpath[f][0]; }

// The object at PATH, as libjs/c4r.js's readC4r reads it, into a new
// module; 0 and a message in MSG if it is not one
static struct xmod *xm_read(char *path, char *msg) {
    int st[4], fd, n, p, W, clen, dlen, plen, slen, conl, desl, i, t, a, v, len, tag, u;
    char *b;
    struct xmod *m;
    if (ustat(path, st) < 0 || st[0] != 2) { ui_cpy(msg, "Cannot find "); ui_ncat(msg, path, 96); return 0; }
    n = st[1];
    m = (struct xmod *)ualloc(sizeof(struct xmod));
    memset((char *)m, 0, sizeof(struct xmod));
    ui_ncpy(m->path, path, 128);
    m->buf = b = (char *)ualloc(n + 8);
    fd = uopen(path, O_RD);
    if (fd < 0 || uread(fd, b, n) != n) { if (fd >= 0) uclose(fd); ui_cpy(msg, "Cannot read the object"); xm_free(m); return 0; }
    uclose(fd);
    m->bufn = n;
    if (n < 13 || b[0] != 'C' || b[1] != '4' || b[2] != 'R') { ui_cpy(msg, "Not a C4R object"); xm_free(m); return 0; }
    W = (b[4] & 255) / 8;
    if (W != 4 && W != 8) { ui_cpy(msg, "A word size this cannot read"); xm_free(m); return 0; }
    m->W = W;
    p = 5;
    m->memsz = xm_word(m, p); p = p + W;
    if (W == 4) p = p + W;
    p = p + W;                                // the entry
    clen = xm_word(m, p); p = p + W;
    dlen = xm_word(m, p); p = p + W;
    plen = xm_word(m, p); p = p + W;
    slen = xm_word(m, p); p = p + W;
    conl = xm_word(m, p); p = p + W;
    desl = xm_word(m, p); p = p + W;
    if (m->memsz < dlen) m->memsz = dlen;
    if (p + W * (clen + 3 * plen + conl + desl + 5) + dlen > n || b[p] != 'C') { ui_cpy(msg, "The object is cut short"); xm_free(m); return 0; }
    p = p + W;
    m->ncode = clen;
    m->code = xp_ints(clen); m->ptype = xp_ints(clen); m->pval = xp_ints(clen);
    i = 0;
    while (i < clen) { m->code[i] = xm_word(m, p); m->ptype[i] = 0; p = p + W; ++i; }
    p = p + W;                                // 'D'
    m->data = b + p; m->ndata = dlen;
    p = p + dlen + W;                         // the data, 'P'
    i = 0;
    while (i < plen) {
        t = xm_word(m, p); a = xm_word(m, p + W); v = xm_word(m, p + 2 * W);
        // only what is patched into the code: a code or data address, or a symbol
        if ((t == P_CODE || t == P_DATA || t > 0) && a >= 0 && a < clen) { m->ptype[a] = t; m->pval[a] = v; }
        p = p + 3 * W;
        ++i;
    }
    p = p + W + conl * W + W + desl * W;      // 'c', 'd'
    if (p + W <= n && b[p] == 'S') {
        p = p + W;
        m->sid = xp_ints(slen); m->scls = xp_ints(slen); m->sattr = xp_ints(slen); m->sval = xp_ints(slen);
        m->sname = (char **)xp_ints(slen);
        i = 0;
        while (i < slen && p + 4 * W + 1 <= n) {
            m->sid[i] = xm_word(m, p); m->scls[i] = xm_word(m, p + 2 * W); m->sattr[i] = xm_word(m, p + 3 * W);
            p = p + 4 * W;
            len = b[p] & 255; ++p;
            if (p + len + W > n) break;
            up = p; m->sname[i] = xp_str(b, len); p = p + len;
            m->sval[i] = xm_word(m, p); p = p + W;
            ++i;
        }
        m->nsym = i;
    }
    // the extension trailer: 'X', then tag, length and payload, padded, to a 0 tag
    if (p + W <= n && b[p] == 'X') {
        p = p + W;
        while (p + W <= n && (tag = xm_word(m, p)) != 0) {
            len = xm_word(m, p + W); p = p + 2 * W;
            if (len < 0 || p + len > n) break;
            if (b[p - 2 * W] == 'S' && b[p - 2 * W + 1] == 'M' && b[p - 2 * W + 2] == 'A' && b[p - 2 * W + 3] == 'P')
                xm_smap(m, b + p, len);
            p = p + ((len + W - 1) & (0 - W));
        }
    }
    if (!m->nfn) xm_symfuncs(m);
    if (!m->nfn) { ui_cpy(msg, "No functions: the object has no map and no symbols"); xm_free(m); return 0; }
    // the unit each function came with: its own file, or for a helper
    // spliced in by the compiler, the file of the function before it
    m->funit = xp_ints(m->nfn);
    u = 0 - 1; i = 0;
    while (i < m->nfn) { if (!xm_own(m, m->ffile[i]) && m->fline[i] > 0) u = m->ffile[i]; m->funit[i] = u; ++i; }
    m->stext = (char **)xp_zeros(m->nfile); m->sline = (int **)xp_zeros(m->nfile);
    m->snl = xp_zeros(m->nfile); m->sst = xp_zeros(m->nfile); m->spath = (char **)xp_zeros(m->nfile);
    m->soff = xp_zeros(m->nfile);
    return m;
}

// ---- the sources ------------------------------------------------------------------------------

static int xp_isfile(char *p) { int st[4]; return ustat(p, st) == 0 && st[0] == 2; }
static void xp_dirof(char *path, char *out) {
    int k;
    ui_ncpy(out, path, 128);
    k = ui_len(out);
    while (k > 0 && out[k - 1] != '/') --k;
    if (k > 1) --k;
    out[k] = 0;
    if (!out[0]) ui_cpy(out, "/");
}

// The helpers c4lc brings with it are C kept in strings of its parser:
// "<c4lc softfp>" is p:fpsrc and "<c4lc long long>" p:llsrc, each from
// the line after its define's opening quote; the marker that starts it,
// or 0 if map file I is not one of them
static char *xp_helper(struct xmod *m, int i) {
    if (ui_eq(m->fpath[i], "<c4lc softfp>")) return "(define p:fpsrc \"";
    if (ui_eq(m->fpath[i], "<c4lc long long>")) return "(define p:llsrc \"";
    return 0;
}

// Where module M's map file I is on this disk, into OUT: the file edited;
// the map's path as it is, or under /usr; or beside the module; the
// compiler's helpers, in its parser's source. 0 if nowhere.
static int xp_where(struct xp *x, struct xmod *m, int i, char *out) {
    char *p, dir[128];
    p = m->fpath[i];
    if (xp_helper(m, i)) { ui_cpy(out, "/usr/src/c4sp/lisp/c4lc-parse.lisp"); return xp_isfile(out); }
    if (xm_own(m, i)) return 0;
    if (m == x->mods[0] && i == x->here) { ui_ncpy(out, x->path, 128); return 1; }
    if (m == x->mods[0]) ui_ncpy(dir, x->dir, 128); else xp_dirof(m->path, dir);
    if (p[0] == '/') { if (ui_ncpy(out, p, 128) && xp_isfile(out)) return 1; }
    else {
        ui_cpy(out, "/usr/");
        if (ui_ncat(out, p, 128) && xp_isfile(out)) return 1;
        if (dir[0] && ui_join(out, dir, p, 128) && xp_isfile(out)) return 1;
    }
    if (dir[0] && ui_join(out, dir, ui_base(p), 128) && xp_isfile(out)) return 1;
    return 0;
}

// module M's map file I's source, read the first time it is asked for
static void xp_source(struct xp *x, struct xmod *m, int i) {
    char p[128];
    int st[4], fd, n, k, nl, j;
    char *t, *mk;
    int *ls;
    if (!m || i < 0 || i >= m->nfile || m->sst[i]) return;
    m->sst[i] = 0 - 1;
    if (!xp_where(x, m, i, p) || ustat(p, st) < 0 || st[1] > 1048576) return;
    n = st[1];
    t = (char *)ualloc(n + 1);
    fd = uopen(p, O_RD);
    if (fd < 0) { free(t); return; }
    k = n > 0 ? uread(fd, t, n) : 0;
    uclose(fd);
    if (k != n) { free(t); return; }
    t[n] = 0;
    nl = 1; k = 0;
    while (k < n) { if (t[k] == 10) ++nl; ++k; }
    ls = xp_ints(nl + 1);
    ls[0] = 0; nl = 1; k = 0;
    while (k < n) { if (t[k] == 10) { ls[nl] = k + 1; ++nl; } ++k; }
    ls[nl] = n + 1;                           // so the last line ends at the text's end
    m->sst[i] = n == m->fsize[i] ? 1 : 2;
    // the compiler's helpers: their first line is their define's, after the quote
    if ((mk = xp_helper(m, i))) {
        k = ui_len(mk); j = 0;
        while (j < nl && (ls[j] + k > n || memcmp(t + ls[j], mk, k))) ++j;
        if (j == nl) { free(t); free((char *)ls); return; }
        m->soff[i] = j;
        m->sst[i] = 1;
    }
    m->stext[i] = t; m->sline[i] = ls; m->snl[i] = nl;
    m->spath[i] = (char *)ualloc(ui_len(p) + 1);
    ui_cpy(m->spath[i], p);
}

// line L (1-based) of module M's map file I, its tabs spaced out to eights,
// into xo: its length, or -1 if there is no such line to read
static int xp_line(struct xp *x, struct xmod *m, int i, int l) {
    int a, b, k;
    char *s;
    xp_source(x, m, i);
    if (!m || i < 0 || i >= m->nfile || m->sst[i] <= 0) return 0 - 1;
    l = l + m->soff[i];
    if (l < 1 || l > m->snl[i]) return 0 - 1;
    a = m->sline[i][l - 1]; b = m->sline[i][l] - 1;
    if (b > a && m->stext[i][b - 1] == 13) --b;
    s = m->stext[i];
    k = 0;
    while (a < b && k < XSRC) {
        if (s[a] == 9) { xo[k] = ' '; ++k; while ((k & 7) && k < XSRC) { xo[k] = ' '; ++k; } }
        else { xo[k] = s[a]; ++k; }
        ++a;
    }
    xo[k] = 0;
    return k;
}
static int xp_blank(char *s, int n) {
    int i;
    i = 0;
    while (i < n) { if (s[i] != ' ') return 0; ++i; }
    return 1;
}

// ---- the compile ---------------------------------------------------------------------------

static int xp_seq;

int *xp_new() {
    struct xp *x;
    x = (struct xp *)ualloc(sizeof(struct xp));
    memset((char *)x, 0, sizeof(struct xp));
    x->cur = 0 - 1; x->here = 0 - 1; x->sel = 0 - 1; x->lastline = 0 - 1; x->hfile = 0 - 1; x->opt = 1; x->wrap = 1;
    ++xp_seq;
    ui_cpy(x->obj, "/tmp/.ide-");
    ui_num(x->obj + ui_len(x->obj), getpid());
    ui_cat(x->obj, "-");
    ui_num(x->obj + ui_len(x->obj), xp_seq);
    ui_cat(x->obj, ".c4o");
    return (int *)x;
}

static void xp_unshow(struct xp *x) {
    if (x->ioff) { free((char *)x->ioff); free((char *)x->iop); free((char *)x->iarg); free((char *)x->ilab); free((char *)x->irow); }
    if (x->lband) free((char *)x->lband);
    if (x->dins) { free((char *)x->dins); free((char *)x->dfile); free((char *)x->dline); free((char *)x->dseg); }
    x->ioff = 0; x->lband = 0; x->dins = 0; x->nins = 0; x->nd = 0; x->laycols = 0;
}

static void xp_drop(struct xp *x) {
    int i;
    xp_unshow(x);
    i = 0; while (i < x->nmod) { xm_free(x->mods[i]); x->mods[i] = 0; ++i; }
    if (x->gmod) { free((char *)x->gmod); free((char *)x->gidx); free((char *)x->gdup); }
    if (x->lord) { free((char *)x->lord); free((char *)x->lvis); }
    x->gmod = 0; x->lord = 0; x->nmod = 0; x->nall = 0; x->nvis = 0; x->nhist = 0;
    x->cur = 0 - 1; x->cm = 0; x->here = 0 - 1; x->ok = 0; x->sel = 0 - 1; x->hfile = 0 - 1; x->hline = 0;
}

static void xp_stop(struct xp *x) {
    if (!x->busy) return;
    ukill(x->pid, SIGTERM);
    uclose(x->out_r);
    uwait(x->pid);
    x->busy = 0;
}

void xp_free(int *xi) {
    struct xp *x;
    x = X(xi);
    xp_stop(x);
    xp_drop(x);
    uunlink(x->obj);
    free((char *)x);
}

// cc -g -c [-O] -I DIR -o OBJ PATH on pipes, as edit.c's :make runs
// b4ke; 0 and a message if it cannot start
int xp_compile(int *xi, char *path, char *dir) {
    struct xp *x;
    char **argv;
    int pin[2], pout[2], s0, s1, s2, k;
    x = X(xi);
    xp_stop(x);
    if (x->objmode) { xp_drop(x); x->objmode = 0; x->byname = 0; x->filt[0] = 0; x->filtc = 0; }
    ui_ncpy(x->path, path, 128);
    ui_ncpy(x->dir, dir, 128);
    if (!ui_ends(path, ".c")) { ui_cpy(x->msg, "Only a C file (.c) has code to show"); return 0; }
    argv = (char **)ualloc(12 * sizeof(int));
    k = 0;
    argv[k] = "cc"; ++k; argv[k] = "-g"; ++k; argv[k] = "-c"; ++k;
    if (x->opt) { argv[k] = "-O"; ++k; }
    argv[k] = "-I"; ++k; argv[k] = x->dir; ++k;
    argv[k] = "-o"; ++k; argv[k] = x->obj; ++k;
    argv[k] = x->path; ++k; argv[k] = 0;
    if (upipe(pin) < 0) { free((char *)argv); ui_cpy(x->msg, "No pipe for the compiler"); return 0; }
    if (upipe(pout) < 0) { uclose(pin[0]); uclose(pin[1]); free((char *)argv); ui_cpy(x->msg, "No pipe for the compiler"); return 0; }
    s0 = udup(STDIN); s1 = udup(STDOUT); s2 = udup(STDERR);
    x->pid = 0 - 1;
    if (s0 >= 0 && s1 >= 0 && s2 >= 0) {
        ucloexec(pin[1], 1); ucloexec(pout[0], 1);
        ucloexec(s0, 1); ucloexec(s1, 1); ucloexec(s2, 1);
        if (udup2(pin[0], STDIN) >= 0 && udup2(pout[1], STDOUT) >= 0 && udup2(pout[1], STDERR) >= 0) {
            x->pid = spawn("/bin/cc", k, argv);
            if (x->pid == SPAWN_NOENT) x->pid = spawn("c4ix-cc.c4r", k, argv);   // as cc finds its tools
        }
        udup2(s0, STDIN); udup2(s1, STDOUT); udup2(s2, STDERR);
    }
    uclose(pin[0]); uclose(pout[1]); uclose(pin[1]);
    uclose(s0); uclose(s1); uclose(s2);
    free((char *)argv);
    if (x->pid < 0) { uclose(pout[0]); ui_cpy(x->msg, "Cannot start cc"); return 0; }
    x->out_r = pout[0];
    x->busy = 1; x->failed = 0; x->errn = 0; x->partn = 0;
    ui_cpy(x->msg, x->opt ? "Compiling with -g -O..." : "Compiling with -g...");
    return 1;
}

static void xp_errline(struct xp *x) {
    x->part[x->partn] = 0;
    if (x->partn == 0 || (x->part[0] == ';' && x->part[1] == ';')) return;   // c4sc's size line
    if (x->errn == 2) { ui_cpy(x->err0, x->err1); x->errn = 1; }
    ui_cpy(x->errn ? x->err1 : x->err0, x->part);
    ++x->errn;
}

static int xp_open(struct xp *x, char *path, char *keep);

// The compiler's output, and its end: 1 if the tab changed. Never blocks.
int xp_tick(int *xi) {
    struct xp *x;
    char buf[256], keep[64];
    int n, i, code;
    x = X(xi);
    if (!x->busy) return 0;
    while ((n = uavail(x->out_r)) > 0) {
        if (n > 256) n = 256;
        n = uread(x->out_r, buf, n);
        if (n <= 0) break;
        i = 0;
        while (i < n) {
            if (buf[i] == 10 || x->partn >= 94) { xp_errline(x); x->partn = 0; }
            if (buf[i] != 10 && buf[i] != 13) { x->part[x->partn] = buf[i]; ++x->partn; }
            ++i;
        }
    }
    if (n >= 0) return 0;
    if (x->partn) { xp_errline(x); x->partn = 0; }
    uclose(x->out_r);
    code = uwait(x->pid);
    x->busy = 0;
    // the function shown is shown again, in the new code, if it is still there
    keep[0] = 0;
    if (x->ok && x->cur >= 0) ui_ncpy(keep, x->cm->fname[x->gidx[x->cur]], 64);
    xp_drop(x);
    if (code != 0) { x->failed = 1; ui_cpy(x->msg, "It did not compile:"); return 1; }
    if (xp_open(x, x->obj, keep)) x->msg[0] = 0;
    return 1;
}

int  xp_busy(int *xi) { return X(xi)->busy; }
int  xp_opt(int *xi) { return X(xi)->opt; }

// ---- every function, and the list ----------------------------------------------------------

static struct xmod *xp_mod(struct xp *x, int g) { return x->mods[x->gmod[g]]; }
static char *xp_name(struct xp *x, int g) { return x->mods[x->gmod[g]]->fname[x->gidx[g]]; }
static int xp_lower(int c) { return c >= 'A' && c <= 'Z' ? c + 32 : c; }
static int xp_cmp(char *a, char *b) {
    while (*a && *a == *b) { ++a; ++b; }
    return (*a & 255) - (*b & 255);
}
// the list's order: the program's functions, then each library's; in each,
// by name (then address) or by address
static int xp_before(struct xp *x, int a, int b, int byname) {
    int c;
    if (x->gmod[a] != x->gmod[b]) return x->gmod[a] < x->gmod[b];
    c = byname ? xp_cmp(xp_name(x, a), xp_name(x, b)) : 0;
    return c < 0 || (c == 0 && x->gidx[a] < x->gidx[b]);
}
static void xp_sort(struct xp *x, int *v, int n, int byname) {
    int i, j, t, gap;
    gap = n / 2;
    while (gap > 0) {
        i = gap;
        while (i < n) {
            t = v[i]; j = i;
            while (j >= gap && xp_before(x, t, v[j - gap], byname)) { v[j] = v[j - gap]; j = j - gap; }
            v[j] = t;
            ++i;
        }
        gap = gap / 2;
    }
}
// P in S, in either case
static int xp_has(char *s, char *p) {
    int i, j;
    if (!p[0]) return 1;
    i = 0;
    while (s[i]) {
        j = 0;
        while (p[j] && s[i + j] && xp_lower(s[i + j]) == xp_lower(p[j])) ++j;
        if (!p[j]) return 1;
        ++i;
    }
    return 0;
}
static void xp_filter(struct xp *x) {
    int i, n;
    n = 0; i = 0;
    while (i < x->nall) { if (xp_has(xp_name(x, x->lord[i]), x->filt)) { x->lvis[n] = x->lord[i]; ++n; } ++i; }
    x->nvis = n; x->ltop = 0; x->lfollow = 1;
}
static void xp_order(struct xp *x) {
    int i;
    i = 0; while (i < x->nall) { x->lord[i] = i; ++i; }
    if (x->byname) xp_sort(x, x->lord, x->nall, 1);
    xp_filter(x);
}
// the function named NM, in the modules' order: outside module AVOID
// first, then in it; -1 if none
static int xp_named(struct xp *x, char *nm, int avoid) {
    int g, pass;
    pass = 0;
    while (pass < 2) {
        g = 0;
        while (g < x->nall) {
            if ((pass == 0) == (x->gmod[g] != avoid) && ui_eq(xp_name(x, g), nm)) return g;
            ++g;
        }
        ++pass;
    }
    return 0 - 1;
}
static int xp_listed(struct xp *x, int g) {
    int k;
    k = 0;
    while (k < x->nvis) { if (x->lvis[k] == g) return k; ++k; }
    return 0 - 1;
}

// ---- the function shown ------------------------------------------------------------------------

static int xp_operand(int op) {
    return op <= O_ADJ || op == O_JSRI || op == O_JSRS || (op >= O_LDL && op <= O_IMMP) || op == O_STL;
}

// the row an offset is in, by binary search; -1 before the first
static int xm_row(struct xmod *m, int off) {
    int lo, hi, k, r;
    lo = 0; hi = m->nrow - 1; r = 0 - 1;
    while (lo <= hi) { k = (lo + hi) >> 1; if (m->roff[k] <= off) { r = k; lo = k + 1; } else hi = k - 1; }
    return r;
}
// the function an offset is in, by binary search (they are in address
// order, and do not overlap); -1 if none
static int xm_fn_at(struct xmod *m, int off) {
    int lo, hi, k;
    lo = 0; hi = m->nfn - 1;
    while (lo <= hi) {
        k = (lo + hi) >> 1;
        if (off < m->fstart[k]) hi = k - 1;
        else if (off >= m->fstart[k] + m->flen[k]) lo = k + 1;
        else return k;
    }
    return 0 - 1;
}

// decode function G, its labels, and its lines' bands
static void xp_decode(struct xp *x, int g) {
    int s, e, i, n, op, k, t, lo, hi, md, l, r, f, here;
    struct xmod *m;
    xp_unshow(x);
    x->cur = g; x->cm = m = xp_mod(x, g); f = x->gidx[g];
    x->top = 0; x->left = 0; x->sel = 0 - 1;
    s = m->fstart[f]; e = s + m->flen[f];
    if (e > m->ncode) e = m->ncode;
    n = e - s + 1;
    x->ioff = xp_ints(n); x->iop = xp_ints(n); x->iarg = xp_ints(n); x->ilab = xp_ints(n); x->irow = xp_ints(n);
    i = s; n = 0;
    while (i < e) {
        op = m->code[i];
        x->ioff[n] = i; x->iop[n] = op; x->ilab[n] = 0; x->irow[n] = xm_row(m, i);
        if (xp_operand(op) && i + 1 < e) { x->iarg[n] = m->code[i + 1]; i = i + 2; }
        else { x->iarg[n] = 0; if (xp_operand(op)) x->iop[n] = 0 - 1; i = i + 1; }   // an operand cut off: a word
        ++n;
    }
    x->nins = n;
    // branch targets inside the function are labels, L1 up in order
    k = 0;
    while (k < n) {
        op = x->iop[k];
        if ((op == O_JMP || op == O_BZ || op == O_BNZ) && m->ptype[x->ioff[k] + 1] == P_CODE) {
            t = m->pval[x->ioff[k] + 1];
            lo = 0; hi = n - 1;
            while (lo <= hi) { md = (lo + hi) >> 1; if (x->ioff[md] == t) { x->ilab[md] = 1; lo = hi + 1; } else if (x->ioff[md] < t) lo = md + 1; else hi = md - 1; }
        }
        ++k;
    }
    l = 0; k = 0;
    while (k < n) { if (x->ilab[k]) { ++l; x->ilab[k] = l; } ++k; }
    // which of the edited file's lines have code here, and their colours
    here = m == x->mods[0] ? x->here : 0 - 1;
    x->lmin = 0; x->lmax = 0 - 1;
    k = 0;
    while (here >= 0 && k < n) {
        r = x->irow[k];
        if (r >= 0 && m->rfile[r] == here && m->rline[r] > 0) {
            if (x->lmax < x->lmin) { x->lmin = x->lmax = m->rline[r]; }
            if (m->rline[r] < x->lmin) x->lmin = m->rline[r];
            if (m->rline[r] > x->lmax) x->lmax = m->rline[r];
        }
        ++k;
    }
    if (x->lmax >= x->lmin) {
        x->lband = xp_ints(x->lmax - x->lmin + 1);
        k = 0; while (k <= x->lmax - x->lmin) { x->lband[k] = 0 - 1; ++k; }
        k = 0;
        while (k < n) {
            r = x->irow[k];
            if (r >= 0 && m->rfile[r] == here && m->rline[r] > 0) x->lband[m->rline[r] - x->lmin] = bands[m->rline[r] % 8];
            ++k;
        }
    }
}

// one row of the listing (counted only, while there is nowhere to put it)
static int xp_row_add(struct xp *x, int n, int ins, int file, int line, int seg) {
    if (x->dins) { x->dins[n] = ins; x->dfile[n] = file; x->dline[n] = line; x->dseg[n] = seg; }
    return n + 1;
}
// ... and the rows of a source line, COLS wide (0: one row, scrolled across)
static int xp_src_rows(struct xp *x, int n, int file, int line, int len, int cols) {
    int k;
    if (cols <= 0 || len <= cols) return xp_row_add(x, n, 0 - 1, file, line, 0);
    k = 0;
    while (k * cols < len) { n = xp_row_add(x, n, 0 - 1, file, line, k); ++k; }
    return n;
}

// ---- which source lines go with a row ----
//
// A row names the line its statement starts on. The listing shows that
// line, the lines the statement goes on to, and some of the lines above
// it that have no code of their own: all of them in the function's head
// (its name to its first statement: the parameters, the brace, the
// locals), a few anywhere else, and past those the run of labels, braces
// and comments just above it -- so a case's label is over its code.

// the first character of line L that is not a space, or 0 (none, or no line)
static int xp_lead_c(struct xp *x, struct xmod *m, int i, int l) {
    int n, k;
    n = xp_line(x, m, i, l);
    k = 0;
    while (k < n && xo[k] == ' ') ++k;
    return k < n ? xo[k] & 255 : 0;
}
static int xp_idc(int c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'; }
// Line L has no code of its own and reads as part of what follows it: a
// blank line, a comment, a preprocessor line, a case's or a goto's label,
// or braces and else and do alone
static int xp_lead(struct xp *x, struct xmod *m, int i, int l) {
    int n, k, j;
    n = xp_line(x, m, i, l);
    if (n < 0) return 0;
    k = 0;
    while (k < n && xo[k] == ' ') ++k;
    if (k == n || xo[k] == '#' || (xo[k] == '/' && (xo[k + 1] == '/' || xo[k + 1] == '*')) || xo[k] == '*') return 1;
    // a label: a word, then a colon, and nothing after it but a comment
    j = k;
    while (j < n && xp_idc(xo[j] & 255)) ++j;
    if (j - k == 4 && !memcmp(xo + k, "case", 4)) {
        // case V: its value, to the colon (past a character's quotes)
        while (j < n && xo[j] != ':') { if (xo[j] == 39 && j + 2 < n) j = j + 2; ++j; }
    } else while (j > k && j < n && xo[j] == ' ') ++j;
    if (j > k && j < n && xo[j] == ':' && xo[j + 1] != ':') {
        ++j;
        while (j < n && xo[j] == ' ') ++j;
        if (j == n || xo[j] == '{' || (xo[j] == '/' && (xo[j + 1] == '/' || xo[j + 1] == '*'))) return 1;
    }
    // braces, else and do
    while (k < n) {
        if (xo[k] == '{' || xo[k] == '}' || xo[k] == ' ') ++k;
        else if (!memcmp(xo + k, "else", 4) && !xp_idc(xo[k + 4] & 255)) k = k + 4;
        else if (!memcmp(xo + k, "do", 2) && !xp_idc(xo[k + 2] & 255)) k = k + 2;
        else if (xo[k] == '/' && (xo[k + 1] == '/' || xo[k + 1] == '*')) k = n;
        else return 0;
    }
    return 1;
}
// Whether line L leaves its statement unfinished: a bracket still open
// (*DEPTH, carried from line to line, as *CMT carries a comment), an
// initializer's brace, or an operator or a comma at its end
static int xp_goes_on(struct xp *x, struct xmod *m, int i, int l, int *depth, int *cmt) {
    int n, k, c, q, last;
    n = xp_line(x, m, i, l);
    if (n < 0) return 0;
    k = 0; q = 0; last = 0;
    while (k < n) {
        c = xo[k] & 255;
        if (*cmt) { if (c == '*' && xo[k + 1] == '/') { *cmt = 0; ++k; } }
        else if (q) { if (c == 92) ++k; else if (c == q) q = 0; }
        else if (c == '/' && xo[k + 1] == '/') k = n;
        else if (c == '/' && xo[k + 1] == '*') { *cmt = 1; ++k; }
        else if (c == '"' || c == 39) { q = c; last = c; }
        else if (c == '(' || c == '[' || (c == '{' && (last == '=' || *depth > 0))) { *depth = *depth + 1; last = c; }
        else if (c == ')' || c == ']' || (c == '}' && *depth > 0)) { *depth = *depth - 1; last = c; }
        else if (c != ' ') last = c;
        ++k;
    }
    if (*depth != 0) return *depth > 0;
    return last == ',' || last == '=' || last == '+' || last == '-' || last == '*' || last == '/' || last == '%' ||
           last == '&' || last == '|' || last == '^' || last == '<' || last == '>' || last == '?' || last == '!' || last == 92;
}
// Line L of file I has a row of the function shown
static int xp_mapped(struct xp *x, int i, int l) {
    int k, r;
    struct xmod *m;
    m = x->cm;
    k = 0;
    while (k < x->nins) { r = x->irow[k]; if (r >= 0 && m->rfile[r] == i && m->rline[r] == l) return 1; ++k; }
    return 0;
}
// The last line of the statement that starts at line L of file I: the
// lines it goes on to, up to a preprocessor's, or past its brackets one
// with code of its own (an if's last line can hold its body)
static int xp_stmt_end(struct xp *x, struct xmod *m, int i, int l) {
    int e, depth, cmt;
    depth = 0; cmt = 0; e = l;
    if (!xp_goes_on(x, m, i, l, &depth, &cmt)) return l;
    while (e - l < XCONT) {
        if (xp_line(x, m, i, e + 1) < 0 || xp_lead_c(x, m, i, e + 1) == '#' || (depth <= 0 && xp_mapped(x, i, e + 1))) return e;
        ++e;
        if (!xp_goes_on(x, m, i, e, &depth, &cmt)) return e;
    }
    return e;
}

// The listing's rows, for source COLS wide (0 when it is not wrapped):
// each instruction, after the source lines of its row when that is a new
// one (above); blank lines are left out. Counted only while x->dins is 0.
static int xp_text(struct xp *x, int k, char *mn, char *d);
static int xp_lay(struct xp *x, int cols) {
    int f, k, r, l, lf, lr, ll, hi, a, e, n, len, fi, hd;
    struct xmod *m;
    m = x->cm; f = x->gidx[x->cur];
    n = 0; x->maxw = 0;
    // the file and line of the last row, the last line shown and the
    // furthest: the line before the function's, so that its own first
    // line is shown
    lf = m->ffile[f]; lr = ll = hi = m->fline[f] - 1;
    hd = 1;                                   // until a row past the function's own line
    k = 0;
    while (k < x->nins) {
        r = x->irow[k];
        if (r >= 0 && m->rline[r] > 0 && (m->rfile[r] != lf || m->rline[r] != lr)) {
            fi = m->rfile[r]; l = m->rline[r];
            // a line the statement before it went on to is shown already
            if (fi != lf || l <= lr || l > ll) {
                a = l;
                if (fi == lf && l > ll) {
                    if ((hd && l - ll <= XHEAD) || l - ll <= XGAP + 1) a = ll + 1;
                    else while (a - 1 > ll && l - a < XLEAD && xp_lead(x, m, fi, a - 1)) --a;
                    // not again what a loop's body showed before its condition came back up
                    if (a <= hi) a = hi < l ? hi + 1 : l;
                }
                if (fi == m->ffile[f] && l > m->fline[f]) hd = 0;
                e = xp_stmt_end(x, m, fi, l);
                while (a <= e) {
                    len = xp_line(x, m, fi, a);
                    if (a == l || (len > 0 && !xp_blank(xo, len))) {
                        n = xp_src_rows(x, n, fi, a, len, cols);
                        if (len > x->maxw) x->maxw = len;
                    }
                    ++a;
                }
                if (fi != lf || e > hi) hi = e;
                ll = e;
            }
            lf = fi; lr = l;
        }
        n = xp_row_add(x, n, k, r >= 0 ? m->rfile[r] : 0 - 1, r >= 0 ? m->rline[r] : 0, 0);
        ++k;
    }
    return n;
}
static void xp_layout(struct xp *x, int cols) {
    int k, n, w;
    char mn[8];
    if (x->dins) { free((char *)x->dins); free((char *)x->dfile); free((char *)x->dline); free((char *)x->dseg); }
    x->dins = 0;
    n = xp_lay(x, cols) + 1;                  // count them, then make them
    x->dins = xp_ints(n); x->dfile = xp_ints(n); x->dline = xp_ints(n); x->dseg = xp_ints(n);
    n = xp_lay(x, cols);
    x->nd = n;
    // the widest instruction, for the bar across: a label's room, the
    // mnemonic's, and its operand, which can be a long string
    k = 0;
    while (k < x->nins) {
        xp_text(x, k, mn, xb);
        w = 10 + ui_len(xb) + (x->ilab[k] ? 4 : 0);
        if (w > x->maxw) x->maxw = w;
        ++k;
    }
    x->laycols = cols > 0 ? cols : 0 - 1;
}

// Show function G; PUSH keeps the one shown before for Back
static void xp_show(struct xp *x, int g, int push) {
    int i;
    if (g < 0 || g >= x->nall) return;
    if (push && x->cur >= 0 && x->cur != g) {
        if (x->nhist == XHIST) { i = 1; while (i < XHIST) { x->hist[i - 1] = x->hist[i]; ++i; } --x->nhist; }
        x->hist[x->nhist] = x->cur; ++x->nhist;
    }
    if (g != x->cur || !x->ioff) xp_decode(x, g);
    x->lfollow = 1;
}
static void xp_back(struct xp *x) {
    if (!x->nhist) return;
    --x->nhist;
    xp_show(x, x->hist[x->nhist], 0);
}

// the libraries module M loads, as the loader finds them: a static global
// __c4_needed for each, whose value is the data offset of its path
static void xp_needs(struct xp *x, struct xmod *m) {
    int i, k, j, n;
    char path[128];
    struct xmod *l;
    i = 0;
    while (i < m->nsym && x->nmod < XMODS) {
        if (m->scls[i] == S_GLO && ui_eq(m->sname[i], "__c4_needed") && m->sval[i] >= 0 && m->sval[i] < m->ndata) {
            k = m->sval[i]; n = 0;
            while (k + n < m->ndata && m->data[k + n] && n < 127) { path[n] = m->data[k + n]; ++n; }
            path[n] = 0;
            j = 0;
            while (j < x->nmod && !ui_eq(x->mods[j]->path, path)) ++j;
            if (j == x->nmod && (l = xm_read(path, x->note))) { x->mods[x->nmod] = l; ++x->nmod; }
        }
        ++i;
    }
}

// The object at PATH as module 0, the libraries it loads after it, every
// function numbered, and the list; shows KEEP (by name) if it is there,
// else a compiled file's main, or the first function of its own (not
// one of the compiler's, as "<udiv>"). 0 if it cannot be read.
static int xp_open(struct xp *x, char *path, char *keep) {
    struct xmod *m;
    int i, j, k, g, *v;
    x->note[0] = 0;
    if (!(m = xm_read(path, x->msg))) return 0;
    x->mods[0] = m; x->nmod = 1;
    // the file edited, by its path, else by its name
    i = 0;
    while (!x->objmode && i < m->nfile && x->here < 0) { if (ui_eq(m->fpath[i], x->path)) x->here = i; ++i; }
    i = 0;
    while (!x->objmode && i < m->nfile && x->here < 0) { if (ui_eq(ui_base(m->fpath[i]), ui_base(x->path))) x->here = i; ++i; }
    i = 0;
    while (i < x->nmod) { xp_needs(x, x->mods[i]); ++i; }
    x->nall = 0; i = 0;
    while (i < x->nmod) { x->mods[i]->fn0 = x->nall; x->nall = x->nall + x->mods[i]->nfn; ++i; }
    x->gmod = xp_ints(x->nall); x->gidx = xp_ints(x->nall); x->gdup = xp_zeros(x->nall);
    g = 0; i = 0;
    while (i < x->nmod) { j = 0; while (j < x->mods[i]->nfn) { x->gmod[g] = i; x->gidx[g] = j; ++g; ++j; } ++i; }
    // names a module has more than once: by name, side by side
    v = xp_ints(x->nall);
    k = 0; while (k < x->nall) { v[k] = k; ++k; }
    xp_sort(x, v, x->nall, 1);
    k = 1;
    while (k < x->nall) {
        if (x->gmod[v[k]] == x->gmod[v[k - 1]] && ui_eq(xp_name(x, v[k]), xp_name(x, v[k - 1]))) { x->gdup[v[k]] = 1; x->gdup[v[k - 1]] = 1; }
        ++k;
    }
    free((char *)v);
    x->lord = xp_ints(x->nall); x->lvis = xp_ints(x->nall);
    x->ok = 1;
    xp_order(x);
    g = 0 - 1;
    if (keep && keep[0]) g = xp_named(x, keep, 0 - 1);
    if (g < 0 && x->objmode) g = xp_named(x, "main", 0 - 1);
    k = 0;
    while (g < 0 && x->objmode && k < x->nvis) { if (xp_name(x, x->lvis[k])[0] != '<') g = x->lvis[k]; ++k; }
    if (g < 0 && x->objmode && x->nvis) g = x->lvis[0];
    if (g >= 0) xp_show(x, g, 0);
    return 1;
}

int xp_load(int *xi, char *path, char *dir) {
    struct xp *x;
    x = X(xi);
    xp_stop(x);
    xp_drop(x);
    x->objmode = 1; x->byname = 1; x->failed = 0; x->msg[0] = 0; x->note[0] = 0;
    x->filt[0] = 0; x->filtc = 0;
    ui_ncpy(x->path, path, 128);
    ui_ncpy(x->dir, dir, 128);
    return xp_open(x, path, 0);
}

// The function for the cursor's LINE in the file edited: the one with
// code from that line, else the last one this file starts at or before it
static int xp_fn_for(struct xp *x, int line) {
    int i, f, best;
    struct xmod *m;
    m = x->mods[0];
    i = 0;
    while (i < m->nrow) {
        if (m->rfile[i] == x->here && m->rline[i] == line && (f = xm_fn_at(m, m->roff[i])) >= 0) return f;
        ++i;
    }
    best = 0 - 1;
    i = 0;
    while (i < m->nfn) {
        if (m->ffile[i] == x->here && m->fline[i] <= line && (best < 0 || m->fline[i] >= m->fline[best])) best = i;
        ++i;
    }
    return best;
}

// The band beside source LINE (1-based) of the function shown, or -1
int xp_band(int *xi, int line) {
    struct xp *x;
    x = X(xi);
    if (!x->ok || !x->lband || line < x->lmin || line > x->lmax) return 0 - 1;
    return x->lband[line - x->lmin];
}

// the first row of line LINE of the file edited, or -1
static int xp_row_of(struct xp *x, int line) {
    int k;
    k = 0;
    while (k < x->nd) { if (x->cm == x->mods[0] && x->dfile[k] == x->here && x->dline[k] == line) return k; ++k; }
    return 0 - 1;
}

// The editor's cursor on LINE (1-based), when it moves: its function, its
// line lit, and the view on it. edit.c calls this as it draws.
void xp_cursor(int *xi, int line) {
    struct xp *x;
    int f, k;
    x = X(xi);
    if (!x->ok || x->objmode || (line == x->lastline && x->cur >= 0)) return;
    f = xp_fn_for(x, line);
    // before every function: this file's first, if nothing is shown yet
    k = 0;
    while (f < 0 && x->cur < 0 && k < x->mods[0]->nfn) { if (x->mods[0]->ffile[k] == x->here) f = k; ++k; }
    if (f < 0 && x->cur < 0 && x->mods[0]->nfn) f = 0;
    if (f >= 0) xp_show(x, f, 0);
    x->hmod = 0; x->hfile = x->here; x->hline = line;
    x->lastline = line;
    x->sel = 0 - 2;                           // the view goes to the line when it is laid out
}

// The line asked for in the editor (after xp_mouse or xp_key said 2): its
// file into PATH (128 bytes), and its number
int xp_goto(int *xi, char *path) {
    struct xp *x;
    x = X(xi);
    ui_ncpy(path, x->gopath, 128);
    return x->goline;
}

// ---- an operand, as libjs/c4r.js's insnText says it --------------------------------------------

static char *xm_symname(struct xmod *m, int id) {
    int i;
    i = 0;
    while (i < m->nsym) { if (m->sid[i] == id) return m->sname[i]; ++i; }
    return 0;
}
// the function starting at OFF: the symbols', then the map's; 0 if none
static char *xm_fn_named(struct xmod *m, int off) {
    int i;
    i = 0;
    while (i < m->nsym) { if (m->scls[i] == S_FUN && !(m->sattr[i] & S_EXTERN) && m->sval[i] == off) return m->sname[i]; ++i; }
    i = xm_fn_at(m, off);
    if (i >= 0 && m->fstart[i] == off) return m->fname[i];
    return 0;
}
// the global a data offset is in, or -1
static int xm_global(struct xmod *m, int off) {
    int i, g, next;
    g = 0 - 1;
    i = 0;
    while (i < m->nsym) {
        if (m->scls[i] == S_GLO && !(m->sattr[i] & S_EXTERN) && m->sval[i] <= off && (g < 0 || m->sval[i] > m->sval[g])) g = i;
        ++i;
    }
    if (g < 0) return g;
    next = m->memsz;
    i = 0;
    while (i < m->nsym) {
        if (m->scls[i] == S_GLO && !(m->sattr[i] & S_EXTERN) && m->sval[i] > m->sval[g] && m->sval[i] < next) next = m->sval[i];
        ++i;
    }
    if (next <= m->sval[g]) next = m->sval[g] + 1;
    return off < next ? g : 0 - 1;
}
// the printable C string at a data offset: its length (200 at most), or
// -1. The data's end ends one too: c4lc leaves the last literal's NUL to
// the zeroed memory after it.
static int xm_cstr(struct xmod *m, int off) {
    int i, c;
    if (off < 0 || off >= m->ndata) return 0 - 1;
    i = off;
    while (i < m->ndata) {
        c = m->data[i] & 255;
        if (c == 0) return i - off;
        if ((c < 32 && c != 9 && c != 10 && c != 13 && c != 27) || c > 126) return 0 - 1;
        ++i;
        if (i - off == 200) return 200;
    }
    return i - off;
}
static void xp_hex(char *d, int v) {
    char t[12];
    int n;
    ui_cat(d, "0x");
    n = 0;
    if (v == 0) { t[0] = '0'; n = 1; }
    while (v != 0 && n < 8) { t[n] = hexd[v & 15]; v = (v >> 4) & 0xfffffff; ++n; }
    d = d + ui_len(d);
    while (n > 0) { --n; *d = t[n]; ++d; }
    *d = 0;
}
// a string literal, quoted and escaped as JSON.stringify does it
static void xm_quote(struct xmod *m, char *d, int off, int n, int max) {
    int i, c, k;
    k = ui_len(d);
    d[k] = '"'; ++k;
    i = 0;
    while (i < n && k < max - 8) {
        c = m->data[off + i] & 255;
        if (c == '"' || c == 92) { d[k] = 92; d[k + 1] = c; k = k + 2; }
        else if (c == 10) { d[k] = 92; d[k + 1] = 'n'; k = k + 2; }
        else if (c == 13) { d[k] = 92; d[k + 1] = 'r'; k = k + 2; }
        else if (c == 9) { d[k] = 92; d[k + 1] = 't'; k = k + 2; }
        else if (c == 27) { d[k] = 0; ui_cat(d, "\\u001b"); k = k + 6; }
        else { d[k] = c; ++k; }
        ++i;
    }
    d[k] = '"'; d[k + 1] = 0;
}

// instruction K's mnemonic into M and its operand into D; the operand's
// colour
static int xp_text(struct xp *x, int k, char *mn, char *d) {
    int op, a, w, t, v, f, g, n, j;
    char *nm;
    struct xmod *m;
    m = x->cm;
    op = x->iop[k]; a = x->iarg[k]; w = x->ioff[k] + 1;
    d[0] = 0;
    if (op < 0) { ui_cpy(mn, ".word"); ui_num(d, m->code[x->ioff[k]]); return XC_NUM; }
    if (op < O_N) { memcpy(mn, opnames + op * 5, 4); mn[4] = 0; j = 3; while (j > 0 && mn[j] == ' ') { mn[j] = 0; --j; } }
    else { ui_cpy(mn, "?"); ui_num(mn + 1, op); }
    if (!xp_operand(op)) return XC_TEXT;
    t = m->ptype[w]; v = m->pval[w];
    if (t == P_CODE) {
        f = xm_fn_at(m, v);
        if ((op == O_JMP || op == O_BZ || op == O_BNZ) && f == x->gidx[x->cur]) {
            j = 0;
            while (j < x->nins) { if (x->ioff[j] == v && x->ilab[j]) { ui_cpy(d, "L"); ui_num(d + 1, x->ilab[j]); return XC_PRE; } ++j; }
            xp_hex(d, v); return XC_PRE;
        }
        if ((nm = xm_fn_named(m, v))) { if (op != O_JSR) ui_cpy(d, "&"); ui_cat(d, nm); return XC_TYPE; }
        if (f >= 0) { ui_cpy(d, m->fname[f]); ui_cat(d, "+"); ui_num(d + ui_len(d), v - m->fstart[f]); return XC_TYPE; }
        xp_hex(d, v); return XC_NUM;
    }
    if (t == P_DATA) {
        // a switch's table of addresses, which c4lc puts after its unit's
        // globals with no name of its own: its IMM is a JMPA's, a few on
        j = k + 1;
        while (j < x->nins && j <= k + 3 && x->iop[j] != O_JMPA) ++j;
        if (op == O_IMM && j < x->nins && j <= k + 3) { ui_cpy(d, "jump table, data+"); ui_num(d + ui_len(d), v); return XC_NUM; }
        g = xm_global(m, v);
        n = xm_cstr(m, v);
        // a unit's literals follow its globals with no symbol of their own
        if (g >= 0 && n >= 2 && v - m->sval[g] >= m->W && v > 0 && m->data[v - 1] == 0) g = 0 - 1;
        if (g >= 0) {
            ui_cpy(d, op == O_JSRI ? "*" : "&");
            ui_cat(d, m->sname[g]);
            if (v != m->sval[g]) { ui_cat(d, "+"); ui_num(d + ui_len(d), v - m->sval[g]); }
            return XC_TYPE;
        }
        if (n >= 0) {
            if (n > 200) n = 200;
            xm_quote(m, d, v, n, 240);
            if (n == 200) ui_cat(d, "...");
            return XC_STR;
        }
        ui_cpy(d, "data+"); ui_num(d + 5, v); return XC_NUM;
    }
    if (t > 0) {
        nm = xm_symname(m, t);
        if (nm) ui_cpy(d, nm); else { ui_cpy(d, "symbol "); ui_num(d + 7, t); }
        return XC_TYPE;
    }
    if (op == O_LEA || op == O_LDL || op == O_STL || op == O_PSHL || op == O_LEAP || op == O_JSRS) {
        ui_cpy(d, "[bp");
        if (a >= 0) ui_cat(d, "+");
        ui_num(d + ui_len(d), a);
        ui_cat(d, "]");
        return XC_NUM;
    }
    // a plain number, INT_MIN too (ui_num's): only a patch makes an
    // operand an address
    ui_num(d, a);
    return XC_NUM;
}

// ---- drawing ---------------------------------------------------------------------------------

// the function list's width in a tab CW wide
static int xp_lw(int cw) { int w; w = cw / 4; if (w < 120) w = 120; if (w > 220) w = 220; return w; }
// how many hex digits the code's offsets take, four at least
static int xp_ow(struct xp *x) { int n, v; n = 1; v = x->cm ? x->cm->ncode >> 4 : 0; while (v) { ++n; v = v >> 4; } return n < 4 ? 4 : n; }
// "file:line" of map file F of module M
static void xp_where_s(struct xmod *m, char *d, int f, int l) {
    ui_cpy(d, m && f >= 0 && f < m->nfile ? ui_base(m->fpath[f]) : "?");
    ui_cat(d, ":");
    ui_num(d + ui_len(d), l);
}
// the code area's buttons: Wrap, Back, and -O for a compile
static int xp_bw(struct xp *x) { return x->objmode ? 76 : 116; }

// the list: the filter, its order, the names
static void xp_draw_list(struct xp *x, int ox, int oy, int w, int h, int *cols, int focused) {
    int rows, i, k, g, y, c, n;
    struct xmod *m;
    d_rect(ox, oy, w, XHDR, C_FACE);
    ui_field(ox, oy, w - 34, x->filt, x->filtc, focused);
    if (!x->filt[0] && x->ok) {
        ui_num(xb, x->nvis); ui_cat(xb, x->nvis == 1 ? " function" : " functions");
        d_clip(ox + 2, oy + 2, w - 38, XHDR - 4);
        d_text(ox + 8, oy + 5, C_SHADOW, F_SANS, xb);
        d_clip_end();
    }
    ui_button(ox + w - 32, oy + 1, 30, XHDR - 2, "A-Z", x->byname, 0);
    rows = (h - XHDR - 4) / XCH;
    if (rows < 1) rows = 1;
    x->lrows = rows;
    if (x->lfollow) {
        k = xp_listed(x, x->cur);
        if (k >= 0 && k < x->ltop) x->ltop = k;
        if (k >= 0 && k >= x->ltop + rows) x->ltop = k - rows + 1;
        x->lfollow = 0;
    }
    if (x->ltop > x->nvis - rows) x->ltop = x->nvis - rows;
    if (x->ltop < 0) x->ltop = 0;
    y = oy + XHDR;
    d_rect(ox, y, w - 17, h - XHDR, cols[XC_BG]);
    d_clip(ox, y, w - 17, h - XHDR);
    i = 0;
    while (x->ok && i < rows && x->ltop + i < x->nvis) {
        g = x->lvis[x->ltop + i];
        m = xp_mod(x, g);
        // a library's in a colour of its own; the file edited's own, and the rest dimmer
        c = x->gmod[g] > 0 ? cols[XC_TYPE] : !x->objmode && m->ffile[x->gidx[g]] != x->here ? cols[XC_COM] : cols[XC_TEXT];
        if (g == x->cur) { d_rect(ox, y + 2 + i * XCH, w - 17, XCH, cols[XC_SEL]); c = cols[XC_KW]; }
        n = ui_len(xp_name(x, g));
        d_textn(ox + 4, y + 2 + i * XCH, c, XFONT, XFACE, XCW, xp_name(x, g), n);
        // a name the module has more than once: the unit each copy came with
        k = m->funit[x->gidx[g]];
        if (x->gdup[g] && k >= 0) d_text(ox + 4 + (n + 1) * XCW, y + 2 + i * XCH, cols[XC_COM], F_SANS, ui_base(m->fpath[k]));
        ++i;
    }
    if (x->ok && !x->nvis) d_text(ox + 4, y + 4, cols[XC_COM], F_SANS, "None by that name");
    d_clip_end();
    ui_scrollbar(ox + w - 17, y, h - XHDR, x->nvis, rows, x->ltop);
}

// the code: its header, then the listing
static void xp_draw_code(struct xp *x, int ox, int oy, int cw, int ch, int *cols) {
    char mn[8];
    int rows, y, k, j, c, i, sx, n, ow, c1, cm, ry, lw, bw, hot, hb, lh, cols0, f, a;
    struct xmod *m;
    m = x->cm;
    // the header: the function, where it is, Wrap, Back and -O
    bw = xp_bw(x);
    d_rect(ox, oy, cw, XHDR, C_FACE);
    d_bevel(ox, oy, cw, XHDR, B_RAISED);
    ui_cpy(xb, "Code");
    if (x->ok && x->cur >= 0) {
        f = x->gidx[x->cur];
        ui_cpy(xb, m->fname[f]);
        ui_cat(xb, " ("); ui_num(xb + ui_len(xb), m->flen[f]); ui_cat(xb, " words");
        if (m->ffile[f] >= 0 && m->fline[f] > 0) { ui_cat(xb, ", "); xp_where_s(m, xb + ui_len(xb), m->ffile[f], m->fline[f]); }
        else if (m->funit[f] >= 0) { ui_cat(xb, ", with "); ui_cat(xb, ui_base(m->fpath[m->funit[f]])); }
        if (x->gmod[x->cur] > 0) { ui_cat(xb, ", in "); ui_cat(xb, ui_base(m->path)); }
        ui_cat(xb, ")");
    }
    d_clip(ox, oy, cw - bw - 4, XHDR);
    d_text(ox + 6, oy + 5, C_DARK, F_SANS, xb);
    d_clip_end();
    ui_button(ox + cw - bw, oy + 2, 44, XHDR - 4, "Wrap", x->wrap, 0);
    ui_button(ox + cw - bw + 48, oy + 2, 26, XHDR - 4, "<", 0, 0);
    if (!x->objmode) ui_button(ox + cw - 40, oy + 2, 36, XHDR - 4, "-O", x->opt, 0);

    // the listing, laid out for its width
    lw = cw - 17;
    ow = xp_ow(x);
    c1 = ow + 3;                              // labels, and the source's text
    cols0 = (lw - 6) / XCW - c1;
    if (cols0 < 8) cols0 = 8;
    x->cols = (lw - 6) / XCW;
    if (x->ok && x->cur >= 0 && x->laycols != (x->wrap ? cols0 : 0 - 1)) {
        // laid out again: the view stays on the instruction at its top
        k = x->top; a = 0 - 1;
        while (x->dins && k < x->nd && a < 0) { if (x->dins[k] >= 0) a = x->dins[k]; ++k; }
        xp_layout(x, x->wrap ? cols0 : 0);
        if (a >= 0) { k = 0; while (k < x->nd && x->dins[k] != a) ++k; x->top = k; }
    }
    hb = !x->wrap;
    lh = ch - XHDR - (hb ? 16 : 0);
    rows = (lh - 4) / XCH;
    if (rows < 1) rows = 1;
    x->rows = rows;
    if (x->sel == 0 - 2) {
        // the cursor's line, from xp_cursor: into view
        x->sel = 0 - 1;
        k = xp_row_of(x, x->hline);
        if (k >= 0 && (k < x->top || k >= x->top + rows)) x->top = k - rows / 3;
    }
    if (x->top > x->nd - rows) x->top = x->nd - rows;
    if (x->top < 0) x->top = 0;
    if (x->left > x->maxw + c1 + 2 - x->cols) x->left = x->maxw + c1 + 2 - x->cols;
    if (x->left < 0 || x->wrap) x->left = 0;
    y = oy + XHDR;
    d_rect(ox, y, lw, lh, cols[XC_BG]);
    sx = ox + 6 - x->left * XCW;
    d_clip(ox, y, lw, lh);
    k = x->top; i = 0;
    while (x->ok && x->cur >= 0 && k < x->nd && i < rows) {
        ry = y + 2 + i * XCH;
        hot = x->dline[k] > 0 && x->gmod[x->cur] == x->hmod && x->dfile[k] == x->hfile && x->dline[k] == x->hline;
        if (x->dins[k] < 0) {
            // a line of source: its number where the offsets are, its text where the labels are
            d_rect(ox, ry, lw, XCH, hot ? cols[XC_SEL] : cols[XC_GUT]);
            d_rect(ox + 1, ry, 3, XCH, bands[x->dline[k] % 8]);
            if (x->dseg[k] == 0) {
                ui_num(xb, x->dline[k]);
                n = ui_len(xb);
                d_textn(sx + (ow + 1 - n) * XCW, ry, cols[XC_COM], XFONT, XFACE, XCW, xb, n);
            }
            n = xp_line(x, m, x->dfile[k], x->dline[k]);
            if (n >= 0) {
                // a wrapped line's piece, or the whole line scrolled across
                a = x->wrap && x->laycols > 0 ? x->dseg[k] * x->laycols : 0;
                n = n - a;
                if (x->wrap && x->laycols > 0 && n > x->laycols) n = x->laycols;
                if (n > 0) d_textn(sx + c1 * XCW, ry, cols[XC_TEXT], XFONT, XFACE, XCW, xo + a, n);
            }
            else { xp_where_s(m, xb, x->dfile[k], x->dline[k]); d_textn(sx + c1 * XCW, ry, cols[XC_COM], XFONT, XFACE, XCW, xb, ui_len(xb)); }
        } else {
            // an instruction: its offset (in hex), a label, the mnemonic and its operand
            j = x->dins[k];
            if (hot) d_rect(ox, ry, lw, XCH, cols[XC_SEL]);
            if (x->dline[k] > 0) d_rect(ox + 1, ry, 3, XCH, bands[x->dline[k] % 8]);
            xb[0] = 0;
            xp_hex(xb, x->ioff[j]);
            n = ui_len(xb + 2);
            d_textn(sx + (ow + 1 - n) * XCW, ry, cols[XC_COM], XFONT, XFACE, XCW, xb + 2, n);
            cm = c1 + 5;
            if (x->ilab[j]) {
                ui_cpy(xb, "L"); ui_num(xb + 1, x->ilab[j]); ui_cat(xb, ":");
                d_textn(sx + c1 * XCW, ry, cols[XC_PRE], XFONT, XFACE, XCW, xb, ui_len(xb));
                if (c1 + ui_len(xb) + 1 > cm) cm = c1 + ui_len(xb) + 1;
            }
            c = xp_text(x, j, mn, xb);
            d_textn(sx + cm * XCW, ry, cols[XC_KW], XFONT, XFACE, XCW, mn, ui_len(mn));
            if (xb[0]) d_textn(sx + (cm + 5) * XCW, ry, cols[c], XFONT, XFACE, XCW, xb, ui_len(xb));
        }
        if (k == x->sel) d_recto(ox, ry, lw, XCH, cols[XC_KW]);
        ++k; ++i;
    }
    d_clip_end();
    if (x->ok && x->cur < 0) d_text(ox + 6, y + 4, cols[XC_COM], F_SANS, "Pick a function from the list");
    ui_scrollbar(ox + cw - 17, y, lh, x->nd, rows, x->top);
    if (hb) {
        ui_hscrollbar(ox, y + lh, cw - 17, x->maxw + c1 + 2, x->cols, x->left);
        d_rect(ox + cw - 17, y + lh, 17, 16, C_FACE);
    }
    // a failed compile's last words, over the listing
    if (x->failed && !x->busy) {
        if (x->errn > 0) d_textn(ox + 6, y + 4, cols[XC_STR], XFONT, XFACE, XCW, x->err0, ui_len(x->err0));
        if (x->errn > 1) d_textn(ox + 6, y + 4 + XCH, cols[XC_STR], XFONT, XFACE, XCW, x->err1, ui_len(x->err1));
    }
}

// The tab at OX, OY, CW by CH: the list, the code, and a footer across
// both; for a text MODIFIED since it was saved, COLS the IDE's scheme
void xp_draw(int *xi, int ox, int oy, int cw, int ch, int *cols, int modified, int focused) {
    struct xp *x;
    char mn[8];
    int lw, h, y, k, j, f, i;
    struct xmod *m;
    x = X(xi);
    lw = xp_lw(cw);
    h = ch - XFOOT;
    xp_draw_list(x, ox, oy, lw, h, cols, focused);
    d_rect(ox + lw, oy, 2, h, C_SHADOW);
    xp_draw_code(x, ox + lw + 2, oy, cw - lw - 2, h, cols);

    // the footer: what is going on, the row picked, or what is shown
    y = oy + h;
    d_rect(ox, y, cw, XFOOT, C_FACE);
    d_bevel(ox, y, cw, XFOOT, B_SUNKEN);
    xb[0] = 0;
    m = x->cm;
    f = x->ok && x->cur >= 0 ? m->ffile[x->gidx[x->cur]] : 0 - 1;
    if (f >= 0) xp_source(x, m, f);
    if (x->busy || !x->ok) ui_cpy(xb, x->msg[0] ? x->msg : "Save the file, and the code it compiles to is shown here");
    else if (x->failed) ui_cpy(xb, x->msg);
    else if (x->note[0]) ui_cpy(xb, x->note);
    else if (x->sel >= 0 && x->sel < x->nd && x->dline[x->sel] > 0) {
        k = x->sel;
        xp_where_s(m, xb, x->dfile[k], x->dline[k]);
        if ((j = x->dins[k]) >= 0) { ui_cat(xb, "  "); xp_text(x, j, mn, xo); ui_cat(xb, mn); ui_cat(xb, " "); ui_ncat(xb, xo, 300); }
        else if (x->dfile[k] >= 0 && m->sst[x->dfile[k]] > 0) { ui_cat(xb, "  "); ui_ncat(xb, m->spath[x->dfile[k]], 300); }
    }
    else if (modified && !x->objmode) ui_cpy(xb, "Changed since it was compiled: save to see the new code");
    else if (f >= 0 && m->sst[f] < 0 && !xm_own(m, f)) { ui_cpy(xb, "No source on this disk for "); ui_ncat(xb, m->fpath[f], 300); }
    else if (f >= 0 && m->sst[f] == 2) { ui_ncpy(xb, m->spath[f], 200); ui_cat(xb, " has changed since this was compiled"); }
    else if (x->objmode) {
        m = x->mods[0];
        ui_cpy(xb, ui_base(x->path)); ui_cat(xb, ": ");
        ui_num(xb + ui_len(xb), m->nfn); ui_cat(xb, m->nfn == 1 ? " function, " : " functions, ");
        ui_num_commas(xb + ui_len(xb), m->ncode); ui_cat(xb, " words of code, ");
        if (m->nrow) { ui_cat(xb, "a map of "); ui_num(xb + ui_len(xb), m->nfile); ui_cat(xb, m->nfile == 1 ? " file" : " files"); }
        else ui_cat(xb, "no source map");
        i = 1;
        while (i < x->nmod) { ui_cat(xb, i == 1 ? "; loads " : ", "); ui_ncat(xb, ui_base(x->mods[i]->path), 300); ++i; }
    }
    else if (x->here < 0) ui_cpy(xb, "The map does not name this file");
    else ui_cpy(xb, x->opt ? "Compiled with -g -O" : "Compiled with -g");
    d_clip(ox, y, cw, XFOOT);
    d_text(ox + 4, y + 3, C_DARK, F_SANS, xb);
    d_clip_end();
}

// ---- the mouse and the keys -------------------------------------------------------------------

// Row K followed: a call (or a function's address) goes to the callee, in
// this tab, in a library if that is where it is; anything else with a
// line, to the line, in the editor (2)
static int xp_follow(struct xp *x, int k) {
    int j, t, v, f, d, g;
    char *nm;
    struct xmod *m;
    m = x->cm;
    j = x->dins[k];
    if (j >= 0 && x->iop[j] >= 0 && xp_operand(x->iop[j])) {
        t = m->ptype[x->ioff[j] + 1]; v = m->pval[x->ioff[j] + 1];
        g = 0 - 1;
        if (t == P_CODE) { f = xm_fn_at(m, v); if (f >= 0 && m->fstart[f] == v) g = m->fn0 + f; }
        else if (t > 0 && (nm = xm_symname(m, t))) {
            // an extern: another module's, the libraries' first
            g = xp_named(x, nm, x->gmod[x->cur]);
            if (g < 0) { ui_cpy(x->note, nm); ui_cat(x->note, " is not in this file or the libraries it loads: it is linked in from elsewhere"); return 1; }
        }
        if (g >= 0 && g != x->cur) { xp_show(x, g, 1); return 1; }
    }
    d = x->dfile[k];
    if (x->dline[k] <= 0 || d < 0) return 1;
    xp_source(x, m, d);
    if (m->sst[d] <= 0) { ui_cpy(x->note, "No source on this disk for "); ui_ncat(x->note, m->fpath[d], 150); return 1; }
    ui_ncpy(x->gopath, m->spath[d], 128);
    x->goline = x->dline[k] + m->soff[d];
    if (m == x->mods[0] && d == x->here) x->lastline = x->goline;   // the editor's cursor is going there: nothing to follow
    return 2;
}

static int xp_mouse_list(struct xp *x, int ev, int px, int py, int w, int h) {
    int t, k;
    if (py < XHDR) {
        if (ev != E_DOWN) return 0;
        if (ui_hit(px, py, w - 32, 1, 30, XHDR - 2)) { x->byname = !x->byname; if (x->ok) xp_order(x); return 1; }
        if (px < w - 34) x->filtc = ui_field_hit(px, 0, w - 34, x->filt, x->filtc);
        return 1;
    }
    if (px >= w - 17) {
        t = ui_scroll_click(px, py, w - 17, XHDR, h - XHDR, x->nvis, x->lrows, x->ltop);
        if (t >= 0) x->ltop = t;
        return 1;
    }
    k = x->ltop + (py - XHDR - 2) / XCH;
    if (x->ok && k >= 0 && k < x->nvis) xp_show(x, x->lvis[k], 1);
    return 1;
}

static int xp_mouse_code(struct xp *x, int ev, int px, int py, int cw, int ch) {
    int t, k, bw, lh;
    lh = ch - XHDR - (x->wrap ? 0 : 16);
    if (py < XHDR) {
        if (ev != E_DOWN) return 0;
        bw = xp_bw(x);
        if (ui_hit(px, py, cw - bw, 2, 44, XHDR - 4)) { x->wrap = !x->wrap; x->left = 0; return 1; }
        if (ui_hit(px, py, cw - bw + 48, 2, 26, XHDR - 4)) { xp_back(x); return 1; }
        if (!x->objmode && ui_hit(px, py, cw - 40, 2, 36, XHDR - 4)) {
            x->opt = !x->opt;
            if (x->path[0]) xp_compile((int *)x, x->path, x->dir);
            return 0 - 1;
        }
        return 0;
    }
    if (px >= cw - 17) {
        t = ui_scroll_click(px, py, cw - 17, XHDR, lh, x->nd, x->rows, x->top);
        if (t >= 0) x->top = t;
        return 1;
    }
    if (py >= XHDR + lh) {
        t = ui_hscroll_click(px, py, 0, XHDR + lh, cw - 17, x->maxw + xp_ow(x) + 5, x->cols, x->left);
        if (t >= 0) x->left = t;
        return 1;
    }
    if (!x->ok || x->cur < 0) return 0;
    k = x->top + (py - XHDR - 2) / XCH;
    if (k < 0 || k >= x->nd) return 0;
    x->sel = k;
    if (x->dline[k] > 0) { x->hmod = x->gmod[x->cur]; x->hfile = x->dfile[k]; x->hline = x->dline[k]; }
    if (ev == E_DBL) return xp_follow(x, k);
    return 1;
}

// A mouse event at PX, PY in the tab, CW by CH (a wheel's PY is how far,
// and PX where): 1 if it did something, 0 if not, 2 for a line to go to
// in the editor (xp_goto), -1 when -O was turned on or off (and it
// compiles again), -2 while a bar is dragged
int xp_mouse(int *xi, int ev, int px, int py, int cw, int ch) {
    struct xp *x;
    int lw, h, t, ccw, lh;
    x = X(xi);
    lw = xp_lw(cw);
    h = ch - XFOOT;
    ccw = cw - lw - 2;                        // the code's width, right of the list
    lh = h - XHDR - (x->wrap ? 0 : 16);
    x->note[0] = 0;
    if (ev == E_WHEEL) { if (px < lw) x->ltop = x->ltop + py * 3; else x->top = x->top + py * 3; return 1; }
    if (ev == E_MOVE) {
        // a thumb being dragged, named by where its bar is, as the click named it
        t = ui_scroll_drag(lw - 17, XHDR, py);
        if (t >= 0) { x->ltop = t; return 0 - 2; }
        t = ui_scroll_drag(ccw - 17, XHDR, py);
        if (t >= 0) { x->top = t; return 0 - 2; }
        t = ui_scroll_drag(0, XHDR + lh, px - lw - 2);
        if (t >= 0) { x->left = t; return 0 - 2; }
        return 0;
    }
    if ((ev != E_DOWN && ev != E_DBL) || py >= h) return 0;
    if (px < lw) return xp_mouse_list(x, ev, px, py, lw, h);
    if (px < lw + 2) return 0;
    return xp_mouse_code(x, ev, px - lw - 2, py, ccw, h);
}

// A key: typing finds a function by name (the first the filter keeps is
// shown), Up and Down go through the list, PgUp and PgDn scroll the
// code, Enter follows the row picked, Backspace (with nothing typed) or
// Alt+Left goes back. 1 if it was used, 2 for a line to go to in the
// editor; Esc with nothing typed is not used (edit.c goes back to the
// text).
int xp_key(int *xi, int code, int ch, int mods) {
    struct xp *x;
    int k;
    x = X(xi);
    x->note[0] = 0;
    if ((mods & M_ALT) && code == KEY_LEFT) { xp_back(x); return 1; }
    if (code == KEY_UP || code == KEY_DOWN) {
        k = xp_listed(x, x->cur);
        if (k < 0) k = code == KEY_DOWN ? 0 - 1 : x->nvis;
        k = code == KEY_DOWN ? k + 1 : k - 1;
        if (k >= 0 && k < x->nvis) xp_show(x, x->lvis[k], 0);
        return 1;
    }
    if (code == KEY_PGUP) { x->top = x->top - (x->rows - 1); return 1; }
    if (code == KEY_PGDN) { x->top = x->top + (x->rows - 1); return 1; }
    if ((mods & M_CTRL) && code == KEY_HOME) { x->top = 0; return 1; }
    if ((mods & M_CTRL) && code == KEY_END) { x->top = x->nd; return 1; }
    if (code == KEY_ENTER) { if (x->ok && x->sel >= 0 && x->sel < x->nd) return xp_follow(x, x->sel); return 1; }
    if (code == KEY_ESC) {
        if (!x->filt[0]) return 0;
        x->filt[0] = 0; x->filtc = 0;
        if (x->ok) xp_filter(x);
        return 1;
    }
    if (code == KEY_BACK && !x->filt[0]) { xp_back(x); return 1; }
    if (ui_field_key(x->filt, XFILT, &x->filtc, code, ch, mods) && x->ok) {
        xp_filter(x);
        if (x->nvis && xp_listed(x, x->cur) != 0) xp_show(x, x->lvis[0], 0);
    }
    return 1;
}
// files.c -- Files, the file manager. docs/c4ix-desktop.md.
//
// A folder tree beside a file list, over C4IX's VFS. Double-click opens:
// a folder shows its contents, a program (a .c4r, or anything C4R
// inside, which is how /bin's are named) runs in a new
// Terminal, a source file opens in the Editor, anything else in the Text Editor.
// Object files and libraries (.c4o, .c4l, .c4s) are C4R inside too, but
// only c4rlink and the loader use them, so they open in the IDE's Code
// tab, which shows their code; File > Show Code does that for a program.
// New Folder, Delete (confirmed)
// and Rename go through the kernel's mkdir, unlink and rename.
//
// A right click on an item opens a menu of what can be done with it:
// Open, Open in IDE (a program, an object file or a library into the IDE's
// Code tab; a source into its editor), Rename, Delete and Download, and New
// Folder; on the empty part of the list, New Folder and Refresh; on a
// folder in the tree, which it shows, Expand or Collapse, New Folder in it
// and Refresh. The bar between the tree and the list is a splitter, which
// sizes the tree; the width it is left at is every Files window's, kept
// in /etc/desktop.cfg (theme_tree).
//
// Several items can be selected, as in Explorer: Ctrl-click adds or
// removes one, Shift-click (or Shift with the arrows) takes the range from
// the last one clicked, Ctrl+A takes them all. Delete takes what is
// selected, and a folder with all that is in it, files first and then the
// folders as they empty -- after saying so.
//
// The tree scrolls on its own: a scroll bar (arrows, page clicks, a thumb
// to drag, as every bar on the desktop has: ui_scroll_drag) and the wheel. It follows the selection only when that moves,
// not at every redraw, or the bar could never leave it. A folder with
// folders in it has a +/- box: click it, double-click the row, or use
// Left/Right or -/+ to collapse and expand. Each folder's folders are in
// name order, whatever order the list is in. The tree starts collapsed but
// for the root, so it shows the root's folders and nothing deeper; a
// folder opened stays open through a reload (by the hash of its path),
// one new to the tree comes in collapsed, and the folders above the one
// being shown always open.
//
// The list is sorted by name, type (the extension), size or date, either
// way round, folders first always: View > Sort, or a click on a column's
// header (again reverses it), which shows the order with an arrow. One
// order for every Files window, kept in /etc/desktop.cfg as Settings'
// choices are (theme_sort). Names sort without regard to case. The date
// is the VFS's modification order (vfs.c, vfs_touch): C4IX has no clock
// every host keeps, but a later change always sorts after an earlier one.

#include "desktop.h"

// NAMEW is the kernel's VN_NAME_MAX, TPW a tree path. Sized for the root
// archive's tree (some 70 folders, 80 files in the largest), and to fit
// ST_BYTES with room to spare.
enum { MAXE = 400, NAMEW = 64, MAXT = 256, TPW = 128, MAXDEPTH = 10, TREE_W = 180, ROW_H = 17, TOOL_H = 30, STATUS_H = 20 };
// the splitter between the tree and the list: its width; the narrowest
// the tree and the list may be made
enum { SPW = 6, TREE_MIN = 100, LIST_MIN = 280 };
// a tree node's flags: it has folders under it, and it is collapsed
enum { T_KIDS = 1, T_COLL = 2, MAXOPEN = 64 };

struct files {
    char path[128];
    int n, sel, top;                   // the list: entries, selection, first row shown
    char name[MAXE * NAMEW];
    int isdir[MAXE], size[MAXE], prog[MAXE];
    int mtime[MAXE];                   // ST_MTIME: the order things changed in
    int nt, tsel, ttop;                // the tree: folders, their depth, the one shown
    char tpath[MAXT * TPW];
    int tdepth[MAXT];
    char tflag[MAXT];                  // T_KIDS, T_COLL
    int tfollow;                       // scroll the tree to tsel at the next draw
    int pane;                          // 0 the list has the keyboard, 1 the tree
    int tleft;                         // the tree scrolled across: 6-pixel steps
    char mark[MAXE];                   // the selected items (sel is the one with the focus)
    int anchor;                        // where a Shift-click's range starts
    int tw, twx, tdrag;                // the tree's width: chosen, as drawn; its splitter being dragged
};

static struct files *F(struct win *w) { return (struct files *)w->st; }
static void mark_only(struct files *f, int i);
static char tbuf[256];

static struct wk_menu menus[3];
static char *file_items[9];
static char *view_items[10];
static char *go_items[2];
// View's sort items, each with WK_CHECKED before it: the item is the
// string from its second byte on, or from its first when it is the one in use
enum { V_SORT = 2, V_ASC = 7, V_DESC = 8 };
enum { VCHK_W = 16 };
static char vchk[6 * VCHK_W];
static char *vlabel[6] = { "Sort by Name", "Sort by Type", "Sort by Size", "Sort by Date", "Ascending", "Descending" };

static char *ename(struct files *f, int i) { return f->name + i * NAMEW; }

static void join(char *out, char *dir, char *name) {
    ui_cpy(out, dir);
    if (!(out[0] == '/' && out[1] == 0)) ui_cat(out, "/");
    ui_cat(out, name);
}

// ---- the order ----

static int lower(int c) { c = c & 255; return c >= 'A' && c <= 'Z' ? c + 32 : c; }

// names without regard to case; the same but for case, in byte order
static int namecmp(char *a, char *b) {
    char *p, *q;
    p = a; q = b;
    while (*p && lower(*p) == lower(*q)) { ++p; ++q; }
    if (lower(*p) != lower(*q)) return lower(*p) - lower(*q);
    while (*a && *a == *b) { ++a; ++b; }
    return (*a & 255) - (*b & 255);
}

// what follows a name's last '.', or "" (a leading '.' is not one)
static char *ext_of(char *s) {
    char *e;
    e = 0;
    if (*s == '.') ++s;
    while (*s) { if (*s == '.') e = s + 1; ++s; }
    return e ? e : s;
}

// Entry I against entry J in the order in use: below 0 if I goes first.
// Folders first either way; what the order leaves equal goes by name.
static int cmp(struct files *f, int i, int j) {
    int key, r;
    if (f->isdir[i] != f->isdir[j]) return f->isdir[j] - f->isdir[i];
    key = theme_sort() / 2;
    r = 0;
    if (key == SORT_TYPE && !f->isdir[i]) r = namecmp(ext_of(ename(f, i)), ext_of(ename(f, j)));
    else if (key == SORT_SIZE) r = f->size[i] < f->size[j] ? 0 - 1 : f->size[i] > f->size[j];
    else if (key == SORT_DATE) r = f->mtime[i] < f->mtime[j] ? 0 - 1 : f->mtime[i] > f->mtime[j];
    if (!r) r = namecmp(ename(f, i), ename(f, j));
    return theme_sort() & 1 ? 0 - r : r;
}

// entry SRC's name and facts into slot DST
static void e_move(struct files *f, int dst, int src) {
    ui_cpy(ename(f, dst), ename(f, src));
    f->isdir[dst] = f->isdir[src]; f->size[dst] = f->size[src];
    f->prog[dst] = f->prog[src]; f->mtime[dst] = f->mtime[src];
}

// Sort the list: an insertion sort of the entries' numbers, then each
// entry moved once into place, a cycle of the permutation at a time, so
// a name is copied once rather than at every step. The spare slot is
// the one past the last, kept free for it.
static int ord[MAXE];
static void sort_list(struct files *f) {
    int i, j, k, t;
    i = 0;
    while (i < f->n) {
        t = i;
        j = i;
        while (j > 0 && cmp(f, t, ord[j - 1]) < 0) { ord[j] = ord[j - 1]; --j; }
        ord[j] = t;
        ++i;
    }
    // row R is to hold entry ord[R]
    i = 0;
    while (i < f->n) {
        if (ord[i] != i) {
            e_move(f, MAXE - 1, i);
            j = i;
            while (ord[j] != i) { k = ord[j]; e_move(f, j, k); ord[j] = j; j = k; }
            e_move(f, j, MAXE - 1);
            ord[j] = j;
        }
        ++i;
    }
}

// View's check marks, for the order in use
static void sort_marks() {
    int k, s, on;
    s = theme_sort();
    k = 0;
    while (k < 6) {
        vchk[k * VCHK_W] = WK_CHECKED;
        ui_cpy(vchk + k * VCHK_W + 1, vlabel[k]);
        if (k < 4) on = k == s / 2;
        else on = k - 4 == (s & 1);
        view_items[k < 4 ? V_SORT + k : V_ASC + k - 4] = vchk + k * VCHK_W + (on ? 0 : 1);
        ++k;
    }
}

// the list sorted again, the focus kept on the same item
static void resort(struct files *f) {
    char nm[NAMEW];
    int i;
    nm[0] = 0;
    if (f->sel >= 0 && f->sel < f->n) ui_cpy(nm, ename(f, f->sel));
    sort_list(f);
    i = 0;
    while (i < f->n && !ui_eq(ename(f, i), nm)) ++i;
    f->sel = i < f->n ? i : 0;
    mark_only(f, f->sel);
}

// Another order, kept, and every Files window's list in it
static void set_sort(int sort) {
    int i;
    theme_set_sort(sort);
    sort_marks();
    i = wk_next(0);
    while (i) {
        if (wk_class_of(i) == kind_class(K_FILES)) resort(F(win_get(i)));
        i = wk_next(i);
    }
    mark_dirty();
}

// an object file or a library: linked into programs, never run itself
static int is_linkable(char *p) {
    return ui_ends(p, ".c4o") || ui_ends(p, ".c4l") || ui_ends(p, ".c4s");
}

// Read a directory, in the order in use. Slot MAXE - 1 is sort_list's.
static void load(struct files *f) {
    int i, r, st[ST_MTIME + 1];
    char nm[NAMEW];
    f->n = 0;
    i = 0;
    while (f->n < MAXE - 1) {
        r = ureaddir(f->path, i, nm);
        if (r < 0) break;
        ui_cpy(ename(f, f->n), nm);
        f->isdir[f->n] = r;
        join(tbuf, f->path, nm);
        st[ST_SIZE] = 0; st[ST_PROG] = 0; st[ST_MTIME] = 0;
        ustat2(tbuf, st, ST_MTIME + 1);
        f->size[f->n] = r ? 0 : st[ST_SIZE];
        f->mtime[f->n] = st[ST_MTIME];
        f->prog[f->n] = !r && !is_linkable(nm) && (st[ST_PROG] || ui_ends(nm, ".c4r"));
        ++f->n;
        ++i;
    }
    sort_list(f);
    if (f->sel >= f->n) f->sel = f->n - 1;
    if (f->sel < 0) f->sel = 0;
    if (f->top > f->sel) f->top = f->sel;
    mark_only(f, f->sel);
}

// ---- the selection ----

// just item I
static void mark_only(struct files *f, int i) {
    int k;
    k = 0;
    while (k < MAXE) { f->mark[k] = 0; ++k; }
    if (i >= 0 && i < f->n) f->mark[i] = 1;
    f->anchor = i;
}

// the range from the anchor to I
static void mark_range(struct files *f, int i) {
    int k, a, b;
    a = f->anchor < i ? f->anchor : i;
    b = f->anchor < i ? i : f->anchor;
    k = 0;
    while (k < f->n) { f->mark[k] = k >= a && k <= b; ++k; }
}

static int nmarked(struct files *f) {
    int k, n;
    n = 0;
    k = 0;
    while (k < f->n) { if (f->mark[k]) ++n; ++k; }
    return n;
}

// The focus moved to I, by a key: Shift takes the range, else just I
static void move_to(struct files *f, int i, int mods) {
    f->sel = i;
    if (mods & M_SHIFT) mark_range(f, i);
    else mark_only(f, i);
}

// A folder and all in it: files first, then the folders as they empty.
// How many could not be removed.
static int del_tree(char *dir) {
    char name[NAMEW], sub[256];
    int i, r, bad, n;
    bad = 0;
    i = 0;
    while ((r = ureaddir(dir, i, name)) >= 0) {
        if (ui_len(dir) + ui_len(name) + 2 > 256) { ++bad; ++i; continue; }
        join(sub, dir, name);
        n = r == 1 ? del_tree(sub) : uunlink(sub) < 0;
        if (n) { bad = bad + n; ++i; }      // what stayed keeps index i
    }
    if (uunlink(dir) < 0) ++bad;
    return bad;
}

// The folders open in the tree, by the hash of the path, while it is
// made again (tree_load)
static int t_open[MAXOPEN], t_nopen;

static int phash(char *s);

// Is DIR the folder shown, or one above it?
static int t_above(struct files *f, char *dir) {
    int n;
    n = ui_len(dir);
    if (n == 1 && dir[0] == '/') return 1;
    return !memcmp(f->path, dir, n) && (f->path[n] == 0 || f->path[n] == '/');
}

// Has DIR a folder in it? One a directory still on the host (stat's
// device 3: vfs.c, vfs_lazydir) is taken to have, as the games' do: to
// look would make its entries.
static int t_haskids(char *dir) {
    int i, r, st[ST_WORDS];
    char nm[NAMEW];
    if (ustat2(dir, st, ST_WORDS) >= 0 && st[ST_DEV] == 3) return 1;
    i = 0;
    while ((r = ureaddir(dir, i, nm)) >= 0) { if (r == 1) return 1; ++i; }
    return 0;
}

// The tree's folders, depth first, each folder's own by name (as namecmp
// orders them) -- but only in the open folders and those above the one
// shown: the rest are a row each, with a box if they have folders, and
// are read when opened (t_toggle). Every folder on the disk was walked at
// every click once, hundreds with the games' sources: a second each.
// DIR is copied in first thing, so a caller may pass a buffer the
// recursion will reuse. A folder's folders are taken smallest first, a
// pass over it for each -- the next name after the last one taken --
// rather than with a list of them at every level of the recursion.
static void tree_walk(struct files *f, char *dir, int depth) {
    int i, r, me, took, found, h;
    char nm[NAMEW], last[NAMEW], next[NAMEW];
    if (f->nt >= MAXT || depth > MAXDEPTH) return;
    me = f->nt;
    ui_cpy(f->tpath + me * TPW, dir);
    f->tdepth[me] = depth;
    f->tflag[me] = 0;
    ++f->nt;
    if (depth > 0 && !t_above(f, dir)) {
        h = phash(dir);
        i = 0;
        while (i < t_nopen && t_open[i] != h) ++i;
        if (i == t_nopen) {
            if (depth < MAXDEPTH && t_haskids(dir)) f->tflag[me] = T_KIDS;
            return;
        }
    }
    took = 0;
    while (f->nt < MAXT) {
        found = 0;
        i = 0;
        while ((r = ureaddir(f->tpath + me * TPW, i, nm)) >= 0) {
            if (r == 1 && (!took || namecmp(nm, last) > 0) && (!found || namecmp(nm, next) < 0)) { ui_cpy(next, nm); found = 1; }
            ++i;
        }
        if (!found) break;
        ui_cpy(last, next);
        took = 1;
        join(tbuf, f->tpath + me * TPW, next);
        tree_walk(f, tbuf, depth + 1);
    }
    // a box only where a folder below was taken: not past MAXDEPTH or MAXT
    if (f->nt > me + 1) f->tflag[me] = T_KIDS;
}

static int phash(char *s) {
    int h;
    h = 5381;
    while (*s) { h = (h * 33 + (*s & 255)) & 0x7fffffff; ++s; }
    return h;
}

// The tree again, from the disk. A folder with folders in it is collapsed
// unless it was open before -- the first time, only the root is -- but
// every folder above the one shown opens, so the selection can be seen.
static void tree_load(struct files *f) {
    int first, i, j, h, d;
    first = f->nt == 0;
    t_nopen = 0;
    i = 0;
    while (i < f->nt) {
        if ((f->tflag[i] & T_KIDS) && !(f->tflag[i] & T_COLL) && t_nopen < MAXOPEN) { t_open[t_nopen] = phash(f->tpath + i * TPW); ++t_nopen; }
        ++i;
    }
    f->nt = 0;
    tree_walk(f, "/", 0);
    i = 0;
    while (i < f->nt) {
        if ((f->tflag[i] & T_KIDS) && !(first && i == 0)) {
            h = phash(f->tpath + i * TPW);
            j = 0;
            while (j < t_nopen && t_open[j] != h) ++j;
            if (j == t_nopen) f->tflag[i] = f->tflag[i] | T_COLL;
        }
        ++i;
    }
    f->tsel = 0;
    while (f->tsel < f->nt && !ui_eq(f->tpath + f->tsel * TPW, f->path)) ++f->tsel;
    if (f->tsel >= f->nt) f->tsel = 0;
    d = f->tdepth[f->tsel];
    i = f->tsel - 1;
    while (i >= 0 && d > 0) {
        if (f->tdepth[i] < d) { f->tflag[i] = f->tflag[i] & T_KIDS; d = f->tdepth[i]; }
        --i;
    }
    f->tfollow = 1;
}

// The node shown after node I (itself shown): a collapsed one hides
// everything deeper that follows it.
static int t_next(struct files *f, int i) {
    int d;
    if (!(f->tflag[i] & T_COLL)) return i + 1;
    d = f->tdepth[i];
    ++i;
    while (i < f->nt && f->tdepth[i] > d) ++i;
    return i;
}

// how many nodes are shown, and the row node I is on (-1 if hidden)
static int t_shown(struct files *f) {
    int i, n;
    i = 0; n = 0;
    while (i < f->nt) { ++n; i = t_next(f, i); }
    return n;
}
static int t_row(struct files *f, int node) {
    int i, n;
    i = 0; n = 0;
    while (i < f->nt) { if (i == node) return n; ++n; i = t_next(f, i); }
    return 0 - 1;
}
// the node on shown row R, or -1
static int t_at(struct files *f, int r) {
    int i;
    i = 0;
    while (i < f->nt && r > 0) { i = t_next(f, i); --r; }
    return (r == 0 && i < f->nt) ? i : 0 - 1;
}

// the tree's rows, and its scroll bar's place, in client coordinates
// The tree's widest row, in 6-pixel steps (a character of the sans font);
// wider than the pane, it gets a bar across, which takes a row.
static int t_maxw(struct files *f) {
    int i, k, w, mx;
    mx = 0; i = 0;
    while (i < f->nt) {
        if (i == 0) k = 8;
        else {
            k = ui_len(f->tpath + i * TPW);
            w = k;
            while (w > 0 && f->tpath[i * TPW + w - 1] != '/') --w;
            k = k - w;
        }
        w = (18 + f->tdepth[i] * 14 + 26) / 6 + k + 1;
        if (w > mx) mx = w;
        i = t_next(f, i);
    }
    return mx;
}
enum { THB_X = 4 };
#define THB_W (f->twx - 22)
static int t_hvis(struct files *f) { return THB_W / 6; }
static int t_hbar(struct files *f) { return t_maxw(f) > t_hvis(f); }
static int t_rows(struct files *f, int ch) { return (ch - TOOL_H - STATUS_H - 2 - 6 - (t_hbar(f) ? 16 : 0)) / ROW_H; }
static int t_hby(int ch) { return ch - STATUS_H - 2 - 18; }
static void t_hclamp(struct files *f) {
    int max;
    max = t_maxw(f) - t_hvis(f);
    if (max < 0) max = 0;
    if (f->tleft > max) f->tleft = max;
    if (f->tleft < 0) f->tleft = 0;
}
static int t_clamp(struct files *f, int rows) {
    int max;
    max = t_shown(f) - rows;
    if (max < 0) max = 0;
    if (f->ttop > max) f->ttop = max;
    if (f->ttop < 0) f->ttop = 0;
    return max;
}
#define TSB_X (2 + f->twx - 18)
// the tree's width in a window CW wide: the one chosen, as far as the list keeps its own
static int t_width(struct files *f, int cw) {
    int w;
    w = f->tw;
    if (w > cw - SPW - 4 - LIST_MIN) w = cw - SPW - 4 - LIST_MIN;
    if (w < TREE_MIN) w = TREE_MIN;
    return w;
}

static void go(struct win *w, char *path) {
    struct files *f;
    f = F(w);
    if (path != f->path) ui_cpy(f->path, path);
    f->sel = 0; f->top = 0;
    load(f);
    tree_load(f);
    ui_cpy(tbuf, "Files - ");
    ui_cat(tbuf, f->path);
    win_title(w, tbuf);
}

static void up(struct win *w) {
    struct files *f;
    int k;
    f = F(w);
    k = ui_len(f->path);
    while (k > 0 && f->path[k] != '/') --k;
    if (k == 0) f->path[1] = 0; else f->path[k] = 0;
    go(w, f->path);
}

// show tree node I's folder, keeping the keyboard in the tree
static void t_select(struct win *w, int node) {
    struct files *f;
    f = F(w);
    if (node < 0 || node >= f->nt) return;
    ui_cpy(tbuf, f->tpath + node * TPW);
    go(w, tbuf);
    f->pane = 1;
}

// Collapse or expand node I. A selection it hides moves to it, as a
// collapsed folder is where the selection was going to be seen.
static void t_toggle(struct win *w, int i) {
    struct files *f;
    int d, j;
    f = F(w);
    if (i < 0 || i >= f->nt || !(f->tflag[i] & T_KIDS)) return;
    f->tflag[i] = f->tflag[i] ^ T_COLL;
    if (!(f->tflag[i] & T_COLL)) {
        // opened, and its folders not read yet: the tree again, with it open
        if (i + 1 >= f->nt || f->tdepth[i + 1] <= f->tdepth[i]) {
            d = f->ttop;
            tree_load(f);
            f->ttop = d;
            f->tfollow = 0;
        }
        return;
    }
    d = f->tdepth[i];
    j = i + 1;
    while (j < f->nt && f->tdepth[j] > d) { if (j == f->tsel) { t_select(w, i); return; } ++j; }
}

static char *type_of(char *name, int dir, int prog) {
    if (dir) return "Folder";
    if (prog) return "C4IX Program";
    if (ui_ends(name, ".c4o")) return "C4R Object";
    if (ui_ends(name, ".c4l")) return "C4R Library";
    if (ui_ends(name, ".c4s")) return "Shared Library";
    if (ui_ends(name, ".c")) return "C Source";
    if (ui_ends(name, ".h")) return "C Header";
    if (ui_ends(name, ".txt")) return "Text";
    if (ui_ends(name, ".sh")) return "Shell Script";
    if (ui_ends(name, ".lisp")) return "Lisp Source";
    if (ui_ends(name, ".f")) return "Forth Source";
    return "File";
}

// what opens in the Editor, the IDE, rather than the Text Editor: source of any
// kind, build files, scripts; plain text documents stay the Text Editor's
static int is_source(char *p) {
    return ui_ends(p, ".c") || ui_ends(p, ".h") || ui_ends(p, ".b4k") || ui_ends(p, ".B4K") ||
           ui_ends(p, ".lisp") || ui_ends(p, ".scm") || ui_ends(p, ".f") || ui_ends(p, ".fs") ||
           ui_ends(p, ".js") || ui_ends(p, ".mjs") || ui_ends(p, ".sh") || ui_ends(p, ".S") ||
           ui_ends(p, ".s") || ui_ends(p, ".asm") || ui_ends(p, ".py") || ui_ends(p, ".json") ||
           ui_ends(p, ".md") || ui_ends(p, ".html") || ui_ends(p, ".css") || ui_ends(p, ".mk") ||
           ui_ends(p, "Makefile") || ui_ends(p, ".lst");
}

static void open_sel(struct win *w) {
    struct files *f;
    f = F(w);
    if (f->sel < 0 || f->sel >= f->n) return;
    join(tbuf, f->path, ename(f, f->sel));
    if (f->isdir[f->sel]) go(w, tbuf);
    else if (f->prog[f->sel]) run_command(tbuf);
    else if (is_linkable(tbuf)) edit_open(tbuf);
    else if (is_source(tbuf)) edit_open(tbuf);
    else note_open(tbuf);
}

int files_open(char *path) {
    int i;
    struct win *w;
    i = win_open(K_FILES, "Files", 600, 420, sizeof(struct files));
    if (i < 0) return i;
    w = win_get(i);
    F(w)->tw = theme_tree();
    menus[0].title = "File"; menus[1].title = "View"; menus[2].title = "Go";
    file_items[0] = "Open"; file_items[1] = "New Folder"; file_items[2] = "Delete";
    file_items[3] = "Rename"; file_items[4] = "Show Code"; file_items[5] = "Download";
    file_items[6] = "-"; file_items[7] = "Close"; file_items[8] = 0;
    view_items[0] = "Refresh"; view_items[1] = "-"; view_items[6] = "-"; view_items[9] = 0;
    sort_marks();
    go_items[0] = "Up"; go_items[1] = 0;
    menus[0].items = file_items; menus[1].items = view_items; menus[2].items = go_items;
    wk_menu(i, menus, 3);
    go(w, path);
    return i;
}

// ---- drawing --------------------------------------------------------------------

static void small_icon(int dir, int prog, int x, int y) {
    if (dir) {
        d_rect(x, y + 2, 6, 2, 0xc8a000); d_rect(x, y + 4, 14, 9, 0xffd84a); d_recto(x, y + 4, 14, 9, 0x806000);
    } else if (prog) {
        d_rect(x, y + 1, 14, 12, C_WHITE); d_recto(x, y + 1, 14, 12, C_DARK); d_rect(x + 1, y + 2, 12, 3, C_TITLE);
    } else {
        d_rect(x + 2, y, 10, 14, C_WHITE); d_recto(x + 2, y, 10, 14, C_SHADOW);
        d_rect(x + 4, y + 4, 6, 1, C_SHADOW); d_rect(x + 4, y + 7, 6, 1, C_SHADOW);
    }
}

static int widths[3];
static char *labels[3];
// the columns, left to right, and the order a click on each sorts by
static int col_sort[3] = { SORT_NAME, SORT_SIZE, SORT_TYPE };

// the arrow on the header of the column the list is sorted by: up for
// ascending, down for descending (by date has no column)
static void sort_arrow(int x, int y) {
    int k, r, down;
    down = theme_sort() & 1;
    k = 0;
    while (k < 3 && col_sort[k] != theme_sort() / 2) { x = x + widths[k]; ++k; }
    if (k == 3) return;
    x = x + widths[k] - 14;
    r = 0;
    while (r < 4) {
        if (down) d_rect(x + r, y + r, 7 - 2 * r, 1, C_SHADOW);
        else d_rect(x + 3 - r, y + r, 1 + 2 * r, 1, C_SHADOW);
        ++r;
    }
}

// the +/- box on a folder with folders in it, centred where its lines meet
static void t_box(int x, int y, int coll) {
    d_rect(x, y, 9, 9, C_WHITE);
    d_recto(x, y, 9, 9, C_SHADOW);
    d_rect(x + 2, y + 4, 5, 1, C_DARK);
    if (coll) d_rect(x + 4, y + 2, 1, 5, C_DARK);
}

void files_draw(struct win *w, int ox, int oy, int cw, int ch, int focused) {
    struct files *f;
    int i, y, lx, lw, lh, rows, tx, th, trows, sel_bg, nv, r, hb, dx;
    f = F(w);
    f->twx = t_width(f, cw);
    d_rect(ox, oy, cw, ch, C_FACE);
    // the toolbar: Up, and the address
    ui_button(ox + 4, oy + 4, 26, 22, "", 0, 0);
    d_rect(ox + 10, oy + 9, 6, 2, 0xc8a000); d_rect(ox + 10, oy + 11, 14, 10, 0xffd84a);
    d_line(ox + 17, oy + 13, ox + 17, oy + 19, C_DARK); d_line(ox + 14, oy + 16, ox + 17, oy + 13, C_DARK); d_line(ox + 20, oy + 16, ox + 17, oy + 13, C_DARK);
    d_text(ox + 38, oy + 9, C_DARK, F_SANS, "Address");
    ui_field(ox + 86, oy + 4, cw - 90, f->path, 0, 0);
    // the tree
    tx = ox + 2; th = ch - TOOL_H - STATUS_H - 2;
    d_rect(tx, oy + TOOL_H, f->twx, th, C_WHITE);
    d_bevel(tx, oy + TOOL_H, f->twx, th, B_SUNKEN);
    trows = t_rows(f, ch);
    nv = t_shown(f);
    hb = t_hbar(f);
    t_hclamp(f);
    dx = f->tleft * 6;
    // the names and lines stay inside the tree, under its bars
    d_clip(tx + 2, oy + TOOL_H + 2, f->twx - 4 - (nv > trows ? 16 : 0), th - 4 - (hb ? 16 : 0));
    if (f->tfollow) {
        r = t_row(f, f->tsel);
        if (r >= 0 && r < f->ttop) f->ttop = r;
        if (r >= f->ttop + trows) f->ttop = r - trows + 1;
        f->tfollow = 0;
    }
    t_clamp(f, trows);
    i = t_at(f, f->ttop);
    r = 0;
    y = oy + TOOL_H + 3;
    while (i >= 0 && i < f->nt && r < trows) {
        lx = tx + 18 + f->tdepth[i] * 14 - dx;
        if (f->tdepth[i] > 0) {
            d_rect(lx - 9, y + 8, 7, 1, C_SHADOW);
            d_rect(lx - 9, y - 2, 1, 10, C_SHADOW);
        }
        if (f->tflag[i] & T_KIDS) t_box(lx - 13, y + 4, f->tflag[i] & T_COLL);
        small_icon(1, 0, lx, y + 1);
        tbuf[0] = 0;
        if (i == 0) ui_cpy(tbuf, "C4IX (/)");
        else {
            lw = ui_len(f->tpath + i * TPW);
            while (lw > 0 && f->tpath[i * TPW + lw - 1] != '/') --lw;
            ui_cpy(tbuf, f->tpath + i * TPW + lw);
        }
        sel_bg = i == f->tsel;
        if (sel_bg) d_rect(lx + 17, y, ui_len(tbuf) * 6 + 6, ROW_H - 1, f->pane == 1 && focused ? C_SEL : C_FACE);
        d_text(lx + 20, y + 2, sel_bg && f->pane == 1 && focused ? C_WHITE : C_DARK, F_SANS, tbuf);
        y = y + ROW_H;
        ++r;
        i = t_next(f, i);
    }
    d_clip_end();
    if (nv > trows) ui_scrollbar(ox + TSB_X, oy + TOOL_H + 2, th - 4 - (hb ? 16 : 0), nv, trows, f->ttop);
    if (hb) ui_hscrollbar(ox + THB_X, oy + t_hby(ch), THB_W, t_maxw(f), t_hvis(f), f->tleft);
    // the splitter, and the list
    ui_splitter(tx + f->twx, oy + TOOL_H, SPW, th);
    lx = tx + f->twx + SPW; lw = cw - f->twx - SPW - 4;
    d_rect(lx, oy + TOOL_H, lw, th, C_WHITE);
    d_bevel(lx, oy + TOOL_H, lw, th, B_SUNKEN);
    widths[0] = lw - 4 - 16 - 170; widths[1] = 70; widths[2] = 100;
    labels[0] = "Name"; labels[1] = "Size"; labels[2] = "Type";
    ui_header(lx + 2, oy + TOOL_H + 2, widths, labels, 3);
    sort_arrow(lx + 2, oy + TOOL_H + 9);
    lh = th - 22;
    rows = (lh - 4) / ROW_H;
    if (f->sel < f->top) f->top = f->sel;
    if (f->sel >= f->top + rows) f->top = f->sel - rows + 1;
    i = f->top;
    y = oy + TOOL_H + 22;
    while (i < f->n && i < f->top + rows) {
        small_icon(f->isdir[i], f->prog[i], lx + 6, y + 1);
        sel_bg = f->mark[i];
        if (sel_bg) d_rect(lx + 23, y, ui_len(ename(f, i)) * 6 + 6, ROW_H - 1, f->pane == 0 && focused ? C_SEL : C_FACE);
        d_text(lx + 26, y + 2, sel_bg && f->pane == 0 && focused ? C_WHITE : C_DARK, F_SANS, ename(f, i));
        if (!f->isdir[i]) {
            ui_num_commas(tbuf, (f->size[i] + 1023) / 1024);
            ui_cat(tbuf, " KB");
            d_text(lx + 2 + widths[0] + widths[1] - ui_len(tbuf) * 6 - 8, y + 2, C_DARK, F_SANS, tbuf);
        }
        d_text(lx + 2 + widths[0] + widths[1] + 6, y + 2, C_DARK, F_SANS, type_of(ename(f, i), f->isdir[i], f->prog[i]));
        y = y + ROW_H;
        ++i;
    }
    ui_scrollbar(lx + lw - 18, oy + TOOL_H + 20, lh - 2, f->n, rows, f->top);
    // the status bar
    d_rect(ox, oy + ch - STATUS_H, cw, STATUS_H, C_FACE);
    d_bevel(ox + 2, oy + ch - STATUS_H + 2, cw - 4, STATUS_H - 3, B_SUNKEN);
    ui_num(tbuf, f->n);
    ui_cat(tbuf, f->n == 1 ? " item" : " items");
    if ((i = nmarked(f)) > 1) { ui_cat(tbuf, ", "); ui_num(tbuf + ui_len(tbuf), i); ui_cat(tbuf, " selected"); }
    d_text(ox + 8, oy + ch - STATUS_H + 5, C_DARK, F_SANS, tbuf);
}

// ---- input ------------------------------------------------------------------------------

// The right click's menus: their items as drawn, and what each does
enum { P_OPEN = 1, P_IDE = 2, P_NEWDIR = 3, P_RENAME = 4, P_DELETE = 5, P_DOWNLOAD = 6,
       P_REFRESH = 7, P_TOGGLE = 8, P_MAX = 12 };
static char *pop_items[P_MAX];
static int pop_act[P_MAX], pop_n;
static void pop_add(char *label, int act) { pop_items[pop_n] = label; pop_act[pop_n] = act; ++pop_n; pop_items[pop_n] = 0; }

// what opens in the IDE: a compiled file (into its Code tab), or a source
static int ide_ok(struct files *f, int i) {
    if (f->isdir[i]) return 0;
    return f->prog[i] || is_linkable(ename(f, i)) || is_source(ename(f, i));
}

// A right click on the list: on an item (taking it, unless it is among
// those selected already), or on the list's empty part
static void pop_list(struct win *w, int row, int x, int y) {
    struct files *f;
    f = F(w);
    pop_n = 0;
    if (row >= 0 && row < f->n) {
        if (!f->mark[row]) mark_only(f, row);
        f->sel = row;
        pop_add("Open", P_OPEN);
        if (ide_ok(f, row)) pop_add("Open in IDE", P_IDE);
        pop_add("-", 0);
        pop_add("Rename", P_RENAME);
        pop_add("Delete", P_DELETE);
        pop_add("-", 0);
        pop_add("New Folder", P_NEWDIR);
        pop_add("Download", P_DOWNLOAD);
    } else {
        pop_add("New Folder", P_NEWDIR);
        pop_add("Refresh", P_REFRESH);
    }
    wk_popup(w->id, x, y, pop_items);
}

// ... and on a folder in the tree, the one now shown
static void pop_tree(struct win *w, int x, int y) {
    struct files *f;
    f = F(w);
    pop_n = 0;
    if (f->tflag[f->tsel] & T_KIDS) pop_add(f->tflag[f->tsel] & T_COLL ? "Expand" : "Collapse", P_TOGGLE);
    pop_add("New Folder", P_NEWDIR);
    pop_add("Refresh", P_REFRESH);
    wk_popup(w->id, x, y, pop_items);
}

// an item of those menus chosen
static void pop_do(struct win *w, int k) {
    struct files *f;
    f = F(w);
    if (k < 0 || k >= pop_n) return;
    k = pop_act[k];
    if (k == P_OPEN) open_sel(w);
    else if (k == P_IDE && f->sel >= 0 && f->sel < f->n) {
        // a compiled file opens in the IDE's Code tab alone, as its own
        // File > Open does one (edit.c, e_open); a source in its editor
        join(tbuf, f->path, ename(f, f->sel));
        edit_open(tbuf);
    }
    else if (k == P_NEWDIR) files_command(w, 0, 1);
    else if (k == P_RENAME) files_command(w, 0, 3);
    else if (k == P_DELETE) files_command(w, 0, 2);
    else if (k == P_DOWNLOAD) files_command(w, 0, 5);
    else if (k == P_REFRESH) files_command(w, 1, 0);
    else if (k == P_TOGGLE) t_toggle(w, f->tsel);
}

// The pointer: arrows, but for the splitter's left and right
int files_pointer(struct win *w, int x, int y, int cw, int ch) {
    struct files *f;
    f = F(w);
    f->twx = t_width(f, cw);
    if (x >= 2 + f->twx && x < 2 + f->twx + SPW && y >= TOOL_H && y < ch - STATUS_H) return PTR_COLS;
    return PTR_ARROW;
}

void files_mouse(struct win *w, int ev, int x, int y, int cw, int ch) {
    struct files *f;
    int th, lx, lw, rows, row, t, lh, trows, nv, node, bx, k;
    f = F(w);
    f->twx = t_width(f, cw);
    th = ch - TOOL_H - STATUS_H - 2;
    lx = 2 + f->twx + SPW; lw = cw - f->twx - SPW - 4;
    lh = th - 22;
    rows = (lh - 4) / ROW_H;
    trows = t_rows(f, ch);
    nv = t_shown(f);
    // the splitter let go: its width kept, for Files windows opened after
    if (ev == E_UP) { if (f->tdrag) { f->tdrag = 0; theme_set_tree(f->tw); } return; }
    if (ev == E_MOVE && f->tdrag && (t = ui_split_drag(x)) >= 0) {
        f->tw = t;
        if (f->tw > cw - SPW - 4 - LIST_MIN) f->tw = cw - SPW - 4 - LIST_MIN;
        if (f->tw < TREE_MIN) f->tw = TREE_MIN;
        return;
    }
    if (ev == E_MOVE) {
        t = ui_scroll_drag(TSB_X, TOOL_H + 2, y);
        if (t >= 0) { f->ttop = t; t_clamp(f, trows); return; }
        t = ui_scroll_drag(THB_X, t_hby(ch), x);
        if (t >= 0) { f->tleft = t; t_hclamp(f); return; }
        t = ui_scroll_drag(lx + lw - 18, TOOL_H + 20, y);
        if (t >= 0) {
            f->top = t;
            if (f->sel < f->top) f->sel = f->top;
            if (f->sel >= f->top + rows) f->sel = f->top + rows - 1;
        }
        return;
    }
    if (ev == E_WHEEL && x < 2 + f->twx) {
        f->ttop = f->ttop + y * 3;
        t_clamp(f, trows);
        return;
    }
    if (ev == E_WHEEL) {
        // y is the wheel's direction here
        f->top = f->top + y * 3;
        if (f->top > f->n - rows) f->top = f->n - rows;
        if (f->top < 0) f->top = 0;
        if (f->sel < f->top) f->sel = f->top;
        if (f->sel >= f->top + rows) f->sel = f->top + rows - 1;
        return;
    }
    if (ev != E_DOWN && ev != E_DBL) return;
    if (ui_hit(x, y, 4, 4, 26, 22)) { if (ev == E_DOWN) up(w); return; }
    if (ev == E_DOWN && wm_button == 0 && ui_split_click(x, y, 2 + f->twx, TOOL_H, SPW, th, f->twx)) { f->tdrag = 1; return; }
    if (nv > trows && ui_hit(x, y, TSB_X, TOOL_H + 2, 16, th - 4 - (t_hbar(f) ? 16 : 0))) {
        if (ev != E_DOWN) return;
        t = ui_scroll_click(x, y, TSB_X, TOOL_H + 2, th - 4 - (t_hbar(f) ? 16 : 0), nv, trows, f->ttop);
        if (t >= 0) f->ttop = t;
        return;
    }
    if (t_hbar(f) && ui_hit(x, y, 2, t_hby(ch), f->twx, 16)) {
        if (ev != E_DOWN) return;
        t = ui_hscroll_click(x, y, THB_X, t_hby(ch), THB_W, t_maxw(f), t_hvis(f), f->tleft);
        if (t >= 0) f->tleft = t;
        return;
    }
    if (ui_hit(x, y, 2, TOOL_H, f->twx, th)) {
        f->pane = 1;
        node = t_at(f, f->ttop + (y - TOOL_H - 3) / ROW_H);
        if (node < 0) return;
        // a right click: that folder shown, and its menu
        if (wm_button == 2) { if (ev == E_DOWN) { t_select(w, node); pop_tree(w, x, y); } return; }
        bx = 2 + 18 + f->tdepth[node] * 14 - 13 - f->tleft * 6;
        if (x >= bx - 2 && x < bx + 11 && (f->tflag[node] & T_KIDS)) { if (ev == E_DOWN) t_toggle(w, node); return; }
        if (ev == E_DOWN) t_select(w, node);
        else t_toggle(w, node);
        return;
    }
    // A column's header: sort by it, or the other way round if it is
    // already. Each click, not the E_DBL that follows a second quick one.
    if (ui_hit(x, y, lx + 2, TOOL_H + 2, lw - 4 - 16, 18)) {
        if (ev != E_DOWN) return;
        t = x - lx - 2 - (lw - 4 - 16 - 170);
        k = col_sort[t < 0 ? 0 : t < 70 ? 1 : 2];
        set_sort(theme_sort() / 2 == k ? theme_sort() ^ 1 : k * 2);
        return;
    }
    t = ui_scroll_click(x, y, lx + lw - 18, TOOL_H + 20, lh - 2, f->n, rows, f->top);
    if (t >= 0) { f->top = t; if (f->sel < f->top) f->sel = f->top; if (f->sel >= f->top + rows) f->sel = f->top + rows - 1; return; }
    if (ui_hit(x, y, lx, TOOL_H + 22, lw, lh)) {
        f->pane = 0;
        row = f->top + (y - TOOL_H - 22) / ROW_H;
        if (wm_button == 2) { if (ev == E_DOWN) pop_list(w, row, x, y); return; }
        if (row >= 0 && row < f->n) {
            f->sel = row;
            if (ev == E_DBL) { mark_only(f, row); open_sel(w); }
            else if (wm_mods & M_CTRL) { f->mark[row] = !f->mark[row]; f->anchor = row; }
            else if (wm_mods & M_SHIFT) mark_range(f, row);
            else mark_only(f, row);
        }
    }
}

void files_key(struct win *w, int code, int ch, int mods) {
    struct files *f;
    int r, i;
    f = F(w);
    if (code == KEY_TAB) { f->pane = !f->pane; return; }
    // these mean the same whichever pane has the keyboard
    if (code == KEY_F5) { files_command(w, 1, 0); return; }
    if (code == KEY_BACK) { up(w); return; }
    if (f->pane == 1) {
        r = t_row(f, f->tsel);
        if (code == KEY_UP && r > 0) t_select(w, t_at(f, r - 1));
        else if (code == KEY_DOWN && r >= 0 && r < t_shown(f) - 1) t_select(w, t_at(f, r + 1));
        else if (code == KEY_HOME) t_select(w, 0);
        else if (code == KEY_END) t_select(w, t_at(f, t_shown(f) - 1));
        else if (code == KEY_LEFT || ch == '-') {
            // collapse; on one already collapsed (or with none), its parent
            if ((f->tflag[f->tsel] & T_KIDS) && !(f->tflag[f->tsel] & T_COLL)) t_toggle(w, f->tsel);
            else if (code == KEY_LEFT && f->tsel > 0) {
                i = f->tsel - 1;
                while (i > 0 && f->tdepth[i] >= f->tdepth[f->tsel]) --i;
                t_select(w, i);
            }
        }
        else if (code == KEY_RIGHT || ch == '+') {
            // expand; on one already open, its first folder
            if (f->tflag[f->tsel] & T_COLL) t_toggle(w, f->tsel);
            else if (code == KEY_RIGHT && (f->tflag[f->tsel] & T_KIDS) && f->tsel + 1 < f->nt) t_select(w, f->tsel + 1);
        }
        return;
    }
    if (code == KEY_UP && f->sel > 0) move_to(f, f->sel - 1, mods);
    else if (code == KEY_DOWN && f->sel < f->n - 1) move_to(f, f->sel + 1, mods);
    else if (code == KEY_HOME) move_to(f, 0, mods);
    else if (code == KEY_END) move_to(f, f->n - 1, mods);
    else if (code == KEY_PGUP) move_to(f, f->sel - 10 < 0 ? 0 : f->sel - 10, mods);
    else if (code == KEY_PGDN) move_to(f, f->sel + 10 >= f->n ? f->n - 1 : f->sel + 10, mods);
    else if ((mods & M_CTRL) && (code == 'A' || ch == 1 || ch == 'a')) {
        i = 0;
        while (i < f->n) { f->mark[i] = 1; ++i; }
    }
    else if (code == KEY_ENTER) open_sel(w);
    else if (code == KEY_BACK) up(w);
    else if (code == KEY_DEL) files_command(w, 0, 2);
    else if (code == KEY_F2) files_command(w, 0, 3);
    else if (code == KEY_F5) files_command(w, 1, 0);
}

void files_command(struct win *w, int menu, int item) {
    struct files *f;
    char path[256], name[NAMEW];
    char *av[3];
    int n, i, dirs, pid;
    f = F(w);
    if (menu == WK_POPUP) { pop_do(w, item); return; }
    if (menu == 0) {
        if (item == 0) open_sel(w);
        else if (item == 1) inputbox(w, "New Folder", "Name of the new folder:", "New Folder", A_NEWDIR);
        else if (item == 2 && f->n) {
            if (!nmarked(f)) mark_only(f, f->sel);
            n = nmarked(f);
            dirs = 0;
            i = 0;
            while (i < f->n) { if (f->mark[i] && f->isdir[i]) ++dirs; ++i; }
            if (n > 1) {
                ui_cpy(tbuf, "Delete these ");
                ui_num(tbuf + ui_len(tbuf), n);
                ui_cat(tbuf, dirs ? " items, and all in the folders among them?" : " items?");
                msgbox(w, "Delete Items", tbuf, 1, A_DELETE);
            } else {
                i = 0;
                while (!f->mark[i]) ++i;
                ui_cpy(tbuf, "Delete '");
                ui_cat(tbuf, ename(f, i));
                // a folder with something in it goes with all of it: say so
                join(path, f->path, ename(f, i));
                ui_cat(tbuf, f->isdir[i] && ureaddir(path, 0, name) >= 0 ? "' and all in it?" : "'?");
                msgbox(w, f->isdir[i] ? "Delete Folder" : "Delete File", tbuf, 1, A_DELETE);
            }
        }
        else if (item == 3 && f->n) inputbox(w, "Rename", "New name:", ename(f, f->sel), A_RENAME);
        else if (item == 4 && f->n && f->sel >= 0 && f->sel < f->n && !f->isdir[f->sel]) {
            // the IDE's Code tab, for a compiled file (edit.c knows one by its header)
            join(tbuf, f->path, ename(f, f->sel));
            edit_open(tbuf);
        }
        else if (item == 5 && f->n && f->sel >= 0 && f->sel < f->n) {
            // to the web page, which saves it where the browser keeps
            // downloads, a folder as a tar: persist's download (/bin/download).
            // The desktop waits for it, as it does for persist save
            join(path, f->path, ename(f, f->sel));
            av[0] = "download"; av[1] = path; av[2] = 0;
            if ((pid = spawn("/bin/download", 2, av)) < 0 || uwait(pid) != 0)
                msgbox(w, "Download", "It could not be downloaded: only the web page takes downloads.", 0, A_NONE);
        }
        else if (item == 7) win_close(win_index(w));
    } else if (menu == 1) {
        if (item == 0) { load(f); tree_load(f); }
        else if (item >= V_SORT && item < V_SORT + N_SORTS) set_sort((item - V_SORT) * 2 + (theme_sort() & 1));
        else if (item == V_ASC || item == V_DESC) set_sort(theme_sort() / 2 * 2 + (item == V_DESC));
    }
    else if (menu == 2) up(w);
}

void files_answer(struct win *w, int action, int yes) {
    struct files *f;
    char path[256];
    int i, bad;
    f = F(w);
    if (!yes) return;
    if (action == A_DELETE && f->n) {
        // every item selected, a folder with all in it
        bad = 0;
        i = 0;
        while (i < f->n) {
            if (f->mark[i]) {
                join(path, f->path, ename(f, i));
                if (f->isdir[i]) bad = bad + del_tree(path);
                else if (uunlink(path) < 0) ++bad;
            }
            ++i;
        }
        if (bad) {
            ui_num(tbuf, bad);
            ui_cat(tbuf, bad == 1 ? " item could not be deleted: in use, or part of the disk." : " items could not be deleted: in use, or part of the disk.");
            msgbox(w, "Error Deleting", tbuf, 0, A_NONE);
        }
        load(f); tree_load(f);
    } else if (action == A_RENAME && f->n) {
        join(path, f->path, ename(f, f->sel));
        if (urename(path, dialog_text()) < 0) msgbox(w, "Error Renaming", "Cannot rename: that name is taken or not allowed.", 0, A_NONE);
        load(f); tree_load(f);
    } else if (action == A_NEWDIR) {
        join(path, f->path, dialog_text());
        if (umkdir(path) < 0) msgbox(w, "Error", "Cannot create that folder.", 0, A_NONE);
        load(f); tree_load(f);
    }
}
// hl.c -- the IDE's syntax colouring (edit.c): what each character of a
// line is, for C and JavaScript, Lisp, Forth, shell scripts and Makefiles,
// and B4KE build files. A module of its own since edit.c grew past what
// C4IX's compiler can hold at once (docs/c4ix-desktop.md, part twenty).
//
// Each line is coloured on its own, character by character, into hlc;
// the one thing carried from line to line is being inside a C comment.

#include "desktop.h"

static int hlc[HL_MAX];

static int hl_isword(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

// The language a file's name says it is
int hl_lang(char *p) {
    if (ui_ends(p, ".c") || ui_ends(p, ".h")) return L_C;
    if (ui_ends(p, ".js") || ui_ends(p, ".mjs")) return L_JS;
    if (ui_ends(p, ".lisp") || ui_ends(p, ".scm") || ui_ends(p, ".el")) return L_LISP;
    if (ui_ends(p, ".f") || ui_ends(p, ".fs") || ui_ends(p, ".fth") || ui_ends(p, ".4th")) return L_FORTH;
    if (ui_ends(p, ".sh") || ui_ends(p, "Makefile") || ui_ends(p, ".mk")) return L_SH;
    if (ui_ends(p, ".b4k") || ui_ends(p, ".B4K")) return L_B4K;
    return L_TEXT;
}

// Is S[0..N) one of LIST's words? LIST has a space before each word and
// after the last.
int hl_inwords(char *s, int n, char *list) {
    int i, k;
    i = 0;
    while (list[i]) {
        if (list[i] == ' ' && list[i + 1]) {
            k = 0;
            while (k < n && list[i + 1 + k] == s[k]) ++k;
            if (k == n && list[i + 1 + k] == ' ') return 1;
        }
        ++i;
    }
    return 0;
}

static void hl_paint(int i, int j, int c) {
    while (i < j && i < HL_MAX) { hlc[i] = c; ++i; }
}

static char *c_kw = " if else while for do switch case default break continue return goto sizeof typedef struct union enum static extern const volatile register inline restrict ";
static char *c_ty = " int char short long unsigned signed void float double ";
static char *js_kw = " function var let const if else for while do return new class this null true false undefined import export from of in typeof instanceof await async break continue switch case default throw try catch finally delete yield ";
static char *lisp_kw = " define lambda if begin let let* letrec set! cond else and or not quote next define-macro when unless do case ";
static char *forth_kw = " IF ELSE THEN BEGIN WHILE REPEAT UNTIL AGAIN DO ?DO LOOP +LOOP LEAVE UNLOOP EXIT ; : VARIABLE CONSTANT VALUE CREATE DOES> RECURSE DEFER IS TO CASE OF ENDOF ENDCASE IMMEDIATE POSTPONE ['] [CHAR] LITERAL :NONAME {: :} :M ;M ";
static char *sh_kw = " if then else elif fi for in do done while until case esac function return export local set exit break continue shift ";

// a string from I (its quote) to its end, \ escapes skipped
static int hl_strend(char *s, int n, int i) {
    int q;
    q = s[i];
    ++i;
    while (i < n && s[i] != q) { if (s[i] == 92) ++i; ++i; }
    return i < n ? i + 1 : n;
}

// C and JavaScript; ST 1 is inside /* */
static int hl_c(char *s, int n, int st, int js) {
    int i, j, c, nb;
    i = 0; nb = 0;
    while (i < n) {
        c = s[i];
        if (st == 1) {
            j = i;
            while (j < n && !(s[j] == '*' && j + 1 < n && s[j + 1] == '/')) ++j;
            if (j < n) { j = j + 2; st = 0; }
            hl_paint(i, j, HC_COM); i = j;
        } else if (c == '/' && i + 1 < n && s[i + 1] == '/') { hl_paint(i, n, HC_COM); i = n; }
        else if (c == '/' && i + 1 < n && s[i + 1] == '*') { hl_paint(i, i + 2, HC_COM); i = i + 2; st = 1; }
        else if (c == '"' || c == 39 || (js && c == '`')) { j = hl_strend(s, n, i); hl_paint(i, j, HC_STR); i = j; }
        else if (!js && c == '#' && !nb) {
            j = i + 1;
            while (j < n && s[j] == ' ') ++j;
            while (j < n && hl_isword(s[j])) ++j;
            hl_paint(i, j, HC_PRE); i = j;
        } else if (c >= '0' && c <= '9' && (i == 0 || !hl_isword(s[i - 1]))) {
            j = i;
            while (j < n && (hl_isword(s[j]) || s[j] == '.')) ++j;
            hl_paint(i, j, HC_NUM); i = j;
        } else if (hl_isword(c)) {
            j = i;
            while (j < n && hl_isword(s[j])) ++j;
            if (hl_inwords(s + i, j - i, js ? js_kw : c_kw)) hl_paint(i, j, HC_KW);
            else if (!js && hl_inwords(s + i, j - i, c_ty)) hl_paint(i, j, HC_TYPE);
            i = j;
        } else ++i;
        if (c != ' ' && c != 9) nb = 1;
    }
    return st;
}

static int hl_lispword(int c) { return c > ' ' && c != '(' && c != ')' && c != '"' && c != ';' && c != 39; }
static void hl_lisp(char *s, int n) {
    int i, j, c;
    i = 0;
    while (i < n) {
        c = s[i];
        if (c == ';') { hl_paint(i, n, HC_COM); i = n; }
        else if (c == '"') { j = hl_strend(s, n, i); hl_paint(i, j, HC_STR); i = j; }
        else if (hl_lispword(c)) {
            j = i;
            while (j < n && hl_lispword(s[j])) ++j;
            if ((c >= '0' && c <= '9') || (c == '-' && j > i + 1 && s[i + 1] >= '0' && s[i + 1] <= '9') || c == '#')
                hl_paint(i, j, HC_NUM);
            else if (hl_inwords(s + i, j - i, lisp_kw)) hl_paint(i, j, HC_KW);
            i = j;
        } else ++i;
    }
}

// Forth: blank-separated words, case not mattering; \ and ( comment, S" ." C"
// ABORT" take a string, and : the name it defines
static void hl_forth(char *s, int n) {
    int i, j, k, c, def;
    char up[24];
    i = 0; def = 0;
    while (i < n) {
        if (s[i] == ' ' || s[i] == 9) { ++i; }
        else {
            j = i;
            while (j < n && s[j] != ' ' && s[j] != 9) ++j;
            k = 0;
            while (k < j - i && k < 23) { c = s[i + k]; up[k] = c >= 'a' && c <= 'z' ? c - 32 : c; ++k; }
            if (j - i == 1 && s[i] == 92) { hl_paint(i, n, HC_COM); j = n; }
            else if (j - i == 1 && s[i] == '(') {
                k = j; while (k < n && s[k] != ')') ++k;
                if (k < n) ++k;
                hl_paint(i, k, HC_COM); j = k;
            } else if (j - i <= 23 && j > i && s[j - 1] == '"' && (j - i == 2 || (j - i == 6 && up[0] == 'A'))) {
                hl_paint(i, j, HC_KW);
                k = j + 1; while (k < n && s[k] != '"') ++k;
                if (k < n) ++k;
                hl_paint(j, k, HC_STR); j = k;
            } else if (def) { hl_paint(i, j, HC_TYPE); def = 0; }
            else if ((s[i] >= '0' && s[i] <= '9') || (s[i] == '-' && j > i + 1 && s[i + 1] >= '0' && s[i + 1] <= '9'))
                hl_paint(i, j, HC_NUM);
            else if (j - i <= 23 && hl_inwords(up, j - i, forth_kw)) {
                hl_paint(i, j, HC_KW);
                if (j - i == 1 && s[i] == ':') def = 1;
            }
            i = j;
        }
    }
}

// shell, Makefiles and B4KE: # comments, quotes, $variables; a B4KE line's
// first word, in capitals, is its directive
static void hl_sh(char *s, int n, int b4k) {
    int i, j, c, first;
    i = 0; first = 1;
    while (i < n) {
        c = s[i];
        if (c == '#' && (i == 0 || s[i - 1] == ' ' || s[i - 1] == 9)) { hl_paint(i, n, HC_COM); i = n; }
        else if (c == '"' || c == 39) { j = hl_strend(s, n, i); hl_paint(i, j, HC_STR); i = j; first = 0; }
        else if (c == '$') {
            j = i + 1;
            if (j < n && (s[j] == '{' || s[j] == '(')) { c = s[j] == '{' ? '}' : ')'; while (j < n && s[j] != c) ++j; if (j < n) ++j; }
            else { while (j < n && hl_isword(s[j])) ++j; }
            hl_paint(i, j, HC_TYPE); i = j; first = 0;
        } else if (hl_isword(c)) {
            j = i;
            while (j < n && hl_isword(s[j])) ++j;
            if (b4k && first && c >= 'A' && c <= 'Z') hl_paint(i, j, HC_KW);
            else if (!b4k && hl_inwords(s + i, j - i, sh_kw)) hl_paint(i, j, HC_KW);
            else if (c >= '0' && c <= '9') hl_paint(i, j, HC_NUM);
            i = j; first = 0;
        } else { if (c != ' ' && c != 9) first = 0; ++i; }
    }
}

// Colour N characters of S as language LANG; ST is the state at its start
// (1: inside a C comment), and the state at its end comes back. hl_at
// then says what each character is (HC_*).
int hl_line(char *s, int n, int st, int lang) {
    hl_paint(0, n, HC_TEXT);
    if (lang == L_C || lang == L_JS) return hl_c(s, n, st, lang == L_JS);
    if (lang == L_LISP) hl_lisp(s, n);
    else if (lang == L_FORTH) hl_forth(s, n);
    else if (lang == L_SH || lang == L_B4K) hl_sh(s, n, lang == L_B4K);
    return 0;
}
int hl_at(int i) { return i < HL_MAX ? hlc[i] : HC_TEXT; }
// host.c -- what the window kit asks of its host (winkit.h), from C4IX:
// memory from the kernel, and files in its filesystem.

#include "desktop.h"

// libc's fp.c (the Calculator's conversions) sets errno; the desktop has
// no libc to own one
int errno;

char *wk_alloc(int n) {
    char *p;
    if (n <= 0) n = 1;
    if ((p = (char *)ualloc(n))) memset(p, 0, n);
    return p;
}
void wk_free(char *p) { if (p) free(p); }

int wk_fopen(char *path, int wr) { return uopen(path, wr ? O_WR | O_CREATE | O_TRUNCATE : O_RD); }
int wk_fread(int fd, char *buf, int n) { return uread(fd, buf, n); }
int wk_fwrite(int fd, char *buf, int n) { return write(fd, buf, n); }
void wk_fclose(int fd) { uclose(fd); }
int wk_readdir(char *dir, int i, char *name) { return ureaddir(dir, i, name); }
// shell.c -- the C4IX desktop's shell, over the window kit (src/winkit).
// docs/c4ix-desktop.md.
//
// It owns the display: it takes it from the kernel, attaches the rings,
// and runs the loop that reads events, keeps the windows' programs going
// and draws. It draws what is the desktop's own -- its picture and icons
// under the windows, the taskbar and the Go menu over them -- and keeps
// Settings' choices in /etc/desktop.cfg. The windows are the kit's.
// The taskbar's tray has the volume: the sound card's master, which
// every program's sound goes through (libjs/guest/snd.h).

#include "desktop.h"
#define printf uprintf
#include "wkgui.h"

enum { START_W = 200, N_ICONS = 6 };
// the sound card's master volume (libjs/guest/snd.h), written here and
// not through snd.c: the desktop is linked whole by the host's Makefile
// too, without the card's functions
enum { SND_MASTER = 0x4bc, SND_MUTE = 256, C4I_SND = 0x8000 };
static int running;
static int vol_open, vol_drag;
static int icon_t, icon_k;
static int cpu_shown, cpu_n;
static int frame_waiting;          // a program's framebuffer frame (term.c): no 25 ms wait

void mark_frame() { frame_waiting = 1; }
static char tbuf[128];

// ---- Settings' choices -------------------------------------------------------
//
// The colour scheme (the kit's), the desktop's own colour, its picture, the
// screen saver and its wait, the look, the screen's size, the volume, and
// the interface's font; and the order Files lists in.
static int swatches[8] = { 0x008080, 0x000040, 0x000000, 0x3a4a5a, 0x205030, 0x502850, 0xa09070, 0x606060 };
enum { T_MODERN = 8 };
static int cur_scheme, cur_bg;
static int cur_wall;               // the picture (wall.c) under everything, or the colour
static int cur_saver, cur_wait;    // the screen saver (savers.c, 0 none) and after how many minutes
static int cur_sort;               // Files' order: SORT_* * 2, plus 1 for descending
static int cur_tree = 180;         // Files' folder tree: its width (its splitter)
// The sizes offered: the window kit lays itself out at any of them, and
// the page scales the display to its pane. 640x480 still fits Settings,
// the Go menu and the desktop's icons.
enum { N_SIZES = 3 };
static int size_w[N_SIZES] = { 640, 800, 1024 }, size_h[N_SIZES] = { 480, 600, 768 };
static char *size_names[N_SIZES] = { "640x480", "800x600", "1024x768" };
static int cur_size;
static int cur_vol, cur_mute;      // the volume, 0-100 as the tray shows it, and muted
static int cur_font, cur_fsize;    // the interface's face and size (the kit's, wk_font_use)

static void theme_init() {
    cur_scheme = T_MODERN; cur_bg = 0 - 1; cur_wall = 1; cur_saver = 1; cur_wait = 5; wk.style = S_FLAT;
    cur_size = 1; cur_vol = 100; cur_mute = 0; cur_font = 0; cur_fsize = 1;
}
static void theme_apply() { wk_scheme_use(cur_scheme, cur_bg); wk_font_use(cur_font, cur_fsize); }
int theme_count() { return wk_scheme_count(); }
char *theme_name(int i) { return wk_scheme_name(i); }
int theme_scheme() { return cur_scheme; }
int theme_bg() { return cur_bg; }
int theme_wall() { return cur_wall; }
int theme_saver() { return cur_saver; }
int theme_wait() { return cur_wait; }
int theme_sort() { return cur_sort; }
int theme_tree() { return cur_tree; }
int theme_font() { return cur_font; }
int theme_fsize() { return cur_fsize; }
int theme_swatch(int i) { return i >= 0 && i < 8 ? swatches[i] : 0; }

// /etc/desktop.cfg: "scheme N bg V wall W saver S wait M style L sort O
// res W H vol V mute M font F fsize Z tree T", read
// when the desktop starts, so a choice outlives Power Off (and, with
// persist, a reload of the page). Read into a buffer longer than any
// file it takes, zeroed, so looking a few bytes ahead stays inside it.
static char cfg[160];
static int cfg_num(char *s, int *v) {
    int n, neg, k;
    n = 0; neg = 0; k = 0;
    if (s[0] == '-') { neg = 1; ++s; ++k; }
    while (*s >= '0' && *s <= '9') { n = n * 10 + (*s - '0'); ++s; ++k; }
    *v = neg ? 0 - n : n;
    return k;
}
static void theme_load() {
    int fd, n, i, v, h, k;
    if ((fd = uopen("/etc/desktop.cfg", O_RD)) < 0) return;
    memset(cfg, 0, 160);
    n = uread(fd, cfg, 143);
    uclose(fd);
    if (n <= 0) return;
    cfg[n] = 0;
    i = 0;
    while (i < n) {
        if (cfg[i] == 's' && cfg[i + 1] == 'c' && cfg[i + 6] == ' ') {
            cfg_num(cfg + i + 7, &v);
            if (v >= 0 && v < wk_scheme_count()) cur_scheme = v;
        }
        if (cfg[i] == 'b' && cfg[i + 1] == 'g' && cfg[i + 2] == ' ') { cfg_num(cfg + i + 3, &v); cur_bg = v; }
        if (cfg[i] == 'w' && cfg[i + 1] == 'a' && cfg[i + 2] == 'l' && cfg[i + 4] == ' ') { cfg_num(cfg + i + 5, &v); cur_wall = v != 0; }
        if (cfg[i] == 's' && cfg[i + 1] == 'a' && cfg[i + 5] == ' ') { cfg_num(cfg + i + 6, &v); if (v >= 0 && v < saver_count()) cur_saver = v; }
        if (cfg[i] == 's' && cfg[i + 1] == 't' && cfg[i + 5] == ' ') { cfg_num(cfg + i + 6, &v); if (v >= 0 && v < N_STYLES) wk.style = v; }
        if (cfg[i] == 'w' && cfg[i + 1] == 'a' && cfg[i + 2] == 'i' && cfg[i + 4] == ' ') { cfg_num(cfg + i + 5, &v); if (v >= 1 && v <= 60) cur_wait = v; }
        if (cfg[i] == 's' && cfg[i + 1] == 'o' && cfg[i + 4] == ' ') { cfg_num(cfg + i + 5, &v); if (v >= 0 && v < N_SORTS * 2) cur_sort = v; }
        if (cfg[i] == 'r' && cfg[i + 1] == 'e' && cfg[i + 2] == 's' && cfg[i + 3] == ' ') {
            k = cfg_num(cfg + i + 4, &v);
            cfg_num(cfg + i + 5 + k, &h);
            k = 0;
            while (k < N_SIZES) { if (size_w[k] == v && size_h[k] == h) cur_size = k; ++k; }
        }
        if (cfg[i] == 'v' && cfg[i + 1] == 'o' && cfg[i + 2] == 'l' && cfg[i + 3] == ' ') { cfg_num(cfg + i + 4, &v); if (v >= 0 && v <= 100) cur_vol = v; }
        if (cfg[i] == 'm' && cfg[i + 1] == 'u' && cfg[i + 4] == ' ') { cfg_num(cfg + i + 5, &v); cur_mute = v != 0; }
        if (cfg[i] == 'f' && cfg[i + 1] == 'o' && cfg[i + 4] == ' ') { cfg_num(cfg + i + 5, &v); if (v >= 0 && v < WK_FACES) cur_font = v; }
        if (cfg[i] == 'f' && cfg[i + 1] == 's' && cfg[i + 5] == ' ') { cfg_num(cfg + i + 6, &v); if (v >= 0 && v < WK_SIZES) cur_fsize = v; }
        if (cfg[i] == 't' && cfg[i + 1] == 'r' && cfg[i + 4] == ' ') { cfg_num(cfg + i + 5, &v); if (v >= 100 && v < 2000) cur_tree = v; }
        ++i;
    }
    theme_apply();
}
static void theme_save() {
    int fd;
    umkdir("/etc");
    if ((fd = uopen("/etc/desktop.cfg", O_WR + O_CREATE + O_TRUNCATE)) < 0) return;
    ui_cpy(cfg, "scheme ");
    ui_num(cfg + ui_len(cfg), cur_scheme);
    ui_cat(cfg, " bg ");
    if (cur_bg < 0) ui_cat(cfg, "-1"); else ui_num(cfg + ui_len(cfg), cur_bg);
    ui_cat(cfg, cur_wall ? " wall 1 saver " : " wall 0 saver ");
    ui_num(cfg + ui_len(cfg), cur_saver);
    ui_cat(cfg, " wait ");
    ui_num(cfg + ui_len(cfg), cur_wait);
    ui_cat(cfg, " style ");
    ui_num(cfg + ui_len(cfg), wk.style);
    ui_cat(cfg, " sort ");
    ui_num(cfg + ui_len(cfg), cur_sort);
    ui_cat(cfg, " res ");
    ui_num(cfg + ui_len(cfg), size_w[cur_size]);
    ui_cat(cfg, " ");
    ui_num(cfg + ui_len(cfg), size_h[cur_size]);
    ui_cat(cfg, " vol ");
    ui_num(cfg + ui_len(cfg), cur_vol);
    ui_cat(cfg, cur_mute ? " mute 1 font " : " mute 0 font ");
    ui_num(cfg + ui_len(cfg), cur_font);
    ui_cat(cfg, " fsize ");
    ui_num(cfg + ui_len(cfg), cur_fsize);
    ui_cat(cfg, " tree ");
    ui_num(cfg + ui_len(cfg), cur_tree);
    ui_cat(cfg, "\n");
    write(fd, cfg, ui_len(cfg));
    uclose(fd);
}
void theme_set(int scheme, int bg) {
    if (scheme >= 0 && scheme < wk_scheme_count()) cur_scheme = scheme;
    cur_bg = bg;
    cur_wall = 0;
    theme_apply();
    theme_save();
    wk_redraw_all();
}
// the picture on or off; the colour stays what it was
void theme_set_wall(int on) {
    cur_wall = on != 0;
    theme_save();
    wk_redraw_all();
}
void theme_set_style(int style) {
    wk.style = style >= 0 && style < N_STYLES ? style : S_FLAT;
    theme_save();
    wk_redraw_all();
}
// Files' order, kept as the rest are; each Files window sorts its own list
void theme_set_sort(int sort) {
    if (sort >= 0 && sort < N_SORTS * 2) cur_sort = sort;
    theme_save();
}
// Files' folder tree dragged to a width: the one a Files window opens with
void theme_set_tree(int w) {
    if (w >= 100 && w < 2000) cur_tree = w;
    theme_save();
}
void theme_set_saver(int which, int wait) {
    if (which >= 0 && which < saver_count()) cur_saver = which;
    if (wait >= 1 && wait <= 60) cur_wait = wait;
    theme_save();
    wk_redraw_all();
}

// The interface's font: the face and size the kit draws F_SANS and F_BOLD in
void theme_set_font(int face, int size) {
    if (face >= 0 && face < WK_FACES) cur_font = face;
    if (size >= 0 && size < WK_SIZES) cur_fsize = size;
    theme_apply();
    theme_save();
    wk_redraw_all();
}

// The screen's size: asked of the display now (the page sizes its canvas,
// the kit lays the windows out again, the picture is stretched to it)
int display_count() { return N_SIZES; }
char *display_name(int i) { return i >= 0 && i < N_SIZES ? size_names[i] : ""; }
int display_cur() { return cur_size; }
void display_set(int i) {
    if (i < 0 || i >= N_SIZES) return;
    cur_size = i;
    theme_save();
    if (wk.sw != size_w[i] || wk.sh != size_h[i]) wk_screen(size_w[i], size_h[i]);
    wk_redraw_all();
}

// The volume, to the sound card: its master, 0-255, from the tray's
// 0-100 squared, so the slider's middle sounds about half as loud
static void volume_apply() {
    int v;
    if (!(__c4_info() & C4I_SND)) return;
    v = cur_vol * cur_vol * 255 / 10000;
    *(int *)SND_MASTER = cur_mute ? v | SND_MUTE : v;
}

// Settings' Preview: the saver now, past the click that asked for it
static int saver_grace;
void saver_preview() {
    if (!cur_saver) return;
    saver_start(cur_saver);
    saver_grace = __time() + 150;
}

// ---- the desktop: its picture, and its icons ----------------------------------------

static char *icon_labels[N_ICONS] = { "Filesystem", "Terminal", "Text Editor", "IDE", "Calculator", "System Monitor" };
static int icon_kinds[N_ICONS] = { 0, K_TERM, K_NOTE, K_EDIT, K_CALC, K_TASKS };

static void icon(int x, int y, char *label, int kind) {
    int lw;
    if (kind == 0) {                               // Filesystem
        gui_rect(x + 10, y, 28, 20, C_FACE); d_bevel(x + 10, y, 28, 20, B_RAISED);
        gui_rect(x + 13, y + 3, 22, 14, 0x008080);
        gui_rect(x + 8, y + 22, 32, 8, C_FACE); d_bevel(x + 8, y + 22, 32, 8, B_RAISED);
    } else if (kind == K_TERM) {
        gui_rect(x + 8, y, 32, 26, C_FACE); d_bevel(x + 8, y, 32, 26, B_RAISED);
        gui_rect(x + 11, y + 3, 26, 18, C_DARK);
        gui_text2(x + 13, y + 5, 0xc0c0c0, 10, F_MONO, 0, ">_", 2);
        gui_rect(x + 12, y + 28, 24, 3, C_FACE);
    } else {
        gui_rect(x + 14, y + 4, 20, 24, C_WHITE); gui_recto(x + 14, y + 4, 20, 24, C_SHADOW);
        if (kind == K_NOTE) { gui_rect(x + 17, y + 10, 14, 1, 0x4060c0); gui_rect(x + 17, y + 14, 14, 1, 0x4060c0); gui_rect(x + 17, y + 18, 10, 1, 0x4060c0); }
        else d_icon(kind, x + 16, y + 8);
    }
    lw = ui_len(label) * 6;
    // over the picture, a shadow to read it by
    if (wall_shown()) d_text(x + 25 - lw / 2, y + 37, 0x000000, F_SANS, label);
    d_text(x + 24 - lw / 2, y + 36, C_LIGHT, F_SANS, label);
}

// under the windows: the picture (or the colour, when only the damage is
// drawn; a whole redraw has cleared to it), then the icons that reach in
static void desktop(int x, int y, int w, int h) {
    int k;
    if (!wall_draw(x, y, w, h) && wk_part) gui_rect(x, y, w, h, C_DESK);
    k = 0;
    while (k < N_ICONS) {
        // an icon's label is centred under it and can be wider than it
        if (wk_in_damage(0, 14 + k * 72, 80, 52)) icon(18, 14 + k * 72, icon_labels[k], icon_kinds[k]);
        ++k;
    }
}

// ---- the Go menu: a banner down the left, then the tools -----------------------------
//
// A row starts something, or opens another menu beside it: Games, and in
// that a group of games. The tools are listed here. The games list
// themselves in /etc/desktop.apps (games/README.md).

enum { GO_RUN = 0 - 1, GO_OFF = 0 - 2, GO_CMD = 0 - 3 };
enum { M_GO, M_GAMES, M_GROUPS, N_MENUS = 12, N_GAMES = 128, APPS_MAX = 8192, GO_ROW = 26, GO_DEPTH = 3 };
struct go_item { char *label; int kind; int opens; char *cmd; int menu; };
static struct go_item start_items[] = {
    { "Terminal", K_TERM }, { "Files", K_FILES }, { "Text Editor", K_NOTE }, { "IDE", K_EDIT },
    { "Calculator", K_CALC }, { "System Monitor", K_TASKS }, { "Settings", K_SETTINGS },
    { "About C4IX", K_ABOUT }, { "-", 0 },
    { "Games", 0, M_GAMES }, { "Run...", GO_RUN }, { "-", 0 }, { "Power Off...", GO_OFF }
};
static int n_start;
// The rows of every menu but Go, each menu's together (games_load)
static struct go_item game_items[N_GAMES];
static int n_games, n_menus;
static int menu_first[N_MENUS], menu_n[N_MENUS];

static struct go_item *menu_items(int m) { return m ? &game_items[menu_first[m]] : start_items; }
static int menu_count(int m) { return m ? menu_n[m] : n_start; }

// the field at s ends at the next |: the one after it, or 0 if this was the last
static char *next_field(char *s) {
    while (*s && *s != '|') ++s;
    if (!*s) return 0;
    *s = 0;
    return s + 1;
}

// A command's program is on the disk: at the path it names, or else by name
// in /usr/games/bin, where a game's programs are (vfs-games.py)
static int program_there(char *cmd) {
    char path[96], *d;
    int k, st[8];
    d = path;
    k = 0;
    while (cmd[k] && cmd[k] != ' ' && cmd[k] != '/') ++k;
    if (cmd[k] != '/') { ui_cpy(path, "/usr/games/bin/"); d = path + ui_len(path); }
    k = 0;
    while (cmd[k] && cmd[k] != ' ' && k < 80) { d[k] = cmd[k]; ++k; }
    d[k] = 0;
    return ustat(path, st) == 0;
}

static void game_add(char *label, int kind, char *cmd, int menu, int opens) {
    struct go_item *it;
    it = &game_items[n_games];
    ++n_games;
    it->label = label; it->kind = kind; it->cmd = cmd; it->menu = menu; it->opens = opens;
}

// the menu of a group of games, new the first time it is named; 0 if there is no room
static int game_group(char *name) {
    int k;
    k = 0;
    while (k < n_games) {
        if (game_items[k].opens && ui_eq(game_items[k].label, name)) return game_items[k].opens;
        ++k;
    }
    if (n_menus == N_MENUS || n_games == N_GAMES) return 0;
    game_add(name, 0, 0, M_GAMES, n_menus);
    ++n_menus;
    return n_menus - 1;
}

// the word w is one of s's, which are separated by spaces
static int has_word(char *s, char *w) {
    int n;
    n = ui_len(w);
    while (*s) {
        while (*s == ' ') ++s;
        if (!memcmp(s, w, n) && (s[n] == 0 || s[n] == ' ')) return 1;
        while (*s && *s != ' ') ++s;
    }
    return 0;
}

// A line of /etc/desktop.apps: CATEGORY|NAME|COMMAND|FLAGS, cut up where it
// is. CATEGORY is Games, or Games/GROUP for a menu of its own within Games.
// Any other category is not this menu's. Nor is a line whose program is not
// on the disk. FLAGS, which may be left out, are words: `window` says the
// program plays in a window of its own, with no Terminal, from here and from
// Files (tools.c, run_command). docs/c4-explorer.md's W2 would add `single`
// to them, and its fields after them.
static void game_line(char *s) {
    char *name, *cmd, *group, *flags;
    int menu;
    if (!(name = next_field(s)) || !(cmd = next_field(name))) return;
    if ((flags = next_field(cmd))) next_field(flags);
    if (flags && cmd[0] && has_word(flags, "window")) desk_window_app(cmd);
    group = s;
    while (*group && *group != '/') ++group;
    if (*group) { *group = 0; ++group; }
    if (!ui_eq(s, "Games") || !name[0] || !cmd[0] || !program_there(cmd)) return;
    menu = group[0] ? game_group(group) : M_GAMES;
    if (menu && n_games < N_GAMES) game_add(name, GO_CMD, cmd, menu, 0);
}

// In a menu, its groups first, then by name
static int game_before(struct go_item *a, struct go_item *b) {
    char *p, *q;
    if (a->menu != b->menu) return a->menu < b->menu;
    if (!a->opens != !b->opens) return a->opens != 0;
    p = a->label; q = b->label;
    while (*p && *p == *q) { ++p; ++q; }
    return (*p & 255) < (*q & 255);
}

static void games_load() {
    struct go_item t;
    char *buf, *s, *e;
    int fd, n, k, j;
    n_menus = M_GROUPS;
    if ((fd = uopen("/etc/desktop.apps", O_RD)) < 0) return;
    if (!(buf = wk_alloc(APPS_MAX))) { uclose(fd); return; }
    n = uread(fd, buf, APPS_MAX - 1);
    uclose(fd);
    s = buf;
    while (n > 0 && *s) {
        e = s;
        while (*e && *e != 10) ++e;
        k = *e;
        *e = 0;
        game_line(s);
        s = k ? e + 1 : e;
    }
    k = 1;
    while (k < n_games) {
        memcpy((char *)&t, (char *)&game_items[k], sizeof(struct go_item));
        j = k;
        while (j > 0 && game_before(&t, &game_items[j - 1])) {
            memcpy((char *)&game_items[j], (char *)&game_items[j - 1], sizeof(struct go_item));
            --j;
        }
        memcpy((char *)&game_items[j], (char *)&t, sizeof(struct go_item));
        ++k;
    }
    k = n_games;
    while (k > 0) { --k; menu_first[game_items[k].menu] = k; ++menu_n[game_items[k].menu]; }
}

// Games is in the menu only where there is one to list
static void start_games() {
    int k, n;
    games_load();
    k = 0;
    n = 0;
    while (k < n_start) {
        if (!start_items[k].opens || menu_n[start_items[k].opens]) {
            start_items[n].label = start_items[k].label;
            start_items[n].kind = start_items[k].kind;
            start_items[n].opens = start_items[k].opens;
            ++n;
        }
        ++k;
    }
    n_start = n;
}

// What is open: Go, then what it opened, each over the last
struct go_panel { int menu, x, y, w, h, rows, colw, hot; };
static struct go_panel go_open[GO_DEPTH];
static int go_depth;               // how many: 0 is the menu shut
static int go_x;                   // where the pointer was

static int start_height() {
    int k, h;
    h = 6; k = 0;
    while (k < n_start) { h = h + (start_items[k].label[0] == '-' ? 8 : GO_ROW); ++k; }
    return h;
}

static void go_start() {
    struct go_panel *p;
    p = &go_open[0];
    p->menu = M_GO; p->hot = 0 - 1;
    p->x = 2; p->w = START_W; p->h = start_height();
    p->y = wk.sh - TASK_H - p->h;
    p->rows = n_start; p->colw = START_W - 29;
    go_depth = 1;
}

// where row k of a menu is: Go's right of its banner and with its rules,
// the others in columns
static void go_row_at(struct go_panel *p, int k, int *x, int *y) {
    int j, t;
    if (p->menu) {
        *x = p->x + 3 + k / p->rows * p->colw;
        *y = p->y + 3 + k % p->rows * GO_ROW;
        return;
    }
    t = p->y + 3;
    j = 0;
    while (j < k) { t = t + (start_items[j].label[0] == '-' ? 8 : GO_ROW); ++j; }
    *x = p->x + 26;
    *y = t;
}

// Open the menu that row k of level l opens, beside that row: as many rows
// as fit above the taskbar to a column, as many columns as that takes, and
// over its parent if the screen has no room to the right.
static void go_flyout(int l, int k) {
    struct go_panel *p, *q;
    struct go_item *items;
    int x, y, n, wide, j, room;
    p = &go_open[l];
    q = &go_open[l + 1];
    q->menu = menu_items(p->menu)[k].opens;
    q->hot = 0 - 1;
    n = menu_count(q->menu);
    items = menu_items(q->menu);
    wide = 0;
    j = 0;
    while (j < n) { if (ui_len(items[j].label) > wide) wide = ui_len(items[j].label); ++j; }
    q->colw = wide * (7 + wk.fsize) + 34;
    room = (wk.sh - TASK_H - 6) / GO_ROW;
    q->rows = n < room ? n : room;
    q->w = (n + q->rows - 1) / q->rows * q->colw + 6;
    q->h = q->rows * GO_ROW + 6;
    go_row_at(p, k, &x, &y);
    q->x = x + p->colw - 1;
    if (q->x + q->w > wk.sw) q->x = wk.sw - q->w;
    if (q->x < 0) q->x = 0;
    q->y = y - 3;
    if (q->y + q->h > wk.sh - TASK_H) q->y = wk.sh - TASK_H - q->h;
    if (q->y < 0) q->y = 0;
    go_depth = l + 2;
}

static void draw_go_panel(struct go_panel *p) {
    struct go_item *items;
    int n, k, x, y, a, rgb;
    char c[2], *banner;
    gui_rect(p->x, p->y, p->w, p->h, C_FACE);
    d_bevel(p->x, p->y, p->w, p->h, B_RAISED);
    if (p->menu == M_GO) {
        gui_rect(p->x + 3, p->y + 3, 22, p->h - 6, ui_style == S_FLAT ? C_TITLE : C_SHADOW);
        c[1] = 0;
        banner = "C4IX";
        k = 0;
        while (k < 4) { c[0] = banner[k]; gui_text2(p->x + 8, p->y + p->h - 30 - (3 - k) * 18, C_WHITE, 16, F_BOLD, 0, c, 1); ++k; }
    }
    items = menu_items(p->menu);
    n = menu_count(p->menu);
    k = 0;
    while (k < n) {
        go_row_at(p, k, &x, &y);
        if (items[k].label[0] == '-') {
            gui_rect(x + 2, y + 3, p->w - 32, 1, C_SHADOW); gui_rect(x + 2, y + 4, p->w - 32, 1, C_LIGHT);
        } else {
            rgb = k == p->hot ? C_WHITE : C_DARK;
            if (k == p->hot) gui_rect(x, y, p->colw, GO_ROW, C_SEL);
            if (items[k].kind > 0) d_icon(items[k].kind, x + 6, y + 5);
            d_text(x + (p->menu == M_GO ? 30 : 10), y + 7, rgb, F_SANS, items[k].label);
            // a row that opens a menu has an arrow at its right
            a = 0;
            while (items[k].opens && a < 5) { gui_rect(x + p->colw - 14 + a, y + 8 + a, 1, 9 - a - a, rgb); ++a; }
        }
        ++k;
    }
}

static void draw_start() {
    int l;
    l = 0;
    while (l < go_depth) { draw_go_panel(&go_open[l]); ++l; }
}

static int go_hit(struct go_panel *p, int px, int py) {
    struct go_item *items;
    int n, k, x, y;
    items = menu_items(p->menu);
    n = menu_count(p->menu);
    k = 0;
    while (k < n) {
        go_row_at(p, k, &x, &y);
        if (items[k].label[0] != '-' && ui_hit(px, py, x, y, p->colw, GO_ROW)) return k;
        ++k;
    }
    return 0 - 1;
}

// the topmost menu at (x, y), or -1
static int go_under(int x, int y) {
    struct go_panel *p;
    int l;
    l = go_depth;
    while (l > 0) {
        --l;
        p = &go_open[l];
        if (ui_hit(x, y, p->x, p->y, p->w, p->h)) return l;
    }
    return 0 - 1;
}

// The pointer moved. Over a row, that row lights, and if it opens a menu the
// menu opens; what any other row had open closes. Except on the way across:
// moving right, over the rows below the one that opened a menu, nothing
// changes, so the menu is still there when the pointer arrives.
static void go_move(int x, int y) {
    struct go_panel *p;
    int l, k, depth, hot;
    l = go_under(x, y);
    if (l < 0) {
        go_x = x;
        p = &go_open[go_depth - 1];
        if (p->hot >= 0) { p->hot = 0 - 1; wk_redraw_all(); }
        return;
    }
    p = &go_open[l];
    k = go_hit(p, x, y);
    if (l < go_depth - 1 && k != p->hot && x > go_x) { go_x = x; return; }
    go_x = x;
    depth = go_depth;
    hot = p->hot;
    if (l < go_depth - 1 && k == hot) {
        // back on the row that opened the next: that one stays, what it opened goes
        go_depth = l + 2;
        if (go_open[l + 1].hot >= 0 || depth != go_depth) { go_open[l + 1].hot = 0 - 1; wk_redraw_all(); }
        return;
    }
    p->hot = k;
    go_depth = l + 1;
    if (k >= 0 && menu_items(p->menu)[k].opens) go_flyout(l, k);
    if (k != hot || depth != go_depth) wk_redraw_all();
}

static void start_pick(struct go_item *it) {
    if (it->kind > 0) launch(it->kind);
    else if (it->kind == GO_RUN) inputbox(0, "Run", "Program to run:", "", A_RUN);
    else if (it->kind == GO_OFF) running = 0;
    else if (it->kind == GO_CMD) run_command(it->cmd);
}

// A press: as a move first (a touch has none before it), then a row that
// starts something does, a row that opens a menu has done, and anywhere else
// shuts the menu.
static void go_press(int x, int y) {
    struct go_item *it;
    int l, k;
    go_x = x;
    go_move(x, y);
    l = go_under(x, y);
    k = l < 0 ? 0 - 1 : go_hit(&go_open[l], x, y);
    it = k < 0 ? 0 : &menu_items(go_open[l].menu)[k];
    if (it && it->opens) return;
    go_depth = 0;
    wk_redraw_all();
    if (it) start_pick(it);
}

// ---- the taskbar ----------------------------------------------------------------------

static int n_buttons() {
    struct win *w;
    int n;
    n = 0; w = win_first();
    while (w) { if (w->used && !w->dialog) ++n; w = w->next; }
    return n;
}
static int button_w() { int n, w; n = n_buttons(); if (!n) return 150; w = (wk.sw - 64 - 178) / n - 4; return w > 150 ? 150 : w; }

// The CPU meter beside the tray: System Monitor's number (tasks_cpu_usage),
// taken every two seconds; a click opens System Monitor on Performance.
// The tray: the volume's speaker, then the clock, in one panel.
enum { CPU_W = 66, TRAY_W = 96 };
static int cpu_x() { return wk.sw - 170; }
static int tray_x() { return wk.sw - 4 - TRAY_W; }

// ---- the volume: the tray's speaker, and the popup it opens ---------------------------
//
// A slider (loud at the top, as Windows has it) and Mute, over the tray.
// Each change goes to the sound card at once; the choice is remembered
// when the popup closes, or when Mute is clicked.
enum { VOL_W = 76, VOL_H = 190, VOL_TOP = 34, VOL_LEN = 100 };
static int vol_x() { return wk.sw - 4 - VOL_W; }
static int vol_y() { return wk.sh - TASK_H - VOL_H; }

// the speaker, 16 by 16 at x, y: its waves by the volume, a red cross muted
static void speaker(int x, int y) {
    gui_rect(x + 1, y + 6, 4, 5, C_DARK);
    gui_rect(x + 5, y + 5, 2, 7, C_DARK);
    gui_rect(x + 7, y + 3, 2, 11, C_DARK);
    if (cur_mute) {
        gui_line(x + 11, y + 5, x + 15, y + 11, 0xd02020); gui_line(x + 11, y + 11, x + 15, y + 5, 0xd02020);
        gui_line(x + 12, y + 5, x + 16, y + 11, 0xd02020); gui_line(x + 12, y + 11, x + 16, y + 5, 0xd02020);
        return;
    }
    if (cur_vol > 0) gui_rect(x + 11, y + 6, 1, 5, C_DARK);
    if (cur_vol > 33) { gui_rect(x + 13, y + 4, 1, 9, C_DARK); gui_rect(x + 12, y + 3, 1, 1, C_DARK); gui_rect(x + 12, y + 13, 1, 1, C_DARK); }
    if (cur_vol > 66) { gui_rect(x + 15, y + 3, 1, 11, C_DARK); gui_rect(x + 14, y + 2, 1, 1, C_DARK); gui_rect(x + 14, y + 14, 1, 1, C_DARK); }
}

static void draw_volume() {
    int x, y, ty, k;
    x = vol_x(); y = vol_y();
    gui_rect(x, y, VOL_W, VOL_H, C_FACE);
    if (ui_style == S_FLAT) gui_recto(x, y, VOL_W, VOL_H, C_SHADOW); else d_bevel(x, y, VOL_W, VOL_H, B_RAISED);
    d_text(x + 16, y + 10, C_DARK, F_BOLD, "Volume");
    // the track, its marks, and the thumb where the volume is
    gui_rect(x + VOL_W / 2 - 2, y + VOL_TOP, 4, VOL_LEN, C_SHADOW);
    gui_rect(x + VOL_W / 2 - 1, y + VOL_TOP + 1, 2, VOL_LEN - 2, C_DARK);
    k = 0;
    while (k <= 10) { gui_rect(x + VOL_W / 2 + 14, y + VOL_TOP + k * VOL_LEN / 10, k % 5 ? 3 : 6, 1, C_SHADOW); ++k; }
    ty = y + VOL_TOP + (100 - cur_vol) * VOL_LEN / 100 - 5;
    gui_rect(x + VOL_W / 2 - 11, ty, 22, 10, ui_style == S_FLAT ? C_TITLE : C_FACE);
    if (ui_style != S_FLAT) d_bevel(x + VOL_W / 2 - 11, ty, 22, 10, B_RAISED);
    ui_num(tbuf, cur_vol);
    ui_cat(tbuf, "%");
    d_text(x + VOL_W / 2 - ui_len(tbuf) * 3, y + VOL_TOP + VOL_LEN + 8, C_DARK, F_SANS, tbuf);
    // Mute: a check box
    k = y + VOL_H - 26;
    gui_rect(x + 12, k, 13, 13, C_WHITE);
    if (ui_style == S_FLAT) gui_recto(x + 12, k, 13, 13, C_SHADOW); else d_bevel(x + 12, k, 13, 13, B_SUNKEN);
    if (cur_mute) {
        gui_line(x + 15, k + 6, x + 17, k + 9, C_DARK); gui_line(x + 17, k + 9, x + 22, k + 3, C_DARK);
        gui_line(x + 15, k + 7, x + 17, k + 10, C_DARK); gui_line(x + 17, k + 10, x + 22, k + 4, C_DARK);
    }
    d_text(x + 31, k, C_DARK, F_SANS, "Mute");
}

// the volume for a point on the slider
static void vol_slide(int y) {
    int v;
    v = 100 - (y - vol_y() - VOL_TOP) * 100 / VOL_LEN;
    if (v < 0) v = 0;
    if (v > 100) v = 100;
    if (v != cur_vol) { cur_vol = v; volume_apply(); wk_redraw_all(); }
}

static void vol_close() {
    vol_open = 0; vol_drag = 0;
    theme_save();
    wk_redraw_all();
}

static void draw_taskbar() {
    int k, i, bx, bw, secs, h, m, f, ty;
    char *p;
    struct win *w;
    ty = wk.sh - TASK_H;
    gui_rect(0, ty, wk.sw, TASK_H, C_FACE);
    gui_rect(0, ty + (ui_style == S_FLAT ? 0 : 1), wk.sw, 1, ui_style == S_FLAT ? C_SHADOW : C_LIGHT);
    gui_rect(2, ty + 4, 56, 22, ui_style == S_FLAT && go_depth ? C_LIGHT : C_FACE);
    if (ui_style != S_FLAT || go_depth) d_bevel(2, ty + 4, 56, 22, go_depth ? B_PRESSED : B_RAISED);
    // C4IX's mark: a cake (C4IX, C4KE -- cakes), its candle lit
    k = ty + 4;
    gui_rect(8, k + 13, 15, 6, 0x8b5a2b);
    gui_rect(8, k + 10, 15, 3, 0xf0a0c8); gui_rect(10, k + 13, 2, 2, 0xf0a0c8); gui_rect(17, k + 13, 2, 3, 0xf0a0c8);
    gui_rect(15, k + 4, 2, 6, 0xf4f4f4); gui_rect(15, k + 1, 2, 3, 0xffb020);
    d_text(28, ty + 9, C_DARK, F_BOLD, "Go");
    f = wk_focus();
    bw = button_w();
    k = 0; w = win_first();
    while (w) {
        i = w->id;
        if (w->used && !w->dialog) {
            bx = 64 + k * (bw + 4);
            if (ui_style == S_FLAT) {
                gui_rect(bx, ty + 4, bw, 22, i == f ? C_LIGHT : C_FACE);
                if (i == f) gui_rect(bx, ty + 24, bw, 2, C_TITLE);
            } else {
                gui_rect(bx, ty + 4, bw, 22, i == f ? 0xe0e0e0 : C_FACE);
                d_bevel(bx, ty + 4, bw, 22, i == f ? B_PRESSED : B_RAISED);
            }
            d_icon(w->kind, bx + 4, ty + 7);
            wk_clip_screen(bx + 22, ty + 4, bw - 26, 22);
            d_text(bx + 24, ty + 9, C_DARK, i == f ? F_BOLD : F_SANS, w->title);
            wk_noclip();
            ++k;
        }
        w = w->next;
    }
    gui_rect(cpu_x(), ty + 4, CPU_W, 22, C_FACE);
    if (ui_style != S_FLAT) d_bevel(cpu_x(), ty + 4, CPU_W, 22, B_SUNKEN);
    gui_rect(cpu_x() + 5, ty + 8, 8, 14, 0x000000);
    h = (cpu_shown * 14 + 50) / 100;
    if (h > 0) gui_rect(cpu_x() + 5, ty + 22 - h, 8, h, 0x00e000);
    ui_cpy(tbuf, "CPU ");
    ui_num(tbuf + 4, cpu_shown);
    ui_cat(tbuf, "%");
    d_text(cpu_x() + 17, ty + 9, C_DARK, F_SANS, tbuf);
    gui_rect(tray_x(), ty + 4, TRAY_W, 22, C_FACE);
    if (ui_style != S_FLAT) d_bevel(tray_x(), ty + 4, TRAY_W, 22, B_SUNKEN);
    if (vol_open && ui_style == S_FLAT) gui_rect(tray_x() + 1, ty + 5, 24, 20, C_LIGHT);
    speaker(tray_x() + 5, ty + 7);
    secs = gui_clock();
    h = secs / 3600; m = (secs / 60) % 60;
    p = tbuf;
    if (h % 12 == 0) { *p = '1'; ++p; *p = '2'; ++p; }
    else { if (h % 12 >= 10) { *p = '1'; ++p; } *p = '0' + (h % 12) % 10; ++p; }
    *p = ':'; ++p; *p = '0' + m / 10; ++p; *p = '0' + m % 10; ++p;
    *p = ' '; ++p; *p = h < 12 ? 'A' : 'P'; ++p; *p = 'M'; ++p; *p = 0;
    d_text(tray_x() + 32, ty + 9, C_DARK, F_SANS, tbuf);
}

// over the windows: the taskbar, and the Go menu while it is open
static void front() {
    if (wk_in_damage(0, wk.sh - TASK_H, wk.sw, TASK_H)) draw_taskbar();
    if (go_depth) draw_start();
    if (vol_open) draw_volume();
}

static int popup() { return go_depth || vol_open; }

// ---- input the shell takes before the windows, and where there are none ----

static int mouse_front(int ev, int x, int y, int b) {
    int k, bw, ty;
    struct win *w;
    ty = wk.sh - TASK_H;
    if (vol_open) {
        if (ev == E_MOVE) {
            if (vol_drag && (b & 1)) vol_slide(y);
            else vol_drag = 0;
            return 1;
        }
        if (ev != E_DOWN) return 0;
        if (ui_hit(x, y, vol_x() + VOL_W / 2 - 12, vol_y() + VOL_TOP - 6, 24, VOL_LEN + 12)) { vol_drag = 1; vol_slide(y); return 1; }
        if (ui_hit(x, y, vol_x() + 8, vol_y() + VOL_H - 30, VOL_W - 12, 20)) {
            cur_mute = !cur_mute; volume_apply(); theme_save(); wk_redraw_all();
            return 1;
        }
        if (ui_hit(x, y, vol_x(), vol_y(), VOL_W, VOL_H)) return 1;
        // elsewhere, the speaker too: the popup closes, and the click goes no further
        vol_close();
        return 1;
    }
    if (ev == E_MOVE) {
        if (!go_depth) return 0;
        go_move(x, y);
        return 1;
    }
    if (ev != E_DOWN) return 0;
    if (go_depth) { go_press(x, y); return 1; }
    if (y < ty) return 0;
    if (wk_modal()) return 1;
    if (ui_hit(x, y, 2, ty + 4, 56, 22)) { go_start(); wk_redraw_all(); return 1; }
    if (ui_hit(x, y, cpu_x(), ty + 4, CPU_W, 22)) { tasks_open_perf(); wk_redraw_all(); return 1; }
    if (ui_hit(x, y, tray_x(), ty + 4, 26, 22)) { vol_open = 1; vol_drag = 0; wk_redraw_all(); return 1; }
    bw = button_w();
    k = 0; w = win_first();
    while (w) {
        if (w->used && !w->dialog) {
            if (ui_hit(x, y, 64 + k * (bw + 4), ty + 4, bw, 22)) {
                if (w->id == wk_focus()) w->min = 1;
                else wk_raise(w->id);
                wk_redraw_all();
                return 1;
            }
            ++k;
        }
        w = w->next;
    }
    return 1;
}

// the desktop icons: a double click opens
static void mouse_desk(int ev, int x, int y, int b) {
    int k, i, t;
    if (ev != E_DOWN) return;
    t = now_ms();
    k = 0 - 1;
    i = 0;
    while (i < N_ICONS) { if (ui_hit(x, y, 14, 12 + i * 72, 56, 64)) k = i; ++i; }
    if (k >= 0 && k == icon_k && t - icon_t < 500) {
        if (icon_kinds[k] == 0) files_open("/"); else launch(icon_kinds[k]);
        icon_k = 0 - 1;
    } else { icon_k = k; icon_t = t; }
}

static int key(int down, int code, int ch, int mods) {
    icon_k = 0 - 1;
    // Ctrl+Shift+Esc: System Monitor, from anywhere
    if (code == KEY_ESC && (mods & M_CTRL) && (mods & M_SHIFT)) { tasks_open(); return 1; }
    if (go_depth && code == KEY_ESC) { go_depth = 0; wk_redraw_all(); return 1; }
    if (vol_open && code == KEY_ESC) { vol_close(); return 1; }
    return 0;
}

static int pointer(int x, int y) { return go_depth || vol_open || y >= wk.sh - TASK_H ? PTR_ARROW : 0 - 1; }

// a dialog no window asked: Run
static void answer(int dialog, int yes) {
    if (dialog == A_RUN && yes && dialog_text()[0]) run_command(dialog_text());
}

// the screen changed size: the taskbar along its new bottom, and the picture stretched again
static void resized() {
    go_depth = 0;
    wk_set_area(0, 0, wk.sw, wk.sh - TASK_H);
    wall_resize();
}

static struct wk_shell shell = {
    .desktop = desktop, .front = front, .popup = popup, .mouse_front = mouse_front,
    .mouse_desk = mouse_desk, .key = key, .pointer = pointer, .answer = answer, .resized = resized
};

// ---- starting and stopping ------------------------------------------------------------

// What changed since boot, kept (persist save) before the machine stops:
// the page keeps it, and the next boot lays it back. Where there is no
// drive to keep it on, persist says so on the console and nothing waits.
static void save_files() {
    char *av[3];
    int pid;
    gui_clear(C_DARK);
    gui_text2(wk.sw / 2 - 120, wk.sh / 2 - 20, 0xffffff, 22, F_BOLD, 0, "Saving your files...", 0 - 1);
    gui_show();
    av[0] = "persist"; av[1] = "save"; av[2] = 0;
    if ((pid = spawn("/bin/persist", 2, av)) > 0) uwait(pid);
}

static void shutdown_screen() {
    gui_clear(C_DARK);
    gui_text2(wk.sw / 2 - 200, wk.sh / 2 - 20, 0xff8c1a, 22, F_BOLD, 0, "C4IX has stopped. You can close this page.", 0 - 1);
    gui_show();
}

// The ring's command half takes the largest frame the desktop sends, one
// of the picture's tiles (wall.c): 128x96 at 1024x768, 48 KB. A frame
// longer than half of it is placed only when the ring's head happens to
// allow (gui_frame), so the half is 128 KB.
// GUI_M_REL: the mouse's motion while it is locked to the display, which
// only a canvas that asked for it (window.h's L) has it be (term.c)
enum { RING = 262144, EVENTS = GUI_M_MOVE | GUI_M_BUTTONS | GUI_M_KEYS | GUI_M_WHEEL | GUI_M_WINDOW | GUI_M_REL };

// The display lets the mouse go, and the kit draws its pointer again
void desk_unlock() { gui_cursor(GUI_PTR_ARROW); wk_repoint(); }

int main(int argc, char **argv) {
    int *region, k, busy, secs, clock_min, last_tick, last_draw, input, start_ms, second_draw;
    int last_input, last_frame, aside, ev[4];

    if (!gui_present()) { printf("desktop: not fitted\n"); return 0; }
    // Run in the background (init --desktop has the console's shell run
    // "desktop &"), the desktop's stdin is a pipe that has ended: sh.c
    // gives a background job no input. The desktop never reads it, but
    // its sleep (SYS_EVWAIT, below) wakes for every pipe it reads, and one
    // at its end is always ready, so the desktop would never sleep. Its
    // stdin becomes its stdout, which is no pipe it reads. Fd 0 stays
    // open: the Terminals' spawns (term.c, start) save and put back 0.
    if (uavail(STDIN) < 0) udup2(STDOUT, STDIN);
    // the display, from the kernel, giving way to a game that asks for it
    // (include/display.h, and "aside" below)
    if (!udisplay_take(DISP_YIELDS)) { printf("desktop: a program has the display\n"); return 1; }
    if (!(region = ualloc(RING))) { printf("desktop: no memory for the display's ring\n"); udisplay_give(); return 1; }
    theme_init();
    theme_apply();                     // the default scheme, unless the file names one
    theme_load();
    // at the size Settings chose: 800x600 unless the file names another
    if (!gui_attach(region, RING, size_w[cur_size], size_h[cur_size])) { printf("desktop: the display refused the ring\n"); udisplay_give(); return 1; }
    // GUI_M_WINDOW too: a resize or a focus change from the page means the
    // canvas may have been cleared, and the scene is drawn again
    gui_events(EVENTS);
    volume_apply();
    n_start = sizeof(start_items) / sizeof(start_items[0]);
    start_games();
    // the kit's Notepad, as this desktop has always called it
    notepad_name = "Text Editor";
    notepad_about = "Text Editor for C4IX: edits text in the RAM filesystem.";
    notepad_home = "/";
    notepad_untitled = "/tmp/untitled.txt";
    notepad_filebox = 1;
    notepad_filter = "All Files (*)|*|Text Documents (*.txt)|*.txt|C Source (*.c;*.h)|*.c;*.h";
    // its Format menu's choices, kept beside the desktop's and the IDE's
    notepad_cfg = "/etc/notepad.cfg";
    umkdir("/etc");
    wk_init(&shell);
    wall_load("/usr/share/splash/c4ix.c4p.gz");
    icon_k = 0 - 1;
    printf("desktop: running on the display. Go > Power Off to come back here.\n");

    term_open(0);
    running = 1; wk_redraw_all();
    clock_min = 0 - 1; last_tick = 0; last_draw = 0;
    start_ms = now_ms(); second_draw = 0;
    last_input = __time(); last_frame = 0;
    aside = 0;
    while (running) {
        busy = 0; input = 0;
        // A game asks for the whole display (wolf3d, include/display.h): give
        // way, between frames, and stand aside until it has gone -- reading
        // the terminals' pipes, so their programs run on, but drawing
        // nothing and reading no events, which go to the game. Then the
        // display again, at the desktop's size, and the whole scene drawn on it.
        if (!aside && udisplay(DISP_STATE, 0) == 1 && udisplay(DISP_YIELD, 0)) aside = 1;
        if (aside) {
            if (udisplay(DISP_STATE, 0) == 2) {
                wk_tick();
                uevwait(100, 0, 1);
                continue;
            }
            aside = 0;
            gui_attach(region, RING, wk.sw, wk.sh);
            gui_events(EVENTS);
            gui_cursor(saver_active() ? GUI_PTR_NONE : GUI_PTR_ARROW);
            wk_repoint();
            wk.mods = 0;
            last_input = __time();
            wk_redraw_all();
        }
        while (gui_poll(ev)) {
            busy = 1; input = 1;
            last_input = __time();
            // a screen saver running: the first key or movement ends it, and
            // goes no further (except while a Preview's click is let go)
            if (saver_active()) {
                if (ev[0] == GUI_EV_RESIZE) { wk_event(ev); continue; }
                if (__time() - saver_grace < 0) continue;
                if (ev[0] == GUI_EV_FOCUS) continue;
                saver_stop();
                gui_cursor(GUI_PTR_ARROW);
                wk_repoint();
                wk_redraw_all();
                continue;
            }
            // the mouse locked to a canvas: its motion and buttons the program's
            if (term_lock_event(ev)) continue;
            wk_event(ev);
        }
        // the first frame, once more half a second in, in case the page was
        // not yet showing the display when it came
        if (!second_draw && now_ms() - start_ms >= 500) { second_draw = 1; wk_redraw_all(); }
        // the windows closed meanwhile freed; the terminals' pipes read; the timers due
        wk_tick();
        term_lock_tick();
        // the CPU meter, every other MACHINE second, and a redraw only when
        // it moved: machine time is what its numbers count (cpustat's ms)
        // and what the desktop sleeps on. Host time runs at another rate
        // whenever the machine is not paced to it.
        if (__time() - last_tick >= 1000) {
            last_tick = __time();
            cpu_n = cpu_n + 1;
            if (cpu_n >= 2) {
                cpu_n = 0;
                k = tasks_cpu_usage();
                if (k != cpu_shown) { cpu_shown = k; wk_dirty_rect(0, wk.sh - TASK_H, wk.sw, TASK_H); }
            }
        }
        secs = gui_clock() / 60;
        if (secs != clock_min) { clock_min = secs; wk_dirty_rect(0, wk.sh - TASK_H, wk.sw, TASK_H); }
        // The screen saver: after cur_wait minutes with no input, and then
        // a frame every SAVER_MS in place of the desktop's own drawing
        if (!saver_active() && cur_saver && __time() - last_input >= cur_wait * 60000) {
            saver_start(cur_saver);
            gui_cursor(GUI_PTR_NONE);
        }
        if (saver_active()) {
            if (__time() - last_frame >= SAVER_MS) {
                saver_frame();
                gui_show();
                last_frame = __time();
            }
            k = SAVER_MS - (__time() - last_frame);
            if (k < 1) k = 1;
            uevwait(k, gui_events_ring(), 0);
            continue;
        }
        // A redraw: the whole scene, or what is damaged. Input gets one at
        // once; a program pouring out text (raycast, top) gets at most one
        // every 25 ms -- it can print far faster than a person can read.
        // A game's frame gets one at once too: it sends the next only when
        // told this one was drawn (wk_drawn), so it cannot flood the
        // desktop, and held back it would be held to 40 frames a second.
        if (wk_dirty() && (input || frame_waiting || __time() - last_draw >= 25)) {
            frame_waiting = 0;
            wk_redraw(0);
            last_draw = __time();
            wk_drawn();                // the frames just shown have been read: their programs may draw again
            busy = 1;
        }
        // Nothing to do: sleep until there is. That is an event (a key, the
        // mouse), output on a terminal's pipe, or the next thing due -- a
        // redraw held back by the 25 ms above, a window's timer, the meter
        // -- and the kernel watches for the first two itself (SYS_EVWAIT).
        // While a redraw is held back the pipes are not watched: a program
        // pouring out text would wake it at once, with nothing to do until
        // the 25 ms are up.
        if (!busy) {
            if (wk_dirty()) k = 25 - (__time() - last_draw);
            else k = 1000 - (__time() - last_tick);
            secs = wk_next_timer();
            if (secs >= 0 && secs < k) k = secs;
            if (!second_draw && k > 100) k = 100;   // the half-second first-frame redraw
            if (k < 1) k = 1;
            uevwait(k, gui_events_ring(), !wk_dirty());
        }
    }

    wk_close_all();
    save_files();
    shutdown_screen();
    gui_detach();
    udisplay_give();
    printf("desktop: shut down\n");
    return 0;
}
// taskmgr.c -- System Monitor: programs, tasks and load. docs/c4ix-desktop.md.
//
// Applications: the desktop's windows (Close, Show, New Task).
// Processes: every C4IX task, from utaskinfo, with the CPU share each
// took over the last second and the memory it holds (Kill). Performance:
// a CPU gauge and a scrolling history, and the memory in use and free.
//
// Memory is the snapshot's too: a task's image, stack, library data and
// what it allocated, and the machine's heap as the host counts it. What
// no task holds -- the files, which are RAM, the shared libraries' code,
// the kernel's own tables -- is System's.
//
// CPU use is cpustat.h's, the same as top's: each second, one snapshot of
// the kernel's accounting, and the share of the machine each task took
// since the last. As NT does it, the kernel's own work -- syscalls and
// switches -- is the System row, not the program's, and the idle task and
// the time the machine napped are idle; CPU usage is
// everything but idle, and the rows add up to 100.
//
// With several CPUs (docs/c4ix-smp.md S4) the machine is all of them, as
// in NT: the usage is their average, the idle row is every CPU's idle
// task together, and Load draws a history for each CPU.

#include "desktop.h"
#include "cpustat.h"

enum { MAXP = CPU_MAXT + 2, HIST = 60, ROW_H = 16, TAB_Y = 6, PAGE_Y = 28, NAMEW = 24,
       CPU_SHOW = 8 };          // histories drawn, at most

struct tasks {
    int tab, sel, top, asel;
    int n;                                     // rows: idle, System, then the tasks
    int id[MAXP], state[MAXP], privs[MAXP], sys[MAXP], cpu[MAXP];
    int on[MAXP];                              // the CPU running it, -1 none (several CPUs)
    int ival[MAXP];                            // Interval: thousands of cycles in the last sample
    int mem[MAXP];                             // bytes held; -1 for the idle row, which shows none
    int heap, heapused;                        // the heap, when the host says (else 0)
    int largest;                               // ... its biggest block, KB (/proc/meminfo)
    int swap, swapfree;                        // swap, KB, 0 if there is none
    int pgin, pgout, held;                     // pages in and out a second, tasks held (mmu.c)
    int swin, swout, swms;                     // the counts as last read, and when
    long long time[MAXP];                      // CPU Time, in cycles
    char name[MAXP * NAMEW];
    struct cpusample s[2];                     // this snapshot and the one before
    int cur;                                   // which of s is the latest
    int usage, hist[HIST], nhist;
    int ncpu, chist[CPU_SHOW * HIST];          // several CPUs: each one's load, HIST apiece
    int mhist[HIST], nmhist;                   // the heap's use, percent, each sample
    int sampled;
    int uptime0;
};

static struct tasks *S(struct win *w) { return (struct tasks *)w->st; }
static char buf[160];
static char *tabs[3];
static int pct[CPU_MAXT];

static int row(struct tasks *t, int id, char *name, int privs, int state, int sys, int cpu, int ival, long long time, int mem) {
    int k;
    k = t->n;
    t->id[k] = id; t->privs[k] = privs; t->state[k] = state; t->sys[k] = sys; t->cpu[k] = cpu;
    t->on[k] = 0 - 1;
    t->ival[k] = ival;
    t->mem[k] = mem;
    t->time[k] = time;
    ui_cpy(t->name + k * NAMEW, name);
    t->name[k * NAMEW + NAMEW - 1] = 0;
    ++t->n;
    return k;
}

// /proc/meminfo's value for NAME in BUF ("name value" lines), 0 if it has none
static char membuf[768];
static int meminfo(char *name) {
    char *p;
    int i, v;
    p = membuf;
    while (*p) {
        i = 0;
        while (name[i] && p[i] == name[i]) ++i;
        if (!name[i] && p[i] == ' ') {
            p = p + i + 1;
            v = 0;
            while (*p >= '0' && *p <= '9') { v = v * 10 + *p - '0'; ++p; }
            return v;
        }
        while (*p && *p != '\n') ++p;
        if (*p) ++p;
    }
    return 0;
}

// What the Load tab shows of swap, only when it is showing: reading the file makes
// the kernel walk every RAM file. The rates are over the time since the last look;
// a long time since (the tab was not showing) is no measure of now.
static void swap_sample(struct tasks *t) {
    int fd, n, got, now, in, out;
    if ((fd = uopen("/proc/meminfo", O_RD)) < 0) return;
    got = 0;
    while (got < 767 && (n = uread(fd, membuf + got, 767 - got)) > 0) got = got + n;
    uclose(fd);
    membuf[got] = 0;
    t->largest = meminfo("largest");
    t->swap = meminfo("swap");
    t->swapfree = meminfo("swapfree");
    t->held = meminfo("held");
    in = meminfo("swapins");
    out = meminfo("swapouts");
    now = __time();
    if (t->swms && now - t->swms > 0 && now - t->swms < 5000) {
        t->pgin = (in - t->swin) * 1000 / (now - t->swms);
        t->pgout = (out - t->swout) * 1000 / (now - t->swms);
    } else { t->pgin = 0; t->pgout = 0; }
    t->swin = in;
    t->swout = out;
    t->swms = now;
}

static void sample(struct tasks *t) {
    struct cpusample *a, *b;
    struct cpustat_task *r;
    int k, sys, nsys, kival, tmem, ip, iv, c;
    long long ktime, it;

    a = &t->s[t->cur];
    b = &t->s[1 - t->cur];
    cpu_sample(b);
    if (t->sampled) t->usage = cpu_shares(a, b, pct, &sys);
    else { k = 0; while (k < CPU_MAXT) { pct[k] = 0; ++k; } sys = 0; t->usage = 0; }
    t->ncpu = b->h.ncpu;

    // the idle task and System first, as NT lists them; System's time is
    // all the kernel has spent on everyone, the reaped included
    t->n = 0;
    // Interval, as top has it: what each row ran in the last sample, in
    // thousands of cycles -- the idle task's own cycles (not its naps),
    // the kernel's for System, a task's own for a task. Several CPUs'
    // idle tasks are one row.
    ip = 0; iv = 0; it = 0;
    k = 0;
    while (k < b->h.ntasks) {
        if (cpu_isidle(b, b->t[k].id)) {
            r = &b->t[k];
            ip = ip + pct[k];
            if (t->sampled) iv = iv + cpu_kdelta(a, b, k, 0) + cpu_kdelta(a, b, k, 1);
            it = it + r->user + r->kernel;
        }
        ++k;
    }
    k = cpu_find(b, b->h.idle);
    if (k >= 0) row(t, b->h.idle, "idle", 0, b->t[k].state, b->t[k].nsyscalls, ip, iv, it, 0 - 1);
    t->heap = b->h.heap;
    t->heapused = b->h.heapused;
    tmem = 0;
    k = 0;
    while (k < b->h.ntasks) { tmem = tmem + b->t[k].mem; ++k; }
    ktime = b->h.gone_kernel;
    nsys = 0;
    kival = 0;
    k = 0;
    while (k < b->h.ntasks) {
        if (!cpu_isidle(b, b->t[k].id)) {
            ktime = ktime + b->t[k].kernel;
            nsys = nsys + b->t[k].nsyscalls;
            if (t->sampled) kival = kival + cpu_kdelta(a, b, k, 1);
        }
        ++k;
    }
    // System holds what no task does, where the heap's use is known
    row(t, -1, "System", 0, TS_RUNNING, nsys, sys, kival, ktime,
        t->heapused > tmem ? t->heapused - tmem : 0 - 1);
    k = 0;
    while (k < b->h.ntasks) {
        r = &b->t[k];
        if (!cpu_isidle(b, r->id)) {
            c = row(t, r->id, r->name, r->privs, r->state, r->nsyscalls, pct[k], t->sampled ? cpu_kdelta(a, b, k, 0) : 0, r->user, r->mem);
            t->on[c] = r->cpu;
        }
        ++k;
    }
    t->cur = 1 - t->cur;
    if (t->sampled) {
        // each CPU's history moves with the machine's, a sample at a time
        c = 0;
        while (c < t->ncpu && c < CPU_SHOW) {
            ip = cpu_load(a, b, c);
            if (t->nhist < HIST) t->chist[c * HIST + t->nhist] = ip;
            else {
                k = 0;
                while (k < HIST - 1) { t->chist[c * HIST + k] = t->chist[c * HIST + k + 1]; ++k; }
                t->chist[c * HIST + HIST - 1] = ip;
            }
            ++c;
        }
        if (t->nhist < HIST) { t->hist[t->nhist] = t->usage; ++t->nhist; }
        else { k = 0; while (k < HIST - 1) { t->hist[k] = t->hist[k + 1]; ++k; } t->hist[HIST - 1] = t->usage; }
    }
    if (t->heap > 0) {
        k = (int)(((long long)t->heapused * 100) / t->heap);
        if (t->nmhist < HIST) { t->mhist[t->nmhist] = k; ++t->nmhist; }
        else { sys = 0; while (sys < HIST - 1) { t->mhist[sys] = t->mhist[sys + 1]; ++sys; } t->mhist[HIST - 1] = k; }
    }
    t->sampled = 1;
    if (t->tab == 2) swap_sample(t);
    if (t->sel >= t->n) t->sel = t->n - 1;
}

int tasks_open() {
    int i, k, info[TASKINFO_WORDS];
    struct win *w;
    // one System Monitor at a time: another request brings it forward
    w = win_first();
    while (w) { if (w->used && w->kind == K_TASKS) { win_raise(w->id); return w->id; } w = w->next; }
    // room for Memory; and on several CPUs, for the CPU column
    i = win_open(K_TASKS, "System Monitor", utaskinfo(0, info) && info[TI_NCPU] > 1 ? 600 : 570, 440, sizeof(struct tasks));
    if (i < 0) return i;
    w = win_get(i);
    S(w)->tab = 1;
    S(w)->uptime0 = __time();
    sample(S(w));
    mark_dirty();
    return i;
}

int tasks_open_perf() {
    int i;
    i = tasks_open();
    if (i >= 0) S(win_get(i))->tab = 2;
    return i;
}

// The sample is taken minimised too, so the history has no gap when the
// window comes back; but a minimised window shows nothing, and redrawing
// the whole scene every second for it was most of what an idle desktop
// cost (docs/c4ix-cpu.md, step 11).
void tasks_tick(struct win *w) {
    sample(S(w));
    mark_win_dirty(w);   // its own window, and nothing for a minimised one
}

// The taskbar's CPU meter: the same sample as the Performance tab, kept
// apart from any System Monitor window, so the two agree and neither
// disturbs the other's deltas.
static struct tasks *bar;
int tasks_cpu_usage() {
    if (!bar) { bar = (struct tasks *)ualloc(sizeof(struct tasks)); memset(bar, 0, sizeof(struct tasks)); }
    sample(bar);
    return bar->usage;
}

static char *state_name(int s) {
    if (s == TS_READY) return "Ready";
    if (s == TS_RUNNING) return "Running";
    if (s == TS_ZOMBIE) return "Exited";
    if (s == TS_WAITING) return "Waiting";
    if (s == TS_BLOCKED) return "Blocked";
    if (s == TS_SLEEPING) return "Sleeping";
    if (s == TS_VFORK) return "Vforked";
    return "?";
}

// ---- drawing ----------------------------------------------------------------------

static int widths[9];
static char *labels[9];

// bytes as the Memory column shows them: "348 K", or "12.4 M"
static void kbytes(char *out, int b) {
    int k, n;
    k = (b + 1023) / 1024;
    if (k < 10000) { ui_num_commas(out, k); ui_cat(out, " K"); return; }
    ui_num_commas(out, k / 1024);
    n = ui_len(out);
    out[n] = '.'; out[n + 1] = '0' + ((k % 1024) * 10) / 1024; out[n + 2] = ' '; out[n + 3] = 'M'; out[n + 4] = 0;
}
// megabytes to one place, for the totals: "16.6"
static void mbytes(char *out, int b) {
    int n, tenths;
    tenths = (int)(((long long)b * 10 + 524288) / 1048576);
    ui_num_commas(out, tenths / 10);
    n = ui_len(out);
    out[n] = '.'; out[n + 1] = '0' + tenths % 10; out[n + 2] = 0;
}

// thousands of cycles, as Interval shows them: "850k", or "12.3M"
static void kcycles(char *out, int kc) {
    int n;
    if (kc < 1000) { ui_num(out, kc); ui_cat(out, "k"); return; }
    ui_num_commas(out, kc / 1000);
    n = ui_len(out);
    out[n] = '.'; out[n + 1] = '0' + (kc % 1000) / 100; out[n + 2] = 'M'; out[n + 3] = 0;
}

static void list_box(int x, int y, int w, int h) {
    d_rect(x, y, w, h, C_WHITE);
    d_bevel(x, y, w, h, B_SUNKEN);
}

static void draw_apps(struct win *me, struct tasks *t, int ox, int oy, int cw, int ch) {
    int k, y, n;
    struct win *w;
    list_box(ox + 8, oy + PAGE_Y + 10, cw - 16, ch - PAGE_Y - 60);
    widths[0] = cw - 20 - 90; widths[1] = 90;
    labels[0] = "Task"; labels[1] = "Status";
    ui_header(ox + 10, oy + PAGE_Y + 12, widths, labels, 2);
    y = oy + PAGE_Y + 32;
    n = 0;
    w = win_first();
    while (w) {
        if (w->used && w->kind != K_MSG && w->kind != K_INPUT) {
            if (n == t->asel) d_rect(ox + 12, y - 1, cw - 26, ROW_H, C_SEL);
            d_icon(w->kind, ox + 14, y - 1);
            d_text(ox + 34, y + 1, n == t->asel ? C_WHITE : C_DARK, F_SANS, w->title);
            d_text(ox + 14 + widths[0], y + 1, n == t->asel ? C_WHITE : C_DARK, F_SANS, "Running");
            y = y + ROW_H + 2;
            ++n;
        }
        w = w->next;
    }
    ui_button(ox + cw - 300, oy + ch - 40, 90, 24, "Close", 0, 0);
    ui_button(ox + cw - 202, oy + ch - 40, 90, 24, "Show", 0, 0);
    ui_button(ox + cw - 104, oy + ch - 40, 90, 24, "Run...", 0, 0);
}

// The Tasks columns. On several CPUs one more, after PID: the CPU running
// each task (docs/c4ix-smp.md S4), and the share becomes "CPU %" beside it.
static void draw_procs(struct tasks *t, int ox, int oy, int cw, int ch) {
    int k, y, x, rows, fg, smp, c;
    list_box(ox + 8, oy + PAGE_Y + 10, cw - 16, ch - PAGE_Y - 60);
    smp = t->ncpu > 1;
    c = 0;
    widths[c] = smp ? 110 : 120; labels[c++] = "Name";
    widths[c] = 40; labels[c++] = "PID";
    if (smp) { widths[c] = 30; labels[c++] = "CPU"; }
    widths[c] = smp ? 40 : 36; labels[c++] = smp ? "CPU %" : "CPU";
    widths[c] = 66; labels[c++] = "Interval";
    widths[c] = 74; labels[c++] = "CPU Time";
    widths[c] = 70; labels[c++] = "Memory";
    widths[c] = 60; labels[c++] = "Syscalls";
    widths[c] = cw - 20 - (smp ? 490 : 466); labels[c++] = "State";
    ui_header(ox + 10, oy + PAGE_Y + 12, widths, labels, c);
    rows = (ch - PAGE_Y - 60 - 26) / ROW_H;
    if (t->sel < t->top) t->top = t->sel;
    if (t->sel >= t->top + rows) t->top = t->sel - rows + 1;
    y = oy + PAGE_Y + 32;
    k = t->top;
    while (k < t->n && k < t->top + rows) {
        fg = k == t->sel ? C_WHITE : C_DARK;
        if (k == t->sel) d_rect(ox + 12, y - 1, cw - 26, ROW_H, C_SEL);
        x = ox + 14;
        c = 0;
        d_text(x, y + 1, fg, F_SANS, t->name + k * NAMEW); x = x + widths[c++];
        buf[0] = 0; if (t->id[k] >= 0) ui_num(buf, t->id[k]);   // System has no PID
        d_text(x + widths[c] - 8 - ui_len(buf) * 6, y + 1, fg, F_SANS, buf); x = x + widths[c++];
        if (smp) {
            buf[0] = 0; if (t->on[k] >= 0) ui_num(buf, t->on[k]);   // running nowhere: blank
            d_text(x + widths[c] - 8 - ui_len(buf) * 6, y + 1, fg, F_SANS, buf); x = x + widths[c++];
        }
        ui_num(buf, t->cpu[k]); if (ui_len(buf) < 2) { buf[1] = buf[0]; buf[0] = '0'; buf[2] = 0; }
        d_text(x + widths[c] - 8 - ui_len(buf) * 6, y + 1, fg, F_SANS, buf); x = x + widths[c++];
        kcycles(buf, t->ival[k]);
        d_text(x + widths[c] - 8 - ui_len(buf) * 6, y + 1, fg, F_SANS, buf); x = x + widths[c++];
        // CPU time: thousands of cycles, or millions once they pass a billion
        if (t->time[k] >= 1000000000) { ui_num_commas(buf, (int)(t->time[k] / 1000000)); ui_cat(buf, "M"); }
        else { ui_num_commas(buf, (int)(t->time[k] / 1000)); ui_cat(buf, "k"); }
        d_text(x + widths[c] - 8 - ui_len(buf) * 6, y + 1, fg, F_SANS, buf); x = x + widths[c++];
        buf[0] = 0; if (t->mem[k] >= 0) kbytes(buf, t->mem[k]);
        d_text(x + widths[c] - 8 - ui_len(buf) * 6, y + 1, fg, F_SANS, buf); x = x + widths[c++];
        ui_num_commas(buf, t->sys[k]); d_text(x + widths[c] - 8 - ui_len(buf) * 6, y + 1, fg, F_SANS, buf); x = x + widths[c++];
        d_text(x + 4, y + 1, fg, F_SANS, state_name(t->state[k]));
        y = y + ROW_H;
        ++k;
    }
    ui_scrollbar(ox + cw - 26, oy + PAGE_Y + 30, ch - PAGE_Y - 82, t->n, rows, t->top);
    ui_button(ox + cw - 104, oy + ch - 40, 90, 24, "Kill", 0, 0);
}

// NT's gauge: green bars on black, lit from the bottom up to the usage.
static void gauge(int x, int y, int w, int h, int pct) {
    int k, n, lit, by;
    d_rect(x, y, w, h, C_DARK);
    n = (h - 22) / 3;
    lit = (n * pct + 50) / 100;
    k = 0;
    while (k < n) {
        by = y + h - 20 - k * 3;
        d_rect(x + 8, by, w / 2 - 10, 2, k < lit ? C_GREEN : 0x004000);
        d_rect(x + w / 2 + 2, by, w / 2 - 10, 2, k < lit ? C_GREEN : 0x004000);
        ++k;
    }
    ui_num(buf, pct); ui_cat(buf, " %");
    d_text(x + w / 2 - ui_len(buf) * 3, y + h - 15, C_GREEN, F_SANS, buf);
}

// a minute of percentages, newest at the right: CPU use, or memory's
static void graph(int *hist, int nhist, int x, int y, int w, int h) {
    int k, gx, px, py, qx, qy;
    d_rect(x, y, w, h, C_DARK);
    k = 1;
    while (k < 5) { d_rect(x, y + (h * k) / 5, w, 1, 0x006000); ++k; }
    gx = (nhist * 12) % 12;
    k = w - 1 - gx;
    while (k > 0) { d_rect(x + k, y, 1, h, 0x006000); k = k - 12; }
    if (nhist < 2) return;
    k = 1;
    while (k < nhist) {
        px = x + w - 1 - (nhist - k) * (w - 2) / (HIST - 1);
        qx = x + w - 1 - (nhist - 1 - k) * (w - 2) / (HIST - 1);
        py = y + h - 2 - (hist[k - 1] * (h - 4)) / 100;
        qy = y + h - 2 - (hist[k] * (h - 4)) / 100;
        d_line(px, py, qx, qy, C_GREEN);
        ++k;
    }
}

// The heap: a bar of what is in use, and the figures. A host that does
// not say how big its heap is (native c4m) gets "not known".
static void memory(struct tasks *t, int x, int y, int w, int h) {
    int fill;
    ui_group(x, y, w, h, "Memory");
    if (t->heap <= 0) { d_text(x + 12, y + 20, C_DARK, F_SANS, "not known on this host"); return; }
    d_rect(x + 12, y + 20, w - 24, 12, C_DARK);
    fill = (int)(((long long)(w - 26) * t->heapused) / t->heap);
    d_rect(x + 13, y + 21, fill, 10, C_GREEN);
    d_text(x + 12, y + 40, C_DARK, F_SANS, "In use (MB)");
    mbytes(buf, t->heapused); d_text(x + w - 16 - ui_len(buf) * 6, y + 40, C_DARK, F_SANS, buf);
    d_text(x + 12, y + 56, C_DARK, F_SANS, "Free (MB)");
    mbytes(buf, t->heap - t->heapused); d_text(x + w - 16 - ui_len(buf) * 6, y + 56, C_DARK, F_SANS, buf);
    d_text(x + 12, y + 72, C_DARK, F_SANS, "Total (MB)");
    mbytes(buf, t->heap); d_text(x + w - 16 - ui_len(buf) * 6, y + 72, C_DARK, F_SANS, buf);
    // free memory in pieces shows here: less than Free is all that can be had at once
    d_text(x + 12, y + 88, C_DARK, F_SANS, "Largest free (MB)");
    mbytes(buf, t->largest * 1024); d_text(x + w - 16 - ui_len(buf) * 6, y + 88, C_DARK, F_SANS, buf);
}

// A figure in a group's row, at its right
static void figure(int x, int y, int w, char *label, int v) {
    d_text(x + 12, y, C_DARK, F_SANS, label);
    ui_num_commas(buf, v);
    d_text(x + w - 16 - ui_len(buf) * 6, y, C_DARK, F_SANS, buf);
}

// Swap: a bar of what is on it, and how fast pages are going: a machine with more
// programs than memory says so here. A host with no swap (no MMU) says how to get
// it, in lines that fit the box's 25 or so characters.
static void swapbox(struct tasks *t, int x, int y, int w, int h) {
    int used, fill;
    ui_group(x, y, w, h, "Swap");
    if (t->swap <= 0) {
        d_text(x + 12, y + 20, C_DARK, F_SANS, "Enable MMU in");
        d_text(x + 12, y + 36, C_DARK, F_SANS, "Configuration for swap.");
        d_text(x + 12, y + 56, C_DARK, F_SANS, "Slight performance");
        d_text(x + 12, y + 72, C_DARK, F_SANS, "penalty in games.");
        return;
    }
    used = t->swap - t->swapfree;
    d_rect(x + 12, y + 20, w - 24, 12, C_DARK);
    fill = (int)(((long long)(w - 26) * used) / t->swap);
    d_rect(x + 13, y + 21, fill, 10, C_GREEN);
    d_text(x + 12, y + 40, C_DARK, F_SANS, "On swap (MB)");
    mbytes(buf, used * 1024); d_text(x + w - 16 - ui_len(buf) * 6, y + 40, C_DARK, F_SANS, buf);
    figure(x, y + 56, w, "Pages in /s", t->pgin);
    figure(x, y + 72, w, "Pages out /s", t->pgout);
    figure(x, y + 88, w, "Tasks held", t->held);
}

static void draw_perf(struct tasks *t, int ox, int oy, int cw, int ch) {
    int gw, secs, k, n, hw, hx;
    struct win *w;
    gw = 90;
    ui_group(ox + 8, oy + PAGE_Y + 8, gw + 16, 130, "CPU Usage");
    gauge(ox + 16, oy + PAGE_Y + 24, gw, 106, t->usage);
    // one history for the machine, or one for each CPU, side by side
    n = t->ncpu > CPU_SHOW ? CPU_SHOW : t->ncpu;
    if (n > 1) {
        ui_num(buf, t->ncpu); ui_cat(buf, " CPUs: Usage History");
        ui_group(ox + gw + 34, oy + PAGE_Y + 8, cw - gw - 42, 130, buf);
        hw = (cw - gw - 58 - (n - 1) * 6) / n;
        k = 0;
        while (k < n) {
            hx = ox + gw + 42 + k * (hw + 6);
            graph(t->chist + k * HIST, t->nhist, hx, oy + PAGE_Y + 24, hw, 106);
            ++k;
        }
    } else {
        ui_group(ox + gw + 34, oy + PAGE_Y + 8, cw - gw - 42, 130, "CPU Usage History");
        graph(t->hist, t->nhist, ox + gw + 42, oy + PAGE_Y + 24, cw - gw - 58, 106);
    }
    // Totals, Memory and Swap, side by side
    gw = (cw - 32) / 3;
    ui_group(ox + 8, oy + PAGE_Y + 150, gw, 106, "Totals");
    figure(ox + 8, oy + PAGE_Y + 170, gw, "Tasks", t->n);
    secs = 0; w = win_first(); while (w) { if (w->used) ++secs; w = w->next; }
    figure(ox + 8, oy + PAGE_Y + 188, gw, "Open windows", secs);
    figure(ox + 8, oy + PAGE_Y + 206, gw, "Up for (seconds)", (__time() - t->uptime0) / 1000);
    memory(t, ox + 16 + gw, oy + PAGE_Y + 150, gw, 106);
    swapbox(t, ox + 24 + 2 * gw, oy + PAGE_Y + 150, gw, 106);
    // the page ends at ch: what is under the totals, if there is room
    if (t->heap > 0 && ch - PAGE_Y > 336) {
        ui_group(ox + 8, oy + PAGE_Y + 266, cw - 16, ch - PAGE_Y - 274, "Memory Usage History");
        graph(t->mhist, t->nmhist, ox + 16, oy + PAGE_Y + 282, cw - 32, ch - PAGE_Y - 298);
    }
}

void tasks_draw(struct win *w, int ox, int oy, int cw, int ch, int focused) {
    struct tasks *t;
    t = S(w);
    tabs[0] = "Programs"; tabs[1] = "Tasks"; tabs[2] = "Load";
    d_rect(ox, oy, cw, ch, C_FACE);
    // the page, then the tabs over its top edge
    d_bevel(ox + 4, oy + PAGE_Y, cw - 8, ch - PAGE_Y - 26, B_RAISED);
    ui_tabs(ox + 8, oy + TAB_Y, tabs, 3, t->tab);
    if (t->tab == 0) draw_apps(w, t, ox, oy, cw, ch - 26);
    else if (t->tab == 1) draw_procs(t, ox, oy, cw, ch - 26);
    else draw_perf(t, ox, oy, cw, ch - 26);
    d_bevel(ox + 2, oy + ch - 22, 120, 20, B_SUNKEN);
    d_bevel(ox + 124, oy + ch - 22, cw - 126, 20, B_SUNKEN);
    ui_cpy(buf, "Processes: "); ui_num(buf + ui_len(buf), t->n);
    d_text(ox + 8, oy + ch - 18, C_DARK, F_SANS, buf);
    ui_cpy(buf, "CPU Usage: "); ui_num(buf + ui_len(buf), t->usage); ui_cat(buf, "%");
    d_text(ox + 130, oy + ch - 18, C_DARK, F_SANS, buf);
    if (t->heap > 0) {
        ui_cpy(buf, "Memory: "); mbytes(buf + ui_len(buf), t->heapused);
        ui_cat(buf, " MB of "); mbytes(buf + ui_len(buf), t->heap); ui_cat(buf, " MB");
        d_text(ox + 250, oy + ch - 18, C_DARK, F_SANS, buf);
    }
}

// ---- input --------------------------------------------------------------------------

// The n'th application window's number, or -1.
static int app_window(int n) {
    int i;
    struct win *w;
    i = 0; w = win_first();
    while (w) {
        if (w->used && w->kind != K_MSG && w->kind != K_INPUT) { if (i == n) return w->id; ++i; }
        w = w->next;
    }
    return 0 - 1;
}

static void end_process(struct win *w) {
    struct tasks *t;
    t = S(w);
    if (t->sel < 0 || t->sel >= t->n) return;
    if (t->privs[t->sel] == 0) {
        msgbox(w, "Cannot Kill", "This is a kernel task; ending it would stop the machine.", 0, A_NONE);
        return;
    }
    ui_cpy(buf, "Kill task ");
    ui_cat(buf, t->name + t->sel * NAMEW);
    ui_cat(buf, "? Unsaved work in it will be lost.");
    msgbox(w, "System Monitor", buf, 1, A_ENDPROC);
}

void tasks_mouse(struct win *w, int ev, int x, int y, int cw, int ch) {
    struct tasks *t;
    int k, rows, r;
    t = S(w);
    ch = ch - 26;
    if (ev == E_WHEEL && t->tab == 1) {
        t->sel = t->sel + y; if (t->sel < 0) t->sel = 0; if (t->sel >= t->n) t->sel = t->n - 1;
        return;
    }
    rows = (ch - PAGE_Y - 60 - 26) / ROW_H;
    if (ev == E_MOVE && t->tab == 1) {
        r = ui_scroll_drag(cw - 26, PAGE_Y + 30, y);
        if (r >= 0) t->top = r;
        if (r >= 0 && t->sel < t->top) t->sel = t->top;
        if (r >= 0 && t->sel >= t->top + rows) t->sel = t->top + rows - 1;
        return;
    }
    if (ev != E_DOWN && ev != E_DBL) return;
    k = ui_tab_hit(x, y, 8, TAB_Y, tabs, 3);
    if (k >= 0) { t->tab = k; return; }
    if (t->tab == 0) {
        if (ui_hit(x, y, 12, PAGE_Y + 30, cw - 26, ch - PAGE_Y - 80)) {
            t->asel = (y - PAGE_Y - 31) / (ROW_H + 2);
            if (ev == E_DBL && (k = app_window(t->asel)) >= 0) win_raise(k);
        } else if (ui_hit(x, y, cw - 300, ch - 40, 90, 24)) {
            if ((k = app_window(t->asel)) >= 0 && k != win_index(w)) win_close(k);
        } else if (ui_hit(x, y, cw - 202, ch - 40, 90, 24)) {
            if ((k = app_window(t->asel)) >= 0) win_raise(k);
        } else if (ui_hit(x, y, cw - 104, ch - 40, 90, 24))
            inputbox(0, "Run", "Program to run:", "", A_RUN);
    } else if (t->tab == 1) {
        rows = (ch - PAGE_Y - 60 - 26) / ROW_H;
        r = ui_scroll_click(x, y, cw - 26, PAGE_Y + 30, ch - PAGE_Y - 82, t->n, rows, t->top);
        // the selection comes along, or the redraw would scroll back to it
        if (r >= 0) {
            t->top = r;
            if (t->sel < t->top) t->sel = t->top;
            if (t->sel >= t->top + rows) t->sel = t->top + rows - 1;
            return;
        }
        if (ui_hit(x, y, 12, PAGE_Y + 31, cw - 40, rows * ROW_H)) {
            r = t->top + (y - PAGE_Y - 31) / ROW_H;
            if (r < t->n) t->sel = r;
        } else if (ui_hit(x, y, cw - 104, ch - 40, 90, 24)) end_process(w);
    }
}

void tasks_key(struct win *w, int code, int ch, int mods) {
    struct tasks *t;
    t = S(w);
    if (code == KEY_TAB && (mods & M_CTRL)) { t->tab = (t->tab + 1) % 3; return; }
    if (t->tab == 1) {
        if (code == KEY_UP && t->sel > 0) --t->sel;
        else if (code == KEY_DOWN && t->sel < t->n - 1) ++t->sel;
        else if (code == KEY_DEL) end_process(w);
    } else if (t->tab == 0) {
        if (code == KEY_UP && t->asel > 0) --t->asel;
        else if (code == KEY_DOWN && app_window(t->asel + 1) >= 0) ++t->asel;
    }
}

void tasks_answer(struct win *w, int action, int yes) {
    struct tasks *t;
    t = S(w);
    if (action != A_ENDPROC || !yes || t->sel < 0 || t->sel >= t->n) return;
    // interrupt whatever it is running first, then end it
    uintr(t->id[t->sel]);
    ukill(t->id[t->sel], SIGTERM);
    sample(t);
    mark_dirty();
}
// term.c -- Terminal: a terminal running c4ix-sh over pipes.
// docs/c4ix-desktop.md.
//
// The shell is a real task whose stdin and stdout are pipes this desktop
// holds. Its output is drawn in the window kit's text grid (textgrid.c,
// a VT100 subset); typing is edited there a line at a time, as a tty in
// cooked mode does, and sent down the pipe on Enter. Ctrl-C interrupts
// the job running under this window's shell and nothing else, and drops
// whatever was typed that it had not read.
//
// A program may also make the window its canvas (include/window.h): it
// writes drawing commands as escape sequences, ESC _ G ... ESC \, and
// while it does the window shows the last frame it presented and sends
// the mouse and keys down its stdin instead of editing a line. The
// window becomes a terminal again when the program says so, when Ctrl-C
// stops it, or when the shell's prompt comes back.
//
// Or a program may take the keys and leave the text, as from a tty in
// raw mode: after ESC _ T r ESC \ each key goes down its stdin as it is
// typed, unechoed -- the arrows, PgUp, PgDn, Home, End and the function
// keys as a VT100 sends them, Enter as CR -- until ESC _ T c ESC \, Ctrl-C
// (which stays an interrupt) or the prompt coming back. top does this;
// on the console the kernel does the same (console.c).
//
// Or the window is a program's own (term_run): no shell and no menu, the
// program itself on the pipes, and the window only its canvas. It closes
// when the program ends -- unless it is showing text the program wrote,
// an error most likely, which stays to be read. Ctrl-C ends the program,
// as closing the window does. Go > Games and Files start a game so when
// its /etc/desktop.apps line says `window` (tools.c, run_command). The
// program may give its window a menu bar (window.h: the M and I ops): the
// window grows by the bar's height, and a pick goes down the pipe as 'c'.
//
// A program run in the background from a Terminal (`quake --window &`)
// gets such a window too (term_adopt). The Terminal's canvas is its
// foreground job's, and its pipes are shared by every job it runs: two
// games drawing there would each read the other's frame acks and keys,
// and the shell at its prompt would read them too. So the shell gives a
// background job an input that has ended, as POSIX's does, and a program
// that asks for a canvas with no input asks for a window of its own
// instead (window.c, win_open: the O op, with its task id). The desktop
// makes the window and its pipes and gives them to that task as its stdin
// and stdout (SYS_FDGIVE). Its stderr stays the Terminal's.
//
// A canvas is GW by GH, whatever the window's size, unless the program
// asks for it to follow the window (the z op, window.h's win_resizable):
// then it is the window's whole inside, a window of the program's own may
// be dragged to any size, and the program hears each new size ('s') once
// the window has held still at it (follow).
//
// A canvas may show a framebuffer, the 'f' op: 8-bit pixels and a
// palette in the program's own memory, which GUI_BLIT8 has the host read
// and scale to the canvas. Once a frame with one has been drawn the
// program hears 'f' back, and may draw the next; and it hears keys let
// go ('K') as well as pressed, which a game needs.
//
// Its Edit menu is the desktop's clipboard, as a console window's is: the
// mouse selects (a run of lines, or with Alt held a block), Copy takes
// the selection and Copy All the scrollback and the screen, and Paste
// types the clipboard in, a key a character. Ctrl+Shift+C and V, Ctrl+Ins
// and Shift+Ins do the same; Ctrl+C copies when there is a selection, and
// is ^C when there is none.

#include "desktop.h"
#include "textgrid.h"
#include "wkgui.h"

enum { IOBUF = 8192 };
// graphics mode: the canvas (the grid's own area), and the two display
// lists -- the one being built, and the one shown
enum { GW = 640, GH = 400, GLIST = 6000 };
// a program's own window's menu bar: menus, items in each, and their text
enum { MENUS = 4, MITEMS = 40, MTEXT = 2048 };

struct term {
    int win;                      // its window's number
    int pid, in_w, out_r, ended;
    int bare;                     // the program's own window: no shell (term_run)
    int adopted;                  // ... and the program a Terminal's job (term_adopt): not ours to wait for
    struct tgrid *g;              // the text
    char pending[128];            // a command to type at the first prompt
    int gfx, buttons;             // a canvas now; mouse buttons held on it
    int raw;                      // keys go to the program as typed (ESC _ T r)
    int fpend;                    // a frame with a framebuffer presented, not yet drawn
    int fit, gw, gh;              // the canvas follows the window (z); its size
    int lock, mx, my;             // the mouse is to be locked to the canvas (L 1); the pointer in it
    int nw, nh, nat;              // the size the window last had, and since when
    char title[48];               // the window's own title, while a program's shows
    int ncur, nshow;
    int gcur[GLIST];              // [len, op, numbers..., text]
    int gshow[GLIST];
    // the menu bar a program gave its own window (prog_menu)
    int nmenus, mlen, mcount[MENUS];
    struct wk_menu menus[MENUS];
    char *mitem[MENUS * (MITEMS + 1)];
    char mtext[MTEXT];
};

static char tmp[128];
static char iobuf[IOBUF];
static char *edit_items[7] = { "Copy   Ctrl+Shift+C", "Paste   Ctrl+Shift+V", "-", "Select All", "Copy All", 0 };
static struct wk_menu menus[1];
enum { T_COPY = 0, T_PASTE = 1, T_ALL = 3, T_COPYALL = 4 };

static struct term *T(struct win *w) { return (struct term *)w->st; }

// ---- graphics mode ------------------------------------------------------------------

static void send(struct term *t, char *s) { write(t->in_w, s, ui_len(s)); }

// An event down the program's stdin: ESC E kind a,b,c newline.
static void event(struct term *t, int kind, int a, int b, int c) {
    int k;
    tmp[0] = 27; tmp[1] = 'E'; tmp[2] = kind; tmp[3] = 0;
    ui_num(tmp + 3, a); k = ui_len(tmp); tmp[k] = ','; tmp[k + 1] = 0;
    ui_num(tmp + k + 1, b); k = ui_len(tmp); tmp[k] = ','; tmp[k + 1] = 0;
    ui_num(tmp + k + 1, c); k = ui_len(tmp); tmp[k] = 10; tmp[k + 1] = 0;
    send(t, tmp);
}

static void lk_drop(struct term *t);

static void gfx_mode(struct term *t, int on) {
    lk_drop(t);
    t->lock = 0;
    if (on && !t->gfx) ui_ncpy(t->title, wk_get_title(t->win), 48);
    if (!on && t->gfx && t->title[0]) wk_title(t->win, t->title);
    if (on && t->g) tg_unselect(t->g);
    if (on != t->gfx) { t->fit = 0; t->gw = GW; t->gh = GH; }
    t->gfx = on;
    t->ncur = 0; t->nshow = 0; t->buttons = 0; t->fpend = 0;
    mark_dirty();
}

// A program's own window's menu bar (window.h): M starts menu m (m 0 the
// whole bar again), I adds an item to menu m. They come in order; one
// that does not fit is dropped. The first menu grows the window by the
// bar's height, so the canvas keeps its size and its place in the client
// area, where the mouse is measured from.
static void prog_menu(struct term *t, int op, int m, char *s) {
    struct win *w;
    int k, had;
    if (!s) s = "";
    k = ui_len(s);
    if (m < 0 || m >= MENUS) return;
    had = t->nmenus;
    if (op == 'M') {
        if (m == 0) { t->nmenus = 0; t->mlen = 0; }
        if (m != t->nmenus || t->mlen + k + 1 > MTEXT) return;
        t->menus[m].title = t->mtext + t->mlen;
        t->menus[m].items = t->mitem + m * (MITEMS + 1);
        t->menus[m].items[0] = 0;
        t->mcount[m] = 0;
        t->nmenus = m + 1;
    } else {
        if (m >= t->nmenus || t->mcount[m] >= MITEMS || t->mlen + k + 1 > MTEXT) return;
        t->menus[m].items[t->mcount[m]] = t->mtext + t->mlen;
        t->mcount[m] = t->mcount[m] + 1;
        t->menus[m].items[t->mcount[m]] = 0;
    }
    ui_cpy(t->mtext + t->mlen, s);
    if (op == 'I' && s[0] == '*') t->mtext[t->mlen] = WK_CHECKED;
    t->mlen = t->mlen + k + 1;
    wk_menu(t->win, t->menus, t->nmenus);
    if (!had && t->nmenus && (w = win_get(t->win))) wk_place(t->win, w->x, w->y, w->w, w->h + MENU_H);
    mark_dirty();
}

// The canvas follows the window's size, or (on 0) is GW by GH again.
static void fit(struct term *t, int on) {
    struct win *w;
    t->fit = on != 0;
    t->nw = 0 - 1;
    if (t->bare && (w = win_get(t->win))) w->resizable = t->fit;
    if (!t->fit && (t->gw != GW || t->gh != GH)) {
        t->gw = GW; t->gh = GH;
        event(t, 's', GW, GH, 0);
        mark_dirty();
    }
}

// A canvas that follows its window takes the window's size once it has
// held still at it for a moment: dragging an edge goes through many sizes,
// and each is the program laying itself out again. The program hears it.
static void follow(struct term *t, struct win *w) {
    int nw, nh, now;
    nw = wk_client_w(w) - 4 - (t->bare ? 0 : TG_SB_W);
    nh = wk_client_h(w) - 4;
    if (nw < 1) nw = 1;
    if (nh < 1) nh = 1;
    now = __time();
    if (nw != t->nw || nh != t->nh) { t->nw = nw; t->nh = nh; t->nat = now; return; }
    if ((nw != t->gw || nh != t->gh) && now - t->nat >= 100) {
        t->gw = nw; t->gh = nh;
        event(t, 's', nw, nh, 0);
        mark_dirty();
    }
}

static void term_adopt(int pid, char *title);

// One command, ESC _ and ESC \ already stripped: G, the op, numbers
// separated by commas, and for text a ';' and the string.
static void apc(char *ctx, char *abuf, int alen) {
    struct term *t;
    int i, n, v, neg, op, len, *g, k, nums[8];
    char *s;
    t = (struct term *)ctx;
    // T: raw keys (r) or lines (c)
    if (alen == 2 && abuf[0] == 'T') { if (abuf[1] == 'r' || abuf[1] == 'c') t->raw = abuf[1] == 'r'; return; }
    if (alen < 2 || abuf[0] != 'G') return;
    op = abuf[1];
    i = 2; n = 0;
    while (i < alen && abuf[i] != ';' && n < 8) {
        v = 0; neg = 0;
        if (abuf[i] == '-') { neg = 1; ++i; }
        while (i < alen && abuf[i] >= '0' && abuf[i] <= '9') { v = v * 10 + (abuf[i] - '0'); ++i; }
        nums[n] = neg ? 0 - v : v; ++n;
        if (i < alen && abuf[i] == ',') ++i;
        else break;
    }
    s = 0;
    if (i < alen && abuf[i] == ';') s = abuf + i + 1;
    if (op == 'o') {
        gfx_mode(t, 1);
        if (s && *s) { if (ui_len(s) > 44) s[44] = 0; wk_title(t->win, s); }
        event(t, 's', t->gw, t->gh, 0);
        return;
    }
    if (op == 'q') { gfx_mode(t, 0); return; }
    // a program in the background wants a window of its own (window.c)
    if (op == 'O') { if (n && nums[0] > 0) term_adopt(nums[0], s); return; }
    if (!t->gfx) return;
    // a menu bar: a program's own window's only (a Terminal has its own)
    if (op == 'M' || op == 'I') { if (t->bare) prog_menu(t, op, n ? nums[0] : 0, s); return; }
    if (op == 'z') { fit(t, n ? nums[0] : 1); return; }
    // the mouse locked to the canvas at a click, or not: the pointer says which
    if (op == 'L') { t->lock = n ? nums[0] != 0 : 1; if (!t->lock) lk_drop(t); wk_repoint(); return; }
    if (op == 'p') {
        memcpy(t->gshow, t->gcur, t->ncur * sizeof(int));
        t->nshow = t->ncur;
        t->ncur = 0;
        // a framebuffer in it: tell the program once it has been drawn
        k = 0;
        while (k < t->nshow && t->gshow[k] >= 2) {
            if (t->gshow[k + 1] == 'f') t->fpend = 1;
            k = k + t->gshow[k];
        }
        // A framebuffer fills the canvas, so only the canvas changed, and
        // its frame covers all of it (gfx_draw): nothing under it or
        // around it is drawn again. Lines and text may reach outside it,
        // and the whole window is drawn for those.
        if (t->fpend) { wk_invalidate_covered(t->win, 2, 2, t->gw, t->gh); mark_frame(); }
        else wk_invalidate(t->win, 0, 0, 0, 0);
        return;
    }
    // everything else is drawn later: into the list being built
    len = 2 + n + (s ? 1 + (ui_len(s) + 4) / 4 : 0);
    if (t->ncur + len > GLIST) return;           // a frame too big: the rest is dropped
    g = t->gcur + t->ncur;
    g[0] = len; g[1] = op;
    k = 0;
    while (k < n) { g[2 + k] = nums[k]; ++k; }
    if (s) { g[2 + n] = ui_len(s); ui_cpy((char *)(g + 3 + n), s); }
    t->ncur = t->ncur + len;
}

static void gfx_draw(struct term *t, int ox, int oy) {
    int i, *g, n, op, fb, clip;
    // The last framebuffer covers the whole canvas, and what came before
    // it: drawn from there, with no black under it, and what follows it
    // kept to the canvas (only the canvas is drawn again after a frame)
    fb = 0 - 1;
    i = 0;
    while (i < t->nshow && t->gshow[i] >= 2) {
        if (t->gshow[i + 1] == 'f' && t->gshow[i] >= 7) fb = i;
        i = i + t->gshow[i];
    }
    clip = 0;
    if (fb < 0) { d_rect(ox, oy, t->gw, t->gh, 0); i = 0; }
    else {
        i = fb;
        if (i + t->gshow[i] < t->nshow) { d_clip(ox, oy, t->gw, t->gh); clip = 1; }
    }
    while (i < t->nshow) {
        g = t->gshow + i;
        op = g[1];
        n = g[0] - 2;
        if (op == 'c' && n >= 1) d_rect(ox, oy, t->gw, t->gh, g[2]);
        else if (op == 'r' && n >= 5) d_rect(ox + g[2], oy + g[3], g[4], g[5], g[6]);
        else if (op == 'R' && n >= 5) d_recto(ox + g[2], oy + g[3], g[4], g[5], g[6]);
        else if (op == 'l' && n >= 5) d_line(ox + g[2], oy + g[3], ox + g[4], oy + g[5], g[6]);
        else if (op == 'd' && n >= 4) d_disc(ox + g[2], oy + g[3], g[4], g[5]);
        else if (op == 't' && n >= 6) d_textn(ox + g[2], oy + g[3], g[4], g[5], F_SANS, 0, (char *)(g + 7), g[6]);
        else if (op == 'f' && n >= 5) {
            // the program's memory, which the display reads at the
            // desktop's word: lent to the desktop first (under the MMU
            // each task's is its own); a frame it will not lend is not drawn
            if (umapfrom(g[2], g[5] * g[4]) == 0 && umapfrom(g[6], 1024) == 0)
                d_blit8(ox, oy, g[3], g[4], (char *)g[2], g[5], (int *)g[6], t->gw, t->gh);
            else d_rect(ox, oy, t->gw, t->gh, 0);
        }
        if (g[0] < 2) break;
        i = i + g[0];
    }
    if (clip) d_clip_end();
}

// ---- the shell --------------------------------------------------------------------

// Our ends of the pipes are close-on-spawn, so no shell -- this one or a
// later window's -- inherits them: that is what lets a shell see end of
// file, and keeps each window's pipes its own.
//
// spawn gives the shell this task's 0, 1 and 2, so they point at the
// pipes for the spawn and are put back after it. That takes seven
// descriptors at once, and every step is checked: when the table is
// full, a desktop that went on would keep a Terminal's pipe as its
// stdout, and its own messages, and Power Off's, would go into that
// window and never reach the console. Instead what was opened is closed,
// 0, 1 and 2 are as they were, and term_open says no shell started.
static char *sh_argv[3] = { "c4ix-sh.c4r", "-p", 0 };   // -p: the prompt on the input line
static int start(struct term *t, char *path, int argc, char **argv) {
    int pin[2], pout[2], s0, s1, s2;
    t->pid = 0 - 1;
    if (upipe(pin) < 0) return 0;
    if (upipe(pout) < 0) { uclose(pin[0]); uclose(pin[1]); return 0; }
    s0 = udup(STDIN); s1 = udup(STDOUT); s2 = udup(STDERR);
    if (s0 >= 0 && s1 >= 0 && s2 >= 0) {
        ucloexec(pin[1], 1); ucloexec(pout[0], 1);
        ucloexec(s0, 1); ucloexec(s1, 1); ucloexec(s2, 1);
        if (udup2(pin[0], STDIN) >= 0 && udup2(pout[1], STDOUT) >= 0 && udup2(pout[1], STDERR) >= 0)
            t->pid = spawn(path, argc, argv);
        // s0, s1 and s2 are open, so these cannot fail
        udup2(s0, STDIN); udup2(s1, STDOUT); udup2(s2, STDERR);
    }
    uclose(s0); uclose(s1); uclose(s2);   // one that is -1 closes nothing
    uclose(pin[0]); uclose(pout[1]);
    if (t->pid < 0) { uclose(pin[1]); uclose(pout[0]); return 0; }
    t->in_w = pin[1];
    t->out_r = pout[0];
    return 1;
}

// A new Terminal; with cmd, that command is typed at its first
// prompt (Run, and Files running a program).
int term_open(char *cmd) {
    int i, k;
    struct win *w;
    struct term *t;
    i = win_open(K_TERM, "Terminal", TG_W + 2 * BORDER + TG_SB_W, TG_H + 2 * BORDER + TITLE_H + 1 + MENU_H, sizeof(struct term));
    if (i < 0) return 0 - 1;
    w = win_get(i);
    w->resizable = 0;
    menus[0].title = "Edit"; menus[0].items = edit_items;
    wk_menu(i, menus, 1);
    t = T(w);
    t->win = i;
    if (!(t->g = tg_new(i))) { t->ended = 1; win_close(i); return 0 - 1; }   // no memory left for it
    t->g->apc = apc; t->g->ctx = (char *)t;
    if (cmd) ui_ncpy(t->pending, cmd, 128);
    if (!start(t, "c4ix-sh.c4r", 2, sh_argv)) { tg_say(t->g, "desktop: could not start a shell\n"); t->ended = 1; t->pid = 0 - 1; return i; }
    // "Terminal - task N": the id ps shows for this window's shell
    ui_cpy(tmp, "Terminal - task ");
    k = ui_len(tmp);
    ui_num(tmp + k, t->pid);
    win_title(w, tmp);
    return i;
}

// A program in a window of its own, with no shell: the command's words are
// its arguments, the first found as the shell finds it (desk_which). The
// window is the canvas's size, with no menu and no scroll bar, and has the
// program's name for a title until the program gives one.
enum { RUN_ARGS = 16 };
int term_run(char *cmd) {
    int i, n;
    struct win *w;
    struct term *t;
    char path[WK_PATH], line[128], *argv[RUN_ARGS + 1], *s;
    if (!desk_which(cmd, path)) return 0 - 1;
    ui_ncpy(line, cmd, 128);
    n = 0; s = line;
    while (*s && n < RUN_ARGS) {
        while (*s == ' ') { *s = 0; ++s; }
        if (!*s) break;
        argv[n] = s; ++n;
        while (*s && *s != ' ') ++s;
    }
    if (n == 0) return 0 - 1;
    argv[n] = 0;
    s = argv[0];
    while (*s) ++s;
    while (s > argv[0] && s[-1] != '/') --s;
    i = win_open(K_TERM, s, TG_W + 2 * BORDER, TG_H + 2 * BORDER + TITLE_H + 1, sizeof(struct term));
    if (i < 0) return 0 - 1;
    w = win_get(i);
    w->resizable = 0;
    t = T(w);
    t->win = i;
    t->bare = 1;
    if (!(t->g = tg_new(i))) { t->ended = 1; win_close(i); return 0 - 1; }   // no memory left for it
    t->g->apc = apc; t->g->ctx = (char *)t;
    if (!start(t, path, n, argv)) {
        tg_say(t->g, "desktop: could not start "); tg_say(t->g, path); tg_say(t->g, "\n");
        t->ended = 1; t->pid = 0 - 1;
    }
    return i;
}

// A program a Terminal ran in the background asks for a window of its
// own (the O op: its task id, and its title): one as term_run's, whose
// pipes are given to that task as its stdin and stdout (SYS_FDGIVE, which
// gives only to a task the desktop's own tasks started). Its stdout goes
// first: once its stdin is live (win_open waits for that) it is drawing
// here. It is the shell's job, not the desktop's child, so the window
// knows it has ended by the pipe, and closing the window ends it.
static void term_adopt(int pid, char *title) {
    int i, ok, pin[2], pout[2];
    struct win *w;
    struct term *t;
    char name[48];
    ui_ncpy(name, title && *title ? title : "Program", 45);
    i = win_open(K_TERM, name, TG_W + 2 * BORDER, TG_H + 2 * BORDER + TITLE_H + 1, sizeof(struct term));
    if (i < 0) return;
    w = win_get(i);
    w->resizable = 0;
    t = T(w);
    t->win = i;
    t->bare = 1;
    t->adopted = 1;
    t->pid = pid;
    t->ended = 1;                 // until it has its pipes
    if (!(t->g = tg_new(i))) { win_close(i); return; }
    t->g->apc = apc; t->g->ctx = (char *)t;
    ok = 0;
    if (upipe(pin) == 0) {
        if (upipe(pout) == 0) {
            ucloexec(pin[1], 1); ucloexec(pout[0], 1);
            ok = ufdgive(pid, pout[1], STDOUT) >= 0 && ufdgive(pid, pin[0], STDIN) >= 0;
            uclose(pout[1]);
            if (ok) t->out_r = pout[0];
            else uclose(pout[0]);
        }
        uclose(pin[0]);
        if (ok) t->in_w = pin[1];
        else uclose(pin[1]);
    }
    // no pipes, or not a task of ours: its win_open gives up waiting
    if (!ok) { win_close(i); return; }
    t->ended = 0;
}

// The window is going: stop the job running in it, then the shell.
void term_close(struct win *w) {
    struct term *t;
    t = T(w);
    lk_drop(t);
    if (t->g) { tg_free(t->g); t->g = 0; }
    if (t->ended) return;
    uintr(t->pid);
    ukill(t->pid, SIGTERM);
    uclose(t->in_w);
    uclose(t->out_r);
    if (!t->adopted) uwait(t->pid);
    t->ended = 1;
}

// Output waiting in the pipe; never blocks.
void term_tick(struct win *w) {
    struct term *t;
    int n, k, got, prompt;
    t = T(w);
    if (t->ended) return;
    if (t->gfx && t->fit) follow(t, w);
    n = uavail(t->out_r);
    got = 0;
    // Take everything the program has written before drawing: a full-screen
    // program writes a whole frame at once, and drawing half of one is flicker.
    while (n > 0 && got < 65536) {
        if (n > IOBUF) n = IOBUF;
        n = uread(t->out_r, iobuf, n);
        if (n <= 0) break;
        got = got + n;
        tg_feed(t->g, iobuf, n);
        // the shell's prompt ends "$ " (c4ix-sh -p) and is the last thing it writes
        prompt = !t->bare && n >= 2 && iobuf[n - 2] == '$' && iobuf[n - 1] == ' ';
        // The shell's prompt is back: whatever made this a canvas, or took
        // the keys, has ended. What was sent to it and not read -- a frame
        // ack, a key let go -- goes with it, as on a Ctrl-C: the shell
        // would read it next.
        if (t->gfx && prompt) { gfx_mode(t, 0); udiscard(t->in_w); }
        if (prompt) t->raw = 0;
        // ... and time to type a waiting command
        if (t->pending[0] && prompt) {
            k = ui_len(t->pending);
            tg_say(t->g, t->pending);
            t->pending[k] = 10;
            write(t->in_w, t->pending, k + 1);
            tg_echo(t->g, 10);
            t->pending[0] = 0;
        }
        n = uavail(t->out_r);
    }
    if (n < 0) {
        // every writer is gone: the shell exited
        uclose(t->in_w);
        uclose(t->out_r);
        if (!t->adopted) uwait(t->pid);
        t->ended = 1;
        // a program's own window goes with it, unless it shows what the program wrote
        if (t->bare && (t->gfx || (!t->g->cx && !t->g->cy && !t->g->sbn))) { win_close(t->win); return; }
        if (t->bare) tg_say(t->g, "\n[the program has ended; close this window]\n");
        else tg_say(t->g, "\n[the shell has exited; close this window]\n");
    }
}

// A key let go: only a canvas hears it.
void term_keyup(struct win *w, int code, int ch, int mods) {
    struct term *t;
    t = T(w);
    if (t->ended || !t->gfx) return;
    event(t, 'K', code, ch, mods);
}

// The desktop has drawn: a framebuffer it showed has been read.
void term_drawn(struct win *w) {
    struct term *t;
    t = T(w);
    if (!t->fpend) return;
    t->fpend = 0;
    if (t->gfx && !t->ended) event(t, 'f', 0, 0, 0);
}

// The clipboard typed in, as keys: a line at a time down the pipe, as
// typing it would send them; to a canvas, each as a key.
static void paste(struct win *w, struct term *t) {
    char *s;
    int n, k, c;
    s = wk_clip_get(&n);
    k = 0;
    while (k < n && !t->ended) {
        c = s[k] & 255;
        if (c == 9) c = ' ';
        if (t->gfx) { if (c == 10) event(t, 'k', KEY_ENTER, 13, 0); else if (c >= 32 && c < 127) event(t, 'k', 0, c, 0); }
        else if (t->raw) { tmp[0] = c == 10 ? 13 : c; if (c == 10 || (c >= 32 && c < 127)) write(t->in_w, tmp, 1); }
        else if (c == 10) { if ((c = tg_key(t->g, KEY_ENTER, 0, 0)) > 0) write(t->in_w, t->g->line, c); }
        else if (c >= 32 && c < 127) tg_key(t->g, 0, c, 0);
        ++k;
    }
    wk_invalidate(w->id, 0, 0, 0, 0);
}

void term_command(struct win *w, int menu, int item) {
    struct term *t;
    t = T(w);
    // a program's own window: its menus are the program's
    if (t->bare) { if (!t->ended && t->gfx) event(t, 'c', menu, item, 0); return; }
    if (!t->g) return;
    if (item == T_COPY) { if (tg_copy(t->g, 0)) tg_unselect(t->g); }
    else if (item == T_COPYALL) tg_copy(t->g, 1);
    else if (item == T_ALL) tg_select_all(t->g);
    else if (item == T_PASTE && !t->ended) { tg_unselect(t->g); paste(w, t); }
}

// Raw keys (t->raw): what a VT100 sends for a key that is not a character,
// after its ESC, or 0
static char *raw_tail(int code) {
    if (code == KEY_UP) return "[A";
    if (code == KEY_DOWN) return "[B";
    if (code == KEY_RIGHT) return "[C";
    if (code == KEY_LEFT) return "[D";
    if (code == KEY_HOME) return "[H";
    if (code == KEY_END) return "[F";
    if (code == KEY_PGUP) return "[5~";
    if (code == KEY_PGDN) return "[6~";
    if (code == KEY_INS) return "[2~";
    if (code == KEY_DEL) return "[3~";
    if (code == KEY_F2 - 1) return "OP";
    if (code == KEY_F2) return "OQ";
    if (code == KEY_F2 + 1) return "OR";
    if (code == KEY_F4) return "OS";
    if (code == KEY_F5) return "[15~";
    if (code == KEY_F5 + 1) return "[17~";
    if (code == KEY_F5 + 2) return "[18~";
    if (code == KEY_F5 + 3) return "[19~";
    if (code == KEY_F5 + 4) return "[20~";
    if (code == KEY_F5 + 5) return "[21~";
    if (code == KEY_F5 + 6) return "[23~";
    if (code == KEY_F5 + 7) return "[24~";
    return 0;
}

// ... and the key itself down the program's stdin: a character as it is,
// Enter as CR and Backspace as DEL, Ctrl with a letter as its control
// code, Alt with ESC in front
static void raw_key(struct term *t, int code, int ch, int mods) {
    char b[8];
    char *s;
    int n, c;
    n = 0;
    if (!ch && (s = raw_tail(code))) {
        b[0] = 27; n = 1;
        while (*s && n < 7) { b[n] = *s; ++n; ++s; }
        write(t->in_w, b, n);
        return;
    }
    c = ch;
    if (!ch && (code == KEY_ENTER || code == KEY_BACK || code == KEY_TAB || code == KEY_ESC)) c = code;
    if (c == 10) c = 13;
    if (c == 8) c = 127;
    if ((mods & M_CTRL) && code >= 'A' && code <= 'Z') c = code - 64;
    if (c <= 0 || c > 255) return;
    if (mods & M_ALT) { b[n] = 27; ++n; }
    b[n] = c; ++n;
    write(t->in_w, b, n);
}

// the letter key, with Ctrl and Shift held
static int ctrl_shift(int code, int ch, int mods, int c) {
    return (mods & M_CTRL) && (mods & M_SHIFT) && (code == c || ch == c || ch == c + 32);
}

// A key typed here.
void term_key(struct win *w, int code, int ch, int mods) {
    struct term *t;
    int n;
    t = T(w);
    if (t->g && (ctrl_shift(code, ch, mods, 'C') || ((mods & M_CTRL) && code == KEY_INS) ||
                 (t->g->sel && (mods & M_CTRL) && (ch == 'c' || ch == 'C' || code == 'C')))) { term_command(w, 0, T_COPY); return; }
    if (t->g && (ctrl_shift(code, ch, mods, 'V') || ((mods & M_SHIFT) && code == KEY_INS))) { term_command(w, 0, T_PASTE); return; }
    if (t->ended) return;
    // the modifiers alone are a canvas's business; anything else typed drops a selection
    if (code == 16 || code == 17 || code == 18) { if (t->gfx) event(t, 'k', code, ch, mods); return; }
    tg_unselect(t->g);
    // a program's own window: Ctrl-C ends the program, and with it the window
    if (t->bare && (mods & M_CTRL) && (ch == 'c' || ch == 'C' || code == 'C')) { ukill(t->pid, SIGINT); return; }
    if ((mods & M_CTRL) && (ch == 'c' || ch == 'C' || code == 'C')) {
        // What the program wrote before the interrupt shows first, as a
        // tty's output queue would have it: drawn after the ^C, the last
        // frame of a full-screen program (top) would clear it away.
        term_tick(w);
        if (t->ended) return;
        if (t->gfx) gfx_mode(t, 0);
        t->raw = 0;
        tg_interrupt(t->g);
        // Lines typed at the job and not read by it go with it, as a tty
        // flushes its input on an interrupt: left in the pipe, the shell
        // would read them next and run them as commands of its own.
        udiscard(t->in_w);
        // nothing running under the shell: an empty line brings a fresh prompt
        if (uintr(t->pid) <= 0) write(t->in_w, "\n", 1);
        return;
    }
    // raw keys: all of them the program's, Ctrl-L too; the screen, not the scrollback
    if (t->raw && !t->gfx) { if (t->g->view) { t->g->view = 0; wk_redraw_all(); } raw_key(t, code, ch, mods); return; }
    if ((mods & M_CTRL) && (ch == 'l' || ch == 'L' || code == 'L')) { tg_clear_screen(t->g); return; }
    if (t->gfx) { event(t, 'k', code, ch, mods); return; }
    if ((n = tg_key(t->g, code, ch, mods)) > 0) write(t->in_w, t->g->line, n);
}

void term_mouse(struct win *w, int ev, int x, int y, int cw, int ch) {
    struct term *t;
    int b;
    t = T(w);
    if (!t->g) return;
    if (!t->gfx) {
        // the grid selects, its scroll bar scrolls
        if (ev == E_WHEEL || ui_scroll_active() || (ev != E_UP && x >= TG_W)) { tg_mouse(t->g, ev, x, y); return; }
        tg_select(t->g, ev, x - 2, y - 2, (wk.mods & M_ALT) != 0);
        return;
    }
    if (t->ended) return;
    x = x - 2; y = y - 2;                          // inside the sunken edge
    if (x < 0) x = 0; if (y < 0) y = 0;
    if (x >= t->gw) x = t->gw - 1; if (y >= t->gh) y = t->gh - 1;
    t->mx = x; t->my = y;
    // each button as it is (0 the left, 1 the middle, 2 the right), and a
    // move with those held, a bit each
    b = wm_button & 7;
    if (ev == E_DOWN) { t->buttons = t->buttons | (1 << b); event(t, 'd', x, y, b); }
    else if (ev == E_UP) { if (t->buttons & (1 << b)) event(t, 'u', x, y, b); t->buttons = t->buttons & ~(1 << b); }
    else if (ev == E_MOVE) event(t, 'm', x, y, t->buttons);
}

// Over a canvas that asked for the mouse locked (L 1), the pointer says
// "click to capture" (GUI_PTR_LOCK): the page locks the mouse to the
// display at the next click (libjs/display.js). Elsewhere a text beam.
int term_pointer(struct win *w, int x, int y, int cw, int ch) {
    struct term *t;
    t = T(w);
    if (t->gfx && t->lock && !t->ended && x >= 2 && y >= 2 && x < t->gw + 2 && y < t->gh + 2) return PTR_LOCK;
    return PTR_TEXT;
}

// ---- the mouse locked to a canvas ---------------------------------------------------
//
// Locked, the page sends the mouse's motion as GUI_EV_REL (the desktop's
// event mask asks for it, shell.c), and the canvas whose window had the
// focus when it began has it, as `r dx,dy,buttons` (window.h); its buttons
// go there too, as d and u at the pointer's place, kept here by adding up
// the motion. A plain move again says the page let it go (Esc, which the
// browser keeps for itself); the window losing the focus, the canvas
// going, its program ending or L 0 let it go from this side, all buttons
// let go first. Then a click locks it again. grin's game windows do the
// same (src/grin/fwin.c).
static int lk_win;                 // the window the mouse is locked to, or 0

static struct term *lk_term() {
    struct win *w;
    if (!lk_win || !(w = win_get(lk_win)) || w->kind != K_TERM) return 0;
    return T(w);
}

// let the lock go, if it is T's: its buttons up, the display told
static void lk_drop(struct term *t) {
    int b;
    if (!lk_win || !t || t->win != lk_win) return;
    b = 0;
    while (b < 3) {
        if ((t->buttons & (1 << b)) && !t->ended && t->gfx) event(t, 'u', t->mx, t->my, b);
        ++b;
    }
    t->buttons = 0;
    lk_win = 0;
    desk_unlock();
}

int term_lock_event(int *ev) {
    struct term *t;
    struct win *w;
    int f, b;
    if (ev[0] == GUI_EV_REL) {
        if (!lk_win) {
            // the page has just locked it: the focused canvas's, if it asked
            f = wk_focus();
            if (f && (w = win_get(f)) && w->kind == K_TERM && T(w)->gfx && T(w)->lock && !T(w)->ended && !wk_modal() && !wk_menu_open())
                lk_win = f;
            else { desk_unlock(); return 1; }       // nobody's: let it go
        }
        if (!(t = lk_term())) { lk_win = 0; desk_unlock(); return 1; }
        t->mx = t->mx + ev[1]; t->my = t->my + ev[2];
        if (t->mx < 0) t->mx = 0; if (t->my < 0) t->my = 0;
        if (t->mx >= t->gw) t->mx = t->gw - 1; if (t->my >= t->gh) t->my = t->gh - 1;
        if (ev[1] || ev[2]) event(t, 'r', ev[1], ev[2], t->buttons);
        return 1;
    }
    if (!lk_win) return 0;
    if (!(t = lk_term())) { lk_win = 0; desk_unlock(); return 0; }
    // a plain move: the page let it go (Esc); the kit has the mouse again
    if (ev[0] == GUI_EV_MOVE) { t->buttons = 0; lk_win = 0; wk_repoint(); return 0; }
    b = ev[3] & 7;
    if (ev[0] == GUI_EV_DOWN) { t->buttons = t->buttons | (1 << b); event(t, 'd', t->mx, t->my, b); return 1; }
    if (ev[0] == GUI_EV_UP) {
        if (t->buttons & (1 << b)) event(t, 'u', t->mx, t->my, b);
        t->buttons = t->buttons & ~(1 << b);
        return 1;
    }
    if (ev[0] == GUI_EV_WHEEL) return 1;
    // the page lost the keyboard, and with it the lock
    if (ev[0] == GUI_EV_FOCUS && !ev[1]) lk_drop(t);
    return 0;
}

// each pass: the lock let go once its canvas is no longer the one to have it
void term_lock_tick() {
    struct term *t;
    if (!lk_win) return;
    if (!(t = lk_term())) { lk_win = 0; desk_unlock(); return; }
    if (t->ended || !t->gfx || !t->lock || wk_focus() != lk_win || wk_modal() || wk_menu_open()) lk_drop(t);
}

void term_draw(struct win *w, int ox, int oy, int cw, int ch, int focused) {
    struct term *t;
    t = T(w);
    // only the canvas being drawn again (a frame): it covers all of that
    if (t->gfx && d_damage_within(ox + 2, oy + 2, t->gw, t->gh)) { gfx_draw(t, ox + 2, oy + 2); return; }
    d_rect(ox, oy, cw, ch, C_DARK);
    if (t->gfx) { d_bevel(ox, oy, t->gw + 4, t->gh + 4, B_SUNKEN); gfx_draw(t, ox + 2, oy + 2); return; }
    d_bevel(ox, oy, TG_W, TG_H, B_SUNKEN);
    if (t->g) tg_draw(t->g, ox + 2, oy + 2, focused && !t->ended);
}
// tools.c -- the desktop's window kinds as window kit classes.
// docs/c4ix-desktop.md.
//
// The desktop's own tools -- Terminal, Files, System Monitor, the Editor,
// About and Settings -- were written before the kit, against a struct
// win and hooks handed the client area's corner. Their hooks are one
// table here (the desktop review's M1, in place of a ladder of kinds in
// each of six places), and one set of adapters makes every kind a kit
// class. The Calculator, Text Editor and Clock are the kit's own classes.
// The calls the tools make -- win_open, msgbox, inputbox -- are the
// kit's, under their old names.

#include "desktop.h"

struct tool {
    void (*draw)(struct win *w, int ox, int oy, int cw, int ch, int focused);
    void (*mouse)(struct win *w, int ev, int x, int y, int cw, int ch);
    void (*key)(struct win *w, int code, int ch, int mods);
    void (*keyup)(struct win *w, int code, int ch, int mods);
    void (*command)(struct win *w, int menu, int item);
    void (*answer)(struct win *w, int action, int yes);
    void (*tick)(struct win *w);              // every pass (a pipe to read)
    void (*second)(struct win *w);            // once a machine second (live numbers)
    void (*drawn)(struct win *w);             // a frame with it in was shown
    void (*close)(struct win *w);             // going: let go of what it holds
    int  (*pointer)(struct win *w, int x, int y, int cw, int ch);
    int  pointer_shape;
};

static struct tool tools[N_KINDS] = {
    [K_TERM]     = { .draw = term_draw, .mouse = term_mouse, .key = term_key, .keyup = term_keyup, .command = term_command,
                     .tick = term_tick, .drawn = term_drawn, .close = term_close, .pointer = term_pointer,
                     .pointer_shape = PTR_TEXT },
    [K_FILES]    = { .draw = files_draw, .mouse = files_mouse, .key = files_key,
                     .command = files_command, .answer = files_answer, .pointer = files_pointer },
    [K_TASKS]    = { .draw = tasks_draw, .mouse = tasks_mouse, .key = tasks_key,
                     .answer = tasks_answer, .second = tasks_tick },
    [K_EDIT]     = { .draw = edit_draw, .mouse = edit_mouse, .key = edit_key, .command = edit_command,
                     .answer = edit_answer, .tick = edit_tick, .close = edit_close, .pointer = edit_pointer },
    [K_SETTINGS] = { .draw = settings_draw, .mouse = settings_mouse, .key = settings_key },
    [K_ABOUT]    = { .draw = about_draw }
};
static struct wk_class classes[N_KINDS];
static int ready;
int wm_button;                                // the button of the last press or release (desktop.h)

static struct tool *tool(struct win *w) { return &tools[w->kind]; }

// ---- the adapters: a kit class's hooks, calling a tool's ----

static void a_draw(int i, int cw, int ch, int focused) {
    struct win *w;
    if ((w = win_get(i))) tool(w)->draw(w, 0, 0, cw, ch, focused);
}
static void a_mouse(int i, int ev, int x, int y, int b) {
    struct win *w;
    int cw, ch;
    if (!(w = win_get(i))) return;
    wk_size(i, &cw, &ch);
    if (ev == E_DOWN || ev == E_UP || ev == E_DBL) wm_button = b;
    tool(w)->mouse(w, ev, x, ev == E_WHEEL ? b : y, cw, ch);   // the wheel's steps came as y
}
static void a_key(int i, int down, int code, int ch, int mods) {
    struct win *w;
    if (!(w = win_get(i))) return;
    if (down) tool(w)->key(w, code, ch, mods);
    else if (tool(w)->keyup) tool(w)->keyup(w, code, ch, mods);
}
static void a_command(int i, int id) {
    struct win *w;
    if ((w = win_get(i))) tool(w)->command(w, id / WK_CMD_STEP, id % WK_CMD_STEP);
}
static void a_answer(int i, int dialog, int yes) {
    struct win *w;
    if ((w = win_get(i))) tool(w)->answer(w, dialog, yes);
}
static void a_idle(int i) { struct win *w; if ((w = win_get(i))) tool(w)->tick(w); }
static void a_timer(int i, int id) { struct win *w; if ((w = win_get(i))) tool(w)->second(w); }
static void a_drawn(int i) { struct win *w; if ((w = win_get(i))) tool(w)->drawn(w); }
static void a_destroy(int i) { struct win *w; if ((w = win_get(i))) tool(w)->close(w); }
static int a_pointer(int i, int x, int y) {
    struct win *w;
    int cw, ch;
    if (!(w = win_get(i))) return PTR_ARROW;
    wk_size(i, &cw, &ch);
    return tool(w)->pointer(w, x, y, cw, ch);
}

static void init() {
    int k;
    struct tool *t;
    struct wk_class *c;
    ready = 1;
    k = 0;
    while (k < N_KINDS) {
        t = &tools[k]; c = &classes[k];
        c->kind = k;
        c->pointer_shape = t->pointer_shape;
        if (t->draw) c->draw = a_draw;
        if (t->mouse) c->mouse = a_mouse;
        if (t->key) c->key = a_key;
        if (t->command) c->command = a_command;
        if (t->answer) c->answer = a_answer;
        if (t->tick) c->idle = a_idle;
        if (t->second) c->timer = a_timer;
        if (t->drawn) c->drawn = a_drawn;
        if (t->close) c->destroy = a_destroy;
        if (t->pointer) c->pointer = a_pointer;
        ++k;
    }
}

struct wk_class *kind_class(int kind) {
    if (kind == K_CALC) return &calc_class;
    if (kind == K_NOTE) return &notepad_class;
    if (kind == K_CLOCK) return &clock_class;
    if (!ready) init();
    return kind > 0 && kind < N_KINDS ? &classes[kind] : &classes[K_ABOUT];
}

// ---- the calls the tools make ----

int win_open(int kind, char *title, int w, int h, int size) {
    struct wk_class *c;
    int i;
    c = kind_class(kind);
    c->size = size;
    i = wk_open(c, title, w, h, 0, 0);
    if (i > 0 && kind > 0 && kind < N_KINDS && tools[kind].second) wk_timer(i, 1, 1000);
    return i;
}
void win_close(int i) { wk_close(i); }
void win_title(struct win *w, char *s) { wk_title(w->id, s); }
void win_raise(int i) { wk_raise(i); }
int  win_focused() { int f; f = wk_focus(); return f ? f : 0 - 1; }
void mark_dirty() { wk_redraw_all(); }
void mark_win_dirty(struct win *w) { wk_invalidate(w->id, 0, 0, 0, 0); }
int  now_ms() { return wk_now(); }

void msgbox(struct win *owner, char *title, char *text, int yesno, int action) {
    wk_msgbox(owner ? owner->id : 0, action, title, text, yesno ? WK_YESNO : WK_OK);
}

// The text a box was answered with, copied here as the answer is given:
// each box edits a text of its own while it is open.
static char dtext[WK_PATH];
char *dialog_text() { return dtext; }
void inputbox(struct win *owner, char *title, char *prompt, char *initial, int action) {
    ui_ncpy(dtext, initial, 121);
    wk_inputbox(owner ? owner->id : 0, action, title, prompt, dtext, 121);   // 120 characters
}

// ---- starting a program -------------------------------------------------------------
//
// A command runs in a new Terminal, typed at its shell's first prompt; or,
// for a game whose /etc/desktop.apps line says `window` (shell.c), in a
// window that is only its canvas, with no shell (term.c, term_run). Those
// games are known by their programs' names, which are unique on the disk
// (/usr/games/bin, vfs-games.py): a command names one by that name alone,
// or by a path under /usr/games, as Files does. The rest -- a program
// elsewhere, anything the desktop.apps lines do not mark -- gets a
// Terminal, where such a game still opens its window, the Terminal itself.

enum { N_WINDOWED = 96, WNAME = 32 };
static char windowed[N_WINDOWED * WNAME];
static int n_windowed;

// The name a command's program goes by: its first word's last part, less
// any .c4r. 0 if there is none, or it is too long to be a game's.
static int prog_name(char *cmd, char *out) {
    char *s, *base;
    int n;
    while (*cmd == ' ') ++cmd;
    base = cmd; s = cmd;
    while (*s && *s != ' ') { if (*s == '/') base = s + 1; ++s; }
    n = s - base;
    if (n > 4 && base[n - 4] == '.' && base[n - 3] == 'c' && base[n - 2] == '4' && base[n - 1] == 'r') n = n - 4;
    if (n <= 0 || n >= WNAME) return 0;
    memcpy(out, base, n);
    out[n] = 0;
    return 1;
}

void desk_window_app(char *cmd) {
    if (n_windowed < N_WINDOWED && prog_name(cmd, windowed + n_windowed * WNAME)) ++n_windowed;
}

static int is_windowed(char *cmd) {
    char name[WNAME], *s;
    int i;
    while (*cmd == ' ') ++cmd;
    s = cmd;
    while (*s && *s != ' ' && *s != '/') ++s;
    // a path: one of the games' only under /usr/games
    if (*s == '/' && memcmp(cmd, "/usr/games/", 11) != 0) return 0;
    if (!prog_name(cmd, name)) return 0;
    i = 0;
    while (i < n_windowed) { if (ui_eq(windowed + i * WNAME, name)) return 1; ++i; }
    return 0;
}

// The program a command's first word names, as the shell finds it (sh.c):
// a path as written, or with .c4r; a bare name in /bin, /usr/bin or
// /usr/games/bin, as is or with .c4r. 1 with its path in path (WK_PATH).
static char *which_dirs[4] = { "/bin/", "/usr/bin/", "/usr/games/bin/", 0 };
int desk_which(char *cmd, char *path) {
    char name[WK_NAME];
    int k, d, slash, st[8];
    while (*cmd == ' ') ++cmd;
    k = 0; slash = 0;
    while (cmd[k] && cmd[k] != ' ') { if (cmd[k] == '/') slash = 1; ++k; }
    if (k == 0 || k >= WK_NAME - 4) return 0;
    memcpy(name, cmd, k);
    name[k] = 0;
    d = 0;
    while (slash ? d < 1 : which_dirs[d] != 0) {
        path[0] = 0;
        if (!slash) ui_cpy(path, which_dirs[d]);
        ui_cat(path, name);
        if (ustat(path, st) == 0 && st[0] != 1) return 1;
        ui_cat(path, ".c4r");
        if (ustat(path, st) == 0 && st[0] != 1) return 1;
        ++d;
    }
    return 0;
}

void run_command(char *cmd) {
    if (is_windowed(cmd) && term_run(cmd) >= 0) return;
    term_open(cmd);
}
int note_open(char *path) { return notepad_open(path); }

void launch(int kind) {
    if (kind == K_TERM) term_open(0);
    else if (kind == K_FILES) files_open("/");
    else if (kind == K_TASKS) tasks_open();
    else if (kind == K_NOTE) note_open(0);
    else if (kind == K_EDIT) edit_open(0);
    else if (kind == K_CALC) calc_open();
    else if (kind == K_CLOCK) clock_open();
    else if (kind == K_SETTINGS) settings_open();
    else if (kind == K_ABOUT) about_open();
}
// wall.c -- the desktop's picture. docs/c4ix-desktop.md.
//
// The boot logo (/usr/share/splash/c4ix.c4p.gz, what splash shows),
// stretched over the whole desktop. It goes to the display once (and
// again when the screen changes size), as WALL_TX x WALL_TY tiles the
// display keeps (d_imgdef: each tile has
// to fit the command ring), and every redraw of the desktop's
// background draws the tiles it needs (d_image), clipped to the
// damage as everything else is. Settings turns it off and on
// (theme_set / theme_wall, /etc/desktop.cfg).
//
// The image is 256 colours, gzipped: "C4P8", width, height, colours
// (16-bit little-endian), the RGB palette, a byte per pixel
// (src/c4ix/art/mkc4p.py; user/splash.c reads the same).

#include "desktop.h"
#include "archive.h"

enum { WALL_TX = 8, WALL_TY = 8, WALL_ID = 100 };

static int wall_ok;                      // the tiles are on the display
static int wall_tw, wall_th;             // a tile's size on the desktop
static int wall_tile[(WK_MAX_W / WALL_TX) * (WK_MAX_H / WALL_TY)];
static char *wall_pix;                   // the picture, kept to stretch again
static int wall_w, wall_h, wall_lut[256];

// Give the display the tiles, stretched from the picture to the screen
// as it is now (nearest pixel: the logo is made at 800x600, so it is 1:1
// there). A new screen size needs nothing new from memory.
static void wall_tiles() {
    int tx, ty, x, y, sx, sy;
    wall_tw = wk.sw / WALL_TX;
    wall_th = wk.sh / WALL_TY;
    ty = 0;
    while (ty < WALL_TY) {
        tx = 0;
        while (tx < WALL_TX) {
            y = 0;
            while (y < wall_th) {
                sy = (ty * wall_th + y) * wall_h / wk.sh;
                x = 0;
                while (x < wall_tw) {
                    sx = (tx * wall_tw + x) * wall_w / wk.sw;
                    wall_tile[y * wall_tw + x] = wall_lut[wall_pix[sy * wall_w + sx] & 255];
                    ++x;
                }
                ++y;
            }
            d_imgdef(WALL_ID + ty * WALL_TX + tx, wall_tw, wall_th, wall_tile);
            ++tx;
        }
        ++ty;
    }
}

// Load the picture and give the display its tiles. 1 if it can be shown.
// The inflated picture is kept (the gzipped file is not).
int wall_load(char *path) {
    char *gz, *d;
    int glen, dlen, w, h, n, i;
    if (wall_ok) return 1;
    if (!(gz = arc_readfile(path, &glen))) return 0;
    i = arc_gunzip(gz, glen, &d, &dlen);
    free(gz);
    if (i < 0) return 0;
    if (dlen < 10 || d[0] != 'C' || d[1] != '4' || d[2] != 'P' || d[3] != '8') { free(d); return 0; }
    w = (d[4] & 255) | ((d[5] & 255) << 8);
    h = (d[6] & 255) | ((d[7] & 255) << 8);
    n = (d[8] & 255) | ((d[9] & 255) << 8);
    if (w < 1 || h < 1 || n < 1 || n > 256 || dlen < 10 + 3 * n + w * h) { free(d); return 0; }
    i = 0;
    while (i < n) {
        wall_lut[i] = ((d[10 + 3 * i] & 255) << 16) | ((d[11 + 3 * i] & 255) << 8) | (d[12 + 3 * i] & 255);
        ++i;
    }
    wall_pix = d + 10 + 3 * n;
    wall_w = w; wall_h = h;
    wall_tiles();
    wall_ok = 1;
    return 1;
}

// The screen changed size: the tiles again, at the new one.
void wall_resize() {
    if (wall_ok && (wall_tw != wk.sw / WALL_TX || wall_th != wk.sh / WALL_TY)) wall_tiles();
}

// The picture over X, Y, W, H, or 0 if there is none to draw.
int wall_draw(int x, int y, int w, int h) {
    int tx, ty;
    if (!wall_ok || !theme_wall()) return 0;
    ty = y / wall_th;
    while (ty < WALL_TY && ty * wall_th < y + h) {
        tx = x / wall_tw;
        while (tx < WALL_TX && tx * wall_tw < x + w) {
            d_image(WALL_ID + ty * WALL_TX + tx, tx * wall_tw, ty * wall_th);
            ++tx;
        }
        ++ty;
    }
    return 1;
}

int wall_shown() { return wall_ok && theme_wall(); }
// calc.c -- Calculator, a window kit class. docs/c4ix-desktop.md,
// docs/grin-plan.md 4.
//
// A programmer's calculator in three modes. Integer: 32-bit words shown
// in Hex, Dec, Oct or Bin, with the bitwise operators. Single and Double:
// IEEE floating point (docs/c4-float.md), each operation done in that
// precision -- c4lc's float and double, so in software unless the
// machine has an FPU -- with the value shown as the shortest decimal
// that reads back to it, and its bits under it. 0.1 + 0.2 is
// 0.30000000000000004 in Double and 0.3 in Single; Max * 2 is inf.
//
// Ctrl+C copies the display and Ctrl+V types the clipboard in.
//
// The decimal conversions are libc's fp.c (src/c4ix/libc), linked into
// the shell: exact both ways. (fp.c sets errno, which the shell owns.)

#include "winkit.h"

int __c4ix_fmtfp(char *o, double x, int conv, int prec, int alt, int plus, int space);
double strtod(char *s, char **end);
float strtof(char *s, char **end);

enum { M_INT = 0, M_SINGLE = 1, M_DOUBLE = 2 };

struct calc {
    int acc, cur, op, radix, fresh, err;        // Integer mode's
    int lastop, lastb;                          // what = did, for = again
    int mode;
    double dacc, dcur;                          // Single and Double's (a Single value is exactly a double)
    double dlastb;
    int typed;                                  // a number being typed: TEXT is it
    char text[40];
    char disp[48];                              // what the display shows, and the bits line
    char bits[24];
};

static struct calc *C(int w) { return (struct calc *)wk_state(w); }
static char buf[64];

// the key grids: 6 columns, 5 rows
static char *keys[30] = {
    "D", "E", "F", "Mod", "And", "Not",
    "A", "B", "C", "/", "Or", "Xor",
    "7", "8", "9", "*", "Lsh", "Rsh",
    "4", "5", "6", "-", "+/-", "Back",
    "1", "2", "3", "+", "0", "="
};
static char *fkeys[30] = {
    "Sqrt", "x^2", "1/x", "Int", "Pi", "e",
    "Exp", "Max", "Eps", "/", "Min", "Inf",
    "7", "8", "9", "*", ".", "Abs",
    "4", "5", "6", "-", "+/-", "Back",
    "1", "2", "3", "+", "0", "="
};

static void refresh(struct calc *c);

static void calc_open_hook(int w, char *arg) {
    C(w)->radix = 10;
    C(w)->fresh = 1;
    refresh(C(w));
}

int calc_open() {
    calc_class.size = sizeof(struct calc);
    return wk_open(&calc_class, "Calculator", 360, 332, WK_FIXED, 0);
}

// ---- Integer -----------------------------------------------------------------------

static int apply(struct calc *c, int a, int b, int op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/' || op == '%') {
        if (!b) { c->err = 1; return 0; }
        return op == '/' ? a / b : a % b;
    }
    if (op == '&') return a & b;
    if (op == '|') return a | b;
    if (op == '^') return a ^ b;
    if (op == '<') return a << (b & 31);
    if (op == '>') {                         // logical: zeros come in from the top
        b = b & 31;
        if (!b) return a;
        return (a >> b) & (0x7fffffff >> (b - 1));
    }
    return b;
}

// the value in the current radix
static char *show(struct calc *c, char *out) {
    char t[40];
    int n, v, k, d;
    if (c->err) { ui_cpy(out, "Cannot divide by zero"); return out; }
    v = c->fresh && c->op ? c->acc : c->cur;
    if (c->radix == 10) return ui_num(out, v);
    n = 0;
    if (v == 0) { t[0] = '0'; n = 1; }
    while (v != 0 && n < 32) {
        d = v & (c->radix - 1);
        t[n] = d < 10 ? '0' + d : 'A' + d - 10;
        ++n;
        if (c->radix == 16) v = (v >> 4) & 0x0fffffff;
        else if (c->radix == 8) v = (v >> 3) & 0x1fffffff;
        else v = (v >> 1) & 0x7fffffff;
    }
    k = 0;
    while (n) { --n; out[k] = t[n]; ++k; }
    out[k] = 0;
    return out;
}

static int binop(char *key) {
    if (ui_eq(key, "+")) return '+';
    if (ui_eq(key, "-")) return '-';
    if (ui_eq(key, "*")) return '*';
    if (ui_eq(key, "/")) return '/';
    if (ui_eq(key, "Mod")) return '%';
    if (ui_eq(key, "And")) return '&';
    if (ui_eq(key, "Or")) return '|';
    if (ui_eq(key, "Xor")) return '^';
    if (ui_eq(key, "Lsh")) return '<';
    if (ui_eq(key, "Rsh")) return '>';
    if (ui_eq(key, "=")) return '=';
    return 0;
}

static void press_int(struct calc *c, char *key) {
    int d, op;
    d = 0 - 1;
    if (key[1] == 0 && key[0] >= '0' && key[0] <= '9') d = key[0] - '0';
    if (key[1] == 0 && key[0] >= 'A' && key[0] <= 'F') d = key[0] - 'A' + 10;
    if (d >= 0) {
        if (d >= c->radix) return;
        if (c->err) { c->err = 0; c->acc = 0; c->op = 0; }
        if (c->fresh) { c->cur = 0; c->fresh = 0; }
        c->cur = c->cur * c->radix + d;
        return;
    }
    if (ui_eq(key, "C")) { c->acc = 0; c->cur = 0; c->op = 0; c->lastop = 0; c->fresh = 1; c->err = 0; return; }
    if (ui_eq(key, "CE")) { c->cur = 0; c->fresh = 1; c->err = 0; return; }
    if (ui_eq(key, "Back")) { if (!c->fresh) c->cur = c->cur / c->radix; return; }
    if (ui_eq(key, "+/-")) { c->cur = 0 - c->cur; c->fresh = 0; return; }
    if (ui_eq(key, "Not")) { c->cur = ~c->cur; c->fresh = 0; return; }
    op = binop(key);
    if (!op) return;
    if (op == '=') {
        // = finishes what is pending ("5 + =" is 5 + 5), and = again does
        // the same to the answer: 2 + 3 = = is 8; a new number then = is
        // that number + 3
        if (c->op) {
            c->lastop = c->op;
            c->lastb = c->fresh ? c->acc : c->cur;
            c->acc = apply(c, c->acc, c->lastb, c->op);
        } else if (c->lastop) {
            if (!c->fresh) c->acc = c->cur;
            c->acc = apply(c, c->acc, c->lastb, c->lastop);
        } else c->acc = c->cur;
        c->cur = c->acc; c->op = 0; c->fresh = 1;
        return;
    }
    // a pending operation finishes first; two operators in a row replace
    if (c->op && !c->fresh) c->acc = apply(c, c->acc, c->cur, c->op);
    else if (!c->op) c->acc = c->cur;
    c->op = op;
    c->lastop = 0;
    c->fresh = 1;
}

// ---- Single and Double -------------------------------------------------------------

// a double rounded to single when the mode is Single
static double prec(struct calc *c, double v) { return c->mode == M_SINGLE ? (double)(float)v : v; }

static double c_sqrt(double x) {
    unsigned long long b;
    b = __c4d_sqrt(*(unsigned long long *)&x);
    return *(double *)&b;
}
static double c_bits(unsigned int hi, unsigned int lo) {
    unsigned long long b;
    b = ((unsigned long long)hi << 32) | lo;
    return *(double *)&b;
}

// each operation in the mode's own precision: float arithmetic in Single
static double fapply(struct calc *c, double a, double b, int op) {
    float x, y, r;
    if (c->mode == M_SINGLE) {
        x = (float)a; y = (float)b;
        if (op == '+') r = x + y;
        else if (op == '-') r = x - y;
        else if (op == '*') r = x * y;
        else if (op == '/') r = x / y;
        else r = y;
        return r;
    }
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return b;
}

static int c_has(char *s, int ch) { while (*s) { if (*s == ch) return 1; ++s; } return 0; }
static void c_parse(struct calc *c) {
    c->dcur = c->mode == M_SINGLE ? (double)strtof(c->text, 0) : strtod(c->text, 0);
}
static void c_append(struct calc *c, int ch) {
    int n;
    n = ui_len(c->text);
    if (n >= 32) return;
    c->text[n] = ch;
    c->text[n + 1] = 0;
}

// x towards zero, whole
static double c_trunc(double x) {
    unsigned long long b, m;
    int e;
    b = *(unsigned long long *)&x;
    e = (int)((b >> 52) & 2047) - 1023;
    if (e >= 52) return x;
    if (e < 0) return c_bits((unsigned int)(b >> 32) & 0x80000000, 0);
    m = 0x000FFFFFFFFFFFFFull >> e;
    b = b & ~m;
    return *(double *)&b;
}

// a unary key: the current value, replaced
static int funary(struct calc *c, char *key) {
    double v, r;
    int single;
    single = c->mode == M_SINGLE;
    v = c->dcur;
    if (ui_eq(key, "Sqrt")) r = c_sqrt(v);
    else if (ui_eq(key, "x^2")) r = fapply(c, v, v, '*');
    else if (ui_eq(key, "1/x")) r = fapply(c, 1.0, v, '/');
    else if (ui_eq(key, "Int")) r = c_trunc(v);
    else if (ui_eq(key, "Abs")) r = v < 0 ? 0.0 - v : v;
    else if (ui_eq(key, "Pi")) r = 3.14159265358979323846;
    else if (ui_eq(key, "e")) r = 2.71828182845904523536;
    else if (ui_eq(key, "Max")) r = single ? c_bits(0x47EFFFFF, 0xE0000000) : c_bits(0x7FEFFFFF, 0xFFFFFFFF);
    else if (ui_eq(key, "Min")) r = single ? c_bits(0x38100000, 0) : c_bits(0x00100000, 0);
    else if (ui_eq(key, "Eps")) r = single ? c_bits(0x3E800000, 0) : c_bits(0x3CB00000, 0);
    else if (ui_eq(key, "Inf")) r = c_bits(0x7FF00000, 0);
    else return 0;
    c->dcur = prec(c, r);
    c->typed = 0;
    c->fresh = 0;
    return 1;
}

static void press_fp(struct calc *c, char *key) {
    int op, n;
    if (key[1] == 0 && key[0] >= '0' && key[0] <= '9') {
        if (!c->typed) { c->text[0] = 0; c->typed = 1; c->fresh = 0; }
        c_append(c, key[0]);
        c_parse(c);
        return;
    }
    if (ui_eq(key, ".")) {
        if (!c->typed) { ui_cpy(c->text, "0"); c->typed = 1; c->fresh = 0; }
        if (!c_has(c->text, '.') && !c_has(c->text, 'e')) c_append(c, '.');
        c_parse(c);
        return;
    }
    if (ui_eq(key, "Exp")) {
        if (!c->typed) { ui_cpy(c->text, "1"); c->typed = 1; c->fresh = 0; }
        if (!c_has(c->text, 'e')) c_append(c, 'e');
        c_parse(c);
        return;
    }
    if (ui_eq(key, "C")) { c->dacc = 0; c->dcur = 0; c->op = 0; c->lastop = 0; c->fresh = 1; c->typed = 0; return; }
    if (ui_eq(key, "CE")) { c->dcur = 0; c->fresh = 1; c->typed = 0; return; }
    if (ui_eq(key, "Back")) {
        if (!c->typed) return;
        n = ui_len(c->text);
        if (n > 0) c->text[n - 1] = 0;
        c_parse(c);
        return;
    }
    if (ui_eq(key, "+/-")) {
        if (c->typed) {
            // the exponent's sign once one is being typed, else the number's
            n = 0;
            while (c->text[n] && c->text[n] != 'e') ++n;
            if (!c->text[n]) n = 0 - 1;
            if (c->text[n + 1] == '-') ui_cpy(c->text + n + 1, c->text + n + 2);
            else if (ui_len(c->text) < 32) {
                ui_cpy(buf, c->text + n + 1);
                c->text[n + 1] = '-';
                ui_cpy(c->text + n + 2, buf);
            }
            c_parse(c);
        } else { c->dcur = 0.0 - c->dcur; c->fresh = 0; }
        return;
    }
    if (funary(c, key)) return;
    op = binop(key);
    if (op != '+' && op != '-' && op != '*' && op != '/' && op != '=') return;
    c->typed = 0;
    if (op == '=') {
        // as Integer's: = again repeats the last operation on the answer
        if (c->op) {
            c->lastop = c->op;
            c->dlastb = c->fresh ? c->dacc : c->dcur;
            c->dacc = fapply(c, c->dacc, c->dlastb, c->op);
        } else if (c->lastop) {
            if (!c->fresh) c->dacc = c->dcur;
            c->dacc = fapply(c, c->dacc, c->dlastb, c->lastop);
        } else c->dacc = c->dcur;
        c->dcur = c->dacc; c->op = 0; c->fresh = 1;
        return;
    }
    if (c->op && !c->fresh) c->dacc = fapply(c, c->dacc, c->dcur, c->op);
    else if (!c->op) c->dacc = c->dcur;
    c->op = op;
    c->lastop = 0;
    c->fresh = 1;
}

static int c_toint(double v) {
    if (!(v == v)) return 0;
    if (v >= 2147483647.0) return 2147483647;
    if (v <= -2147483648.0) return 0 - 2147483647 - 1;
    return (int)v;
}

static void set_mode(struct calc *c, int mode) {
    if (mode == c->mode) return;
    if (c->mode == M_INT) { c->dacc = c->acc; c->dcur = c->cur; c->err = 0; }
    else if (mode == M_INT) { c->acc = c_toint(c->dacc); c->cur = c_toint(c->dcur); }
    c->mode = mode;
    c->lastop = 0;
    c->dacc = prec(c, c->dacc);
    c->dcur = prec(c, c->dcur);
    c->typed = 0;
}

// the shortest %g that reads back as the value (9 digits always do for a
// single, 17 for a double), and the bits
static char *hex8(char *o, unsigned int v) {
    int i, d;
    i = 0;
    while (i < 8) { d = (v >> (28 - 4 * i)) & 15; o[i] = d < 10 ? '0' + d : 'A' + d - 10; ++i; }
    o[8] = 0;
    return o + 8;
}
static void refresh(struct calc *c) {
    double v, back;
    unsigned long long b;
    float f;
    int p, maxp;
    char *o;
    if (c->mode == M_INT) { show(c, c->disp); c->bits[0] = 0; return; }
    v = c->fresh && c->op ? c->dacc : c->dcur;
    if (c->typed && !(c->fresh && c->op)) ui_cpy(c->disp, c->text);
    else {
        maxp = c->mode == M_SINGLE ? 9 : 17;
        p = 1;
        while (p < maxp) {
            __c4ix_fmtfp(c->disp, v, 'g', p, 0, 0, 0);
            back = c->mode == M_SINGLE ? (double)strtof(c->disp, 0) : strtod(c->disp, 0);
            if (back == v) break;
            ++p;
        }
        __c4ix_fmtfp(c->disp, v, 'g', p, 0, 0, 0);
    }
    if (c->mode == M_SINGLE) {
        f = (float)v;
        hex8(c->bits, *(unsigned int *)&f);
    } else {
        b = *(unsigned long long *)&v;
        o = hex8(c->bits, (unsigned int)(b >> 32));
        *o = ' ';
        hex8(o + 1, (unsigned int)b);
    }
}

static void press(struct calc *c, char *key) {
    if (c->mode == M_INT) press_int(c, key); else press_fp(c, key);
    refresh(c);
}

// ---- drawing and input -------------------------------------------------------------

enum { KW = 50, KH = 30, KX = 12, KY = 128 };
static char *radix_names[4] = { "Hex", "Dec", "Oct", "Bin" };
static int radix_values[4] = { 16, 10, 8, 2 };
static char *mode_names[3] = { "Integer", "Single", "Double" };

static void calc_draw(int w, int cw, int ch, int focused) {
    struct calc *c;
    int k, x, y;
    char **ks;
    c = C(w);
    d_rect(0, 0, cw, ch, C_FACE);
    // the display: right-aligned in a sunken white field
    d_rect(10, 10, cw - 20, 24, C_WHITE);
    d_bevel(10, 10, cw - 20, 24, B_SUNKEN);
    d_textn(cw - 16 - ui_len(c->disp) * 8, 15, C_DARK, 14, F_MONO, 8, c->disp, 0 - 1);
    // the radix, or the bits of a float
    ui_group(10, 40, 214, 44, "");
    if (c->mode == M_INT) {
        k = 0;
        while (k < 4) { ui_radio(20 + k * 50, 60, radix_names[k], c->radix == radix_values[k]); ++k; }
    } else {
        d_text(20, 50, C_SHADOW, F_SANS, c->mode == M_SINGLE ? "IEEE single, bits:" : "IEEE double, bits:");
        d_textn(20, 66, C_DARK, 12, F_MONO, 7, c->bits, 0 - 1);
    }
    ui_button(cw - 118, 50, 50, 28, "CE", 0, 0);
    ui_button(cw - 62, 50, 50, 28, "C", 0, 0);
    // the mode
    ui_group(10, 88, cw - 20, 32, "");
    k = 0;
    while (k < 3) { ui_radio(20 + k * 90, 100, mode_names[k], c->mode == k); ++k; }
    ks = c->mode == M_INT ? keys : fkeys;
    k = 0;
    while (k < 30) {
        x = KX + (k % 6) * (KW + 6);
        y = KY + (k / 6) * (KH + 6);
        ui_button(x, y, KW, KH, ks[k], 0, 0);
        ++k;
    }
    if (c->op) { buf[0] = c->op == '<' ? 'L' : c->op == '>' ? 'R' : c->op; buf[1] = 0; d_text(14, 16, C_SHADOW, F_SANS, buf); }
}

static void calc_mouse(int w, int ev, int x, int y, int b) {
    struct calc *c;
    int k, cw, ch;
    c = C(w);
    if (ev != E_DOWN) return;
    wk_size(w, &cw, &ch);
    k = 0;
    while (k < 4 && c->mode == M_INT) {
        if (ui_hit(x, y, 20 + k * 50, 58, 46, 16)) { c->radix = radix_values[k]; refresh(c); return; }
        ++k;
    }
    k = 0;
    while (k < 3) {
        if (ui_hit(x, y, 20 + k * 90, 98, 80, 16)) { set_mode(c, k); refresh(c); return; }
        ++k;
    }
    if (ui_hit(x, y, cw - 118, 50, 50, 28)) { press(c, "CE"); return; }
    if (ui_hit(x, y, cw - 62, 50, 50, 28)) { press(c, "C"); return; }
    k = 0;
    while (k < 30) {
        if (ui_hit(x, y, KX + (k % 6) * (KW + 6), KY + (k / 6) * (KH + 6), KW, KH)) {
            press(c, c->mode == M_INT ? keys[k] : fkeys[k]);
            return;
        }
        ++k;
    }
}

static void calc_key(int w, int down, int code, int ch, int mods);

// Ctrl+C copies what the display shows; Ctrl+V types the clipboard in,
// a key a character, as Windows' Calculator took a paste (C4IX's desktop
// and grin alike: the kit's clipboard)
static void calc_clip(int w, int paste) {
    struct calc *c;
    char *t;
    int n, k;
    c = C(w);
    if (!paste) {
        k = 0;
        while (c->disp[k] == ' ') ++k;
        wk_clip_set(c->disp + k, ui_len(c->disp + k));
        return;
    }
    t = wk_clip_get(&n);
    k = 0;
    while (k < n && k < 200) { if (t[k] > 32 && t[k] < 127) calc_key(w, 1, 0, t[k], 0); ++k; }
}

static void calc_key(int w, int down, int code, int ch, int mods) {
    struct calc *c;
    char k[2];
    if (!down) return;
    c = C(w);
    k[1] = 0;
    if (ui_key_copy(code, ch, mods)) { calc_clip(w, 0); return; }
    if (ui_key_paste(code, ch, mods)) { calc_clip(w, 1); return; }
    if (mods & M_CTRL) return;
    if (c->mode != M_INT) {
        if (ch == '.' || ch == ',') { press(c, "."); return; }
        if (ch == 'e' || ch == 'E') { press(c, "Exp"); return; }
        if (ch == 'p' || ch == 'P') { press(c, "Pi"); return; }
        if (ch == 'r' || ch == 'R') { press(c, "Sqrt"); return; }
    }
    if (ch >= 'a' && ch <= 'f') ch = ch - 32;
    if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F')) { k[0] = ch; press(c, k); return; }
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { k[0] = ch; press(c, k); return; }
    if (ch == '=' || code == KEY_ENTER) { press(c, "="); return; }
    if (ch == '%') { press(c, "Mod"); return; }
    if (ch == '&') { press(c, "And"); return; }
    if (ch == '|') { press(c, "Or"); return; }
    if (ch == '^') { press(c, "Xor"); return; }
    if (ch == '~') { press(c, "Not"); return; }
    if (ch == '<') { press(c, "Lsh"); return; }
    if (ch == '>') { press(c, "Rsh"); return; }
    if (code == KEY_BACK) { press(c, "Back"); return; }
    if (code == KEY_ESC) { press(c, "C"); return; }
    if (code == KEY_DEL) { press(c, "CE"); return; }
}

struct wk_class calc_class = {
    .kind = ICON_CALC, .open = calc_open_hook, .draw = calc_draw, .mouse = calc_mouse, .key = calc_key
};
// clock.c -- Clock: the time of day, on a face or in figures, as a window
// kit class. docs/grin-plan.md 4. The smallest application, and the one
// grin's loader is first proved with.

#include "winkit.h"

enum { C_ANALOG = 0, C_DIGITAL = 1 };
struct clock { int digital; };

// sin(6k degrees) * 1000, k = 0..15: a minute's step around the face
static int sine[16] = { 0, 105, 208, 309, 407, 500, 588, 669, 743, 809, 866, 914, 951, 978, 995, 1000 };
static int sin60(int k) {
    k = k % 60;
    if (k < 0) k = k + 60;
    if (k <= 15) return sine[k];
    if (k <= 30) return sine[30 - k];
    if (k <= 45) return 0 - sine[k - 30];
    return 0 - sine[60 - k];
}

static char *settings_items[3] = { "Analog", "Digital", 0 };
static struct wk_menu menus[1];
static char tbuf[16];

static void hand(int cx, int cy, int pos, int len, int thick, int rgb) {
    int x, y;
    x = cx + len * sin60(pos) / 1000;
    y = cy - len * sin60(pos + 15) / 1000;
    d_line(cx, cy, x, y, rgb);
    if (thick) { d_line(cx + 1, cy, x + 1, y, rgb); d_line(cx, cy + 1, x, y + 1, rgb); }
}

static void two(char *p, int v) { p[0] = '0' + v / 10; p[1] = '0' + v % 10; }

static void clock_draw(int w, int cw, int ch, int focused) {
    struct clock *c;
    int t, h, m, s, cx, cy, r, k, x, y;
    c = (struct clock *)wk_state(w);
    t = wk_clock();
    h = t / 3600; m = (t / 60) % 60; s = t % 60;
    d_rect(0, 0, cw, ch, C_FACE);
    if (c->digital) {
        two(tbuf, h); tbuf[2] = ':'; two(tbuf + 3, m); tbuf[5] = ':'; two(tbuf + 6, s); tbuf[8] = 0;
        d_textn((cw - 8 * 15) / 2, (ch - 24) / 2, C_DARK, 24, F_MONO, 15, tbuf, 8);
        return;
    }
    cx = cw / 2; cy = ch / 2;
    r = (cw < ch ? cw : ch) / 2 - 8;
    if (r < 10) r = 10;
    d_disc(cx, cy, r + 2, C_SHADOW);
    d_disc(cx, cy, r, C_WHITE);
    // the hours as squares, the minutes as dots
    k = 0;
    while (k < 60) {
        x = cx + (r - 6) * sin60(k) / 1000;
        y = cy - (r - 6) * sin60(k + 15) / 1000;
        if (k % 5 == 0) d_rect(x - 2, y - 2, 4, 4, C_TITLE);
        else d_rect(x, y, 1, 1, C_SHADOW);
        ++k;
    }
    hand(cx, cy, (h % 12) * 5 + m / 12, r * 5 / 10, 1, C_DARK);
    hand(cx, cy, m, r * 8 / 10, 1, C_DARK);
    hand(cx, cy, s, r * 9 / 10, 0, 0xc02020);
    d_disc(cx, cy, 3, C_DARK);
}

static void clock_tick(int w, int id) { wk_invalidate(w, 0, 0, 0, 0); }

static void clock_command(int w, int id) {
    struct clock *c;
    c = (struct clock *)wk_state(w);
    c->digital = id % WK_CMD_STEP == C_DIGITAL;
    wk_invalidate(w, 0, 0, 0, 0);
}

static void clock_open_hook(int w, char *arg) {
    menus[0].title = "Settings"; menus[0].items = settings_items;
    wk_menu(w, menus, 1);
    wk_timer(w, 1, 1000);
}

struct wk_class clock_class = {
    .kind = ICON_CLOCK, .open = clock_open_hook, .draw = clock_draw, .timer = clock_tick,
    .command = clock_command
};

int clock_open() {
    clock_class.size = sizeof(struct clock);
    return wk_open(&clock_class, "Clock", 240, 260, 0, 0);
}
// dialog.c -- the window kit's dialogs: message, input and file boxes.
// docs/grin-plan.md 3.4.
//
// Each is a window of its own class, modal while it is on top. Its state
// is its own -- the text being typed, the message, the folder listed --
// so two dialogs open at once never share anything (the desktop review's
// B7 and B10). The answer goes to the window that asked, through its
// class's answer hook, or to the shell's when no window did; an input or
// file box copies what was typed into the asker's buffer first, if the
// asker is still open.

#include "wkwin.h"

enum { DLG_LINES = 16, DLG_TEXT = 512, LINE_CHARS = 82 };

// a message or input box; the file box's state begins the same way
struct dlg {
    char *buf;                    // where an answer's text goes (input, file)
    int max;                      // ... and its size
    char out[WK_PATH];            // the text: typed (input), or the path chosen (file)
    int caret;
    int buttons;                  // a message box's: WK_OK or WK_YESNO
    int nlines, ls[DLG_LINES], ll[DLG_LINES];   // a long message, wrapped
    char text[DLG_TEXT];          // the message, or the input box's prompt
};

void wk_dialog_answer(struct win *d, int yes) {
    struct dlg *g;
    int owner, dialog;
    g = (struct dlg *)d->st;
    owner = d->owner; dialog = d->action;
    if (yes && g->buf && g->max > 0 && (owner <= 0 || win_get(owner))) ui_ncpy(g->buf, g->out, g->max);
    wk_close(d->id);
    wk_answer_owner(owner, dialog, yes);
}

static struct win *dialog_open(struct wk_class *c, int size, int owner, int dialog, char *title, int w, int h) {
    int i;
    struct win *d;
    c->size = size;
    i = wk_open(c, title, w, h, WK_DIALOG | WK_FIXED | WK_CENTER, 0);
    if (i < 0 || !(d = win_get(i))) return 0;
    d->owner = owner > 0 ? owner : 0;
    d->action = dialog;
    return d;
}

static void buttons_draw(int cw, int ch, char *a, char *b) {
    ui_button(cw - 176, ch - 34, 76, 24, a, 0, 1);
    ui_button(cw - 88, ch - 34, 76, 24, b, 0, 0);
}
static int buttons_hit(int x, int y, int cw, int ch) {
    if (ui_hit(x, y, cw - 176, ch - 34, 76, 24)) return 1;
    if (ui_hit(x, y, cw - 88, ch - 34, 76, 24)) return 0;
    return 0 - 1;
}

// ---- message boxes ---------------------------------------------------------------
//
// One line as long as it fits the widest box; a longer message is broken
// at spaces into lines, and the box grows to hold them.

static void msg_wrap(struct dlg *g) {
    int n, s, k, brk;
    n = ui_len(g->text);
    g->nlines = 0;
    s = 0;
    while (s < n && g->nlines < DLG_LINES) {
        k = s; brk = 0 - 1;
        while (k < n && k - s < LINE_CHARS) { if (g->text[k] == ' ') brk = k; ++k; }
        if (k < n && brk > s) k = brk;
        g->ls[g->nlines] = s; g->ll[g->nlines] = k - s;
        ++g->nlines;
        s = k;
        while (s < n && g->text[s] == ' ') ++s;
    }
}

static void msg_draw(int w, int cw, int ch, int focused) {
    struct dlg *g;
    int bx, k;
    g = (struct dlg *)wk_state(w);
    d_rect(0, 0, cw, ch, C_FACE);
    d_disc(30, 30, 14, g->buttons ? C_TITLE : 0xd02020);
    d_textn(26, 20, C_WHITE, 18, F_BOLD, 0, g->buttons ? "?" : "i", 1);
    if (g->nlines <= 1) d_text(56, 24, C_DARK, F_SANS, g->text);
    else {
        k = 0;
        while (k < g->nlines) { d_textn(56, 24 + k * 16, C_DARK, 11, F_SANS, 0, g->text + g->ls[k], g->ll[k]); ++k; }
    }
    if (g->buttons) {
        bx = cw / 2 - 84;
        ui_button(bx, ch - 34, 76, 24, g->buttons == WK_OKCANCEL ? "OK" : "Yes", 0, 1);
        ui_button(bx + 92, ch - 34, 76, 24, g->buttons == WK_OKCANCEL ? "Cancel" : "No", 0, 0);
    } else ui_button(cw / 2 - 38, ch - 34, 76, 24, "OK", 0, 1);
}

static void msg_mouse(int w, int ev, int x, int y, int b) {
    struct dlg *g;
    struct win *d;
    int bx, cw, ch;
    if (ev != E_DOWN || !(d = win_get(w))) return;
    g = (struct dlg *)d->st;
    wk_size(w, &cw, &ch);
    if (g->buttons) {
        bx = cw / 2 - 84;
        if (ui_hit(x, y, bx, ch - 34, 76, 24)) wk_dialog_answer(d, 1);
        else if (ui_hit(x, y, bx + 92, ch - 34, 76, 24)) wk_dialog_answer(d, 0);
    } else if (ui_hit(x, y, cw / 2 - 38, ch - 34, 76, 24)) wk_dialog_answer(d, 1);
}

static void msg_key(int w, int down, int code, int ch, int mods) {
    struct dlg *g;
    struct win *d;
    if (!down || !(d = win_get(w))) return;
    g = (struct dlg *)d->st;
    if (code == KEY_ESC) { wk_dialog_answer(d, 0); return; }
    if (code == KEY_ENTER) { wk_dialog_answer(d, 1); return; }
    if (g->buttons == WK_YESNO && (ch == 'y' || ch == 'Y')) wk_dialog_answer(d, 1);
    else if (g->buttons == WK_YESNO && (ch == 'n' || ch == 'N')) wk_dialog_answer(d, 0);
}

struct wk_class wk_msg_class = { .kind = ICON_MSG, .draw = msg_draw, .mouse = msg_mouse, .key = msg_key };

void wk_msgbox(int owner, int dialog, char *title, char *text, int buttons) {
    struct win *d;
    struct dlg *g;
    int tw;
    tw = ui_len(text) * 6 + 40;
    if (tw < 260) tw = 260;
    if (tw > 560) tw = 560;
    if (!(d = dialog_open(&wk_msg_class, sizeof(struct dlg), owner, dialog, title, tw, 120))) return;
    g = (struct dlg *)d->st;
    g->buttons = buttons;
    ui_ncpy(g->text, text, DLG_TEXT);
    msg_wrap(g);
    if (g->nlines > 1) { d->h = 120 + 16 * (g->nlines - 1); d->y = (wk.sh - d->h) / 2 - 40; }
}

// ---- input boxes -------------------------------------------------------------------

static void input_draw(int w, int cw, int ch, int focused) {
    struct dlg *g;
    g = (struct dlg *)wk_state(w);
    d_rect(0, 0, cw, ch, C_FACE);
    d_text(12, 12, C_DARK, F_SANS, g->text);
    ui_field(12, 30, cw - 24, g->out, g->caret, 1);
    buttons_draw(cw, ch, "OK", "Cancel");
}

static void input_mouse(int w, int ev, int x, int y, int b) {
    struct dlg *g;
    struct win *d;
    int cw, ch, k;
    if (ev != E_DOWN || !(d = win_get(w))) return;
    g = (struct dlg *)d->st;
    wk_size(w, &cw, &ch);
    if ((k = buttons_hit(x, y, cw, ch)) >= 0) { wk_dialog_answer(d, k); return; }
    if (ui_hit(x, y, 12, 30, cw - 24, 22)) g->caret = ui_field_hit(x, 12, cw - 24, g->out, g->caret);
}

static void input_key(int w, int down, int code, int ch, int mods) {
    struct dlg *g;
    struct win *d;
    int max;
    if (!down || !(d = win_get(w))) return;
    g = (struct dlg *)d->st;
    if (code == KEY_ESC) { wk_dialog_answer(d, 0); return; }
    if (code == KEY_ENTER) { wk_dialog_answer(d, 1); return; }
    max = g->max > 0 && g->max <= WK_PATH ? g->max - 1 : WK_PATH - 1;
    ui_field_key(g->out, max, &g->caret, code, ch, mods);
}

struct wk_class wk_input_class = { .kind = ICON_INPUT, .draw = input_draw, .mouse = input_mouse, .key = input_key };

void wk_inputbox(int owner, int dialog, char *title, char *prompt, char *buf, int max) {
    struct win *d;
    struct dlg *g;
    if (!(d = dialog_open(&wk_input_class, sizeof(struct dlg), owner, dialog, title, 380, 130))) return;
    g = (struct dlg *)d->st;
    g->buf = buf; g->max = max;
    ui_ncpy(g->text, prompt, DLG_TEXT);
    if (buf) ui_ncpy(g->out, buf, max > 0 && max <= WK_PATH ? max : WK_PATH);
    g->caret = ui_len(g->out);
}

// ---- file boxes ----------------------------------------------------------------------
//
// The folder's contents, folders first, then a name. A double click on a
// folder (or "..") goes into it; on a file, or OK with a name, answers
// with the folder and the name joined. A name with a * in it is a pattern
// instead: the files it matches are listed.
//
// The types a box offers are its pattern: "*", or Windows' filter string,
// a label and its patterns in turn, "C Source (*.c;*.h)|*.c;*.h|All
// Files (*)|*". The first is shown to start with. This file draws the box
// in Windows 3.1's look, which shows the first type's files; look95.c
// draws Windows 95's, with a list to choose the type from.

char *wk_fb_name(struct fdlg *f, int k) { return f->names + f->order[k] * WK_NAME; }
static char *fname(struct fdlg *f, int k) { return wk_fb_name(f, k); }

// the k'th field of the filter, '|' between them, into out: 0 if none
static int fb_field(char *s, int k, char *out, int n) {
    int i;
    while (k > 0 && *s) { if (*s == '|') --k; ++s; }
    if (k > 0) return 0;
    i = 0;
    while (s[i] && s[i] != '|' && i < n - 1) { out[i] = s[i]; ++i; }
    out[i] = 0;
    return 1;
}
static int fb_bar(char *s) { while (*s) { if (*s == '|') return 1; ++s; } return 0; }

int wk_fb_types(struct fdlg *f) {
    int n;
    char t[4];
    if (!fb_bar(f->filter)) return 1;
    n = 0;
    while (fb_field(f->filter, 2 * n + 1, t, 4)) ++n;
    return n > 0 ? n : 1;
}

void wk_fb_label(struct fdlg *f, int i, char *out, int n) {
    if (fb_bar(f->filter)) { fb_field(f->filter, 2 * i, out, n); return; }
    ui_ncpy(out, ui_eq(f->filter, "*") || !f->filter[0] ? "All Files (*)" : f->filter, n);
}

void wk_fb_type(struct fdlg *f, int i) {
    if (i < 0 || i >= wk_fb_types(f)) i = 0;
    f->ftype = i;
    if (!fb_bar(f->filter) || !fb_field(f->filter, 2 * i + 1, f->pattern, WK_NAME)) ui_ncpy(f->pattern, f->filter, WK_NAME);
    wk_fb_list(f);
}

// name's end is end, whatever the letters' case
static int fb_ends(char *name, char *end, int n) {
    int k, a, b;
    k = ui_len(name);
    if (n > k) return 0;
    name = name + k - n;
    k = 0;
    while (k < n) {
        a = name[k]; b = end[k];
        if (a >= 'A' && a <= 'Z') a = a + 32;
        if (b >= 'A' && b <= 'Z') b = b + 32;
        if (a != b) return 0;
        ++k;
    }
    return 1;
}

// a folder always; a file if one of the patterns takes it ("*", "*.c", or a name)
static int fb_wanted(struct fdlg *f, char *name, int dir) {
    char *p;
    int n;
    if (dir || !f->pattern[0]) return 1;
    p = f->pattern;
    while (*p) {
        n = 0;
        while (p[n] && p[n] != ';') ++n;
        if (n == 1 && p[0] == '*') return 1;
        if (n > 1 && p[0] == '*' && fb_ends(name, p + 1, n - 1)) return 1;
        if (n > 0 && p[0] != '*' && n == ui_len(name) && fb_ends(name, p, n)) return 1;
        p = p + n;
        if (*p == ';') ++p;
    }
    return 0;
}

static int fb_before(struct fdlg *f, int a, int b) {
    char *p, *q;
    if (f->isdir[a] != f->isdir[b]) return f->isdir[a];
    p = f->names + a * WK_NAME; q = f->names + b * WK_NAME;
    while (*p && *p == *q) { ++p; ++q; }
    return (*p & 255) < (*q & 255);
}

void wk_fb_list(struct fdlg *f) {
    int i, k, j, r;
    char name[WK_NAME];
    f->n = 0; f->top = 0; f->sel = 0 - 1;
    if (f->dir[0] && !ui_eq(f->dir, "/") && !f->up) {
        ui_cpy(f->names, ".."); f->isdir[0] = 1; f->order[0] = 0; f->n = 1;
    }
    i = 0;
    while (f->n < FB_MAX && (r = wk_readdir(f->dir, i, name)) >= 0) {
        ++i;
        name[WK_NAME - 1] = 0;
        if (name[0] == '.' && (!name[1] || (name[1] == '.' && !name[2]))) continue;
        if (!fb_wanted(f, name, r)) continue;
        ui_ncpy(f->names + f->n * WK_NAME, name, WK_NAME);
        f->isdir[f->n] = r;
        // into order, folders first and by name (".." stays first)
        k = f->n;
        j = f->n && ui_eq(f->names, "..") ? 1 : 0;
        while (k > j && fb_before(f, f->n, f->order[k - 1])) { f->order[k] = f->order[k - 1]; --k; }
        f->order[k] = f->n;
        ++f->n;
    }
}

void wk_fb_enter(struct fdlg *f, char *name) {
    int k;
    if (ui_eq(name, "..")) {
        k = ui_len(f->dir);
        while (k > 1 && f->dir[k - 1] == '/') --k;
        while (k > 0 && f->dir[k - 1] != '/') --k;
        if (k > 1) --k;
        if (k < 1) k = 1;
        f->dir[k] = 0;
    } else if (!ui_join(f->dir, f->dir, name, WK_PATH)) return;
    wk_fb_list(f);
    wk_redraw_all();
}
static void fb_enter(struct fdlg *f, char *name) { wk_fb_enter(f, name); }

// OK, or a double click on a file: the folder and the name joined
void wk_fb_ok(struct win *d, struct fdlg *f) {
    int k;
    char name[WK_NAME];
    k = 0;
    while (k < f->n) { if (f->isdir[f->order[k]] && ui_eq(fname(f, k), f->out)) { fb_enter(f, f->out); f->out[0] = 0; f->caret = 0; return; } ++k; }
    // nothing typed: the folder picked, if one is
    if (!f->out[0] && f->sel >= 0 && f->sel < f->n && f->isdir[f->order[f->sel]]) { ui_ncpy(name, fname(f, f->sel), WK_NAME); fb_enter(f, name); return; }
    if (!f->out[0]) return;
    // a pattern: the files it takes
    k = 0;
    while (f->out[k] && f->out[k] != '*') ++k;
    if (f->out[k] == '*' && f->out[0] != '/') { ui_ncpy(f->pattern, f->out, WK_NAME); f->out[0] = 0; f->caret = 0; wk_fb_list(f); wk_redraw_all(); return; }
    if (f->out[0] != '/') {                     // a name: in the folder shown
        ui_ncpy(name, f->out, WK_NAME);
        if (!ui_join(f->out, f->dir, name, WK_PATH)) { ui_ncpy(f->out, name, WK_NAME); return; }
    }
    wk_dialog_answer(d, 1);
}

static void fb_ok(struct win *d, struct fdlg *f) { wk_fb_ok(d, f); }

static void file_draw(int w, int cw, int ch, int focused) {
    struct fdlg *f;
    int k, y, lw;
    f = (struct fdlg *)wk_state(w);
    d_rect(0, 0, cw, ch, C_FACE);
    d_text(12, 10, C_DARK, F_SANS, f->dir);
    lw = cw - 24;
    d_rect(12, 28, lw, FB_ROWS * FB_ROW + 4, C_WHITE);
    d_bevel(12, 28, lw, FB_ROWS * FB_ROW + 4, B_SUNKEN);
    k = f->top; y = 30;
    while (k < f->n && k < f->top + FB_ROWS) {
        if (k == f->sel) d_rect(14, y, lw - 22, FB_ROW, C_SEL);
        if (f->isdir[f->order[k]]) d_icon(ICON_FILES, 16, y);
        d_text(36, y + 2, k == f->sel ? C_WHITE : C_DARK, F_SANS, fname(f, k));
        y = y + FB_ROW;
        ++k;
    }
    ui_scrollbar(12 + lw - 18, 30, FB_ROWS * FB_ROW, f->n, FB_ROWS, f->top);
    d_text(12, ch - 64, C_DARK, F_SANS, f->save ? "Save as:" : "File name:");
    ui_field(80, ch - 68, cw - 92, f->out, f->caret, 1);
    buttons_draw(cw, ch, f->save ? "Save" : "Open", "Cancel");
}

static void file_mouse(int w, int ev, int x, int y, int b) {
    struct fdlg *f;
    struct win *d;
    int cw, ch, k, t, lw;
    if (!(d = win_get(w))) return;
    f = (struct fdlg *)d->st;
    wk_size(w, &cw, &ch);
    lw = cw - 24;
    if (ev == E_WHEEL) {
        f->top = f->top + b * 3;
        if (f->top > f->n - FB_ROWS) f->top = f->n - FB_ROWS;
        if (f->top < 0) f->top = 0;
        return;
    }
    if (ev == E_MOVE) { t = ui_scroll_drag(12 + lw - 18, 30, y); if (t >= 0) f->top = t; return; }
    if (ev != E_DOWN && ev != E_DBL) return;
    if (ev == E_DOWN && (k = buttons_hit(x, y, cw, ch)) >= 0) { if (k) fb_ok(d, f); else wk_dialog_answer(d, 0); return; }
    t = ui_scroll_click(x, y, 12 + lw - 18, 30, FB_ROWS * FB_ROW, f->n, FB_ROWS, f->top);
    if (t >= 0) { f->top = t; return; }
    if (ui_hit(x, y, 14, 30, lw - 22, FB_ROWS * FB_ROW)) {
        k = f->top + (y - 30) / FB_ROW;
        if (k >= f->n) return;
        f->sel = k;
        if (ev == E_DBL) {
            if (f->isdir[f->order[k]]) { fb_enter(f, fname(f, k)); return; }
            ui_ncpy(f->out, fname(f, k), WK_PATH);
            fb_ok(d, f);
            return;
        }
        if (!f->isdir[f->order[k]]) { ui_ncpy(f->out, fname(f, k), WK_PATH); f->caret = ui_len(f->out); }
        return;
    }
    if (ui_hit(x, y, 80, ch - 68, cw - 92, 22)) f->caret = ui_field_hit(x, 80, cw - 92, f->out, f->caret);
}

static void file_key(int w, int down, int code, int ch, int mods) {
    struct fdlg *f;
    struct win *d;
    if (!down || !(d = win_get(w))) return;
    f = (struct fdlg *)d->st;
    if (code == KEY_ESC) { wk_dialog_answer(d, 0); return; }
    if (code == KEY_ENTER) { fb_ok(d, f); return; }
    if (code == KEY_BACK && !f->out[0]) { fb_enter(f, ".."); return; }
    ui_field_key(f->out, WK_NAME - 1, &f->caret, code, ch, mods);
}

struct wk_class wk_file_class = { .kind = ICON_FILEBOX, .draw = file_draw, .mouse = file_mouse, .key = file_key };

void wk_filebox(int owner, int dialog, int save, char *pattern, char *buf, int max) {
    struct win *d;
    struct fdlg *f;
    char *s;
    int k;
    if (wk.style == S_WIN31) d = dialog_open(&wk_file_class, sizeof(struct fdlg), owner, dialog, save ? "Save As" : "Open", 420, 330);
    else d = dialog_open(&wk_file95_class, sizeof(struct fdlg), owner, dialog, save ? "Save As" : "Open", 470, 330);
    if (!d) return;
    f = (struct fdlg *)d->st;
    f->buf = buf; f->max = max; f->save = save;
    f->up = wk.style != S_WIN31;
    ui_ncpy(f->filter, pattern ? pattern : "*", WK_PATH);
    // buf: a folder to start in, or a path whose folder it is and whose name is offered
    f->dir[0] = '/'; f->dir[1] = 0;
    if (buf && buf[0] == '/') {
        ui_ncpy(f->dir, buf, WK_PATH);
        s = ui_base(f->dir);
        if (s[0] && !ui_ends(f->dir, "/")) { ui_ncpy(f->out, s, WK_NAME); k = s - f->dir; f->dir[k > 1 ? k - 1 : 1] = 0; }
    } else if (buf && buf[0]) ui_ncpy(f->out, buf, WK_NAME);
    f->caret = ui_len(f->out);
    wk_fb_type(f, 0);
}
// draw.c -- the window kit's drawing layer, over the display (gui.h).
// docs/grin-plan.md 3.5.
//
// Everything a window draws goes through d_*, relative to an origin --
// its client area's corner while its class draws, the screen's for the
// chrome and the shell -- and clipped to that client area. A redraw is
// either the whole scene, or only the damage: what changed on its own (a
// terminal's output, a clock) marks its rectangle, and the redraw draws
// only what lies in it, clipped to it, with no clear: the display keeps
// the rest of the last frame (docs/c4ix-cpu.md, step 11).

#include "wkwin.h"
#include "libjs/guest/gui.h"

struct wk_env wk;

// ---- colour schemes ----------------------------------------------------------
//
// Nine colours each: desktop, face, light and shadow edges, the active
// and inactive title bars (each a gradient's two ends), and the
// selection, which is the active title's first colour.
enum { N_SCHEMES = 9, S_COLS = 8 };
static char *scheme_names[N_SCHEMES] = {
    "Classic Teal", "Granite", "Drizzle", "Sandstone", "Blush", "Pine", "Lavender", "Thunder",
    "Modern"                          // the flat look's own: cool greys, slate title bars
};
static int schemes[N_SCHEMES * S_COLS] = {
    0x008080, 0xc0c0c0, 0xffffff, 0x808080, 0x000080, 0x1084d0, 0x808080, 0xb4b4b4,
    0x3a4e62, 0xb8c4cc, 0xeef3f6, 0x687884, 0x384c60, 0x7890a8, 0x808c98, 0xb0bcc8,
    0x48586c, 0xb4bcc4, 0xeef2f6, 0x707880, 0x4c5c7c, 0x8898b8, 0x80888c, 0xb0b8c0,
    0xa08060, 0xd5ccbb, 0xf5f0e8, 0xa29275, 0x008080, 0x40b0b0, 0xa29275, 0xc8bca8,
    0x804050, 0xcfafb7, 0xf3e4e8, 0x9f6070, 0x9f6070, 0xd090a0, 0xa08890, 0xc8b0b8,
    0x285040, 0xa2c8a9, 0xe2f2e6, 0x5e9a6a, 0x184830, 0x408048, 0x6a8a70, 0x9ab8a0,
    0x504878, 0xaea8d9, 0xeae6f8, 0x6c64a8, 0x504888, 0x8880c8, 0x8880a0, 0xb4b0d0,
    0x202830, 0xa8a8a8, 0xe8e8e8, 0x606060, 0x303848, 0x607088, 0x707070, 0x989898,
    0x2e3440, 0xeceff4, 0xffffff, 0xa0a8b4, 0x3b4252, 0x3b4252, 0xd8dee9, 0xd8dee9
};

int wk_scheme_count() { return N_SCHEMES; }
char *wk_scheme_name(int i) { return i >= 0 && i < N_SCHEMES ? scheme_names[i] : ""; }
void wk_scheme_use(int i, int desk) {
    int *t;
    if (i < 0 || i >= N_SCHEMES) i = 0;
    t = schemes + i * S_COLS;
    wk.desk = desk >= 0 ? desk : t[0];
    wk.face = t[1]; wk.light = t[2]; wk.shadow = t[3];
    wk.title = t[4]; wk.title2 = t[5]; wk.ititle = t[6]; wk.ititle2 = t[7]; wk.sel = t[4];
    wk_full = 1;
}

// ---- fonts -------------------------------------------------------------------------
//
// The interface's three faces, each with its bold, the editors' three
// fixed-width ones, and three sizes. A grid is a font size and a cell,
// the cell no narrower than the face's characters (0.6 of its size in
// Courier New, a little less in the others).
static char *face_names[WK_FACES] = { "Tahoma", "Verdana", "Georgia" };
static int faces[WK_FACES * 2] = { F_SANS, F_BOLD, F_VERDANA, F_VERDANA_B, F_SERIF, F_SERIF_B };
static char *mono_names[WK_FACES] = { "Consolas", "Courier New", "Lucida Console" };
static int monos[WK_FACES] = { F_MONO, F_COURIER, F_LUCIDA };
static char *size_names[WK_SIZES] = { "Small", "Normal", "Large" };
static int grids[WK_SIZES * 3] = { 10, 6, 13, 12, 7, 15, 14, 8, 17 };

char *wk_face_name(int i) { return i >= 0 && i < WK_FACES ? face_names[i] : ""; }
char *wk_mono_name(int i) { return i >= 0 && i < WK_FACES ? mono_names[i] : ""; }
int wk_mono_font(int i) { return i >= 0 && i < WK_FACES ? monos[i] : F_MONO; }
char *wk_size_name(int i) { return i >= 0 && i < WK_SIZES ? size_names[i] : ""; }
void wk_font_use(int face, int size) {
    if (face < 0 || face >= WK_FACES) face = 0;
    if (size < 0 || size >= WK_SIZES) size = 1;
    wk.fsans = faces[face * 2]; wk.fbold = faces[face * 2 + 1]; wk.fsize = size - 1;
    wk_full = 1;
}
void wk_grid(int size, int *font_size, int *cw, int *ch) {
    if (size < 0 || size >= WK_SIZES) size = 1;
    *font_size = grids[size * 3]; *cw = grids[size * 3 + 1]; *ch = grids[size * 3 + 2];
}

int ui_mix(int a, int b, int t, int n) {
    int r, g, bl;
    r = ((a >> 16) & 255) + ((((b >> 16) & 255) - ((a >> 16) & 255)) * t) / n;
    g = ((a >> 8) & 255) + ((((b >> 8) & 255) - ((a >> 8) & 255)) * t) / n;
    bl = (a & 255) + (((b & 255) - (a & 255)) * t) / n;
    return (r << 16) | (g << 8) | bl;
}

// ---- damage --------------------------------------------------------------------

int wk_full, wk_part;
int wk_dmg, wk_dmg_x0, wk_dmg_y0, wk_dmg_x1, wk_dmg_y1;

void wk_redraw_all() { wk_full = 1; }

void wk_dirty_rect(int x, int y, int w, int h) {
    if (wk_full || w <= 0 || h <= 0) return;
    if (x < 0) { w = w + x; x = 0; }
    if (y < 0) { h = h + y; y = 0; }
    if (x + w > wk.sw) w = wk.sw - x;
    if (y + h > wk.sh) h = wk.sh - y;
    if (w <= 0 || h <= 0) return;
    if (!wk_dmg) { wk_dmg = 1; wk_dmg_x0 = x; wk_dmg_y0 = y; wk_dmg_x1 = x + w; wk_dmg_y1 = y + h; return; }
    if (x < wk_dmg_x0) wk_dmg_x0 = x;
    if (y < wk_dmg_y0) wk_dmg_y0 = y;
    if (x + w > wk_dmg_x1) wk_dmg_x1 = x + w;
    if (y + h > wk_dmg_y1) wk_dmg_y1 = y + h;
}

int wk_in_damage(int x, int y, int w, int h) {
    if (!wk_part) return 1;
    return x < wk_dmg_x1 && x + w > wk_dmg_x0 && y < wk_dmg_y1 && y + h > wk_dmg_y0;
}

// Clipping, always inside the damage while only the damage is drawn: the
// clip a window sets for its title or its client area must not reach past
// what is being redrawn, or it would draw over what is not.
void wk_clip_screen(int x, int y, int w, int h) {
    int x1, y1;
    if (wk_part) {
        x1 = x + w; y1 = y + h;
        if (x < wk_dmg_x0) x = wk_dmg_x0;
        if (y < wk_dmg_y0) y = wk_dmg_y0;
        if (x1 > wk_dmg_x1) x1 = wk_dmg_x1;
        if (y1 > wk_dmg_y1) y1 = wk_dmg_y1;
        w = x1 > x ? x1 - x : 0;
        h = y1 > y ? y1 - y : 0;
    }
    gui_clip(x, y, w, h);
}
void wk_noclip() {
    if (wk_part) gui_clip(wk_dmg_x0, wk_dmg_y0, wk_dmg_x1 - wk_dmg_x0, wk_dmg_y1 - wk_dmg_y0);
    else gui_noclip();
}

// ---- the origin, and drawing narrowed to part of a client area ------------------

static int ox, oy;                        // where d_* draw from, on the screen
static int clip_x, clip_y, clip_w, clip_h;

void wk_origin(int x, int y) { ox = x; oy = y; }
void wk_client_clip(int x, int y, int w, int h) {
    clip_x = x; clip_y = y; clip_w = w; clip_h = h;
    wk_clip_screen(x, y, w, h);
}

// An app's pane, and back to all of its client area: never wider than that.
void d_clip(int x, int y, int w, int h) {
    int x1, y1;
    x = x + ox; y = y + oy;
    x1 = x + w; y1 = y + h;
    if (x < clip_x) x = clip_x;
    if (y < clip_y) y = clip_y;
    if (x1 > clip_x + clip_w) x1 = clip_x + clip_w;
    if (y1 > clip_y + clip_h) y1 = clip_y + clip_h;
    wk_clip_screen(x, y, x1 > x ? x1 - x : 0, y1 > y ? y1 - y : 0);
}
void d_clip_end() { wk_clip_screen(clip_x, clip_y, clip_w, clip_h); }

// ---- the drawing -----------------------------------------------------------------

void d_rect(int x, int y, int w, int h, int rgb) { if (w > 0 && h > 0) gui_rect(x + ox, y + oy, w, h, rgb); }
void d_recto(int x, int y, int w, int h, int rgb) { gui_recto(x + ox, y + oy, w, h, rgb); }
void d_line(int x0, int y0, int x1, int y1, int rgb) { gui_line(x0 + ox, y0 + oy, x1 + ox, y1 + oy, rgb); }
void d_disc(int x, int y, int r, int rgb) { gui_disc(x + ox, y + oy, r, rgb); }
// F_SANS and F_BOLD in the interface's face and size, when one was chosen
// (wk_font_use; grin never does); every other font as it is
void d_text(int x, int y, int rgb, int font, char *s) { d_textn(x, y, rgb, 11, font, 0, s, 0 - 1); }
void d_textn(int x, int y, int rgb, int size, int font, int advance, char *s, int n) {
    if (font == F_SANS && wk.fsans) { font = wk.fsans; size = size + wk.fsize; }
    else if (font == F_BOLD && wk.fbold) { font = wk.fbold; size = size + wk.fsize; }
    gui_text2(x + ox, y + oy, rgb, size, font, advance, s, n);
}
void d_imgdef(int id, int w, int h, int *px) { gui_imgdef(id, w, h, px); }
void d_image(int id, int x, int y) { gui_image(id, x + ox, y + oy); }
void d_blit8(int x, int y, int w, int h, char *src, int pitch, int *pal, int dw, int dh) {
    gui_blit8(x + ox, y + oy, w, h, src, pitch, pal, dw, dh);
}

// While only the damage is drawn: 1 if all of it is inside this part of
// the client area, so what a draw paints around that part is not seen
int d_damage_within(int x, int y, int w, int h) {
    x = x + ox; y = y + oy;
    return wk_part && wk_dmg_x0 >= x && wk_dmg_y0 >= y && wk_dmg_x1 <= x + w && wk_dmg_y1 <= y + h;
}

// The bevels: two pixels, light top-left, dark bottom-right (or the other
// way round for a sunken one). Flat draws an outline, the accent's when
// pressed; Classic and Windows 3.1 bevel.
void d_bevel(int x, int y, int w, int h, int style) {
    int a, b, c, d;
    x = x + ox; y = y + oy;
    if (wk.style == S_FLAT) {
        if (w > 1 && h > 1) gui_recto(x, y, w - 1, h - 1, style == B_PRESSED ? C_TITLE : C_SHADOW);
        return;
    }
    if (style == B_ETCHED) {
        gui_recto(x, y, w - 1, h - 1, C_SHADOW);
        gui_recto(x + 1, y + 1, w - 1, h - 1, C_LIGHT);
        return;
    }
    if (style == B_RAISED) { a = C_LIGHT; b = C_DARK; c = C_FACE; d = C_SHADOW; }
    else if (style == B_PRESSED) { a = C_DARK; b = C_LIGHT; c = C_SHADOW; d = C_FACE; }
    else { a = C_SHADOW; b = C_LIGHT; c = C_DARK; d = C_FACE; }
    gui_rect(x, y, w, 1, a);             gui_rect(x, y, 1, h, a);
    gui_rect(x, y + h - 1, w, 1, b);     gui_rect(x + w - 1, y, 1, h, b);
    gui_rect(x + 1, y + 1, w - 2, 1, c); gui_rect(x + 1, y + 1, 1, h - 2, c);
    gui_rect(x + 1, y + h - 2, w - 2, 1, d); gui_rect(x + w - 2, y + 1, 1, h - 2, d);
}

// 16x16 pictures for each kind of window: title bars, the taskbar, icons.
void d_icon(int kind, int x, int y) {
    x = x + ox; y = y + oy;
    if (kind == ICON_TERM) {
        gui_rect(x, y + 1, 16, 13, C_DARK); gui_recto(x, y + 1, 16, 13, C_SHADOW);
        gui_text2(x + 2, y + 3, 0xc0c0c0, 8, F_MONO, 0, ">_", 2);
    } else if (kind == ICON_FILES) {
        gui_rect(x, y + 3, 7, 3, 0xc8a000); gui_rect(x, y + 5, 16, 10, 0xffd84a);
        gui_recto(x, y + 5, 16, 10, 0x806000);
    } else if (kind == ICON_TASKS) {
        gui_rect(x, y + 1, 16, 12, C_DARK); gui_recto(x, y + 1, 16, 12, C_SHADOW);
        gui_line(x + 2, y + 10, x + 6, y + 5, C_GREEN); gui_line(x + 6, y + 5, x + 9, y + 8, C_GREEN);
        gui_line(x + 9, y + 8, x + 14, y + 3, C_GREEN); gui_rect(x + 5, y + 13, 6, 2, C_SHADOW);
    } else if (kind == ICON_EDIT) {
        gui_rect(x + 1, y, 14, 16, C_WHITE); gui_recto(x + 1, y, 14, 16, C_SHADOW);
        gui_text2(x + 2, y + 3, 0x008000, 8, F_MONO, 0, "{}", 2);
        gui_rect(x + 3, y + 12, 10, 1, 0x4060c0);
    } else if (kind == ICON_NOTE) {
        gui_rect(x + 2, y, 12, 16, C_WHITE); gui_recto(x + 2, y, 12, 16, C_SHADOW);
        gui_rect(x + 4, y + 4, 8, 1, 0x4060c0); gui_rect(x + 4, y + 7, 8, 1, 0x4060c0);
        gui_rect(x + 4, y + 10, 6, 1, 0x4060c0);
    } else if (kind == ICON_SETTINGS) {
        // a gear: a disc with teeth, and a hole
        gui_rect(x + 7, y, 3, 16, 0x707070); gui_rect(x, y + 7, 16, 3, 0x707070);
        gui_line(x + 2, y + 2, x + 13, y + 13, 0x707070); gui_line(x + 13, y + 2, x + 2, y + 13, 0x707070);
        gui_line(x + 3, y + 2, x + 14, y + 13, 0x707070); gui_line(x + 12, y + 2, x + 1, y + 13, 0x707070);
        gui_disc(x + 8, y + 8, 6, 0x909090);
        gui_disc(x + 8, y + 8, 2, C_FACE);
    } else if (kind == ICON_CALC) {
        gui_rect(x + 2, y, 12, 16, 0xa0a0a0); gui_recto(x + 2, y, 12, 16, C_DARK);
        gui_rect(x + 4, y + 2, 8, 4, 0xd0ffd0);
        gui_rect(x + 4, y + 8, 3, 2, C_DARK); gui_rect(x + 9, y + 8, 3, 2, C_DARK);
        gui_rect(x + 4, y + 12, 3, 2, C_DARK); gui_rect(x + 9, y + 12, 3, 2, 0xc02020);
    } else if (kind == ICON_CLOCK) {
        gui_disc(x + 8, y + 8, 7, C_DARK); gui_disc(x + 8, y + 8, 6, C_WHITE);
        gui_line(x + 8, y + 8, x + 8, y + 4, C_DARK); gui_line(x + 8, y + 8, x + 11, y + 8, C_DARK);
    } else {
        gui_rect(x + 1, y + 1, 14, 14, C_WHITE); gui_recto(x + 1, y + 1, 14, 14, C_TITLE);
        gui_text2(x + 6, y + 2, C_TITLE, 12, F_BOLD, 0, "i", 1);
    }
}

int wk_clock() { return gui_clock(); }
// look31.c -- window chrome: Windows 3.1. docs/grin-plan.md 3.5.
//
// A thick sizing border, black-edged and notched where a drag moves two
// edges at once; a solid title bar with the title centred in it; the
// control-menu box on its left (a click opens the window's menu, a double
// click closes the window); and raised minimise and maximise buttons on
// its right, arrows pointing down and up (both, once maximised, for
// Restore). There is no close button: 3.1 closed from the control menu.
// A dialog has the box alone, and a frame in the title's colour. The
// measures are the other looks', so a window's client area is the same
// size whichever look draws it.
//
// It also draws minimised windows as icons along the bottom of the
// screen, for a shell that asks (wk_min_icons; below).

#include "wkwin.h"
#include "wkgui.h"

enum { BOX = TITLE_H, NOTCH = TITLE_H + BORDER };

// arrowheads four rows deep: up has its point at y, down at y + 3
static void up(int cx, int y) { int i; i = 0; while (i < 4) { gui_rect(cx - i, y + i, 2 * i + 1, 1, C_DARK); ++i; } }
static void down(int cx, int y) { int i; i = 0; while (i < 4) { gui_rect(cx - i, y + 3 - i, 2 * i + 1, 1, C_DARK); ++i; } }

// a raised button on the title bar, black on its left
static void caption_button(int x, int y, int what) {
    int cx;
    gui_rect(x, y, 1, BOX, C_DARK);
    gui_rect(x + 1, y, BOX - 1, BOX, C_FACE);
    gui_rect(x + 1, y, BOX - 1, 1, C_LIGHT); gui_rect(x + 1, y, 1, BOX - 1, C_LIGHT);
    gui_rect(x + 1, y + BOX - 1, BOX - 1, 1, C_SHADOW); gui_rect(x + BOX - 1, y, 1, BOX, C_SHADOW);
    gui_rect(x + 2, y + BOX - 2, BOX - 3, 1, C_SHADOW); gui_rect(x + BOX - 2, y + 1, 1, BOX - 2, C_SHADOW);
    cx = x + BOX / 2;
    if (what == HT_MIN) down(cx, y + 7);
    else if (what == HT_MAX) up(cx, y + 7);
    else { up(cx, y + 3); down(cx, y + 10); }
}

// the control-menu box: a bar like a space bar, on the face
static void sysbox(int x, int y) {
    gui_rect(x, y, BOX - 1, BOX, C_FACE);
    gui_rect(x + BOX - 1, y, 1, BOX, C_DARK);
    gui_rect(x + 4, y + 8, 11, 3, C_SHADOW);
    gui_rect(x + 3, y + 7, 11, 3, C_WHITE);
    gui_recto(x + 3, y + 7, 10, 2, C_DARK);
}

static void frame31(struct win *w, int focused) {
    int bg, ink, x1, x2, tw, tx, edge, x, y;
    x = w->x; y = w->y;
    // the frame: black outside and in, the border's colour between
    edge = w->dialog ? (focused ? C_TITLE : C_ITITLE) : C_FACE;
    gui_rect(x, y, w->w, w->h, edge);
    gui_recto(x, y, w->w - 1, w->h - 1, C_DARK);
    gui_recto(x + BORDER - 1, y + BORDER - 1, w->w - 2 * BORDER + 1, w->h - 2 * BORDER + 1, C_DARK);
    if (w->resizable && !w->max) {
        // the notches: where a drag on the border moves two edges
        gui_rect(x + NOTCH, y, 1, BORDER, C_DARK);            gui_rect(x + w->w - 1 - NOTCH, y, 1, BORDER, C_DARK);
        gui_rect(x + NOTCH, y + w->h - BORDER, 1, BORDER, C_DARK); gui_rect(x + w->w - 1 - NOTCH, y + w->h - BORDER, 1, BORDER, C_DARK);
        gui_rect(x, y + NOTCH, BORDER, 1, C_DARK);            gui_rect(x, y + w->h - 1 - NOTCH, BORDER, 1, C_DARK);
        gui_rect(x + w->w - BORDER, y + NOTCH, BORDER, 1, C_DARK); gui_rect(x + w->w - BORDER, y + w->h - 1 - NOTCH, BORDER, 1, C_DARK);
    }
    // inside: the face, then the title bar and the black line under it
    gui_rect(x + BORDER, y + BORDER, w->w - 2 * BORDER, w->h - 2 * BORDER, C_FACE);
    bg = focused ? C_TITLE : C_LIGHT;
    gui_rect(x + BORDER, y + BORDER, w->w - 2 * BORDER, TITLE_H, bg);
    gui_rect(x + BORDER, y + BORDER + TITLE_H, w->w - 2 * BORDER, 1, C_DARK);
    sysbox(x + BORDER, y + BORDER);
    x1 = x + BORDER + BOX;
    x2 = x + w->w - BORDER;
    if (!w->dialog) {
        x2 = x2 - 2 * BOX;
        caption_button(x2, y + BORDER, HT_MIN);
        caption_button(x2 + BOX, y + BORDER, w->max ? HT_NONE : HT_MAX);
    }
    // the title, centred between the box and the buttons (its width a
    // guess: the host's fonts cannot be measured from here)
    ink = wk_ink(bg);
    tw = ui_len(w->title) * 7;
    tx = x1 + (x2 - x1 - tw) / 2;
    if (tx < x1 + 4) tx = x1 + 4;
    wk_clip_screen(x1, y + BORDER, x2 - x1 > 0 ? x2 - x1 : 0, TITLE_H);
    d_text(tx, y + BORDER + 3, ink, F_BOLD, w->title);
    wk_noclip();
}

// the menu bar: black on white, the menu open shown inverted, a black line under it
static void menubar31(struct win *w, int focused, int open, int hot) {
    int k, x, y, lw;
    y = w->y + BORDER + TITLE_H + 1;
    gui_rect(wk_client_x(w), y, wk_client_w(w), MENU_H - 1, C_WHITE);
    gui_rect(wk_client_x(w), y + MENU_H - 1, wk_client_w(w), 1, C_DARK);
    x = wk_client_x(w) + 4;
    k = 0;
    while (k < w->nmenus) {
        lw = wk_menu_w(w, k);
        if (open == k) gui_rect(x, y + 1, lw, MENU_H - 3, C_SEL);
        d_text(x + 6, y + 4, open == k ? C_WHITE : C_DARK, F_SANS, w->menus[k].title);
        x = x + lw;
        ++k;
    }
}

static int hit31(struct win *w, int x, int y) {
    int e, x2, ty;
    ty = w->y + BORDER;
    if (ui_hit(x, y, w->x + BORDER, ty, BOX, TITLE_H)) return HT_SYSMENU;
    x2 = w->x + w->w - BORDER - 2 * BOX;
    if (!w->dialog && ui_hit(x, y, x2, ty, BOX, TITLE_H)) return HT_MIN;
    if (!w->dialog && ui_hit(x, y, x2 + BOX, ty, BOX, TITLE_H)) return HT_MAX;
    // the sizing border, its ends moving two edges
    if (w->resizable && !w->max) {
        e = 0;
        if (x < w->x + BORDER) e = SZ_L;
        else if (x >= w->x + w->w - BORDER) e = SZ_R;
        if (y < w->y + BORDER) e = e | SZ_T;
        else if (y >= w->y + w->h - BORDER) e = e | SZ_B;
        if (e) {
            if (e == SZ_L || e == SZ_R) {
                if (y < w->y + NOTCH) e = e | SZ_T;
                else if (y >= w->y + w->h - NOTCH) e = e | SZ_B;
            } else if (e == SZ_T || e == SZ_B) {
                if (x < w->x + NOTCH) e = e | SZ_L;
                else if (x >= w->x + w->w - NOTCH) e = e | SZ_R;
            }
            return HT_SIZE + e;
        }
    }
    if (y < w->y + BORDER + TITLE_H) return HT_CAPTION;
    if (w->nmenus && y < wk_client_y(w)) return HT_MENUBAR;
    if (ui_hit(x, y, wk_client_x(w), wk_client_y(w), wk_client_w(w), wk_client_h(w))) return HT_CLIENT;
    return HT_NONE;
}

struct wk_look look_win31 = { .frame = frame31, .menubar = menubar31, .hit = hit31, .title_centred = 1 };

// ---- minimised windows as icons ------------------------------------------------
//
// Windows 3.1 kept a minimised window on the desktop as an icon: a
// picture with the window's title under it, in a row along the bottom of
// the screen filled from the left, under the windows (one can cover an
// icon). A click opens the window's control menu over the icon, a double
// click restores it. A shell asks for this (wk_min_icons, grin does);
// otherwise minimising only hides a window, as in the C4IX desktop,
// whose taskbar brings it back. Each icon keeps the place it was given
// when its window was minimised, the first one free, until Arrange Icons
// packs them again.

enum { SLOT_W = 76, SLOT_H = 64, PIC = 32 };
int wk_icons_on;
int wk_icon_sel;

void wk_min_icons(int on) { wk_icons_on = on != 0; wk_full = 1; }

static int per_row() { int n; n = wk.aw / SLOT_W; return n > 0 ? n : 1; }

// place s (0 up): its picture's corner. The rows go up from the bottom.
static void slot_xy(int s, int *x, int *y) {
    *x = wk.ax + (s % per_row()) * SLOT_W + (SLOT_W - PIC) / 2;
    *y = wk.ay + wk.ah - (s / per_row() + 1) * SLOT_H + 4;
}

void wk_icon_place(struct win *w) {
    struct win *q;
    int s;
    s = 1;
    q = win_first();
    while (q) {
        if (q != w && q->used && q->min && q->islot == s) { ++s; q = win_first(); }
        else q = q->next;
    }
    w->islot = s;
}

void wk_arrange_icons() {
    struct win *q;
    int s;
    s = 1;
    q = win_first();
    while (q) { if (q->used && q->min) { q->islot = s; ++s; } q = q->next; }
    wk_full = 1;
}

void wk_icon_xy(struct win *w, int *x, int *y) {
    if (!w->islot) wk_icon_place(w);
    slot_xy(w->islot - 1, x, y);
}

struct win *wk_icon_hit(int px, int py) {
    struct win *w;
    int x, y;
    if (!wk_icons_on) return 0;
    w = win_first();
    while (w) {
        if (w->used && w->min) {
            wk_icon_xy(w, &x, &y);
            if (ui_hit(px, py, x - (SLOT_W - PIC) / 2, y, SLOT_W, SLOT_H - 4)) return w;
        }
        w = w->next;
    }
    return 0;
}

// the picture: a little window in the title's colour, with its kind's icon in it
static void icon_picture(struct win *w, int x, int y) {
    gui_rect(x, y + 2, PIC, PIC - 4, C_WHITE);
    gui_recto(x, y + 2, PIC - 1, PIC - 5, C_DARK);
    gui_rect(x + 1, y + 3, PIC - 2, 5, C_TITLE);
    gui_rect(x + 1, y + 8, PIC - 2, 1, C_DARK);
    d_icon(w->kind, x + 8, y + 11);
}

static void label_line(int cx, int y, char *s, int n, int sel) {
    int lw;
    lw = n * 6 + 4;
    gui_rect(cx - lw / 2, y - 1, lw, 13, sel ? C_SEL : C_DESK);    // over a pattern too
    d_textn(cx - lw / 2 + 2, y, sel ? C_WHITE : wk_ink(C_DESK), 11, F_SANS, 0, s, n);
}

// the title under it: on one line if it fits the place, else on two,
// broken at the space nearest its middle (its width a guess, as the title bar's)
static void icon_label(struct win *w, int x, int y, int sel) {
    char *t;
    int n, k, brk, d, bd, cx;
    t = w->title; n = ui_len(t);
    cx = x + PIC / 2;
    brk = 0 - 1;
    if (n * 6 > SLOT_W - 4) {
        bd = n; k = 1;
        while (k < n) {
            if (t[k] == ' ') { d = k - n / 2; if (d < 0) d = 0 - d; if (d < bd) { bd = d; brk = k; } }
            ++k;
        }
    }
    if (brk < 0) { label_line(cx, y + PIC + 2, t, n, sel); return; }
    label_line(cx, y + PIC + 2, t, brk, sel);
    label_line(cx, y + PIC + 15, t + brk + 1, n - brk - 1, sel);
}

void wk_icons_draw() {
    struct win *w;
    int x, y;
    if (!wk_icons_on) return;
    w = win_first();
    while (w) {
        if (w->used && w->min) {
            wk_icon_xy(w, &x, &y);
            if (wk_in_damage(x - (SLOT_W - PIC) / 2, y, SLOT_W, SLOT_H)) {
                icon_picture(w, x, y);
                icon_label(w, x, y, w->id == wk_icon_sel);
            }
        }
        w = w->next;
    }
}
// look95.c -- window chrome: the Flat and Classic looks. docs/grin-plan.md 3.5.
//
// Classic is Windows 95's: a raised frame, a title bar shading from one
// colour to another, the window's icon and title on the left, and raised
// minimise, maximise and close buttons on the right. Flat keeps the
// layout and draws it with outlines and solid colours. Both draw the
// kit's file box as Windows 95's Open and Save As (below).

#include "wkwin.h"
#include "wkgui.h"

void wk_gradient(int x, int y, int w, int h, int a, int b) {
    int i, n, bw;
    if (wk.style != S_CLASSIC) { gui_rect(x, y, w, h, a); return; }
    n = 16; bw = (w + n - 1) / n;
    i = 0;
    while (i < n) {
        if (i * bw < w) gui_rect(x + i * bw, y, (i + 1) * bw > w ? w - i * bw : bw, h, ui_mix(a, b, i, n - 1));
        ++i;
    }
}

// white on a dark bar, the scheme's dark on a light one
int wk_ink(int bg) {
    return (((bg >> 16) & 255) + ((bg >> 8) & 255) + (bg & 255)) < 384 ? C_WHITE : 0x404850;
}

enum { CAP_CLOSE = 0, CAP_MAX = 1, CAP_RESTORE = 2, CAP_MIN = 3 };
static int cap_ink, cap_bg;           // flat: the glyph's colour and the bar's under it

static void cap_button(int x, int y, int what) {
    int k;
    k = C_DARK;
    if (wk.style == S_FLAT) k = cap_ink;
    else { gui_rect(x, y, 16, 14, C_FACE); d_bevel(x, y, 16, 14, B_RAISED); }
    if (what == CAP_CLOSE) {                       // an X
        gui_line(x + 4, y + 3, x + 10, y + 9, k); gui_line(x + 5, y + 3, x + 11, y + 9, k);
        gui_line(x + 10, y + 3, x + 4, y + 9, k); gui_line(x + 11, y + 3, x + 5, y + 9, k);
    } else if (what == CAP_MAX) {
        gui_recto(x + 3, y + 2, 9, 9, k); gui_rect(x + 3, y + 3, 9, 1, k);
    } else if (what == CAP_RESTORE) {
        gui_recto(x + 5, y + 2, 7, 6, k); gui_rect(x + 5, y + 3, 7, 1, k);
        gui_rect(x + 3, y + 5, 7, 6, wk.style == S_FLAT ? cap_bg : C_FACE);
        gui_recto(x + 3, y + 5, 7, 6, k); gui_rect(x + 3, y + 6, 7, 1, k);
    } else gui_rect(x + 4, y + 9, 6, 2, k);        // minimise
}

static void frame95(struct win *w, int focused) {
    int tx, bx, by, ink;
    gui_rect(w->x, w->y, w->w, w->h, C_FACE);
    if (wk.style == S_FLAT) {
        cap_bg = focused ? C_TITLE : C_ITITLE;
        gui_rect(w->x, w->y, w->w, BORDER + TITLE_H, cap_bg);
        gui_recto(w->x, w->y, w->w - 1, w->h - 1, focused ? C_TITLE : C_SHADOW);
        ink = wk_ink(cap_bg);
        cap_ink = ink;
    } else {
        d_bevel(w->x, w->y, w->w, w->h, B_RAISED);
        if (focused) wk_gradient(w->x + BORDER, w->y + BORDER, w->w - 2 * BORDER, TITLE_H, C_TITLE, C_TITLE2);
        else wk_gradient(w->x + BORDER, w->y + BORDER, w->w - 2 * BORDER, TITLE_H, C_ITITLE, C_ITITLE2);
        ink = focused ? C_LIGHT : C_FACE;
    }
    tx = w->x + BORDER + 3;
    if (!w->dialog) { d_icon(w->kind, tx, w->y + BORDER + 1); tx = tx + 20; }
    wk_clip_screen(w->x + BORDER, w->y + BORDER, w->w - 2 * BORDER - 56, TITLE_H);
    d_text(tx, w->y + BORDER + 3, ink, F_BOLD, w->title);
    wk_noclip();
    by = w->y + BORDER + 2;
    bx = w->x + w->w - BORDER - 2 - 16;
    cap_button(bx, by, CAP_CLOSE);
    if (!w->dialog) {
        cap_button(bx - 18, by, w->max ? CAP_RESTORE : CAP_MAX);
        cap_button(bx - 34, by, CAP_MIN);
    }
}

static void menubar95(struct win *w, int focused, int open, int hot) {
    int k, x, y, lw;
    y = w->y + BORDER + TITLE_H + 1;
    gui_rect(wk_client_x(w), y, wk_client_w(w), MENU_H, C_FACE);
    x = wk_client_x(w) + 4;
    k = 0;
    while (k < w->nmenus) {
        lw = wk_menu_w(w, k);
        if (open == k) gui_rect(x, y + 1, lw, MENU_H - 2, C_SEL);
        d_text(x + 6, y + 4, open == k ? C_WHITE : C_DARK, F_SANS, w->menus[k].title);
        x = x + lw;
        ++k;
    }
}

// the size grip, over the client area's corner
static void grip95(struct win *w) {
    int bx, by;
    if (!w->resizable || w->max) return;
    bx = w->x + w->w - BORDER - 12; by = w->y + w->h - BORDER - 12;
    gui_line(bx + 3, by + 11, bx + 11, by + 3, C_LIGHT); gui_line(bx + 4, by + 11, bx + 11, by + 4, C_SHADOW);
    gui_line(bx + 7, by + 11, bx + 11, by + 7, C_LIGHT); gui_line(bx + 8, by + 11, bx + 11, by + 8, C_SHADOW);
}

static int hit95(struct win *w, int x, int y) {
    int bx, by;
    by = w->y + BORDER + 2;
    bx = w->x + w->w - BORDER - 2 - 16;
    if (ui_hit(x, y, bx, by, 16, 14)) return HT_CLOSE;
    if (!w->dialog && ui_hit(x, y, bx - 18, by, 16, 14)) return HT_MAX;
    if (!w->dialog && ui_hit(x, y, bx - 34, by, 16, 14)) return HT_MIN;
    if (y < w->y + BORDER + TITLE_H) return HT_CAPTION;
    if (w->resizable && !w->max && x >= w->x + w->w - 16 && y >= w->y + w->h - 16) return HT_SIZE + SZ_R + SZ_B;
    if (w->nmenus && y < wk_client_y(w)) return HT_MENUBAR;
    if (ui_hit(x, y, wk_client_x(w), wk_client_y(w), wk_client_w(w), wk_client_h(w))) return HT_CLIENT;
    return HT_NONE;
}

struct wk_look look_flat = { .frame = frame95, .menubar = menubar95, .hit = hit95, .grip = grip95 };
struct wk_look look_classic = { .frame = frame95, .menubar = menubar95, .hit = hit95, .grip = grip95 };

// ---- the file box, as Windows 95 drew it ---------------------------------------------
//
// dialog.c's file box (struct fdlg, wk_fb_*) laid out as Windows 95's
// Open and Save As: "Look in" with the folder shown, a list down from it
// of the folders above it to go back to, and a button up one; the
// folder's contents, folders first, each with its icon; the name, and
// "Files of type" with the types the box offers; Open or Save, and Cancel.
// A click picks an entry, a double click opens it; Up and Down walk the
// list, Backspace on an empty name goes up a folder.

enum { FB_LX = 10, FB_LY = 40, FB_FX = 100, FB_DROP_ROW = 16 };

static int fb_lw(int cw) { return cw - 2 * FB_LX; }
static int fb_lh(int ch) { return ch - FB_LY - 76; }
static int fb_rows(int ch) { return (fb_lh(ch) - 4) / FB_ROW; }
static int fb_cw(int cw) { return cw - FB_FX - 96; }        // the name field's and the type list's width
static int fb_look_w(int cw) { return cw - 78 - 40; }

// the folders above the one shown, and it: how many, and the k'th's path and depth
static int fb_depth(struct fdlg *f) {
    int k, n;
    n = 1; k = 1;
    while (f->dir[k]) { if (f->dir[k] == '/' || !f->dir[k + 1]) ++n; ++k; }
    return f->dir[1] ? n : 1;
}
static void fb_ancestor(struct fdlg *f, int k, char *out) {
    int i, seen;
    if (k == 0) { out[0] = '/'; out[1] = 0; return; }
    if (k >= fb_depth(f) - 1) { ui_ncpy(out, f->dir, WK_PATH); return; }
    i = 1; seen = 0;
    while (f->dir[i]) {
        if (f->dir[i] == '/') { ++seen; if (seen == k) break; }
        ++i;
    }
    ui_ncpy(out, f->dir, i + 1 < WK_PATH ? i + 1 : WK_PATH);
}

static char fbtmp[WK_PATH];

static void fb_folder_icon(int x, int y) {
    d_rect(x + 1, y + 3, 6, 2, 0xc8a000);
    d_rect(x + 1, y + 5, 14, 9, 0xffd84a);
    d_recto(x + 1, y + 5, 13, 8, 0xc8a000);
}
static void fb_file_icon(int x, int y) {
    d_rect(x + 3, y + 1, 10, 14, C_WHITE);
    d_recto(x + 3, y + 1, 9, 13, C_SHADOW);
    d_rect(x + 5, y + 5, 6, 1, C_SHADOW); d_rect(x + 5, y + 8, 6, 1, C_SHADOW); d_rect(x + 5, y + 11, 4, 1, C_SHADOW);
}

// a drop-down list's box: what is chosen, and the arrow that opens the list
static void fb_combo(int x, int y, int w, char *text, int folder) {
    int bx;
    d_rect(x, y, w, 22, C_WHITE);
    d_bevel(x, y, w, 22, B_SUNKEN);
    if (folder) fb_folder_icon(x + 4, y + 3);
    d_clip(x + 2, y + 2, w - 22, 18);
    d_text(x + (folder ? 24 : 6), y + 5, C_DARK, F_SANS, text);
    d_clip_end();
    bx = x + w - 19;
    d_rect(bx, y + 2, 17, 18, C_FACE);
    d_bevel(bx, y + 2, 17, 18, B_RAISED);
    d_line(bx + 4, y + 9, bx + 12, y + 9, C_DARK); d_line(bx + 5, y + 10, bx + 11, y + 10, C_DARK);
    d_line(bx + 6, y + 11, bx + 10, y + 11, C_DARK); d_line(bx + 7, y + 12, bx + 9, y + 12, C_DARK);
    d_rect(bx + 8, y + 13, 1, 1, C_DARK);
}

// the name a folder shows: its last part (a / after it or not), C4IX (/) for the top
static char fbname[WK_NAME];
static char *fb_folder_name(char *path) {
    int k, e;
    e = ui_len(path);
    while (e > 1 && path[e - 1] == '/') --e;
    if (e <= 1) return "C4IX (/)";
    k = e;
    while (k > 0 && path[k - 1] != '/') --k;
    ui_ncpy(fbname, path + k, e - k + 1 < WK_NAME ? e - k + 1 : WK_NAME);
    return fbname;
}

static void file95_draw(int w, int cw, int ch, int focused) {
    struct fdlg *f;
    int k, y, lw, lh, rows, x, n, ty, dy;
    f = (struct fdlg *)wk_state(w);
    d_rect(0, 0, cw, ch, C_FACE);
    // Look in: the folder, and Up
    d_text(FB_LX, 14, C_DARK, F_SANS, f->save ? "Save in:" : "Look in:");
    fb_combo(78, 10, fb_look_w(cw), fb_folder_name(f->dir), 1);
    ui_button(cw - 34, 10, 24, 22, "", 0, 0);
    x = cw - 34;
    fb_folder_icon(x + 3, 13);
    d_line(x + 16, 14, x + 16, 22, C_DARK); d_line(x + 13, 17, x + 16, 14, C_DARK); d_line(x + 19, 17, x + 16, 14, C_DARK);
    d_line(x + 16, 22, x + 20, 22, C_DARK);
    // the folder's contents
    lw = fb_lw(cw); lh = fb_lh(ch); rows = fb_rows(ch);
    d_rect(FB_LX, FB_LY, lw, lh, C_WHITE);
    d_bevel(FB_LX, FB_LY, lw, lh, B_SUNKEN);
    d_clip(FB_LX + 2, FB_LY + 2, lw - 20, lh - 4);
    k = f->top; y = FB_LY + 2;
    while (k < f->n && k < f->top + rows) {
        if (f->isdir[f->order[k]]) fb_folder_icon(FB_LX + 4, y);
        else fb_file_icon(FB_LX + 4, y);
        n = ui_len(wk_fb_name(f, k));
        if (k == f->sel) d_rect(FB_LX + 22, y, n * 6 + 6, FB_ROW, C_SEL);
        d_text(FB_LX + 25, y + 2, k == f->sel ? C_WHITE : C_DARK, F_SANS, wk_fb_name(f, k));
        y = y + FB_ROW;
        ++k;
    }
    d_clip_end();
    ui_scrollbar(FB_LX + lw - 18, FB_LY + 2, lh - 4, f->n, rows, f->top);
    // the name, the type, and the buttons
    y = ch - 66;
    d_text(FB_LX, y + 5, C_DARK, F_SANS, "File name:");
    ui_field(FB_FX, y, fb_cw(cw), f->out, f->caret, !f->drop);
    ui_button(cw - 88, y, 78, 24, f->save ? "Save" : "Open", 0, 1);
    ty = ch - 34;
    d_text(FB_LX, ty + 5, C_DARK, F_SANS, f->save ? "Save as type:" : "Files of type:");
    wk_fb_label(f, f->ftype, fbtmp, WK_PATH);
    fb_combo(FB_FX, ty, fb_cw(cw), fbtmp, 0);
    ui_button(cw - 88, ty, 78, 24, "Cancel", 0, 0);
    // a list dropped down, over the rest
    if (f->drop == 1) {
        n = fb_depth(f);
        lw = fb_look_w(cw);
        d_rect(78, 32, lw, n * FB_DROP_ROW + 4, C_WHITE);
        d_recto(78, 32, lw - 1, n * FB_DROP_ROW + 3, C_DARK);
        k = 0;
        while (k < n) {
            dy = 34 + k * FB_DROP_ROW;
            fb_ancestor(f, k, fbtmp);
            if (k == n - 1) d_rect(80 + k * 10 + 20, dy, ui_len(fb_folder_name(fbtmp)) * 6 + 6, FB_DROP_ROW, C_SEL);
            fb_folder_icon(82 + k * 10, dy);
            d_text(80 + k * 10 + 23, dy + 2, k == n - 1 ? C_WHITE : C_DARK, F_SANS, fb_folder_name(fbtmp));
            ++k;
        }
    } else if (f->drop == 2) {
        n = wk_fb_types(f);
        lw = fb_cw(cw);
        dy = ty - n * FB_DROP_ROW - 4;               // up from the box: there is no room under it
        d_rect(FB_FX, dy, lw, n * FB_DROP_ROW + 4, C_WHITE);
        d_recto(FB_FX, dy, lw - 1, n * FB_DROP_ROW + 3, C_DARK);
        k = 0;
        while (k < n) {
            if (k == f->ftype) d_rect(FB_FX + 2, dy + 2 + k * FB_DROP_ROW, lw - 4, FB_DROP_ROW, C_SEL);
            wk_fb_label(f, k, fbtmp, WK_PATH);
            d_text(FB_FX + 6, dy + 4 + k * FB_DROP_ROW, k == f->ftype ? C_WHITE : C_DARK, F_SANS, fbtmp);
            ++k;
        }
    }
}

// the entry picked: a file's name goes into the name
static void fb_pick(struct fdlg *f, int k, int rows) {
    if (k < 0 || k >= f->n) return;
    f->sel = k;
    if (k < f->top) f->top = k;
    if (k >= f->top + rows) f->top = k - rows + 1;
    if (!f->isdir[f->order[k]]) { ui_ncpy(f->out, wk_fb_name(f, k), WK_NAME); f->caret = ui_len(f->out); }
}

static void file95_mouse(int w, int ev, int x, int y, int b) {
    struct fdlg *f;
    struct win *d;
    int cw, ch, k, t, lw, rows, n, dy;
    if (!(d = win_get(w))) return;
    f = (struct fdlg *)d->st;
    wk_size(w, &cw, &ch);
    lw = fb_lw(cw); rows = fb_rows(ch);
    if (ev == E_WHEEL) {
        f->top = f->top + b * 3;
        if (f->top > f->n - rows) f->top = f->n - rows;
        if (f->top < 0) f->top = 0;
        return;
    }
    if (ev == E_MOVE) { t = ui_scroll_drag(FB_LX + lw - 18, FB_LY + 2, y); if (t >= 0) f->top = t; return; }
    if (ev != E_DOWN && ev != E_DBL) return;
    // a list dropped down takes the click, and closes
    if (f->drop) {
        if (ev != E_DOWN) return;
        if (f->drop == 1) {
            n = fb_depth(f);
            if (ui_hit(x, y, 78, 34, fb_look_w(cw), n * FB_DROP_ROW)) {
                k = (y - 34) / FB_DROP_ROW;
                fb_ancestor(f, k, fbtmp);
                ui_ncpy(f->dir, fbtmp, WK_PATH);
                wk_fb_list(f);
            }
        } else {
            n = wk_fb_types(f);
            dy = ch - 34 - n * FB_DROP_ROW - 4;
            if (ui_hit(x, y, FB_FX, dy + 2, fb_cw(cw), n * FB_DROP_ROW)) wk_fb_type(f, (y - dy - 2) / FB_DROP_ROW);
        }
        f->drop = 0;
        wk_redraw_all();
        return;
    }
    if (ev == E_DOWN && ui_hit(x, y, cw - 88, ch - 66, 78, 24)) { wk_fb_ok(d, f); return; }
    if (ev == E_DOWN && ui_hit(x, y, cw - 88, ch - 34, 78, 24)) { wk_dialog_answer(d, 0); return; }
    if (ev == E_DOWN && ui_hit(x, y, cw - 34, 10, 24, 22)) { if (f->dir[1]) wk_fb_enter(f, ".."); return; }
    if (ev == E_DOWN && ui_hit(x, y, 78, 10, fb_look_w(cw), 22)) { f->drop = 1; wk_redraw_all(); return; }
    if (ev == E_DOWN && ui_hit(x, y, FB_FX, ch - 34, fb_cw(cw), 22)) { f->drop = 2; wk_redraw_all(); return; }
    t = ui_scroll_click(x, y, FB_LX + lw - 18, FB_LY + 2, fb_lh(ch) - 4, f->n, rows, f->top);
    if (t >= 0) { f->top = t; return; }
    if (ui_hit(x, y, FB_LX + 2, FB_LY + 2, lw - 20, fb_lh(ch) - 4)) {
        k = f->top + (y - FB_LY - 2) / FB_ROW;
        if (k >= f->n) { f->sel = 0 - 1; return; }
        fb_pick(f, k, rows);
        if (ev == E_DBL) {
            if (f->isdir[f->order[k]]) { ui_ncpy(fbtmp, wk_fb_name(f, k), WK_PATH); wk_fb_enter(f, fbtmp); return; }
            wk_fb_ok(d, f);
        }
        return;
    }
    if (ui_hit(x, y, FB_FX, ch - 66, fb_cw(cw), 22)) f->caret = ui_field_hit(x, FB_FX, fb_cw(cw), f->out, f->caret);
}

static void file95_key(int w, int down, int code, int ch, int mods) {
    struct fdlg *f;
    struct win *d;
    int cw, chh;
    if (!down || !(d = win_get(w))) return;
    f = (struct fdlg *)d->st;
    wk_size(w, &cw, &chh);
    if (code == KEY_ESC) { if (f->drop) { f->drop = 0; return; } wk_dialog_answer(d, 0); return; }
    f->drop = 0;
    if (code == KEY_ENTER) { wk_fb_ok(d, f); return; }
    if (code == KEY_BACK && !f->out[0]) { if (f->dir[1]) wk_fb_enter(f, ".."); return; }
    if (code == KEY_DOWN) { fb_pick(f, f->sel < 0 ? 0 : f->sel + 1, fb_rows(chh)); return; }
    if (code == KEY_UP) { fb_pick(f, f->sel > 0 ? f->sel - 1 : 0, fb_rows(chh)); return; }
    ui_field_key(f->out, WK_NAME - 1, &f->caret, code, ch, mods);
}

struct wk_class wk_file95_class = { .kind = ICON_FILEBOX, .draw = file95_draw, .mouse = file95_mouse, .key = file95_key };
// notepad.c -- Notepad: a plain text editor, as a window kit class.
// docs/grin-plan.md 4; it was the C4IX desktop's Text Editor (apps.c).
//
// The whole file in one buffer, edited in place, which grows as it must:
// a file is as big as memory allows, and one that will not fit is refused
// rather than cut short (the desktop review's B6). Lines are found by
// scanning for newlines, and drawn in a fixed-width face so the caret can
// be placed exactly. Files open from, and save to, the host's (wk_fopen).
//
// A selection runs from an anchor to the caret: Shift with the moving
// keys, or the mouse dragged, makes one, and typing replaces it. Edit's
// Cut, Copy and Paste (and Ctrl+X, C and V, or Shift+Del, Ctrl+Ins and
// Shift+Ins) go through the kit's clipboard, which every window shares.
//
// Find (Edit > Find..., Ctrl+F): the kit's find bar under the text (ui.c),
// which looks from the selection for the next match (Enter, F3, Next) or
// the one before (Shift+Enter, Shift+F3, Previous), round past the end or
// the top with a note that it went round, and selects it. Match case or
// not; a selection on one line is what it looks for to start with.
//
// Format: Word Wrap, on until it is turned off, folds a long line onto the
// rows below; off, the text scrolls across under a bar. And the face and
// size the text is drawn in, the kit's fixed-width ones. The choices are
// every Notepad window's, and kept in notepad_cfg when the host names one.

#include "winkit.h"

enum { CHUNK = 4096 };
enum { D_OPEN = 1, D_SAVEAS = 2 };                // its dialogs
enum { N_NEW = 0, N_OPEN = 1, N_SAVE = 2, N_SAVEAS = 3, N_EXIT = 5 };   // File's items
enum { E_CUT = 0, E_COPY = 1, E_PASTE = 2, E_DELETE = 3, E_ALL = 5,     // Edit's
       E_FIND = 7, E_FNEXT = 8, E_FPREV = 9 };
enum { FM_WRAP = 0, FM_FACE = 2, FM_SIZE = 6, FM_N = 9 };                // Format's: then the faces, the sizes

char *notepad_name = "Notepad";
char *notepad_about = "Notepad: edits plain text.";
char *notepad_home = "/";                         // where Open starts
char *notepad_untitled = "untitled.txt";          // where Save As offers to put a new one
int notepad_filebox = 0;                          // Open and Save As: the kit's file box, not a typed path
char *notepad_filter = "*";                       // ... and the types it offers (wk_filebox)
char *notepad_cfg = 0;                            // where Format's choices are kept, or 0

struct note {
    char path[WK_PATH];
    char ask[WK_PATH];                            // a dialog's path, in and out
    int len, cap, caret, top, modified;           // top: the first row shown
    int want_col;                                 // the column up/down tries to keep
    int anchor;                                   // the selection's other end (anchor == caret: none)
    int dragging;                                 // the mouse is making a selection
    char *text;                                   // cap bytes, len of them text and a 0
    int left;                                     // without Word Wrap: the first column shown
    int lcaret;                                   // the caret when it last drew (the view follows it when it moves)
    int rows, cols, maxw;                         // as it last drew: rows and columns shown, the longest line
    int lwrap;                                    // ... and whether it folded
    struct ui_find fb;                            // the find bar
};

// Format's choices: Word Wrap, the face and the size; the text grid they make
static int wrap = 1;
static int nface;
static int nsize = 1;
static int cfg_read;
static int nfont = F_MONO;
static int nfs = 12;
static int ncw = 7;
static int nch = 15;

static char buf[WK_PATH + 64];
static char about_item[64];
static char about_title[64];
static char *file_items[7] = { "New", "Open...", "Save", "Save As...", "-", "Exit", 0 };
static char *edit_items[11] = { "Cut", "Copy", "Paste", "Delete", "-", "Select All", "-",
                                "Find...   Ctrl+F", "Find Next   F3", "Find Previous", 0 };
static char *format_items[FM_N + 1];
static char fmt_buf[FM_N * 20];
static char *help_items[2];
static struct wk_menu menus[4];
static char cfgb[72];

static struct note *N(int w) { return (struct note *)wk_state(w); }
static void find_act(int w, int a);

static void retitle(int w) {
    struct note *n;
    n = N(w);
    if (n->path[0]) ui_ncpy(buf, ui_base(n->path), WK_PATH);
    else ui_cpy(buf, "Untitled");
    if (n->modified) ui_cat(buf, " *");
    ui_cat(buf, " - ");
    ui_ncat(buf, notepad_name, WK_PATH + 64);
    wk_title(w, buf);
}

// Room for `more` bytes past len, and the 0 after them: 1 if there is.
static int room(struct note *n, int more) {
    char *t;
    int cap;
    if (n->len + more < n->cap) return 1;
    cap = n->cap ? n->cap : CHUNK;
    while (n->len + more >= cap) cap = cap * 2;
    if (!(t = wk_alloc(cap))) return 0;
    if (n->text) { memcpy(t, n->text, n->len + 1); wk_free(n->text); }
    n->text = t; n->cap = cap;
    return 1;
}

static void empty(struct note *n) {
    n->len = 0; n->caret = 0; n->anchor = 0; n->top = 0; n->modified = 0; n->left = 0;
    if (n->text) n->text[0] = 0;
}

// 1 loaded; 0 cannot open it; -1 no memory to hold it all (the buffer is then empty)
static int load(struct note *n, char *path) {
    int fd, r;
    if ((fd = wk_fopen(path, 0)) < 0) return 0;
    empty(n);
    while (1) {
        if (!room(n, CHUNK)) { wk_fclose(fd); empty(n); return 0 - 1; }
        r = wk_fread(fd, n->text + n->len, n->cap - 1 - n->len);
        if (r <= 0) break;
        n->len = n->len + r;
    }
    wk_fclose(fd);
    n->text[n->len] = 0;
    ui_ncpy(n->path, path, WK_PATH);
    return 1;
}

static int save(struct note *n) {
    int fd, r;
    if ((fd = wk_fopen(n->path, 1)) < 0) return 0;
    r = n->len ? wk_fwrite(fd, n->text, n->len) : 0;
    wk_fclose(fd);
    if (r != n->len) return 0;
    n->modified = 0;
    return 1;
}

static void say(int w, char *s) { wk_msgbox(w, 0, notepad_name, s, WK_OK); }

static void open_file(int w, char *path, int fresh) {
    int r;
    r = load(N(w), path);
    if (r < 0) say(w, "There is not enough memory to open all of that file.");
    else if (!r && fresh) { ui_ncpy(N(w)->path, path, WK_PATH); say(w, "Cannot open that file; starting a new one with its name."); }
    else if (!r) say(w, "Cannot open that file.");
}

// ---- Format's choices ------------------------------------------------------------

static void use_font() {
    nfont = wk_mono_font(nface);
    wk_grid(nsize, &nfs, &ncw, &nch);
}

// notepad_cfg: "wrap W font F size S", each a digit
static void cfg_load() {
    int fd, r, i;
    cfg_read = 1;
    if (notepad_cfg && (fd = wk_fopen(notepad_cfg, 0)) >= 0) {
        r = wk_fread(fd, cfgb, 60);
        wk_fclose(fd);
        if (r < 0) r = 0;
        cfgb[r] = 0;
        i = 0;
        while (i < r) {
            if (cfgb[i] == 'w' && cfgb[i + 1] == 'r' && cfgb[i + 4] == ' ') wrap = cfgb[i + 5] != '0';
            if (cfgb[i] == 'f' && cfgb[i + 1] == 'o' && cfgb[i + 4] == ' ' && cfgb[i + 5] >= '0' && cfgb[i + 5] < '0' + WK_FACES) nface = cfgb[i + 5] - '0';
            if (cfgb[i] == 's' && cfgb[i + 1] == 'i' && cfgb[i + 4] == ' ' && cfgb[i + 5] >= '0' && cfgb[i + 5] < '0' + WK_SIZES) nsize = cfgb[i + 5] - '0';
            ++i;
        }
    }
    use_font();
}

static void cfg_save() {
    int fd;
    if (!notepad_cfg || (fd = wk_fopen(notepad_cfg, 1)) < 0) return;
    ui_cpy(cfgb, "wrap 0 font 0 size 0\n");
    cfgb[5] = '0' + wrap; cfgb[12] = '0' + nface; cfgb[19] = '0' + nsize;
    wk_fwrite(fd, cfgb, ui_len(cfgb));
    wk_fclose(fd);
}

// Format's items, a check beside each choice in use
static void fmt_item(int k, char *name, int on) {
    char *p;
    p = fmt_buf + k * 20;
    p[0] = WK_CHECKED;
    ui_ncpy(on ? p + 1 : p, name, 19);
    format_items[k] = p;
}
static void format_menu() {
    int k;
    fmt_item(FM_WRAP, "Word Wrap", wrap);
    format_items[FM_FACE - 1] = "-";
    k = 0;
    while (k < WK_FACES) { fmt_item(FM_FACE + k, wk_mono_name(k), k == nface); ++k; }
    format_items[FM_SIZE - 1] = "-";
    k = 0;
    while (k < WK_SIZES) { fmt_item(FM_SIZE + k, wk_size_name(k), k == nsize); ++k; }
    format_items[FM_N] = 0;
}

// a choice made: in every Notepad window at once, and kept
static void format_pick(int item) {
    if (item == FM_WRAP) wrap = !wrap;
    else if (item >= FM_FACE && item < FM_FACE + WK_FACES) nface = item - FM_FACE;
    else if (item >= FM_SIZE && item < FM_SIZE + WK_SIZES) nsize = item - FM_SIZE;
    else return;
    use_font();
    format_menu();
    cfg_save();
    wk_redraw_all();
}

static void note_open_hook(int w, char *path) {
    struct note *n;
    n = N(w);
    help_items[0] = about_item; help_items[1] = 0;
    format_menu();
    menus[0].title = "File"; menus[0].items = file_items;
    menus[1].title = "Edit"; menus[1].items = edit_items;
    menus[2].title = "Format"; menus[2].items = format_items;
    menus[3].title = "Help"; menus[3].items = help_items;
    wk_menu(w, menus, 4);
    if (!room(n, 1)) { wk_close(w); return; }
    empty(n);
    if (path) open_file(w, path, 1);
    retitle(w);
}

static void note_destroy(int w) {
    struct note *n;
    n = N(w);
    if (n->text) { wk_free(n->text); n->text = 0; }
}

int notepad_open(char *path) {
    if (!cfg_read) cfg_load();
    ui_cpy(about_item, "About ");
    ui_ncat(about_item, notepad_name, 64);
    ui_cpy(about_title, about_item);
    ui_cpy(buf, "Untitled - ");
    ui_ncat(buf, notepad_name, WK_PATH + 64);
    notepad_class.size = sizeof(struct note);
    return wk_open(&notepad_class, buf, 560, 400, 0, path);
}

// ---- rows: the lines as they are drawn --------------------------------------------
//
// Without Word Wrap a row is a line. With it, a line wider than the
// window folds onto the rows below: after the last space that fits (a
// space just past the edge is the fold itself, and not drawn), or where
// the row is full if it has none. A row is known by where it starts; the
// next starts where it ends, or past the newline or space it ended at. A
// position is on the row it is at or after whose next is past it: the end
// of a line is on its last row, a fold's position on the row after.

static int wcols;      // a row's columns while folding (the window's, as it last drew); 0 not folding

static void lay(struct note *n) { wcols = wrap ? n->cols : 0; }

// where the row from S ends, and where the next starts (past the text: len + 1)
static int row_end(struct note *n, int s, int *next) {
    int e, k;
    e = s;
    while (e < n->len && n->text[e] != 10 && (!wcols || e < s + wcols)) ++e;
    if (e >= n->len || n->text[e] == 10 || n->text[e] == ' ') { *next = e + 1; return e; }
    k = e;
    while (k > s && n->text[k - 1] != ' ') --k;
    if (k > s) e = k;
    *next = e;
    return e;
}

// the row a buffer position is on, and its column there
static int row_of(struct note *n, int pos, int *col) {
    int s, next, row;
    s = 0; row = 0;
    while (1) {
        row_end(n, s, &next);
        if (pos < next || next > n->len) { *col = pos - s; return row; }
        s = next; ++row;
    }
    return row;
}

// where row R starts (the last row's start, past the last)
static int row_start(struct note *n, int r) {
    int s, next;
    s = 0;
    while (r > 0) {
        row_end(n, s, &next);
        if (next > n->len) return s;
        s = next; --r;
    }
    return s;
}

// the buffer position at a column of row R, the nearest the row has
static int row_pos(struct note *n, int r, int col) {
    int s, e, next;
    s = row_start(n, r);
    e = row_end(n, s, &next);
    if (col < 0) col = 0;
    if (s + col > e) col = e - s;
    if (s + col >= next) col = next - 1 - s;     // folded where it was full: its last character
    return s + col;
}

static int row_count(struct note *n) {
    int s, next, r;
    s = 0; r = 1;
    while (1) {
        row_end(n, s, &next);
        if (next > n->len) return r;
        s = next; ++r;
    }
    return r;
}

// the longest line, which the bar across scrolls over
static int widest(struct note *n) {
    int i, start, w;
    w = 0; start = 0; i = 0;
    while (i <= n->len) {
        if (i == n->len || n->text[i] == 10) { if (i - start > w) w = i - start; start = i + 1; }
        ++i;
    }
    return w;
}

static void insert(struct note *n, int c) {
    int i;
    if (!room(n, 1)) return;
    i = n->len;
    while (i > n->caret) { n->text[i] = n->text[i - 1]; --i; }
    n->text[n->caret] = c;
    ++n->len; ++n->caret;
    n->text[n->len] = 0;
    n->modified = 1;
}

static void erase(struct note *n, int at) {
    int i;
    if (at < 0 || at >= n->len) return;
    i = at;
    while (i < n->len) { n->text[i] = n->text[i + 1]; ++i; }
    --n->len;
    n->modified = 1;
}

// ---- the selection, and the clipboard ------------------------------------------

static int sel0(struct note *n) { return n->anchor < n->caret ? n->anchor : n->caret; }
static int sel1(struct note *n) { return n->anchor < n->caret ? n->caret : n->anchor; }
static int has_sel(struct note *n) { return n->anchor != n->caret && n->anchor >= 0 && n->anchor <= n->len; }

// the selection taken out of the text: 1 if there was one
static int cut_sel(struct note *n) {
    int a, b, i;
    if (!has_sel(n)) { n->anchor = n->caret; return 0; }
    a = sel0(n); b = sel1(n);
    i = a;
    while (i + (b - a) <= n->len) { n->text[i] = n->text[i + (b - a)]; ++i; }
    n->len = n->len - (b - a);
    n->caret = a; n->anchor = a;
    n->modified = 1;
    return 1;
}

static void copy_sel(struct note *n) { if (has_sel(n)) wk_clip_set(n->text + sel0(n), sel1(n) - sel0(n)); }

// the clipboard's text at the caret, in place of the selection (its
// carriage returns dropped: a line ends in a newline here)
static void paste(struct note *n) {
    char *c;
    int cn, k, m, i;
    c = wk_clip_get(&cn);
    if (cn <= 0) return;
    if (!room(n, cn)) return;
    cut_sel(n);
    m = 0;
    k = 0;
    while (k < cn) { if (c[k] != 13 && c[k]) ++m; ++k; }
    i = n->len;
    while (i >= n->caret) { n->text[i + m] = n->text[i]; --i; }
    k = 0;
    while (k < cn) { if (c[k] != 13 && c[k]) { n->text[n->caret] = c[k]; ++n->caret; } ++k; }
    n->len = n->len + m;
    n->anchor = n->caret;
    n->modified = 1;
}

static void note_draw(int w, int cw, int ch, int focused) {
    struct note *n;
    int rows, cols, i, row, y, start, end, next, cr, cc, a, b, k, hb, left;
    n = N(w);
    hb = !wrap;                                    // the bar across
    if (n->fb.on) {
        ui_find_draw(&n->fb, 0, ch - UI_FIND_H, cw, focused);
        ch = ch - UI_FIND_H;                       // the text above the find bar
    }
    d_rect(0, 0, cw, ch, C_WHITE);
    d_bevel(0, 0, cw, ch, B_SUNKEN);
    rows = (ch - 6 - (hb ? 16 : 0)) / nch;
    cols = (cw - 26) / ncw;
    if (rows < 1) rows = 1;
    if (cols < 1) cols = 1;
    n->rows = rows; n->cols = cols;
    lay(n);
    cr = row_of(n, n->caret, &cc);
    if (cr < n->top) n->top = cr;
    if (cr >= n->top + rows) n->top = cr - rows + 1;
    n->maxw = hb ? widest(n) : 0;
    if (hb) {
        // across, the view follows the caret only when it has moved (or
        // Word Wrap has just gone off), so the bar can be scrolled away from it
        if (n->caret != n->lcaret || n->lwrap) {
            if (cc < n->left) n->left = cc;
            if (cc >= n->left + cols) n->left = cc - cols + 1;
        }
        if (n->left > n->maxw + 1 - cols) n->left = n->maxw + 1 - cols;
        if (n->left < 0) n->left = 0;
    } else n->left = 0;
    n->lcaret = n->caret;
    n->lwrap = wrap;
    left = n->left;
    // walk to the first row shown, then draw row by row
    i = row_start(n, n->top);
    row = n->top;
    y = 4;
    while (row < n->top + rows && i <= n->len) {
        start = i;
        end = row_end(n, start, &next);
        k = end - start - left;
        if (k > cols) k = cols;
        if (k > 0) d_textn(4, y, C_DARK, nfs, nfont, ncw, n->text + start + left, k);
        // the selection's part of the row, white on the selection's colour
        if (has_sel(n) && sel0(n) < next && sel1(n) > start) {
            a = sel0(n) > start ? sel0(n) - start : 0;
            b = sel1(n) < next ? sel1(n) - start : next - start;   // past the end: its newline or fold, a cell wide
            a = a - left; b = b - left;
            if (a < 0) a = 0;
            if (b > cols) b = cols;
            if (b > a) {
                d_rect(4 + a * ncw, y, (b - a) * ncw, nch - 1, C_SEL);
                k = (b < end - start - left ? b : end - start - left) - a;
                if (k > 0) d_textn(4 + a * ncw, y, C_WHITE, nfs, nfont, ncw, n->text + start + left + a, k);
            }
        }
        if (focused && !n->fb.keys && row == cr && cc >= left && cc - left <= cols) d_rect(4 + (cc - left) * ncw, y, 1, nch - 1, C_DARK);
        y = y + nch;
        ++row;
        i = next;
    }
    ui_scrollbar(cw - 18, 2, ch - 4 - (hb ? 16 : 0), row_count(n), rows, n->top);
    if (hb) {
        ui_hscrollbar(2, ch - 18, cw - 20, n->maxw + 1, cols, left);
        d_rect(cw - 18, ch - 18, 16, 16, C_FACE);
    }
}

// the buffer position under a point of the text, the nearest on its row
static int pos_at(struct note *n, int x, int y) {
    int col, row;
    col = (x - 4 + ncw / 2) / ncw;
    if (col < 0) col = 0;
    row = (y - 4) / nch;
    if (row < 0) row = 0;
    return row_pos(n, n->top + row, n->left + col);
}

static void note_mouse(int w, int ev, int x, int y, int b) {
    struct note *n;
    int rows, t, cw, ch, hb;
    n = N(w);
    wk_size(w, &cw, &ch);
    lay(n);
    hb = !wrap;
    rows = n->rows > 0 ? n->rows : 1;
    if (n->fb.on) {
        ch = ch - UI_FIND_H;                       // the text's, above the find bar
        if (ev != E_WHEEL && ev != E_MOVE && ev != E_UP && (t = ui_find_mouse(&n->fb, ev, x, y, 0, ch, cw)) >= 0) {
            find_act(w, t);
            return;
        }
        if (ev == E_DOWN) n->fb.keys = 0;          // a click in the text: the keys are its again
    }
    if (ev == E_WHEEL) {
        n->top = n->top + b * 3;
        if (n->top > row_count(n) - rows) n->top = row_count(n) - rows;
        if (n->top < 0) n->top = 0;
        // keep the caret on screen, as editors do when they scroll
        n->caret = row_pos(n, n->top + (rows / 2), 0);
        n->anchor = n->caret;
        return;
    }
    if (ev == E_UP) { n->dragging = 0; return; }
    if (ev == E_MOVE) {
        t = ui_scroll_drag(cw - 18, 2, y);
        if (t >= 0) { n->top = t; n->caret = row_pos(n, t, 0); n->anchor = n->caret; return; }
        t = ui_scroll_drag(2, ch - 18, x);
        if (t >= 0) { n->left = t; wk_invalidate(w, 0, 0, 0, 0); return; }
        // a selection being dragged out
        if (n->dragging && (t = pos_at(n, x, y)) != n->caret) {
            n->caret = t;
            row_of(n, n->caret, &n->want_col);
            wk_invalidate(w, 0, 0, 0, 0);
        }
        return;
    }
    if (ev != E_DOWN) return;
    t = ui_scroll_click(x, y, cw - 18, 2, ch - 4 - (hb ? 16 : 0), row_count(n), rows, n->top);
    if (t >= 0) { n->top = t; n->caret = row_pos(n, t, 0); n->anchor = n->caret; return; }
    if (hb && (t = ui_hscroll_click(x, y, 2, ch - 18, cw - 20, n->maxw + 1, n->cols, n->left)) >= 0) { n->left = t; return; }
    n->caret = pos_at(n, x, y);
    if (!(wk.mods & M_SHIFT)) n->anchor = n->caret;      // Shift+click: the selection to here
    n->dragging = 1;
    row_of(n, n->caret, &n->want_col);
}

static void note_command(int w, int id);

// ---- Find --------------------------------------------------------------------------

// The next match (DIR 1) after the selection's start -- from it, when
// HERE, as the text to find is typed -- or the one before it (-1), round
// past the end or the top; selected, or the bar says there is none.
static void find(int w, int dir, int here) {
    struct note *n;
    int m, s0, p, k;
    n = N(w);
    m = ui_len(n->fb.text);
    if (!m) { ui_find_open(&n->fb, 0, 0); return; }   // nothing to look for yet: ask
    s0 = has_sel(n) ? sel0(n) : n->caret;
    if (dir > 0) p = here || !has_sel(n) ? s0 : s0 + 1;
    else p = s0 - 1;
    n->fb.note[0] = 0; n->fb.bad = 0;
    k = 0;
    while (k <= n->len + 1) {
        if (dir > 0 && p + m > n->len) { p = 0; ui_find_say(&n->fb, "Wrapped to the top", 0); }
        if (dir < 0 && p < 0) { p = n->len - m; ui_find_say(&n->fb, "Wrapped to the bottom", 0); }
        if (p >= 0 && ui_find_at(&n->fb, n->text + p, n->len - p)) {
            n->anchor = p; n->caret = p + m;
            row_of(n, n->caret, &n->want_col);
            return;
        }
        p = p + dir;
        ++k;
    }
    ui_find_say(&n->fb, "Not found", 1);
}

// what the find bar asked for
static void find_act(int w, int a) {
    if (a == UF_NEXT) find(w, 1, 0);
    else if (a == UF_PREV) find(w, 0 - 1, 0);
    else if (a == UF_TYPED) find(w, 1, 1);
    wk_invalidate(w, 0, 0, 0, 0);
}

// Find: the bar, with the selection to look for if it is one short line
static void find_open(int w) {
    struct note *n;
    n = N(w);
    ui_find_open(&n->fb, has_sel(n) ? n->text + sel0(n) : 0, has_sel(n) ? sel1(n) - sel0(n) : 0);
    wk_invalidate(w, 0, 0, 0, 0);
}

static void note_key(int w, int down, int code, int ch, int mods) {
    struct note *n;
    int row, col, was, moved;
    if (!down) return;
    n = N(w);
    was = n->modified;
    if ((mods & M_CTRL) && (ch == 'f' || ch == 'F' || code == 'F')) { find_open(w); return; }
    if (code == KEY_F3) { if (!n->fb.text[0]) find_open(w); else find(w, (mods & M_SHIFT) ? 0 - 1 : 1, 0); return; }
    if (n->fb.on && n->fb.keys) { find_act(w, ui_find_key(&n->fb, code, ch, mods)); return; }
    if (code == KEY_ESC && n->fb.on) { n->fb.on = 0; return; }
    if (ui_key_copy(code, ch, mods)) { note_command(w, WK_CMD(1, E_COPY)); return; }
    if (ui_key_cut(code, ch, mods)) { note_command(w, WK_CMD(1, E_CUT)); return; }
    if (ui_key_paste(code, ch, mods)) { note_command(w, WK_CMD(1, E_PASTE)); return; }
    if (mods & M_CTRL) {
        if (ch == 's' || ch == 'S' || code == 'S') note_command(w, WK_CMD(0, N_SAVE));
        else if (ch == 'o' || ch == 'O' || code == 'O') note_command(w, WK_CMD(0, N_OPEN));
        else if (ch == 'n' || ch == 'N' || code == 'N') note_command(w, WK_CMD(0, N_NEW));
        else if (ch == 'a' || ch == 'A' || code == 'A') note_command(w, WK_CMD(1, E_ALL));
        return;
    }
    lay(n);
    row = row_of(n, n->caret, &col);
    // the moving keys, by rows: with Shift they take the selection along
    moved = 1;
    if (code == KEY_LEFT) { if (n->caret > 0) --n->caret; row_of(n, n->caret, &n->want_col); }
    else if (code == KEY_RIGHT) { if (n->caret < n->len) ++n->caret; row_of(n, n->caret, &n->want_col); }
    else if (code == KEY_UP) { if (row > 0) n->caret = row_pos(n, row - 1, n->want_col); }
    else if (code == KEY_DOWN) n->caret = row_pos(n, row + 1, n->want_col);
    else if (code == KEY_HOME) { n->caret = row_pos(n, row, 0); n->want_col = 0; }
    else if (code == KEY_END) { n->caret = row_pos(n, row, 100000); row_of(n, n->caret, &n->want_col); }
    else if (code == KEY_PGUP) n->caret = row_pos(n, row > 20 ? row - 20 : 0, n->want_col);
    else if (code == KEY_PGDN) n->caret = row_pos(n, row + 20, n->want_col);
    else moved = 0;
    if (moved) { if (!(mods & M_SHIFT)) n->anchor = n->caret; return; }
    // the editing keys: a selection is what they delete, or what typing replaces
    if (code == KEY_BACK) { if (!cut_sel(n) && n->caret > 0) { --n->caret; erase(n, n->caret); } row_of(n, n->caret, &n->want_col); }
    else if (code == KEY_DEL) { if (!cut_sel(n)) erase(n, n->caret); }
    else if (code == KEY_ENTER) { cut_sel(n); insert(n, 10); n->want_col = 0; }
    else if (code == KEY_TAB) { cut_sel(n); insert(n, ' '); insert(n, ' '); insert(n, ' '); insert(n, ' '); row_of(n, n->caret, &n->want_col); }
    else if (ch >= 32 && ch < 127) { cut_sel(n); insert(n, ch); row_of(n, n->caret, &n->want_col); }
    n->anchor = n->caret;
    if (n->modified != was) retitle(w);
}

static void save_as(int w, struct note *n) {
    ui_ncpy(n->ask, n->path[0] ? n->path : notepad_untitled, WK_PATH);
    if (notepad_filebox) wk_filebox(w, D_SAVEAS, 1, notepad_filter, n->ask, WK_PATH);
    else wk_inputbox(w, D_SAVEAS, "Save As", "Save as:", n->ask, WK_PATH);
}

static void note_command(int w, int id) {
    struct note *n;
    int item, was;
    n = N(w);
    lay(n);
    item = id % WK_CMD_STEP;
    if (id / WK_CMD_STEP == 3) { wk_msgbox(w, 0, about_title, notepad_about, WK_OK); return; }
    if (id / WK_CMD_STEP == 2) { format_pick(item); return; }
    if (id / WK_CMD_STEP == 1) {
        was = n->modified;
        if (item == E_COPY || item == E_CUT) copy_sel(n);
        if (item == E_CUT || item == E_DELETE) cut_sel(n);
        else if (item == E_PASTE) paste(n);
        else if (item == E_ALL) { n->anchor = 0; n->caret = n->len; }
        else if (item == E_FIND) find_open(w);
        else if (item == E_FNEXT) find(w, 1, 0);
        else if (item == E_FPREV) find(w, 0 - 1, 0);
        row_of(n, n->caret, &n->want_col);
        if (n->modified != was) retitle(w);
        wk_invalidate(w, 0, 0, 0, 0);
        return;
    }
    if (item == N_NEW) { empty(n); n->path[0] = 0; retitle(w); }
    else if (item == N_OPEN) {
        ui_ncpy(n->ask, n->path[0] ? n->path : notepad_home, WK_PATH);
        if (notepad_filebox) wk_filebox(w, D_OPEN, 0, notepad_filter, n->ask, WK_PATH);
        else wk_inputbox(w, D_OPEN, "Open", "File to open:", n->ask, WK_PATH);
    } else if (item == N_SAVE) {
        if (!n->path[0]) save_as(w, n);
        else if (!save(n)) say(w, "Cannot save that file.");
        retitle(w);
    }
    else if (item == N_SAVEAS) save_as(w, n);
    else if (item == N_EXIT) wk_ask_close(w);
}

static void note_answer(int w, int dialog, int yes) {
    struct note *n;
    n = N(w);
    if (!yes) return;
    if (dialog == D_OPEN) open_file(w, n->ask, 0);
    else if (dialog == D_SAVEAS) {
        ui_ncpy(n->path, n->ask, WK_PATH);
        if (!save(n)) say(w, "Cannot save that file.");
    }
    retitle(w);
}

static int note_pointer(int w, int x, int y) {
    int cw, ch;
    wk_size(w, &cw, &ch);
    if (N(w)->fb.on) { if (y >= ch - UI_FIND_H) return PTR_ARROW; ch = ch - UI_FIND_H; }
    return x < cw - 18 && (wrap || y < ch - 18) ? PTR_TEXT : PTR_ARROW;
}

struct wk_class notepad_class = {
    .kind = ICON_NOTE, .open = note_open_hook, .draw = note_draw, .mouse = note_mouse,
    .key = note_key, .command = note_command, .answer = note_answer, .destroy = note_destroy,
    .pointer = note_pointer
};
// savers.c -- the screen savers. docs/c4ix-desktop.md.
//
// After the desktop has had no input for a while (Settings: which saver,
// and how many minutes), one of these takes the whole display until the
// next key or mouse movement. The first four follow the user's
// RetroSavers (D3D ports of the classics) closely, in integer
// arithmetic, drawn with the display's line, rectangle and text
// commands rather than shaders:
//
//   Starfield     stars stream out of the centre, nearer ones bigger and brighter
//   Polygons      two four-cornered shapes bounce about, each leaving a
//                 trail of its last few outlines in cycling colours
//   Beziers       a closed loop of cubic curves, its control points bouncing,
//                 a fading trail in cycling colours
//   Marquee       a line of text crawls across at a random height
//   Digital Rain  columns of falling characters, bright at the head, fading behind
//
// The shell runs them: saver_start, then saver_frame every SAVER_MS, then
// saver_stop on input (and a full redraw of the desktop).

#include "winkit.h"

enum { N_SAVERS = 6 };       // 0 is None

static char *saver_names[N_SAVERS];
static int saver_cur;        // the one running, or 0
static int saver_t;          // frames since it started
static int rnd_s;

static int rnd() {
    rnd_s = rnd_s * 1103515245 + 12345;
    return (rnd_s >> 8) & 0x7fffff;
}
static int rnd_range(int lo, int hi) { return lo + rnd() % (hi - lo + 1); }

// hue 0..1535, full saturation and value
static int hue_rgb(int h, int v) {
    int r, g, b, f;
    h = h % 1536;
    if (h < 0) h = h + 1536;
    f = h % 256;
    if (h < 256)       { r = 255; g = f; b = 0; }
    else if (h < 512)  { r = 255 - f; g = 255; b = 0; }
    else if (h < 768)  { r = 0; g = 255; b = f; }
    else if (h < 1024) { r = 0; g = 255 - f; b = 255; }
    else if (h < 1280) { r = f; g = 0; b = 255; }
    else               { r = 255; g = 0; b = 255 - f; }
    r = r * v / 255; g = g * v / 255; b = b * v / 255;
    return (r << 16) | (g << 8) | b;
}

static void names() {
    saver_names[0] = "(None)";
    saver_names[1] = "Starfield";
    saver_names[2] = "Polygons";
    saver_names[3] = "Beziers";
    saver_names[4] = "Marquee";
    saver_names[5] = "Digital Rain";
}
int saver_count() { return N_SAVERS; }
char *saver_name(int i) { names(); return i >= 0 && i < N_SAVERS ? saver_names[i] : ""; }
int saver_active() { return saver_cur; }

// ---- Starfield ----
// x, y in -1024..1024, z 1024 (far) to 20 (here), as the original's
// -1..1 and 1.0..0.02; both axes scale by half the width.
enum { N_STARS = 120 };
static int st_x[N_STARS], st_y[N_STARS], st_z[N_STARS];
static void star_spawn(int i, int anywhere) {
    st_x[i] = rnd_range(0 - 1024, 1024);
    st_y[i] = rnd_range(0 - 1024, 1024);
    st_z[i] = anywhere ? rnd_range(52, 1024) : 1024;
}
static void star_start() { int i; i = 0; while (i < N_STARS) { star_spawn(i, 1); ++i; } }
static void star_frame() {
    int i, sx, sy, d, sz, br;
    d_rect(0, 0, wk.sw, wk.sh, 0);
    i = 0;
    while (i < N_STARS) {
        st_z[i] = st_z[i] - 12;                       // speed 5: across the field in ~2.5 s at 30 fps
        if (st_z[i] <= 20) { star_spawn(i, 0); ++i; continue; }
        sx = wk.sw / 2 + st_x[i] * (wk.sw / 2) / st_z[i];
        sy = wk.sh / 2 + st_y[i] * (wk.sw / 2) / st_z[i];
        if (sx < 0 - 4 || sy < 0 - 4 || sx > wk.sw + 4 || sy > wk.sh + 4) { star_spawn(i, 0); ++i; continue; }
        d = 1024 - st_z[i];                           // 0 far, 1024 near
        sz = 1 + 3 * d / 1024 * d / 1024;
        br = 90 + 165 * d / 1024;
        d_rect(sx, sy, sz, sz, (br << 16) | (br << 8) | br);
        ++i;
    }
}

// ---- Polygons ----
// Velocities authored for 640x480, as the original's, scaled to the height.
enum { P_V = 4, P_TRAIL = 7 };
static int pg_x[2 * P_V], pg_y[2 * P_V], pg_vx[2 * P_V], pg_vy[2 * P_V];
static int pg_tx[2 * P_TRAIL * P_V], pg_ty[2 * P_TRAIL * P_V], pg_tc[2 * P_TRAIL];
static int pg_n, pg_hue[2], pg_step[2];
static int bounce(int *p, int *v, int max) {
    *p = *p + *v;
    if (*p < 0) { *p = 0 - *p; if (*v < 0) *v = 0 - *v; }
    if (*p > max) { *p = 2 * max - *p; if (*v > 0) *v = 0 - *v; }
    return *p;
}
static void poly_start() {
    int i, sp;
    i = 0;
    while (i < 2 * P_V) {
        pg_x[i] = rnd_range(0, wk.sw - 1) * 16;
        pg_y[i] = rnd_range(0, wk.sh - 1) * 16;
        sp = rnd_range(48, 144) * wk.sh / 480;           // 3..9 pixels, in sixteenths
        pg_vx[i] = (rnd() & 1 ? sp : 0 - sp) * rnd_range(60, 100) / 100;
        pg_vy[i] = (rnd() & 1 ? sp : 0 - sp) * rnd_range(60, 100) / 100;
        ++i;
    }
    pg_n = 0;
    pg_hue[0] = rnd_range(0, 1535); pg_hue[1] = rnd_range(0, 1535);
    pg_step[0] = rnd_range(6, 12); pg_step[1] = rnd_range(6, 12);
}
static void poly_frame() {
    int s, v, k, t, a, b, slot;
    // one tick: move, then keep this outline in the trail
    slot = pg_n % P_TRAIL;
    s = 0;
    while (s < 2) {
        v = 0;
        while (v < P_V) {
            k = s * P_V + v;
            bounce(&pg_x[k], &pg_vx[k], (wk.sw - 1) * 16);
            bounce(&pg_y[k], &pg_vy[k], (wk.sh - 1) * 16);
            pg_tx[(s * P_TRAIL + slot) * P_V + v] = pg_x[k] / 16;
            pg_ty[(s * P_TRAIL + slot) * P_V + v] = pg_y[k] / 16;
            ++v;
        }
        pg_hue[s] = pg_hue[s] + pg_step[s];
        pg_tc[s * P_TRAIL + slot] = hue_rgb(pg_hue[s], 255);
        ++s;
    }
    ++pg_n;
    d_rect(0, 0, wk.sw, wk.sh, 0);
    s = 0;
    while (s < 2) {
        t = 0;
        while (t < P_TRAIL && t < pg_n) {
            k = (s * P_TRAIL + t) * P_V;
            v = 0;
            while (v < P_V) {
                a = k + v; b = k + (v + 1) % P_V;
                d_line(pg_tx[a], pg_ty[a], pg_tx[b], pg_ty[b], pg_tc[s * P_TRAIL + t]);
                ++v;
            }
            ++t;
        }
        ++s;
    }
}

// ---- Beziers ----
// N curves, each anchor, handle, handle, then the next one's anchor: a
// closed loop. Points in sixteenths; the curve in BZ_SUB steps (t in 64ths).
enum { BZ_N = 3, BZ_SUB = 12, BZ_TRAIL = 14, BZ_PTS = BZ_N * BZ_SUB };
static int bz_x[BZ_N * 3], bz_y[BZ_N * 3], bz_vx[BZ_N * 3], bz_vy[BZ_N * 3];
static int bz_px[BZ_TRAIL * BZ_PTS], bz_py[BZ_TRAIL * BZ_PTS], bz_c[BZ_TRAIL];
static int bz_n, bz_hue;
static void bez_start() {
    int i, sp;
    i = 0;
    while (i < BZ_N * 3) {
        bz_x[i] = rnd_range(0, wk.sw - 1) * 16;
        bz_y[i] = rnd_range(0, wk.sh - 1) * 16;
        sp = rnd_range(32, 112) * wk.sh / 480;
        bz_vx[i] = (rnd() & 1 ? sp : 0 - sp) * rnd_range(50, 100) / 100;
        bz_vy[i] = (rnd() & 1 ? sp : 0 - sp) * rnd_range(50, 100) / 100;
        ++i;
    }
    bz_n = 0;
    bz_hue = rnd_range(0, 1535);
}
static void bez_frame() {
    int i, k, t, it, b0, b1, b2, b3, p0, p1, p2, p3, slot, base, a, c, age, r, g, bl, cnt;
    i = 0;
    while (i < BZ_N * 3) { bounce(&bz_x[i], &bz_vx[i], (wk.sw - 1) * 16); bounce(&bz_y[i], &bz_vy[i], (wk.sh - 1) * 16); ++i; }
    slot = bz_n % BZ_TRAIL;
    base = slot * BZ_PTS;
    i = 0;
    while (i < BZ_N) {
        p0 = i * 3; p1 = p0 + 1; p2 = p0 + 2; p3 = ((i + 1) % BZ_N) * 3;
        k = 0;
        while (k < BZ_SUB) {
            t = k * 64 / BZ_SUB; it = 64 - t;
            // Bernstein weights in 64^3ths
            b0 = it * it * it; b1 = 3 * t * it * it; b2 = 3 * t * t * it; b3 = t * t * t;
            bz_px[base + i * BZ_SUB + k] = (b0 / 16 * (bz_x[p0] / 16) + b1 / 16 * (bz_x[p1] / 16) + b2 / 16 * (bz_x[p2] / 16) + b3 / 16 * (bz_x[p3] / 16)) / 16384;
            bz_py[base + i * BZ_SUB + k] = (b0 / 16 * (bz_y[p0] / 16) + b1 / 16 * (bz_y[p1] / 16) + b2 / 16 * (bz_y[p2] / 16) + b3 / 16 * (bz_y[p3] / 16)) / 16384;
            ++k;
        }
        ++i;
    }
    bz_hue = bz_hue + 12;
    bz_c[slot] = hue_rgb(bz_hue, 255);
    ++bz_n;
    d_rect(0, 0, wk.sw, wk.sh, 0);
    cnt = bz_n < BZ_TRAIL ? bz_n : BZ_TRAIL;
    age = 0;
    while (age < cnt) {
        // oldest first, dimmed: the head of the trail reads as the current curve
        slot = (bz_n - cnt + age) % BZ_TRAIL;
        k = cnt > 1 ? 45 + 55 * age / (cnt - 1) : 100;
        c = bz_c[slot];
        r = ((c >> 16) & 255) * k / 100; g = ((c >> 8) & 255) * k / 100; bl = (c & 255) * k / 100;
        c = (r << 16) | (g << 8) | bl;
        base = slot * BZ_PTS;
        i = 0;
        while (i < BZ_PTS) {
            a = base + i;
            k = base + (i + 1) % BZ_PTS;
            d_line(bz_px[a], bz_py[a], bz_px[k], bz_py[k], c);
            ++i;
        }
        ++age;
    }
}

// ---- Marquee ----
static int mq_x, mq_y, mq_hue;
static char *mq_text;
char *saver_marquee = "C4IX -- built upon Robert Swierczek's C4";   // Marquee's line: the shell's to change
static void mq_place() { mq_x = wk.sw; mq_y = rnd_range(40, wk.sh - 100); }
static void mq_start() { mq_text = saver_marquee; mq_place(); mq_hue = rnd_range(0, 1535); }
static void mq_frame() {
    d_rect(0, 0, wk.sw, wk.sh, 0);
    d_textn(mq_x, mq_y, hue_rgb(mq_hue, 255), 48, F_BOLD, 0, mq_text, 0 - 1);
    mq_x = mq_x - 6;
    mq_hue = mq_hue + 4;
    // about 27 pixels a character at 48 points: gone off the left, round again
    if (mq_x < 0 - ui_len(mq_text) * 27) mq_place();
}

// ---- Digital Rain ----
// A column every CW pixels; each has a head falling a row a frame (or two),
// drawn bright, the cell above it green, and the cell its tail has left
// cleared -- so a frame draws three cells a column, not the screen.
enum { CW = 14, CH = 16, R_MAXCOLS = WK_MAX_W / CW };
static int R_COLS, R_ROWS;              // the screen's, when the rain starts
static int rn_head[R_MAXCOLS], rn_len[R_MAXCOLS], rn_wait[R_MAXCOLS], rn_speed[R_MAXCOLS];
static char rn_ch[2];
static char *rn_glyphs;
static void rain_start() {
    int c;
    rn_glyphs = "0123456789ABCDEFabcdef<>=+*#$%&@!?:;{}[]|/\\~^C4IX";
    R_COLS = wk.sw / CW; R_ROWS = wk.sh / CH;
    if (R_COLS > R_MAXCOLS) R_COLS = R_MAXCOLS;
    d_rect(0, 0, wk.sw, wk.sh, 0);
    c = 0;
    while (c < R_COLS) {
        rn_head[c] = 0 - rnd_range(0, R_ROWS);
        rn_len[c] = rnd_range(6, 22);
        rn_speed[c] = rnd_range(1, 2);
        rn_wait[c] = 0;
        ++c;
    }
    rn_ch[1] = 0;
}
static void rain_cell(int c, int r, int rgb) {
    if (r < 0 || r >= R_ROWS) return;
    d_rect(c * CW, r * CH, CW, CH, 0);
    if (rgb < 0) return;
    rn_ch[0] = rn_glyphs[rnd() % ui_len(rn_glyphs)];
    d_textn(c * CW + 2, r * CH + 1, rgb, 13, F_MONO, 0, rn_ch, 1);
}
static void rain_frame() {
    int c;
    c = 0;
    while (c < R_COLS) {
        if (++rn_wait[c] >= rn_speed[c]) {
            rn_wait[c] = 0;
            rain_cell(c, rn_head[c] - 1, 0x00c040);           // last frame's head, green now
            rain_cell(c, rn_head[c] - rn_len[c], 0 - 1);       // the tail's end, cleared
            rain_cell(c, rn_head[c] - rn_len[c] / 2, 0x006020); // half way, dimmer
            rain_cell(c, rn_head[c], 0xd0ffd0);                // the head
            ++rn_head[c];
            if (rn_head[c] - rn_len[c] > R_ROWS) {
                rn_head[c] = 0 - rnd_range(0, R_ROWS / 2);
                rn_len[c] = rnd_range(6, 22);
                rn_speed[c] = rnd_range(1, 2);
            }
        }
        ++c;
    }
}

// ---- running them ----

void saver_start(int which) {
    if (which <= 0 || which >= N_SAVERS) return;
    if (!rnd_s) rnd_s = __time() | 1;
    saver_cur = which;
    saver_t = 0;
    d_rect(0, 0, wk.sw, wk.sh, 0);
    if (which == 1) star_start();
    else if (which == 2) poly_start();
    else if (which == 3) bez_start();
    else if (which == 4) mq_start();
    else rain_start();
}

void saver_frame() {
    if (saver_cur == 1) star_frame();
    else if (saver_cur == 2) poly_frame();
    else if (saver_cur == 3) bez_frame();
    else if (saver_cur == 4) mq_frame();
    else if (saver_cur == 5) rain_frame();
    ++saver_t;
}

int saver_frames() { return saver_t; }

void saver_stop() { saver_cur = 0; }
// textgrid.c -- a VT100 text grid, with scrollback and a line editor.
// docs/grin-plan.md 3.5; it was the C4IX desktop's term.c.
//
// Output is drawn through a VT100 subset: SGR colours (the 16, xterm's
// 256, and 24-bit as the nearest of those), cursor movement, erasing.
// ESC _ ... ESC \ commands are handed to the window's code (g->apc): the
// desktop's Terminal draws window.h programs' canvases with them.
//
// Typing is edited here a line at a time, as a tty in cooked mode does:
// the cursor keys move within the line, Backspace and Delete take out a
// character, Up and Down bring back earlier lines, and Enter hands the
// line to the window's code to send. The line is drawn straight into the
// grid -- the window is its own tty -- from where it began.

#include "winkit.h"
#include "textgrid.h"

enum { COLS = TG_COLS, ROWS = TG_ROWS, CW = TG_CW, CH = TG_CH, RUNMAX = TG_RUNMAX,
       HIST_N = TG_HIST, HIST_W = TG_HIST_W, SB_ROWS = TG_SB_ROWS };

int tg_pal[256];
static char tmp[128];

// xterm's 256 colours: the 16 VGA ones, a 6x6x6 cube, 24 greys.
static int vga[16] = { 0x000000, 0xaa0000, 0x00aa00, 0xaa5500, 0x0000aa, 0xaa00aa, 0x00aaaa, 0xc0c0c0,
                       0x555555, 0xff5555, 0x55ff55, 0xffff55, 0x5555ff, 0xff55ff, 0x55ffff, 0xffffff };
static int level(int v) { if (!v) return 0; return 55 + 40 * v; }
static void palette() {
    int i, r, g, b, v;
    if (tg_pal[15]) return;
    i = 0;
    while (i < 16) { tg_pal[i] = vga[i]; ++i; }
    while (i < 232) {
        r = (i - 16) / 36; g = ((i - 16) / 6) % 6; b = (i - 16) % 6;
        tg_pal[i] = (level(r) << 16) | (level(g) << 8) | level(b);
        ++i;
    }
    while (i < 256) { v = 8 + 10 * (i - 232); tg_pal[i] = (v << 16) | (v << 8) | v; ++i; }
}

// A 24-bit colour, as the nearest step of the cube.
static int cube_step(int c) { if (c < 48) return 0; if (c < 115) return 1; return (c - 35) / 40; }

// ---- the grid -------------------------------------------------------------------

static void clear(struct tgrid *t, int from, int to) {
    int k;
    if (from >= to) return;
    k = from;
    while (k < to) { t->cell[k] = ' ' | (7 << 8) | (t->bg << 16); ++k; }
    k = from / COLS;
    while (k <= (to - 1) / COLS) { t->rowok[k] = 0; ++k; }
}

struct tgrid *tg_new(int win) {
    struct tgrid *t;
    palette();
    if (!(t = (struct tgrid *)wk_alloc(sizeof(struct tgrid)))) return 0;
    if (!(t->sb = (int *)wk_alloc(SB_ROWS * COLS * sizeof(int)))) { wk_free((char *)t); return 0; }
    t->win = win;
    clear(t, 0, ROWS * COLS);
    t->fg = 7; t->cursor = 1;
    return t;
}

void tg_free(struct tgrid *t) {
    if (!t) return;
    wk_free((char *)t->sb);
    wk_free((char *)t);
}

// A scroll moves the cache with the cells: the rows are the same rows.
// (The copies overlap; MCPY copies forwards, to a lower address, so each
// word is read before it is written.)
static void newline(struct tgrid *t) {
    t->cx = 0; t->wrap = 0;
    ++t->cy;
    if (t->cy >= ROWS) {
        memcpy(t->sb + t->sbhead * COLS, t->cell, COLS * sizeof(int));
        t->sbhead = (t->sbhead + 1) % SB_ROWS;
        if (t->sbn < SB_ROWS) ++t->sbn;
        ++t->nscr;
        // looking back: stay on the same rows while new ones arrive
        if (t->view && t->view < t->sbn) ++t->view;
        if (t->llen) --t->erow;
        memcpy(t->cell, t->cell + COLS, (ROWS - 1) * COLS * sizeof(int));
        memcpy(t->runs, t->runs + RUNMAX * 3, (ROWS - 1) * RUNMAX * 3 * sizeof(int));
        memcpy(t->rowok, t->rowok + 1, (ROWS - 1) * sizeof(int));
        memcpy(t->rowk, t->rowk + 1, (ROWS - 1) * sizeof(int));
        clear(t, (ROWS - 1) * COLS, ROWS * COLS);
        t->cy = ROWS - 1;
    }
}

static int attr(struct tgrid *t) {
    int f, b, x;
    f = t->fg; b = t->bg;
    if (t->bold && f < 8) f = f + 8;
    if (t->rev) { x = f; f = b; b = x; }
    return (f << 8) | (b << 16);
}

static void putc_(struct tgrid *t, int c) {
    if (t->wrap) newline(t);
    t->cell[t->cy * COLS + t->cx] = (c & 255) | attr(t);
    t->rowok[t->cy] = 0;
    ++t->cx;
    if (t->cx >= COLS) { t->cx = COLS - 1; t->wrap = 1; }
}

static void sgr(struct tgrid *t) {
    int k, p, v;
    if (!t->np) { t->np = 1; t->param[0] = 0; }
    k = 0;
    while (k < t->np) {
        p = t->param[k];
        if (p == 0) { t->fg = 7; t->bg = 0; t->bold = 0; t->rev = 0; }
        else if (p == 1) t->bold = 1;
        else if (p == 22) t->bold = 0;
        else if (p == 7) t->rev = 1;
        else if (p == 27) t->rev = 0;
        else if (p >= 30 && p <= 37) t->fg = p - 30;
        else if (p == 39) t->fg = 7;
        else if (p >= 40 && p <= 47) t->bg = p - 40;
        else if (p == 49) t->bg = 0;
        else if (p >= 90 && p <= 97) t->fg = p - 90 + 8;
        else if (p >= 100 && p <= 107) t->bg = p - 100 + 8;
        else if (p == 38 || p == 48) {
            // 38;5;N / 48;5;N: one of the 256; 38;2;R;G;B: the nearest of them
            if (k + 2 < t->np && t->param[k + 1] == 5) {
                v = t->param[k + 2] & 255;
                if (p == 38) t->fg = v; else t->bg = v;
                k = k + 2;
            } else if (k + 4 < t->np && t->param[k + 1] == 2) {
                v = 16 + 36 * cube_step(t->param[k + 2]) + 6 * cube_step(t->param[k + 3]) + cube_step(t->param[k + 4]);
                if (p == 38) t->fg = v; else t->bg = v;
                k = k + 4;
            }
        }
        ++k;
    }
}

static void csi(struct tgrid *t, int fin) {
    int p0, p1, n;
    p0 = t->np > 0 ? t->param[0] : 0;
    p1 = t->np > 1 ? t->param[1] : 0;
    n = p0 ? p0 : 1;
    t->wrap = 0;
    if (fin == 'm') sgr(t);
    else if (fin == 'H' || fin == 'f') { t->cy = (p0 ? p0 : 1) - 1; t->cx = (p1 ? p1 : 1) - 1; }
    else if (fin == 'A') t->cy = t->cy - n;
    else if (fin == 'B') t->cy = t->cy + n;
    else if (fin == 'C') t->cx = t->cx + n;
    else if (fin == 'D') t->cx = t->cx - n;
    else if (fin == 'G') t->cx = n - 1;
    else if (fin == 'd') t->cy = n - 1;
    else if (fin == 'J') {
        if (p0 == 2 || p0 == 3) clear(t, 0, ROWS * COLS);
        else if (p0 == 1) clear(t, 0, t->cy * COLS + t->cx + 1);
        else clear(t, t->cy * COLS + t->cx, ROWS * COLS);
    }
    else if (fin == 'K') {
        if (p0 == 2) clear(t, t->cy * COLS, (t->cy + 1) * COLS);
        else if (p0 == 1) clear(t, t->cy * COLS, t->cy * COLS + t->cx + 1);
        else clear(t, t->cy * COLS + t->cx, (t->cy + 1) * COLS);
    }
    else if ((fin == 'h' || fin == 'l') && t->priv && p0 == 25) t->cursor = fin == 'h';
    if (t->cx < 0) t->cx = 0;
    if (t->cy < 0) t->cy = 0;
    if (t->cx >= COLS) t->cx = COLS - 1;
    if (t->cy >= ROWS) t->cy = ROWS - 1;
}

// The window is drawn again only when the grid changed. The ESC _ commands
// are the window's code's (t->apc), which says itself what they changed: a
// game's frames come that way, each only a part of the window (term.c's 'p').
void tg_feed(struct tgrid *t, char *buf, int n) {
    int i, c, grid;
    i = 0; grid = 0;
    while (i < n) {
        c = buf[i] & 255;
        ++i;
        if (t->esc == 1) {
            if (c == '[') { t->esc = 2; t->np = 0; t->priv = 0; t->param[0] = 0; }
            else if (c == '_') { t->esc = 3; t->alen = 0; }
            else t->esc = 0;
            continue;
        }
        if (t->esc == 3) {                         // inside ESC _ ... ESC \
            if (c == 27) t->esc = 4;
            else if (t->alen < TG_APC) { t->abuf[t->alen] = c; ++t->alen; }
            continue;
        }
        if (t->esc == 4) {
            t->esc = 0;
            if (c == '\\') { t->abuf[t->alen] = 0; if (t->apc) t->apc(t->ctx, t->abuf, t->alen); }
            continue;
        }
        if (t->esc == 2) {
            if (c == '?') { t->priv = 1; continue; }
            if (c >= '0' && c <= '9') {
                if (!t->np) t->np = 1;
                t->param[t->np - 1] = t->param[t->np - 1] * 10 + (c - '0');
                continue;
            }
            if (c == ';') { if (!t->np) t->np = 1; if (t->np < 8) { t->param[t->np] = 0; ++t->np; } continue; }
            t->esc = 0;
            if (c >= 64 && c <= 126) csi(t, c);
            grid = 1;
            continue;
        }
        if (c != 27) grid = 1;
        if (c == 27) t->esc = 1;
        else if (c == 10) newline(t);              // a tty turns \n into \r\n
        else if (c == 13) { t->cx = 0; t->wrap = 0; }
        else if (c == 8) { if (t->cx > 0) --t->cx; t->wrap = 0; }
        else if (c == 9) { t->cx = (t->cx + 8) & ~7; if (t->cx >= COLS) t->cx = COLS - 1; }
        else if (c >= 32) putc_(t, c);
    }
    if (grid) wk_invalidate(t->win, 0, 0, 0, 0);
}

void tg_echo(struct tgrid *t, int c) { tmp[0] = c; tg_feed(t, tmp, 1); }
void tg_say(struct tgrid *t, char *s) { tg_feed(t, s, ui_len(s)); }

// ---- line editing -------------------------------------------------------------------

// Put the cursor at character i of the line being typed.
static void ed_goto(struct tgrid *t, int i) {
    int k;
    k = t->erow * COLS + t->ecol + i;
    if (k < 0) k = 0;
    if (k >= ROWS * COLS) { t->cy = ROWS - 1; t->cx = COLS - 1; t->wrap = 1; return; }
    t->cy = k / COLS; t->cx = k % COLS; t->wrap = 0;
}

// Draw the line from character `from` to its end, then `extra` blanks
// over what a longer line left there, and put the cursor back at lpos.
static void ed_tail(struct tgrid *t, int from, int extra) {
    int i;
    ed_goto(t, from);
    i = from;
    while (i < t->llen) { putc_(t, t->line[i]); ++i; }
    while (extra > 0) { putc_(t, ' '); --extra; }
    ed_goto(t, t->lpos);
    wk_redraw_all();
}

// Show s (n characters) as the line, as Up and Down do.
static void ed_replace(struct tgrid *t, char *src, int n) {
    int old, i;
    old = t->llen;
    i = 0;
    while (i < n) { t->line[i] = src[i]; ++i; }
    t->llen = n;
    t->lpos = n;
    ed_tail(t, 0, old > n ? old - n : 0);
}

// The line is done: remember it, unless it is empty or the last one again.
static void ed_remember(struct tgrid *t) {
    int i, same;
    char *h;
    if (!t->llen) return;
    if (t->hn) {
        h = t->hist + (t->hn - 1) * HIST_W;
        same = 1;
        i = 0;
        while (i < t->llen && same) { if (h[i] != t->line[i]) same = 0; ++i; }
        if (same && !h[t->llen]) return;
    }
    if (t->hn == HIST_N) {
        memcpy(t->hist, t->hist + HIST_W, (HIST_N - 1) * HIST_W);
        --t->hn;
    }
    h = t->hist + t->hn * HIST_W;
    i = 0;
    while (i < t->llen) { h[i] = t->line[i]; ++i; }
    h[i] = 0;
    ++t->hn;
}

static void ed_history(struct tgrid *t, int dir) {
    char *h;
    int n;
    if (dir < 0) {
        if (t->hpos <= 0) return;
        if (t->hpos == t->hn) {                // leaving the line being typed: keep it
            memcpy(t->saved, t->line, t->llen);
            t->slen = t->llen;
        }
        --t->hpos;
    } else {
        if (t->hpos >= t->hn) return;
        ++t->hpos;
    }
    if (t->hpos == t->hn) { ed_replace(t, t->saved, t->slen); return; }
    h = t->hist + t->hpos * HIST_W;
    n = 0;
    while (h[n]) ++n;
    ed_replace(t, h, n);
}

void tg_scroll(struct tgrid *t, int rows) {
    t->view = t->view + rows;
    if (t->view > t->sbn) t->view = t->sbn;
    if (t->view < 0) t->view = 0;
    wk_redraw_all();
}

void tg_interrupt(struct tgrid *t) {
    t->view = 0;
    if (t->llen) ed_goto(t, t->llen);
    tg_say(t, "^C\n");
    t->llen = 0; t->lpos = 0; t->hpos = t->hn;
}

void tg_clear_screen(struct tgrid *t) {
    clear(t, 0, ROWS * COLS); t->cx = 0; t->cy = 0; wk_redraw_all();
    if (t->llen) { t->erow = 0; t->ecol = 0; ed_tail(t, 0, 0); }
}

int tg_key(struct tgrid *t, int code, int ch, int mods) {
    int i, n;
    // the scrollback: PgUp and PgDn, a screen at a time
    if (!ch && code == KEY_PGUP) { tg_scroll(t, ROWS - 1); return 0; }
    if (!ch && code == KEY_PGDN) { tg_scroll(t, 1 - ROWS); return 0; }
    // anything else is typing, which happens at the bottom
    if (t->view) { t->view = 0; wk_redraw_all(); }
    // a line starts where the cursor is when its first key comes
    if (!t->llen) {
        if (t->wrap) newline(t);
        t->erow = t->cy; t->ecol = t->cx; t->lpos = 0;
    }
    if (mods & M_CTRL) {
        if (ch == 'a' || ch == 'A' || code == 'A') { t->lpos = 0; ed_goto(t, 0); wk_redraw_all(); }
        else if (ch == 'e' || ch == 'E' || code == 'E') { t->lpos = t->llen; ed_goto(t, t->llen); wk_redraw_all(); }
        else if (ch == 'u' || ch == 'U' || code == 'U') ed_replace(t, t->line, 0);
        return 0;
    }
    if (code == KEY_ENTER || ch == 10) {
        ed_goto(t, t->llen);
        ed_remember(t);
        t->hpos = t->hn;
        t->line[t->llen] = 10;
        n = t->llen + 1;
        t->llen = 0; t->lpos = 0;
        tg_echo(t, 10);
        return n;
    }
    if (!ch) {
        if (code == KEY_LEFT) { if (t->lpos > 0) { --t->lpos; ed_goto(t, t->lpos); wk_redraw_all(); } return 0; }
        if (code == KEY_RIGHT) { if (t->lpos < t->llen) { ++t->lpos; ed_goto(t, t->lpos); wk_redraw_all(); } return 0; }
        if (code == KEY_HOME) { t->lpos = 0; ed_goto(t, 0); wk_redraw_all(); return 0; }
        if (code == KEY_END) { t->lpos = t->llen; ed_goto(t, t->llen); wk_redraw_all(); return 0; }
        if (code == KEY_UP) { ed_history(t, 0 - 1); return 0; }
        if (code == KEY_DOWN) { ed_history(t, 1); return 0; }
        if (code == KEY_DEL) {
            if (t->lpos < t->llen) {
                i = t->lpos;
                while (i < t->llen - 1) { t->line[i] = t->line[i + 1]; ++i; }
                --t->llen;
                ed_tail(t, t->lpos, 1);
            }
            return 0;
        }
    }
    if (code == KEY_BACK) {
        if (t->lpos > 0) {
            i = t->lpos - 1;
            while (i < t->llen - 1) { t->line[i] = t->line[i + 1]; ++i; }
            --t->llen;
            --t->lpos;
            ed_tail(t, t->lpos, 1);
        }
        return 0;
    }
    if (ch >= 32 && ch < 127 && t->llen < TG_LINE) {
        i = t->llen;
        while (i > t->lpos) { t->line[i] = t->line[i - 1]; --i; }
        t->line[t->lpos] = ch;
        ++t->llen;
        ++t->lpos;
        ed_tail(t, t->lpos - 1, 0);
    }
    return 0;
}

// the scroll bar beside the grid: its top is the oldest row kept
void tg_mouse(struct tgrid *t, int ev, int x, int y) {
    int r, bx, bh;
    bx = COLS * CW + 4; bh = ROWS * CH + 4;
    if (ev == E_WHEEL) { tg_scroll(t, 0 - 3 * y); return; }
    if (ev == E_MOVE) {
        r = ui_scroll_drag(bx, 0, y);
        if (r >= 0) { t->view = t->sbn - r; wk_redraw_all(); }
        return;
    }
    if (ev == E_DOWN) {
        r = ui_scroll_click(x, y, bx, 0, bh, t->sbn + ROWS, ROWS, t->sbn - t->view);
        if (r >= 0) { t->view = t->sbn - r; if (t->view < 0) t->view = 0; if (t->view > t->sbn) t->view = t->sbn; wk_redraw_all(); }
    }
}

// ---- the selection --------------------------------------------------------------------
//
// Lines are numbered from the grid's first: line nscr is the grid's top
// row now, and those before it are the scrollback's, as far back as it
// keeps. A selection is two places, where it began and where it was
// dragged to, in whichever order; a run takes every column between them,
// a block only the columns between theirs.

// the cells of line l, or 0 for one the scrollback no longer holds
static int *row_of(struct tgrid *t, int l) {
    int d;
    d = t->nscr - l;
    if (d > 0) {
        if (d > t->sbn) return 0;
        return t->sb + ((t->sbhead - d + SB_ROWS) % SB_ROWS) * COLS;
    }
    if (0 - d >= ROWS) return 0;
    return t->cell + (0 - d) * COLS;
}

// the columns of line l the selection takes, a to b: 0 if none
static int sel_cols(struct tgrid *t, int l, int *a, int *b) {
    int l0, c0, l1, c1, k;
    if (!t->sel) return 0;
    l0 = t->sl0; c0 = t->sc0; l1 = t->sl1; c1 = t->sc1;
    if (l1 < l0 || (l1 == l0 && c1 < c0)) { k = l0; l0 = l1; l1 = k; k = c0; c0 = c1; c1 = k; }
    if (l < l0 || l > l1) return 0;
    if (t->sel == 2) { *a = c0 < c1 ? c0 : c1; *b = c0 < c1 ? c1 : c0; return 1; }
    *a = l == l0 ? c0 : 0;
    *b = l == l1 ? c1 : COLS - 1;
    return 1;
}

void tg_select(struct tgrid *t, int ev, int x, int y, int block) {
    int l, c, r;
    c = x / CW; r = y / CH;
    if (x < 0 || c < 0) c = 0;
    if (c >= COLS) c = COLS - 1;
    if (y < 0 || r < 0) r = 0;
    if (r >= ROWS) r = ROWS - 1;
    l = t->nscr - t->view + r;
    if (ev == E_DOWN) {
        if (t->sel) wk_invalidate(t->win, 0, 0, 0, 0);
        t->sel = 0;
        t->selecting = block ? 2 : 1;
        t->sl0 = l; t->sc0 = c; t->sl1 = l; t->sc1 = c;
    } else if (ev == E_MOVE && t->selecting) {
        if (l == t->sl1 && c == t->sc1) return;
        t->sl1 = l; t->sc1 = c;
        t->sel = l != t->sl0 || c != t->sc0 ? t->selecting : 0;
        wk_invalidate(t->win, 0, 0, 0, 0);
    } else if (ev == E_UP) t->selecting = 0;
}

void tg_select_all(struct tgrid *t) {
    t->sel = 1; t->selecting = 0;
    t->sl0 = t->nscr - t->sbn; t->sc0 = 0;
    t->sl1 = t->nscr + ROWS - 1; t->sc1 = COLS - 1;
    wk_invalidate(t->win, 0, 0, 0, 0);
}

void tg_unselect(struct tgrid *t) {
    if (t->sel) wk_invalidate(t->win, 0, 0, 0, 0);
    t->sel = 0; t->selecting = 0;
}

// Each line's text, its trailing spaces gone, a newline between lines;
// everything (all) ends at its last line with something on it.
int tg_copy(struct tgrid *t, int all) {
    int l, la, lb, a, b, n, end, start, v, *row;
    char *s;
    if (all) { la = t->nscr - t->sbn; lb = t->nscr + ROWS - 1; }
    else {
        if (!t->sel) return 0;
        la = t->sl0 < t->sl1 ? t->sl0 : t->sl1;
        lb = t->sl0 < t->sl1 ? t->sl1 : t->sl0;
    }
    if (!(s = wk_alloc((lb - la + 1) * (COLS + 1) + 1))) return 0;
    n = 0; end = 0;
    l = la;
    while (l <= lb) {
        a = 0; b = COLS - 1;
        if ((row = row_of(t, l)) && (all || sel_cols(t, l, &a, &b))) {
            start = n;
            while (a <= b) { v = row[a] & 255; s[n] = v >= 32 && v < 127 ? v : ' '; ++n; ++a; }
            while (n > start && s[n - 1] == ' ') --n;
            if (!all) end = n;
            else if (n > start) end = n + 1;
            if (l < lb || all) { s[n] = 10; ++n; }
        }
        ++l;
    }
    wk_clip_set(s, end);
    wk_free(s);
    return 1;
}

// ---- drawing ----------------------------------------------------------------------

// Work out row r's runs: its rectangles of background, and its stretches
// of text in one colour that are not all blank -- what tg_draw would
// draw for it -- into the row cache. A row with more than RUNMAX gets
// rowk -1 and is drawn from its cells every time.
static void row_build(struct tgrid *t, int r) {
    int c, k, f, b, start, blank, *row, *run;
    row = t->cell + r * COLS;
    run = t->runs + r * RUNMAX * 3;
    k = 0;
    c = 0;
    while (c < COLS) {
        b = (row[c] >> 16) & 255;
        start = c;
        while (c < COLS && ((row[c] >> 16) & 255) == b) ++c;
        if (b) {
            if (k == RUNMAX) { t->rowk[r] = 0 - 1; t->rowok[r] = 1; return; }
            run[3 * k] = start; run[3 * k + 1] = c - start; run[3 * k + 2] = b;
            ++k;
        }
    }
    c = 0;
    while (c < COLS) {
        f = (row[c] >> 8) & 255;
        start = c;
        blank = 1;
        while (c < COLS && ((row[c] >> 8) & 255) == f) { if ((row[c] & 255) != ' ') blank = 0; ++c; }
        if (!blank) {
            if (k == RUNMAX) { t->rowk[r] = 0 - 1; t->rowok[r] = 1; return; }
            run[3 * k] = start; run[3 * k + 1] = c - start; run[3 * k + 2] = (1 << 8) | f;
            ++k;
        }
    }
    t->rowk[r] = k;
    t->rowok[r] = 1;
}

// n characters of row r from column c, into tmp
static void row_text(struct tgrid *t, int r, int c, int n) {
    int i, *row;
    row = t->cell + r * COLS + c;
    i = 0;
    while (i < n) { tmp[i] = row[i] & 255; ++i; }
    tmp[n] = 0;
}

// A row from its cells, at screen row r: the grid's own, or one from the
// scrollback.
static void row_scan(int *row, int r, int ox, int oy) {
    int c, k, a, f, b, start;
    char *s;
    c = 0;
    while (c < COLS) {
        b = (row[c] >> 16) & 255;
        start = c;
        while (c < COLS && ((row[c] >> 16) & 255) == b) ++c;
        if (b) d_rect(ox + start * CW, oy + r * CH, (c - start) * CW, CH, tg_pal[b]);
    }
    c = 0;
    while (c < COLS) {
        f = (row[c] >> 8) & 255;
        start = c;
        s = tmp;
        while (c < COLS && ((row[c] >> 8) & 255) == f && c - start < 90) { *s = row[c] & 255; ++s; ++c; }
        *s = 0;
        k = 0; a = 0;
        while (tmp[k]) { if (tmp[k] != ' ') a = 1; ++k; }
        if (a) d_textn(ox + start * CW, oy + r * CH + 1, tg_pal[f], TG_FONT, F_MONO, CW, tmp, c - start);
    }
}

// The grid, a row at a time from the row cache (the scan of 2,000 cells
// twice over was a third of what an idle desktop's redraw cost), at
// ox, oy inside its sunken edge, its scroll bar beside that edge.
void tg_draw(struct tgrid *t, int ox, int oy, int focused) {
    int r, k, n, g, v, *run;
    // Looking back, the top `view` rows come from the scrollback, the
    // newest of them last; the grid's rows follow, lower by as many.
    ui_scrollbar(ox - 2 + COLS * CW + 4, oy - 2, ROWS * CH + 4, t->sbn + ROWS, ROWS, t->sbn - t->view);
    v = t->view;
    r = 0;
    while (r < v && r < ROWS) {
        row_scan(t->sb + ((t->sbhead - v + r + 2 * SB_ROWS) % SB_ROWS) * COLS, r, ox, oy);
        ++r;
    }
    while (r < ROWS) {
        g = r - v;
        if (!t->rowok[g]) row_build(t, g);
        n = t->rowk[g];
        if (n < 0) row_scan(t->cell + g * COLS, r, ox, oy);
        run = t->runs + g * RUNMAX * 3;
        k = 0;
        while (k < n) {
            if (run[2] >> 8) {
                row_text(t, g, run[0], run[1]);
                d_textn(ox + run[0] * CW, oy + r * CH + 1, tg_pal[run[2] & 255], TG_FONT, F_MONO, CW, tmp, run[1]);
            } else d_rect(ox + run[0] * CW, oy + r * CH, run[1] * CW, CH, tg_pal[run[2]]);
            run = run + 3;
            ++k;
        }
        ++r;
    }
    // the selection, as a console shows it: black on the text's grey
    r = 0;
    while (t->sel && r < ROWS) {
        if (sel_cols(t, t->nscr - v + r, &k, &n) && (run = row_of(t, t->nscr - v + r))) {
            d_rect(ox + k * CW, oy + r * CH, (n - k + 1) * CW, CH, tg_pal[7]);
            g = 0;
            while (k + g <= n) { tmp[g] = run[k + g] & 255; if (tmp[g] < 32 || tmp[g] > 126) tmp[g] = ' '; ++g; }
            d_textn(ox + k * CW, oy + r * CH + 1, C_DARK, TG_FONT, F_MONO, CW, tmp, g);
        }
        ++r;
    }
    if (focused && t->cursor && !t->view)
        d_rect(ox + t->cx * CW, oy + t->cy * CH + CH - 3, CW, 2, tg_pal[7]);
}
// ui.c -- the window kit's widgets, drawn through d_* (draw.c). docs/c4ix-desktop.md.
//
// Stateless: each call draws one thing, or answers whether a point hit
// it. The tools keep their own state (selection, scroll position, which
// field has the caret) and pass it in.

#include "winkit.h"

// ---- strings ----------------------------------------------------------------

int ui_len(char *s) { int n; n = 0; while (s[n]) ++n; return n; }
void ui_cpy(char *d, char *s) { while (*s) { *d = *s; ++d; ++s; } *d = 0; }
void ui_cat(char *d, char *s) { while (*d) ++d; ui_cpy(d, s); }
int ui_eq(char *a, char *b) { while (*a && *a == *b) { ++a; ++b; } return *a == *b; }
// Bounded copies, for every path and name kept in a fixed buffer: at
// most n - 1 bytes and a 0, and 1 if all of it fit. A caller refuses
// what did not fit, rather than keep it cut short. (d and s may be the
// same buffer.)
int ui_ncpy(char *d, char *s, int n) {
    int k;
    if (n <= 0) return 0;
    k = 0;
    while (s[k] && k < n - 1) { d[k] = s[k]; ++k; }
    d[k] = 0;
    return !s[k];
}
int ui_ncat(char *d, char *s, int n) {
    int k;
    k = ui_len(d);
    return ui_ncpy(d + k, s, n - k);
}
// dir and name joined by one '/', into out (which may be dir)
int ui_join(char *out, char *dir, char *name, int n) {
    int k;
    if (out != dir && !ui_ncpy(out, dir, n)) return 0;
    k = ui_len(out);
    if (k > 0 && out[k - 1] != '/') {
        if (k + 1 >= n) return 0;
        out[k] = '/'; out[k + 1] = 0;
    }
    return ui_ncat(out, name, n);
}
char *ui_base(char *p) {
    int k;
    k = ui_len(p);
    while (k > 0 && p[k - 1] != '/') --k;
    return p + k;
}

int ui_ends(char *s, char *suffix) {
    int n, m;
    n = ui_len(s); m = ui_len(suffix);
    if (m > n) return 0;
    return ui_eq(s + n - m, suffix);
}

char *ui_num(char *buf, int v) {
    char t[24];
    int n, neg, k;
    // digits from the remainders, kept positive: INT_MIN has no positive
    // twin to negate into
    neg = v < 0;
    n = 0;
    while (1) { k = v % 10; if (k < 0) k = 0 - k; t[n] = '0' + k; ++n; v = v / 10; if (!v) break; }
    k = 0;
    if (neg) { buf[k] = '-'; ++k; }
    while (n) { --n; buf[k] = t[n]; ++k; }
    buf[k] = 0;
    return buf;
}

char *ui_num_commas(char *buf, int v) {
    char t[32];
    int n, k, i;
    ui_num(t, v);
    n = ui_len(t);
    k = 0;
    i = 0;
    while (i < n) {
        buf[k] = t[i]; ++k;
        if (t[i] != '-' && (n - i - 1) % 3 == 0 && i < n - 1) { buf[k] = ','; ++k; }
        ++i;
    }
    buf[k] = 0;
    return buf;
}

int ui_hit(int px, int py, int x, int y, int w, int h) {
    return px >= x && py >= y && px < x + w && py < y + h;
}

// ---- controls ------------------------------------------------------------------

void ui_button(int x, int y, int w, int h, char *label, int pressed, int deflt) {
    int lw;
    if (ui_style == S_FLAT) {
        // a light face and an outline; the default's in the accent, two deep
        d_rect(x, y, w, h, pressed ? ui_mix(C_FACE, C_SHADOW, 1, 3) : C_LIGHT);
        d_bevel(x, y, w, h, B_RAISED);
        if (deflt) { d_recto(x, y, w - 1, h - 1, C_TITLE); d_recto(x + 1, y + 1, w - 3, h - 3, C_TITLE); }
        lw = ui_len(label) * 6;
        d_text(x + (w - lw) / 2, y + (h - 12) / 2, C_DARK, F_SANS, label);
        return;
    }
    d_rect(x, y, w, h, C_FACE);
    if (deflt) { d_recto(x - 1, y - 1, w + 1, h + 1, C_DARK); }
    d_bevel(x, y, w, h, pressed ? B_PRESSED : B_RAISED);
    lw = ui_len(label) * 6;
    d_text(x + (w - lw) / 2 + (pressed ? 1 : 0), y + (h - 12) / 2 + (pressed ? 1 : 0), C_DARK, F_SANS, label);
}

// A vertical scroll bar: arrows at both ends, a thumb sized to what is
// visible. Nothing to scroll draws it disabled.
void ui_scrollbar(int x, int y, int h, int total, int visible, int top) {
    int track, th, ty;
    d_rect(x, y, 16, h, 0xe0e0e0);
    if (ui_style != S_FLAT) {
        d_rect(x, y, 16, 16, C_FACE); d_bevel(x, y, 16, 16, B_RAISED);
        d_rect(x, y + h - 16, 16, 16, C_FACE); d_bevel(x, y + h - 16, 16, 16, B_RAISED);
    }
    d_line(x + 8, y + 5, x + 4, y + 9, C_DARK); d_line(x + 8, y + 5, x + 12, y + 9, C_DARK);
    d_rect(x + 4, y + 9, 9, 1, C_DARK);
    d_line(x + 4, y + h - 10, x + 8, y + h - 6, C_DARK); d_line(x + 12, y + h - 10, x + 8, y + h - 6, C_DARK);
    d_rect(x + 4, y + h - 11, 9, 1, C_DARK);
    track = h - 32;
    if (total <= visible || track < 8) return;
    th = (track * visible) / total;
    if (th < 10) th = 10;
    ty = y + 16 + ((track - th) * top) / (total - visible);
    if (ui_style == S_FLAT) { d_rect(x + 4, ty + 1, 8, th - 2, C_SHADOW); return; }
    d_rect(x, ty, 16, th, C_FACE);
    d_bevel(x, ty, 16, th, B_RAISED);
}

// A drag of a scroll bar's thumb. ui_scroll_click starts one when it is
// the thumb that is pressed; each move then asks ui_scroll_drag for the
// top line, naming the bar by where it is (a window may have two); the
// desktop ends it when the button comes up. The thumb keeps its place
// under the pointer: a pixel of travel is (total - visible) / (track -
// thumb) lines.
//
// A press on an arrow or on the track either side of the thumb is said
// to repeat (ui_scroll_repeat): the desktop presses it again while the
// button is held (wmcore.c), so a held arrow keeps scrolling, as a held
// track pages until the thumb reaches the pointer.
static int sd_on, sd_x, sd_y, sd_y0, sd_top0, sd_range, sd_span, sr_on;
static int sp_on, sp_x0, sp_pos0;     // a splitter's drag (below)

int ui_scroll_drag(int x, int y, int py) {
    int top;
    if (!sd_on || x != sd_x || y != sd_y) return 0 - 1;
    top = sd_top0;
    if (sd_span > 0) top = sd_top0 + ((py - sd_y0) * sd_range) / sd_span;
    if (top > sd_range) top = sd_range;
    if (top < 0) top = 0;
    return top;
}
int ui_scroll_active() { return sd_on || sp_on; }
int ui_scroll_repeat() { return sr_on; }
void ui_scroll_end() { sd_on = 0; sr_on = 0; sp_on = 0; }

// A bar across, for what is wider than its pane: the same parts turned
// on their side. LEFT is the first column shown of TOTAL, VISIBLE at once.
void ui_hscrollbar(int x, int y, int w, int total, int visible, int left) {
    int track, tw, tx;
    d_rect(x, y, w, 16, 0xe0e0e0);
    if (ui_style != S_FLAT) {
        d_rect(x, y, 16, 16, C_FACE); d_bevel(x, y, 16, 16, B_RAISED);
        d_rect(x + w - 16, y, 16, 16, C_FACE); d_bevel(x + w - 16, y, 16, 16, B_RAISED);
    }
    d_line(x + 5, y + 8, x + 9, y + 4, C_DARK); d_line(x + 5, y + 8, x + 9, y + 12, C_DARK);
    d_rect(x + 9, y + 4, 1, 9, C_DARK);
    d_line(x + w - 6, y + 8, x + w - 10, y + 4, C_DARK); d_line(x + w - 6, y + 8, x + w - 10, y + 12, C_DARK);
    d_rect(x + w - 11, y + 4, 1, 9, C_DARK);
    track = w - 32;
    if (total <= visible || track < 8) return;
    tw = (track * visible) / total;
    if (tw < 10) tw = 10;
    tx = x + 16 + ((track - tw) * left) / (total - visible);
    if (ui_style == S_FLAT) { d_rect(tx + 1, y + 4, tw - 2, 8, C_SHADOW); return; }
    d_rect(tx, y, tw, 16, C_FACE);
    d_bevel(tx, y, tw, 16, B_RAISED);
}

// The new first column for a click on a bar across, or -1 if it missed. A
// press on the thumb starts a drag, which ui_scroll_drag then follows with
// the pointer's x.
int ui_hscroll_click(int px, int py, int x, int y, int w, int total, int visible, int left) {
    int track, tw, tx, max;
    if (!ui_hit(px, py, x, y, w, 16)) return 0 - 1;
    max = total - visible;
    if (max < 0) max = 0;
    if (px < x + 16) { left = left - 1; sr_on = 1; }
    else if (px >= x + w - 16) { left = left + 1; sr_on = 1; }
    else {
        track = w - 32;
        if (total <= visible) return left;
        tw = (track * visible) / total;
        if (tw < 10) tw = 10;
        tx = x + 16 + ((track - tw) * left) / (total - visible);
        if (px < tx) { left = left - visible; sr_on = 1; }
        else if (px >= tx + tw) { left = left + visible; sr_on = 1; }
        else { sd_on = 1; sd_x = x; sd_y = y; sd_y0 = px; sd_top0 = left; sd_range = total - visible; sd_span = track - tw; }
    }
    if (left > max) left = max;
    if (left < 0) left = 0;
    return left;
}

// The new top line for a click on the scroll bar, or -1 if it missed.
int ui_scroll_click(int px, int py, int x, int y, int h, int total, int visible, int top) {
    int track, th, ty, max;
    if (!ui_hit(px, py, x, y, 16, h)) return 0 - 1;
    max = total - visible;
    if (max < 0) max = 0;
    if (py < y + 16) { top = top - 1; sr_on = 1; }
    else if (py >= y + h - 16) { top = top + 1; sr_on = 1; }
    else {
        track = h - 32;
        if (total <= visible) return top;
        th = (track * visible) / total;
        if (th < 10) th = 10;
        ty = y + 16 + ((track - th) * top) / (total - visible);
        if (py < ty) { top = top - visible; sr_on = 1; }
        else if (py >= ty + th) { top = top + visible; sr_on = 1; }
        else { sd_on = 1; sd_x = x; sd_y = y; sd_y0 = py; sd_top0 = top; sd_range = total - visible; sd_span = track - th; }
    }
    if (top > max) top = max;
    if (top < 0) top = 0;
    return top;
}

// A single-line text field: sunken white, monospace so the caret can sit
// exactly between two characters (7 pixels a character).
void ui_field(int x, int y, int w, char *text, int caret, int focused) {
    int n, first, show;
    d_rect(x, y, w, 22, C_WHITE);
    d_bevel(x, y, w, 22, B_SUNKEN);
    n = ui_len(text);
    show = (w - 10) / 7;
    first = 0;
    if (caret > show) first = caret - show;
    d_textn(x + 4, y + 5, C_DARK, 12, F_MONO, 7, text + first, n - first > show ? show : n - first);
    if (focused) d_rect(x + 4 + (caret - first) * 7, y + 4, 1, 14, C_DARK);
}

// Where a click at px puts the caret in a field drawn as above.
int ui_field_hit(int px, int x, int w, char *text, int caret) {
    int n, first, show, c;
    n = ui_len(text);
    show = (w - 10) / 7;
    first = 0;
    if (caret > show) first = caret - show;
    c = first + (px - x - 4) / 7;
    if (c > n) c = n;
    if (c < 0) c = 0;
    return c;
}

// Editing keys for a field's text; returns 1 if the text changed.
static int ctrl_letter(int code, int ch, int mods, int c) {
    return (mods & M_CTRL) && !(mods & M_ALT) && (ch == c || ch == c + 32 || code == c);
}
int ui_key_copy(int code, int ch, int mods) { return ctrl_letter(code, ch, mods, 'C') || ((mods & M_CTRL) && code == KEY_INS); }
int ui_key_cut(int code, int ch, int mods) { return ctrl_letter(code, ch, mods, 'X') || ((mods & M_SHIFT) && code == KEY_DEL); }
int ui_key_paste(int code, int ch, int mods) { return ctrl_letter(code, ch, mods, 'V') || ((mods & M_SHIFT) && code == KEY_INS); }

// A field has no selection: copy and cut take the whole of it, and a
// paste puts the clipboard's first line in at the caret, as much as fits.
int ui_field_key(char *text, int max, int *caret, int code, int ch, int mods) {
    int n, i, k, cn;
    char *c;
    n = ui_len(text);
    if (ui_key_copy(code, ch, mods) || ui_key_cut(code, ch, mods)) {
        wk_clip_set(text, n);
        if (!ui_key_cut(code, ch, mods) || !n) return 0;
        text[0] = 0; *caret = 0;
        return 1;
    }
    if (ui_key_paste(code, ch, mods)) {
        c = wk_clip_get(&cn);
        k = 0;
        while (k < cn && c[k] != 10 && c[k] != 13 && n < max) {
            if (c[k] >= 32 && c[k] <= 126) {
                i = n + 1;
                while (i > *caret) { text[i] = text[i - 1]; --i; }
                text[*caret] = c[k];
                *caret = *caret + 1;
                ++n;
            }
            ++k;
        }
        return k > 0;
    }
    if (code == KEY_LEFT) { if (*caret > 0) *caret = *caret - 1; return 0; }
    if (code == KEY_RIGHT) { if (*caret < n) *caret = *caret + 1; return 0; }
    if (code == KEY_HOME) { *caret = 0; return 0; }
    if (code == KEY_END) { *caret = n; return 0; }
    if (code == KEY_BACK) {
        if (*caret == 0) return 0;
        i = *caret - 1;
        while (i < n) { text[i] = text[i + 1]; ++i; }
        *caret = *caret - 1;
        return 1;
    }
    if (code == KEY_DEL) {
        if (*caret >= n) return 0;
        i = *caret;
        while (i < n) { text[i] = text[i + 1]; ++i; }
        return 1;
    }
    if ((mods & M_CTRL) || ch < 32 || ch > 126 || n >= max) return 0;
    i = n + 1;
    while (i > *caret) { text[i] = text[i - 1]; --i; }
    text[*caret] = ch;
    *caret = *caret + 1;
    return 1;
}

// Tabs across the top of a property sheet, the selected one raised into
// the page below it.
void ui_tabs(int x, int y, char **labels, int n, int sel) {
    int k, tx, tw;
    tx = x;
    k = 0;
    while (k < n) {
        tw = ui_len(labels[k]) * 7 + 16;
        if (ui_style == S_FLAT) {
            d_rect(tx, y, tw, 22, k == sel ? C_LIGHT : C_FACE);
            if (k == sel) d_rect(tx, y + 19, tw, 3, C_TITLE);
            d_text(tx + 8, y + 5, C_DARK, k == sel ? F_BOLD : F_SANS, labels[k]);
        } else if (k == sel) {
            d_rect(tx - 2, y, tw + 4, 22, C_FACE);
            d_rect(tx - 2, y, tw + 4, 1, C_LIGHT); d_rect(tx - 2, y, 1, 22, C_LIGHT);
            d_rect(tx + tw + 1, y + 1, 1, 21, C_DARK);
            d_text(tx + 8, y + 5, C_DARK, F_SANS, labels[k]);
        } else {
            d_rect(tx, y + 3, tw, 1, C_LIGHT); d_rect(tx, y + 3, 1, 19, C_LIGHT);
            d_rect(tx + tw - 1, y + 4, 1, 18, C_DARK);
            d_text(tx + 8, y + 7, C_DARK, F_SANS, labels[k]);
        }
        tx = tx + tw;
        ++k;
    }
}

int ui_tab_hit(int px, int py, int x, int y, char **labels, int n) {
    int k, tx, tw;
    if (py < y || py >= y + 22) return 0 - 1;
    tx = x;
    k = 0;
    while (k < n) {
        tw = ui_len(labels[k]) * 7 + 16;
        if (px >= tx && px < tx + tw) return k;
        tx = tx + tw;
        ++k;
    }
    return 0 - 1;
}

// A group box: an etched frame with its label set into the top edge.
void ui_group(int x, int y, int w, int h, char *label) {
    d_bevel(x, y + 6, w, h - 6, B_ETCHED);
    d_rect(x + 8, y, ui_len(label) * 6 + 6, 12, C_FACE);
    d_text(x + 10, y, C_DARK, F_SANS, label);
}

void ui_radio(int x, int y, char *label, int on) {
    d_disc(x + 6, y + 6, 6, ui_style == S_FLAT && on ? C_TITLE : C_SHADOW);
    d_disc(x + 6, y + 6, 5, C_WHITE);
    if (on) d_disc(x + 6, y + 6, ui_style == S_FLAT ? 3 : 2, ui_style == S_FLAT ? C_TITLE : C_DARK);
    d_text(x + 16, y, C_DARK, F_SANS, label);
}

// A list view's column headers: raised buttons side by side.
void ui_header(int x, int y, int *widths, char **labels, int n) {
    int k;
    k = 0;
    while (k < n) {
        d_rect(x, y, widths[k], 18, C_FACE);
        if (ui_style == S_FLAT) { d_rect(x, y + 17, widths[k], 1, C_SHADOW); d_rect(x + widths[k] - 1, y + 3, 1, 12, C_SHADOW); }
        else d_bevel(x, y, widths[k], 18, B_RAISED);
        d_text(x + 5, y + 3, C_DARK, F_SANS, labels[k]);
        x = x + widths[k];
        ++k;
    }
}

// A check box: a sunken white square, ticked when ON, its label beside it.
void ui_check(int x, int y, char *label, int on) {
    int k;
    d_rect(x, y, 13, 13, C_WHITE);
    if (ui_style == S_FLAT) d_recto(x, y, 13, 13, on ? C_TITLE : C_SHADOW);
    else d_bevel(x, y, 13, 13, B_SUNKEN);
    if (on) {
        k = 0;
        while (k < 7) { d_rect(x + 3 + k, y + (k < 2 ? 5 + k : 9 - k), 2, 2, ui_style == S_FLAT ? C_TITLE : C_DARK); ++k; }
    }
    d_text(x + 18, y, C_DARK, F_SANS, label);
}

// ---- a splitter ------------------------------------------------------------------
//
// The bar between two panes side by side, dragged across to size them.
// ui_split_click starts a drag when the bar is pressed, from POS (what the
// window sizes by it, the left pane's width); each move then asks
// ui_split_drag what the pointer has made that, which the window keeps
// within its limits. The drag ends when the button comes up, as a thumb's
// does (ui_scroll_end), and follows the pointer out of the window
// meanwhile (ui_scroll_active).

void ui_splitter(int x, int y, int w, int h) {
    int k;
    d_rect(x, y, w, h, C_FACE);
    d_rect(x, y, 1, h, C_LIGHT);
    d_rect(x + w - 1, y, 1, h, C_SHADOW);
    // a grip in the middle, three dots down
    k = 0;
    while (k < 3 && h > 30) { d_rect(x + w / 2 - 1, y + h / 2 - 7 + k * 6, 2, 2, C_SHADOW); ++k; }
}
int ui_split_click(int px, int py, int x, int y, int w, int h, int pos) {
    if (!ui_hit(px, py, x, y, w, h)) return 0;
    sp_on = 1; sp_x0 = px; sp_pos0 = pos;
    return 1;
}
int ui_split_drag(int px) { return sp_on ? sp_pos0 + px - sp_x0 : 0 - 1; }
int ui_split_active() { return sp_on; }

// ---- a find bar --------------------------------------------------------------------
//
// Under an editor's text: what to find, Next and Previous, Match case, a
// note of what the last look found, and a box to close it. The editor
// keeps one (struct ui_find) and does the looking; the bar takes the
// keys while it has them (f->keys) and the clicks on it, and says what
// they asked for: UF_NEXT, UF_PREV, UF_TYPED (the text changed, to look
// again from where the match is), UF_CLOSE. Enter is Next, Shift+Enter
// Previous, F3 and Shift+F3 the same, Esc closes, Alt+C turns Match case
// over.

// where its parts are, for a bar W wide at (x, y)
static int fb_fx, fb_fw, fb_nx, fb_px, fb_cx, fb_tx, fb_xx;
static void fb_layout(int x, int w) {
    fb_fw = w < 620 ? w - 470 : 150;          // narrower, so the note keeps some room
    if (fb_fw < 80) fb_fw = 80;
    fb_fx = x + 40;
    fb_nx = fb_fx + fb_fw + 6;                 // Next
    fb_px = fb_nx + 50;                        // Previous
    fb_cx = fb_px + 70;                        // Match case
    fb_tx = fb_cx + 92;                        // the note
    fb_xx = x + w - 22;                        // the close box
}

void ui_find_open(struct ui_find *f, char *seed, int n) {
    int k;
    f->on = 1; f->keys = 1;
    if (seed && n > 0 && n < UI_FIND_MAX) {
        k = 0;
        while (k < n && seed[k] != 10 && seed[k] != 13) ++k;
        if (k == n) { memcpy(f->text, seed, n); f->text[n] = 0; }
    }
    f->caret = ui_len(f->text);
    f->note[0] = 0; f->bad = 0;
}

void ui_find_say(struct ui_find *f, char *note, int bad) {
    ui_ncpy(f->note, note, 64);
    f->bad = bad;
}

void ui_find_draw(struct ui_find *f, int x, int y, int w, int focused) {
    fb_layout(x, w);
    d_rect(x, y, w, UI_FIND_H, C_FACE);
    d_rect(x, y, w, 1, C_SHADOW);
    d_rect(x, y + 1, w, 1, C_LIGHT);
    d_text(x + 6, y + 8, C_DARK, F_SANS, "Find:");
    ui_field(fb_fx, y + 4, fb_fw, f->text, f->caret, focused && f->keys);
    ui_button(fb_nx, y + 4, 46, 22, "Next", 0, 0);
    ui_button(fb_px, y + 4, 66, 22, "Previous", 0, 0);
    ui_check(fb_cx, y + 9, "Match case", f->mcase);
    if (f->note[0] && fb_tx < fb_xx - 12) {
        d_clip(fb_tx, y + 2, fb_xx - 4 - fb_tx, UI_FIND_H - 2);
        d_text(fb_tx, y + 8, f->bad ? 0xc00000 : C_DARK, F_SANS, f->note);
        d_clip_end();
    }
    ui_button(fb_xx, y + 5, 18, 18, "x", 0, 0);
}

int ui_find_mouse(struct ui_find *f, int ev, int px, int py, int x, int y, int w) {
    if (!f->on || !ui_hit(px, py, x, y, w, UI_FIND_H)) return 0 - 1;
    if (ev != E_DOWN) return UF_NONE;
    fb_layout(x, w);
    f->keys = 1;
    if (ui_hit(px, py, fb_fx, y + 4, fb_fw, 22)) { f->caret = ui_field_hit(px, fb_fx, fb_fw, f->text, f->caret); return UF_NONE; }
    if (ui_hit(px, py, fb_nx, y + 4, 46, 22)) return UF_NEXT;
    if (ui_hit(px, py, fb_px, y + 4, 66, 22)) return UF_PREV;
    if (ui_hit(px, py, fb_cx, y + 6, 88, 18)) { f->mcase = !f->mcase; return UF_NONE; }
    if (ui_hit(px, py, fb_xx, y + 5, 18, 18)) { f->on = 0; f->keys = 0; return UF_CLOSE; }
    return UF_NONE;
}

int ui_find_key(struct ui_find *f, int code, int ch, int mods) {
    if (code == KEY_ESC) { f->on = 0; f->keys = 0; return UF_CLOSE; }
    if (code == KEY_ENTER || code == KEY_F3) return (mods & M_SHIFT) ? UF_PREV : UF_NEXT;
    if ((mods & M_ALT) && (ch == 'c' || ch == 'C' || code == 'C')) { f->mcase = !f->mcase; return UF_NONE; }
    if (ui_field_key(f->text, UI_FIND_MAX - 1, &f->caret, code, ch, mods)) { f->note[0] = 0; f->bad = 0; return UF_TYPED; }
    return UF_NONE;
}

// Does what F looks for start at S, which has N characters to look at?
int ui_find_at(struct ui_find *f, char *s, int n) {
    int m, k, a, b;
    m = ui_len(f->text);
    if (!m || m > n) return 0;
    k = 0;
    while (k < m) {
        a = s[k] & 255; b = f->text[k] & 255;
        if (a != b) {
            if (f->mcase) return 0;
            if (a >= 'A' && a <= 'Z') a = a + 32;
            if (b >= 'A' && b <= 'Z') b = b + 32;
            if (a != b) return 0;
        }
        ++k;
    }
    return 1;
}
// wmcore.c -- the window kit's window manager. docs/grin-plan.md 3.5.
//
// The windows: a list in the order they opened, and through the same
// nodes a z-order, bottom first. Focus is the topmost window showing; a
// dialog on top keeps the input to itself. The mouse drags title bars and
// sizes windows, menu bars open drop-downs, and everything else is handed
// to the window's class, in its client area's coordinates. The shell
// draws what lies under and over the windows (struct wk_shell).

#include "wkwin.h"
#include "wkgui.h"

static struct wk_shell *shell;
static struct win *first;
static struct win *zbot, *ztop;
static int next_id;
static int drag, drag_dx, drag_dy;        // a window's number while its title bar is dragged
static int sizing, size_edges, size_w0, size_h0, size_x0, size_y0, size_wx, size_wy;
static int down_win, down_t, down_x, down_y;   // for double clicks
// a press on a scroll bar's arrow or track (ui_scroll_repeat), pressed
// again while the button is held: after REP_WAIT, every REP_MS
enum { REP_WAIT = 400, REP_MS = 50 };
static int rep_win, rep_x, rep_y, rep_b, rep_next;
static int menu_win, menu_idx, menu_hot;  // an open drop-down: its window, menu (-1 the
                                          // system menu, M_POPUP a pop-up's), hot item
static char **pop_items;                  // a pop-up menu's items (wk_popup), and where it is
static int pop_x, pop_y;
enum { M_POPUP = 0 - 2 };
static int ptr_shape;
static char *clip_text;
static int clip_n;

enum { MIN_W = 220, MIN_H = 140, DROP_W = 160 };

int wk_now() { return __time(); }

// ---- the list -------------------------------------------------------------------

struct win *win_get(int i) {
    struct win *w;
    if (i <= 0) return 0;
    w = first;
    while (w) { if (w->id == i && w->used) return w; w = w->next; }
    return 0;
}
int win_index(struct win *w) { return w ? w->id : 0 - 1; }
struct win *win_first() { return first; }

int wk_alive(int i) { return win_get(i) != 0; }
void *wk_state(int i) { struct win *w; w = win_get(i); return w ? w->st : 0; }
struct wk_class *wk_class_of(int i) { struct win *w; w = win_get(i); return w ? w->cls : 0; }
char *wk_get_title(int i) { struct win *w; w = win_get(i); return w ? w->title : ""; }

int wk_find(struct wk_class *c) {
    struct win *w;
    w = first;
    while (w) { if (w->used && w->cls == c) return w->id; w = w->next; }
    return 0;
}

int wk_next(int i) {
    struct win *w;
    w = first;
    if (i > 0) {
        while (w && w->id != i) w = w->next;
        if (w) w = w->next;
    }
    while (w && !w->used) w = w->next;
    return w ? w->id : 0;
}

int wk_client_x(struct win *w) { return w->x + BORDER; }
static int menu_h(struct win *w) { return w->nmenus ? MENU_H : 0; }
int wk_client_y(struct win *w) { return w->y + BORDER + TITLE_H + 1 + menu_h(w); }
int wk_client_w(struct win *w) { return w->w - 2 * BORDER; }
int wk_client_h(struct win *w) { return w->h - (wk_client_y(w) - w->y) - BORDER; }

void wk_size(int i, int *cw, int *ch) {
    struct win *w;
    if (!(w = win_get(i))) { *cw = 0; *ch = 0; return; }
    *cw = wk_client_w(w); *ch = wk_client_h(w);
}

static void z_unlink(struct win *w) {
    if (w->below) w->below->above = w->above; else if (zbot == w) zbot = w->above;
    if (w->above) w->above->below = w->below; else if (ztop == w) ztop = w->below;
    w->above = 0; w->below = 0;
}

void wk_raise(int i) {
    struct win *w;
    if (!(w = win_get(i))) return;
    if (ztop != w) {
        z_unlink(w);
        w->below = ztop;
        if (ztop) ztop->above = w; else zbot = w;
        ztop = w;
    }
    w->min = 0;
    wk_full = 1;
}

// The topmost window that is showing, or 0.
static struct win *focus() {
    struct win *w;
    w = ztop;
    while (w && w->min) w = w->below;
    return w;
}
int wk_focus() { struct win *f; f = focus(); return f ? f->id : 0; }

int wk_modal() {
    struct win *f;
    f = focus();
    return f && f->dialog ? f->id : 0;
}

// The windows closed since the last pass, freed.
static void sweep() {
    struct win *w, *p, *n;
    p = 0; w = first;
    while (w) {
        n = w->next;
        if (!w->used) {
            if (p) p->next = n; else first = n;
            wk_free(w->st); wk_free((char *)w);
        } else p = w;
        w = n;
    }
}

// Opens a window, or answers -1 when there is no memory for one.
int wk_open(struct wk_class *c, char *title, int w, int h, int flags, char *arg) {
    int slot, size;
    struct win *p, *q;
    if (!next_id) next_id = 1;
    if (!(p = (struct win *)wk_alloc(sizeof(struct win)))) return 0 - 1;
    size = c->size > 0 ? c->size : 16;
    if (!(p->st = wk_alloc(size))) { wk_free((char *)p); return 0 - 1; }
    // it cascades from the first place no open window holds
    slot = 0; q = first;
    while (q) { if (q->used && q->slot == slot) { ++slot; q = first; } else q = q->next; }
    p->slot = slot;
    p->id = next_id; ++next_id;
    if (!first) first = p;
    else { q = first; while (q->next) q = q->next; q->next = p; }
    p->cls = c; p->kind = c->kind;
    p->used = 1; p->resizable = !(flags & WK_FIXED); p->dialog = (flags & WK_DIALOG) != 0;
    p->owner = 0; p->action = 0;
    p->w = w; p->h = h;
    if (flags & WK_CENTER) { p->x = (wk.sw - w) / 2; p->y = (wk.sh - h) / 2 - 40; }
    else {
        p->x = wk.ax + 100 + (slot % 10) * 24 + (slot / 10) * 12; p->y = wk.ay + 20 + (slot % 10) * 22;
        if (p->x + w > wk.sw) p->x = wk.sw - w;
        if (p->x < 0) p->x = 0;
        if (p->y + h > wk.ay + wk.ah) p->y = wk.ay + wk.ah - h;
        if (p->y < 0) p->y = 0;
    }
    ui_ncpy(p->title, title, 48);
    wk_raise(p->id);
    if (c->open) c->open(p->id, arg);
    return p->id;
}

void wk_title(int i, char *s) {
    struct win *w;
    if (!(w = win_get(i))) return;
    ui_ncpy(w->title, s, 48);
    wk_full = 1;
}

void wk_menu(int i, struct wk_menu *m, int n) {
    struct win *w;
    if (!(w = win_get(i))) return;
    w->menus = m; w->nmenus = n;
}

static int drop_h(char **items);
static int drop_w(char **items);

// A pop-up menu at (x, y) in window I's client area, kept on the screen:
// drawn and chosen from as a drop-down is, the item chosen reaching the
// window's command hook as WK_CMD(WK_POPUP, item).
void wk_popup(int i, int x, int y, char **items) {
    struct win *w;
    int h;
    if (!(w = win_get(i)) || !items || !items[0]) return;
    pop_items = items;
    pop_x = wk_client_x(w) + x; pop_y = wk_client_y(w) + y;
    h = drop_h(items);
    if (pop_x + drop_w(items) > wk.sw) pop_x = wk.sw - drop_w(items);
    if (pop_y + h > wk.sh) pop_y = pop_y - h;
    if (pop_y < 0) pop_y = 0;
    if (pop_x < 0) pop_x = 0;
    menu_win = i; menu_idx = M_POPUP; menu_hot = 0 - 1;
    wk_full = 1;
}

void wk_place(int i, int x, int y, int ww, int hh) {
    struct win *w;
    if (!(w = win_get(i))) return;
    w->x = x; w->y = y; w->w = ww; w->h = hh;
    wk_full = 1;
}

void wk_close(int i) {
    struct win *w;
    if (!(w = win_get(i))) return;
    if (w->cls->destroy) w->cls->destroy(i);
    w->used = 0;
    z_unlink(w);
    if (drag == i) drag = 0;
    if (sizing == i) sizing = 0;
    if (menu_win == i) menu_win = 0;
    wk_full = 1;
}

void wk_ask_close(int i) {
    struct win *w;
    if (!(w = win_get(i))) return;
    if (w->dialog) { wk_dialog_answer(w, 0); return; }
    if (w->cls->close && !w->cls->close(i)) return;
    wk_close(i);
}

void wk_close_all() {
    struct win *w;
    w = first;
    while (w) { if (w->used) wk_close(w->id); w = w->next; }
    sweep();
}

// A window's own contents changed (or a part of them); nothing else did.
void wk_invalidate(int i, int x, int y, int ww, int hh) {
    struct win *w;
    if (!(w = win_get(i)) || w->min) return;
    if (ww <= 0) wk_dirty_rect(w->x, w->y, w->w, w->h);
    else wk_dirty_rect(wk_client_x(w) + x, wk_client_y(w) + y, ww, hh);
}

// ... and a part of them that its draw paints whole: a program's frame,
// which in a game is every frame. When that is all the damage at the
// next redraw (redraw_part), the window's own draw and the windows above
// it make the picture there: the desktop, the windows under it and its
// own frame are covered, and are not drawn. One part, the latest: two
// windows' frames make damage that is in neither, and all is drawn.
static int cover_win, cover_x, cover_y, cover_w, cover_h;
void wk_invalidate_covered(int i, int x, int y, int ww, int hh) {
    if (ww <= 0 || hh <= 0) { wk_invalidate(i, 0, 0, 0, 0); return; }
    cover_win = i; cover_x = x; cover_y = y; cover_w = ww; cover_h = hh;
    wk_invalidate(i, x, y, ww, hh);
}

// A dialog's answer: to the window that asked, raised first, or to the
// shell when no window did. An owner closed meanwhile hears nothing.
void wk_answer_owner(int owner, int dialog, int result) {
    struct win *o;
    if (owner <= 0) { if (shell && shell->answer) shell->answer(dialog, result); return; }
    if (!(o = win_get(owner))) return;
    wk_raise(owner);
    if (o->cls->answer) o->cls->answer(owner, dialog, result);
}

// ---- timers ---------------------------------------------------------------------

int wk_timer(int i, int id, int ms) {
    struct win *w;
    int k, f;
    if (!(w = win_get(i))) return 0;
    f = 0 - 1;
    k = 0;
    while (k < WK_TIMERS) {
        if (w->tms[k] && w->tid[k] == id) break;
        if (!w->tms[k] && f < 0) f = k;
        ++k;
    }
    if (k == WK_TIMERS) { if (!ms) return 1; if (f < 0) return 0; k = f; }
    w->tid[k] = id; w->tms[k] = ms > 0 ? ms : 0;
    w->tnext[k] = wk_now() + ms;
    return 1;
}

static void timers() {
    struct win *w;
    int k, now;
    now = wk_now();
    w = first;
    while (w) {
        k = 0;
        while (w->used && k < WK_TIMERS) {
            if (w->tms[k] && now - w->tnext[k] >= 0) {
                w->tnext[k] = w->tnext[k] + w->tms[k];
                if (now - w->tnext[k] >= 0) w->tnext[k] = now + w->tms[k];   // fallen behind
                if (w->cls->timer) w->cls->timer(w->id, w->tid[k]);
            }
            ++k;
        }
        w = w->next;
    }
}

int wk_next_timer() {
    struct win *w;
    int k, d, best, now;
    now = wk_now();
    best = 0 - 1;
    w = first;
    while (w) {
        k = 0;
        while (w->used && k < WK_TIMERS) {
            if (w->tms[k]) {
                d = w->tnext[k] - now;
                if (d < 0) d = 0;
                if (best < 0 || d < best) best = d;
            }
            ++k;
        }
        w = w->next;
    }
    if (rep_win) {
        d = rep_next - now;
        if (d < 0) d = 0;
        if (best < 0 || d < best) best = d;
    }
    return best;
}

// ---- the clipboard ----------------------------------------------------------------

int wk_clip_set(char *s, int n) {
    char *t;
    if (n < 0) n = 0;
    if (!(t = wk_alloc(n + 1))) return 0;
    memcpy(t, s, n);
    t[n] = 0;
    if (clip_text) wk_free(clip_text);
    clip_text = t; clip_n = n;
    return 1;
}
char *wk_clip_get(int *n) { *n = clip_text ? clip_n : 0; return clip_text ? clip_text : ""; }

// ---- menus ------------------------------------------------------------------------

static char *sys_items[6] = { "Restore", "Minimize", "Maximize", "-", "Close", 0 };
static char *sys_dlg_items[2] = { "Close", 0 };
enum { SYS_RESTORE = 0, SYS_MIN = 1, SYS_MAX = 2, SYS_CLOSE = 4 };

int wk_menu_w(struct win *w, int k) { return ui_len(w->menus[k].title) * 7 + 12; }
int wk_menu_x(struct win *w, int k) {
    int x, j;
    x = wk_client_x(w) + 4;
    j = 0;
    while (j < k) { x = x + wk_menu_w(w, j); ++j; }
    return x;
}

static int count_items(char **items) { int n; n = 0; while (items[n]) ++n; return n; }

static char **drop_items(struct win *w) {
    if (menu_idx == M_POPUP) return pop_items;
    if (menu_idx < 0) return w->dialog ? sys_dlg_items : sys_items;
    return w->menus[menu_idx].items;
}
static int drop_h(char **items) {
    int k, mh;
    mh = 6;
    k = 0; while (items[k]) { if (items[k][0] == '-') mh = mh + 8; else mh = mh + 20; ++k; }
    return mh;
}
// A column's width: DROP_W, or the widest item's (text widths are guesses,
// six pixels a letter, as elsewhere), the check mark's room and a margin
static int drop_w(char **items) {
    int k, n, w;
    w = DROP_W;
    k = 0;
    while (items[k]) {
        n = ui_len(items[k]);
        if (items[k][0] == WK_CHECKED) --n;
        if (n * 6 + 34 > w) w = n * 6 + 34;
        ++k;
    }
    return w > wk.sw ? wk.sw : w;
}
// A drop-down taller than the screen below its top breaks into columns, as
// 3.1's long menus did: item k's column and its top, from the drop-down's
// top y; *cols, the columns, and *tall, the tallest one's height
static int drop_lay(char **items, int y, int k, int *iy, int *cols, int *tall) {
    int i, c, cy, h, limit, at;
    limit = wk.sh - y - 3;
    if (limit < 40) limit = 40;
    c = 0; cy = 3; *tall = 6; at = 0;
    i = 0;
    while (items[i]) {
        h = items[i][0] == '-' ? 8 : 20;
        if (cy + h > limit && cy > 3) { c = c + 1; cy = 3; }
        if (i == k) { at = c; *iy = y + cy; }
        cy = cy + h;
        if (cy + 3 > *tall) *tall = cy + 3;
        ++i;
    }
    *cols = c + 1;
    return at;
}
// A minimised window's control menu opens over its icon.
static int drop_y(struct win *w);
static int drop_x(struct win *w) {
    int x, y, k, cw;
    if (menu_idx == M_POPUP) return pop_x;
    if (menu_idx < 0 && w->min && wk_icons_on) {
        wk_icon_xy(w, &x, &y);
        return x + DROP_W > wk.sw ? wk.sw - DROP_W : x;
    }
    if (menu_idx < 0) return w->x + BORDER;
    // a menu bar's: kept on the screen, its columns and all
    x = wk_menu_x(w, menu_idx);
    drop_lay(drop_items(w), drop_y(w), 0 - 1, &y, &k, &cw);
    cw = drop_w(drop_items(w)) * k;
    if (x + cw > wk.sw) x = wk.sw - cw;
    return x < 0 ? 0 : x;
}
static int drop_y(struct win *w) {
    int x, y;
    if (menu_idx == M_POPUP) return pop_y;
    if (menu_idx < 0 && w->min && wk_icons_on) {
        wk_icon_xy(w, &x, &y);
        y = y - drop_h(drop_items(w));
        return y < 0 ? 0 : y;
    }
    return menu_idx < 0 ? w->y + BORDER + TITLE_H + 1 : w->y + BORDER + TITLE_H + 1 + MENU_H;
}

// the check mark left of a WK_CHECKED item
static void check_mark(int x, int y, int rgb) {
    int k;
    k = 0;
    while (k < 7) { gui_rect(x + k, y + (k < 2 ? 3 + k : 7 - k), 2, 2, rgb); ++k; }
}

static void draw_dropdown() {
    struct win *w;
    char **items;
    char *s;
    int n, x, y, k, iy, mh, dw, cols, cx;
    if (!(w = win_get(menu_win))) return;
    items = drop_items(w);
    n = count_items(items);
    x = drop_x(w); y = drop_y(w);
    dw = drop_w(items);
    drop_lay(items, y, 0 - 1, &iy, &cols, &mh);
    gui_rect(x, y, dw * cols, mh, C_FACE);
    d_bevel(x, y, dw * cols, mh, B_RAISED);
    k = 0;
    while (k < n) {
        cx = x + drop_lay(items, y, k, &iy, &cols, &mh) * dw;
        if (items[k][0] == '-') { gui_rect(cx + 3, iy + 3, dw - 6, 1, C_SHADOW); gui_rect(cx + 3, iy + 4, dw - 6, 1, C_LIGHT); }
        else {
            if (k == menu_hot) gui_rect(cx + 3, iy, dw - 6, 20, C_SEL);
            s = items[k];
            if (s[0] == WK_CHECKED) { check_mark(cx + 7, iy + 5, k == menu_hot ? C_WHITE : C_DARK); ++s; }
            d_text(cx + 20, iy + 4, k == menu_hot ? C_WHITE : C_DARK, F_SANS, s);
        }
        ++k;
    }
}

// Which item of the open drop-down is at (x, y), or -1.
static int dropdown_hit(int px, int py) {
    struct win *w;
    char **items;
    int n, x, y, k, iy, dw, cx, cols, mh;
    if (!(w = win_get(menu_win))) return 0 - 1;
    items = drop_items(w);
    n = count_items(items);
    x = drop_x(w); y = drop_y(w);
    dw = drop_w(items);
    k = 0;
    while (k < n) {
        cx = x + drop_lay(items, y, k, &iy, &cols, &mh) * dw;
        if (items[k][0] != '-' && px >= cx && px < cx + dw && py >= iy && py < iy + 20) return k;
        ++k;
    }
    return 0 - 1;
}

static void toggle_max(struct win *w) {
    if (!w->max) {
        w->rx = w->x; w->ry = w->y; w->rw = w->w; w->rh = w->h;
        w->x = wk.ax; w->y = wk.ay; w->w = wk.aw; w->h = wk.ah; w->max = 1;
    } else {
        w->x = w->rx; w->y = w->ry; w->w = w->rw; w->h = w->rh; w->max = 0;
    }
    wk_full = 1;
}

static void minimise(struct win *w) {
    w->min = 1;
    if (wk_icons_on) { wk_icon_place(w); wk_icon_sel = w->id; }
    wk_full = 1;
}
void wk_minimize(int i) { struct win *w; if ((w = win_get(i)) && !w->dialog) minimise(w); }

// (a minimised window's menu is its icon's: Restore brings it back as it
// was, maximised or not, and Maximize brings it back maximised)
static void sys_command(struct win *w, int k) {
    if (w->dialog || k == SYS_CLOSE) { wk_ask_close(w->id); return; }
    if (w->min && k == SYS_RESTORE) { wk_raise(w->id); return; }
    if (w->min && k == SYS_MAX) wk_raise(w->id);
    if (k == SYS_RESTORE && w->max) toggle_max(w);
    else if (k == SYS_MAX && !w->max) toggle_max(w);
    else if (k == SYS_MIN && !w->min) minimise(w);
}

// ---- drawing the scene --------------------------------------------------------------

struct wk_look *wk_look() {
    if (wk.style == S_WIN31) return &look_win31;
    if (wk.style == S_CLASSIC) return &look_classic;
    return &look_flat;
}

static void draw_window(struct win *w, int focused) {
    struct wk_look *l;
    int cx, cy, cw, ch;
    l = wk_look();
    l->frame(w, focused);
    if (w->nmenus) l->menubar(w, focused, menu_win == w->id ? menu_idx : 0 - 1, menu_hot);
    cx = wk_client_x(w); cy = wk_client_y(w); cw = wk_client_w(w); ch = wk_client_h(w);
    wk_client_clip(cx, cy, cw, ch);
    wk_origin(cx, cy);
    if (w->cls->draw) w->cls->draw(w->id, cw, ch, focused);
    wk_origin(0, 0);
    wk_noclip();
    if (l->grip) l->grip(w);
}

// The windows that reach into the damage, back to front, from w up
static void draw_windows_from(struct win *w) {
    struct win *f;
    f = focus();
    while (w) {
        if (!w->min && wk_in_damage(w->x, w->y, w->w, w->h)) draw_window(w, w == f);
        w = w->above;
    }
}
static void draw_windows() { draw_windows_from(zbot); }

// The window whose covered part (wk_invalidate_covered) holds all the
// damage, inside its client area as it is now; or 0
static struct win *covering() {
    struct win *w;
    int x0, y0, x1, y1, cx, cy;
    if (!cover_win || !(w = win_get(cover_win)) || w->min || !w->cls->draw) return 0;
    cx = wk_client_x(w); cy = wk_client_y(w);
    x0 = cx + cover_x; y0 = cy + cover_y;
    x1 = x0 + cover_w; y1 = y0 + cover_h;
    if (x0 < cx) x0 = cx;
    if (y0 < cy) y0 = cy;
    if (x1 > cx + wk_client_w(w)) x1 = cx + wk_client_w(w);
    if (y1 > cy + wk_client_h(w)) y1 = cy + wk_client_h(w);
    if (wk_dmg_x0 < x0 || wk_dmg_y0 < y0 || wk_dmg_x1 > x1 || wk_dmg_y1 > y1) return 0;
    return w;
}

// Its client area alone (and the size grip over its corner)
static void draw_client(struct win *w, int focused) {
    struct wk_look *l;
    int cx, cy, cw, ch;
    l = wk_look();
    cx = wk_client_x(w); cy = wk_client_y(w); cw = wk_client_w(w); ch = wk_client_h(w);
    wk_client_clip(cx, cy, cw, ch);
    wk_origin(cx, cy);
    w->cls->draw(w->id, cw, ch, focused);
    wk_origin(0, 0);
    wk_noclip();
    if (l->grip) l->grip(w);
}

static void redraw() {
    wk_part = 0;
    wk_origin(0, 0);
    gui_clear(C_DESK);
    if (shell && shell->desktop) shell->desktop(0, 0, wk.sw, wk.sh);
    wk_icons_draw();
    draw_windows();
    if (menu_win) draw_dropdown();
    if (shell && shell->front) shell->front();
    gui_show();
    wk_full = 0;
    wk_dmg = 0;
    cover_win = 0;
}

// Only the damage: the desktop under it, the windows that reach into it,
// back to front, and what the shell has over them. A menu open is drawn
// over everything, so that is still the whole scene.
static void redraw_part() {
    struct win *c;
    if (menu_win || (shell && shell->popup && shell->popup())) { redraw(); return; }
    wk_part = 1;
    wk_origin(0, 0);
    wk_noclip();
    // a program's frame, and nothing else: that window's picture, and
    // whatever is over it
    if ((c = covering())) {
        draw_client(c, c == focus());
        draw_windows_from(c->above);
    } else {
        if (shell && shell->desktop) shell->desktop(wk_dmg_x0, wk_dmg_y0, wk_dmg_x1 - wk_dmg_x0, wk_dmg_y1 - wk_dmg_y0);
        else gui_rect(wk_dmg_x0, wk_dmg_y0, wk_dmg_x1 - wk_dmg_x0, wk_dmg_y1 - wk_dmg_y0, C_DESK);
        wk_icons_draw();
        draw_windows();
    }
    if (shell && shell->front) shell->front();
    gui_noclip();
    gui_show();
    wk_part = 0;
    wk_dmg = 0;
    cover_win = 0;
}

int wk_dirty() { return wk_full || wk_dmg; }

int wk_redraw(int force) {
    if (force || wk_full) { redraw(); return 1; }
    if (wk_dmg) { redraw_part(); return 1; }
    return 0;
}

void wk_drawn() {
    struct win *w;
    w = first;
    while (w) { if (w->used && w->cls->drawn) w->cls->drawn(w->id); w = w->next; }
}

// ---- the screen's size -----------------------------------------------------------------
//
// The display's size is the kit's to ask for (gui_size) and the page's to
// give: the RESIZE that comes back, or one the page sends of its own, is
// when the windows are laid out again. Maximised windows fill the new
// area; the rest are pulled back inside it.

void wk_set_area(int x, int y, int w, int h) { wk.ax = x; wk.ay = y; wk.aw = w; wk.ah = h; }

static void relayout(int sw, int sh) {
    struct win *w;
    if (sw < 320) sw = 320;
    if (sh < 240) sh = 240;
    if (sw > WK_MAX_W) sw = WK_MAX_W;
    if (sh > WK_MAX_H) sh = WK_MAX_H;
    wk.sw = sw; wk.sh = sh;
    wk_set_area(0, 0, sw, sh);
    if (shell && shell->resized) shell->resized();
    w = first;
    while (w) {
        if (w->used && w->max) { w->x = wk.ax; w->y = wk.ay; w->w = wk.aw; w->h = wk.ah; }
        else if (w->used) {
            if (w->x + w->w > wk.ax + wk.aw) w->x = wk.ax + wk.aw - w->w;
            if (w->y + w->h > wk.ay + wk.ah) w->y = wk.ay + wk.ah - w->h;
            if (w->x < wk.ax) w->x = wk.ax;
            if (w->y < wk.ay) w->y = wk.ay;
            // too big for it now: as big as fits, if it can be sized
            if (w->resizable && w->w > wk.aw) w->w = wk.aw > MIN_W ? wk.aw : MIN_W;
            if (w->resizable && w->h > wk.ah) w->h = wk.ah > MIN_H ? wk.ah : MIN_H;
        }
        w = w->next;
    }
    menu_win = 0; drag = 0; sizing = 0;
    wk_full = 1;
}

void wk_screen(int w, int h) {
    gui_size(w, h);
    relayout(w, h);
}

void wk_init(struct wk_shell *s) {
    shell = s;
    if (!next_id) next_id = 1;
    wk.sw = gui_width(); wk.sh = gui_height();
    if (wk.sw <= 0) wk.sw = 640;
    if (wk.sh <= 0) wk.sh = 480;
    wk_set_area(0, 0, wk.sw, wk.sh);
    if (shell && shell->resized) shell->resized();
    ptr_shape = PTR_ARROW;
    wk_full = 1;
}

// ---- input ------------------------------------------------------------------------------

static void client_mouse(struct win *w, int ev, int x, int y, int b) {
    if (w->cls->mouse) w->cls->mouse(w->id, ev, x - wk_client_x(w), y - wk_client_y(w), b);
}

static void mouse_down(int x, int y, int button) {
    int k, i, t, m, ht;
    struct win *w;
    if (menu_win) {
        w = win_get(menu_win);
        k = dropdown_hit(x, y);
        i = menu_idx;
        menu_win = 0; wk_full = 1;
        if (!w) return;
        if (k >= 0) {
            if (i == M_POPUP) { if (w->cls->command) w->cls->command(w->id, WK_CMD(WK_POPUP, k)); }
            else if (i < 0) sys_command(w, k);
            else if (w->cls->command) w->cls->command(w->id, WK_CMD(i, k));
            return;
        }
        // the icon whose menu this is, clicked again soon after: a double click restores it
        if (i < 0 && w->min && wk_icon_hit(x, y) == w) {
            if (down_win == w->id && wk_now() - down_t < 500) { down_win = 0; wk_raise(w->id); }
            return;
        }
        // a click on another title of the same bar opens that one instead
        if (i >= 0 && y >= w->y + BORDER + TITLE_H + 1 && y < w->y + BORDER + TITLE_H + 1 + MENU_H) {
            m = 0;
            while (m < w->nmenus) {
                if (m != i && x >= wk_menu_x(w, m) && x < wk_menu_x(w, m) + wk_menu_w(w, m)) {
                    menu_win = w->id; menu_idx = m; menu_hot = 0 - 1; return;
                }
                ++m;
            }
        }
        return;
    }
    if (shell && shell->mouse_front && shell->mouse_front(E_DOWN, x, y, button)) return;
    // windows, topmost first; a dialog keeps the input to itself
    w = ztop;
    while (w) {
        i = w->id;
        if (!w->min && ui_hit(x, y, w->x, w->y, w->w, w->h)) {
            if (wk_modal() && wk_modal() != i) return;
            wk_raise(i);
            ht = wk_look()->hit(w, x, y);
            t = wk_now();
            if (ht == HT_CLOSE) { wk_ask_close(i); return; }
            if (ht == HT_MAX) { toggle_max(w); return; }
            if (ht == HT_MIN) { minimise(w); return; }
            if (ht == HT_SYSMENU) {
                // the control-menu box: a double click closes, a click opens its menu
                if (down_win == i && t - down_t < 500) { down_win = 0; wk_ask_close(i); return; }
                down_win = i; down_t = t;
                menu_win = i; menu_idx = 0 - 1; menu_hot = 0 - 1;
                return;
            }
            if (ht == HT_CAPTION) {
                if (!w->dialog && down_win == i && t - down_t < 500) { toggle_max(w); down_win = 0; return; }
                down_win = i; down_t = t;
                if (!w->max) { drag = i; drag_dx = x - w->x; drag_dy = y - w->y; }
                return;
            }
            if (ht >= HT_SIZE) {
                sizing = i; size_edges = ht - HT_SIZE;
                size_w0 = w->w; size_h0 = w->h; size_x0 = x; size_y0 = y; size_wx = w->x; size_wy = w->y;
                return;
            }
            if (ht == HT_MENUBAR) {
                m = 0;
                while (m < w->nmenus) {
                    if (x >= wk_menu_x(w, m) && x < wk_menu_x(w, m) + wk_menu_w(w, m)) {
                        menu_win = i; menu_idx = m; menu_hot = 0 - 1; wk_full = 1; return;
                    }
                    ++m;
                }
                return;
            }
            if (ht == HT_CLIENT) {
                ui_scroll_end();
                client_mouse(w, E_DOWN, x, y, button);
                // another button (a right click, which may open a pop-up):
                // never half of a double click
                if (button) { down_win = 0; wk_full = 1; return; }
                if (ui_scroll_repeat()) { rep_win = i; rep_x = x; rep_y = y; rep_b = button; rep_next = wk_now() + REP_WAIT; }
                if (w->used && down_win == i && t - down_t < 500 && x - down_x < 5 && down_x - x < 5 && y - down_y < 5 && down_y - y < 5) {
                    client_mouse(w, E_DBL, x, y, button);
                    down_win = 0;
                } else { down_win = i; down_t = t; down_x = x; down_y = y; }
                wk_full = 1;
            }
            return;
        }
        w = w->below;
    }
    if (wk_modal()) return;
    // an icon (wk_min_icons): a click opens its window's control menu over
    // it, a double click restores the window
    if ((w = wk_icon_hit(x, y))) {
        t = wk_now();
        wk_icon_sel = w->id;
        wk_full = 1;
        if (down_win == w->id && t - down_t < 500) { down_win = 0; wk_raise(w->id); return; }
        down_win = w->id; down_t = t;
        menu_win = w->id; menu_idx = 0 - 1; menu_hot = 0 - 1;
        return;
    }
    if (shell && shell->mouse_desk) shell->mouse_desk(E_DOWN, x, y, button);
}

// ---- the pointer: the host's own, its shape chosen by what is under it ----
static int shape_at(int x, int y) {
    struct win *w;
    int cx, cy, s, ht;
    if (sizing) return PTR_RESIZE;
    if (drag || menu_win) return PTR_ARROW;
    if (shell && shell->pointer && (s = shell->pointer(x, y)) >= 0) return s;
    w = ztop;
    while (w) {
        if (!w->min && ui_hit(x, y, w->x, w->y, w->w, w->h)) {
            ht = wk_look()->hit(w, x, y);
            if (ht >= HT_SIZE) return PTR_RESIZE;
            if (ht != HT_CLIENT) return PTR_ARROW;
            cx = x - wk_client_x(w); cy = y - wk_client_y(w);
            if (w->cls->pointer) return w->cls->pointer(w->id, cx, cy);
            return w->cls->pointer_shape;
        }
        w = w->below;
    }
    return PTR_ARROW;
}
void wk_repoint() { ptr_shape = PTR_ARROW; }
// a drop-down menu is open (keys are its, not a window's: grin's game window)
int wk_menu_open() { return menu_win != 0; }

static void pointer(int x, int y) {
    int s;
    s = shape_at(x, y);
    if (s != ptr_shape) { ptr_shape = s; gui_cursor(s); }
}

static void mouse_move(int x, int y, int b) {
    struct win *w;
    int k, dx, dy;
    pointer(x, y);
    if (drag && (w = win_get(drag))) {
        w->x = x - drag_dx; w->y = y - drag_dy;
        if (w->y < wk.ay) w->y = wk.ay;
        if (w->y > wk.ay + wk.ah - TITLE_H) w->y = wk.ay + wk.ah - TITLE_H;
        if (w->x < 60 - w->w) w->x = 60 - w->w;
        if (w->x > wk.sw - 60) w->x = wk.sw - 60;
        wk_full = 1;
        return;
    }
    if (sizing && (w = win_get(sizing))) {
        dx = x - size_x0; dy = y - size_y0;
        if (size_edges & SZ_R) w->w = size_w0 + dx;
        if (size_edges & SZ_B) w->h = size_h0 + dy;
        if (size_edges & SZ_L) w->w = size_w0 - dx;
        if (size_edges & SZ_T) w->h = size_h0 - dy;
        if (w->w < MIN_W) w->w = MIN_W;
        if (w->h < MIN_H) w->h = MIN_H;
        if (size_edges & SZ_L) w->x = size_wx + size_w0 - w->w;
        if (size_edges & SZ_T) w->y = size_wy + size_h0 - w->h;
        wk_full = 1;
        return;
    }
    if (shell && shell->mouse_front && shell->mouse_front(E_MOVE, x, y, b)) return;
    if (menu_win) { k = dropdown_hit(x, y); if (k != menu_hot) { menu_hot = k; wk_full = 1; } return; }
    if ((w = focus())) {
        // a thumb being dragged follows the pointer out of the window too
        if (ui_scroll_active() || ui_hit(x, y, wk_client_x(w), wk_client_y(w), wk_client_w(w), wk_client_h(w))) {
            client_mouse(w, E_MOVE, x, y, b);
            if (ui_scroll_active()) wk_full = 1;          // the thumb moved: draw it there
        }
    }
}

static void mouse_up(int x, int y, int b) {
    struct win *w;
    drag = 0; sizing = 0; rep_win = 0;
    ui_scroll_end();
    pointer(x, y);
    if ((w = focus())) client_mouse(w, E_UP, x, y, b);
}

static void wheel(int x, int y, int dy) {
    struct win *w;
    w = ztop;
    while (w) {
        if (!w->min && ui_hit(x, y, wk_client_x(w), wk_client_y(w), wk_client_w(w), wk_client_h(w))) {
            client_mouse(w, E_WHEEL, x, y, dy);
            wk_full = 1;
            return;
        }
        w = w->below;
    }
}

static void key_down(int code, int ch, int mods) {
    struct win *f;
    // typing between two clicks makes them two clicks, not a double click
    down_win = 0;
    if (shell && shell->key && shell->key(1, code, ch, mods)) return;
    if (menu_win && code == KEY_ESC) { menu_win = 0; wk_full = 1; return; }
    if (!(f = focus())) return;
    if (f->cls->key) f->cls->key(f->id, 1, code, ch, mods);
    else if (code == KEY_ENTER || code == KEY_ESC) wk_ask_close(f->id);   // About and the like
    wk_full = 1;
}

// A key let go matters only to a canvas: a game holds keys down.
static void key_up(int code, int ch, int mods) {
    struct win *f;
    if (!(f = focus())) return;
    if (f->cls->key) f->cls->key(f->id, 0, code, ch, mods);
}

void wk_event(int *ev) {
    int t;
    t = ev[0];
    if (t == GUI_EV_DOWN) mouse_down(ev[1], ev[2], ev[3]);
    else if (t == GUI_EV_UP) mouse_up(ev[1], ev[2], ev[3]);
    else if (t == GUI_EV_MOVE) mouse_move(ev[1], ev[2], ev[3]);
    else if (t == GUI_EV_KEYDOWN) { wk.mods = ev[3]; key_down(ev[1], ev[2], ev[3]); }
    else if (t == GUI_EV_KEYUP) { wk.mods = ev[3]; key_up(ev[1], ev[2], ev[3]); }
    else if (t == GUI_EV_WHEEL) wheel(ev[1], ev[2], ev[3]);
    else if (t == GUI_EV_RESIZE) {
        if (ev[1] > 0 && ev[2] > 0 && (ev[1] != wk.sw || ev[2] != wk.sh)) relayout(ev[1], ev[2]);
        wk_full = 1;
    } else if (t == GUI_EV_FOCUS) {
        if (!ev[1]) wk.mods = 0;            // let go of elsewhere
        wk_full = 1;
    }
}

// Every pass of the shell's loop: the windows closed since the last one
// freed, each window's idle hook, and the timers due.
void wk_tick() {
    struct win *w;
    sweep();
    w = first;
    while (w) { if (w->used && w->cls->idle) w->cls->idle(w->id); w = w->next; }
    timers();
    // a scroll bar's arrow or track held: pressed again, as long as it
    // still says it repeats (the thumb may have come under the pointer)
    if (rep_win && wk_now() - rep_next >= 0) {
        if ((w = win_get(rep_win)) && w->used && !w->min) {
            ui_scroll_end();
            client_mouse(w, E_DOWN, rep_x, rep_y, rep_b);
            if (!ui_scroll_repeat()) rep_win = 0;
            rep_next = wk_now() + REP_MS;
            wk_invalidate(w->id, 0, 0, 0, 0);
        } else rep_win = 0;
    }
}
