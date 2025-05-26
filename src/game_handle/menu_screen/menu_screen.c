/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** menu_screen
*/

#include "entity_list.h"
#include "menu_bar.h"
#include "my.h"
#include "struct.h"
#include <SFML/Audio/Listener.h>
#include <SFML/Audio/Sound.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <stdio.h>
#include <string.h>

void adjust_volume(core_t *core, int change)
{
    core->setting.volume += change;
    if (core->setting.volume < 0)
        core->setting.volume = 0;
    if (core->setting.volume > 100)
        core->setting.volume = 100;
    sfListener_setGlobalVolume(core->setting.volume);
}

void get_mouse_pos(menu_mouse_t *mouse_pos, core_t *core)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(core->window);

    mouse_pos->mouse = sfRenderWindow_mapPixelToCoords(core->window,
        pixel_pos, NULL);
    mouse_pos->start_bounds = sfSprite_getGlobalBounds
    (core->setting.images.start_sprite);
    mouse_pos->quit_bounds = sfSprite_getGlobalBounds
    (core->setting.images.quit_sprite);
    mouse_pos->volup_bounds = sfSprite_getGlobalBounds
    (core->setting.images.volup_sprite);
    mouse_pos->voldown_bounds = sfSprite_getGlobalBounds
    (core->setting.images.voldown_sprite);
}

void process_mouse_clicks(core_t *core, menu_mouse_t *mouse_pos)
{
    if (sfFloatRect_contains(&mouse_pos->start_bounds,
        mouse_pos->mouse.x, mouse_pos->mouse.y))
        core->setting.start = true;
    if (sfFloatRect_contains(&mouse_pos->quit_bounds,
        mouse_pos->mouse.x, mouse_pos->mouse.y))
        sfRenderWindow_close(core->window);
    if (sfFloatRect_contains(&mouse_pos->volup_bounds,
        mouse_pos->mouse.x, mouse_pos->mouse.y)) {
        adjust_volume(core, 1);
    }
    if (sfFloatRect_contains(&mouse_pos->voldown_bounds,
        mouse_pos->mouse.x, mouse_pos->mouse.y)) {
        adjust_volume(core, -1);
    }
}

void handle_button_clicks(core_t *core)
{
    menu_mouse_t mouse_pos;

    if (core->event.type != sfEvtMouseButtonPressed)
        return;
    get_mouse_pos(&mouse_pos, core);
    process_mouse_clicks(core, &mouse_pos);
}

static void draw_menu(core_t *core)
{
    char high_score[strlen("High score: ") + MAX_SCORE_DIGIT];

    sprintf(high_score, "High score: %d\n", core->statistics.high_score);
    sfText_setString(core->setting.images.high_score, high_score);
    sfRenderWindow_drawSprite(core->window,
        core->setting.images.background_sprite, NULL);
    sfRenderWindow_drawSprite(core->window,
        core->setting.images.start_sprite, NULL);
    sfRenderWindow_drawSprite(core->window,
        core->setting.images.quit_sprite, NULL);
    sfRenderWindow_drawSprite(core->window,
        core->setting.images.volup_sprite, NULL);
    sfRenderWindow_drawSprite(core->window,
        core->setting.images.voldown_sprite, NULL);
    sfRenderWindow_drawText(core->window,
        core->setting.images.high_score, NULL);
}

/*
** draw menu screen
*/
void menu_screen(core_t *core)
{
    core->meta.save = false;
    core->setting.start = false;
    while (sfRenderWindow_isOpen(core->window) && !core->setting.start) {
        limit_frame_hard(core);
        handle_closure(core->window, &core->event, &core->player);
        sfRenderWindow_clear(core->window, sfBlack);
        handle_button_clicks(core);
        draw_menu(core);
        sfRenderWindow_display(core->window);
    }
}
