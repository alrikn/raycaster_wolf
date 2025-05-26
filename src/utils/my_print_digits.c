/*
** EPITECH PROJECT, 2024
** day03
** File description:
** task03
*/

#include <unistd.h>

int my_print_digits(void)
{
    int i;

    for (i = 48; i < 58; ++i) {
        write(1, &i, 1);
    }
    return 0;
}
