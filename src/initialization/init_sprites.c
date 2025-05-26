/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** init_sprites.c
*/

#include "entity_list.h"
#include "my.h"

const init_fn_t sprite_init_map[LAST_TYPE] =
{[ENEMY] = init_enemy};

bool init_sprite(entity_t *entity, core_t *core)
{
    bool init_status;

    init_status = sprite_init_map[entity->context->type](entity, core);
    return init_status;
}
