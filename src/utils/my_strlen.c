/*
** EPITECH PROJECT, 2024
** Day04
** File description:
** Task03
*/
#include <unistd.h>

int my_strlen(char const *str)
{
    char const *ptr = str;
    int len = 0;

    while (*ptr != '\0') {
        ptr++;
        len++;
    }
    return (len);
}
