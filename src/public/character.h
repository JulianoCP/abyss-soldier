#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/node.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

typedef struct 
{
    fix16 _X;
    fix16 _Y;
    bool _IsFiring;

} Input;

typedef struct 
{
    Node _Node;
    Attribute _Attribute;
    Input _Input;
    Velocity _Velocity;
    Direction _Direction;
    
} Character;

u16 CharacterInit(Character* NodeReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const u16 PaletteValue, u16 VRAMIndex);

Input MakeInput(const fix16 X, const fix16 Y, const bool IsFiring);
fix16 GetCharacterSpeed(Character* CharacterReference, const bool IsDiagonal);

void UpdateCharacterPosition(Character* CharacterReference);
void ClearCharacterInputs(Character* CharacterReference);
void UpdateCharacterVelocity(Character* CharacterReference);

#endif