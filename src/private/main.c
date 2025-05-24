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
        PlayerUpdate();
        
        SPR_update();
        SYS_doVBlankProcess();
    }

    return 0;
}

void GameInit()
{
	SPR_init();
    SYS_enableInts();

    VDP_setScreenHeight224();
    VDP_setScreenWidth320();

    VRAMTileIndex += MapInit(VRAMTileIndex);
    VRAMTileIndex += PlayerInit(VRAMTileIndex);
}