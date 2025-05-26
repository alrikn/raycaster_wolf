/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** handle_textures
*/

#include "my.h"
#include <math.h>

static void north_south_special(core_t *core, vision_t *vis,
    float horiz_ray_x, float horiz_ray_y)
{
    int tex_width;
    int tex_x;
    int map_x = (int)(horiz_ray_x) / TILE_SIZE;
    int map_y = (int)(horiz_ray_y) / TILE_SIZE;

    if (core->meta.map[map_y][map_x] == 4) {
        tex_width = sfTexture_getSize(vis->door).x;
        tex_x = ((int)(horiz_ray_x) % TILE_SIZE) * (tex_width / TILE_SIZE);
        if (sinf(vis->all_rays[vis->i].ray_angle) > 0)
            tex_x = tex_width - tex_x - 1;
        vis->all_rays[vis->i].texture = vis->door;
    }
    if (core->meta.map[map_y][map_x] == 3) {
        tex_width = sfTexture_getSize(vis->health).x;
        tex_x = ((int)(horiz_ray_x) % TILE_SIZE) * (tex_width / TILE_SIZE);
        if (sinf(vis->all_rays[vis->i].ray_angle) > 0)
            tex_x = tex_width - tex_x - 1;
        vis->all_rays[vis->i].texture = vis->health;
    }
    vis->all_rays[vis->i].texture_x_pos = tex_x;
}

void north_south(core_t *cor, vision_t *vis,
    float horiz_ray_x, float horiz_ray_y)
{
    int map_x = (int)(horiz_ray_x) / TILE_SIZE;
    int map_y = (int)(horiz_ray_y) / TILE_SIZE;
    int tex_width;
    int tex_x;

    if (cor->meta.map[map_y][map_x] == 4 || cor->meta.map[map_y][map_x] == 3) {
        north_south_special(cor, vis, horiz_ray_x, horiz_ray_y);
    } else {
        tex_width = sfTexture_getSize(vis->texture_one).x;
        tex_x = ((int)(horiz_ray_x) % TILE_SIZE) * (tex_width / TILE_SIZE);
        if (sinf(vis->all_rays[vis->i].ray_angle) > 0)
            tex_x = tex_width - tex_x - 1;
        vis->all_rays[vis->i].texture = vis->texture_one;
        vis->all_rays[vis->i].texture_x_pos = tex_x;
    }
    vis->all_rays[vis->i].full_dist = vis->all_rays[vis->i].horizontal_len;
}

static void east_west_special(core_t *core, vision_t *vis,
    float vertical_ray_x, float vertical_ray_y)
{
    int tex_width;
    int tex_x;
    int map_x = (int)(vertical_ray_x) / TILE_SIZE;
    int map_y = (int)(vertical_ray_y) / TILE_SIZE;

    if (core->meta.map[map_y][map_x] == 4) {
        tex_width = sfTexture_getSize(vis->door).x;
        tex_x = ((int)(vertical_ray_y) % TILE_SIZE) * (tex_width / TILE_SIZE);
        if (cosf(vis->all_rays[vis->i].ray_angle) < 0)
            tex_x = tex_width - tex_x - 1;
        vis->all_rays[vis->i].texture = vis->door;
    }
    if (core->meta.map[map_y][map_x] == 3) {
        tex_width = sfTexture_getSize(vis->health).x;
        tex_x = ((int)(vertical_ray_y) % TILE_SIZE) * (tex_width / TILE_SIZE);
        if (cosf(vis->all_rays[vis->i].ray_angle) < 0)
            tex_x = tex_width - tex_x - 1;
        vis->all_rays[vis->i].texture = vis->health;
    }
    vis->all_rays[vis->i].texture_x_pos = tex_x;
}

void east_west(core_t *cor, vision_t *vis,
    float vertical_ray_x, float vertical_ray_y)
{
    int map_x = (int)(vertical_ray_x) / TILE_SIZE;
    int map_y = (int)(vertical_ray_y) / TILE_SIZE;
    int tex_width;
    int tex_x;

    if (cor->meta.map[map_y][map_x] == 4 || cor->meta.map[map_y][map_x] == 3) {
        east_west_special(cor, vis, vertical_ray_x, vertical_ray_y);
    } else {
        tex_width = sfTexture_getSize(vis->texture_two).x;
        tex_x = ((int)(vertical_ray_y) % TILE_SIZE) * (tex_width / TILE_SIZE);
        if (cosf(vis->all_rays[vis->i].ray_angle) < 0)
            tex_x = tex_width - tex_x - 1;
        vis->all_rays[vis->i].texture = vis->texture_two;
        vis->all_rays[vis->i].texture_x_pos = tex_x;
    }
    vis->all_rays[vis->i].full_dist = vis->all_rays[vis->i].vertical_len;
}
