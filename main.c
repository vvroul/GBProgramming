#include <gb/gb.h>
#include <gb/font.h>
#include <stdio.h>
#include "Knights.c"
#include "backgroundtiles.c"
#include "simplebg_map.c"
#include "windowmap.c"

void main() 
{   
    font_t min_font;
    font_init();
    min_font = font_load(font_min); //36 tiles
    font_set(min_font);

    set_bkg_data(37, 7, TileLabel);
    set_bkg_tiles(0, 0, 40, 18, simplebg_map);

    set_win_tiles(0, 0, 5, 1, windowmap);

    move_win(7, 130);

    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;

    while (1) 
    {
        scroll_bkg(1, 0);
        delay(50);
    }
}