/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** my_error_putstr
*/

#include <unistd.h>

static int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int my_error_putstr(char const *str)
{
    int len;
    int written;

    if (!str) {
        write(1, "(null)", 6);
        return -1;
    }
    len = my_strlen(str);
    written = write(2, str, len);
    if (written != len) {
        return -1;
    }
    return 0;
}
