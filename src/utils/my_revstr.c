/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** rev_str
*/

#include "entity_list.h"
#include "my.h"

int stat_error(core_t *core)
{
    void *c_check = calloc(1, sizeof(char));
    void *m_check = malloc(sizeof(char));
    int mem_error = 0;

    if (c_check)
        free(c_check);
    else
        mem_error = 1;
    if (m_check)
        free(m_check);
    else
        mem_error = 1;
    if (mem_error)
        exit(84);
    return 0;
}

void my_charswap(char *a, char *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}

char *my_revstr(char *str)
{
    char *str_end = str;
    char *str_start = str;

    while (str_end[1] != '\0') {
        str_end++;
    }
    for (; str_start < str_end; str_start++) {
        my_charswap(str_start, str_end);
        str_end--;
    }
    return str;
}
