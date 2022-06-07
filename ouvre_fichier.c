/*
** EPITECH PROJECT, 2022
** parcing.c
** File description:
** parcing
*/

#include "my.h"

int counter(char *file)
{
    int i = 0;
    int k = 0;
    while (file[i] != '\0') {
        if (file[i] == '\n')
            k++;
        i++;
    }
    return k + 1;
}

int counter2(char *file)
{
    int i = 0;
    while (file[i] != '\n')
        i++;
    return i + 1;
}

char **my_str2(char *file, int nb)
{
    int i = counter(file);
    char **str2 = malloc(sizeof(char *) * (i + 1));
    int k = 0;
    int j = 0;
    i = 0;
    while (i != nb) {
        str2[j] = malloc(sizeof(char) * (counter2(file) + 1));
        while (file[i] != '\n') {
            str2[j][k] = file[i];
            i++;
            k++;
        }
        str2[j][k] = '\0';
        k = 0;
        j++;
        i++;
    }
    str2[j] = NULL;
    return str2;
}

char **ouvre_fichiez(char *str)
{
    int fd = open(str, O_RDWR);
    struct stat stt;
    stat(str, &stt);
    char buff[stt.st_size];
    int offset = stt.st_size;
    read(fd, buff, offset);
    return my_str2(buff, stt.st_size);
}

void affichage(char **str2)
{
    for (int i = 0; str2[i] != NULL; i++)
        printf("%s\n",str2[i]);
}