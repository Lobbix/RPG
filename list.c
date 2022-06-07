#include "my.h"

Chaine *add_cell(char *str, int x, int y)
{
    Chaine *cell = malloc(sizeof(Chaine));
    cell->texte = text(str, "ps.ttf", 20, x, y);
    cell->str = str;
    cell->pos.x = x;
    cell->pos.y = y;
    cell->next = NULL;
    cell->prev = NULL;
    return cell;
}

Chaine *creatcell(Chaine *menu, char *str, int x, int y)
{
    Chaine *cell = add_cell(str, x, y);
    if(!cell) return menu;
    if (menu == NULL) {
        menu = cell;
        return menu;
    }
    Chaine *temp = menu;
    for (; temp->next != NULL; temp = temp->next);
    temp->next = cell;
    cell->prev = temp;
    return menu;
}
