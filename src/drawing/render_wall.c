/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** render_wall
*/

#include "my.h"
#include <math.h>

static void shading(sfSprite* sprite, vision_t *vision, int column)
{
    sfColor color = sfColor_fromRGB(255, 255, 255);
    float darkness = fmin(1.0f, vision->all_rays[column].wall_height / 400.0f);

    color.r *= darkness;
    color.g *= darkness;
    color.b *= darkness;
    sfSprite_setColor(sprite, color);
}

static sfIntRect set_texture(int texture_x, int tex_height)
{
    sfIntRect texture_rect = {
        .left = texture_x,
        .top = 0,
        .width = 1,
        .height = tex_height
    };

    return texture_rect;
}

static void draw_column(int column, vision_t *vision,
    sfSprite* sprite, int tex_height)
{
    float y_pos;
    float scale_x;
    float scale_y;

    scale_x = (float)SCREEN_WIDTH / SCREEN_WIDTH;
    scale_y = vision->all_rays[column].wall_height / (float)tex_height;
    sfSprite_setScale(sprite, (sfVector2f){scale_x, scale_y});
    y_pos = ((float)SCREEN_HEIGHT / 2) -
    (vision->all_rays[column].wall_height / 2);
    sfSprite_setPosition(sprite, (sfVector2f){column * scale_x, y_pos});
    shading(sprite, vision, column);
    sfRenderWindow_drawSprite(vision->window, sprite, NULL);
}

void render_wall_column(int column, vision_t *vision)
{
    sfSprite* sprite = vision->sprite;
    sfTexture* texture = vision->all_rays[column].texture;
    int texture_x = vision->all_rays[column].texture_x_pos;
    int tex_width = sfTexture_getSize(texture).x;
    int tex_height = sfTexture_getSize(texture).y;
    sfIntRect texture_rect;

    if (texture_x < 0)
        texture_x = 0;
    if (texture_x >= tex_width)
        texture_x = tex_width - 1;
    texture_rect = set_texture(texture_x, tex_height);
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setTextureRect(sprite, texture_rect);
    draw_column(column, vision, sprite, tex_height);
}
