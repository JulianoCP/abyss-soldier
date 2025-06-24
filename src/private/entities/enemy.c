#include "public/entities/enemy.h"

s16 EnemyInit(s16 VRAMIndex, Character* EnemyReference)
{
    if (!EnemyReference) { return VRAMIndex; };

    VRAMIndex += CharacterInit(EnemyReference, &EnemySprite, GetSafeRandomScreenPosition(), MakeAttribute(FIX16(INIT_ENEMY_SPEED), FIX16(INIT_ENEMY_HEALTH), FIX16(INIT_ENEMY_DAMAGE)), PAL_ENTITIES, VRAMIndex);
    ActivateCharacter(EnemyReference);

    return VRAMIndex;
}

void RespawnEnemy(Character* EnemyReference)
{
    if (!EnemyReference) { return; };

    Position randomPosition = GetSafeRandomScreenPosition();
    
    EnemyReference->_Node._Position._Y = randomPosition._Y;
    EnemyReference->_Node._Position._X = randomPosition._X;
    
    EnemyReference->_Attribute._Speed = FIX16(INIT_ENEMY_SPEED);
    EnemyReference->_Attribute._Health = FIX16(INIT_ENEMY_HEALTH);
    EnemyReference->_Attribute._Damage = FIX16(INIT_ENEMY_DAMAGE);
    
    ActivateCharacter(EnemyReference);
    UpdateCharacterPosition(EnemyReference);
}

void UpdateEnemy(Character* EnemyReference, Character* PlayerReference)
{
    if (!EnemyReference) { return; };

    UpdateEnemyState(EnemyReference);
    UpdateEnemyInputs(EnemyReference, PlayerReference);

    UpdateCharacterPosition(EnemyReference);
    EnemyCheckHitPlayer(EnemyReference, PlayerReference);
}

void EnemyCheckHitPlayer(Character* EnemyReference, Character* PlayerReference)
{
    if (!EnemyReference || !EnemyReference->_IsActive) { return; }
    else if (!PlayerReference || !PlayerReference->_IsActive) { return; }

    fix16 distanceToX = PlayerReference->_Node._Position._X - EnemyReference->_Node._Position._X;
    fix16 distanceToY = PlayerReference->_Node._Position._Y - EnemyReference->_Node._Position._Y;
    
    s16 resultToX = ABS(F16_toInt(distanceToX));
    s16 resultToY = ABS(F16_toInt(distanceToY));
    
    if (resultToX <= ENEMY_HIT_RADIUS && resultToY <= ENEMY_HIT_RADIUS)
    {
        ApplyCharacterDamage(EnemyReference, EnemyReference->_Attribute._Health);
        ApplyCharacterDamage(PlayerReference, EnemyReference->_Attribute._Damage);
        return;
    }
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
           
            if (EnemyReference->_RespawnTimer <= 0)
            {
                RespawnEnemy(EnemyReference);
            }
        }
    }
}

void UpdateEnemyInputs(Character* EnemyReference, Character* PlayerReference)
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