/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** reset_values
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"

void reset_enemies(core_t *core)
{
    enemy_list_t *enemy = core->vision->enemy_head;

    while (enemy) {
        ((enemy_info_t *)(enemy->context->info))->dead = false;
        ((enemy_info_t *)(enemy->context->info))->dying = false;
        enemy->context->position = rand_pos(core);
        enemy = enemy->next;
    }
}

void reset_values(core_t *core)
{
    if (core->player.health <= 0)
        core->player.score = 0;
    core->player.health = 100;
    core->player.ammo = 8;
    core->player.x = 1.5 * TILE_SIZE;
    core->player.y = 1.5 * TILE_SIZE;
    core->meta.last_frame_press = true;
    maze_generator(core->meta.map);
    make_blocks(core);
    reset_enemies(core);
    core->setting.soft_quit = false;
}
