#include "public/entities/enemy.h"

s16 EnemyInit(s16 VRAMIndex, Character* EnemyReference)
{
    if (!EnemyReference) { return VRAMIndex; };

    VRAMIndex += CharacterInit(EnemyReference, &EnemySprite, GetSafeRandomScreenPosition(), MakeAttribute(FIX16(INIT_ENEMY_SPEED), FIX16(INIT_ENEMY_HEALTH), FIX16(5)), PAL_ENEMY, VRAMIndex);
    DeactivateCharacter(EnemyReference);

    return VRAMIndex;
}

void RespawnEnemy(Character* EnemyReference)
{
    if (!EnemyReference) { return; };

    ActivateCharacter(EnemyReference);

    Position randomPosition = GetSafeRandomScreenPosition();

    EnemyReference->_Node._Position._Y = randomPosition._Y;
    EnemyReference->_Node._Position._X = randomPosition._X;

    EnemyReference->_Attribute._Speed = FIX16(INIT_ENEMY_SPEED);
    EnemyReference->_Attribute._Health = FIX16(INIT_ENEMY_HEALTH);
}

void UpdateEnemy(Character* EnemyReference, const Character* PlayerReference)
{
    if (!EnemyReference) { return; };

    UpdateEnemyState(EnemyReference);
    UpdateEnemyInputs(EnemyReference, PlayerReference);
    UpdateCharacterPosition(EnemyReference);
}

void UpdateEnemyState(Character* EnemyReference)
{
    if (!EnemyReference) { return; };

    if (EnemyReference->_IsActive)
    {
        if (EnemyReference->_Attribute._Health <= 0)
        {
            DeactivateCharacter(EnemyReference);
            EnemyReference->_RespawnTimer = RESPAWN_TIME;
        }
    }
    else
    {  
        if (EnemyReference->_RespawnTimer > 0)
        {
            EnemyReference->_RespawnTimer--;

            if (EnemyReference->_RespawnTimer == 0)
            {
                RespawnEnemy(EnemyReference);
            }
        }
    }
}

void UpdateEnemyInputs(Character* EnemyReference, const Character* PlayerReference)
{
    if (!EnemyReference || !PlayerReference) { return; };
    
    ClearCharacterInputs(EnemyReference);

    EnemyReference->_Direction._X = PlayerReference->_Node._Position._X - EnemyReference->_Node._Position._X;
    EnemyReference->_Direction._Y = PlayerReference->_Node._Position._Y - EnemyReference->_Node._Position._Y;

    if (EnemyReference->_Direction._X < -1) { EnemyReference->_Input._X = -1; }
    else if (EnemyReference->_Direction._X > 1) { EnemyReference->_Input._X = 1; };

    if (EnemyReference->_Direction._Y < -1) { EnemyReference->_Input._Y = -1; }
    else if (EnemyReference->_Direction._Y > 1) { EnemyReference->_Input._Y = 1; };
}