#include "public/main.h"

s16 VRAMTileIndex = TILE_USER_INDEX;

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
        UpdateController(Enemies, EnemyCount);
        
        SPR_update();
        SYS_doVBlankProcess();
        VDP_waitVSync();
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
    VRAMTileIndex += ControllerInit(VRAMTileIndex);
    VRAMTileIndex += WaveManagerInit(VRAMTileIndex);
}