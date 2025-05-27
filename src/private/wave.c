#include "public/wave.h"

u16 EnemyCount = 0;
Character* Enemies[MAX_ENEMIES];

u16 WaveManagerInit(u16 VRAMIndex)
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

u16 AddEnemy(u16 VRAMIndex)
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
     for (u16 enemyIndex = 0; enemyIndex < EnemyCount; enemyIndex++)
    {
        Character* enemyReference = Enemies[enemyIndex];

        if (!enemyReference)
        {
            continue;
        }

        UpdateEnemy(enemyReference, PlayerReference);
    }
}