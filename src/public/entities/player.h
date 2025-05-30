#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/base/character.h"
#include "public/entities/bullet.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define TEXT_COL 34
#define TEXT_ROW 3

#define INIT_PLAYER_SPEED 5
#define INIT_PLAYER_HEALTH 200
#define INIT_PLAYER_DAMAGE 20

#define NUM_DIRECTIONS 8
#define DIRECTION_TOLERANCE 2

#define SHOT_COOLDOWN 180
#define CHANGE_TARGET_COOLDOWN 300

#define MAX_BULLETS 8
#define BULLET_SPEED 0.5
#define BULLET_HEALTH 0

extern s16 BulletCount;
extern Bullet* Bullets[MAX_BULLETS];

extern s16 ShootingCooldown;
extern s16 ChooseTargetCooldown;

extern s16 OldButtons[NUMBER_OF_JOYPADS];
extern s16 CurrentButtons[NUMBER_OF_JOYPADS];

s16 PlayerInit(s16 VRAMIndex, Character* PlayerReference);
s16 AddPlayerBullet(s16 VRAMIndex, Character* PlayerReference);

s16 GetDirectionIndex(const s16 X, const s16 Y);
fix16 GetDistanceSquared(Character* PlayerReference, const Position TargetPosition);
Character* FindNearbyTarget(Character* PlayerReference, Character* ListOfEnemies[], const s16 EnemyCount);

bool IsBitset(const s16 Value, const s16 Bit);
bool IsKeyReleased(const s16 JoyId, const s16 Key);
bool IsKeyDown(const s16 JoyId, const s16 Key);
bool IsKeyPressed(const s16 JoyId, const s16 Key);

void UpdateHUDInfo(Character* PlayerReference);

void UpdatePlayerInputs(Character* PlayerReference);
void UpdatePlayerShooting(Character* PlayerReference);

void UpdatePlayerBullets(Character* PlayerReference, Character* ListOfEnemies[], const s16 EnemyCount);
void UpdatePlayer(Character* PlayerReference, Character* ListOfEnemies[], const s16 EnemyCount);
void UpdatePlayerTarget(Character* PlayerReference, Character* ListOfEnemies[], const s16 EnemyCount);

#endif