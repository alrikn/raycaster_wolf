/*
** EPITECH PROJECT, 2024
** day03
** File description:
** task02
*/
#include <unistd.h>

int my_print_revalpha(void)
{
    int i;

    for (i = 122; i > 96; --i) {
        write(1, &i, 1);
    }
    return 0;
}
