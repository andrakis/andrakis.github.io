# c4-images.sh c4ix|bare -- Quake's part of c4's build-images.sh, which
# sources it from c4's root (games/README.md in c4)
GAMEDIR=games/quake
# The shareware's pak0.pak, into DIR. With QUAKE_AS_ZIP=1 (the site's
# build) id's package instead, whole and as it was distributed, its
# licence in it, and beside it the recipe c4's libjs makes pak0.pak from it
# with when the game opens it, pak0.pak.unpack (libjs/unpack.js): the
# licence lets the shareware be passed on only so (data/README.md). The
# disk's listings name pak0.pak all the same (c4's
# src/c4bb/tests/unpacked.py). The recipe is c4/pak0-unpack.json here: the
# game's text files go on C4IX's disk too, as the IDE's sources, where a
# NAME.unpack would be one. C4IX's disk is not made anew each time, so
# what the other way left there goes first.
quake_pak () {          # quake_pak DIR
    rm -f $1/pak0.pak $1/quake106.zip $1/pak0.pak.unpack
    case "${QUAKE_AS_ZIP:-0}" in
    0|'') if [ -f $GAMEDIR/data/pak0.pak ]; then cp $GAMEDIR/data/pak0.pak $1/; fi ;;
    *) if [ -f $GAMEDIR/data/quake106.zip ]; then
           cp $GAMEDIR/data/quake106.zip $1/; cp $GAMEDIR/c4/pak0-unpack.json $1/pak0.pak.unpack
       fi ;;
    esac
}
case "$1" in
c4ix)
    # linked against C4IX's libc, with the shareware pak beside it
    # (c4ix.vfs.txt: /usr/games/quake)
    if [ -f .quake/qg-sum.c4o ] && [ -f $PB/lib/libc.c4s ]; then
        say "linking Quake for C4IX"
        ./c4rlink32 .quake/*.c4o .quake/plat/qg-c4ix.c4o -l $PB/lib/libc.c4s -o $DISK/c4ix-quake.c4r > /dev/null
        quake_pak $DISK
    fi ;;
bare)
    if [ -f .quake/qg-sum.c4o ]; then
        item quake
        # (.quake has its own math: c4.mk)
        ./c4rlink32 .quake/*.c4o .quake/plat/qg-bare.c4o $(ls .libc-bare/libc-*.c4o | grep -v '/libc-math\.c4o$') -o $GAMESDISK/quake.c4r > /dev/null
        quake_pak $GAMESDISK
        GAMES_ON_DISK="$GAMES_ON_DISK QUAKE"
    fi ;;
esac
