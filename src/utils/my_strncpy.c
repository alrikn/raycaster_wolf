/*
** EPITECH PROJECT, 2024
** Task02 Pool Day 6
** File description:
** Does the same as task01 but copies n characters instead of all
*/

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (i < n -1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    return dest;
}
