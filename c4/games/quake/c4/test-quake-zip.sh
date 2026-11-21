#!/bin/sh
# test-quake-zip.sh -- make test-quake-zip (c4.mk), from c4's root: Quake
# from the disks as the site has them. `make c4bb-images` with
# QUAKE_AS_ZIP=1 puts id's quake106.zip, whole, where pak0.pak went, and
# its recipe beside it (pak0.pak.unpack); libjs makes pak0.pak from it
# when the game opens it (c4's libjs/unpack.js). Then:
#   - no disk has a pak0.pak, every disk Quake reads from has the package
#     byte for byte as id's, and every listing names pak0.pak (C4DOS's
#     c4dos.dir, C4IX's c4ix.sizes, the page's index.json, with the hash
#     the page keeps it under);
#   - libjs makes it, and how long that takes (libjs/tests/test-unpack.mjs);
#   - demo3's timedemo on the bare machine, under C4DOS (the games disk's,
#     flat, and the page's ladder disk's, in \GAMES\QUAKE) and inside C4IX
#     shows gcc's frames from pak0.pak itself, as test-quake's do.
# Last, the images are built again without QUAKE_AS_ZIP, as the other
# tests have them (also when a check fails).
MAKE=${MAKE:-make}
D=games/quake/data
RUN='-nosound -nocdaudio -sum +timedemo demo3'
T=.quake_z
LOG=$T/images.log
rm -rf $T && mkdir -p $T/id1
restore () {
    echo "test-quake-zip: the images again, without QUAKE_AS_ZIP"
    QUAKE_AS_ZIP= $MAKE --no-print-directory c4bb-images > $LOG 2>&1 || { tail -20 $LOG; echo "test-quake-zip: the images could not be built again"; }
}
fail () { echo "test-quake-zip: $*"; restore; exit 1; }

echo "test-quake-zip: the images, with QUAKE_AS_ZIP=1"
QUAKE_AS_ZIP=1 $MAKE --no-print-directory c4bb-images > $LOG 2>&1 || { tail -20 $LOG; fail "make c4bb-images failed"; }

# the disks
pak=$(find src/c4bb/images libjs/images -iname pak0.pak | head -5)
[ -z "$pak" ] || fail "a pak0.pak on the disks: $pak"
for d in src/c4bb/images/games src/c4bb/images/disk libjs/images/dos/GAMES/QUAKE libjs/images/ladder/GAMES/QUAKE; do
    cmp -s $D/quake106.zip $d/quake106.zip || fail "$d has no quake106.zip, or not id's"
    [ -f $d/pak0.pak.unpack ] || fail "$d has no pak0.pak.unpack"
done
for l in src/c4bb/images/games/c4dos.dir libjs/images/dos/GAMES/QUAKE/c4dos.dir libjs/images/ladder/GAMES/QUAKE/c4dos.dir; do
    grep -qx 'pak0.pak' $l || fail "$l does not list pak0.pak"
    ! grep -qx 'pak0.pak.unpack' $l || fail "$l lists the recipe"
done
grep -qx '18689235 pak0.pak' src/c4bb/images/disk/c4ix.sizes || fail "C4IX's c4ix.sizes does not list pak0.pak"
for i in src/c4bb/images/games/index.json src/c4bb/images/disk/index.json libjs/images/dos/index.json libjs/images/ladder/index.json; do
    grep -q '\["[A-Za-z/]*pak0.pak",18689235,"35a9c55e5e5a284a"\]' $i || fail "$i does not list pak0.pak with its hash"
done
echo "test-quake-zip: the disks carry quake106.zip as id's, no pak0.pak, and list pak0.pak"

# libjs makes it
QUAKE_ZIP=$D/quake106.zip node libjs/tests/test-unpack.mjs || fail "libjs did not make pak0.pak"

# the frames: gcc's from the pak itself ...
cp $D/pak0.pak $T/id1/
(cd $T && ../quake-host $RUN 2> /dev/null | grep '^timedemo' > host.txt)
cat $T/host.txt
[ -s $T/host.txt ] || fail "quake-host gave no frames"
# ... and libjs's, from the package: bare and under the games disk's C4DOS
# at once, then inside C4IX and under the ladder's C4DOS
(cd src/c4bb/images/games && { timeout 1500 node ../../../../libjs/cli.js -m 128 -d . quake.c4r $RUN \
     > ../../../../$T/bare.out 2> ../../../../$T/bare.err &
   printf 'quake %s\nver\n' "$RUN" | timeout 1500 node ../../../../libjs/cli.js -m 128 -d . ../c4dos32.c4r \
     > ../../../../$T/dos.out 2> ../../../../$T/dos.err; wait; })
printf 'quake %s\nexit\n' "$RUN" | timeout 1500 node libjs/cli.js -m 64 -d src/c4bb/images/disk src/c4bb/images/c4ix32.c4r \
    > $T/c4ix.out 2> $T/c4ix.err
printf 'cd \\GAMES\\QUAKE\nquake %s\nver\n' "$RUN" | timeout 1500 node libjs/cli.js -m 192 -d libjs/images/ladder libjs/images/ladder/c4dos32.c4r \
    > $T/ladder.out 2> $T/ladder.err
for w in bare dos c4ix ladder; do
    if grep '^timedemo' $T/$w.out | cmp -s $T/host.txt -; then echo "test-quake-zip: $w: gcc's frames"
    else echo "test-quake-zip: $w's frames differ:"; tail -5 $T/$w.out; tail -3 $T/$w.err; fail "$w's frames differ"; fi
done
restore
rm -rf $T
echo "test-quake-zip: OK"
