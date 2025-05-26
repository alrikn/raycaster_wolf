/*
** EPITECH PROJECT, 2024
** Day03
** File description:
** task01
*/
#include <unistd.h>

int my_print_alpha(void)
{
    int i;

    for (i = 97; i < 123; ++i){
        write(1, &i, 1);
    }
    return 0;
}
