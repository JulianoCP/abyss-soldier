#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "resource.h"

#ifndef _UTILS_H_
#define _UTILS_H_

#define NUMBER_OF_JOYPADS 2

extern s16 OldButtons[NUMBER_OF_JOYPADS];
extern s16 CurrentButtons[NUMBER_OF_JOYPADS];

bool IsBitset(const s16 Value, const s16 Bit);
bool IsKeyReleased(const s16 JoyId, const s16 Key);
bool IsKeyDown(const s16 JoyId, const s16 Key);
bool IsKeyPressed(const s16 JoyId, const s16 Key);

#endif