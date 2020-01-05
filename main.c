#include <gb/gb.h>
#include <gb/font.h>
#include <stdio.h>
#include "Knights.c"
#include "backgroundtiles.c"
#include "simplebg_map.c"
#include "windowmap.c"
#include "GameCharacter.c"
#include "GameSprites.c"
#include "mario_data.c"
#include "mario_map.c"

GameCharacter ship;
GameCharacter buggy;
UBYTE spriteSize = 8;
UINT8 iter;

UBYTE checkCollision(GameCharacter* one, GameCharacter* two)
{
    return (one->x >= two->x && one->x <= two->x + two->width) && (one->y >= two->y && one->x <= two->y + two->height) || (two->x >= one->x && two->x <= one->x + one->width) && (two->y >= one->y && two->x <= one->y + one->height);
}

void moveGameCharacter(GameCharacter* character, UINT8 x, UINT8 y)
{
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spriteSize, y);
    move_sprite(character->spritids[2], x, y + spriteSize);
    move_sprite(character->spritids[3], x + spriteSize, y + spriteSize);
}

void setupShip()
{
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    set_sprite_tile(0, 0);
    ship.spritids[0] = 0;
    set_sprite_tile(1,1);
    ship.spritids[1] = 1;
    set_sprite_tile(2, 2);
    ship.spritids[2] = 2;
    set_sprite_tile(3, 3);
    ship.spritids[3] = 3;

    moveGameCharacter(&ship, ship.x, ship.y);
}

void setupBug()
{
    buggy.x = 30;
    buggy.y = 0;
    buggy.width = 16;
    buggy.height = 16;

    set_sprite_tile(4, 4);
    buggy.spritids[0] = 4;
    set_sprite_tile(5, 5);
    buggy.spritids[1] = 5;
    set_sprite_tile(6, 6);
    buggy.spritids[2] = 6;
    set_sprite_tile(7, 7);
    buggy.spritids[3] = 7;

    moveGameCharacter(&buggy, buggy.x, buggy.y);
}

void performantDelay(UINT8 numloops)
{
    UINT8 i;
    for(i = 0; i < numloops; i++)
    {
        wait_vbl_done();
    }
}

void oldMain() 
{
    set_sprite_data(0, 8, GameSprites);
    setupShip();
    setupBug();
    SHOW_SPRITES;
    DISPLAY_ON;

    while(!checkCollision(&ship, &buggy))     //while we don't have a collision
    {
        if (joypad() & J_LEFT)
        {
            ship.x -= 2;
            moveGameCharacter(&ship, ship.x, ship.y);
        }
        if (joypad() & J_RIGHT)
        {
            ship.x += 2;
            moveGameCharacter(&ship, ship.x, ship.y);
        }

        //make the bug move down the screen
        buggy.y += 5;
        if (buggy.y >= 144)
        {
            buggy.y = 0;
            buggy.x = ship.x;
        }
        moveGameCharacter(&buggy, buggy.x, buggy.y);
        performantDelay(5);
    }

    printf("\n \n \n \n \n \n \n **** GAME OVER ****");
}

void fadeout()
{
    for (iter = 0; iter < 4; iter++)
    {
        switch (iter)
        {
            case 0:
                BGP_REG = 0xE4;
                break;
            case 1:
                BGP_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xFE;
                break;
            case 3:
                BGP_REG = 0xFF;
                break;
            default:
                break;
        }
        performantDelay(10);
    }
}

void fadein()
{
    for (iter = 0; iter < 3; iter++)
    {
        switch (iter)
        {
            case 0:
                BGP_REG = 0xFE;
                break;
            case 1:
                BGP_REG = 0xF9;
                break;
            case 2:
                BGP_REG = 0xE4;
                break;
            default:
                break;
        }
        performantDelay(10);
    }
}


void main()
{
    set_bkg_data(0, 158, mario_data);
    set_bkg_tiles(0, 0, 20, 18, mario_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);

    fadeout();

    fadein();

    // printf("START THE GAME");
    // oldMain();
}