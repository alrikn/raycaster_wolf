/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** main_loop
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Time.h>
#include <SFML/System/Types.h>
#include <SFML/System/Time.h>
#include <stdio.h>

#include <stdio.h>


void handle_closure(sfRenderWindow* window, sfEvent *event, player_t *player)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if (event->type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
}

/*
** this is all stuff i need to actually launch rays and
print on screen so no touching
*/
void vision_initialize(player_t *player, vision_t *vision,
    sfRenderWindow* window)
{
    vision->player = player;
    vision->all_rays = malloc(sizeof(raycast_t) * SCREEN_WIDTH);
    vision->texture_one = sfTexture_createFromFile
    ("assets/wall_blood.png", NULL);
    vision->door = sfTexture_createFromFile
    ("assets/door.png", NULL);
    vision->health = sfTexture_createFromFile
    ("assets/health.png", NULL);
    vision->texture_two = sfTexture_createFromFile
    ("assets/wall.png", NULL);
    if (!vision->texture_one || !vision->texture_two || !vision->door) {
        exit(84);
    }
    vision->window = window;
    vision->sprite = sfSprite_create();
}

static void draw_hud(core_t *core)
{
    entity_t *current = core->entities;

    while (current) {
        if (current->context->type != ENEMY)
            current->sf_functions.draw(core->window, current->data, NULL);
        current = current->next;
    }
}

/*
** nothing happens until we reack the limit
*/
void limit_frame_hard(core_t *core)
{
    sfTime time;
    long long frame;

    if (!core->frame.tick)
        core->frame.tick = sfClock_create();
    time = sfClock_getElapsedTime(core->frame.tick);
    frame = sfTime_asMilliseconds(time);
    if (frame > TPS)
        printf("framerate lower than expects: %lld\n", frame);
    while (frame <= TPS) {
        time = sfClock_getElapsedTime(core->frame.tick);
        frame = sfTime_asMilliseconds(time);
    }
    sfClock_restart(core->frame.tick);
}

static bool update_sprites(core_t *core)
{
    entity_t *current_entity = core->entities;
    bool no_error = true;

    while (current_entity && no_error) {
        if (current_entity->update)
            no_error = current_entity->update(current_entity, core);
        current_entity = current_entity->next;
    }
    return no_error;
}

static void general_checks(core_t *core)
{
    enemy_list_t *current = core->vision->enemy_head;
    bool all_enemies_dead = true;

    if (core->player.health <= 0) {
        core->setting.soft_quit = true;
        core->statistics.deaths += 1;
    }
    while (current && all_enemies_dead) {
        if (!((enemy_info_t *)current->context->info)->dead)
            all_enemies_dead = false;
        current = current->next;
    }
    if (all_enemies_dead) {
        core->setting.soft_quit = true;
        core->player.health = 100;
        core->statistics.wins += 1;
    }
}

/*
** this where the game logic will be situated,
** feel free to change to each own needs,
** but try to keep same ordere of execution
*/
void game_loop(core_t *core)
{
    while (sfRenderWindow_isOpen(core->window) && !core->setting.soft_quit) {
        limit_frame_hard(core);
        update_sprites(core);
        handle_closure(core->window, &core->event, &core->player);
        sfRenderWindow_clear(core->window, sfBlack);
        draw_floor_and_ceiling(core->window, core);
        cast_all_rays(&core->player, core->window, core->vision, core);
        draw_hud(core);
        if (!key_pressed(&core->event, &core->player, core) &&
        core->sound.walk_sound)
            sfSound_stop(core->sound.walk_sound);
        sfRenderWindow_display(core->window);
        general_checks(core);
    }
}

/*
** when player starts, we goto game loop
** when player dies, we go back to menu screen
*/
static void print_stats(core_t *core)
{
    printf("\nStatistics:\n\n"
        "\tHigh score: %d\n"
        "\tTimes Won: %d\n"
        "\tTimes Died: %d\n"
        "\tDogs put to sleep: %d\n"
        "\tSoldiers killed %d\n\n",
        core->statistics.high_score,
        core->statistics.wins,
        core->statistics.deaths,
        core->statistics.dogs_k,
        core->statistics.gun_k
    );
}

void game_play_prep(core_t *core)
{
    while (sfRenderWindow_isOpen(core->window)) {
        if (!core->meta.save)
            reset_values(core);
        menu_screen(core);
        game_loop(core);
        if (core->player.score > core->statistics.high_score)
            core->statistics.high_score = core->player.score;
    }
    print_stats(core);
    write_statistics(core);
    destroy_everything(core);
}
