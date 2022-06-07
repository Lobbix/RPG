/*
** EPITECH PROJECT, 2022
** parcing.c
** File description:
** parcing
*/

#include "my.h"

void affiche_menu(Chaine *chaine, Core core, size_t i)
{
    for(size_t u = 0;chaine != NULL; chaine = chaine->next, u++) {
        if (u == i) {
            sfText_destroy(chaine->texte);
            chaine->texte = text(chaine->str, "ps.ttf", 30, chaine->pos.x, chaine->pos.y);
        } else {
            sfText_destroy(chaine->texte);
            chaine->texte = text(chaine->str, "ps.ttf", 20, chaine->pos.x, chaine->pos.y);
        }
        sfText_setColor(chaine->texte, sfBlack);
        sfRenderWindow_drawText(core.window, chaine->texte, NULL);
    }
}

int New(Chaine *chaine, Core core)
{
    main_classe(core);
}

void Continue(Chaine *chaine)
{
    printf("A nawelle de le faire\n");
}

char *int_to_char(int nb)
{
    int save_nb = nb;
    int size = 0;
    int n = 0;
    int i = 0;
    char *buffer;
    while (save_nb != 0) {
        save_nb /= 10;
        size += 1;
    }
    buffer = malloc(sizeof(char) * size);
    i = size - 1;
    while (nb != 0) {
        n = nb % 10;
        nb = nb / 10;
        buffer[i] = n + 48;
        i -= 1;
    }
    buffer[size] = '\0';
    return buffer;
}

