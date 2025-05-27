/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** kill_enemy
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <SFML/Audio/Sound.h>
#include <math.h>

static float set_angle_diff(vision_t *vision, enemy_list_t *enemy)
{
    float sprite_dx = enemy->render_x - vision->player->x;
    float sprite_dy = enemy->render_y - vision->player->y;
    float sprite_angle = atan2f(sprite_dy, sprite_dx);
    float angle_diff;

    if (sprite_angle < 0)
        sprite_angle += 2 * M_PI;
    angle_diff = sprite_angle - vision->player->angle;
    if (angle_diff > M_PI)
        angle_diff -= 2 * M_PI;
    if (angle_diff < - M_PI)
        angle_diff += 2 * M_PI;
    return angle_diff;
}

static sprite_print_t set_mini_values(sprite_print_t hold,
    int sprite_screen_x, int column)
{
    hold.sprite_height = (TILE_SIZE / hold.sprite_dist) * PROJECTION_PLANE;
    hold.sprite_width = hold.sprite_height;
    hold.draw_start_x = sprite_screen_x - hold.sprite_width / 2;
    hold.draw_end_x = sprite_screen_x + hold.sprite_width / 2;
    return hold;
}

/*
 * this func may look similar vto the ones found in  drawing enemies.
 * this is because, for all intents and purposes, they are the same function
 * just wth the unecessay parts removed.
 * (they both check at a column if there is a sprite)
 */
static bool loop_handle(vision_t *vision, int column, enemy_list_t *enemy)
{
    sprite_print_t hold = {0};
    bool seen = false;
    float sprite_dx = enemy->context->position.x - vision->player->x;
    float sprite_dy = enemy->context->position.y - vision->player->y;
    float angle_diff = set_angle_diff(vision, enemy);
    int sprite_screen_x = (int)((0.5f + (angle_diff / (FOV))) * SCREEN_WIDTH);

    hold.sprite_dist = sqrtf(sprite_dx * sprite_dx + sprite_dy * sprite_dy);
    hold = set_mini_values(hold, sprite_screen_x, column);
    if (column >= hold.draw_start_x && column < hold.draw_end_x) {
        if (hold.sprite_dist < vision->all_rays[column].full_dist)
            seen = true;
    }
    return (seen && !((enemy_info_t *)enemy->context->info)->dying &&
        !((enemy_info_t *)enemy->context->info)->dead);
}

bool valid_shot(enemy_list_t *enemy, core_t *core)
{
    if (core->player.wp == WP_PISTOL && core->player.ammo <= 0) {
        return false;
    }
    if (core->player.wp == WP_KNIFE && enemy->dist >= (1 * TILE_SIZE)) {
        return false;
    }
    return true;
}

/*
** TODO: jose implements his dying boolean
*/
bool can_shoot_enemy(enemy_list_t *enemy, core_t *core)
{
    int i = (SCREEN_WIDTH / 2);
    bool worked = false;

    if (!valid_shot(enemy, core))
        return false;
    worked = loop_handle(core->vision, i, enemy);
    if (worked) {
        core->player.score += 10;
        ((enemy_info_t *)(enemy->context->info))->dying = true;
    }
    return worked;
}

void player_attack(core_t *core)
{
    enemy_list_t *enemy = core->vision->enemy_head;

    if (core->player.wp == WP_PISTOL && core->player.ammo > 0) {
        core->player.ammo -= 1;
        core->player.shooting = true;
        sfSound_play(core->sound.shoot_sound);
    }
    if (core->player.wp == WP_KNIFE) {
        core->player.shooting = true;
        sfSound_play(core->sound.knife_sound);
    }
    while (enemy) {
        if (!((enemy_info_t *)(enemy->context->info))->dead &&
        ((enemy_info_t *)enemy->context->info)->activated &&
        !((enemy_info_t *)enemy->context->info)->dying &&
        can_shoot_enemy(enemy, core))
            break;
        enemy = enemy->next;
    }
}
