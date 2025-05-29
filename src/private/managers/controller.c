#include "public/managers/controller.h"

Character Player;

s16 ControllerInit(s16 VRAMIndex)
{
    return PlayerInit(VRAMIndex, &Player);
}

void UpdateController(Character* ListOfEnemies[], s16 EnemyCount)
{
    UpdatePlayer(&Player, ListOfEnemies, EnemyCount);
}