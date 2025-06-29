#include "public/entities/player.h"

s16 BulletCount = 0;
Bullet* Bullets[MAX_BULLETS];

s16 ShootingCooldown = 0;
s16 ChooseTargetCooldown = 0;

const fix16 DIRECTION_X_TABLE[8] = { FIX16(1.0),  FIX16(0.707), FIX16(0.0),   FIX16(-0.707), FIX16(-1.0), FIX16(-0.707), FIX16(0.0),  FIX16(0.707) };
const fix16 DIRECTION_Y_TABLE[8] = { FIX16(0.0),  FIX16(-0.707), FIX16(-1.0), FIX16(-0.707), FIX16(0.0),  FIX16(0.707),  FIX16(1.0),  FIX16(0.707) };

s16 PlayerInit(s16 VRAMIndex, Character* PlayerReference)
{
    if (!PlayerReference) { return VRAMIndex; };
    
    VRAMIndex += CharacterInit(PlayerReference, &SoldierSprite, MakePosition(FIX16((SCREEN_W / 2 ) - 16), FIX16((SCREEN_H / 2 ) - 16)), MakeAttribute(FIX16(INIT_PLAYER_SPEED), FIX16(INIT_PLAYER_HEALTH), FIX16(INIT_PLAYER_DAMAGE)), PAL_ENTITIES, VRAMIndex);
    
    UpdateHUDInfo(PlayerReference);
    ActivateCharacter(PlayerReference);

    while (MAX_BULLETS > BulletCount)
    {
        VRAMIndex += AddPlayerBullet(VRAMIndex, PlayerReference);
        BulletCount++;
    }

    return VRAMIndex;
}

s16 AddPlayerBullet(s16 VRAMIndex, Character* PlayerReference)
{
    if (!PlayerReference) { return VRAMIndex; };

    Bullet* newBullet = malloc(sizeof(Bullet));

    if (!newBullet)
    {
        return VRAMIndex;
    }

    Bullets[BulletCount] = newBullet;
    return BulletInit(newBullet, &BulletSprite, PlayerReference->_Node._Position, MakeAttribute(FIX16(BULLET_SPEED), FIX16(0), FIX16(INIT_PLAYER_DAMAGE)), PAL_ENTITIES, VRAMIndex);
}

void UpdateHUDInfo(Character* PlayerReference)
{
    if (!PlayerReference) { return; };

    char waveText[8];
    u8 currentWave = PlayerReference->_KillCount / 30 + 1;

    if (currentWave <= 2)
    {
        strcpy(waveText, "WAVE ");
        waveText[5] = '0' + currentWave;
        waveText[6] = '\0';

        VDP_clearTextArea(17, 3, 6, 1);
        VDP_drawText(waveText, 17, 3);
    }
    else
    {
        VDP_clearTextArea(15, 3, 12, 1);
        VDP_drawText("WAVE FINAL", 15, 3);
    }

    char killText[8];
    char countStr[6];

    intToStr(PlayerReference->_KillCount, countStr, 1);

    strcpy(killText, countStr);
    strcat(killText, "x");

    VDP_clearTextArea(34, 3, 6, 1);
    VDP_setTextPalette(PAL_HUD);
    PAL_setColor(PAL_HUD*16+15, RGB24_TO_VDPCOLOR(0x8000FF));
    VDP_drawText(killText, 34, 3);

    char hpText[8];
    char hpStr[6];

    intToStr(F16_toInt(PlayerReference->_Attribute._Health), hpStr, 1);
    strcpy(hpText, "HP ");
    strcat(hpText, hpStr);

    VDP_clearTextArea(3, 3, 6, 1);
    VDP_drawText(hpText, 3, 3);

    TotalKills = PlayerReference->_KillCount;
    
    if (PlayerReference->_KillCount >= KILLS_TO_WIN)
    {
        Victory = TRUE;
        GameOver = TRUE;
    }
}

void UpdatePlayer(Character* PlayerReference, Character* ListOfEnemies[], const s16 EnemyCount)
{
    if (!PlayerReference) { return; };

    UpdatePlayerInputs(PlayerReference);
    UpdateHUDInfo(PlayerReference);
    UpdateCharacterPosition(PlayerReference);
    
    UpdatePlayerBullets(PlayerReference, ListOfEnemies, EnemyCount);
    UpdatePlayerTarget(PlayerReference, ListOfEnemies, EnemyCount);

    UpdatePlayerState(PlayerReference);
}

void UpdatePlayerState(Character* PlayerReference)
{
    if (!PlayerReference) { return; };

    if (PlayerReference->_IsActive)
    {
        if (PlayerReference->_Attribute._Health <= 0)
        {
            DeactivateCharacter(PlayerReference);

            Victory = FALSE;
            GameOver = TRUE;
        }
    }
}

