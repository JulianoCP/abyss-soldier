#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "resource.h"
#include "public/library.h"

#ifndef _NODE_H_
#define _NODE_H_

typedef struct 
{
	u16 _H;
	u16 _W;

} Dimension;

typedef struct 
{
    fix16 _Speed;
    fix16 _Health;
    fix16 _Damage;

} Attribute;

typedef struct 
{
	fix16 _X;
	fix16 _Y;

} Position;

typedef struct 
{
	Sprite* _Sprite;
    Position _Position;
    Dimension _Dimension;

} Node;

u16 NodeInit(Node* NodeReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const u8 PaletteValue, u16 VRAMIndex);

Position GetSafeRandomScreenPosition();
Attribute MakeAttribute(fix16 Speed, fix16 Health, fix16 Damage);
Position MakePosition(fix16 X, fix16 Y);

#endif