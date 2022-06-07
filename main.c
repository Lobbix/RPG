#include "my.h"
#include "includes/my_h.h"

sfRenderWindow *renderwindow(Core core)
{
    sfRenderWindow *window;
    sfVideoMode video_mode = {1000, 980, 32};
    window = sfRenderWindow_create(video_mode,
    "first window", sfClose | sfResize, NULL);
    sfWindow_setFramerateLimit(window, 30);
    return (window);
}

void where_perso(Perso *perso, Utile utile)
{
    int i = 0;
    int j = 0;
    while (utile.map[i][j] != '2') {
        if (utile.map[i][j] == '\0') {
            j = -1;
            i++;
        }
        j++;
    }
    perso->life_max = 100;
    perso->xp = 0;
    perso->level = 1;
    perso->xp_max = perso->level * perso->level;

}

void makoumba(All *all)
{
    sfVector2f popos = sfView_getCenter(all->map.view);
    popos.x += 50;
    //popos.y += 10;
    sfSprite_setPosition(all->perso.perso, popos);
}

void do_clock(Clock *clocki, All *all)
{
    clocki->time = sfClock_getElapsedTime(clocki->clock);
    if (clocki->time.microseconds / 10000 >= 1) {
        mvt_perso(all);
        makoumba(all);
        //affichage(all->utile.map);
        sfClock_restart(clocki->clock);
    }
}

void init_varia(All *all, Core *core, Core core_opt)
{
    sfMusic_pause(core_opt.title);
    sfMusic_play(core_opt.title2);
    all->map.view2 = sfView_create();
    all->utile.doremem = all->perso.x;
    all->utile.doremem2 = all->perso.y;
    all->perso.x = 31 * 42;
    all->perso.y = 41 * 43;
    sfVector2f offset = {600, 1300};
    sfView_move(all->map.view2, offset);
    sfRenderWindow_setView(core->window, all->map.view2);
    all->map.map = spr_cr("./dark/dark_map.png", 2, 2);
    all->utile.mapmonde = 1;
    all->utile.mapmonde2 = 0;
    all->boss.boss = spr_cr("./sprites/degeulassor.png", 1, 1);
    sfVector2f pos = {26.5 * 42, 2 * 43};
    sfSprite_setPosition(all->boss.boss, pos);
}

void init_varib(All *all, Core *core, Core core_opt)
{
    sfMusic_pause(core_opt.title2);
    sfMusic_play(core_opt.title);
    all->perso.x = all->utile.doremem;
    all->perso.y = all->utile.doremem2;
    all->map.map = spr_cr("map.png", 2, 2);
    all->utile.mapmonde = 0;
    all->utile.mapmonde2 = 1;
}

void verif(All *all, Core *core)
{
    if (all->utile.arbre == 1) {
        sfSprite *tree = spr_cr("calque.png", 2, 2);
        sfRenderWindow_drawSprite(core->window, tree, NULL);
    }
}

quete *sup_quete(quete *l_mob, All *all)
{
    if (l_mob == NULL){
        return NULL;
    }
    if (l_mob->finished == 1) {
        all->perso.xp = all->perso.xp + 10;
        quete *tmp = l_mob->next;
        free(l_mob);
        return tmp;
    } else {
        l_mob->next = sup_quete(l_mob->next, all);
        return l_mob;
    }
}

int print_quest(All all)
{
    quete *tmp = all.perso.quest;
    sfVector2f pos = sfView_getCenter(sfRenderWindow_getView(all.core.window));
    sfSprite *men = spr_cr("./sprites/menucmbt/menu.png", 2.1, 2.5);
    sfVector2f pos2 = pos;
    pos2.y = pos2.y - 500;
    pos = pos2;
    sfSprite_setPosition(men, pos2);
    pos.x = pos.x + 40;
    sfText *txt;
    while(sfRenderWindow_isOpen(all.core.window)) {
        tmp = all.perso.quest;
        pos2 = pos;
        txt = text("Quest:", "sprites/menucmbt/ff.ttf", 50, pos2.x, pos2.y);
        sfRenderWindow_drawSprite(all.core.window, men, NULL);
        sfRenderWindow_drawText(all.core.window, txt, NULL);
        pos2.y = pos2.y + 50;
        while(tmp != NULL) {
            txt = text(tmp->name, "sprites/menucmbt/ff.ttf", 50, pos2.x, pos2.y);
            sfRenderWindow_drawText(all.core.window, txt, NULL);
            for(int x = 0; tmp->task[x].name != NULL; x++) {
                pos2.y = pos2.y + 50;
                if(tmp->task[x].finished == 1) {
                sfText *val = text("v", "sprites/menucmbt/ff.ttf", 50, pos2.x, pos2.y);
                sfRenderWindow_drawText(all.core.window, val, NULL);
                }
                txt = text(tmp->task[x].name, "sprites/menucmbt/ff.ttf", 50, pos2.x + 30, pos2.y);
                sfRenderWindow_drawText(all.core.window, txt, NULL);
            }
            tmp = tmp->next;
            pos2.y = pos2.y + 50;
        }
        while (sfRenderWindow_pollEvent(all.core.window, &all.core.event)) {
        if (all.core.event.type == sfEvtClosed) {
            sfRenderWindow_close(all.core.window);
            return 0;
        }
        if (all.core.event.type == sfEvtKeyReleased && all.core.event.key.code == sfKeyP)
            return;
        }
        sfRenderWindow_display(all.core.window);
    }
}

