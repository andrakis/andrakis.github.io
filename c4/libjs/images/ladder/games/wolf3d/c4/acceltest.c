// acceltest.c -- c4sdl: Wolfenstein 3D's accelerators (c4/accel.mjs)
// against the loops they stand for, each as wl_draw.c, wl_scale.c, id_vl.c,
// c4sdl.c and wl_utils.c have them: the same pixels, on made-up textures,
// sprites, heights and scales, the same checksums, the same FixedMul.
// test-wolf3d runs it on c4's libjs.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "c4accel.h"

int wolf_accel = -1;
int wolf_accel_on = 1;
int wolf_accel_base(void) { return wolf_accel = accel_find("wolf3d"); }

unsigned seed = 12345;
int rnd(int n) { seed = seed * 1103515245 + 12345; return (int)((seed >> 8) % (unsigned)n); }

enum { W = 320, H = 160, BUFN = W * H, TS = 64 };
unsigned char *tex, *bufc, *bufa, *base;
uint32_t ylookup[H * 4];
int fails, cases;

void fill(unsigned char *p, int n) { int i; for (i = 0; i < n; i++) p[i] = rnd(256); }
void check(char *what, int k) {
    cases++;
    if (memcmp(bufc, bufa, BUFN) != 0) {
        fails++;
        if (fails < 10) printf("accel: %s, case %d, differs\n", what, k);
    }
}
void clear() { base[rnd(BUFN)] = rnd(256); memcpy(bufc, base, BUFN); memcpy(bufa, base, BUFN); }

// wl_draw.c's ScalePost, its globals as arguments
void postc(int wh, unsigned char *vbuf, int pitch, int postx, int centery, int viewheight, unsigned char *postsource) {
    int ywcount, yoffs, yw, yd, yendoffs;
    unsigned char col;
    ywcount = yd = wh >> 3;
    if(yd <= 0) yd = 100;
    yoffs = (centery - ywcount) * pitch;
    if(yoffs < 0) yoffs = 0;
    yoffs += postx;
    yendoffs = centery + ywcount - 1;
    yw=TS-1;
    while(yendoffs >= viewheight) {
        ywcount -= TS/2;
        while(ywcount <= 0) { ywcount += yd; yw--; }
        yendoffs--;
    }
    if(yw < 0) return;
    col = postsource[yw];
    yendoffs = yendoffs * pitch + postx;
    {
        unsigned char *dest = vbuf + yendoffs, *top = vbuf + yoffs, *src = postsource;
        while(dest >= top) {
            *dest = col;
            ywcount -= TS/2;
            if(ywcount <= 0) {
                do { ywcount += yd; yw--; } while(ywcount <= 0);
                if(yw < 0) break;
                col = src[yw];
            }
            dest -= pitch;
        }
    }
}
void test_post() {
    int k, wh, postx, vh, cy;
    for (k = 0; k < 1500; k++) {
        clear();
        vh = 2 * (20 + rnd(H / 2 - 20)); cy = vh / 2; postx = rnd(W);
        switch (k % 4) {
        case 0: wh = rnd(8 * vh); break;                 // within the view
        case 1: wh = 8 * vh + rnd(64 * vh); break;       // taller than it
        case 2: wh = rnd(16) - 8; break;                 // nothing, or below 0
        default: wh = rnd(32767); break;
        }
        {
            unsigned char *s = tex + rnd(4096);
            postc((int16_t)wh, bufc, W, postx, cy, vh, s);
            wolf_post((int16_t)wh, bufa, W, postx, cy, vh, s, TS);
        }
        check("post", k);
    }
}

// wl_scale.c's ScaleLine, a made-up compiled sprite's column: segments
// of (end * 2, top, start * 2), ending in 0
unsigned short rs(unsigned char *p) { return p[0] | (p[1] << 8); }
void linec(int x, int toppix, int fracstep, unsigned char *linesrc, unsigned char *linecmds, int vh) {
    unsigned char *src, *dest, col;
    int start, end, top, startpix, endpix, frac;
    for (end = rs(linecmds) >> 1; end; end = rs(linecmds) >> 1) {
        top = (int16_t) rs(linecmds + 2);
        start = rs(linecmds + 4) >> 1;
        frac = start * fracstep;
        endpix = (frac >> 16) + toppix;
        for (src = &linesrc[top + start]; start != end; start++, src++) {
            startpix = endpix;
            if (startpix >= vh) break;
            frac += fracstep;
            endpix = (frac >> 16) + toppix;
            if (endpix < 0) continue;
            if (startpix < 0) startpix = 0;
            if (endpix > vh) endpix = vh;
            col = *src;
            dest = bufc + ylookup[startpix] + x;
            while (startpix < endpix) { *dest = col; dest += W; startpix++; }
        }
        linecmds += 6;
    }
}
unsigned char cmds[6 * 16];
void put16(unsigned char *p, int v) { p[0] = v & 255; p[1] = (v >> 8) & 255; }
void test_line() {
    int k, n, i, s, e, x, toppix, step, vh;
    for (k = 0; k < 1500; k++) {
        clear();
        n = rnd(6); s = rnd(8);
        for (i = 0; i < n; i++) {
            e = s + 1 + rnd(12); if (e > 64) e = 64;
            put16(cmds + 6 * i, 2 * e); put16(cmds + 6 * i + 2, rnd(2000) - 1000); put16(cmds + 6 * i + 4, 2 * s);
            s = e + rnd(4); if (s >= 63) { n = i + 1; break; }
        }
        put16(cmds + 6 * n, 0);
        vh = 40 + rnd(H - 40); x = rnd(W);
        toppix = rnd(3 * vh) - vh; step = 1 + rnd(1 << 19);
        linec(x, toppix, step, tex + 2000, cmds, vh);
        wolf_line(x, toppix, step, tex + 2000, cmds, bufa, ylookup, W, vh);
        check("line", k);
    }
}

