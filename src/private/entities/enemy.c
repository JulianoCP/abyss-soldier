#include "public/entities/enemy.h"

const EnemyPreset EnemyPresets[NUM_ENEMY_PRESETS] = {
    { .Damage = 5, .Speed = 3, .Health = 20, .Frame = 0 },
    { .Damage = 10, .Speed = 5, .Health = 15, .Frame = 1 },
    { .Damage = 5, .Speed = 2, .Health = 60, .Frame = 2 }
};

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

    EnemyPreset presetData = EnemyPresets[(random() % NUM_ENEMY_PRESETS)];

    EnemyReference->_Attribute._Speed = FIX16(presetData.Speed);
    EnemyReference->_Attribute._Health = FIX16(presetData.Health);
    EnemyReference->_Attribute._Damage = FIX16(presetData.Damage);
    
    SPR_setFrame(EnemyReference->_Node._Sprite, presetData.Frame);

    ActivateCharacter(EnemyReference);
    UpdateCharacterPosition(EnemyReference);
}

void PredictRespawnLocation(Character* EnemyReference)
{
    if (!EnemyReference) { return; };

    Position randomPosition = GetSafeRandomScreenPosition();
    
    EnemyReference->_Node._Position._Y = randomPosition._Y;
    EnemyReference->_Node._Position._X = randomPosition._X;

    SPR_setFrame(EnemyReference->_Node._Sprite, 3);
    SPR_setPosition(EnemyReference->_Node._Sprite, F16_toInt(EnemyReference->_Node._Position._X), F16_toInt(EnemyReference->_Node._Position._Y));
    SPR_setVisibility(EnemyReference->_Node._Sprite, VISIBLE);
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
            EnemyReference->_RespawnTimer = RESPAWN_TIME;

            DeactivateCharacter(EnemyReference);
            PredictRespawnLocation(EnemyReference);
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