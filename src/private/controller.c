#include "public/controller.h"

Character Player;

u16 ControllerInit(u16 VRAMIndex)
{
    return PlayerInit(VRAMIndex, &Player);
}

void UpdateController(Character* ListOfEnemies[], u16 EnemyCount)
{
    UpdatePlayer(&Player, ListOfEnemies, EnemyCount);
}