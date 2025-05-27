#include <genesis.h>
#include <sprite_eng.h>

#include "public/node.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

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
    Attribute _Attribute;
    Input _Input;
    Velocity _Velocity;
    
} Character;

u16 CharacterInit(Character* NodeReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const u16 PaletteValue, u16 VRAMIndex);

Input MakeInput(fix16 X, fix16 Y);
Attribute MakeAttribute(fix16 Speed, fix16 Health);
u16 GetCharacterSpeed(Character* CharacterReference, const bool IsDiagonal);

void UpdateCharacterPosition(Character* CharacterReference);
void ClearCharacterInputs(Character* CharacterReference);
void ProcessCharacterInputs(Character* CharacterReference);

#endif