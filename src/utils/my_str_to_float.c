/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** my_str_to_float
*/

static int my_is_digit(char c)
{
    return c >= '0' && c <= '9';
}

const char *sign_getter(const char *ptr, int *sign)
{
    if (*ptr == '-' || *ptr == '+') {
        if (*ptr == '-')
            *sign = -1;
        ptr++;
    }
    return ptr;
}

const char *integer_getter(const char *ptr, double *result)
{
    while (my_is_digit(*ptr)) {
        *result = *result * 10.0 + (*ptr - '0');
        ptr++;
    }
    return ptr;
}

double my_str_to_float(const char *str, char **endptr)
{
    const char *ptr = str;
    double result = 0.0;
    double fraction = 0.1;
    int sign = 1;

    while (*ptr == ' ')
        ptr++;
    ptr = sign_getter(ptr, &sign);
    ptr = integer_getter(ptr, &result);
    if (*ptr == '.') {
        ptr++;
        while (my_is_digit(*ptr)) {
            result += (*ptr - '0') * fraction;
            fraction *= 0.1;
            ptr++;
        }
        *endptr = (char *)ptr;
    }
    return result * sign;
}
