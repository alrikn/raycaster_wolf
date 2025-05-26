/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** make_core
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Audio.h>

const sf_fn_tuple_t tuple_map[MAX_ENTITY_SIZE] =
{
    [SF_SPRITE] =
    {
        .create = (create_fn_t) sfSprite_create,
        .destroy = (destroy_fn_t) sfSprite_destroy,
        .draw = (draw_fn_t) sfRenderWindow_drawSprite,
    },
    [SF_RECTANGLE] =
    {
        .create = (create_fn_t) sfRectangleShape_create,
        .destroy = (destroy_fn_t) sfRectangleShape_destroy,
        .draw = (draw_fn_t) sfRenderWindow_drawRectangleShape,
    },
    [SF_TEXT] =
    {
        .create = (create_fn_t) sfText_create,
        .destroy = (destroy_fn_t) sfText_destroy,
        .draw = (draw_fn_t) sfRenderWindow_drawText,
    },
};

sfRenderWindow* create_window(void)
{
    sfVideoMode video_mode = {SCREEN_WIDTH, SCREEN_HEIGHT, 32};

    return sfRenderWindow_create(video_mode, "Raytcaster",
    sfClose | sfResize, 0);
}

entity_t *append_entity(entity_t **head, entity_type_t entity_type,
    context_type_t context_type)
{
    entity_t *new_node = calloc(1, sizeof(entity_t));
    entity_t *current = *head;

    if (!new_node)
        return NULL;
    new_node->entity_type = entity_type;
    new_node->sf_functions = tuple_map[entity_type];
    new_node->data = new_node->sf_functions.create();
    new_node->context = calloc(1, sizeof(entity_context_t));
    new_node->context->type = context_type;
    new_node->next = NULL;
    if (current) {
        current->prev = new_node;
        new_node->next = current;
    }
    *head = new_node;
    return new_node;
}

static void append_enemy(enemy_list_t **head, entity_t *enemy)
{
    enemy_list_t *new_node = malloc(sizeof(enemy_list_t));
    enemy_list_t *current = *head;

    if (!new_node)
        return;
    new_node->sprite = enemy->data;
    new_node->context = enemy->context;
    new_node->dist = 3000;
    new_node->render_x = enemy->context->position.x;
    new_node->render_y = enemy->context->position.y;
    new_node->next = NULL;
    new_node->prev = NULL;
    if (current) {
        current->prev = new_node;
        new_node->next = current;
        *head = new_node;
        return;
    }
    *head = new_node;
}

static void make_night(core_t *core)
{
    sfTexture *night_tex = sfTexture_createFromFile
    ("assets/static_night.jpg", NULL);
    sfSprite *night_sprite = sfSprite_create();

    if (!night_tex || !night_sprite)
        exit(84);
    sfTexture_setRepeated(night_tex, sfTrue);
    sfSprite_setTexture(night_sprite, night_tex, sfTrue);
    core->meta.night = night_sprite;
    core->meta.last_frame_press = true;
    core->meta.night_tex = night_tex;
}

/*
** TODO: set the volume
*/
void initialize_sound(core_t *core)
{
    core->sound.background_music = sfMusic_createFromFile("assets/music.ogg");
    if (!core->sound.background_music)
        return;
    sfMusic_setLoop(core->sound.background_music, sfTrue);
    sfMusic_play(core->sound.background_music);
    sfMusic_setVolume(core->sound.background_music, 20.0f);
    core->sound.walk_buffer = sfSoundBuffer_createFromFile("assets/walk.wav");
    if (!core->sound.walk_buffer)
        return;
    core->sound.walk_sound = sfSound_create();
    sfSound_setBuffer(core->sound.walk_sound, core->sound.walk_buffer);
    sfSound_setLoop(core->sound.walk_sound, sfTrue);
    core->sound.shoot_buffer = sfSoundBuffer_createFromFile
    ("assets/shoot.wav");
    if (!core->sound.shoot_buffer)
        return;
    core->sound.shoot_sound = sfSound_create();
    sfSound_setBuffer(core->sound.shoot_sound, core->sound.shoot_buffer);
}

void create_enemies(core_t *core)
{
    entity_t *current = NULL;

    core->vision->enemy_head = NULL;
    for (int i = 0; i < ENEMY_COUNT; i++) {
        current = append_entity(&core->entities, SF_SPRITE, ENEMY);
        current->init = init_sprite;
        current->update = update_enemy;
        current->init(current, core);
        ((enemy_info_t *)current->context->info)->main_player = &core->player;
        append_enemy(&core->vision->enemy_head, current);
    }
}

/*
**this func initializes core
*/
void make_core(core_t *core)
{
    if (core->meta.save)
        parse_save(core);
    else
        maze_generator(core->meta.map);
    make_blocks(core);
    make_night(core);
    core->window = create_window();
    core->entities = NULL;
    init_player(&core->player);
    init_hud(core);
    core->vision = malloc(sizeof(vision_t));
    vision_initialize(&core->player, core->vision, core->window);
    initialize_sound(core);
    create_enemies(core);
    make_menu(core);
}
