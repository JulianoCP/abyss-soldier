#include <genesis.h>
#include <sprite_eng.h>

#include "public/node.h"
#include "public/library.h"
#include "public/character.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define INIT_PLAYER_SPEED   2
#define INIT_PLAYER_HEALTH 	200

extern Character Player;
extern u8 OldButtons[NUMBER_OF_JOYPADS];
extern u8 CurrentButtons[NUMBER_OF_JOYPADS];

void PlayerUpdate();
void UpdatePlayerInputs();

u16 PlayerInit(u16 ind);
bool IsBitset(u8 Value, u8 Bit);
bool IsKeyReleased(u8 JoyId, u8 Key);
bool IsKeyDown(u8 JoyId, u8 Key);
bool IsKeyPressed(u8 JoyId, u8 Key);

#endif