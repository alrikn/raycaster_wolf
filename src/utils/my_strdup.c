/*
** EPITECH PROJECT, 2024
** organized
** File description:
** my_strdup
*/

#include <stdlib.h>

static int my_strlen(char const *str)
{
    char const *ptr = str;
    int len = 0;

    while (*ptr != '\0') {
        ptr++;
        len++;
    }
    return (len);
}

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *dest = malloc(len + 1);

    if (dest == NULL) {
        return NULL;
    }
    for (int n = 0; n < len; n++) {
        dest[n] = src[n];
    }
    dest[len] = '\0';
    return dest;
}