void Option(Chaine *chaine, Core core)
{
    int i = 255;
    int r = core.options.is_rain, fps = core.options.fps_num, muted = core.options.muted, r2 = core.options.anime;
    sfText *volume = text("Volume", "ps.ttf", 30, 50, 210);
    sfText *anim = text("Animations", "ps.ttf", 30, 50, 510);
    sfText *rain = text("Rain", "ps.ttf", 30, 50, 310);
    sfText *framerates = text("FPS", "ps.ttf", 30, 50, 410);
    sfText *arrow = text("<    >", "ps.ttf", 30, 300, 310);
    sfText *arrow2 = text("<    >", "ps.ttf", 30, 300, 410);
    sfText *arrow3 = text("<    >", "ps.ttf", 30, 400, 510);
    sfText *t_on = text("On", "ps.ttf", 30, 345, 310);
    sfText *t_off = text("Off", "ps.ttf", 30, 345, 310);
    sfText *t_on2 = text("On", "ps.ttf", 30, 445, 510);
    sfText *t_off2 = text("Off", "ps.ttf", 30, 445, 510);
    sfText *frames = text(int_to_char(fps), "ps.ttf", 30, 365, 410);
    sfRectangleShape *sound = sfRectangleShape_create();
    sfSprite *mute = spr_cr("mute.png", 1, 1);
    sfSprite *background = spr_cr("4.png", 1, 1);
    sfIntRect r_mute = {0, 0, 58, 50};
    sfVector2i pos_mouse = {0, 0};
    sfVector2f pos_sound = {400, 200}, pos_mute = {300, 200}, pos_cursor = {0, 0}, vect2 = {core.options.music_volume*4, 50}, vect = {400, 50};
    core.window = renderwindow(core);
    sfRectangleShape_setSize(sound, vect);
    if (core.options.muted == 1) r_mute.left += 58;
    while (sfRenderWindow_isOpen(core.window)) {
        pos_mouse = sfMouse_getPositionRenderWindow(core.window);
        while(sfMouse_isButtonPressed(sfMouseLeft) == sfTrue && (pos_mouse.y <= pos_sound.y + vect.y && pos_mouse.y >= pos_sound.y)) {
                pos_mouse = sfMouse_getPositionRenderWindow(core.window);
                pos_cursor.x = pos_mouse.x;
                pos_cursor.y = pos_mouse.y;
                pos_cursor.x - pos_sound.x > 0 && pos_cursor.x - pos_sound.x < 400 ?
                vect.x = pos_cursor.x - pos_sound.x, vect2.x = vect.x, sfRectangleShape_setSize(sound, vect) : 0;
                vect2.x > 266 ? sfRectangleShape_setFillColor(sound, sfColor_fromRGB(24, 130, 24)) : 0;
                vect2.x <= 266 ? sfRectangleShape_setFillColor(sound, sfColor_fromRGB(255, 128, 0)) : 0;
                vect2.x <= 133 ? sfRectangleShape_setFillColor(sound, sfColor_fromRGB(255, 0, 0)) : 0;
                sfMusic_setVolume(core.title, (int)vect2.x / 4);
                sfRenderWindow_clear(core.window, sfBlack);
                sfSprite_setPosition(mute, pos_mute);
                sfSprite_setTextureRect(mute, r_mute);
                sfRenderWindow_drawSprite(core.window, background, NULL);
                sfText_setColor(t_off, sfBlack);
                sfText_setColor(t_off2, sfBlack);
                sfText_setColor(t_on, sfBlack);
                sfText_setColor(t_on2, sfBlack);
                r == 0 || r % 2 == 0 ? sfRenderWindow_drawText(core.window, t_on, NULL) : sfRenderWindow_drawText(core.window, t_off, NULL);
                r2 == 0 || r2 % 2 == 0 ? sfRenderWindow_drawText(core.window, t_on2, NULL) : sfRenderWindow_drawText(core.window, t_off2, NULL);
                sfText_setColor(rain, sfBlack);
                sfText_setColor(framerates, sfBlack);
                sfText_setColor(anim, sfBlack);
                sfText_setColor(frames, sfBlack);
                sfText_setColor(volume, sfBlack);
                sfText_setColor(arrow, sfBlack);
                sfText_setColor(arrow2, sfBlack);
                sfText_setColor(arrow3, sfBlack);
                sfRenderWindow_drawText(core.window, rain, NULL);
                sfRenderWindow_drawText(core.window, framerates, NULL);
                sfRenderWindow_drawText(core.window, anim, NULL);
                sfRenderWindow_drawText(core.window, frames, NULL);
                sfRenderWindow_drawText(core.window, volume, NULL);
                sfRenderWindow_drawText(core.window, arrow, NULL);
                sfRenderWindow_drawText(core.window, arrow2, NULL);
                sfRenderWindow_drawText(core.window, arrow3, NULL);
                sfRenderWindow_drawSprite(core.window, mute, NULL);
                sfRectangleShape_setPosition(sound, pos_sound);
                sfRenderWindow_drawRectangleShape(core.window, sound, NULL);
                sfRenderWindow_display(core.window);
            }
        while (sfRenderWindow_pollEvent(core.window, &core.event)) {
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyEscape) {
                main_clone(core);
            }
            if (core.event.type == sfEvtMouseButtonPressed) {
                pos_cursor.x < 330 && pos_cursor.x > 300 && pos_cursor.y < 340 && pos_cursor.y > 310 ? r += 1 : 0;
                pos_cursor.x < 480 && pos_cursor.x > 450 && pos_cursor.y < 340 && pos_cursor.y > 310 ? r += 1 : 0;
                pos_cursor.x < 430 && pos_cursor.x > 400 && pos_cursor.y < 540 && pos_cursor.y > 510 ? r2 += 1 : 0;
                pos_cursor.x < 580 && pos_cursor.x > 550 && pos_cursor.y < 540 && pos_cursor.y > 510 ? r2 += 1 : 0;
                pos_cursor.x < 330 && pos_cursor.x > 300 && pos_cursor.y < 440 && pos_cursor.y > 410 && fps > 1 ? fps -= 1 : 0;
                pos_cursor.x < 480 && pos_cursor.x > 450 && pos_cursor.y < 440 && pos_cursor.y > 410 && fps < 90 ? fps += 1 : 0;
                frames = text(int_to_char(fps), "ps.ttf", 30, 365, 410);
            }
            if (core.event.type == sfEvtMouseButtonPressed && (pos_mouse.x <= 358 && pos_mouse.x >= 300 && pos_mouse.y <= 250 && pos_mouse.y >= 200)) {
                r_mute.left += 58;
                muted = 1;
                r_mute.left >= 116 ? r_mute.left = 0, muted = 0 : 0;
            }
            muted == 1 ? vect.x = 0, sfRectangleShape_setSize(sound, vect) : 0;
            muted == 0 ? sfRectangleShape_setSize(sound, vect2) : 0;
            vect2.x > 266 ? sfRectangleShape_setFillColor(sound, sfColor_fromRGB(24, 130, 24)) : 0;
            vect2.x <= 266 ? sfRectangleShape_setFillColor(sound, sfColor_fromRGB(255, 128, 0)) : 0;
            vect2.x <= 133 ? sfRectangleShape_setFillColor(sound, sfColor_fromRGB(255, 0, 0)) : 0;
        }
        pos_cursor.x = pos_mouse.x;
        pos_cursor.y = pos_mouse.y;
        sfMusic_setVolume(core.title, (int)vect2.x / 4);
        if (muted == 1) sfMusic_setVolume(core.title, 0);
        sfRenderWindow_clear(core.window, sfBlack);
        sfSprite_setPosition(mute, pos_mute);
        sfSprite_setTextureRect(mute, r_mute);
        sfRenderWindow_drawSprite(core.window, background, NULL);
        sfText_setColor(t_off, sfBlack);
        sfText_setColor(t_off2, sfBlack);
        sfText_setColor(t_on, sfBlack);
        sfText_setColor(t_on2, sfBlack);
        r == 0 || r % 2 == 0 ? sfRenderWindow_drawText(core.window, t_on, NULL) : sfRenderWindow_drawText(core.window, t_off, NULL);
        r2 == 0 || r2 % 2 == 0 ? sfRenderWindow_drawText(core.window, t_on2, NULL) : sfRenderWindow_drawText(core.window, t_off2, NULL);
        sfText_setColor(rain, sfBlack);
        sfText_setColor(framerates, sfBlack);
        sfText_setColor(anim, sfBlack);
        sfText_setColor(frames, sfBlack);
        sfText_setColor(volume, sfBlack);
        sfText_setColor(arrow, sfBlack);
        sfText_setColor(arrow2, sfBlack);
        sfText_setColor(arrow3, sfBlack);
        sfRenderWindow_drawText(core.window, rain, NULL);
        sfRenderWindow_drawText(core.window, framerates, NULL);
        sfRenderWindow_drawText(core.window, anim, NULL);
        sfRenderWindow_drawText(core.window, frames, NULL);
        sfRenderWindow_drawText(core.window, volume, NULL);
        sfRenderWindow_drawText(core.window, arrow, NULL);
        sfRenderWindow_drawText(core.window, arrow2, NULL);
        sfRenderWindow_drawText(core.window, arrow3, NULL);
        sfRenderWindow_drawSprite(core.window, mute, NULL);
        sfRectangleShape_setPosition(sound, pos_sound);
        sfRenderWindow_drawRectangleShape(core.window, sound, NULL);
        sfRenderWindow_display(core.window);
        core.options.fps_num = fps;
        core.options.is_rain = r % 2;
        core.options.music_volume = (int)vect2.x / 4;
        core.options.muted = muted;
        core.options.anime = r2 % 2;
    }
    main_clone(core);
}

