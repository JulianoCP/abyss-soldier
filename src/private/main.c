#include "public/main.h"

bool bIsCreditScreen = false;
s8 SelectedContext = 0;
Sprite* ButtonReference = NULL;
s16 VRAMTileIndex = TILE_USER_INDEX;

int main(bool HardReset)
{
    if (!HardReset) 
    {
        SYS_hardReset();
    }

    MainInit();

    if (!GameStarted)
    {
        GameStartScreen();
    }

    if (bIsCreditScreen)
    {
        CreditScreen();
    }

    if (!GameOver)
    {
        GameLoopScreen();
    }

    GameOverScreen();
    return 0;
}

void MainInit()
{
    SYS_disableInts();
    SYS_showFrameLoad(true);

    SPR_init();
    SYS_enableInts();
    
    VDP_setScreenHeight224();
    VDP_setScreenWidth320();
}

void CreditScreen()
{
    ClearGameScreen();

    VDP_drawImageEx(BG_MAP, &CreditImage, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, 0), 0, 0, TRUE, FALSE);
    VDP_setScrollingMode(HSCROLL_LINE , VSCROLL_PLANE);

    s16 auxiliaryTime = 0;

    while (bIsCreditScreen)
    {
        if (auxiliaryTime < (KEY_DELAY_TIME * 2)) 
        { 
            auxiliaryTime += 1; 
        }

        if (auxiliaryTime >= (KEY_DELAY_TIME * 2)) 
        {
            if (JOY_readJoypad(JOY_1) & BUTTON_START)
            {
                break;
            }
        }

        SYS_doVBlankProcess();
    }

    GameStarted = FALSE;
    bIsCreditScreen = FALSE;
    SYS_hardReset();
}

void GameStartScreen()
{
    ClearGameScreen();
  
    VDP_drawImageEx(BG_MAP, &GameStartImage, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, 0), 0, 0, TRUE, FALSE);
    VDP_setScrollingMode(HSCROLL_LINE , VSCROLL_PLANE);
    
    s16 auxiliaryTime = 0;
    ButtonReference = SPR_addSprite(&EnemySprite, 102, 102, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, VRAMTileIndex));

    while (!GameStarted)
    {
        if (auxiliaryTime < KEY_DELAY_TIME) 
        { 
            auxiliaryTime += 1; 
        }

        if (JOY_readJoypad(JOY_1) & BUTTON_UP)
        {
            SelectedContext = 0;
            SPR_setPosition(ButtonReference, 102, 102);
        }
        
        if (JOY_readJoypad(JOY_1) & BUTTON_DOWN)
        {
            SelectedContext = 1;
            SPR_setPosition(ButtonReference, 95, 122);
        }

        if (auxiliaryTime >= KEY_DELAY_TIME)
        {
            if (JOY_readJoypad(JOY_1) & BUTTON_START)
            {
                bIsCreditScreen = (SelectedContext > 0) ? TRUE : FALSE;
                break;
            }
        }

        SPR_update();
        SYS_doVBlankProcess();
    }
    
    GameStarted = TRUE;
}

void GameLoopScreen()
{
    ClearGameScreen();

    VRAMTileIndex = TILE_USER_INDEX;
    VRAMTileIndex += MapInit(VRAMTileIndex);
    VRAMTileIndex += ControllerInit(VRAMTileIndex);
    VRAMTileIndex += WaveManagerInit(VRAMTileIndex);
    
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
    
    if (Victory)
    {
        VDP_drawImageEx(BG_MAP, &VictoryImage, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, 0), 0, 0, TRUE, FALSE);
    }
    else
    {
        VDP_drawImageEx(BG_MAP, &DefeatImage, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, 0), 0, 0, TRUE, FALSE);
    }

    s16 auxiliaryTime = 0;
    VDP_setScrollingMode(HSCROLL_LINE , VSCROLL_PLANE);

    while (GameOver)
    {
        if (auxiliaryTime < (KEY_DELAY_TIME * 2)) 
        { 
            auxiliaryTime += 1; 
        }

        if (auxiliaryTime >= (KEY_DELAY_TIME * 2)) 
        {
            if (JOY_waitPress(JOY_1, BUTTON_START))
            {
                break;
            }
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
    
    JOY_reset();
    
    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);
    
    VDP_clearTextArea(0, 0, 40, 28);
    SYS_doVBlankProcess();
}