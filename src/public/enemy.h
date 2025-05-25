#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>

#include "public/node.h"
#include "public/library.h"
#include "public/character.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

#define INIT_ENEMY_SPEED    2
#define INIT_ENEMY_HEALTH 	20

u16 EnemyInit(u16 VRAMIndex, Character* EnemyReference);

#endif