/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** make_door
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"

void health_block(core_t *core)
{
    int i = 0;
    sfVector2u health;

    while (i < 200) {
        health.x = (rand()) % (SIZE - 2);
        health.y = (rand()) % (SIZE - 2);
        if (core->meta.map[health.y][health.x] == 0 &&
        core->meta.map[health.y][health.x + 1] == 1) {
            core->meta.map[health.y][health.x + 1] = 3;
            return;
        }
        if (core->meta.map[health.y][health.x] == 0 &&
        core->meta.map[health.y + 1][health.x] == 1) {
            core->meta.map[health.y + 1][health.x] = 3;
            return;
        }
        i++;
    }
}

void sideway_door(core_t *core)
{
    int i = 0;
    sfVector2u door;

    while (i < 200) {
        door.x = (rand() + 1) % (SIZE - 3);
        door.y = (rand() + 1) % (SIZE - 3);
        if (core->meta.map[door.y][door.x] == 0 &&
        core->meta.map[door.y][door.x + 1] == 1 &&
        core->meta.map[door.y][door.x + 2] == 1 &&
        core->meta.map[door.y][door.x + 3] == 0) {
            core->meta.map[door.y][door.x + 1] = 4;
            core->meta.map[door.y][door.x + 2] = 4;
            return;
        }
        i++;
    }
}

void vertical_door(core_t *core)
{
    int i = 0;
    sfVector2u door;

    while (i < 200) {
        door.x = (rand() + 1) % (SIZE - 3);
        door.y = (rand() + 1) % (SIZE - 3);
        if (core->meta.map[door.y][door.x] == 0 &&
        core->meta.map[door.y + 1][door.x] == 1 &&
        core->meta.map[door.y + 2][door.x] == 1 &&
        core->meta.map[door.y + 3][door.x] == 0) {
            core->meta.map[door.y + 1][door.x] = 4;
            core->meta.map[door.y + 2][door.x] = 4;
            return;
        }
        i++;
    }
}

/*
** makes a 2 2 wide doo somewhere random
*/
void make_blocks(core_t *core)
{
    if (core->meta.save)
        return;
    vertical_door(core);
    sideway_door(core);
    health_block(core);
}
