/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** core->player_potential
*/

#include "my.h"
#include "struct.h"
#include "math.h"
#include <stdio.h>

/*
**this to make the core->player slide if it runs into a wall
*/
void handle_sliding(core_t *core, float new_x, float new_y)
{
    if (!is_wall(core, new_x, core->player.y) && new_x > 0) {
        if (print_handle(core->player.x, core->player.y,
        core->player.y, new_x))
            print_pos(new_x, core->player.y, core);
        core->player.x = new_x;
        return;
    }
    if (!is_wall(core, core->player.x, new_y) && new_y > 0) {
        if (print_handle(core->player.x, core->player.y,
        new_y, core->player.x))
            print_pos(core->player.x, new_y, core);
        core->player.y = new_y;
        return;
    }
}

///*
//** pot force is the amount of force you want to apply to the core->player
//(knockback purposes mostly)
//** force angle is where your applying the force
//** we handle the actual movement in another func
//*/
//void move_potential(core->player_t *core->player,
//float pot_force, float force_angle)
//{
//    float move_x = cosf(force_angle) * MOVEMENT_SPEED * pot_force;
//    float move_y = sinf(force_angle) * MOVEMENT_SPEED * pot_force;
//
//    core->player->force_x += move_x;
//    core->player->force_y += move_y;
//}
//
