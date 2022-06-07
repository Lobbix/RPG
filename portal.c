#include "my.h"

sfIntRect portal(Core core, All *all, sfSprite *portal, sfIntRect rectp)
{
    all->trois.time = sfClock_getElapsedTime(all->trois.clock);
    if (all->trois.time.microseconds / 100000 >= 1) {
        rectp.left += 80;
        if (rectp.left > 320) {
            rectp.left = 0;
            rectp.top += 69;
        }
        if (rectp.top > 140) {
            rectp.top = 0;
        }
        // if (rectp.top > 138 && rectp.left > 160) {
        //     rectp.left = 0;
        //     rectp.top = 0;
        // }
        sfClock_restart(all->trois.clock);
    }
    sfSprite_setTextureRect(portal, rectp);
    return rectp;
}