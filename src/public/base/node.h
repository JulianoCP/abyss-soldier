#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/utils/library.h"

#ifndef _NODE_H_
#define _NODE_H_

typedef struct 
{
	u16 _H;
	u16 _W;

} Dimension;

typedef struct 
{
	fix16 _X;
	fix16 _Y;

} Direction;

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
    fix16 _X;
    fix16 _Y;

} Velocity;

typedef struct 
{
	Sprite* _Sprite;
    Position _Position;
    Dimension _Dimension;

} Node;

u16 NodeInit(Node* NodeReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const u8 PaletteValue, u16 VRAMIndex);

Position MakePosition(const fix16 X, const fix16 Y);
Direction MakeDirection(const fix16 X, const fix16 Y);

Position GetSafeRandomScreenPosition();
Attribute MakeAttribute(const fix16 Speed, const fix16 Health, const fix16 Damage);

#endif