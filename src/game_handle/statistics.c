/*
** EPITECH PROJECT, 2024
** wolf3d
** File description:
** statistics.c
*/

#include "entity_list.h"
#include "struct.h"
#include "my.h"
#include <stdio.h>

void write_statistics(core_t *core)
{
    FILE *stats_file = fopen("stats", "w");

    fwrite(&core->statistics, sizeof(stats_t), 1, stats_file);
    if (stats_file)
        fclose(stats_file);
}

void read_statistics(core_t *core)
{
    stats_t blank_stats = {stat_error(core)};
    FILE *stats_file = fopen("stats", "r");

    if (!stats_file)
        return;
    if (fread(&core->statistics, sizeof(stats_t), 1, stats_file) < 1)
        core->statistics = blank_stats;
    fclose(stats_file);
}
