/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** is_wall
*/

#include "my.h"

/*
**takes the raw inputs (not yet divided by 64)
**just check if the wall is over 0
*/
int is_wall(core_t *core, int x, int y)
{
    int tile_x = x / TILE_SIZE;
    int tile_y = y / TILE_SIZE;

    if (tile_x < 0 || tile_x >= SIZE || tile_y < 0 ||
    tile_y >= SIZE)
        return 1;
    return core->meta.map[tile_y][tile_x] >= 1;
}
