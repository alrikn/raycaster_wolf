/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** handle_rays_new
*/

#include "my.h"
#include "struct.h"
#include <math.h>


/*
** pythagorean method
** always positive
*/
float distance_calculator(float init_x, float end_x, float init_y, float end_y)
{
    float distance = sqrt(((end_x - init_x) * (end_x - init_x)) +
    ((end_y - init_y) * (end_y - init_y)));

    if (distance < 0)
        distance *= -1;
    return distance;
}

static float exception_horizontal(core_t *core, float *horiz_x,
    float *horiz_y)
{
    int search_level = 0;

    *horiz_x = (core->player.x);
    *horiz_y = (core->player.y);
    search_level = 15;
    return search_level;
}

static int horizontal_not_found(float *horiz_x,
    float *horiz_y, float *offset, int search_level)
{
    *horiz_x += offset[X_OFFSET];
    *horiz_y += offset[Y_OFFSET];
    search_level += 1;
    return search_level;
}

static float horizontal_loop(float *offset, float *horiz_x,
    float *horiz_y, core_t *core)
{
    int map_x;
    int map_y;
    int level = 0;

    while (level < 15) {
        map_x = (int)(*horiz_x) >> 6;
        map_y = (int)(*horiz_y) >> 6;
        map_x = map_x < 0 ? 0 : map_x;
        map_x = map_x >= SIZE ? SIZE - 1 : map_x;
        map_y = map_y < 0 ? 0 : map_y;
        map_y = map_y >= SIZE ? SIZE - 1 : map_y;
        if (map_x >= 0 && map_x < SIZE &&
            map_y >= 0 && map_y < SIZE && core->meta.map[map_y][map_x] >= 1) {
            return distance_calculator(core->player.x, *horiz_x,
            core->player.y, *horiz_y);
        } else
            level = horizontal_not_found(horiz_x, horiz_y, offset, level);
    }
    return 100000;
}

/*
** this checks horizontal intersections
** TODO fix: search level
*/
float draw_horizontal(float ray_angle, float *horiz_x,
    float *horiz_y, core_t *core)
{
    float aTan = -1 / tan(ray_angle);
    float offset[2];

    if (ray_angle > M_PI) {
        *horiz_y = (((int)(core->player.y) >> 6) << 6) - 0.0001;
        *horiz_x = ((core->player.y) - *horiz_y) * aTan + (core->player.x);
        offset[Y_OFFSET] = -64;
        offset[X_OFFSET] = -offset[Y_OFFSET] * aTan;
    }
    if (ray_angle < M_PI) {
        *horiz_y = (((int)(core->player.y) >> 6) << 6) + 64;
        *horiz_x = ((core->player.y) - *horiz_y) * aTan + (core->player.x);
        offset[Y_OFFSET] = 64;
        offset[X_OFFSET] = -offset[Y_OFFSET] * aTan;
    }
    if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591))
        exception_horizontal(core, horiz_x, horiz_y);
    return horizontal_loop(offset, horiz_x, horiz_y, core);
}

static int vertical_not_found(float *vertical_x,
    float *vertical_y, float *offset, int search_level)
{
    *vertical_x += offset[X_OFFSET];
    *vertical_y += offset[Y_OFFSET];
    search_level += 1;
    return search_level;
}

static float vertical_loop(core_t *core, float *vertical_x,
    float *vertical_y, float *offset)
{
    int map_x;
    int map_y;
    int search_level = 0;

    while (search_level < 15) {
        map_x = (int)(*vertical_x) >> 6;
        map_y = (int)(*vertical_y) >> 6;
        map_x = map_x < 0 ? 0 : map_x;
        map_x = map_x >= SIZE ? SIZE - 1 : map_x;
        map_y = map_y < 0 ? 0 : map_y;
        map_y = map_y >= SIZE ? SIZE - 1 : map_y;
        if (map_x >= 0 && map_x < SIZE &&
            map_y >= 0 && map_y < SIZE && core->meta.map[map_y][map_x] >= 1) {
            return distance_calculator(core->player.x, *vertical_x,
            core->player.y, *vertical_y);
        } else
            search_level = vertical_not_found(vertical_x, vertical_y,
            offset, search_level);
    }
    return 1000000;
}

static float exception_vertical(core_t *core, float *vertical_x,
    float *vertical_y)
{
    int search_level = 0;

    *vertical_x = (core->player.x);
    *vertical_y = (core->player.y);
    search_level = 15;
    return search_level;
}

/*
** this checks vertical intersections
*/
float draw_vertical(float ray_angle, float *ver_x,
    float *ver_y, core_t *core)
{
    float nTan = -tan(ray_angle);
    float offset[2];

    if (ray_angle > P2 && ray_angle < P3) {
        *ver_x = (((int)(core->player.x) >> 6) << 6) - 0.0001;
        *ver_y = ((core->player.x) - *ver_x) * nTan + (core->player.y);
        offset[X_OFFSET] = -64;
        offset[Y_OFFSET] = -offset[X_OFFSET] * nTan;
    }
    if (ray_angle < P2 || ray_angle > P3) {
        *ver_x = (((int)(core->player.x) >> 6) << 6) + 64;
        *ver_y = ((core->player.x) - *ver_x) * nTan + (core->player.y);
        offset[X_OFFSET] = 64;
        offset[Y_OFFSET] = -offset[X_OFFSET] * nTan;
    }
    if (ray_angle == 0 || (ray_angle < 3.141593 && ray_angle > 3.141591))
        exception_vertical(core, ver_x, ver_y);
    return vertical_loop(core, ver_x, ver_y, offset);
}
