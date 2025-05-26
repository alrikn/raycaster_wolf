/*
** EPITECH PROJECT, 2024
** day03
** File description:
** task04
*/
#include <unistd.h>

int my_isneg(int n)
{
    int N;
    int P;

    if (n < 0) {
        N = 78;
        write(1, &N, 1);
        return 1;
    } else {
        P = 80;
        write(1, &P, 1);
        return 0;
    }
}
