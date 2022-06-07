#include "my.h"

sfSprite *pos_sprite(sfSprite *sp, int x, int y)
{
    sfVector2f pos = {x, y};
    sfSprite_setPosition(sp, pos);
    return sp;
}

sfSprite *spr_cr(char *Texture, float scalex , float scaley)
{
    sfTexture *my_texture = sfTexture_createFromFile(Texture, NULL);
    sfSprite *name = sfSprite_create();
    sfVector2f my_scale = {scalex, scaley};
    sfVector2f my_pos = {0, 0};
    sfSprite_setScale(name, my_scale);
    sfSprite_setPosition(name, my_pos);
    sfSprite_setTexture(name, my_texture, sfFalse);
    return name;
}

sfIntRect rect(int top, int left, int width, int height)
{
    sfIntRect rect;
    rect.top = top;
    rect.left = left;
    rect.width = width;
    rect.height = height;
    return rect;
}
