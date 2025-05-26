/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** print_save
*/

#include "entity_list.h"
#include "my.h"
#include "struct.h"
#include <stdio.h>

void specifics(core_t *core, int i, int g, FILE *file)
{
    fprintf(file, "%c", core->meta.map[i][g]);
}

/*
** func must be called right before freeing everything
*/
void print_save(core_t *core)
{
    FILE *file = fopen("save_file", "w");

    if (!file) {
        printf("Couldn't open save file\n");
        return;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int g = 0; g < SIZE; g++) {
            specifics(core, i, g, file);
        }
        fflush(file);
    }
    fprintf(file, "\n\n");
    fclose(file);
    return;
}
