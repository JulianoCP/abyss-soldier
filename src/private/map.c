#include "public/map.h"

u16 MapInit(u16 VRAMIndex)
{
    VDP_drawImageEx(BG_MAP, &MapBackground, TILE_ATTR_FULL(PAL_MAP, FALSE, FALSE, FALSE, VRAMIndex), 0, 0, TRUE, FALSE);

    return 1;
}

// static u16 loadStarField(u16 vramIndex)
// {
//     // Draw the foreground
//     VDP_drawImageEx(BG_B, &img_starfield, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, vramIndex), 0, 0, TRUE, FALSE);
//     vramIndex += img_starfield.tileset->numTile;

//     // Set the proper scrolling mode (line by line)
//     VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);

//     // Create the scrolling offset table
//     s16 s = 1;
//     for(s16 i = 0; i < TABLE_LEN; i++)
//     {
//         s16 ns;

//         scroll_PLAN_B_F[i] = FIX16(0);
//         do
//         {
//             ns = -((random() & 0x7F) + 10);
//         }
//         while (ns == s);
//         scroll_speed[i] = ns;
//         s = ns;
//     }

//     return vramIndex;
// }