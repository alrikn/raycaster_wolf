/*
** EPITECH PROJECT, 2024
** Day05
** File description:
** task02
*/

#include <unistd.h>
#include <stdio.h>

int my_compute_factorial_rec(int nb)
{
    if (nb > 12 || nb < 0) {
        return 0;
    } else if (nb == 0) {
        return 1;
    }
    return (my_compute_factorial_rec(nb - 1) * nb);
}
