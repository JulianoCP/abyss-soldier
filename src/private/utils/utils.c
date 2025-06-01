#include "public/utils/utils.h"

s16 OldButtons[NUMBER_OF_JOYPADS];
s16 CurrentButtons[NUMBER_OF_JOYPADS];

bool IsBitset(const s16 Value, const s16 Bit) 
{
    return ((Value & Bit) == Bit);
}

bool IsKeyDown(const s16 JoyId, const s16 Key) 
{
    return IsBitset(CurrentButtons[JoyId], Key);
}

bool IsKeyPressed(const s16 JoyId, const s16 Key) 
{
    return IsBitset(CurrentButtons[JoyId], Key) && !IsBitset(OldButtons[JoyId], Key);
}

bool IsKeyReleased(const s16 JoyId, const s16 Key) 
{
    return !IsBitset(CurrentButtons[JoyId], Key) && IsBitset(OldButtons[JoyId], Key);
}