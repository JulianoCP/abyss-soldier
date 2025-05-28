#include "public/character.h"

u16 CharacterInit(Character* CharacterReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const u16 PaletteValue, u16 VRAMIndex)
{
    ClearCharacterInputs(CharacterReference);

    CharacterReference->_Attribute._Speed = AttributeValue._Speed;
    CharacterReference->_Attribute._Health = AttributeValue._Health;

    return NodeInit(&CharacterReference->_Node, SpriteValue, PositionValue, PaletteValue, VRAMIndex);
}

Input MakeInput(fix16 X, fix16 Y, bool IsFiring)
{
    Input newInput = { ._X = X, ._Y = Y, ._IsFiring = IsFiring };
    return newInput;
}

void ClearCharacterInputs(Character* CharacterReference)
{
    CharacterReference->_Input._X = FIX16(0);
    CharacterReference->_Input._Y = FIX16(0);
    CharacterReference->_Input._IsFiring = FALSE;

    CharacterReference->_Velocity._X = FIX16(0);
    CharacterReference->_Velocity._Y = FIX16(0);
}

u16 GetCharacterSpeed(Character* CharacterReference, const bool IsDiagonal)
{
    if (IsDiagonal)
    {  
        return F16_mul(DIAGONAL_FIX, CharacterReference->_Attribute._Speed);
    }

    return CharacterReference->_Attribute._Speed;
}

void UpdateCharacterVelocity(Character* CharacterReference)
{
    const fix16 characterSpeed = GetCharacterSpeed(CharacterReference, (CharacterReference->_Input._X != FIX16(0) && CharacterReference->_Input._Y != FIX16(0)));

    CharacterReference->_Velocity._X = F16_mul(characterSpeed, CharacterReference->_Input._X);
    CharacterReference->_Velocity._Y = F16_mul(characterSpeed, CharacterReference->_Input._Y);
}

void UpdateCharacterPosition(Character* CharacterReference)
{
    UpdateCharacterVelocity(CharacterReference);

    fix16 newX = CharacterReference->_Node._Position._X + CharacterReference->_Velocity._X;
    fix16 newY = CharacterReference->_Node._Position._Y + CharacterReference->_Velocity._Y;

    if (newX < FIX16(WALL_BLOCK_SIZE)) { newX = FIX16(WALL_BLOCK_SIZE); }
    else if (newX > FIX16(SCREEN_W - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION))) { newX = FIX16(SCREEN_W - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION)); };

    if (newY < FIX16(WALL_BLOCK_SIZE)) { newY = FIX16(WALL_BLOCK_SIZE); }
    else if (newY > FIX16(SCREEN_H - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION))) { newY = FIX16(SCREEN_H - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION)); };

    CharacterReference->_Node._Position._X = newX;
    CharacterReference->_Node._Position._Y = newY;

    SPR_setPosition(CharacterReference->_Node._Sprite, F16_toInt(CharacterReference->_Node._Position._X), F16_toInt(CharacterReference->_Node._Position._Y));
}