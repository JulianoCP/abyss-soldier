#include "public/player.h"

Character Player;
u8 OldButtons[NUMBER_OF_JOYPADS] = {0};
u8 CurrentButtons[NUMBER_OF_JOYPADS] = {0};

u16 PlayerInit(u16 VRAMIndex)
{
    VRAMIndex += CharacterInit(&Player, &SoldierImage, MakePosition(FIX16((SCREEN_W / 2 ) - 16), FIX16((SCREEN_H / 2 ) - 16)), MakeAttribute(FIX16(INIT_PLAYER_SPEED), FIX16(INIT_PLAYER_HEALTH)), PAL_PLAYER, VRAMIndex);
    return VRAMIndex;
}

void PlayerUpdate()
{
    UpdatePlayerInputs();
}

void UpdatePlayerInputs() 
{
    for (int joyIndex = NUMBER_OF_JOYPADS-1; joyIndex >= 0; --joyIndex) 
    {
		OldButtons[joyIndex] = CurrentButtons[joyIndex];
		CurrentButtons[joyIndex] = JOY_readJoypad(joyIndex);
	}
    
    if (IsKeyDown(JOY_1, BUTTON_LEFT))  { Player._Input._X = -1; }
    if (IsKeyDown(JOY_1, BUTTON_RIGHT)) { Player._Input._X =  1; }
    if (IsKeyDown(JOY_1, BUTTON_UP))    { Player._Input._Y = -1; }
    if (IsKeyDown(JOY_1, BUTTON_DOWN))  { Player._Input._Y =  1; }
    
    FindNearbyTarget(&Player);
    UpdateCharacterPosition(&Player);
    
    ClearCharacterInputs(&Player);
}

void FindNearbyTarget()
{

}

bool IsBitset(u8 Value, u8 Bit) 
{
    return ((Value & Bit) == Bit);
}

bool IsKeyDown(u8 JoyId, u8 Key) 
{
    return IsBitset(CurrentButtons[JoyId], Key);
}

bool IsKeyPressed(u8 JoyId, u8 Key) 
{
    return IsBitset(CurrentButtons[JoyId], Key) && !IsBitset(OldButtons[JoyId], Key);
}

bool IsKeyReleased(u8 JoyId, u8 Key) 
{
    return !IsBitset(CurrentButtons[JoyId], Key) && IsBitset(OldButtons[JoyId], Key);
}