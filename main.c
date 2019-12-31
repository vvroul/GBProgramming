#include <gb/gb.h>
#include <gb/font.h>
#include <stdio.h>
#include "Knights.c"
#include "backgroundtiles.c"
#include "simplebg_map.c"
#include "windowmap.c"

INT8 playerLocation[2];
BYTE isJumping;
UINT8 gravity = -2;
UINT8 currentSpeedY;
UINT8 floorYPosition = 100;

void performantDelay(UINT8 numloops)
{
    UINT8 i;
    for(i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

INT8 wouldHitSurface(UINT8 projectedYPosition)
{
    if (projectedYPosition >= floorYPosition)
    {
        return floorYPosition;
    }
    return -1;
}

void jump(UINT8 spriteId, UINT8 spriteLocation[2])
{
    INT8 possibleSurfaceY;

    if (isJumping == 0) 
    {
        isJumping = 1;
        currentSpeedY = 10;
    }

    currentSpeedY += gravity;
    spriteLocation[1] -= currentSpeedY;
    possibleSurfaceY = wouldHitSurface(spriteLocation[1]);

    if (possibleSurfaceY > -1)
    {
        isJumping = 0;
        move_sprite(spriteId, spriteLocation[0], possibleSurfaceY);
    }
    else
    {
        move_sprite(spriteId, spriteLocation[0], spriteLocation[1]);
    }
}

void main() 
{   
    set_sprite_data(0, 8, Knights);
    set_sprite_tile(0, 0);

    playerLocation[0] = 10;
    playerLocation[1] = floorYPosition;
    isJumping = 0;
    move_sprite(0, playerLocation[0], playerLocation[1]);

    DISPLAY_ON;
    SHOW_SPRITES;

    while(1)
    {
        if (joypad() & J_LEFT) 
        {
            playerLocation[0] -= 2;
            move_sprite(0, playerLocation[0], playerLocation[1]);
        }
        
        if (joypad() & J_RIGHT)
        {
            playerLocation[0] += 2;
            move_sprite(0, playerLocation[0], playerLocation[1]);
        }

        if ((joypad() & J_A) || (isJumping == 1))
        {
            jump(0, playerLocation);
        }

        performantDelay(4);
    }
    
}