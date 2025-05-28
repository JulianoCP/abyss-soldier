#include "public/node.h"

u16 NodeInit(Node* NodeReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const u8 PaletteValue, u16 VRAMIndex)
{
    NodeReference->_Position._Y = PositionValue._Y;
    NodeReference->_Position._X = PositionValue._X;

    NodeReference->_Sprite = SPR_addSprite(SpriteValue, NodeReference->_Position._X, NodeReference->_Position._Y, TILE_ATTR_FULL(PaletteValue, FALSE, FALSE, FALSE, VRAMIndex));
   
    PAL_setPalette(PaletteValue, SpriteValue->palette->data, FALSE);
    SPR_setPosition(NodeReference->_Sprite, F16_toInt(NodeReference->_Position._X), F16_toInt(NodeReference->_Position._Y));

    NodeReference->_Dimension._W = NodeReference->_Sprite->definition->w;
    NodeReference->_Dimension._H = NodeReference->_Sprite->definition->h;

    return NodeReference->_Sprite->definition->maxNumTile;
}

Position MakePosition(fix16 X, fix16 Y)
{
    Position positionResult = { ._X = X, ._Y = Y };
    return positionResult;
}

Direction MakeDirection(fix16 X, fix16 Y)
{
    Direction directionResult = { ._X = X, ._Y = Y };
    return directionResult;
}

Attribute MakeAttribute(fix16 Speed, fix16 Health, fix16 Damage)
{
    Attribute newAttribute = { ._Speed = Speed, ._Health = Health, ._Damage = Damage };
    return newAttribute;
}

Position GetSafeRandomScreenPosition()
{
    Position positionResult;

    u16 minX = WALL_BLOCK_SIZE;
    u16 maxX = SCREEN_W - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION);

    u16 minY = WALL_BLOCK_SIZE;
    u16 maxY = SCREEN_H - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION);

    positionResult._X = FIX16(minX + (random() % (maxX - minX)));
    positionResult._Y = FIX16(minY + (random() % (maxY - minY)));

    return positionResult;
}
