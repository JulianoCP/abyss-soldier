#include "public/player.h"

Character Player;
u8 OldButtons[NUMBER_OF_JOYPADS] = {0};
u8 CurrentButtons[NUMBER_OF_JOYPADS] = {0};

u16 PlayerInit(u16 VRAMIndex)
{
    VRAMIndex += CharacterInit(&Player, &SoldierImage, MakePosition(FIX16((SCREEN_W / 2 ) - 16), FIX16((SCREEN_H / 2 ) - 16)), MakeAttribute(FIX16(INIT_PLAYER_SPEED), FIX16(INIT_PLAYER_HEALTH)), PAL_PLAYER, VRAMIndex);
    return VRAMIndex;
}

void PlayerUpdate(Character* Enemies[], u16 EnemyCount)
{
    ClearCharacterInputs(&Player);
    UpdatePlayerInputs();

    UpdateCharacterPosition(&Player);
    UpdatePlayerTarget(Enemies, EnemyCount);
}

void UpdatePlayerTarget(Character* Enemies[], u16 EnemyCount)
{
    Character* targetReference = FindNearbyTarget(Enemies, EnemyCount);

    if (!targetReference)
    {
       return;
    }

    int distanceToX = F16_toInt(targetReference->_Node._Position._X - Player._Node._Position._X);
    int distanceToY = F16_toInt(targetReference->_Node._Position._Y - Player._Node._Position._Y);

    int approxDeg = GetApproxAngle(distanceToX, distanceToY);
    int directionIndex = DEG_TO_INDEX((approxDeg + 360) % 360);

    Player._Node._Sprite->animation = directionIndex;
    SPR_setAnim(Player._Node._Sprite, Player._Node._Sprite->animation);
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
}

fix16 GetDistanceSquared(Position TargetPosition)
{
    fix16 distanceToX = TargetPosition._X - Player._Node._Position._X;
    fix16 distanceToY = TargetPosition._Y - Player._Node._Position._Y;

    return FIX16(F16_mul(distanceToX, distanceToX) + F16_mul(distanceToY, distanceToY));
}

Character* FindNearbyTarget(Character* Enemies[], u16 EnemyCount)
{
    if (EnemyCount == 0)
    {
        return NULL;
    }

    Character* closestEnemy = NULL;
    fix16 closestDist = FIX16(999999);

    for (u16 enemyIndex = 0; enemyIndex < EnemyCount; enemyIndex++)
    {
        Character* enemyReference = Enemies[enemyIndex];

        if (!enemyReference)
        {
            continue;
        }

        fix16 distResult = GetDistanceSquared(enemyReference->_Node._Position);

        if (distResult < closestDist)
        {
            closestDist = distResult;
            closestEnemy = enemyReference;
        }
    }
    
    return closestEnemy;
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