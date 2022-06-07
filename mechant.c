/*
** EPITECH PROJECT, 2022
** mechant.c
** File description:
** mechant
*/

#include "my.h"

float my_atof(char *arr)
{
    float val = 0, scale = 1;
    int dot = 0, nega = 0;
    if (*arr == '-') {
        arr++;
        nega = 1;
    }
    for (; *arr; arr++) {
        if (dot) {
            scale = scale / 10;
            val = val + ( * arr - '0') * scale;
            continue;
        }
        if (*arr == '.') {
            dot++;
            continue;
        }
        val = val * 10.0 + (*arr - '0');
    }
    if (nega == 1) return -val;
    else    return  val;
}

Mob *cr_mob(int t, char **info)
{
    Mob *cell = malloc(sizeof(Mob));
    if (!cell) {
        return NULL;
    }
    cell->type = t;
    cell->life = get_nbr(info[3]);
    cell->life_max = get_nbr(info[3]);
    cell->att = get_nbr(info[4]);
    cell->slb = spr_cr("sprites/menucmbt/life_bar.png", 3, 2);
    cell->rlb = sfRectangleShape_create();
    sfVector2f taille = {220, 20};
    sfRectangleShape_setSize(cell->rlb, taille);
    cell->sp = spr_cr(info[2], my_atof(info[5]), my_atof(info[5]));
    cell->next = NULL;
    return cell;
}

int len_mob_lc(Mob *mob)
{
    int x = 0;
    for (x; mob != NULL; x++) {
        mob = mob->next;
    }
    return x;
}

Mob *add_mob(Mob *list, int t, char **info, int p, All *all)
{
    sfVector2f pos;
    Mob *cell = cr_mob(t, info);
    sfFloatRect eee = sfSprite_getGlobalBounds(cell->sp);
    (p == 1) ? pos.x = 250 - eee.width / 2, pos.y = 300 : 0;
    (p == 0) ? pos.x = 500 - eee.width / 2, pos.y = 500 : 0;
    (p == 2) ? pos.x = 750 - eee.width / 2, pos.y = 300 : 0;
    if (all->utile.degueulassor == 1) pos.y = 200;
    sfSprite_setPosition(cell->sp, pos);
    pos.x = pos.x - (sfSprite_getGlobalBounds(cell->slb).width / 5);
    if (all->utile.degueulassor == 1) {
        pos.x = 400;
        pos.y -= 150;
    }
    cell->slb = pos_sprite(cell->slb, pos.x, pos.y);
    sfVector2f eae = sfSprite_getPosition(cell->slb);
    eae.y += 4;
    eae.x += 6;
    sfRectangleShape_setPosition(cell->rlb, eae);
    if (list == NULL) {
        list = cell;
        return list;
    }
    cell->next = list;
    list = cell;
    return list;
}

Mob *sup_mob(Mob *l_mob, u_cmbt *cmb, All *all)
{
    if (l_mob == NULL){
        return NULL;
    }
    if (l_mob->life <= 0) {
        cmb->mode = -1;
        cmb->lx = 0;
        cmb->ly = -1;
        all->perso.xp = all->perso.xp + 10;
        Mob *tmp = l_mob->next;
        free(l_mob);
        quete *tmpa = (*all).perso.quest;
        while(tmpa != NULL) {
            for(int x = 0; tmpa->task[x].name != NULL; x++)
                (tmpa->task[x].x == 2) ? tmpa->task[x].tot_t++ : 0;
            tmpa = tmpa->next;
        }
        return tmp;
    } else {
        l_mob->next = sup_mob(l_mob->next, cmb, all);
        return l_mob;
    }
}

char **get_info_mob(int type)
{
    int f = open("./map/mob.txt", O_RDONLY);
    struct stat stt;
    stat("./map/mob.txt", &stt);
    char *buff = malloc(sizeof(char) * stt.st_size);
    read(f, buff, stt.st_size);
    int x = 0, i = 0, k = 0, w;
    char **nouveau = malloc(sizeof(char *) * 6);
    for (; buff[x] != ':' || buff[x + 1] != type + 48; x++);
    x++;
    for (; buff[x] != ':' && buff[x] != '\0'; x++, i++) {
        if (buff[x] == '\n') {
            nouveau[k] = malloc(sizeof(char) * i + 1);
            for (w = 0; w < i; w++) {
                nouveau[k][w] = buff[x - (i - w)];
            }
            nouveau[k][w] = '\0';
            k++;
            i = -1;
        }
    }
    nouveau[k] = NULL;
    return nouveau;
}

Mob *cr_mob_all(All *all, int type)
{
    srand(time(NULL));
    Mob *tmp = NULL;
    int w = (rand() % 3) + 1;
    if (all->utile.degueulassor == 1) w = 1;
    char **info = get_info_mob(type);
    for (int x = 0; x < w; x++)
        tmp = add_mob(tmp, type, info, x, all);
    return tmp;
}
