#include "public/player.h"

Character Player;
u8 OldButtons[NUMBER_OF_JOYPADS] = {0};
u8 CurrentButtons[NUMBER_OF_JOYPADS] = {0};

u16 PlayerInit(u16 VRAMIndex)
{
    VRAMIndex += CharacterInit(&Player, &SoldierImage, MakePosition(FIX16((SCREEN_W / 2 ) - 16), FIX16((SCREEN_H / 2 ) - 16)), MakeAttribute(FIX16(INIT_PLAYER_SPEED), FIX16(INIT_PLAYER_HEALTH)), PAL_PLAYER, VRAMIndex);
    return VRAMIndex;
}

void UpdatePlayer(Character* ListOfEnemies[], u16 EnemyCount)
{
    UpdatePlayerInputs();

    UpdateCharacterPosition(&Player);
    UpdatePlayerTarget(ListOfEnemies, EnemyCount);
}

void UpdatePlayerTarget(Character* ListOfEnemies[], u16 EnemyCount)
{
    const Character* targetReference = FindNearbyTarget(ListOfEnemies, EnemyCount);

    if (!targetReference)
    {
       return;
    }

    const s16 distanceToX = F16_toInt(targetReference->_Node._Position._X - Player._Node._Position._X);
    const s16 distanceToY = F16_toInt(targetReference->_Node._Position._Y - Player._Node._Position._Y);

    SPR_setAnim(Player._Node._Sprite, GetDirectionIndex(distanceToX, distanceToY));
}

void UpdatePlayerInputs() 
{
    ClearCharacterInputs(&Player);

    for (s16 joyIndex = (NUMBER_OF_JOYPADS - 1); joyIndex >= 0; --joyIndex) 
    {
		OldButtons[joyIndex] = CurrentButtons[joyIndex];
		CurrentButtons[joyIndex] = JOY_readJoypad(joyIndex);
	}
    
    if (IsKeyDown(JOY_1, BUTTON_LEFT)) { Player._Input._X = -1; }
    if (IsKeyDown(JOY_1, BUTTON_RIGHT)) { Player._Input._X = 1; }
    if (IsKeyDown(JOY_1, BUTTON_UP)) { Player._Input._Y = -1; }
    if (IsKeyDown(JOY_1, BUTTON_DOWN)) { Player._Input._Y = 1; }
}

Character* FindNearbyTarget(Character* ListOfEnemies[], u16 EnemyCount)
{
    if (EnemyCount == 0)
    {
        return NULL;
    }

    Character* closestEnemy = NULL;
    fix16 closestDist = FIX16(999999);

    for (u16 enemyIndex = 0; enemyIndex < EnemyCount; enemyIndex++)
    {
        Character* enemyReference = ListOfEnemies[enemyIndex];

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

fix16 GetDistanceSquared(Position TargetPosition)
{
    const fix16 distanceToX = Player._Node._Position._X - TargetPosition._X;
    const fix16 distanceToY = Player._Node._Position._Y - TargetPosition._Y;

    return FIX16(F16_mul(distanceToX, distanceToX) + F16_mul(distanceToY, distanceToY));
}

s16 GetDirectionIndex(s16 X, s16 Y)
{
    if (X != 0 || Y != 0)
    {
        if (ABS(X) > ABS(Y))
        {
            if ((ABS(Y) * DIRECTION_TOLERANCE) < ABS(X)) { return X > 0 ? 0 : 4; }
            else { return X > 0 ? (Y < 0 ? 1 : 7) : (Y < 0 ? 3 : 5); };
        }
        else
        {
            if ((ABS(X) * DIRECTION_TOLERANCE) < ABS(Y)) { return Y < 0 ? 2 : 6; }
            else { return X > 0 ? (Y < 0 ? 1 : 7) : (Y < 0 ? 3 : 5); };
        }
    }

    return 0;
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