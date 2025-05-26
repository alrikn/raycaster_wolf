/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** print_pos
*/

#include "my.h"
#include "struct.h"
#include <SFML/System/Vector2.h>
#include <stdio.h>

void print_map_matrix(int x, int y, sfVector2u tile, core_t *core)
{
    if (x == tile.x && y == tile.y) {
        my_cooler_putstr("P ");
        return;
    }
    if (core->meta.map[y][x] == 4) {
        my_cooler_putstr("D ");
        return;
    }
    if (core->meta.map[y][x] >= 1) {
        my_cooler_putstr("X ");
        return;
    }
    if (core->meta.map[y][x] == 0) {
        my_cooler_putstr(". ");
        return;
    }
}

void print_pos(int player_x, int player_y, core_t *core)
{
    sfVector2u tile = {player_x / TILE_SIZE, player_y / TILE_SIZE};

    my_cooler_putstr("\n\n");
    printf("x_pos = %d, y_pos = %d, angle = %f\n", player_x,
    player_y, core->player.angle);
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            print_map_matrix(x, y, tile, core);
        }
        my_cooler_putstr("\n");
    }
}
