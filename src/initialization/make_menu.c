/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** make_menu
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>

static void set_menu_pos(core_t *core)
{
    sfVector2u win_size = sfRenderWindow_getSize(core->window);
    float base_x = win_size.x - 100.0f;
    float base_y = 20.0f;
    float spacing = 20.0f;

    sfSprite_setPosition(core->setting.images.start_sprite,
    (sfVector2f){base_x, base_y});
    sfSprite_setPosition(core->setting.images.quit_sprite,
    (sfVector2f){base_x, base_y + 90 + spacing});
    sfSprite_setPosition(core->setting.images.volup_sprite,
    (sfVector2f){base_x,
    base_y + (90 + spacing) * 2});
    sfSprite_setPosition(core->setting.images.voldown_sprite,
    (sfVector2f){base_x, base_y + (90 + spacing) * 2 + 45 + spacing});
}

static void load_background_texture(core_t *core)
{
    sfVector2u window_size;
    sfVector2u texr_s;
    sfVector2f scale;

    core->setting.images.background_texture =
        sfTexture_createFromFile("assets/back.png", NULL);
    core->setting.images.background_sprite = sfSprite_create();
    sfSprite_setTexture(core->setting.images.background_sprite,
        core->setting.images.background_texture, sfTrue);
    window_size = sfRenderWindow_getSize(core->window);
    texr_s = sfTexture_getSize(core->setting.images.background_texture);
    scale.x = (float)window_size.x / texr_s.x;
    scale.y = (float)window_size.y / texr_s.y;
    sfSprite_setScale(core->setting.images.background_sprite, scale);
}

void load_button_textures(core_t *core)
{
    core->setting.images.start_texture =
    sfTexture_createFromFile("assets/start_button.png", NULL);
    core->setting.images.start_sprite = sfSprite_create();
    sfSprite_setTexture(core->setting.images.start_sprite,
        core->setting.images.start_texture, sfTrue);
    core->setting.images.quit_texture =
    sfTexture_createFromFile("assets/quit.png", NULL);
    core->setting.images.quit_sprite = sfSprite_create();
    sfSprite_setTexture(core->setting.images.quit_sprite,
        core->setting.images.quit_texture, sfTrue);
    core->setting.images.volup_texture =
    sfTexture_createFromFile("assets/vol_up.jpeg", NULL);
    core->setting.images.volup_sprite = sfSprite_create();
    sfSprite_setTexture(core->setting.images.volup_sprite,
        core->setting.images.volup_texture, sfTrue);
    core->setting.images.voldown_texture =
    sfTexture_createFromFile("assets/vol_down.jpeg", NULL);
    core->setting.images.voldown_sprite = sfSprite_create();
    sfSprite_setTexture(core->setting.images.voldown_sprite,
        core->setting.images.voldown_texture, sfTrue);
}

void create_high_score(core_t *core)
{
    core->setting.images.high_score = sfText_create();
    core->setting.images.score_font = sfFont_createFromFile
        ("assets/Xolonium-Regular.ttf");
    sfText_setString(core->setting.images.high_score, "High Score: 0");
    sfText_setFont(core->setting.images.high_score, core->setting.images.
        score_font);
    sfText_setPosition(core->setting.images.high_score, (sfVector2f)
        {MARGIN, MARGIN});
    sfText_setCharacterSize(core->setting.images.high_score, TEXT_SIZE);
}

void make_menu_textures(core_t *core)
{
    load_background_texture(core);
    load_button_textures(core);
    create_high_score(core);
}

void make_menu(core_t *core)
{
    make_menu_textures(core);
    set_menu_pos(core);
}