void print_pnj(All all)
{
    while(all.pnj != NULL) {
        sfRenderWindow_drawSprite(all.core.window, all.pnj->sp, NULL);
        all.pnj = all.pnj->next;
    }
}

void val_task_quest(All *all)
{
    int x = 0, y = 0;
    quete *tmp = all->perso.quest;
    while(tmp != NULL) {
        for(x = 0, y = 0; tmp->task[x].name != NULL; x++) {
            if(tmp->task[x].objectif <= tmp->task[x].tot_t) {
                tmp->task[x].finished = 1;
                y++;
            }
        }
        if (x == y)
            tmp->finished = 1;
        tmp = tmp->next;
    }
}

void mapmonde(Clock *clocki, All *all, Core *core, Core core_opt)
{
    if (all->utile.mapmonde == 0) init_varia(all, core, core_opt);
    do_clock3(clocki, all);
    sfRenderWindow_clear(core->window, sfBlack);
    sfRenderWindow_setView(core->window, all->map.view2);
    sfRenderWindow_drawSprite(core->window, all->map.map, NULL);
    sfSprite_setTextureRect(all->perso.perso, all->perso.rec);
    sfVector2f popos = sfView_getCenter(all->map.view2);
    sfSprite_setPosition(all->perso.perso, popos);
    sfRenderWindow_drawSprite(core->window, all->boss.boss, NULL);
    sfRenderWindow_drawSprite(core->window, all->perso.perso, NULL);
    sfRenderWindow_setView(core->window, all->map.view2);
    // sfRenderWindow_display(core->window);
}

void mapnormal(Clock *clocki, All *all, Core *core, pnj *pnj1, sfSprite *portal, Core core_opt)
{
    if (all->utile.mapmonde2 == 0) init_varib(all, core, core_opt);
    all->core = *core;
    do_clock(clocki, all);
    sfRenderWindow_clear(core->window, sfBlack);
    sfRenderWindow_drawSprite(core->window, all->map.map, NULL);
    event(all, core);
    sfRenderWindow_drawSprite(core->window, portal, NULL);
    sfSprite_setTextureRect(all->perso.perso, all->perso.rec);
    sfRenderWindow_drawSprite(core->window, all->perso.perso, NULL);
    val_task_quest(all);
    all->perso.quest = sup_quete(all->perso.quest, all);
    print_pnj(*all);
    verif(all, core);
}

pnj *pos_pnj(pnj *pnj1, All all)
{
    pnj *tmp = pnj1;
    int x = 0, y = 0;
    char **map = all.utile.map;
    for(;map[y] != NULL && tmp != NULL; x++) {
        if(map[y][x] == '\0') {
            x = -1;
            y++;
        }
        if(map[y][x] == 'P') {
            tmp->sp = pos_sprite(tmp->sp, (x) * 42, (y + 4.5) * 43);
            tmp = tmp->next;
        }
    }
    return pnj1;
}

int stop(Core core, All all, Core core_opt)
{
    int i = 0;
    Chaine *chaine = NULL;
    chaine = creatcell(chaine, "Menu", 100, 200);
    chaine = creatcell(chaine, "Continue", 100, 300);
    chaine = creatcell(chaine, "Exit", 100 , 400);
    sfView *view = sfView_create();
    sfSprite *back = spr_cr("4.png", 1, 1.1);
    sfRenderWindow_setView(core.window, view);
    while (1) {
        while (sfRenderWindow_pollEvent(core.window, &core.event)) {
            /*if (core.event.key.code == sfKeyEscape) {
                sfRenderWindow_close(core.window);
            }*/
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyS) {
                i++;
                if (i > 2) i = 0;
            }
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyZ) {
                if (i - 1 < 0) i = 3;
                i--;
            }
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyEnter) {
                if(i == 0) {
                    sfRenderWindow_close(core.window);
                    sfMusic_pause(core_opt.title);
                    main();
                }
                if(i == 1) return 0;
                if(i == 2) Exit(chaine);
            }
        }
        sfRenderWindow_clear(core.window, sfWhite);
        sfRenderWindow_drawSprite(core.window, back, NULL);
        affiche_menu(chaine, core, i);
        sfRenderWindow_display(core.window);
    }
    return 0;
}

