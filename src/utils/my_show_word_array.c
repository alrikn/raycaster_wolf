/*
** EPITECH PROJECT, 2024
** Day08 task03
** File description:
** writes content of an array of words.
*/
#include "my.h"

int my_show_word_array(char *const *tab)
{
    for (int n = 0; tab[n]; n++) {
        my_putstr(tab[n]);
        my_putchar('\n');
    }
    return 0;
}
