/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** free_memory
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <SFML/Audio/Music.h>
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>

/*
** vision free
*/
static void destroy_vision(vision_t *vision)
{
    sfTexture_destroy(vision->texture_one);
    sfTexture_destroy(vision->texture_two);
    sfSprite_destroy(vision->sprite);
    sfTexture_destroy(vision->door);
    sfTexture_destroy(vision->health);
    free(vision->all_rays);
    free(vision);
}
//raul renales

static void destroy_sounds(core_t *core)
{
    if (core->sound.shoot_sound)
        sfSound_destroy(core->sound.shoot_sound);
    if (core->sound.shoot_buffer)
        sfSoundBuffer_destroy(core->sound.shoot_buffer);
    if (core->sound.walk_buffer)
        sfSoundBuffer_destroy(core->sound.walk_buffer);
    if (core->sound.walk_sound)
        sfSound_destroy(core->sound.walk_sound);
    if (core->sound.background_music)
        sfMusic_destroy(core->sound.background_music);
    if (core->sound.dog_sound)
        sfSound_destroy(core->sound.dog_sound);
    if (core->sound.dog_buffer)
        sfSoundBuffer_destroy(core->sound.dog_buffer);
}

static void destroy_night(core_t *core)
{
    sfTexture_destroy(core->meta.night_tex);
    sfSprite_destroy(core->meta.night);
    sfClock_destroy(core->frame.tick);
}

static void destroy_entities(core_t *core)
{
    entity_t *next;
    entity_t *current = core->entities;

    while (current) {
        next = current->next;
        current->sf_functions.destroy(current->data);
        if (current->context->texture)
            sfTexture_destroy(current->context->texture);
        if (current->context->font)
            sfFont_destroy(current->context->font);
        if (current->context->info)
            free(current->context->info);
        if (current->clock)
            sfClock_destroy(current->clock);
        free(current->context);
        free(current);
        current = next;
    }
}

static void destroy_enemy_list(core_t *core)
{
    enemy_list_t *next;
    enemy_list_t *current = core->vision->enemy_head;

    for (int i = 0; i < ENEMY_COUNT; i++) {
        next = current->next;
        free(current);
        current = next;
    }
}

/*
** every single free must be called here (except between levels)
*/
void destroy_everything(core_t *core)
{
    print_save(core);
    destroy_enemy_list(core);
    destroy_vision(core->vision);
    destroy_sounds(core);
    destroy_entities(core);
    destroy_night(core);
}