void main2(Core core, All all, Clock clocki, Core core_opt)
{
    all.map.map = spr_cr("map.png", 2, 2);
    all.perso.perso = spr_cr(all.perso.perso2, 1.2, 1.2);
    // sfRectangleShape *truc = sfRectangleShape_create();
    // sfVector2f taille = {40, 40};
    // sfRectangleShape_setSize(truc, taille);
    all.perso.rec = rect(0,0, 47, 48);
    all.perso.x = 13 * 42;
    all.perso.y = 7 * 43;
    all.map.view = sfView_create();
    all.core = core;

    pnj *pnj1 = malloc(sizeof(pnj));
    pnj1->sp = spr_cr("./sprites/PNJ/pecheur bg.png", 1.2, 1.2);
    sfIntRect rec = rect(0, 0, 48, 48);
    sfSprite_setTextureRect(pnj1->sp, rec);
    pnj1->quest = quest("./map/quetes_pecheur", 1);

    pnj *pnj2 = malloc(sizeof(pnj));
    pnj2->sp = spr_cr("./sprites/PNJ/papy_Descartes.png", 1.2, 1.2);
    sfSprite_setTextureRect(pnj2->sp, rec);
    pnj2->next = NULL;
    pnj2->quest = quest("./map/quetes_pas_pecheur", 2);
    pnj1->next = pnj2;
    all.pnj = pos_pnj(pnj1, all);

    sfVector2f iu = {24, 24};
    sfSprite_setOrigin(all.perso.perso, iu);

    sfSprite *portail = spr_cr("./sprites/portal/portal_animation.png", 0.8, 0.8);

    sfIntRect rectp = {0, 0, 80, 70};
    sfSprite_setTextureRect(portail, rectp);
    sfVector2f pos = {32 * 42, 28.5 * 43};
    sfSprite_setPosition(portail, pos);

    //Inventory required
    int keyi = -1;
    int keye = -1;
    int l_clicked = -1;
    int r_clicked = -1;
    all.inventory = li_initialisation();
    sfView *view = sfRenderWindow_getView(core.window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f zero;
    zero.x = center.x - 500;
    zero.y = center.y - 470;
    all.perso.life = 100;
    all.perso.life_max = 100;
    all.perso.stat = malloc(sizeof(Stat));
    all.perso.stat->am = 0;
    all.perso.stat->ap = 0;
    all.perso.xp = 0;
    all.perso.level = 0;
    all.perso.xp_max = 100;
    sfSprite *s_stats = sprite_create("graphics/stats.png", (sfVector2f){zero.x, zero.y}, (sfVector2f){1, 1});
    sfVector2i pos_mouse = {0, 0};
    all.inventory->sprite = sprite_create("graphics/inventory.png", (sfVector2f){zero.x + 1000 - 362, zero.y + 980 - 185}, (sfVector2f){1, 1});
    sfText *tlevel = text_create(int_to_str(all.perso.level), "ps.ttf", (sfVector2f){0, 0}, (sfVector2f){0.5, 0.5}, (sfColor){132,105,96, 255});
    sfText *tlife = text_create(my_fusion(int_to_str(all.perso.life), my_fusion(" / ", int_to_str(all.perso.life_max))), "ps.ttf", (sfVector2f){0, 0}, (sfVector2f){0.5, 0.5}, (sfColor){132,105,96, 255});
    sfText *txp = text_create(int_to_str(all.perso.xp), "ps.ttf", (sfVector2f){0, 0}, (sfVector2f){0.5, 0.5}, (sfColor){132,105,96, 255});
    sfText *tam = text_create(int_to_str(all.perso.stat->am), "ps.ttf", (sfVector2f){0, 0}, (sfVector2f){0.5, 0.5}, (sfColor){132,105,96, 255});
    sfText *tap = text_create(int_to_str(all.perso.stat->ap), "ps.ttf", (sfVector2f){0, 0}, (sfVector2f){0.5, 0.5}, (sfColor){132,105,96, 255});

    int jsp_comment_la_nommé = 0;
    core_opt.title2 = sfMusic_createFromFile("mechant.ogg");
    sfMusic_setVolume(core_opt.title2, core_opt.options.music_volume);
    if (core_opt.options.muted == 1) sfMusic_setVolume(core_opt.title2, 0);
    while (sfRenderWindow_isOpen(core.window)) {
        view = sfRenderWindow_getView(core.window);
        center = sfView_getCenter(view);
        zero.x = center.x - 500;
        zero.y = center.y - 470;
        pos_mouse = sfMouse_getPositionRenderWindow(core.window);
        sfRenderWindow_clear(core.window, sfBlack);
        while (sfRenderWindow_pollEvent(core.window, &core.event)) {
            if (core.event.type == sfEvtClosed)
                sfRenderWindow_close(core.window);
            if (core.event.type == sfEvtMouseButtonPressed) {
                if (core.event.mouseButton.button == sfMouseRight)
                    r_clicked *= (-1);
                if (core.event.mouseButton.button == sfMouseLeft)
                    l_clicked *= (-1);
            }
            if (core.event.key.code == sfKeyEscape)
                stop(core, all, core_opt);
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyI) {
                keyi *= (-1);
            }
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyE)
                keye *= (-1);
            if (core.event.type == sfEvtKeyReleased && core.event.key.code == sfKeyP)
                jsp_comment_la_nommé = 1;
        }
        sfRenderWindow_setView(core.window, all.map.view);
        switch (all.utile.world) {
            case (0):
                mapnormal(&clocki, &all, &core, pnj1, portail, core_opt);
                rectp = portal(core, &all, portail, rectp);
                all.utile.ancien = 0;
                break;
            case (1):
                mapmonde(&clocki, &all, &core, core_opt);
                all.utile.ancien = 1;
                break;
            case (2):
                sfMusic_play(core_opt.title);
                test_cmb(&all, core, core_opt);
                if (all.utile.ancien == 1) sfMusic_play(core_opt.title2);
                else
                    sfMusic_play(core_opt.title);
                break;
        }
        quete *q = all.perso.quest;
        if (keyi > 0)
            show_inventory(core.window, all.inventory, zero);

        if (l_clicked > 0 && keyi > 0) {
            use_item(all.inventory, pos_mouse, &(all.perso), zero);
            l_clicked = -1;
        }
        if (r_clicked > 0 && keyi > 0)
            show_description(all.inventory, pos_mouse, core.window, zero);
        if (keye > 0) {
            refresh_text(tlevel, int_to_str(all.perso.level), (sfVector2f){130, 95}, zero);
            refresh_text(tlife, my_fusion2(int_to_str(all.perso.life), my_fusion2("/", int_to_str(all.perso.life_max))), (sfVector2f){40, 150}, zero);
            refresh_text(txp, my_fusion2(int_to_str(all.perso.xp), my_fusion2("/", int_to_str(all.perso.xp_max))), (sfVector2f){40, 205}, zero);
            refresh_text(tam, int_to_str(all.perso.stat->am), (sfVector2f){130, 315}, zero);
            refresh_text(tap, int_to_str(all.perso.stat->ap), (sfVector2f){130, 260}, zero);
            show_stats(core.window, &(all.perso), s_stats, zero);
            sfRenderWindow_drawText(core.window, tlevel, NULL);
            sfRenderWindow_drawText(core.window, tlife, NULL);
            sfRenderWindow_drawText(core.window, txp, NULL);
            sfRenderWindow_drawText(core.window, tam, NULL);
            sfRenderWindow_drawText(core.window, tap, NULL);
        }
        if (jsp_comment_la_nommé == 1)
            jsp_comment_la_nommé = print_quest(all);
        sfRenderWindow_display(core.window);
    }
}

