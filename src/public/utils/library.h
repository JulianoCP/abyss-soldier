#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "resource.h"

#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#define BG_MAP BG_B

#define PAL_MAP PAL1
#define PAL_ENTITIES PAL2
#define PAL_HUD PAL3

#define SCREEN_W 320
#define SCREEN_H 224

#define DIAGONAL_FIX FIX16(0.7071)

#define WALL_SIZE 64
#define WALL_BLOCK_SIZE 12
#define CHARACTER_DIMENSION 32

#define ABS(X) ((X) < 0 ? -(X) : (X))

#endif