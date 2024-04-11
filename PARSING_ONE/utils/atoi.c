#include "../philo.h"

int _is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int check(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (!_is_digit(s[i]))
            return (-1);
        i++;
    }
    return (1);
}

int _atoi(char *s)
{
    int sign;
    int res;
    int i;

    if (check(s) == -1)
        return (-1);
    i = 0;
    sign = 1;
    res = 0;
    while (s[i] == ' ' && (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        res = res * 10 + s[i] - '0';
        i++;
    }
    return (res * sign);
}
