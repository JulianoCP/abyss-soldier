#include <genesis.h>
#include <sprite_eng.h>

#include "public/entities/player.h"

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

extern Character Player;

s16 ControllerInit(s16 VRAMIndex);
void UpdateController(Character* ListOfEnemies[], s16 EnemyCount);

#endif