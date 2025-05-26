/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** init_hud.c
*/

#include "entity_list.h"
#include "struct.h"
#include "my.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include <stdio.h>

static void init_hud_bg(entity_t *hud_bg)
{
    hud_bg->context->texture = NULL;
    sfRectangleShape_setFillColor(hud_bg->data, sfColor_fromRGB(48, 48, 48));
    sfRectangleShape_setSize(hud_bg->data, (sfVector2f){SCREEN_WIDTH,
        SCREEN_HEIGHT / 5});
    sfRectangleShape_setPosition(hud_bg->data, (sfVector2f){0, HUD_Y_POS});
    hud_bg->update = NULL;
}

static void init_hp_title(entity_t *title)
{
    title->update = NULL;
    sfText_setPosition(title->data, (sfVector2f){SCREEN_WIDTH / 14,
        HUD_Y_POS + MARGIN});
    sfText_setCharacterSize(title->data, TEXT_SIZE);
    title->context->font = sfFont_createFromFile
        ("assets/Xolonium-Regular.ttf");
    sfText_setFillColor(title->data, sfColor_fromRGBA(255, 255, 255, 180));
    sfText_setFont(title->data, title->context->font);
    sfText_setStyle(title->data, sfTextRegular);
    sfText_setString(title->data, "HP");
    return;
}

static void init_hp(entity_t *hp)
{
    hp->update = update_hp;
    sfText_setPosition(hp->data, (sfVector2f){SCREEN_WIDTH / 30, SCREEN_HEIGHT
        - MARGIN - TEXT_SIZE * 1.35});
    sfText_setCharacterSize(hp->data, TEXT_SIZE * 1.35);
    hp->context->font = sfFont_createFromFile("assets/Xolonium-Regular.ttf");
    sfText_setFillColor(hp->data, sfColor_fromRGBA(255, 255, 255, 220));
    sfText_setFont(hp->data, hp->context->font);
    sfText_setStyle(hp->data, sfTextRegular);
    sfText_setString(hp->data, "100%");
    return;
}

static void init_score_title(entity_t *title)
{
    title->update = NULL;
    sfText_setPosition(title->data, (sfVector2f){SCREEN_WIDTH / 14 + 150,
        HUD_Y_POS + MARGIN});
    sfText_setCharacterSize(title->data, TEXT_SIZE);
    title->context->font = sfFont_createFromFile
        ("assets/Xolonium-Regular.ttf");
    title->context->texture = NULL;
    sfText_setFillColor(title->data, sfColor_fromRGBA(255, 255, 255, 180));
    sfText_setFont(title->data, title->context->font);
    sfText_setStyle(title->data, sfTextRegular);
    sfText_setString(title->data, "SCORE");
    return;
}

static void init_score(entity_t *score)
{
    score->update = update_score;
    sfText_setPosition(score->data, (sfVector2f){SCREEN_WIDTH / 30 + 232,
        SCREEN_HEIGHT - MARGIN - TEXT_SIZE * 1.35});
    sfText_setCharacterSize(score->data, TEXT_SIZE * 1.35);
    score->context->font = sfFont_createFromFile
        ("assets/Xolonium-Regular.ttf");
    sfText_setFillColor(score->data, sfColor_fromRGBA(255, 255, 255, 220));
    sfText_setFont(score->data, score->context->font);
    sfText_setStyle(score->data, sfTextRegular);
    sfText_setString(score->data, "0");
    return;
}

static void init_ammo_title(entity_t *title)
{
    title->update = NULL;
    sfText_setPosition(title->data, (sfVector2f){SCREEN_WIDTH / 14 + 350,
        HUD_Y_POS + MARGIN});
    sfText_setCharacterSize(title->data, TEXT_SIZE);
    title->context->font = sfFont_createFromFile
        ("assets/Xolonium-Regular.ttf");
    title->context->texture = NULL;
    sfText_setFillColor(title->data, sfColor_fromRGBA(255, 255, 255, 180));
    sfText_setFont(title->data, title->context->font);
    sfText_setStyle(title->data, sfTextRegular);
    sfText_setString(title->data, "AMMO");
    return;
}

static void init_ammo(entity_t *ammo)
{
    ammo->update = update_ammo;
    sfText_setPosition(ammo->data, (sfVector2f){SCREEN_WIDTH / 30 + 397,
        SCREEN_HEIGHT - MARGIN - TEXT_SIZE * 1.35});
    sfText_setCharacterSize(ammo->data, TEXT_SIZE * 1.35);
    ammo->context->font = sfFont_createFromFile
        ("assets/Xolonium-Regular.ttf");
    ammo->context->texture = NULL;
    sfText_setFillColor(ammo->data, sfColor_fromRGBA(255, 255, 255, 220));
    sfText_setFont(ammo->data, ammo->context->font);
    sfText_setStyle(ammo->data, sfTextRegular);
    sfText_setString(ammo->data, "0");
    return;
}

static void init_weapon(entity_t *weapon)
{
    weapon->context->texture_rect = (sfIntRect){172, 84, 96, 48};
    weapon->update = update_weapon;
    weapon->context->texture = sfTexture_createFromFile
        ("assets/grey-white_weapons.png", &weapon->context->texture_rect);
    sfSprite_setPosition(weapon->data,
        (sfVector2f){SCREEN_WIDTH - 230, HUD_Y_POS});
    sfSprite_setScale(weapon->data, (sfVector2f){4, 4});
    sfSprite_setTexture(weapon->data, weapon->context->texture, sfFalse);
    return;
}

static void init_hand(entity_t *crosshair)
{
    crosshair->update = update_hand;
    crosshair->context->entity_rect = (sfIntRect){1, 104, 101, 101};
    crosshair->context->texture = sfTexture_createFromFile
        ("assets/player_hand.png", NULL);
    crosshair->clock = sfClock_create();
    sfSprite_setScale(crosshair->data, (sfVector2f){3, 3});
    sfSprite_setPosition(crosshair->data,
        (sfVector2f){(SCREEN_WIDTH / 2) - 151, HUD_Y_POS - 303});
    sfSprite_setTexture(crosshair->data, crosshair->context->texture, sfFalse);
    sfSprite_setTextureRect(crosshair->data, crosshair->context->entity_rect);
    return;
}

void init_hud(core_t *core)
{
    init_hp_title(append_entity(&core->entities, SF_TEXT, HUD_TITLE));
    init_hp(append_entity(&core->entities, SF_TEXT, HUD_HEALTH));
    init_score_title(append_entity(&core->entities, SF_TEXT, HUD_TITLE));
    init_score(append_entity(&core->entities, SF_TEXT, HUD_SCORE));
    init_ammo_title(append_entity(&core->entities, SF_TEXT, HUD_TITLE));
    init_ammo(append_entity(&core->entities, SF_TEXT, HUD_AMMO));
    init_weapon(append_entity(&core->entities, SF_SPRITE, HUD_WEAPON));
    init_hand(append_entity(&core->entities, SF_SPRITE, HUD_CROSSHAIR));
    init_hud_bg(append_entity(&core->entities, SF_RECTANGLE, HUD_BG));
}
