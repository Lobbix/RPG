/*
** EPITECH PROJECT, 2021
** pnj
** File description:
** onj
*/

#include "my.h"

struct task *add_tasks(char *buff, int *p, int c)
{
    char *test = buff;
    int x = 0, w = 0;
    while (*test != ':') {
        (*test == '-') ? x++ : 0;
        *test++;
    }
    task *tasks = malloc(sizeof(task) * (x + 1));
    while(*buff != ':' && w <= x) {
        if(*buff == '-') {
            *buff++;
            tasks[w].x = c;
            tasks[w].name = my_strcpy(buff);
            while (*buff > '9' || *buff < '0') {
                *buff++;
            }
            tasks[w].objectif = get_nbr(buff);
            tasks[w].tot_t = 0;
            tasks[w].finished = 0;
            w++;
        }
        *buff++;
    }
    tasks[w].name = NULL;
    *p = w;
    return tasks;
}

char *add_txt(char *buff)
{
    while(*buff != '%')
        *buff++;
    *buff++;
    return buff;
}

struct quete *add_quest(char *buff, quete *res, int c)
{
    int i = 0;
    quete *cell = malloc(sizeof(quete));
    *buff++;
    cell->name = my_strcpy(buff);
    cell->next = NULL;
    cell->finished = 0;
    cell->task = add_tasks(buff, &i, c);
    cell->pnj_tx = add_txt(buff);
    if(res == NULL) {
        res = cell;
        return res;
    }
    quete *tmp = res;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = cell;
    return res;
}

struct quete *quest(char *file, int c)
{
    quete *res = NULL;
    int f = open(file, O_RDONLY), x = 0;
    struct stat stt;
    stat(file, &stt);
    char *buff = malloc(sizeof(char) * stt.st_size + 1);
    read(f, buff, stt.st_size);
    buff[stt.st_size] = '\0';
    for(int w = 0; buff[w] != '\0'; w++)
        (buff[w] == '\n') ? x++ : 0;
    for(int w = 0; buff[w] != '\0'; w++)
        (buff[w] == '\n') ? buff[w] = '\0', w++ : 0;
    while(x > 0) {
        (*buff == ':') ? res = add_quest(buff, res, c) : 0;
        while(*buff != '\0') *buff++;
        *buff++;
        x--;
    }
    return res;
    // while(res != NULL) {
    //     my_putstr(res->name);
    //     my_putstr("\n");
    //     // my_putstr("\n");
    //     // for(int d = 0; res->task[d].name != NULL; d++) {
    //         my_putstr(res->pnj_tx);
    //         my_putstr("\n");
    //         my_putstr("\n");
    //     // }
    //     // my_putstr("\n\n");
    //     res = res->next;
    // }
}