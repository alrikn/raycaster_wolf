/*
** EPITECH PROJECT, 2024
** settingup
** File description:
** my_str_to_int
*/

static int my_is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int my_str_to_int(const char *str)
{
    int result = 0;
    int sign = 1;

    while ((*str == ' ' || *str == '\t')) {
        str++;
    }
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    while (*str) {
        if (!my_is_digit(*str))
            return (result * sign);
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}
