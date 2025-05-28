#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/node.h"

#ifndef _BULLET_H_
#define _BULLET_H_

typedef struct 
{
    Node _Node;
    Attribute _Attribute;
    Direction _Direction;
    bool _IsActive; 
    
} Bullet;

u16 BulletInit(Bullet* BulletReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const u16 PaletteValue, u16 VRAMIndex);

#endif