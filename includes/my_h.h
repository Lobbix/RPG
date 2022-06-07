/*
** EPITECH PROJECT, 2021
** my_h.h
** File description:
** my_h.h
*/
#pragma once
#include "../my.h"
#include <SFML/Graphics.h>
#include <SFML/Window/Export.h>
#include <SFML/System.h>
#include <SFML/Audio/Music.h>
#include <SFML/Window/Export.h>
#include "/usr/local/include/SFML/Window/Keyboard.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

char *my_fusion2(char *str1, char *str2);

//l_inventory_functions.c
Inventory *li_initialisation(void);
void li_depush(Inventory *inventory, Item *item);

//item_functions.c
Item *item_initialisation(void);
void add_pv_potion(Inventory *inventory);
void add_xp_potion(Inventory *inventory);
void add_am_potion(Inventory *inventory);
void add_ap_potion(Inventory *inventory);
void add_sardine(Inventory *inventory);
void add_salmon(Inventory *inventory);
void add_tuna(Inventory *inventory);
void add_gold_salmon(Inventory *inventory);

//sprite_function.c
void refresh_text(sfText *text, char *newstring, sfVector2f pos, sfVector2f zero);
sfSprite *sprite_create(char const *path, sfVector2f pos, sfVector2f scale);
sfText *text_create(char *string, char const *path_font, sfVector2f pos, sfVector2f scale, sfColor color);

//inventory.c
Item *is_clicked(Inventory *inventory, sfVector2i mouse, sfVector2f zero);
void use_item(Inventory *inventory, sfVector2i mouse, Perso *perso, sfVector2f zero);
void show_description(Inventory *inventory, sfVector2i mouse, sfRenderWindow *window, sfVector2f zero);
void show_inventory(sfRenderWindow *window, Inventory *inventory, sfVector2f zero);
void show_stats(sfRenderWindow *window, Perso *perso, sfSprite *s_stats, sfVector2f zero);