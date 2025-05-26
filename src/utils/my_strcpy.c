/*
** EPITECH PROJECT, 2024
** Task01 Pool Day 6
** File description:
** Copying one string into another
*/

char *my_strcpy(char *dest, char const *src)
{
    char *dest_start = dest;

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    dest = dest_start;
    return dest;
}
