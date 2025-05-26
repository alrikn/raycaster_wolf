/*
** EPITECH PROJECT, 2024
** task02
** File description:
** turns the command-line given arguments into a single string
*/

#include "my.h"

char *concat_params(int argc, char **argv)
{
    int full_len = 0;
    char *fullstr = NULL;
    int l = 0;
    int n = 0;

    for (l = 0; l < argc; l++) {
        full_len += (my_strlen(argv[l]) + 1);
    }
    fullstr = malloc(full_len);
    for (n = 0; n < argc; n++) {
        fullstr = my_strcat(fullstr, argv[n]);
        if (n + 1 != argc)
            fullstr = my_strcat(fullstr, "\n");
    }
    return fullstr;
}
