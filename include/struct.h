/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** struct
*/

#ifndef INCLUDED_STRUCT_H
    #define INCLUDED_STRUCT_H
    #include <SFML/Audio/Types.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Sprite.h>
    #include <SFML/Graphics/CircleShape.h>
    #include <SFML/Graphics/RectangleShape.h>
    #include <SFML/System/Types.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/Window/Event.h>
    #include <SFML/System/Vector2.h>
    #include <stdbool.h>
    #include <SFML/Audio/Music.h>
    #include "entity_list.h"
    #include "wolf_entities.h"
    #define TILE_SIZE 64
    #define MAP_WIDTH 13
    #define MAP_HEIGHT 13
    #define PI 3.14159265
    #define FOV (M_PI / 3)
    #define STEP_SIZE 0.1f
    #define SCREEN_WIDTH 800.0
    #define SCREEN_HEIGHT 600.0
    #define PROJECTION_PLANE ((float)SCREEN_WIDTH / 2) / tan(FOV / 2)
    #define ROTATION_SPEED 0.015f
    #define MOVEMENT_SPEED 0.3f
    #define P2 PI / 2
    #define P3 3 * PI / 2
    #define RADIAN_DEGREE 0.0175533
    #define X_OFFSET 0
    #define Y_OFFSET 1
    #define DOOR 4
    #define TPS 10 // 1/100 in millisecond -> 100 ticks per second
    #define SPRITE_TEXTURE_WIDTH 64
    #define SPRITE_TEXTURE_HEIGHT 64
    #define ENEMY_COUNT 10
    #define DIR 4
    #define SIZE 21
    #define VALUES 19
    #define SPACE 0
    #define ENEMY_SPEED 0.9f
    #define WALL 1
    #define MAX_SCORE_DIGIT 8
    #define HUD_Y_POS ((SCREEN_HEIGHT / 6.0) * 5)
    #define MARGIN (SCREEN_HEIGHT / 60.)
    #define TEXT_SIZE (SCREEN_HEIGHT / 20)
    #define ANIMATION_TIME 400 //time in milliseconds between frames
    #define CLICK_FRAMES 6
    #define MINIMAP_SCALE 0.2f
    #define MINIMAP_TILE_SIZE 10

typedef struct maze {
    size_t col_stack[SIZE * SIZE];
    size_t row_stack[SIZE * SIZE];
    size_t stack_index;
    int directions[DIR];
    int remaining_directions;
    size_t current_col;
    size_t current_row;
} maze_state_t;

typedef enum {
    PERIM,
    NORTH,
    EAST,
    DOOR_WALL,
    NOWHERE,
} cardinal_t;

/*
** for all intents and purposes, this struct was made
** for the sole purpose of avoiding coding style
** do not touch !!
*/
typedef struct sprite_print_struct {
    int draw_start_x;
    int draw_end_x;
    int draw_start_y;
    int draw_end_y;
    int texture_x;
    float sprite_dist;
    int sprite_width;
    float sprite_height;
} sprite_print_t;

/*
** every single ray has this info
*/
typedef struct raycast {
    float horizontal_len; // this is mostly useless
    float vertical_len; // also this
    float wall_height;
    float full_dist; // this is the shortest val between horiz_len and vert_len
    float ray_angle;
    sfTexture* texture;
    int texture_x_pos;
    bool sprite_seen;
} raycast_t;

typedef struct vision {
    raycast_t *all_rays; //all rays array
    sfSprite *sprite;
    player_t *player;
    sfTexture *texture_one;
    sfTexture *texture_two;
    sfTexture *door;
    sfTexture *health;
    unsigned int i;
    sfRenderWindow *window;
    enemy_list_t *enemy_head;
} vision_t;

/*
** bruna's func, alrik's mess
*/
typedef struct menu_img {
    sfTexture *start_texture;
    sfSprite *start_sprite;
    sfTexture *quit_texture;
    sfSprite *quit_sprite;
    sfTexture *volup_texture;
    sfSprite *volup_sprite;
    sfTexture *voldown_texture;
    sfSprite *voldown_sprite;
    sfTexture *background_texture;
    sfSprite *background_sprite;
    sfText *high_score;
    sfFont *score_font;
} menu_img_t;

/*
** TODO: when player dies, set soft_quit to true
*/
typedef struct settings {
    bool start;
    bool soft_quit;
    int volume; //0 to 100
    menu_img_t images;
}sett_t;

typedef struct sounds {
    sfMusic* background_music;
    sfSoundBuffer* walk_buffer; //continuous sound
    sfSound* walk_sound; //continuous sound
    sfSoundBuffer* shoot_buffer; //one shot sound
    sfSound* shoot_sound; //one shot sound
    sfSoundBuffer* dog_buffer; //one shot sound
    sfSound* dog_sound; //one shot sound
    sfSoundBuffer* button_volume_buffer; //one shot sound
    sfSound* button_volume_sound; //one shot sound
} sound_t;

/*
** this is a struct that contains variables
** that i have not made a specific struct for
*/
typedef struct metadata {
    char map[SIZE][SIZE];
    long score;
    bool save;
    bool last_frame_press;
    sfSprite *night;
    sfTexture *night_tex;
} meta_t;

/*
** this func is to make sure that framerate is not exceeded
** we limit the number of operation that happens per frame
*/
typedef struct framerate {
    sfClock *tick;
} frame_t;

typedef struct stats {
    int high_score;
    int dogs_k;
    int gun_k;
    int deaths;
    int wins;
} stats_t;

typedef struct core {
    vision_t *vision;
    sett_t setting;
    entity_t *entities;
    player_t player;
    sfEvent event;
    frame_t frame;
    sound_t sound;
    sfRenderWindow* window;
    stats_t statistics;
    meta_t meta;
} core_t;


extern const int map[MAP_HEIGHT][MAP_WIDTH];

#endif