void Exit(Chaine *chaine)
{
    exit (0);
}

int boite_de_texte2(char *str, Core core, sfSprite *one)
{
    char *ee = my_strcpy(str);
    int x = my_strlen(ee);
    int w = 0;
    char tmp;
    sfText *txt;
    for(;sfRenderWindow_isOpen(core.window) && w != x + 2; w++) {
        while (sfRenderWindow_pollEvent(core.window, &core.event)) {
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyEscape) return 0;
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyEnter) {
                txt = text(str, "./sprites/menucmbt/3.ttf", 40, 70, 760);
                sfRenderWindow_drawSprite(core.window, one, NULL);
                sfRenderWindow_drawText(core.window, txt, NULL);
                sfRenderWindow_display(core.window);
                w = x + 2;
                while (sfRenderWindow_waitEvent(core.window, &core.event) && core.event.type != sfEvtKeyReleased);
                return 1;
            }
        }
        (w > 0) ? ee[w - 1] = tmp : 0;
        tmp = ee[w];
        ee[w] = '\0';
        txt = text(ee, "./sprites/menucmbt/3.ttf", 40, 70, 760);
        sfRenderWindow_display(core.window);
        sfRenderWindow_drawSprite(core.window, one, NULL);
        sfRenderWindow_drawText(core.window, txt, NULL);
    }
    while (sfRenderWindow_waitEvent(core.window, &core.event) && core.event.type != sfEvtKeyReleased);
    return 1;
}

