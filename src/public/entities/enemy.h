#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/base/character.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

#define RESPAWN_TIME 240

#define INIT_ENEMY_SPEED 3
#define INIT_ENEMY_HEALTH 20

s16 EnemyInit(s16 VRAMIndex, Character* EnemyReference);

void UpdateEnemyState(Character* EnemyReference);
void RespawnEnemy(Character* EnemyReference);

void UpdateEnemy(Character* EnemyReference, const Character* PlayerReference);
void UpdateEnemyInputs(Character* EnemyReference, const Character* PlayerReference);

#endif