void UpdatePlayerBullets(Character* PlayerReference, Character* ListOfEnemies[], const s16 EnemyCount)
{
    if (!PlayerReference) { return; };

    for (s16 bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
    {
        UpdateBullet(PlayerReference, Bullets[bulletIndex], ListOfEnemies, EnemyCount);
    }

    UpdatePlayerShooting(PlayerReference);
}

void UpdatePlayerTarget(Character* PlayerReference, Character* ListOfEnemies[], const s16 EnemyCount)
{
    if (!PlayerReference) { return; }
    else if (ChooseTargetCooldown > 0) { ChooseTargetCooldown--; return; };

    const Character* targetReference = FindNearbyTarget(PlayerReference, ListOfEnemies, EnemyCount);
    
    if (!targetReference)
    {
        return;
    }
    
    s16 directionIndex = GetDirectionIndex(F16_toInt(targetReference->_Node._Position._X - PlayerReference->_Node._Position._X), F16_toInt(targetReference->_Node._Position._Y - PlayerReference->_Node._Position._Y));
    ChooseTargetCooldown = CHANGE_TARGET_COOLDOWN;
    
    PlayerReference->_Direction._X = DIRECTION_X_TABLE[directionIndex];
    PlayerReference->_Direction._Y = DIRECTION_Y_TABLE[directionIndex];
    
    SPR_setAnim(PlayerReference->_Node._Sprite, directionIndex);
}

void UpdatePlayerShooting(Character* PlayerReference)
{
    if (!PlayerReference) { return; }
    else if (ShootingCooldown > 0) { ShootingCooldown--; return; }
    else if (PlayerReference->_Direction._X == 0 && PlayerReference->_Direction._Y == 0) { return; };
    
    for (s16 bulletIndex = 0; bulletIndex < MAX_BULLETS; bulletIndex++)
    {
        if (!Bullets[bulletIndex] || Bullets[bulletIndex]->_IsActive)
        {
            continue;
        }
        
        ActivateBullet(Bullets[bulletIndex], PlayerReference->_Node._Position, PlayerReference->_Direction);
        ShootingCooldown = SHOT_COOLDOWN;
        return;
    }
}

void UpdatePlayerInputs(Character* PlayerReference) 
{
    if (!PlayerReference) { return; };

    ClearCharacterInputs(PlayerReference);

    for (s16 joyIndex = (NUMBER_OF_JOYPADS - 1); joyIndex >= 0; --joyIndex) 
    {
		OldButtons[joyIndex] = CurrentButtons[joyIndex];
		CurrentButtons[joyIndex] = JOY_readJoypad(joyIndex);
	}
    
    if (IsKeyDown(JOY_1, BUTTON_LEFT)) { PlayerReference->_Input._X = -1; }
    else if (IsKeyDown(JOY_1, BUTTON_RIGHT)) { PlayerReference->_Input._X = 1; }

    if (IsKeyDown(JOY_1, BUTTON_UP)) { PlayerReference->_Input._Y = -1; }
    else if (IsKeyDown(JOY_1, BUTTON_DOWN)) { PlayerReference->_Input._Y = 1; }
}

Character* FindNearbyTarget(Character* PlayerReference, Character* ListOfEnemies[], const s16 EnemyCount)
{
    if (EnemyCount == 0) { return NULL; }

    Character* closestEnemy = NULL;
    fix16 closestDist = FIX16(9999);

    for (s16 enemyIndex = 0; enemyIndex < EnemyCount; enemyIndex++)
    {
        Character* enemyReference = ListOfEnemies[enemyIndex];

        if (!enemyReference || !enemyReference->_IsActive)
        {
            continue;
        }

        fix16 distResult = GetDistanceSquared(PlayerReference, enemyReference->_Node._Position);

        if (distResult < closestDist)
        {
            closestDist = distResult;
            closestEnemy = enemyReference;
        }
    }
    
    return closestEnemy;
}

fix16 GetDistanceSquared(Character* PlayerReference, const Position TargetPosition)
{
    const fix16 distanceToX = PlayerReference->_Node._Position._X - TargetPosition._X;
    const fix16 distanceToY = PlayerReference->_Node._Position._Y - TargetPosition._Y;

    return F16_mul(distanceToX, distanceToX) + F16_mul(distanceToY, distanceToY);
}

s16 GetDirectionIndex(const s16 X, const s16 Y)
{
    if (X != 0 || Y != 0)
    {
        if (ABS(X) > ABS(Y))
        {
            if ((ABS(Y) * DIRECTION_TOLERANCE) < ABS(X)) { return X > 0 ? 0 : 4; }
            else { return X > 0 ? (Y < 0 ? 1 : 7) : (Y < 0 ? 3 : 5); };
        }
        else
        {
            if ((ABS(X) * DIRECTION_TOLERANCE) < ABS(Y)) { return Y < 0 ? 2 : 6; }
            else { return X > 0 ? (Y < 0 ? 1 : 7) : (Y < 0 ? 3 : 5); };
        }
    }

    return 0;
}