int intro(Core core)
{
    int i = 255, j = 0, k = 0, l = 0, x = 0, y = 0, z = 0, a = 0;
    sfSprite *one = spr_cr("1.png", 1, 1);
    sfSprite *two = spr_cr("2.png", 1, 1);
    sfSprite *three = spr_cr("3.png", 1, 1);
    sfSprite *four = spr_cr("4.png", 1, 1);
    while (sfRenderWindow_isOpen(core.window)) {
        while (sfRenderWindow_pollEvent(core.window, &core.event))
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyEscape) return 0;
        sfRenderWindow_clear(core.window, sfBlack);
        if (y == 0) {
            if (boite_de_texte2("10,000 years ago Deguelassor the world destroyer\nruled these lands", core, one) == 0) {
                return 0;
            }
        }
        if (z == 1) {
            if (boite_de_texte2("Then it was sealed by a mysterious man in your\nvillage", core, two) == 0) {
                return 0;
            }
        }
        if (a == 2) {
            if (boite_de_texte2("But thanks to his powerful allies he was released, which\ncaused the poisoning and corruption of the forest and\nthe appearance of new highly contagious diseases", core, three) == 0) {
                return 0;
            }
        }
        i >= 0 ? i -= 3, j += 3, y = 1, sfRenderWindow_drawSprite(core.window, one, NULL), sfRenderWindow_drawSprite(core.window, two, NULL) : 0;
        i < 0 && x == 0 ? j -= 3, k += 3, z += 1, sfRenderWindow_drawSprite(core.window, two, NULL),
        sfRenderWindow_drawSprite(core.window, three, NULL) : 0;
        j < 0 ? x = 1, k -= 3, l += 3, a += 1, sfRenderWindow_drawSprite(core.window, three, NULL),
        sfRenderWindow_drawSprite(core.window, four, NULL) : 0;
        if (l == 255) {
            return 0;
        }
        sfSprite_setColor(one, sfColor_fromRGBA(255, 255, 255, i));
        sfSprite_setColor(two, sfColor_fromRGBA(255, 255, 255, j));
        sfSprite_setColor(three, sfColor_fromRGBA(255, 255, 255, k));
        sfSprite_setColor(four, sfColor_fromRGBA(255, 255, 255, l));
        sfRenderWindow_display(core.window);
    }
    return 0;
}

int main_clone(Core core)
{
    int i = 0;
    sfWindow_setFramerateLimit(core.window, core.options.fps_num);
    sfMusic_setVolume(core.title, core.options.music_volume);
    if (core.options.muted == 1) sfMusic_setVolume(core.title, 0);
    Chaine *chaine = NULL;
    sfSprite *background = spr_cr("4.png", 1, 1);
    chaine = creatcell(chaine, "Play", 100, 200);
    chaine = creatcell(chaine, "Settings", 100, 300);
    chaine = creatcell(chaine, "Exit", 100 ,400);
    if (core.x == 0) {
        intro(core);
        core.x = 1;
    }
    while (sfRenderWindow_isOpen(core.window)) {
        sfMusic_setLoop(core.title, 1);
        while (sfRenderWindow_pollEvent(core.window, &core.event)) {
            if (core.event.key.code == sfKeyEscape) {
                sfRenderWindow_close(core.window);
            }
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyS) {
                i++;
                if (i > 3) i = 0;
            }
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyZ) {
                if (i - 1 < 0) i = 4;
                i--;
            }
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyEnter) {
                sfRenderWindow_close(core.window);
                if(i == 0) New(chaine, core);
                if(i == 1) Option(chaine, core);
                if(i == 2) Exit(chaine);
                if(i == 3) Exit(chaine);
            }
        }
        sfRenderWindow_clear(core.window, sfBlack);
        sfRenderWindow_drawSprite(core.window, background, NULL);
        affiche_menu(chaine, core, i);
        sfRenderWindow_display(core.window);
    }
}

void main ()
{
    Core core;
    Options options;
    srand(time(NULL));
    core.options = options;
    core.options.anime = 0;
    core.options.fps_num = 30;
    core.options.is_rain = 0;
    core.options.music_volume = 400 / 4;
    core.options.muted = 0;
    sfMusic *title =  sfMusic_createFromFile("title.ogg");
    core.title = title;
    sfMusic_play(title);
    core.x = 0;
    core.window = renderwindow(core);
    main_clone(core);
}