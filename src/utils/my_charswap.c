/*
** EPITECH PROJECT, 2024
** Task01 Day04
** File description:
** Same as swap function, but with characters
*/

#include <unistd.h>
#include "my.h"

void my_charswap(char *a, char *b)
{
    int placeholder = *a;

    *a = *b;
    *b = placeholder;
}
