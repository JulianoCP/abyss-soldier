#include "public/enemy.h"

u16 EnemyInit(u16 VRAMIndex, Character* EnemyReference)
{
    VRAMIndex += CharacterInit(EnemyReference, &EnemyImage, GetSafeRandomScreenPosition(), MakeAttribute(FIX16(INIT_ENEMY_SPEED), FIX16(INIT_ENEMY_HEALTH), FIX16(5)), PAL_ENEMY, VRAMIndex);
    return VRAMIndex;
}

void UpdateEnemy(Character* EnemyReference, const Character* PlayerReference)
{
    UpdateEnemyInputs(EnemyReference, PlayerReference);
    UpdateCharacterPosition(EnemyReference);
}

void UpdateEnemyInputs(Character* EnemyReference, const Character* PlayerReference)
{
    ClearCharacterInputs(EnemyReference);

    const s16 distanceToX = F16_toInt(PlayerReference->_Node._Position._X - EnemyReference->_Node._Position._X);
    const s16 distanceToY = F16_toInt(PlayerReference->_Node._Position._Y - EnemyReference->_Node._Position._Y);

    if (distanceToX < -1) { EnemyReference->_Input._X = -1; }
    else if (distanceToX > 1) { EnemyReference->_Input._X = 1; };

    if (distanceToY < -1) { EnemyReference->_Input._Y = -1; }
    else if (distanceToY > 1) { EnemyReference->_Input._Y = 1; };
}