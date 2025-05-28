#include "public/bullet.h"

u16 BulletInit(Bullet* BulletReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const u16 PaletteValue, u16 VRAMIndex)
{
    BulletReference->_IsActive = FALSE;
    BulletReference->_Attribute._Speed = AttributeValue._Speed;
    BulletReference->_Attribute._Health = AttributeValue._Health;

    u16 vramResult = NodeInit(&BulletReference->_Node, SpriteValue, PositionValue, PaletteValue, VRAMIndex);
    SPR_setVisibility(BulletReference->_Node._Sprite, HIDDEN);

    return vramResult;
}