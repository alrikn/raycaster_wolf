/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** parse_save
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>
#include <unistd.h>

bool parse_map(core_t *core, FILE *file)
{
    size_t result;
    int i = 0;

    do {
        result = fread(core->meta.map[i], sizeof(char), SIZE, file);
        i++;
    } while (i < SIZE && result == SIZE && core->meta.map[i][0] != '\n');
    if (result != SIZE || i != SIZE) {
        printf("Parsing went wrong\n");
        maze_generator(core->meta.map);
        fclose(file);
        return false;
    }
    return true;
}

/*
** func must be called right before setting everything
** the min fread is to skip '\n'
*/
void parse_save(core_t *core)
{
    FILE *file = fopen("save_file", "r");

    if (!file) {
        printf("Couldn't open save file\n");
        return;
    }
    if (!parse_map(core, file))
        return;
    fclose(file);
    return;
}
