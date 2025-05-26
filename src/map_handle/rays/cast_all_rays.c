/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** cast_all_rays
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <math.h>

static float ray_angle_maker(const float i, const player_t *player)
{
    const float start_angle = player->angle - FOV / 2;
    const float angle_step = FOV / SCREEN_WIDTH;
    float ray_angle = 0.0;

    ray_angle = fmod(start_angle + i * angle_step, 2 * M_PI);
    if (ray_angle < 0)
        ray_angle += 2 * PI;
    if (ray_angle > 2 * PI)
        ray_angle -= 2 * PI;
    return ray_angle;
}

/*
** fish eye correcter
*/
float draw_handler(float ray_angle, float full_dist, player_t *player)
{
    float delta_angle;
    float corrected_dist;

    delta_angle = ray_angle - player->angle;
    corrected_dist = full_dist * cosf(delta_angle);
    if (corrected_dist <= 0)
        corrected_dist = 0.0001;
    return corrected_dist;
}

/*
** here we find the dist as well as the colour
*/
void find_dist(vision_t *vision, float ray_angle, int i,
    core_t *core)
{
    float horizontal_ray_x;
    float horizontal_ray_y;
    float vertical_ray_x;
    float vertical_ray_y;

    vision->all_rays[i].horizontal_len = draw_horizontal(ray_angle,
    &horizontal_ray_x, &horizontal_ray_y, core);
    vision->all_rays[i].vertical_len = draw_vertical(ray_angle,
    &vertical_ray_x, &vertical_ray_y, core);
    if (vision->all_rays[i].vertical_len >
    vision->all_rays[i].horizontal_len) {
        north_south(core, vision, horizontal_ray_x, horizontal_ray_y);
    } else {
        east_west(core, vision, vertical_ray_x, vertical_ray_y);
    }
}

/*
** alrik handles all of the realted function, do not touch
** pthreads
*/
void cast_all_rays(player_t *player, sfRenderWindow* window,
    vision_t *vision, core_t *core)
{
    vision->window = window;
    bubble_sort(&vision->enemy_head);
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        vision->i = i;
        vision->all_rays[i].ray_angle = ray_angle_maker(i, player);
        find_dist(vision,
        vision->all_rays[i].ray_angle, i, core);
        vision->all_rays[i].wall_height = (TILE_SIZE / draw_handler(
        vision->all_rays[i].ray_angle, vision->all_rays[i].full_dist, player))
        * PROJECTION_PLANE;
        render_wall_column(i, vision);
        render_sprites(vision, i);
    }
}
