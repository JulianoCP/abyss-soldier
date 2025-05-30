#include "public/main.h"

Sprite* barSprite = NULL;
s16 VRAMTileIndex = TILE_USER_INDEX;

int main(bool HardReset)
{
    SYS_disableInts();

    if (!HardReset) 
    {
        SYS_hardReset(); 
    }
    
    GameInit();

    while (!GameOver)
    {
        UpdateWave(&Player);
        UpdateController(Enemies, EnemyCount);
        
        SPR_update();
        SYS_doVBlankProcess();
    }

    ShowVictoryScreen();
    return 0;
}

void GameInit()
{
    SPR_init();
    SYS_enableInts();
    SYS_showFrameLoad(true);
    
    VDP_setScreenHeight224();
    VDP_setScreenWidth320();
    
    VRAMTileIndex = TILE_USER_INDEX;
    
    VRAMTileIndex += MapInit(VRAMTileIndex);
    VRAMTileIndex += ControllerInit(VRAMTileIndex);
    VRAMTileIndex += WaveManagerInit(VRAMTileIndex);
}

void ShowVictoryScreen()
{
    ShowVictoryBar();

    VDP_drawText("VOCE VENCEU!", 13, 13);
    VDP_drawText("PRESSIONE START", 12, 14);

    VDP_setTextPalette(PAL_HUD);
    PAL_setColor(PAL_HUD*16+15, RGB24_TO_VDPCOLOR(0x8000FF));

    while (TRUE)
    {
        SYS_doVBlankProcess();

        if (JOY_readJoypad(JOY_1) & BUTTON_START)
        {
            break;
        }
    }

    SYS_hardReset();
}

void ShowVictoryBar()
{
    ClearGameScreen();
    
    VDP_drawImageEx(BG_MAP, &VictorySprite, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, 0), 0, 0, TRUE, FALSE);
    VDP_setScrollingMode(HSCROLL_LINE , VSCROLL_PLANE);
}

void ClearGameScreen()
{
    SPR_reset();
    SPR_update();
    
    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);
    
    VDP_clearTextArea(0, 0, 40, 28);
}