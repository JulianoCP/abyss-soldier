#include "public/entities/bullet.h"

s16 BulletInit(Bullet* BulletReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const s16 PaletteValue, s16 VRAMIndex)
{
    if (!BulletReference) { return VRAMIndex; };

    BulletReference->_IsActive = FALSE;
    BulletReference->_Attribute._Speed = AttributeValue._Speed;
    BulletReference->_Attribute._Health = AttributeValue._Health;

    s16 vramResult = NodeInit(&BulletReference->_Node, SpriteValue, PositionValue, PaletteValue, VRAMIndex);
    SPR_setVisibility(BulletReference->_Node._Sprite, HIDDEN);

    return vramResult;
}

void DeactivateBullet(Bullet* BulletReference)
{
    if (!BulletReference) { return; };

    BulletReference->_IsActive = FALSE;
    BulletReference->_Direction._X = FIX16(0);
    BulletReference->_Direction._Y = FIX16(0);

    SPR_setVisibility(BulletReference->_Node._Sprite, HIDDEN);
}

void ActivateBullet(Bullet* BulletReference, const Position PositionValue, const Direction DirectionValue)
{
    if (!BulletReference) { return; };
    
    BulletReference->_IsActive = TRUE;

    BulletReference->_Node._Position._X = PositionValue._X;
    BulletReference->_Node._Position._Y = PositionValue._Y;

    BulletReference->_Direction._X = DirectionValue._X;
    BulletReference->_Direction._Y = DirectionValue._Y;

    SPR_setPosition(BulletReference->_Node._Sprite, F16_toInt(BulletReference->_Node._Position._X), F16_toInt(BulletReference->_Node._Position._Y));
    SPR_setVisibility(BulletReference->_Node._Sprite, VISIBLE);
}

void UpdateBullet(Bullet* BulletReference)
{
    if (!BulletReference || !BulletReference->_IsActive) { return; }
    
    UpdateBulletPosition(BulletReference);
}

void BulletCheckHitEnemies(Bullet* BulletReference, Character* ListOfEnemies[], const s16 EnemyCount)
{
    if (!BulletReference || !BulletReference->_IsActive) { return; }

    for (s16 enemyIndex = 0; enemyIndex < EnemyCount; enemyIndex++)
    {
        Character* enemyReference = ListOfEnemies[enemyIndex];

        if (!enemyReference) // || !enemyReference->_IsActive
        {
            continue;
        }

        fix16 distanceToX = BulletReference->_Node._Position._X - enemyReference->_Node._Position._X;
        fix16 distanceToY = BulletReference->_Node._Position._Y - enemyReference->_Node._Position._Y;

        fix16 distSquared = F16_mul(distanceToX, distanceToX) + F16_mul(distanceToY, distanceToY);

        if (distSquared <= F16_mul(BULLET_HIT_RADIUS, BULLET_HIT_RADIUS))
        {
            DeactivateBullet(BulletReference);
            ApplyCharacterDamage(enemyReference, BulletReference->_Attribute._Damage);
            return;
        }
    }
}

fix16 GetBulletSpeed(Bullet* BulletReference)
{
    if (!BulletReference) { return FIX16(0); };

    const bool IsDiagonal = (BulletReference->_Direction._X != FIX16(0) && BulletReference->_Direction._Y != FIX16(0));

    return IsDiagonal ? F16_mul(DIAGONAL_FIX, BulletReference->_Attribute._Speed) : BulletReference->_Attribute._Speed;
}

void UpdateBulletPosition(Bullet* BulletReference)
{
    if (!BulletReference || !BulletReference->_IsActive) { return; }
    else if (BulletReference->_Direction._X == FIX16(0) && BulletReference->_Direction._Y == FIX16(0)) { return; };

    BulletReference->_Node._Position._X = BulletReference->_Node._Position._X + F16_mul(BulletReference->_Direction._X, BulletReference->_Attribute._Speed);
    BulletReference->_Node._Position._Y = BulletReference->_Node._Position._Y + F16_mul(BulletReference->_Direction._Y, BulletReference->_Attribute._Speed);

    SPR_setPosition(BulletReference->_Node._Sprite, F16_toInt(BulletReference->_Node._Position._X), F16_toInt(BulletReference->_Node._Position._Y));

    if (BulletReference->_Node._Position._X < FIX16(WALL_BLOCK_SIZE) || BulletReference->_Node._Position._X > FIX16(SCREEN_W - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION))) 
    { 
        DeactivateBullet(BulletReference);
    }
    else if (BulletReference->_Node._Position._Y < FIX16(WALL_BLOCK_SIZE) || BulletReference->_Node._Position._Y > FIX16(SCREEN_H - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION)))
    {
        DeactivateBullet(BulletReference);
    }
}