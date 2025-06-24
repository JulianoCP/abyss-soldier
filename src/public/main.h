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

#define KEY_DELAY_TIME 240

extern bool bIsCredit;
extern s16 VRAMTileIndex;
extern s8 SelectedContext;
extern Sprite* ButtonReference;

int main(bool HardReset);
void MainInit();

void GameStartScreen();
void GameLoopScreen();
void GameOverScreen();
void CreditScreen();
void ClearGameScreen();

#endif