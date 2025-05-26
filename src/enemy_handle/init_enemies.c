/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** init_enemies.c
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdio.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <stdlib.h>
#include "time.h"

/*
** i set a limit to how many times it can search
** cus we shouldn't be stuck on this forever if
** there is no free space for some reason
*/
sfVector2f rand_pos(core_t *core)
{
    int i = 0;
    sfVector2u spawn;
    sfVector2f real;

    while (i < 3000) {
        spawn.x = (rand() + 1) % SIZE;
        spawn.y = (rand() + 1) % SIZE;
        if (core->meta.map[spawn.y][spawn.x] == 0) {
            real.x = (spawn.x + 0.5) * TILE_SIZE;
            real.y = (spawn.y + 0.5) * TILE_SIZE;
            return real;
        }
        i++;
    }
    real.x = (spawn.x + 0.5) * TILE_SIZE;
    real.y = (spawn.y + 0.5) * TILE_SIZE;
    return real;
}

bool init_enemy(entity_t *entity, core_t *core)
{
    enemy_info_t *info = calloc(1, sizeof(enemy_info_t));
    char *sprite_files[WP_UNDEFINED] = {"assets/dog_sprite_clear.png",
        "assets/sprite_shoot_empty.png"};

    info->weapon_type = rand() % 2;
    entity->context->texture = sfTexture_createFromFile
    (sprite_files[info->weapon_type], NULL);
    sfSprite_setTexture(entity->data, entity->context->texture, sfTrue);
    entity->context->position = rand_pos(core);
    entity->context->info = info;
    entity->clock = sfClock_create();
    info->death_counter = -1;
    info->weapon_cooldown = 0;
    info->dead = false;
    info->activated = false;
    info->enemy_destination = (sfVector2f) {1.5f * TILE_SIZE,
    1.5f * TILE_SIZE};
    return true;
}
