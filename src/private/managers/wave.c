#include "public/managers/wave.h"

s16 EnemyCount = 0;
Character* Enemies[MAX_ENEMIES];

s16 WaveManagerInit(s16 VRAMIndex)
{
    if (EnemyCount >= MAX_ENEMIES || MAX_ENEMIES <= 0)
    {
        return VRAMIndex;
    }

    while (MAX_ENEMIES > EnemyCount)
    {
        VRAMIndex += AddEnemy(VRAMIndex);
        EnemyCount++;
    }
    
    return VRAMIndex;
}

s16 AddEnemy(s16 VRAMIndex)
{
    Character* newEnemy = malloc(sizeof(Character));

    if (!newEnemy)
    {
        return VRAMIndex;
    }

    Enemies[EnemyCount] = newEnemy;
    return EnemyInit(VRAMIndex, newEnemy);
}

void UpdateWave(Character* PlayerReference)
{
     for (s16 enemyIndex = 0; enemyIndex < EnemyCount; enemyIndex++)
    {
        Character* enemyReference = Enemies[enemyIndex];

        if (!enemyReference)
        {
            continue;
        }

        UpdateEnemy(enemyReference, PlayerReference);
    }
}