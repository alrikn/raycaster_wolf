/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** init_player
*/

#include "my.h"
#include "struct.h"
#include <stdlib.h>


/*
** don't touch this
*/
void init_player(player_t *player)
{
    player->x = 1.5f * TILE_SIZE;
    player->y = 1.5f * TILE_SIZE;
    player->angle = 0.2f;
    player->ammo = 8;
    player->score = 0;
    player->health = 100;
    player->wp = WP_PISTOL;
}
