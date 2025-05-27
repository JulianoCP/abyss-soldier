#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/node.h"
#include "public/library.h"
#include "public/character.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define INIT_PLAYER_SPEED 10
#define INIT_PLAYER_HEALTH 200

#define NUM_DIRECTIONS 8
#define DIRECTION_TOLERANCE 4

extern Character Player;
extern u8 OldButtons[NUMBER_OF_JOYPADS];
extern u8 CurrentButtons[NUMBER_OF_JOYPADS];

u16 PlayerInit(u16 ind);
s16 GetDirectionIndex(s16 X, s16 Y);
fix16 GetDistanceSquared(Position TargetPosition);
Character* FindNearbyTarget(Character* ListOfEnemies[], u16 EnemyCount);

void UpdatePlayerInputs();
void UpdatePlayer(Character* ListOfEnemies[], u16 EnemyCount);
void UpdatePlayerTarget(Character* ListOfEnemies[], u16 EnemyCount);

bool IsBitset(u8 Value, u8 Bit);
bool IsKeyReleased(u8 JoyId, u8 Key);
bool IsKeyDown(u8 JoyId, u8 Key);
bool IsKeyPressed(u8 JoyId, u8 Key);

#endif