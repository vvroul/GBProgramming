#include <gb/gb.h>
#include <gb/font.h>
#include <stdio.h>
#include "Knights.c"
#include "backgroundtiles.c"
#include "simplebg_map.c"
#include "windowmap.c"

void main() 
{   
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;

    while (1) 
    {
        UBYTE joypad_state = joypad();
        if (joypad_state)
        {
            NR41_REG = 0x1F;
            NR42_REG = 0xF1;
            NR43_REG = 0x30;
            NR44_REG = 0xC0;
            // NR14_REG = 0xC3;
            delay(1000);
        }
    }
}