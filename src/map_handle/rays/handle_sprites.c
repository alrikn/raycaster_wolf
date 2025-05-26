/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_sprites
*/

#include "my.h"
#include "struct.h"
#include <SFML/System/Vector2.h>
#include <math.h>
#include <stdio.h>

static float set_angle_diff(vision_t *vision, enemy_list_t *enemy)
{
    float sprite_dx = enemy->render_x - vision->player->x;
    float sprite_dy = enemy->render_y - vision->player->y;
    float sprite_angle = atan2f(sprite_dy, sprite_dx);
    float angle_diff;

    if (sprite_angle < 0)
        sprite_angle += 2 * M_PI;
    angle_diff = sprite_angle - vision->player->angle;
    if (angle_diff > M_PI)
        angle_diff -= 2 * M_PI;
    if (angle_diff < - M_PI)
        angle_diff += 2 * M_PI;
    return angle_diff;
}

static void set_scale(sfSprite* sprite, float draw_end_y,
    float draw_start_y, int texture_x)
{
    const sfTexture* texture = sfSprite_getTexture(sprite);
    int texture_height = sfTexture_getSize(texture).y;
    sfIntRect texture_rect = {
    texture_x, 0,
    1, texture_height
    };
    float scale_y;

    sfSprite_setTextureRect(sprite, texture_rect);
    scale_y = (float)(draw_end_y - draw_start_y) / texture_height;
    sfSprite_setScale(sprite, (sfVector2f){1.0f, scale_y});
}

/*
** animation counter is which one we are currently on
** each image in the spriteshhet is 64 pix wide
** so i check wich frame the sprite is on, and i move to it
*/
static bool should_draw(enemy_list_t *enemy, sprite_print_t hold,
    int column, vision_t *vision)
{
    int frame_i = ((enemy_info_t *)(enemy->context->info))->animation_counter;
    int frame_offset = frame_i * SPRITE_TEXTURE_WIDTH;

    hold.texture_x += frame_offset;
    set_scale(enemy->sprite, hold.draw_end_y,
    hold.draw_start_y, hold.texture_x);
    sfSprite_setPosition(enemy->sprite, (sfVector2f){
        (float)column,
        (float)hold.draw_start_y
    });
    sfRenderWindow_drawSprite(vision->window, enemy->sprite, NULL);
    return true;
}

static sprite_print_t set_values(sprite_print_t hold,
    int sprite_screen_x, int column)
{
    hold.sprite_height = (TILE_SIZE / hold.sprite_dist) * PROJECTION_PLANE;
    hold.draw_start_y = ((float)SCREEN_HEIGHT / 2) - (hold.sprite_height / 2);
    hold.draw_end_y = hold.draw_start_y + hold.sprite_height;
    hold.sprite_width = hold.sprite_height;
    hold.draw_start_x = sprite_screen_x - hold.sprite_width / 2;
    hold.draw_end_x = sprite_screen_x + hold.sprite_width / 2;
    hold.texture_x = (column - hold.draw_start_x) *
    SPRITE_TEXTURE_WIDTH / hold.sprite_width;
    return hold;
}

static bool loop_handle(vision_t *vision, int column, enemy_list_t *enemy)
{
    sprite_print_t hold = {0};
    bool seen = false;
    float sprite_dx = enemy->render_x - vision->player->x;
    float sprite_dy = enemy->render_y - vision->player->y;
    float angle_diff = set_angle_diff(vision, enemy);
    int sprite_screen_x = (int)((0.5f + (angle_diff / (FOV))) * SCREEN_WIDTH);

    hold.sprite_dist = sqrtf(sprite_dx * sprite_dx + sprite_dy * sprite_dy);
    enemy->dist = hold.sprite_dist;
    hold = set_values(hold, sprite_screen_x, column);
    if (column >= hold.draw_start_x && column < hold.draw_end_x) {
        if (hold.sprite_dist < vision->all_rays[column].full_dist)
            seen = should_draw(enemy, hold, column, vision);
    }
    return seen;
}

/*
*/
void render_sprites(vision_t *vision, int column)
{
    enemy_list_t *enemy = vision->enemy_head;
    bool seen = false;

    while (enemy != NULL) {
        if (((enemy_info_t *)(enemy->context->info))->dead) {
            enemy = enemy->next;
            continue;
        }
        if (!((enemy_info_t *)(enemy->context->info))->dead) {
            enemy->render_x = enemy->context->position.x;
            enemy->render_y = enemy->context->position.y;
            seen = loop_handle(vision, column, enemy);
        }
        if (seen) {
            ((enemy_info_t *)enemy->context->info)->activated = true;
        }
        enemy = enemy->next;
    }
}
