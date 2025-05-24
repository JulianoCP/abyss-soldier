#include <genesis.h>
#include <sprite_eng.h>

#include "public/node.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

typedef struct 
{
    s8 _X;
    s8 _Y;

} Direction;

typedef struct 
{
    fix16 _X;
    fix16 _Y;

} Input;

typedef struct 
{
    fix16 _X;
    fix16 _Y;

} Velocity;

typedef struct 
{
    fix16 _Speed;
    fix16 _Health;

} Attribute;

typedef struct 
{
    Node _Node;
    Direction _Direction;
    Input _Input;
    Attribute _Attribute;
    Velocity _Velocity;
    
} Character;

u16 CharacterInit(Character* NodeReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const u16 PaletteValue, u16 VRAMIndex);

Input MakeInput(f16 X, f16 Y);
Attribute MakeAttribute(f16 Speed, f16 Health);

u16 GetCharacterSpeed(Character* CharacterReference, const bool IsDiagonal);

void ClearCharacterInputs(Character* CharacterReference);
void ProcessCharacterInputs(Character* CharacterReference);

void UpdateCharacterPosition(Character* CharacterReference);
void UpdateCharacterRotation(Character* CharacterReference);

#endif