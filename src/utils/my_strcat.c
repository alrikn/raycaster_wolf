/*
** EPITECH PROJECT, 2024
** placeholder
** File description:
** Concatinates two strings
*/

#include <unistd.h>
char *my_strcat(char *dest, char const *str)
{
    char *dest_start = dest;

    if (!dest || !str) {
        return NULL;
    }
    while (*dest != '\0') {
        dest++;
    }
    while (*str != '\0') {
        *dest = *str;
        dest++;
        str++;
    }
    *dest = '\0';
    return dest_start;
}
