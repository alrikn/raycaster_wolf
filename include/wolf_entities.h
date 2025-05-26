/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** wolf_entities.h
*/

#include "entity_list.h"
#include <SFML/System/Vector2.h>

#ifndef WOLF_ENTITIES
    #define WOLF_ENTITIES
typedef enum {
    WP_KNIFE,
    WP_PISTOL,
    WP_UNDEFINED,
} weapon_type_t;

typedef struct {
    float x;
    float y;
    float angle;
    int health;
    int score;
    weapon_type_t wp;
    int ammo;
    bool shooting;
} player_t;

typedef struct enemy_list {
    struct enemy_list *next;
    struct enemy_list *prev;
    float render_x;
    float render_y;
    entity_context_t *context;
    float dist;
    sfSprite *sprite;
} enemy_list_t;


typedef struct enemy_info {
    bool dying : 1;
    bool dead : 1;
    bool activated : 1;
    int death_counter;
    int animation_counter;
    weapon_type_t weapon_type;
    int weapon_cooldown;
    sfVector2f enemy_destination;
    player_t *main_player;
} enemy_info_t;
#endif
