/*
** EPITECH PROJECT, 2024
** organized
** File description:
** ascii_to sum
*/

int ascci_to_sum(const char *str)
{
    int sum = 0;

    while (*str) {
        sum += (int)(*str);
        str++;
    }
    return sum;
}
