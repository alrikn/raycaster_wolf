/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** Header file for the tasks today
*/
#include "entity_list.h"
#ifndef COMMON_H
    #include <unistd.h>
    #include <limits.h>
    #include <stdlib.h>
    #include "struct.h"
    #include "menu_bar.h"
    #include <stdlib.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #include <stdio.h>
    #define COMMON_H
    #define MAX_INT 2147483647
    #define MIN_INT –2147483648
    #define BUCKET_LIMIT 10
    #define COLLISION_THRESHOLD 20
    #define MAX_BUCKET_SIZE 4
    #define MAX_PARTITIONS 4
    #define UNUSED_ATTR __attribute__((unused))
//utils

void my_putchar(char);
int my_putstr(char const *);
int my_error_putstr(char const *str);
int my_strlen(char const *);
char *my_strcpy(char *, char const *);
char *my_strncpy(char *, char const *, int);
int my_strncmp(char const *, char const *, int);
int my_strcmp(char const *, char const *);
char *my_strstr(char *, char const *);
void my_charswap(char *, char *);
char *my_revstr(char *);
int my_strncmp(char const *, char const *, int);
int my_strcmp(char const *, char const *);
int my_str_isalpha(char const *);
int my_str_islower(char const *);
int my_str_isupper(char const *);
int my_str_isnum(char const *);
char *my_strcat(char *, char const *);
int my_compute_power_rec(int, int);
int my_find_prime_sup(int);
int my_getnbr(char const *);
int my_isneg(int);
int my_is_prime(int);
void do_recursive_int_extraction(int);
int my_put_nbr(int);
int my_showmem(char const *, int);
int my_showstr(char const *);
void my_sort_int_array(int *, int);
int check_to_capitalize_next(char *);
char *my_strcapitalize(char *);
int my_str_isprintable(char const *);
char *my_strlowcase(char *);
char *my_strncat(char *, char const *, int);
char *my_strupcase(char *);
void my_swap(int *, int *);
char *my_strtok(char *str, const char *delim);
double my_strtodouble(const char *ptr);
int my_cooler_putstr(char const *str);
char *my_strdup(char const *src);
char *num_to_str(int num);

// sprite updates

bool update_enemy(entity_t *entity, core_t *core);
float get_distance(sfVector2f *pos1, sfVector2f *pos2);
bool enemy_attack(entity_t *enemy, core_t *core);
//menu screen

void handle_button_clicks(core_t *core);
void menu_screen(core_t *core);

// game loop

void game_loop(core_t *core);
void limit_frame_hard(core_t *core);
void reset_values(core_t *core);

//memory
void destroy_everything(core_t *core);
void game_play_prep(core_t *core);

// player

void init_player(player_t *player); // Inits the player's position and angle
void player_attack(core_t *core);

//collision detection
int is_wall(core_t *core, int x, int y);// Returns 1 if the pos is a wall

//drawing
void print_mini_map(core_t *core);
void draw_floor_and_ceiling(sfRenderWindow* window, core_t *core);
void render_sprites(vision_t *vision, int column);
void north_south(core_t *cor, vision_t *vis,
    float horiz_ray_x, float horiz_ray_y);
void east_west(core_t *core, vision_t *vis,
    float vertical_ray_x, float vertical_ray_y);

//save system
void print_save(core_t *core);
void parse_save(core_t *core);


//update_hud

bool update_hp(entity_t *entity, core_t *core);
bool update_score(entity_t *entity, core_t *core);
bool update_ammo(entity_t *entity, core_t *core);
bool update_weapon(entity_t *entity, core_t *core);
bool update_hand(entity_t *entity, core_t *core);

//wall stuff
void render_wall_column(int column, vision_t *vision);
void make_blocks(core_t *core);

//stats
void write_statistics(core_t *core);
int stat_error(core_t *core);
void read_statistics(core_t *core);

//initialization

sfRenderWindow* create_window(void);
void make_core(core_t *core);
void vision_initialize(player_t *player, vision_t *vision,
    sfRenderWindow* window);
bool init_enemy(entity_t *entity, core_t *core);
bool init_sprite(entity_t *entity, core_t *core);
void maze_generator(char array[SIZE][SIZE]);
void make_menu(core_t *core);
void init_hud(core_t *core);
entity_t *append_entity(entity_t **head, entity_type_t entity_type,
    context_type_t context_type);
sfVector2f rand_pos(core_t *core);

//miscellaneous

void interact_with_block(core_t *core);
void handle_closure(sfRenderWindow* window, sfEvent *event, player_t *player);
cardinal_t find_cardinal(float hit_x, float hit_y);
void cast_all_rays(player_t *player, sfRenderWindow* window,
    vision_t *vison, core_t *core);
float draw_vertical(float ray_angle, float *vertical_x,
    float *vertical_y, core_t *core);
float draw_horizontal(float ray_angle, float *horizontal_x,
    float *horizontal_y, core_t *core);
bool print_handle(int player_x, int player_y, int old_y, int old_x);
void handle_sliding(core_t *core, float new_x, float new_y);
void move_potential(player_t *player, float pot_force, float force_angle);
void apply_potential(player_t *player);
float cast_single_ray(player_t player, float ray_angle,
    sfRenderWindow *window);
bool key_pressed(sfEvent *event, player_t *player, core_t *core);
void print_pos(int player_x, int player_y, core_t *core);
void bubble_sort(enemy_list_t **head);

#endif /* COMMON_H */
