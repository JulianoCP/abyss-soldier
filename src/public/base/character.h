#include <genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include <tools.h>

#include "public/base/node.h"

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

typedef struct 
{
    Node _Node;
    Attribute _Attribute;
    Input _Input;
    Direction _Direction;
    
} Character;

s16 CharacterInit(Character* NodeReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const s16 PaletteValue, s16 VRAMIndex);

Input MakeInput(const fix16 X, const fix16 Y, const bool IsFiring);
fix16 GetCharacterSpeed(Character* CharacterReference);

void UpdateCharacterPosition(Character* CharacterReference);
void ClearCharacterInputs(Character* CharacterReference);

#endif