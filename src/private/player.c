#include "public/player.h"

u16 BulletCount = 0;
Bullet* Bullets[MAX_BULLETS];

u8 OldButtons[NUMBER_OF_JOYPADS];
u8 CurrentButtons[NUMBER_OF_JOYPADS];

u16 PlayerInit(u16 VRAMIndex, Character* PlayerReference)
{
    VRAMIndex += CharacterInit(PlayerReference, &SoldierSprite, MakePosition(FIX16((SCREEN_W / 2 ) - 16), FIX16((SCREEN_H / 2 ) - 16)), MakeAttribute(FIX16(INIT_PLAYER_SPEED), FIX16(INIT_PLAYER_HEALTH), FIX16(INIT_PLAYER_DAMAGE)), PAL_PLAYER, VRAMIndex);

    while (MAX_BULLETS > BulletCount)
    {
        VRAMIndex += AddBullet(VRAMIndex, PlayerReference);
        BulletCount++;
    }

    return VRAMIndex;
}

u16 AddBullet(u16 VRAMIndex, Character* PlayerReference)
{
    Bullet* newBullet = malloc(sizeof(Bullet));

    if (!newBullet)
    {
        return VRAMIndex;
    }

    Bullets[BulletCount] = newBullet;
    return BulletInit(newBullet, &BulletSprite, PlayerReference->_Node._Position, MakeAttribute(FIX16(BULLET_SPEED), FIX16(BULLET_HEALTH), FIX16(INIT_PLAYER_DAMAGE)), PAL_BULLET, VRAMIndex);
}

void UpdatePlayer(Character* PlayerReference, Character* ListOfEnemies[], u16 EnemyCount)
{
    UpdatePlayerInputs(PlayerReference);

    UpdateCharacterPosition(PlayerReference);
    UpdatePlayerTarget(PlayerReference, ListOfEnemies, EnemyCount);
}

void UpdatePlayerTarget(Character* PlayerReference, Character* ListOfEnemies[], u16 EnemyCount)
{
    const Character* targetReference = FindNearbyTarget(PlayerReference, ListOfEnemies, EnemyCount);

    if (!targetReference)
    {
       return;
    }

    const s16 distanceToX = F16_toInt(targetReference->_Node._Position._X - PlayerReference->_Node._Position._X);
    const s16 distanceToY = F16_toInt(targetReference->_Node._Position._Y - PlayerReference->_Node._Position._Y);

    SPR_setAnim(PlayerReference->_Node._Sprite, GetDirectionIndex(distanceToX, distanceToY));
}

void UpdatePlayerInputs(Character* PlayerReference) 
{
    ClearCharacterInputs(PlayerReference);

    for (s16 joyIndex = (NUMBER_OF_JOYPADS - 1); joyIndex >= 0; --joyIndex) 
    {
		OldButtons[joyIndex] = CurrentButtons[joyIndex];
		CurrentButtons[joyIndex] = JOY_readJoypad(joyIndex);
	}
    
    if (IsKeyDown(JOY_1, BUTTON_LEFT)) { PlayerReference->_Input._X = -1; }
    if (IsKeyDown(JOY_1, BUTTON_RIGHT)) { PlayerReference->_Input._X = 1; }
    if (IsKeyDown(JOY_1, BUTTON_UP)) { PlayerReference->_Input._Y = -1; }
    if (IsKeyDown(JOY_1, BUTTON_DOWN)) { PlayerReference->_Input._Y = 1; }
}

Character* FindNearbyTarget(Character* PlayerReference, Character* ListOfEnemies[], u16 EnemyCount)
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

        fix16 distResult = GetDistanceSquared(PlayerReference, enemyReference->_Node._Position);

        if (distResult < closestDist)
        {
            closestDist = distResult;
            closestEnemy = enemyReference;
        }
    }
    
    return closestEnemy;
}

fix16 GetDistanceSquared(Character* PlayerReference, Position TargetPosition)
{
    const fix16 distanceToX = PlayerReference->_Node._Position._X - TargetPosition._X;
    const fix16 distanceToY = PlayerReference->_Node._Position._Y - TargetPosition._Y;

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