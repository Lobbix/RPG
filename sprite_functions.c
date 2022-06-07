/*
** EPITECH PROJECT, 2022
** inventory_rpg
** File description:
** sprite_functions
*/
#include "includes/my_h.h"

void refresh_text(sfText *text, char *newstring, sfVector2f pos, sfVector2f zero)
{
    sfVector2f newpos = {pos.x + zero.x, pos.y + zero.y};
    sfText_setPosition(text, newpos);
    sfText_setString(text, newstring);
}

sfSprite *sprite_create(char const *path, sfVector2f pos, sfVector2f scale)
{
    sfTexture *texture = sfTexture_createFromFile(path, NULL);
    sfSprite *sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, pos);
    sfSprite_setScale(sprite, scale);
    return sprite;
}

sfText *text_create(char *string, char const *path_font, sfVector2f pos, sfVector2f scale, sfColor color)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("ps.ttf");
    char *str_level = malloc(sizeof(char) * 10);
    sfText_setFont(text, font);
    sfText_setPosition(text, pos);
    sfText_scale (text, scale);
    sfText_setFillColor (text, color);
    sfText_setString(text, string);
    return text;
}