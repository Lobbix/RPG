#include "my.h"

void do_clock3(Clock *clocki, All *all)
{
    clocki->time = sfClock_getElapsedTime(clocki->clock);
    if (clocki->time.microseconds / 10000 >= 1) {
        mvt_perso2(all);
        sfVector2f popos = sfView_getCenter(all->map.view);
        sfSprite_setPosition(all->perso.perso, popos);
        sfClock_restart(clocki->clock);
    }
}

void combat_ou_non2(All *all)
{
    int w = (rand() % 200) + 1;
    if (w == 25) all->utile.world = 2;
}

void mvt_perso2(All *all) {
    sfVector2f offset = {0, 0};
    if (sfKeyboard_isKeyPressed(sfKeyZ)){
        if (cond(all->utile.map2, all->perso.x / 42, (all->perso.y - 10) / 43, &all->utile, all) == 0) {
            all->perso.rec.top = 144;
            do_clock2(all);
            sfVector2f offset = {0, -10};
            all->perso.y -= 10;
            sfView_move(all->map.view2, offset);
            combat_ou_non2(all);
            return;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)){
        if (cond(all->utile.map2, all->perso.x / 42, (all->perso.y + 10) / 43, &all->utile, all) == 0) {
            all->perso.rec.top = 0;
            do_clock2(all);
            sfVector2f offset = {0, 10};
            all->perso.y += 10;
            sfView_move(all->map.view2, offset);
            combat_ou_non2(all);
            return;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)){
        if (cond(all->utile.map2, (all->perso.x - 10) / 42, (all->perso.y) / 43, &all->utile, all) == 0) {
            all->perso.rec.top = 48;
            do_clock2(all);
            sfVector2f offset = {-10, 0};
            all->perso.x -= 10;
            sfView_move(all->map.view2, offset);
            combat_ou_non2(all);
            return;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)){
        if (cond(all->utile.map2, (all->perso.x + 10) / 42, (all->perso.y) / 43, &all->utile, all) == 0) {
            all->perso.rec.top = 96;
            do_clock2(all);
            sfVector2f offset = {10, 0};
            all->perso.x += 10;
            sfView_move(all->map.view2, offset);
            combat_ou_non2(all);
            return;
        }
    }
}
