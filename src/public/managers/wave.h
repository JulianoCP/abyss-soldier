#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/entities/enemy.h"

#ifndef _WAVE_H_
#define _WAVE_H_

#define MAX_ENEMIES 1

extern s16 EnemyCount;
extern Character* Enemies[MAX_ENEMIES];

s16 WaveManagerInit(s16 VRAMIndex);
s16 AddEnemy(s16 VRAMIndex);
void UpdateWave(Character* PlayerReference);

#endif