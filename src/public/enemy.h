#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/node.h"
#include "public/library.h"
#include "public/character.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

#define INIT_ENEMY_SPEED 5
#define INIT_ENEMY_HEALTH 20

u16 EnemyInit(u16 VRAMIndex, Character* EnemyReference);

void UpdateEnemy(Character* EnemyReference, const Character* PlayerReference);
void UpdateEnemyInputs(Character* EnemyReference, const Character* PlayerReference);

#endif