/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** update_hud.c
*/

#include "entity_list.h"
#include "struct.h"
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Time.h>
#include <stdbool.h>
#include <stdio.h>

bool update_hp(entity_t *entity, core_t *core)
{
    char health[5];
    int displayed_health = core->player.health;

    if (core->player.health < 0)
        displayed_health = 0;
    sprintf(health, "%3d%c", displayed_health, '%');
    sfText_setString(entity->data, health);
    return true;
}

bool update_score(entity_t *entity, core_t *core)
{
    char score[5];
    int displayed_score = core->player.score;

    if (core->player.score > 9999)
        displayed_score = 9999;
    sprintf(score, "%4d", displayed_score);
    sfText_setString(entity->data, score);
    return true;
}

bool update_ammo(entity_t *entity, core_t *core)
{
    char ammo[5];
    int displayed_ammo = core->player.ammo;

    if (core->player.ammo < 0)
        displayed_ammo = 0;
    sprintf(ammo, "%3d", displayed_ammo);
    if (core->player.wp == WP_KNIFE)
        sprintf(ammo, "   /");
    sfText_setString(entity->data, ammo);
    return true;
}

bool update_weapon(entity_t *entity, core_t *core)
{
    int top_rect_weapons[WP_UNDEFINED] = {
        [WP_KNIFE] = 0,
        [WP_PISTOL] = 26,
    };
    int left_rect_weapons[WP_UNDEFINED] = {
        [WP_KNIFE] = 0,
        [WP_PISTOL] = 0,
    };

    entity->context->entity_rect.top = top_rect_weapons[core->player.wp];
    entity->context->entity_rect.left = left_rect_weapons[core->player.wp];
    entity->context->entity_rect.width = 47;
    entity->context->entity_rect.height = 23;
    sfSprite_setTextureRect(entity->data, entity->context->entity_rect);
    return true;
}

bool update_hand(entity_t *entity, core_t *core)
{
    sfTime entity_time = sfClock_getElapsedTime(entity->clock);
    int left_hand_rect[CLICK_FRAMES] = {1, 104, 207, 310, 104, 1};
    int top_hand_rect[WP_UNDEFINED] = {[WP_KNIFE] = 1, [WP_PISTOL] = 104};

    if (core->player.shooting && sfTime_asMilliseconds(entity_time) > 50) {
        sfClock_restart(entity->clock);
        entity->context->rect_counter += 1;
    }
    if (entity->context->rect_counter > 5) {
        entity->context->rect_counter = 0;
        core->player.shooting = false;
    }
    entity->context->entity_rect.top = top_hand_rect[core->player.wp];
    entity->context->entity_rect.left = left_hand_rect[entity->context->
        rect_counter];
    entity->context->entity_rect.width = 101;
    entity->context->entity_rect.height = 101;
    sfSprite_setTextureRect(entity->data, entity->context->entity_rect);
    return true;
}
