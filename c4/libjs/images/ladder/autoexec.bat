@ECHO OFF
ECHO Welcome to C4DOS, the Build Ladder
VER
PATH \BUILD;\GRIN;\BIN
REM C4KE and C4IX find their files, and the games, through APPEND
APPEND \BUILD;\C4KE;\C4IX;\GRIN;\BIN;\GAMES\DOOM;\GAMES\ROTT;\GAMES\WOLF3D
ECHO The games, in \GAMES: DOOM, ROTT, WOLF3D.
ECHO GRIN starts the graphical shell.
ECHO Climb: BUILD, then RUN dosload.c4r c4ke.c4r boots the kernel it built.
ECHO TYPE LADDER.TXT says every step, up to C4IX.
