#include <genesis.h>
#include <sprite_eng.h>

#include "public/entities/player.h"

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

extern Character Player;

u16 ControllerInit(u16 VRAMIndex);
void UpdateController(Character* ListOfEnemies[], u16 EnemyCount);

#endif