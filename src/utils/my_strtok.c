/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** my_strtok
*/
#include <unistd.h>
#include "./../../include/my.h"

static char *fake_my_move_to_char(const char *str, int c)
{
    if (!str)
        return NULL;
    while (*str) {
        if (*str == (char)c) {
            return (char *)str;
        }
        str++;
    }
    if (c == '\0') {
        return (char *)str;
    }
    return NULL;
}

char *my_strtok(char *str, const char *delim)
{
    static char *next_token = NULL;
    char *start;

    if (str != NULL)
        next_token = str;
    if (next_token == NULL)
        return NULL;
    while (*next_token && fake_my_move_to_char(delim, *next_token))
        next_token++;
    if (*next_token == '\0')
        return NULL;
    start = next_token;
    while (*next_token && !fake_my_move_to_char(delim, *next_token))
        next_token++;
    if (*next_token) {
        *next_token = '\0';
        next_token++;
    }
    return start;
}
