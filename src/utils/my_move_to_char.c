/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** my_move_to_char
*/

#include <time.h>
char *my_move_to_char(const char *str, int c)
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
