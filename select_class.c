#include "my.h"

sfRenderWindow *renderwindow2(void)
{
    sfRenderWindow *window;
    sfVideoMode video_mode = {1920, 1080, 32};
    window = sfRenderWindow_create(video_mode,
    "first window", sfClose | sfResize, NULL);
    sfWindow_setFramerateLimit(window, 30);
    return (window);
}

void knight(Menu menu, sfSprite *s_knight, sfSprite *s_cursor, Perso *perso)
{
    if ((menu.pos_mouse.x <= 580 && menu.pos_mouse.x > 435) && (menu.pos_mouse.y <= 531 && menu.pos_mouse.y > 384)) {
        perso->perso2 = "sprites/sprites classes/madame_chevaliere.png";
        perso->parle2 = "sprites/sprites classes/tete_madame_chevaliere.png";
        menu.pos_cursor.x = 405;
        menu.pos_cursor.y = 354;
        sfSprite_setPosition(s_cursor, menu.pos_cursor);
        sfRenderWindow_drawSprite(menu.window, s_cursor, NULL);
        menu.pos_des.x = 555;
        menu.pos_des.y = 354;
        sfSprite_setPosition(s_knight, menu.pos_des);
        sfRenderWindow_drawSprite(menu.window, s_knight, NULL);
        perso->wichone = 1;
    }
    if ((menu.pos_mouse.x <= 754 && menu.pos_mouse.x > 608) && (menu.pos_mouse.y <= 532 && menu.pos_mouse.y > 380)) {
        perso->perso2 = "sprites/sprites classes/monsieur_chevalier.png";
        perso->parle2 = "sprites/sprites classes/tete_monsieur_chevalier.png";
        menu.pos_cursor.x = 575;
        menu.pos_cursor.y = 354;
        sfSprite_setPosition(s_cursor, menu.pos_cursor);
        sfRenderWindow_drawSprite(menu.window, s_cursor, NULL);
        menu.pos_des.x = 725;
        menu.pos_des.y = 354;
        sfSprite_setPosition(s_knight, menu.pos_des);
        sfRenderWindow_drawSprite(menu.window, s_knight, NULL);
        perso->wichone = 1;
    }
}

void elf(Menu menu, sfSprite *s_elf, sfSprite *s_cursor, Perso *perso)
{
    if ((menu.pos_mouse.x <= 1319 && menu.pos_mouse.x > 1172) && (menu.pos_mouse.y <= 540 && menu.pos_mouse.y > 393)) {
        perso->perso2 = "sprites/sprites classes/madame_elf.png";
        perso->parle2 = "sprites/sprites classes/tete_madame_elf.png";
        menu.pos_cursor.x = 1145;
        menu.pos_cursor.y = 364;
        sfSprite_setPosition(s_cursor, menu.pos_cursor);
        sfRenderWindow_drawSprite(menu.window, s_cursor, NULL);
        menu.pos_des.x = 1294;
        menu.pos_des.y = 364;
        sfSprite_setPosition(s_elf, menu.pos_des);
        sfRenderWindow_drawSprite(menu.window, s_elf, NULL);
        perso->wichone = 2;
    }
    if ((menu.pos_mouse.x <= 1501 && menu.pos_mouse.x > 1360) && (menu.pos_mouse.y <= 541 && menu.pos_mouse.y > 397)) {
        perso->perso2 = "sprites/sprites classes/monsieur_elf.png";
        perso->parle2 = "sprites/sprites classes/tete_monsieur_elf.png";
        menu.pos_cursor.x = 1330;
        menu.pos_cursor.y = 364;
        sfSprite_setPosition(s_cursor, menu.pos_cursor);
        sfRenderWindow_drawSprite(menu.window, s_cursor, NULL);
        menu.pos_des.x = 1480;
        menu.pos_des.y = 364;
        sfSprite_setPosition(s_elf, menu.pos_des);
        sfRenderWindow_drawSprite(menu.window, s_elf, NULL);
        perso->wichone = 2;
    }
}

