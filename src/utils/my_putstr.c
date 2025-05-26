/*
** EPITECH PROJECT, 2024
** Day04
** File description:
** task02
*/

#include <unistd.h>

int my_putstr(char const *str)
{
    char const *ptr = str;

    while (*ptr != '\0') {
        write(1, ptr, 1);
        ptr++;
    }
    return (0);
}
