#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/base/character.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

#define INIT_ENEMY_DAMAGE 5
#define INIT_ENEMY_SPEED 3
#define INIT_ENEMY_HEALTH 20

#define RESPAWN_TIME 640
#define ENEMY_HIT_RADIUS 6

s16 EnemyInit(s16 VRAMIndex, Character* EnemyReference);

void UpdateEnemyState(Character* EnemyReference);
void RespawnEnemy(Character* EnemyReference);
void PredictRespawnLocation(Character* EnemyReference);
void EnemyCheckHitPlayer(Character* EnemyReference, Character* PlayerReference);

void UpdateEnemy(Character* EnemyReference, Character* PlayerReference);
void UpdateEnemyInputs(Character* EnemyReference, Character* PlayerReference);

#endif