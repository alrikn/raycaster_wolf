/*
** EPITECH PROJECT, 2024
** Task 04 Pool Day 5
** File description:
** Uses a recursive function to calculate powers
*/

int my_compute_power_rec(int nb, int p)
{
    if (p > 0) {
        return (my_compute_power_rec(nb, p - 1) * nb);
    } else if (p == 0) {
        return 1;
    } else {
        return 0;
    }
}
