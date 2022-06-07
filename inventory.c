/*
** EPITECH PROJECT, 2022
** main.c
** File description:
** main.c
*/

#include "includes/my_h.h"
#include "my.h"

Item *is_clicked(Inventory *inventory, sfVector2i mouse, sfVector2f zero)
{
    sfVector2f pos_mouse = {zero.x + mouse.x, zero.y + mouse.y};
    for (Item *current = inventory->first; current != NULL; current = current->next) {
        if (pos_mouse.x <= (current->pos.x + 55) && pos_mouse.x >= current->pos.x
        && pos_mouse.y <= (current->pos.y + 65) && pos_mouse.y >= current->pos.y) {
            return current;
        }
    }
    return NULL;
}

void use_item(Inventory *inventory, sfVector2i mouse, Perso *perso, sfVector2f zero)
{
    Item *delete = is_clicked(inventory, mouse, zero);
    if (!delete) return;
    perso->life += delete->pv;
    perso->xp += delete->xp;
    perso->stat->am += delete->am;
    perso->stat->ap += delete->ap;
    perso->life_max += delete->life;
    if (perso->life > perso->life_max) perso->life = perso->life_max;
    if (perso->xp >= perso->xp_max) {
        perso->xp = 0;
        perso->level ++;
        perso->xp_max += 20;
    }
    li_depush(inventory, delete);
}

void show_description(Inventory *inventory, sfVector2i mouse, sfRenderWindow *window, sfVector2f zero)
{
    Item *clicked = is_clicked(inventory, mouse, zero);
    if (!clicked) return;
    sfVector2f pos_description = {0, 0};
    pos_description.x = clicked->pos.x - 100;
    pos_description.y = clicked->pos.y - 100;
    sfSprite_setPosition(clicked->description, pos_description);
    sfRenderWindow_drawSprite(window, clicked->description, NULL);
}

void show_inventory(sfRenderWindow *window, Inventory *inventory, sfVector2f zero)
{
    sfSprite_setPosition(inventory->sprite, (sfVector2f){zero.x + 1000 - 362, zero.y + 980 - 185});
    sfRenderWindow_drawSprite(window, inventory->sprite, NULL);
    int x = zero.x + 670, y = zero.y + 825;
    int i = 0;
    for (Item *current = inventory->first; current != NULL; current = current->next, x += 65, i ++) {
        if (i == 5) {
            y += 65;
            x = zero.x + 670;
        }
        current->pos.x = x;
        current->pos.y = y;
        sfSprite_setPosition(current->sprite, current->pos);
        sfRenderWindow_drawSprite(window, current->sprite, NULL);
    }
    return;
}

void show_stats(sfRenderWindow *window, Perso *perso, sfSprite *s_stats, sfVector2f zero)
{
    sfSprite_setPosition(s_stats, zero);
    sfRenderWindow_drawSprite(window, s_stats, NULL);
    return;
}