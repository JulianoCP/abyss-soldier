#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>

#include "resource.h"

#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#define BG_MAP        BG_B

#define PAL_PLAYER 		PAL0
#define PAL_ENEMY 		PAL1
#define PAL_MAP 		PAL2

#define M_PI 3.14159265f

#define SCREEN_W 320
#define SCREEN_H 224

#define SCREEN_W_F16 FIX16(320)
#define SCREEN_H_F16 FIX16(224)

#define ENEMY_DIMENSION FIX16(16)
#define PLAYER_DIMENSION FIX16(32)

#define SCREEN_TILES_W SCREEN_W/8
#define SCREEN_TILES_H SCREEN_H/8

#define WALL_SIZE 32
#define NUMBER_OF_JOYPADS 2

#define ABS(X) ((X) < 0 ? -(X) : (X))

#endif