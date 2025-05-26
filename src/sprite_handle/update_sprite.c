/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** update_sprite.c
*/

#include "entity_list.h"
#include "my.h"

const update_fn_t sprite_update_map[LAST_TYPE] =
{
    [ENEMY] = update_enemy,
};

bool update_sprite(entity_t *sprite)
{
    if (sprite->entity_type != SF_SPRITE)
        return false;
    return sprite_update_map[sprite->context->type];
}
