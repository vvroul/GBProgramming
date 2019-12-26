#include <gb/gb.h>
#include <stdio.h>
#include "Knights.c"
#include "backgroundtiles.c"
#include "simplebg_map.c"

void main() 
{   
    set_bkg_data(0, 7, TileLabel);
    set_bkg_tiles(0, 0, 40, 18, simplebg_map);

    SHOW_BKG;
    DISPLAY_ON;

    while (1) 
    {
        scroll_bkg(1, 0);
        delay(50);
    }
}