/*
** EPITECH PROJECT, 2025
** bootstrap_raycasting
** File description:
** handle_input
*/

#include "my.h"
#include "math.h"
#include "struct.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundStatus.h>
#include <SFML/Window/Keyboard.h>
#include <stdbool.h>
#include <stdio.h>

static float normalize_angle(float angle)
{
    angle = fmodf(angle, 2 * M_PI);
    if (angle <= 0)
        angle += 2 * M_PI;
    return angle;
}

static bool rotate(sfEvent *event, player_t *player)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        player->angle -= ROTATION_SPEED;
    }
    if (sfKeyboard_isKeyPressed(sfKeyE)) {
        player->angle += ROTATION_SPEED;
    }
    player->angle = normalize_angle(player->angle);
    return true;
}

/*
**should only print if the player is in a new tile
*/
bool print_handle(int player_x, int player_y, int old_y, int old_x)
{
    player_x = player_x / TILE_SIZE;
    player_y = player_y / TILE_SIZE;
    old_x = old_x / TILE_SIZE;
    old_y = old_y / TILE_SIZE;
    if (player_x != old_x || player_y != old_y)
        return true;
    return false;
}

static bool move_player(player_t *player, float move_dir,
    float angle, core_t *core)
{
    float move_x = cosf(angle) * MOVEMENT_SPEED * move_dir;
    float move_y = sinf(angle) * MOVEMENT_SPEED * move_dir;
    float new_x = player->x + move_x;
    float new_y = player->y + move_y;

    if (core->sound.walk_sound &&
    sfSound_getStatus(core->sound.walk_sound) != sfPlaying)
        sfSound_play(core->sound.walk_sound);
    if (!is_wall(core, new_x, new_y) && new_x > 0 && new_y > 0) {
        if (print_handle(player->x, player->y, new_y, new_x))
            print_pos(new_x, new_y, core);
        player->x = new_x;
        player->y = new_y;
    } else
        handle_sliding(core, new_x, new_y);
    return true;
}

bool handle_player_move(sfEvent *event, player_t *player, core_t *core)
{
    bool happened = false;

    if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyE))
        happened = rotate(event, player);
    if (sfKeyboard_isKeyPressed(sfKeyW) || sfKeyboard_isKeyPressed(sfKeyUp))
        happened = move_player(player, 4, player->angle, core);
    if (sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown))
        happened = move_player(player, -3, player->angle, core);
    if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight))
        happened = move_player(player, 2, player->angle + P2, core);
    if (sfKeyboard_isKeyPressed(sfKeyA) || sfKeyboard_isKeyPressed(sfKeyLeft))
        happened = move_player(player, 2, player->angle - P2, core);
    return happened;
}

static void change_weapon(core_t *core)
{
    if (sfKeyboard_isKeyPressed(sfKeyNum1)) {
        core->player.wp = WP_KNIFE;
    }
    if (sfKeyboard_isKeyPressed(sfKeyNum2))
        core->player.wp = WP_PISTOL;
}

bool key_pressed(sfEvent *event, player_t *player, core_t *core)
{
    bool happened = false;
    bool attack = sfKeyboard_isKeyPressed(sfKeyEnter) ||
    sfMouse_isButtonPressed(sfMouseLeft);

    happened = handle_player_move(event, player, core);
    change_weapon(core);
    if (sfKeyboard_isKeyPressed(sfKeyI) || sfKeyboard_isKeyPressed(sfKeySpace))
        interact_with_block(core);
    if (attack && !core->meta.last_frame_press)
        player_attack(core);
    if (sfKeyboard_isKeyPressed(sfKeyM))
        print_mini_map(core);
    core->meta.last_frame_press = attack;
    return happened;
}
