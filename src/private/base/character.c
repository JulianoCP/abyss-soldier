#include "public/base/character.h"

s16 CharacterInit(Character* CharacterReference, const SpriteDefinition* SpriteValue, const Position PositionValue, const Attribute AttributeValue, const s16 PaletteValue, s16 VRAMIndex)
{
    if (!CharacterReference) { return VRAMIndex; };

    ClearCharacterInputs(CharacterReference);

    CharacterReference->_Attribute._Speed = AttributeValue._Speed;
    CharacterReference->_Attribute._Health = AttributeValue._Health;
    CharacterReference->_Attribute._Damage = AttributeValue._Damage;

    return NodeInit(&CharacterReference->_Node, SpriteValue, PositionValue, PaletteValue, VRAMIndex);
}

void ClearCharacterInputs(Character* CharacterReference)
{
    if (!CharacterReference) { return; };

    CharacterReference->_Input._X = FIX16(0);
    CharacterReference->_Input._Y = FIX16(0);
    CharacterReference->_Input._IsFiring = FALSE;
}

void ApplyCharacterDamage(Character* CharacterReference, const fix16 DamageValue)
{
    if (!CharacterReference) { return; };
    
    CharacterReference->_Attribute._Health = (CharacterReference->_Attribute._Health - DamageValue);
}

fix16 GetCharacterSpeed(Character* CharacterReference)
{
    if (!CharacterReference) { return FIX16(0); };

    const bool IsDiagonal = (CharacterReference->_Input._X != FIX16(0) && CharacterReference->_Input._Y != FIX16(0));

    return IsDiagonal ? F16_mul(DIAGONAL_FIX, CharacterReference->_Attribute._Speed) : CharacterReference->_Attribute._Speed;
}

void UpdateCharacterPosition(Character* CharacterReference)
{
    if (!CharacterReference || !CharacterReference->_IsActive) { return; }
    else if (CharacterReference->_Input._X == FIX16(0) && CharacterReference->_Input._Y == FIX16(0)) { return; };
    
    const fix16 characterSpeed = GetCharacterSpeed(CharacterReference);

    fix16 newX = CharacterReference->_Node._Position._X + F16_mul(characterSpeed, CharacterReference->_Input._X);
    fix16 newY = CharacterReference->_Node._Position._Y + F16_mul(characterSpeed, CharacterReference->_Input._Y);

    if (newX < FIX16(WALL_BLOCK_SIZE)) { newX = FIX16(WALL_BLOCK_SIZE); }
    else if (newX > FIX16(SCREEN_W - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION))) { newX = FIX16(SCREEN_W - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION)); };

    if (newY < FIX16(WALL_BLOCK_SIZE)) { newY = FIX16(WALL_BLOCK_SIZE); }
    else if (newY > FIX16(SCREEN_H - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION))) { newY = FIX16(SCREEN_H - (WALL_BLOCK_SIZE + CHARACTER_DIMENSION)); };

    CharacterReference->_Node._Position._X = newX;
    CharacterReference->_Node._Position._Y = newY;

    SPR_setPosition(CharacterReference->_Node._Sprite, F16_toInt(CharacterReference->_Node._Position._X), F16_toInt(CharacterReference->_Node._Position._Y));
}

Input MakeInput(const fix16 X, const fix16 Y, const bool IsFiring)
{
    Input newInput = { ._X = X, ._Y = Y, ._IsFiring = IsFiring };
    return newInput;
}

void DeactivateCharacter(Character* CharacterReference)
{
    if (!CharacterReference) { return; };

    CharacterReference->_IsActive = false;
    SPR_setVisibility(CharacterReference->_Node._Sprite, HIDDEN);
}

void ActivateCharacter(Character* CharacterReference)
{
    if (!CharacterReference) { return; };

    CharacterReference->_IsActive = true;
    SPR_setVisibility(CharacterReference->_Node._Sprite, VISIBLE);
}