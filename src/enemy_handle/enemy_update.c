/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** enemy_update.c
*/

#include "entity_list.h"
#include "wolf_entities.h"
#include "struct.h"
#include "my.h"
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <math.h>
#include <stdio.h>
#include <SFML/System/Vector2.h>

float get_distance(sfVector2f *pos1, sfVector2f *pos2)
{
    float x_diff = pos1->x - pos2->x;
    float y_diff = pos1->y - pos2->y;

    return sqrtf((x_diff * x_diff) + (y_diff * y_diff));
}

static void handle_sliding_enemy(core_t *core,
    sfVector2f *new_dir, sfVector2f *start)
{
    if (!is_wall(core, new_dir->x, start->y) && new_dir->x > 0) {
        new_dir->y = start->y;
        return;
    }
    if (!is_wall(core, start->x, new_dir->y) && new_dir->y > 0) {
        new_dir->x = start->x;
        return;
    }
    new_dir->x = start->x;
    new_dir->y = start->y;
}

/*
** there are sliding enemies
*/
sfVector2f get_new_pos(sfVector2f *dest, sfVector2f *start, core_t *core)
{
    float dx = dest->x - start->x;
    float dy = dest->y - start->y;
    float magnitude = sqrtf(dx * dx + dy * dy);
    float x_direction;
    float y_direction;
    sfVector2f new_dir;

    if (magnitude == 0)
        return *start;
    x_direction = dx / magnitude;
    y_direction = dy / magnitude;
    new_dir.x = (x_direction * ENEMY_SPEED) + start->x;
    new_dir.y = (y_direction * ENEMY_SPEED) + start->y;
    if (is_wall(core, new_dir.x, new_dir.y)) {
        handle_sliding_enemy(core, &new_dir, start);
    }
    return new_dir;
}

static bool death_animation(entity_t *enemy, core_t *core)
{
    sfTime enemy_time = sfClock_getElapsedTime(enemy->clock);
    enemy_info_t *info = ((enemy_info_t *)(enemy->context->info));

    if (sfTime_asMilliseconds(enemy_time) > ANIMATION_TIME) {
        info->animation_counter += 1;
        sfClock_restart(enemy->clock);
    }
    if (info->animation_counter > 5) {
        info->dead = true;
        info->dying = false;
        if (info->weapon_type == WP_KNIFE)
            core->statistics.dogs_k += 1;
        if (info->weapon_type == WP_PISTOL)
            core->statistics.gun_k += 1;
    }
    return true;
}

static void alive_animation(entity_t *enemy)
{
    sfTime enemy_time = sfClock_getElapsedTime(enemy->clock);
    enemy_info_t *info = ((enemy_info_t *)(enemy->context->info));

    if (sfTime_asMilliseconds(enemy_time) > ANIMATION_TIME) {
        info->animation_counter += 1;
        sfClock_restart(enemy->clock);
    }
    if (info->animation_counter > 2)
        info->animation_counter = 0;
}

void move_enemy(entity_t *enemy, player_t *player,
    enemy_info_t *info, core_t *core)
{
    sfVector2f new_position = enemy->context->position;
    float distance = get_distance(&enemy->context->position,
    &(sfVector2f){player->x, player->y});

    new_position = get_new_pos(&(sfVector2f){player->x, player->y},
    &enemy->context->position, core);
    if (distance < (2 * TILE_SIZE) && info->weapon_type == WP_PISTOL) {
        new_position = enemy->context->position;
    }
    if (distance < (0.5 * TILE_SIZE) && info->weapon_type == WP_KNIFE) {
        new_position = enemy->context->position;
    }
    enemy->context->position = new_position;
}

bool update_enemy(entity_t *enemy, core_t *core)
{
    enemy_info_t *current_info = enemy->context->info;

    if (current_info->dying)
        return death_animation(enemy, core);
    if (current_info->dead || !current_info->activated)
        return true;
    alive_animation(enemy);
    current_info->activated = false;
    current_info->enemy_destination = ((sfVector2f) {core->player.x,
    core->player.y});
    move_enemy(enemy, &core->player, current_info, core);
    return enemy_attack(enemy, core);
}
