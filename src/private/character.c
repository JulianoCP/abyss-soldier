#include "public/character.h"

u16 CharacterInit(Character* CharacterReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const u16 PaletteValue, u16 VRAMIndex)
{
    CharacterReference->_Input._X = FIX16(0);
    CharacterReference->_Input._Y = FIX16(0);

    CharacterReference->_Velocity._X = FIX16(0);
    CharacterReference->_Velocity._Y = FIX16(0);

    CharacterReference->_Attribute._Speed = AttributeValue._Speed;
    CharacterReference->_Attribute._Health = AttributeValue._Health;

    return NodeInit(&CharacterReference->_Node, SpriteValue, PositionValue, PaletteValue, VRAMIndex);
}

Attribute MakeAttribute(f16 Speed, f16 Health)
{
    Attribute newAttribute = { ._Speed = Speed, ._Health = Health };
    return newAttribute;
}

Input MakeInput(f16 X, f16 Y)
{
    Input newInput = { ._X = X, ._Y = Y };
    return newInput;
}

void ClearCharacterInputs(Character* CharacterReference)
{
    CharacterReference->_Input._X = FIX16(0);
    CharacterReference->_Input._Y = FIX16(0);
}

u16 GetCharacterSpeed(Character* CharacterReference, const bool IsDiagonal)
{
    if (IsDiagonal)
    {  
        return F16_mul(FIX16(0.70710678), CharacterReference->_Attribute._Speed);
    }

    return CharacterReference->_Attribute._Speed;
}

void ProcessCharacterInputs(Character* CharacterReference)
{
    fix16 characterSpeed = GetCharacterSpeed(CharacterReference, (CharacterReference->_Input._X != 0 && CharacterReference->_Input._Y != 0));

    CharacterReference->_Velocity._X = F16_mul(characterSpeed, CharacterReference->_Input._X);
    CharacterReference->_Velocity._Y = F16_mul(characterSpeed, CharacterReference->_Input._Y);
}

void UpdateCharacterPosition(Character* CharacterReference)
{
    ProcessCharacterInputs(CharacterReference);

    fix16 newX = CharacterReference->_Node._Position._X + CharacterReference->_Velocity._X;
    fix16 newY = CharacterReference->_Node._Position._Y + CharacterReference->_Velocity._Y;

    if (newX < FIX16(PLAYER_DIMENSION)) { newX = FIX16(PLAYER_DIMENSION); };
    if (newX > FIX16(SCREEN_W - F16_toInt(PLAYER_DIMENSION))) { newX = FIX16(SCREEN_W - F16_toInt(PLAYER_DIMENSION)); };

    if (newY < FIX16(PLAYER_DIMENSION)) { newY = FIX16(PLAYER_DIMENSION); };
    if (newY > FIX16(SCREEN_H - F16_toInt(PLAYER_DIMENSION))) { newY = FIX16(SCREEN_H - F16_toInt(PLAYER_DIMENSION)); };

    CharacterReference->_Node._Position._X = newX;
    CharacterReference->_Node._Position._Y = newY;

    SPR_setPosition(CharacterReference->_Node._Sprite, F16_toInt(CharacterReference->_Node._Position._X), F16_toInt(CharacterReference->_Node._Position._Y));
}