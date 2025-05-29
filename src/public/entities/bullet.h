#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/base/node.h"

#ifndef _BULLET_H_
#define _BULLET_H_

typedef struct 
{
    Node _Node;
    Attribute _Attribute;
    Direction _Direction;
    bool _IsActive;
    
} Bullet;

s16 BulletInit(Bullet* BulletReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const s16 PaletteValue, s16 VRAMIndex);

void UpdateBullet(Bullet* BulletReference);
void UpdateBulletPosition(Bullet* BulletReference);

void DeactivateBullet(Bullet* BulletReference);
void ActivateBullet(Bullet* BulletReference, const Position PositionValue, const Direction DirectionValue);

#endif