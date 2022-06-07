/*
** EPITECH PROJECT, 2022
** inventory_rpg
** File description:
** l_inventory_functions
*/
#include "includes/my_h.h"

Inventory *li_initialisation(void)
{
    Inventory *inventory = malloc(sizeof(inventory));
    inventory->first = item_initialisation();
    inventory->sprite = sprite_create("graphics/inventory.png", (sfVector2f){0, 0}, (sfVector2f){1, 1});
    return inventory;
}

void li_depush(Inventory *inventory, Item *item)
{
    Item *current = inventory->first;
    if (current == item) {
        inventory->first = current->next;
        sfSprite_destroy(current->description);
        sfSprite_destroy(current->sprite);
        free(current);
        return;
    }
    for (; current != NULL && current->next != item; current = current->next);
    if (current == NULL) return;
    Item *delete = current->next;
    current->next = current->next->next;
    sfSprite_destroy(delete->description);
    sfSprite_destroy(delete->sprite);
    free(delete);
}