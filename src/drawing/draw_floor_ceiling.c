/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** draw_floor_ceiling
*/

#include "entity_list.h"
#include "my.h"
#include "math.h"
#include "struct.h"
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Types.h>


/*
** closer to the middle the darker
*/
void draw_floor(sfRenderWindow* window, const int center_y,
    const float max_distance, float distance)
{
    float normalized = 0.0;
    float brightness = 0.0;
    sfColor floor_color;
    sfRectangleShape* line;

    for (int y = center_y; y < SCREEN_HEIGHT; y++) {
        distance = y - center_y;
        normalized = distance / max_distance;
        brightness = powf(normalized, 2.0f);
        floor_color = sfColor_fromRGB(140, 80, 15);
        floor_color.r *= brightness;
        floor_color.g *= brightness;
        floor_color.b *= brightness;
        line = sfRectangleShape_create();
        sfRectangleShape_setSize(line, (sfVector2f){SCREEN_WIDTH, 1});
        sfRectangleShape_setPosition(line, (sfVector2f){0, y});
        sfRectangleShape_setFillColor(line, floor_color);
        sfRenderWindow_drawRectangleShape(window, line, NULL);
        sfRectangleShape_destroy(line);
    }
}

sfIntRect rectangle_getter(float left, float tex_fov_width,
    const sfVector2u tex_size)
{
    sfIntRect rectangle = {
        .left = (int)left,
        .top = 0,
        .width = (int)tex_fov_width,
        .height = tex_size.y
    };

    return rectangle;
}

/*
** this is not working
*/
void draw_ceiling(sfRenderWindow* window, core_t *core, int center_y)
{
    const sfTexture *tex = sfSprite_getTexture(core->meta.night);
    const sfVector2u tex_size = sfTexture_getSize(tex);
    float norm_angle = fmodf(core->player.angle, 2 * PI);
    float tex_fov_width = (FOV / (2 * PI)) * tex_size.x;
    float tex_center_x = (norm_angle / (2 * PI)) * tex_size.x;
    float left = tex_center_x - tex_fov_width / 2;

    if (left < 0)
        left += tex_size.x;
    if (left + tex_fov_width > tex_size.x)
        left = fmodf(left, tex_size.x);
    sfSprite_setTextureRect(core->meta.night,
    rectangle_getter(left, tex_fov_width, tex_size));
    sfSprite_setPosition(core->meta.night, (sfVector2f){0, 0});
    sfSprite_setScale(core->meta.night, (sfVector2f){
        SCREEN_WIDTH / tex_fov_width,
        center_y / (float)tex_size.y
    });
    sfRenderWindow_drawSprite(window, core->meta.night, NULL);
}

void draw_floor_and_ceiling(sfRenderWindow* window, core_t *core)
{
    const int center_y = SCREEN_HEIGHT / 2;
    const float max_distance = center_y;

    draw_ceiling(window, core, center_y);
    draw_floor(window, center_y, max_distance, 0);
}
