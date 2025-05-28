#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/entities/enemy.h"

#ifndef _WAVE_H_
#define _WAVE_H_

#define MAX_ENEMIES 1

extern u16 EnemyCount;
extern Character* Enemies[MAX_ENEMIES];

u16 WaveManagerInit(u16 VRAMIndex);
u16 AddEnemy(u16 VRAMIndex);
void UpdateWave(Character* PlayerReference);

#endif