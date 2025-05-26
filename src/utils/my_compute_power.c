/*
** EPITECH PROJECT, 2024
** day05
** File description:
** task03
*/
#include <unistd.h>
#include <stdio.h>

int my_compute_power_it(int nb, int p)
{
    int temp = nb;

    if (p <= 0) {
        return 1;
    } else {
        for (int i = 1; i <= p; i++) {
            temp = temp * nb;
        }
    }
    return temp;
}