void sorcerer(Menu menu, sfSprite *s_sorcerer, sfSprite *s_cursor, Perso *perso)
{
    if ((menu.pos_mouse.x <= 570 && menu.pos_mouse.x > 433) && (menu.pos_mouse.y <= 775 && menu.pos_mouse.y > 638)) {
        perso->perso2 = "sprites/sprites classes/madame_sorcière.png";
        perso->parle2 = "sprites/sprites classes/tete_madame_sorciere.png";
        menu.pos_cursor.x = 400;
        menu.pos_cursor.y = 604;
        sfSprite_setPosition(s_cursor, menu.pos_cursor);
        sfRenderWindow_drawSprite(menu.window, s_cursor, NULL);
        menu.pos_des.x = 550;
        menu.pos_des.y = 604;
        sfSprite_setPosition(s_sorcerer, menu.pos_des);
        sfRenderWindow_drawSprite(menu.window, s_sorcerer, NULL);
        perso->wichone = 3;
    }
    if ((menu.pos_mouse.x <= 744 && menu.pos_mouse.x > 611) && (menu.pos_mouse.y <= 775 && menu.pos_mouse.y > 638)) {
        perso->perso2 = "sprites/sprites classes/monsieur_sorcier.png";
        perso->parle2 = "sprites/sprites classes/tete_monsieur_sorcier.png";
        menu.pos_cursor.x = 574;
        menu.pos_cursor.y = 604;
        sfSprite_setPosition(s_cursor, menu.pos_cursor);
        sfRenderWindow_drawSprite(menu.window, s_cursor, NULL);
        menu.pos_des.x = 723;
        menu.pos_des.y = 604;
        sfSprite_setPosition(s_sorcerer, menu.pos_des);
        sfRenderWindow_drawSprite(menu.window, s_sorcerer, NULL);
        perso->wichone = 3;
    }
}

void demon(Menu menu, sfSprite *s_demon, sfSprite *s_cursor, Perso *perso)
{
    if ((menu.pos_mouse.x <= 1315 && menu.pos_mouse.x > 1171) && (menu.pos_mouse.y <= 793 && menu.pos_mouse.y > 638)) {
        perso->perso2 = "sprites/sprites classes/madame_Démonne.png";
        perso->parle2 = "sprites/sprites classes/tete_madame_demonne.png";
        menu.pos_cursor.x = 1138, menu.pos_cursor.y = 616;
        sfSprite_setPosition(s_cursor, menu.pos_cursor);
        sfRenderWindow_drawSprite(menu.window, s_cursor, NULL);
        menu.pos_des.x = 1288, menu.pos_des.y = 616;
        sfSprite_setPosition(s_demon, menu.pos_des);
        sfRenderWindow_drawSprite(menu.window, s_demon, NULL);
        perso->wichone = 4;
    }
    if ((menu.pos_mouse.x <= 1497 && menu.pos_mouse.x > 1352) && (menu.pos_mouse.y <= 793 && menu.pos_mouse.y > 647)) {
        perso->perso2 = "sprites/sprites classes/monsieur_Démon.png";
        perso->parle2 = "sprites/sprites classes/tete_monsieur_demon.png";
        menu.pos_cursor.x = 1320, menu.pos_cursor.y = 618;
        sfSprite_setPosition(s_cursor, menu.pos_cursor);
        sfRenderWindow_drawSprite(menu.window, s_cursor, NULL);
        menu.pos_des.x = 1470, menu.pos_des.y = 618;
        sfSprite_setPosition(s_demon, menu.pos_des);
        sfRenderWindow_drawSprite(menu.window, s_demon, NULL);
        perso->wichone = 4;
    }
}

Menu mamacita(Menu menu)
{
    menu.pos_cursor.x = 0;
    menu.pos_cursor.y = 0;
    menu.pos_des.x = 0;
    menu.pos_des.y = 0;
    menu.pos_mouse.x = 0;
    menu.pos_mouse.y = 0;
    return menu;
}

void main_classe(Core core)
{
    Menu menu = mamacita(menu);
    menu.window = renderwindow2();
    Perso perso;
    const sfView *view = sfRenderWindow_getDefaultView(menu.window);
    while (sfRenderWindow_isOpen(menu.window)) {
        menu.pos_mouse = sfMouse_getPositionRenderWindow(menu.window);
        sfVector2f pos = sfRenderWindow_mapPixelToCoords(menu.window, menu.pos_mouse, view);
        menu.pos_mouse.x = pos.x;
        menu.pos_mouse.y = pos.y;
        while (sfRenderWindow_pollEvent(menu.window, &menu.event)) {
            if (menu.event.key.code == sfKeyEscape) {
                sfRenderWindow_close(menu.window);
                exit(EXIT_SUCCESS);
            } else if (menu.event.type == sfEvtMouseButtonPressed) {
                if (menu.event.mouseButton.button == sfMouseLeft) {
                    sfRenderWindow_close(menu.window);
                    main3(perso, core);
                    return;
                }
            }
        }
        sfRenderWindow_display(menu.window);
        sfRenderWindow_drawSprite(menu.window, spr_cr("sprites/select_class.jpg", 1, 1), NULL);
        knight(menu, spr_cr("sprites/knight des.png", 1, 1), spr_cr("sprites/cursor.png", 1, 1), &perso);
        elf(menu, spr_cr("sprites/elf des.png", 1, 1), spr_cr("sprites/cursor.png", 1, 1), &perso);
        sorcerer(menu, spr_cr("sprites/sorcerer des.png", 1, 1), spr_cr("sprites/cursor.png", 1, 1), &perso);
        demon(menu, spr_cr("sprites/demon des.png", 1, 1), spr_cr("sprites/cursor.png", 1, 1), &perso);
    }
}
