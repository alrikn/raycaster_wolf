##
## EPITECH PROJECT, 2024
## wolf3d
## File description:
## Makefile
##

LIB_NAME = libmy.a
NAME = wolf3d
TEST_BIN = unit_tests

SRC = ./main.c \
	./src/drawing/draw_floor_ceiling.c \
	./src/drawing/render_wall.c \
	./src/drawing/map_create.c \
	./src/game_handle/main_loop.c \
	./src/game_handle/reset_values.c \
	./src/game_handle/menu_screen/menu_screen.c \
	./src/game_handle/statistics.c \
	./src/initialization/make_core.c \
	./src/initialization/make_random_blocks.c \
	./src/initialization/make_map.c \
	./src/initialization/init_sprites.c \
	./src/initialization/make_menu.c \
	./src/hud/init_hud.c \
	./src/hud/minimap.c \
	./src/hud/update_hud.c \
	./src/map_handle/is_wall.c \
	./src/map_handle/rays/cast_all_rays.c \
	./src/map_handle/rays/handle_ray.c \
	./src/map_handle/rays/handle_sprites.c \
	./src/map_handle/rays/handle_textures.c \
	./src/map_handle/rays/sort_sprites.c \
	./src/memory_handle/free_memory.c \
	./src/player/init_player.c \
	./src/player/print_pos.c \
	./src/player/door_interaction.c \
	./src/player/handle_input.c \
	./src/player/player_potential.c \
	./src/save_system/print_save.c \
	./src/save_system/parse_save.c \
	./src/enemy_handle/enemy_attack.c \
	./src/enemy_handle/enemy_update.c \
	./src/enemy_handle/init_enemies.c \
	./src/enemy_handle/kill_enemy.c \
	./src/utils/my_cooler_putstr.c \
	./src/utils/my_num_to_str.c \
	./src/utils/my_numlen.c \
	./src/utils/my_revstr.c \
	./src/utils/my_strcat.c \
	./src/utils/my_strcpy.c \
	./src/utils/my_str_to_int.c \
	./src/utils/my_strlen.c \
	./src/utils/my_strdup.c \
	./src/utils/my_strtok.c \
	./src/utils/my_str_to_double.c \
	./src/utils/my_error_putstr.c \

TEST_SRC = $(SRC) \
	./tests/test_my_printf.c

CC = gcc
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -g
INCLUDE_PATH = ./include/
LDFLAGS = -I$(INCLUDE_PATH)
TEST_LDFLAGS = $(LDFLAGS) --coverage -lcriterion
DESTINATION = -I$(INCLUDE_PATH) -L. -lmy -lm



all: $(LIB_NAME) $(NAME)

$(NAME): $(LIB_NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(DESTINATION) \
	-lcsfml-window -lcsfml-system -lcsfml-graphics -lcsfml-audio

$(LIB_NAME): $(OBJ)
	ar -rc $(LIB_NAME) $(OBJ)

$(TEST_BIN):
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(TEST_SRC) $(TEST_LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ)
	rm -f *.gc*

fclean: clean
	rm -f $(LIB_NAME)
	rm -f $(NAME)
	rm -f $(TEST_BIN)

re: fclean $(LIB_NAME) $(NAME)

compile:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS)

coverage: tests_run
	gcovr -r .
	gcovr -r . --branches

.PHONY: all re compile coverage fclean clean
