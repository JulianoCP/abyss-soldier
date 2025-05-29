#include "public/level/map.h"

s16 MapInit(s16 VRAMIndex)
{
    VDP_drawImageEx(BG_MAP, &MapBackground, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, VRAMIndex), 0, 0, TRUE, FALSE);
    VDP_setScrollingMode(HSCROLL_LINE , VSCROLL_PLANE);

    return MapBackground.tileset->numTile;
}