#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/level/map.h"
#include "public/utils/library.h"
#include "public/managers/wave.h"
#include "public/utils/game.h"
#include "public/managers/controller.h"

#ifndef _MAIN_H_
#define _MAIN_H_

extern s16 VRAMTileIndex;

int main(bool HardReset);
void GameInit();

void GameStartScreen();
void GameLoopScreen();
void GameOverScreen();
void ClearGameScreen();

#endif