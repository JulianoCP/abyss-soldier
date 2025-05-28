#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/library.h"
#include "public/character.h"
#include "public/bullet.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define INIT_PLAYER_SPEED 10
#define INIT_PLAYER_HEALTH 200
#define INIT_PLAYER_DAMAGE 5

#define NUM_DIRECTIONS 8
#define DIRECTION_TOLERANCE 4

#define MAX_BULLETS 8
#define BULLET_SPEED 2
#define BULLET_HEALTH 0

extern u16 BulletCount;
extern Bullet* Bullets[MAX_BULLETS];

extern u8 OldButtons[NUMBER_OF_JOYPADS];
extern u8 CurrentButtons[NUMBER_OF_JOYPADS];

u16 PlayerInit(u16 VRAMIndex, Character* PlayerReference);
u16 AddBullet(u16 VRAMIndex, Character* PlayerReference);

s16 GetDirectionIndex(s16 X, s16 Y);
fix16 GetDistanceSquared(Character* PlayerReference, Position TargetPosition);
Character* FindNearbyTarget(Character* PlayerReference, Character* ListOfEnemies[], u16 EnemyCount);

void UpdatePlayerInputs();
void UpdatePlayer(Character* PlayerReference, Character* ListOfEnemies[], u16 EnemyCount);
void UpdatePlayerTarget(Character* PlayerReference, Character* ListOfEnemies[], u16 EnemyCount);

bool IsBitset(u8 Value, u8 Bit);
bool IsKeyReleased(u8 JoyId, u8 Key);
bool IsKeyDown(u8 JoyId, u8 Key);
bool IsKeyPressed(u8 JoyId, u8 Key);

#endif