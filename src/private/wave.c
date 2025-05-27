#include "public/wave.h"

int EnemyCount = 0;
Character* Enemies[MAX_ENEMIES];

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

u16 WaveManagerInit(u16 VRAMIndex)
{
    if (EnemyCount >= MAX_ENEMIES)
    {
        return VRAMIndex;
    }

    return AddEnemy(VRAMIndex);
}

u16 AddEnemy(u16 VRAMIndex)
{
    Character* newEnemy = malloc(sizeof(Character));

    if (!newEnemy)
    {
        return VRAMIndex;
    }

    Enemies[EnemyCount] = newEnemy;
    EnemyCount++;

    return EnemyInit(VRAMIndex, newEnemy);
}