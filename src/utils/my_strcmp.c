/*
** EPITECH PROJECT, 2024
** my_ls
** File description:
** my_strcmp
*/

int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
