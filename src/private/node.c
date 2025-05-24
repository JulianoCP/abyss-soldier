#include "public/node.h"

u16 NodeInit(Node* NodeReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const u8 PaletteValue, u16 VRAMIndex)
{
    NodeReference->_Position._Y = PositionValue._Y;
    NodeReference->_Position._X = PositionValue._X;

    NodeReference->_Sprite = SPR_addSprite(SpriteValue, NodeReference->_Position._X, NodeReference->_Position._Y, TILE_ATTR_FULL(PaletteValue, FALSE, FALSE, 0, VRAMIndex));
   
    PAL_setPalette(PaletteValue, SpriteValue->palette->data, FALSE);
    SPR_setPosition(NodeReference->_Sprite, F16_toInt(NodeReference->_Position._X), F16_toInt(NodeReference->_Position._Y));

    NodeReference->_Dimension._W = NodeReference->_Sprite->definition->w;
    NodeReference->_Dimension._H = NodeReference->_Sprite->definition->h;

    return NodeReference->_Sprite->definition->maxNumTile;
}

Position MakePosition(fix16 X, fix16 Y)
{
    Position newPosition = { ._X = X, ._Y = Y };
    return newPosition;
}