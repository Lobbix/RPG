/*
** EPITECH PROJECT, 2021
** functions
** File description:
** functions
*/

#include "my.h"

int get_nbr(char *yes)
{
    int res = 0, i = my_strlen(yes), x = 0, neg = 1;
    if (yes[0] == '-') {
        neg = -1;
        x++;
    }
    while (yes[x] >= '0' && yes[x] <= '9') {
        res = res * 10;
        res = res + (yes[x] - 48);
        x++;
    }
    res = res * neg;
    return res;
}

int my_putnbr(int n)
{
    if (n < 0) {
        my_putchar('-');
        n = n * (-1);
    }
    if (n >= 10) {
        my_putnbr(n / 10);
        my_putchar(n % 10 + '0');
    }
    if (n < 10) {
        my_putchar(n % 10 + '0');
    }
    return (n);
}

char *my_strcpy(char *eee)
{
    int e = 0;
    char *yes = malloc(sizeof(char) * my_strlen(eee));

    while (eee[e] != '\0') {
        yes[e] = eee[e];
        e++;
    }
    yes[e] = eee[e];
    return yes;
}

char *my_fusion(char *str1, char *str2)
{
    int w = 0;
    char *res = malloc(sizeof(char) *(my_strlen(str1) + my_strlen(str2))+5);
    int i = 0, k = 0;
    for (int x = 0; str1[x] != '\0'; i++) {
        if(k == 33) {
            res[i] = '\n';
            k = 0;
            continue;
        }
        res[i] = str1[x];
        x++;
        k++;
    }
    res[i] = ' ';
    i++;
    for (int w = 0; str2[w] != '\0'; i++) {
        if(k == 33) {
            res[i] = '\n';
            k = 0;
            continue;
        }
        res[i] = str2[w];
        w++;
        k++;
    }
    res[i] = '\0';
    return res;
}

char *my_fusion2(char *str1, char *str2)
{
    int w = 0;
    char *res = malloc(sizeof(char) *(my_strlen(str1) + my_strlen(str2))+5);
    int i = 0, k = 0;
    for (int x = 0; str1[x] != '\0'; i++) {
        if(k == 33) {
            res[i] = '\n';
            k = 0;
            continue;
        }
        res[i] = str1[x];
        x++;
        k++;
    }
    for (int w = 0; str2[w] != '\0'; i++) {
        if(k == 33) {
            res[i] = '\n';
            k = 0;
            continue;
        }
        res[i] = str2[w];
        w++;
        k++;
    }
    res[i] = '\0';
    return res;
}