// c4sdl.c's checksum
unsigned char pal[1024];
void test_sum() {
    int k, x, y, w, h, pitch;
    unsigned sum, c, a;
    unsigned *words;
    for (k = 0; k < 60; k++) {
        fill(bufc, BUFN); fill(pal, 1024);
        w = 4 * (1 + rnd(W / 4)); pitch = W; h = 1 + rnd(H);
        if (k & 1) { w = W; h = H - 1; }
        sum = (unsigned)rnd(1 << 30) * 4;
        c = sum;
        for (y = 0; y < h; y++) {
            words = (unsigned *)(bufc + y * pitch);
            for (x = 0; x < w / 4; x++) c = (c * 31 + words[x]) & 0xFFFFFFFF;
        }
        for (x = 0; x < 256; x++) c = (c * 31 + pal[4 * x] * 65536 + pal[4 * x + 1] * 256 + pal[4 * x + 2]) & 0xFFFFFFFF;
        a = (unsigned)wolf_sum(sum, bufc, w, h, pitch, pal);
        cases++;
        if (a != c) { fails++; if (fails < 10) printf("accel: sum, case %d, %08x, not %08x\n", k, a, c); }
    }
}

// id_vl.c's scaled blits
void blitc(unsigned char *source, int ow, int srcx, int srcy, int width, int height, int destx, int desty, int sc) {
    int i, j, sci, scj, m, n;
    for (j = 0, scj = 0; j < height; j++, scj += sc)
        for (i = 0, sci = 0; i < width; i++, sci += sc) {
            unsigned char col = source[((j + srcy) * ow) + (i + srcx)];
            for (m = 0; m < sc; m++)
                for (n = 0; n < sc; n++)
                    bufc[ylookup[scj + m + desty] + sci + n + destx] = col;
        }
}
void test_blit() {
    int k, ow, oh, srcx, srcy, w, h, sc, dx, dy;
    for (k = 0; k < 400; k++) {
        clear();
        sc = 1 + rnd(3);
        ow = 1 + rnd(80); oh = 1 + rnd(40);
        srcx = rnd(ow); srcy = rnd(oh); w = 1 + rnd(ow - srcx); h = 1 + rnd(oh - srcy);
        if (k & 1) { srcx = srcy = 0; w = ow; h = oh; }
        dx = rnd(W - w * sc + 1); dy = rnd(H - h * sc + 1);
        blitc(tex + 3000, ow, srcx, srcy, w, h, dx, dy, sc);
        wolf_blit(tex + 3000, ow, srcx, srcy, w, h, bufa, ylookup, dx, dy, sc);
        check("blit", k);
    }
}

// wl_utils.c's FixedMul, and the 64-bit arithmetic it stands for
int fixmulc(int a, int b) {
    uint32_t ah = (uint32_t)(a >> 16), al = (uint32_t)a & 0xffff;
    uint32_t bh = (uint32_t)(b >> 16), bl = (uint32_t)b & 0xffff;
    return (int)(((ah * bh) << 16) + ah * bl + al * bh + ((al * bl + 0x8000) >> 16));
}
int pick(int k) {
    switch (rnd(6)) {
    case 0: return rnd(65536) - 32768;
    case 1: return (int)((unsigned)rnd(1 << 30) * 4 + rnd(4));
    case 2: return k & 1 ? 0x7fffffff : (int)0x80000000;
    case 3: return rnd(1 << 24) - (1 << 23);
    case 4: return rnd(3) - 1;
    }
    return rnd(1 << 30) - (1 << 29);
}
void test_math() {
    int k, a, b, r, w;
    for (k = 0; k < 4000; k++) {
        a = pick(k); b = pick(k + 1);
        r = wolf_fixmul(a, b); w = fixmulc(a, b);
        cases++;
        if (r != w) { fails++; if (fails < 10) printf("accel: fixmul %d %d: %d, not %d\n", a, b, r, w); }
        w = (int)((((int64_t)a * (int64_t)b + 0x8000) >> 16) & 0xffffffff);
        cases++;
        if (r != w) { fails++; if (fails < 10) printf("accel: fixmul (64-bit) %d %d: %d, not %d\n", a, b, r, w); }
    }
}

int main() {
    int i;
    if (WOLF_ACCEL() <= 0) { printf("accel: Wolf3D's are not here\n"); return 0; }
    tex = malloc(8192); bufc = malloc(BUFN); bufa = malloc(BUFN); base = malloc(BUFN);
    fill(tex, 8192); fill(base, BUFN);
    for (i = 0; i < H * 4; i++) ylookup[i] = i < H ? i * W : 0;
    test_post(); test_line(); test_sum(); test_blit(); test_math();
    if (fails) printf("accel: %d of %d cases differ\n", fails, cases);
    else printf("accel: Wolf3D's, %d cases, each as its loop has it\n", cases);
    return fails != 0;
}
