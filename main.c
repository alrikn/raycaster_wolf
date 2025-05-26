/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** main
*/

#include "./include/my.h"
#include "struct.h"
#include <SFML/Graphics/Texture.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

static int explanation(void)
{
    printf("[MY_RAYTRACER]\n\t-h shows this help message\n");
    printf("a basic raycaster program\n");
    printf("USAGE: \n\t");
    printf("./wolf3d\n\t");
    printf("OPTION\n");
    printf("\t-h\tprint the usage and quit\nUSER INTERACTIONS\n");
    printf("\t'Mouse1' or 'Enter' key\tuse weapon\n");
    printf("\t'1' key\tswitch to knife\n");
    printf("\t'2' key\tswitch to pistol\n");
    printf("\t'm' key\tshow minimap\n");
    printf("\t'q' key\trotate left\n");
    printf("\t'e' key\trotate right\n");
    printf("\t'w' key\tmove forward\n");
    printf("\t's' key\tmove backward\n");
    printf("\t'a' key\tmove left\n");
    printf("\t'd' key\tmove right\n");
    return 0;
}

void destroy_sprites(core_t *core)
{
    sfSprite_destroy(core->setting.images.start_sprite);
    sfTexture_destroy(core->setting.images.start_texture);
    sfSprite_destroy(core->setting.images.quit_sprite);
    sfTexture_destroy(core->setting.images.quit_texture);
    sfSprite_destroy(core->setting.images.volup_sprite);
    sfTexture_destroy(core->setting.images.volup_texture);
    sfSprite_destroy(core->setting.images.voldown_sprite);
    sfTexture_destroy(core->setting.images.voldown_texture);
    sfFont_destroy(core->setting.images.score_font);
    sfText_destroy(core->setting.images.high_score);
    sfTexture_destroy(core->setting.images.background_texture);
    sfSprite_destroy(core->setting.images.background_sprite);
}

int main(int ac, char **av)
{
    core_t core = {0};

    srand(time(NULL));
    if (ac == 2 && my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h')
        return explanation();
    if (ac == 2 && my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 's')
        core.meta.save = true;
    read_statistics(&core);
    make_core(&core);
    sfRenderWindow_setFramerateLimit(core.window, 0);
    game_play_prep(&core);
    destroy_sprites(&core);
    sfRenderWindow_destroy(core.window);
    return 0;
}
