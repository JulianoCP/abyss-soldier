#include "public/enemy.h"

u16 EnemyInit(u16 VRAMIndex, Character* EnemyReference)
{
    VRAMIndex += CharacterInit(EnemyReference, &EnemySprite, GetSafeRandomScreenPosition(), MakeAttribute(FIX16(INIT_ENEMY_SPEED), FIX16(INIT_ENEMY_HEALTH), FIX16(5)), PAL_ENEMY, VRAMIndex);
    return VRAMIndex;
}

void UpdateEnemy(Character* EnemyReference, const Character* PlayerReference)
{
    UpdateEnemyInputs(EnemyReference, PlayerReference);
    UpdateCharacterPosition(EnemyReference);
}

void UpdateEnemyInputs(Character* EnemyReference, const Character* PlayerReference)
{
    if (!EnemyReference) { return; };
    
    ClearCharacterInputs(EnemyReference);

    // EnemyReference->_Direction._X = PlayerReference->_Node._Position._X - EnemyReference->_Node._Position._X;
    // EnemyReference->_Direction._Y = PlayerReference->_Node._Position._Y - EnemyReference->_Node._Position._Y;

    // if (EnemyReference->_Direction._X < -1) { EnemyReference->_Input._X = -1; }
    // else if (EnemyReference->_Direction._X > 1) { EnemyReference->_Input._X = 1; };

    // if (EnemyReference->_Direction._Y < -1) { EnemyReference->_Input._Y = -1; }
    // else if (EnemyReference->_Direction._Y > 1) { EnemyReference->_Input._Y = 1; };
}