void main3(Perso perso, Core core_opt)
{
    Core core;
    Clock clocki;
    All all;
    sfMusic *world = sfMusic_createFromFile("world.ogg");
    sfMusic_pause(core_opt.title);
    sfMusic_setLoop(core_opt.title, 0);
    sfMusic_stop(core_opt.title);
    sfMusic_destroy(core_opt.title);
    core_opt.title = world;
    sfMusic_play(core_opt.title);
    if (core_opt.options.muted == 1) sfMusic_setVolume(core_opt.title, 0);
    sfMusic_setVolume(core_opt.title, core_opt.options.music_volume);
    sfMusic_setLoop(core_opt.title, 1);
    all.perso = perso;
    all.un.clock = sfClock_create();
    all.deux.clock = sfClock_create();
    all.trois.clock = sfClock_create();
    clocki.clock = sfClock_create();
    core.window = renderwindow(core);
    all.utile.map2 = ouvre_fichiez("./dark/dark_map.txt");
    all.utile.map = ouvre_fichiez("./map/map.txt");
    sfWindow_setFramerateLimit(core.window, core_opt.options.fps_num);
    all.utile.world = 0;
    all.utile.monstre = 0;
    all.utile.mapmonde = 0;
    all.utile.mapmonde2 = 1;
    all.utile.haut = 0;
    all.utile.gauche = 0;
    all.utile.p_step = 'S';
    all.utile.PNJ = -1;
    all.perso.quest = NULL;
    where_perso(&all.perso, all.utile);
    main2(core, all, clocki, core_opt);
}