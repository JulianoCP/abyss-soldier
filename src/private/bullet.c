#include "public/bullet.h"

u16 BulletInit(Bullet* BulletReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const u16 PaletteValue, u16 VRAMIndex)
{
    if (!BulletReference) { return VRAMIndex; };

    BulletReference->_IsActive = FALSE;
    BulletReference->_Attribute._Speed = AttributeValue._Speed;
    BulletReference->_Attribute._Health = AttributeValue._Health;

    u16 vramResult = NodeInit(&BulletReference->_Node, SpriteValue, PositionValue, PaletteValue, VRAMIndex);
    SPR_setVisibility(BulletReference->_Node._Sprite, HIDDEN);

    return vramResult;
}

void DeactivateBullet(Bullet* BulletReference)
{
    if (!BulletReference) { return; };

    BulletReference->_IsActive = FALSE;
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
    
    UpdateBulletVelocity(BulletReference);
    UpdateBulletPosition(BulletReference);
}

u16 GetBulletSpeed(Bullet* BulletReference, const bool IsDiagonal)
{
    if (IsDiagonal)
    {  
        return F16_mul(DIAGONAL_FIX, BulletReference->_Attribute._Speed);
    }

    return BulletReference->_Attribute._Speed;
}

void UpdateBulletVelocity(Bullet* BulletReference)
{
    if (!BulletReference) { return; };

    const fix16 bulletSpeed = GetBulletSpeed(BulletReference, (BulletReference->_Direction._X != FIX16(0) && BulletReference->_Direction._Y != FIX16(0)));

    BulletReference->_Velocity._X = F16_mul(bulletSpeed, BulletReference->_Direction._X);
    BulletReference->_Velocity._Y = F16_mul(bulletSpeed, BulletReference->_Direction._Y);
}

void UpdateBulletPosition(Bullet* BulletReference)
{
    if (!BulletReference) { return; };

    BulletReference->_Node._Position._X = BulletReference->_Node._Position._X + BulletReference->_Velocity._X;
    BulletReference->_Node._Position._Y = BulletReference->_Node._Position._Y + BulletReference->_Velocity._Y;

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