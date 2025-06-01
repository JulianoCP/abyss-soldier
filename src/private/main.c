#include "public/main.h"

Sprite* barSprite = NULL;
s16 VRAMTileIndex = TILE_USER_INDEX;

int main(bool HardReset)
{
    if (!HardReset) 
    {
        SYS_hardReset(); 
    }

    if (!GameStarted)
    {
        GameStartScreen();
    }

    if (!GameOver)
    {
        GameLoopScreen();
    }

    GameOverScreen();
    return 0;
}

void GameInit()
{
    SYS_disableInts();
    SYS_showFrameLoad(true);

    SPR_init();
    SYS_enableInts();
    
    VDP_setScreenHeight224();
    VDP_setScreenWidth320();
    
    VRAMTileIndex = TILE_USER_INDEX;
    
    VRAMTileIndex += MapInit(VRAMTileIndex);
    VRAMTileIndex += ControllerInit(VRAMTileIndex);
    VRAMTileIndex += WaveManagerInit(VRAMTileIndex);
}

void GameStartScreen()
{
    ClearGameScreen();
    
    VDP_drawImageEx(BG_MAP, &GameStartImage, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, 0), 0, 0, TRUE, FALSE);
    VDP_setScrollingMode(HSCROLL_LINE , VSCROLL_PLANE);

    while (!GameStarted)
    {
        if (JOY_readJoypad(JOY_1) & BUTTON_START)
        {
            break;
        }

        SYS_doVBlankProcess();
    }

    GameStarted = TRUE;
}

void GameLoopScreen()
{
    ClearGameScreen();
    GameInit();

    while (!GameOver)
    {
        UpdateWave(&Player);
        UpdateController(Enemies, EnemyCount);
        
        SPR_update();
        SYS_doVBlankProcess();
    }
}

void GameOverScreen()
{
    ClearGameScreen();
    
    VDP_drawImageEx(BG_MAP, &GameOverImage, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, 0), 0, 0, TRUE, FALSE);
    VDP_setScrollingMode(HSCROLL_LINE , VSCROLL_PLANE);

    while (GameOver)
    {
        if (JOY_readJoypad(JOY_1) & BUTTON_START)
        {
            break;
        }

        SYS_doVBlankProcess();
    }

    GameOver = FALSE;
    GameStarted = FALSE;

    SYS_hardReset();
}

void ClearGameScreen()
{
    SPR_reset();
    SPR_update();
    
    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);
    
    VDP_clearTextArea(0, 0, 40, 28);
}