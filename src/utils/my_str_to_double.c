/*
** EPITECH PROJECT, 2025
** my_radar
** File description:
** my_str_to_double
*/

#include <stddef.h>

static int my_is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static const char *sign_getter(const char *ptr, int *sign)
{
    if (*ptr == '-' || *ptr == '+') {
        if (*ptr == '-')
            *sign = -1;
        ptr++;
    }
    return ptr;
}

static const char *integer_getter(const char *ptr, double *result)
{
    while (my_is_digit(*ptr)) {
        *result = *result * 10.0 + (*ptr - '0');
        ptr++;
    }
    return ptr;
}

static const char *fractional_getter(const char *ptr, double *fractional)
{
    int fraction_multiplier = 10;

    while (*ptr >= '0' && *ptr <= '9') {
        *fractional += (double)(*ptr - '0') / fraction_multiplier;
        fraction_multiplier *= 10;
        ptr++;
        if (fraction_multiplier > 10000)
            break;
    }
    return ptr;
}

double my_strtodouble(const char *ptr)
{
    double result = 0.0;
    double fractional = 0.0;
    int sign = 1;

    if (ptr == NULL)
        return 0.0;
    ptr = sign_getter(ptr, &sign);
    ptr = integer_getter(ptr, &result);
    if (*ptr == '.') {
        ptr++;
        ptr = fractional_getter(ptr, &fractional);
    }
    result += fractional;
    result *= sign;
    return result;
}
