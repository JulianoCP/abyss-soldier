#include "public/enemy.h"

u16 EnemyInit(u16 VRAMIndex, Character* EnemyReference)
{
    VRAMIndex += CharacterInit(EnemyReference, &EnemyImage, MakePosition(FIX16((SCREEN_W / 4 ) - 16), FIX16((SCREEN_H / 4 ) - 16)), MakeAttribute(FIX16(INIT_ENEMY_SPEED), FIX16(INIT_ENEMY_HEALTH)), PAL_ENEMY, VRAMIndex);
    return VRAMIndex;
}