/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** door_interaction
*/

#include "my.h"
#include "math.h"

void interact_with_block(core_t *core)
{
    float move_x = cosf(core->player.angle) * MOVEMENT_SPEED * 15;
    float move_y = sinf(core->player.angle) * MOVEMENT_SPEED * 15;
    float new_x = core->player.x + move_x;
    float new_y = core->player.y + move_y;
    int tile_x = new_x / TILE_SIZE;
    int tile_y = new_y / TILE_SIZE;

    if (core->meta.map[tile_y][tile_x] == 4) {
        core->meta.map[tile_y][tile_x] = 0;
    }
    if (core->meta.map[tile_y][tile_x] == 3) {
        core->meta.map[tile_y][tile_x] = 0;
        core->player.score += 100;
        core->player.ammo += 10;
        core->player.health += 30;
    }
}
