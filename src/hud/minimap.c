/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** minimap
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>



void tile_colour(core_t *core, int x, int y, sfRectangleShape *block)
{
    if (x == (int)(core->player.x / TILE_SIZE) &&
    y == (int)(core->player.y / TILE_SIZE)) {
        sfRectangleShape_setFillColor(block, sfBlue);
        return;
    }
    if (core->meta.map[y][x] >= 1) {
        sfRectangleShape_setFillColor(block, sfRed);
    } else {
        sfRectangleShape_setFillColor(block, sfWhite);
    }
}

void print_mini_map(core_t *core)
{
    sfVector2u win_size = sfRenderWindow_getSize(core->window);
    sfRectangleShape *block = sfRectangleShape_create();
    sfVector2f block_size = {MINIMAP_TILE_SIZE, MINIMAP_TILE_SIZE};
    const float map_width = SIZE * MINIMAP_TILE_SIZE;
    const float map_height = SIZE * MINIMAP_TILE_SIZE;
    sfVector2f map_pos = {(win_size.x - map_width) / 2,
    (win_size.y - map_height) / 2};
    sfVector2f draw_pos;

    sfRectangleShape_setSize(block, block_size);
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            draw_pos.x = map_pos.x + x * MINIMAP_TILE_SIZE;
            draw_pos.y = map_pos.y + y * MINIMAP_TILE_SIZE;
            tile_colour(core, x, y, block);
            sfRectangleShape_setPosition(block, draw_pos);
            sfRenderWindow_drawRectangleShape(core->window, block, NULL);
        }
    }
    sfRectangleShape_destroy(block);
}
