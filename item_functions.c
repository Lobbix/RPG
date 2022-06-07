/*
** EPITECH PROJECT, 2022
** inventory_rpg
** File description:
** items_functions
*/
#include "includes/my_h.h"

Item *item_initialisation(void)
{
    Item *item = malloc(sizeof(Item));
    item->sprite = sprite_create("graphics/pv_potion.png", (sfVector2f){0,0}, (sfVector2f){0.7, 0.7});
    item->description = sprite_create("graphics/pv_description.png", (sfVector2f){0,0}, (sfVector2f){0.25,0.25});
    item->am = 0;
    item->ap = 0;
    item->pv = 5;
    item->xp = 0;
    item->life = 0;
    item->name = "pv_potion";
    item->next = NULL;
    return item;
}

void add_pv_potion(Inventory *inventory)
{
    Item *item = malloc(sizeof(Item));
    item->sprite = sprite_create("graphics/pv_potion.png", (sfVector2f){0,0}, (sfVector2f){0.7,0.7});
    item->description = sprite_create("graphics/pv_description.png", (sfVector2f){0,0}, (sfVector2f){0.25,0.25});
    item->am = 0;
    item->ap = 0;
    item->pv = 5;
    item->xp = 0;
    item->life = 0;
    item->name = "pv_potion";
    item->next = NULL;
    if (inventory->first == NULL) {
        inventory->first = item;
        return;
    }
    Item *current = inventory->first;
    for (;current->next != NULL; current = current->next);
    current->next = item;
}

void add_xp_potion(Inventory *inventory)
{
    Item *item = malloc(sizeof(Item));
    item->sprite = sprite_create("graphics/xp_potion.png", (sfVector2f){0,0}, (sfVector2f){0.7,0.7});
    item->description = sprite_create("graphics/xp_description.png", (sfVector2f){0,0}, (sfVector2f){0.25,0.25});
    item->am = 0;
    item->ap = 0;
    item->pv = 0;
    item->xp = 20;
    item->life = 0;
    item->name = "xp_potion";
    item->next = NULL;
    if (inventory->first == NULL) {
        inventory->first = item;
        return;
    }
    Item *current = inventory->first;
    for (;current->next != NULL; current = current->next);
    current->next = item;
}

void add_am_potion(Inventory *inventory)
{
    if (inventory->first == NULL) inventory = li_initialisation();
    Item *item = malloc(sizeof(Item));
    item->sprite = sprite_create("graphics/am_potion.png", (sfVector2f){0,0}, (sfVector2f){0.7,0.7});
    item->description = sprite_create("graphics/am_description.png", (sfVector2f){0,0}, (sfVector2f){0.25,0.25});
    item->xp = 0;
    item->ap = 0;
    item->pv = 0;
    item->am = 5;
    item->life = 0;
    item->name = "am_potion";
    item->next = NULL;
    if (inventory->first == NULL) {
        inventory->first = item;
        return;
    }
    Item *current = inventory->first;
    for (;current->next != NULL; current = current->next);
    current->next = item;
}

void add_ap_potion(Inventory *inventory)
{
    if (inventory->first == NULL) inventory = li_initialisation();
    sfSprite *ap_potion = sprite_create("graphics/ap_potion.png", (sfVector2f){0,0}, (sfVector2f){0.7, 0.7});
    sfSprite *description = sprite_create("graphics/ap_description.png", (sfVector2f){0,0}, (sfVector2f){0.25,0.25});
    Item *item = malloc(sizeof(Item));
    item->sprite = ap_potion;
    item->description = description;
    item->xp = 0;
    item->am = 0;
    item->pv = 0;
    item->ap = 5;
    item->life = 0;
    item->name = "ap_potion";
    item->next = NULL;
    if (inventory->first == NULL) {
        inventory->first = item;
        return;
    }
    Item *current = inventory->first;
    for (;current->next != NULL; current = current->next);
    current->next = item;
}

void add_sardine(Inventory *inventory)
{
    if (inventory->first == NULL) inventory = li_initialisation();
    Item *item = malloc(sizeof(Item));
    item->sprite = sprite_create("graphics/sardine.png", (sfVector2f){0, 0}, (sfVector2f){0.7, 0.7});
    item->description = sprite_create("graphics/sardine_description.png", (sfVector2f){0,0}, (sfVector2f){0.25, 0.25});
    item->am = 0;
    item->ap = 0;
    item->pv = 3;
    item->xp = 0;
    item->life = 0;
    item->name = "sardine";
    item->next = NULL;
    if (inventory->first == NULL) {
        inventory->first = item;
        return;
    }
    Item *current = inventory->first;
    for (;current->next != NULL; current = current->next);
    current->next = item;
}

void add_salmon(Inventory *inventory)
{
    if (inventory->first == NULL) inventory = li_initialisation();
    Item *item = malloc(sizeof(Item));
    item->sprite = sprite_create("graphics/salmon.png", (sfVector2f){0,0}, (sfVector2f){0.7, 0.7});
    item->description = sprite_create("graphics/salmon_description.png", (sfVector2f){0,0}, (sfVector2f){0.25, 0.25});
    item->am = 0;
    item->ap = 0;
    item->pv = 5;
    item->xp = 0;
    item->life = 0;
    item->name = "salmon";
    item->next = NULL;
    if (inventory->first == NULL) {
        inventory->first = item;
        return;
    }
    Item *current = inventory->first;
    for (;current->next != NULL; current = current->next);
    current->next = item;
}

void add_tuna(Inventory *inventory)
{
    if (inventory->first == NULL) inventory = li_initialisation();
    Item *item = malloc(sizeof(Item));
    item->sprite = sprite_create("graphics/tuna.png", (sfVector2f){0,0}, (sfVector2f){0.7, 0.7});
    item->description = sprite_create("graphics/tuna_description.png", (sfVector2f){0,0}, (sfVector2f){0.25, 0.25});
    item->am = 0;
    item->ap = 0;
    item->pv = 10;
    item->xp = 0;
    item->life = 0;
    item->name = "tuna";
    item->next = NULL;
    if (inventory->first == NULL) {
        inventory->first = item;
        return;
    }
    Item *current = inventory->first;
    for (;current->next != NULL; current = current->next);
    current->next = item;
}

void add_gold_salmon(Inventory *inventory)
{
    if (inventory->first == NULL) inventory = li_initialisation();
    Item *item = malloc(sizeof(Item));
    item->sprite = sprite_create("graphics/gold_salmon.png", (sfVector2f){0,0}, (sfVector2f){0.7, 0.7});
    item->description = sprite_create("graphics/gold_salmon_description.png", (sfVector2f){0,0}, (sfVector2f){0.25, 0.25});
    item->am = 0;
    item->ap = 0;
    item->pv = 1000;
    item->xp = 0;
    item->life = 50;
    item->name = "gold_salmon";
    item->next = NULL;
    if (inventory->first == NULL) {
        inventory->first = item;
        return;
    }
    Item *current = inventory->first;
    for (;current->next != NULL; current = current->next);
    current->next = item;
}