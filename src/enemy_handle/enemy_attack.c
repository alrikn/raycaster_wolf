/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** enemy_attack.c
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <SFML/Audio/Sound.h>
#include <stdio.h>

void can_swipe(enemy_info_t *info, core_t *core)
{
    info->weapon_cooldown++;
        if (info->weapon_cooldown >= 80) {
            info->weapon_cooldown = 0;
            info->main_player->health -= 30;
        }
}

void can_shoot(enemy_info_t *info, core_t *core)
{
    info->weapon_cooldown += 1;
    if (info->weapon_cooldown >= 120) {
        info->weapon_cooldown = 0;
        info->main_player->health -= 20;
        sfSound_play(core->sound.shoot_sound);
    }
}

bool enemy_attack(entity_t *enemy, core_t *core)
{
    enemy_info_t *enemy_info = enemy->context->info;
    float distance = get_distance(&enemy->context->position,
        &(sfVector2f){core->player.x, core->player.y});

    if (enemy_info->weapon_type == WP_KNIFE && distance <= (0.5 * TILE_SIZE))
        can_swipe(enemy_info, core);
    if (enemy_info->weapon_type == WP_PISTOL && distance < (4 * TILE_SIZE))
        can_shoot(enemy_info, core);
    if ((enemy_info->weapon_type == WP_KNIFE && distance >
    (0.6 * TILE_SIZE))) {
        enemy_info->weapon_cooldown = 0;
    }
    return true;
}
