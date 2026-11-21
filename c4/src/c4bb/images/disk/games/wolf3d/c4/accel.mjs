// accel.mjs -- Wolfenstein 3D's accelerators for c4's libjs (its
// libjs/accel.js, docs/accel.md): the walls' and sprites' scalers, the
// screen's scaled blit, the timedemo's checksum and FixedMul, run by the
// host when the machine has them and the Control menu's Accelerated is on.
// c4/c4accel.h is the game's side, with each operation's number (WA_*);
// wl_draw.c, wl_scale.c, id_vl.c, c4sdl.c and wl_utils.h call them, and
// keep their own C for every other machine. Each does exactly what that C
// does: the same pixels in the same order, 32-bit arithmetic wrapping,
// shifts as c4's SHR and LSR take them.
export default function wolf3d({ reader, writer, reader32, args }) {
  // WA_POST (wh, vbuf, pitch, postx, centery, vh, src, tsize): ScalePost,
  // a wall's post from the bottom up, the rows below the view stepped over
  // first, wh being wallheight[postx]
  function post(m) {
    const [wh, vbuf, pitch, postx, centery, vh, src, tsize] = args(m, 8);
    const half = tsize >> 1;
    let ywcount = wh >> 3, yd = ywcount;
    if (yd <= 0) yd = 100;
    let yoffs = Math.imul((centery - ywcount) | 0, pitch);
    if (yoffs < 0) yoffs = 0;
    yoffs = (yoffs + postx) | 0;
    let yendoffs = (centery + ywcount - 1) | 0, yw = tsize - 1;
    while (yendoffs >= vh) {
      ywcount = (ywcount - half) | 0;
      while (ywcount <= 0) { ywcount = (ywcount + yd) | 0; yw--; }
      yendoffs--;
    }
    if (yw < 0) return 0;
    const rs = reader(m), wr = writer(m);
    let col = rs((src + yw) | 0);
    yendoffs = (Math.imul(yendoffs, pitch) + postx) | 0;
    let dest = (vbuf + yendoffs) | 0;
    const top = (vbuf + yoffs) | 0;
    while (dest >= top) {
      wr(dest, col);
      ywcount = (ywcount - half) | 0;
      if (ywcount <= 0) {
        do { ywcount = (ywcount + yd) | 0; yw--; } while (ywcount <= 0);
        if (yw < 0) break;
        col = rs((src + yw) | 0);
      }
      dest = (dest - pitch) | 0;
    }
    return 0;
  }

  // WA_LINE (x, toppix, fracstep, linesrc, linecmds, vbuf, ylookup, pitch,
  // vh): ScaleLine, a sprite's column, every segment of its list
  function line(m) {
    let [x, toppix, fracstep, linesrc, linecmds, vbuf, ylookup, pitch, vh] = args(m, 9);
    const rc = reader(m), rs = reader(m), ry = reader32(m), wr = writer(m);
    const short = a => rc(a) | (rc((a + 1) | 0) << 8);
    for (let end = short(linecmds) >> 1; end; end = short(linecmds) >> 1) {
      const top = (short((linecmds + 2) | 0) << 16) >> 16;
      let start = short((linecmds + 4) | 0) >> 1;
      let frac = Math.imul(start, fracstep);
      let endpix = ((frac >> 16) + toppix) | 0;
      for (let src = (linesrc + top + start) | 0; start !== end; start++, src = (src + 1) | 0) {
        let startpix = endpix;
        if (startpix >= vh) break;
        frac = (frac + fracstep) | 0;
        endpix = ((frac >> 16) + toppix) | 0;
        if (endpix < 0) continue;
        if (startpix < 0) startpix = 0;
        if (endpix > vh) endpix = vh;
        if (startpix >= endpix) continue;
        const col = rs(src);
        let dest = (vbuf + ry((ylookup + 4 * startpix) | 0) + x) | 0;
        for (; startpix < endpix; startpix++, dest = (dest + pitch) | 0) wr(dest, col);
      }
      linecmds = (linecmds + 6) | 0;
    }
    return 0;
  }

  // WA_SUM (sum, pixels, w, h, pitch, pal): c4sdl_present's checksum of a
  // timedemo's frame, each row's words as they lie, then the 256 colours
  function sum(m) {
    let [s, pix, w, h, pitch, pal] = args(m, 6);
    const r32 = reader32(m), rb = reader(m);
    const n = w >> 2;
    for (let y = 0; y < h; y++) {
      const row = (pix + Math.imul(y, pitch)) | 0;
      for (let x = 0; x < n; x++) s = (Math.imul(s, 31) + r32((row + 4 * x) | 0)) | 0;
    }
    for (let x = 0; x < 256; x++) {
      const c = (pal + 4 * x) | 0;
      s = (Math.imul(s, 31) + rb(c) * 65536 + rb((c + 1) | 0) * 256 + rb((c + 2) | 0)) | 0;
    }
    return s;
  }

  // WA_FIXMUL (a, b): wl_utils.c's FixedMul, ((int64_t)a * b + 0x8000) >>
  // 16, its low word, as its 32-bit pieces make it
  function fixmul(m) {
    const [a, b] = args(m, 2);
    const ah = a >> 16, al = a & 0xffff, bh = b >> 16, bl = b & 0xffff;
    return ((Math.imul(ah, bh) << 16) + Math.imul(ah, bl) + Math.imul(al, bh) + ((al * bl + 0x8000) >>> 16)) | 0;
  }

  // WA_BLIT (source, origwidth, srcx, srcy, width, height, dest, ylookup,
  // destx, desty, scale): id_vl.c's VL_MemToScreenScaledCoord and its
  // ...2, a block's part, each pixel a scale x scale square
  function blit(m) {
    const [source, ow, srcx, srcy, width, height, dest, ylookup, destx, desty, sc] = args(m, 11);
    const rs = reader(m), ry = reader32(m), wr = writer(m);
    for (let j = 0, scj = 0; j < height; j++, scj += sc) {
      const srow = (source + Math.imul(j + srcy, ow) + srcx) | 0;
      for (let i = 0, sci = 0; i < width; i++, sci += sc) {
        const col = rs((srow + i) | 0);
        for (let mm = 0; mm < sc; mm++) {
          const base = (dest + ry((ylookup + 4 * (scj + mm + desty)) | 0) + sci + destx) | 0;
          for (let nn = 0; nn < sc; nn++) wr((base + nn) | 0, col);
        }
      }
    }
    return 0;
  }

  return [post, line, sum, fixmul, blit];
}
