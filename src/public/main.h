#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>

#include "resource.h"
#include "public/map.h"
#include "public/library.h"
#include "public/player.h"
#include "public/enemy.h"
#include "public/wave.h"

#ifndef _MAIN_H_
#define _MAIN_H_

extern u16 VRAMTileIndex;

int main(bool HardReset);
void GameInit();

#endif