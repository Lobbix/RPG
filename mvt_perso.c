/*
** EPITECH PROJECT, 2022
** parcing.c
** File description:
** parcing
*/

#include "my.h"

int wich_pnj(char **map, int x, int y)
{
    int h = 0, l = 0, tot = 0;
    for(;h != x || l != y; h++) {
        if(map[l][h] == '\0') {
            h = 0;
            l++;
        }
        if (map[l][h] == 'P') tot++;
    }
    return tot;
}

int cond(char **map, int x, int y, Utile *utile, All *all)
{
    if (map[y][x] == '_' || map[y][x] == 'o'|| map[y][x] == 'X') return 1;
    if (map[y][x] == 'P') {
        utile->PNJ = wich_pnj(map, x, y);
        return 1;
    }
    if (map[y][x] == 'W' && all->perso.level > 3) {
        utile->world = 1;
        return 0;
    }
     if (map[y][x] == 'R') {
        if (sfKeyboard_isKeyPressed(sfKeyF)) QTE(all->core, all);
        return 1;
    }
    if (map[y][x] == 'K') {
        utile->world = 0;
        return 0;
    }
    if (map[y][x] == 'M') {
        utile->world = 2;
        return 0;
    }
    if (map[y][x] == '!') {
        return 1;
    }
    utile->arbre = 0;
    if (map[y][x] == 'A') {
        utile->arbre = 1;
        return 0;
    }
    if (map[y][x] == 'D') {
        utile->world = 2;
        utile->degueulassor = 1;
        return 1;
    }
    return 0;
}

void do_clock2(All *all)
{
    all->un.time = sfClock_getElapsedTime(all->un.clock);
    if (all->un.time.microseconds / 5000 >= 10) {
        all->perso.rec.left += 45;
        if (all->perso.rec.left > 100) all->perso.rec.left = 0;
        sfClock_restart(all->un.clock);
    }
}

void combat_ou_non(All *all)
{
    int w = (rand() % 100) + 1;
    if (w == 25) all->utile.world = 2;
}

void mvt_perso(All *all) {
    sfVector2f offset = {0, 0};
    if (sfKeyboard_isKeyPressed(sfKeyZ)){
        if (cond(all->utile.map, all->perso.x / 42, (all->perso.y - 5) / 43, &all->utile, all) == 0) {
            all->perso.rec.top = 144;
            do_clock2(all);
            sfVector2f offset = {0, -10};
            all->perso.y -= 10;
            sfView_move(all->map.view, offset);
            combat_ou_non(all);
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)){
        if (cond(all->utile.map, all->perso.x / 42, (all->perso.y + 15) / 43, &all->utile, all) == 0) {
            all->perso.rec.top = 0;
            do_clock2(all);
            sfVector2f offset = {0, 10};
            all->perso.y += 10;
            sfView_move(all->map.view, offset);
            combat_ou_non(all);
            return;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)){
        if (cond(all->utile.map, (all->perso.x - 10) / 42, (all->perso.y + 5) / 43, &all->utile, all) == 0) {
            all->perso.rec.top = 48;
            do_clock2(all);
            sfVector2f offset = {-10, 0};
            all->perso.x -= 10;
            sfView_move(all->map.view, offset);
            combat_ou_non(all);
            return;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)){
        if (cond(all->utile.map, (all->perso.x + 10) / 42, (all->perso.y + 5) / 43, &all->utile, all) == 0) {
            all->perso.rec.top = 96;
            do_clock2(all);
            sfVector2f offset = {10, 0};
            all->perso.x += 10;
            sfView_move(all->map.view, offset);
            combat_ou_non(all);
        }
    }
}


void do_mvt(int x, int y, All *all)
{
    all->utile.map[all->perso.y][all->perso.x] = all->utile.p_step;
    all->perso.x = x;
    all->perso.y = y;
    all->utile.map[y][x] = '2';
}
