/*
** EPITECH PROJECT, 2024
** Day05
** File description:
** task01
*/

#include <unistd.h>

int my_compute_factorial_it(int nb)
{
    int factorial = 1;

    if (nb < 1 || nb > 12) {
        factorial = 0;
    } else {
        for (int i = 1; i != nb; i++) {
            factorial = factorial * i;
        }
        factorial = factorial * nb;
    }
    return (factorial);
}
