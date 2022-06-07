/*
** EPITECH PROJECT, 2021
** functions
** File description:
** functions
*/

#include "my.h"

char my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    int e = 0;

    while (str[e] != '\0')
    {
        my_putchar(str[e]);
        e = e + 1;
    }
}

int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return i;
}

char *my_revstr(char *a)
{
    int e = 0, f = my_strlen(a) - 1;
    char c;
    while (e < f) {
        c = a[e];
        a[e] = a[f];
        a[f] = c;
        e++;
        f--;
    }
    return a;
}

char *get_inf_nbr(int w)
{
    int x = 10, e = 0;
    char *aaa = malloc(sizeof(char) * (10000));

    while (w / x != 0) {
        aaa[e] = (w % x) + 48;
        w = w / x;
        e++;
    }
    aaa[e] = (w % x) + 48;
    e++;
    aaa[e] = '\0';
    aaa = my_revstr(aaa);
    return aaa;
}
