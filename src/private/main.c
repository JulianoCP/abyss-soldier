#include "public/main.h"

u16 VRAMTileIndex = TILE_USER_INDEX;

int main(bool HardReset)
{
    SYS_disableInts();

    if (!HardReset) 
    {
        SYS_hardReset(); 
    }
    
    GameInit();

    while (TRUE)
    {
        UpdateWave(&Player);
        UpdatePlayer(Enemies, EnemyCount);
        
        SPR_update();
        SYS_doVBlankProcess();
    }

    return 0;
}

void GameInit()
{
	SPR_init();
    SYS_enableInts();
    SYS_showFrameLoad(true);

    VDP_setScreenHeight224();
    VDP_setScreenWidth320();
    
    VRAMTileIndex += MapInit(VRAMTileIndex);
    VRAMTileIndex += PlayerInit(VRAMTileIndex);
    VRAMTileIndex += WaveManagerInit(VRAMTileIndex);
    
    SYS_doVBlankProcess();
}