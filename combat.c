/*
** EPITECH PROJECT, 2021
** functions
** File description:
** functions
*/

#include "my.h"
#include "includes/my_h.h"

char *int_to_str(int nb)
{
    if (nb == 0)
        return ("0");
    int size = 0;
    int n = 0;
    int save_nb = nb;
    char *buffer;
    for (; save_nb != 0; size++)
        save_nb /= 10;
    buffer = malloc(sizeof(char) * size);
    buffer[size] = '\0';
    for (int i = size - 1; nb != 0; i--) {
        n = nb % 10;
        nb = nb / 10;
        buffer[i] = n + 48;
    }
    return buffer;
}

int len_list_sp(gr_combat *list)
{
    gr_combat *tmp = list;
    int x;
    tmp = tmp->next;
    for (x = 0; tmp != NULL; x++)
        tmp = tmp->next;
    return x;
}

void boite_de_texte(char *str, Core core, u_cmbt cmb)
{
    char *ee = my_strcpy(str);
    int x = my_strlen(ee);
    char tmp;
    sfText *txt;
    for (int w = 0; sfRenderWindow_isOpen(core.window) && w != x + 2; w++) {
        (w > 0) ? ee[w - 1] = tmp : 0;
        tmp = ee[w];
        ee[w] = '\0';
        txt = text(ee, "./sprites/menucmbt/3.ttf", 40, 70, 760);
        aff_mob(&core, cmb.l_mob, &cmb);
        sfRenderWindow_display(core.window);
        sfRenderWindow_drawSprite(core.window, cmb.bc, NULL);
        sfRenderWindow_drawSprite(core.window, cmb.menu1, NULL);
        sfRenderWindow_drawSprite(core.window, cmb.menu2, NULL);
        sfRenderWindow_drawText(core.window, txt, NULL);
    }

}

gr_combat *get_stat_spell(char *name, gr_combat *cell)
{
    int x = my_strlen(name);
    for (int w = 0; w < x; w++)
        (name[w] == ' ') ? name[w] = '\0' : 0;
    cell->name = my_strcpy(name);
    while (*name != '\0') name++;
    while (*name == '\0') name++;
    cell->sta = get_nbr(name);
    while (*name != '\0') name++;
    while (*name == '\0') name++;
    cell->nbr = get_nbr(name);
    while (*name != '\0') name++;
    while (*name == '\0') name++;
    cell->sp_att = my_strcpy(name);
    while (*name != '\0') name++;
    while (*name == '\0') name++;
    cell->sp_sh = get_nbr(name);
    return cell;
}

gr_combat *add_spell(gr_combat *list, char *name, int i, int w)
{
    if (name == NULL)
        return NULL;
    gr_combat *cell = malloc(sizeof(gr_combat));
    cell->sp_att = NULL;
    cell = get_stat_spell(my_strcpy(name), cell);
    cell->type = i;
    char *txt = "./sprites/menucmbt/3.ttf";
    cell->text = text(cell->name, txt, 60, 300, ((w % 4)*50) + 760);
    if (list == NULL) {
        cell->next = NULL;
        list = cell;
        return list;
    }
    gr_combat *tmp = list;
    while (tmp->next != NULL)
        tmp = tmp->next;
    cell->next = NULL;
    tmp->next = cell;
    return list;
}

gr_combat **list_spell()
{
    int f = open("./map/sort.txt", O_RDONLY);
    struct stat stt;
    stat("./map/sort.txt", &stt);
    char *buff = malloc(sizeof(char) * stt.st_size + 1);
    read(f, buff, stt.st_size);
    buff[stt.st_size] = '\0';
    gr_combat **list = malloc(sizeof(gr_combat *) * 4);

    int x = 0, i = 0, k = 0, w = 0, o = 0, y = 0;
    char *yes;
    for (int x = 0; buff[x] != '\0' && i < 4; i++) {
        if (buff[x] == ':') {
            x++;
            for (w = x; buff[w] != '\n'; w++);
            list[i] = malloc(sizeof(gr_combat));
            yes = malloc(sizeof(char) * (w - x));
            for (o = 0; x < w; o++, x++)
                yes[o] = buff[x];
            yes[o] = '\0';
            list[i]->name = yes;
            list[i]->text = text(yes, "./sprites/menucmbt/3.ttf", 60, 70, (i*50) + 760);
            list[i]->next = NULL;
            list[i]->type = i;
            x++;
        }
        for (x, y = 0; buff[x] != ':' && buff[x] != '\0'; x++, y++) {
            for (w = x; buff[w] != '\n' && buff[w] != '\0'; w++);
            yes = malloc(sizeof(char) * (w - x));
            for (o = 0; x < w; o++, x++)
                yes[o] = buff[x];
            yes[o] = '\0';
            list[i] = add_spell(list[i], yes, i, y);
        }
    }
    return list;
}

void print_spell(u_cmbt cmb, int i, Core core)
{
    if (cmb.ly == -1) return;
    gr_combat *tmp = cmb.list[i]->next;
    int w = cmb.ly / 4;
    for (int x = 0; x < (4 * w) && tmp != NULL; x++)
        tmp = tmp->next;
    for (int x = 0; x < 4 && tmp != NULL; x++) {
        sfRenderWindow_drawText(core.window, tmp->text, NULL);
        tmp = tmp->next;
    }
    return;
}

void attack_annimation_2(u_cmbt *cmb, Core core, sfSprite *atta)
{
    sfRenderWindow_drawSprite(core.window, cmb->bc, NULL);
    sfRenderWindow_drawSprite(core.window, cmb->menu1, NULL);
    sfRenderWindow_drawSprite(core.window, cmb->menu2, NULL);
    aff_mob(&core, cmb->l_mob, cmb);
    sfRenderWindow_drawSprite(core.window, atta, NULL);
    sfRenderWindow_display(core.window);
}

sfSprite *attack_anni(gr_combat *spell, Mob *mob, sfIntRect *rec, All *all)
{
    sfSprite *atta = spr_cr(spell->sp_att, 2, 2);
    sfVector2f or = {192/4, 192/4};
    sfSprite_setOrigin(atta, or);
    sfVector2f posm = sfSprite_getPosition(mob->sp);
    if (all->utile.degueulassor == 1) {
        posm.x = 400;
        posm.y += 50;
    }
    sfSprite_setPosition(atta, posm);
    rec->left = 0;
    rec->top = 0;
    rec->height = 192;
    rec->width = 192;
    sfSprite_setTextureRect(atta, *rec);
    return atta;
}

void attack_annimation(u_cmbt *cmb, Core core, gr_combat *spell, Mob *mob, All *all)
{
    sfIntRect rec;
    sfSprite *atta = attack_anni(spell, mob, &rec, all);
    sfClock *yes = sfClock_create();
    sfTime t;
    int x = 0;
    while (x < spell->sp_sh) {
        t = sfClock_getElapsedTime(yes);
        if (t.microseconds >= 40000) {
            rec.left = rec.left + 192;
            if (rec.left/192 > 4) rec.left = 0, rec.top = rec.top + 192;
            sfSprite_setTextureRect(atta, rec);
            x++;
            sfClock_restart(yes);
        }
        attack_annimation_2(cmb, core, atta);
    }
    sfClock_destroy(yes);
}

void ennemy_annimation(u_cmbt *cmb, Core core, All *all, Mob *mob)
{
    int w[17] = {4,4,8,14,14,20,20,0,0,-20,-20,-14,-14,-8,-4,-4};
    sfClock *yes = sfClock_create();
    sfTime t;
    int x = 0;
    t = sfClock_getElapsedTime(yes);
    while ((t.microseconds) < 500000) {
        sfVector2f off = {0, 0};
        off.y = w[x];
        sfSprite_move(mob->sp, off);
        t = sfClock_getElapsedTime(yes);
        aff_mob(&core, cmb->l_mob, cmb);
        sfRenderWindow_display(core.window);
        sfRenderWindow_drawSprite(core.window, cmb->bc, NULL);
        sfRenderWindow_drawSprite(core.window, cmb->menu1, NULL);
        sfRenderWindow_drawSprite(core.window, cmb->menu2, NULL);
        x++;
    }
    sfClock_destroy(yes);
}

void ennemy_attak(u_cmbt *cmb, Core core, All *all)
{
    Mob *tmp = cmb->l_mob;
    for (int x = 0; tmp != NULL; x++) {
        bar_mob(all, *cmb, 220);
        (cmb->animation == 0) ? ennemy_annimation(cmb, core, all, tmp): 0;
        char *ee = my_fusion("You receive", int_to_str(tmp->att));
        ee = my_fusion(ee, "points of dammage");
        boite_de_texte(ee, core, *cmb);
        all->perso.life = all->perso.life - tmp->att;
        tmp = tmp->next;
        while (sfRenderWindow_waitEvent(core.window, &core.event) && core.event.type != sfEvtKeyReleased);
        if (all->perso.life <= 0) {
            cmb->state = 1;
            return;
        }
    }
}

void do_damage(u_cmbt *cmb, Core core, All *all)
{
    Mob *tmp = cmb->l_mob;
    gr_combat *tmp_s = cmb->list[cmb->lx];
    tmp_s = tmp_s->next;
    for (int x = 0; x < cmb->mode; x++)
        tmp = tmp->next;
    for (int x = 0; x < cmb->ly; x++)
        tmp_s = tmp_s->next;
    (cmb->animation == 0) ? attack_annimation(cmb, core, tmp_s, tmp, all): 0;
    if (all->perso.wichone == 1 && cmb->lx == 1 && (cmb->ly == 1 || cmb->ly == 0)) tmp_s->nbr *= 2;
    if (all->perso.wichone == 2 && cmb->lx == 0 && cmb->ly == 2) tmp_s->nbr *= 2;
    if (all->perso.wichone == 3 && cmb->lx == 0 && cmb->ly == 1) tmp_s->nbr *= 2;
    if (all->perso.wichone == 4 && (cmb->lx == 0 && cmb->ly == 0) || (cmb->lx == 1 && cmb->ly == 2)) tmp_s->nbr *= 2;
    tmp->life = tmp->life - tmp_s->nbr;
    char *ee = my_fusion("You inflict", int_to_str(tmp_s->nbr));
    ee = my_fusion(ee, "points of dammage");
    boite_de_texte(ee, core, *cmb);
    cmb->lx = 0;
    cmb->ly = -1;
    cmb->mode = -1;
    while (sfRenderWindow_waitEvent(core.window, &core.event) && core.event.type != sfEvtKeyReleased);
}

void combat_event(Core *core, All *all, u_cmbt *cmb)
{
    while (sfRenderWindow_pollEvent(core->window, &core->event)) {
        if (core->event.type == sfEvtClosed)
            sfRenderWindow_close(core->window);
        if (cmb->mode == -1) {
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyEnter && cmb->ly != -1) {
                cmb->mode = 0;
                return;
            }
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyS) {
                if (cmb->ly == -1)
                    cmb->lx = (cmb->lx == 2) ? 0 : cmb->lx + 1;
                else
                    cmb->ly = (cmb->ly == len_list_sp(cmb->list[cmb->lx]) - 1) ? 0 : cmb->ly + 1;
            }
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyZ) {
                if (cmb->ly == -1)
                    cmb->lx = (cmb->lx == 0) ? 2 : cmb->lx - 1;
                else
                    cmb->ly = (cmb->ly == 0) ?  len_list_sp(cmb->list[cmb->lx]) - 1 : cmb->ly - 1;
            }
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyEnter && cmb->ly == -1)
                (len_list_sp(cmb->list[cmb->lx]) > 0) ? cmb->ly = 0 : 0;
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyEnter && cmb->ly == -1 && cmb->lx == 2){
                all->utile.world = all->utile.ancien;
                all->utile.degueulassor = 0;
            }
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyBackspace)
                cmb->ly = -1;
            continue;
        }
        if (cmb->mode != -1) {
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyBackspace)
                cmb->mode = -1;
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyD) {
                cmb->mode = (cmb->mode == len_mob_lc(cmb->l_mob) - 1) ? 0 : cmb->mode + 1;
            }
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyQ) {
                cmb->mode = (cmb->mode == 0) ? len_mob_lc(cmb->l_mob) - 1 : cmb->mode - 1;
            }
            if (core->event.type == sfEvtKeyReleased && core->event.key.code == sfKeyEnter) {
                do_damage(cmb, *core, all);
                cmb->l_mob = sup_mob(cmb->l_mob, cmb, all);
                aff_mob(core, cmb->l_mob, cmb);
                ennemy_attak(cmb, *core, all);
                cmb->lx = 0;
                cmb->ly = -1;
                cmb->mode = -1;
            }
        }

    }
}

u_cmbt pos_curs_1(u_cmbt cmb)
{
    sfVector2f s = sfSprite_getScale(cmb.curs);
    float rot = sfSprite_getRotation(cmb.curs);
    (rot == 0) ? 0 : sfSprite_rotate(cmb.curs, 90);
    int x = cmb.lx;
    (x == -1) ? x = 0 : 0;
    sfVector2f pos = sfText_getPosition(cmb.list[x]->text);
    int tmp = pos.x - 16 * (s.x + 1);
    float posx = (cmb.ly == -1) ?  tmp : (tmp + 300) -16 * (s.x + 1);
    int posy = (cmb.ly == -1) ? 760 + ((50 * x) + 16) : 760 + (50 * (cmb.ly % 4)) + 16;
    cmb.curs = pos_sprite(cmb.curs, posx, posy);
    return cmb;
}

u_cmbt pos_curs_2(u_cmbt cmb)
{
    float rot = sfSprite_getRotation(cmb.curs);
    (rot == 0) ? sfSprite_rotate(cmb.curs, 90) : 0;
    Mob *tmp = cmb.l_mob;
    for (int x = 0; tmp != NULL && x < cmb.mode; x++)
        tmp = tmp->next;
    sfFloatRect rec = sfSprite_getGlobalBounds(tmp->sp);
    sfVector2f pos = sfSprite_getPosition(tmp->sp);
    float posx = pos.x + (rec.width / 2) + 16;
    float posy = pos.y - 50;
    cmb.curs = pos_sprite(cmb.curs, posx, posy);
    return cmb;
}

u_cmbt pos_curs(u_cmbt cmb)
{
    if (cmb.mode == -1)
        cmb = pos_curs_1(cmb);
    else
        cmb = pos_curs_2(cmb);
    return cmb;
}

// sfRectangleShape *change_xp(sfRectangleShape *xpbar, sfVector2f *taille, int taille_mx, All * all)
// {
//     int max = all->perso.xp_max;
//     int xp = all->perso.xp;
//     (*taille).x = (taille_mx * xp) / max;
//     sfRectangleShape_setSize(xpbar, (*taille));
//     sfRectangleShape_setFillColor(xpbar, sfCyan);
// }

sfRectangleShape *change_xp(sfRectangleShape *xpbar, sfVector2f *taille, int taille_mx, All * all)
{
    int max = all->perso.xp_max;
    int xp = all->perso.xp;
    (*taille).x = (taille_mx * xp) / max;
    if (taille->x > 215) {
        taille->x -= 215;
        all->perso.level += 1;
        all->perso.xp_max = all->perso.level * all->perso.level;
    }
    sfRectangleShape_setSize(xpbar, (*taille));
    sfRectangleShape_setFillColor(xpbar, sfCyan);
}

sfRectangleShape *change_life(sfRectangleShape *lifebar, sfVector2f *taille, int taille_mx, All * all)
{
    int max = all->perso.life_max;
    int life = all->perso.life;
    (*taille).x = (taille_mx * life) / max;
    sfRectangleShape_setSize(lifebar, (*taille));
    int p = life * 100 / max;
    if (p > 50) {
        sfRectangleShape_setFillColor(lifebar, sfColor_fromRGB(24, 206, 24));
        return lifebar;
    }
    if (p == 50 || p > 25) {
        sfRectangleShape_setFillColor(lifebar, sfColor_fromRGB(255, 126, 0));
        return lifebar;
    }
    if (p <= 25) {
        sfRectangleShape_setFillColor(lifebar, sfRed);
        return lifebar;
    }
}

void bar_mob(All * all, u_cmbt cmb, int taille_mx)
{
    Mob *tmp = cmb.l_mob;
    while (tmp != NULL) {
        sfVector2f taille = sfRectangleShape_getSize(tmp->rlb);
        taille.x = (taille_mx * tmp->life) / tmp->life_max;
        sfRectangleShape_setSize(tmp->rlb, taille);
        int p = tmp->life * 100 / tmp->life_max;
        if (p > 50)
            sfRectangleShape_setFillColor(tmp->rlb, sfColor_fromRGB(24, 206, 24));
        else if (p == 50 || p > 25)
            sfRectangleShape_setFillColor(tmp->rlb, sfColor_fromRGB(255, 126, 0));
        else if (p <= 25)
            sfRectangleShape_setFillColor(tmp->rlb, sfRed);
        tmp = tmp->next;
    }
}

void aff_mob(Core *core, Mob *mob, u_cmbt *cmb)
{
    if (mob == NULL){
        cmb->state = 2;
        return;
    }
    Mob *tmp = mob;
    while (tmp != NULL) {
        sfRenderWindow_drawSprite(core->window, tmp->sp, NULL);
        sfRenderWindow_drawRectangleShape(core->window, tmp->rlb, NULL);
        sfRenderWindow_drawSprite(core->window, tmp->slb, NULL);
        tmp = tmp->next;
    }
}

int dead_not_dead(u_cmbt *cmb, Core core, All *all, sfMusic *mus)
{
    if (cmb->state == 1) {
        sfSprite *end = spr_cr("./sprites/loose_screen.jpg", 0, 0);
        sfRenderWindow_drawSprite(core.window, end, NULL);
        sfRenderWindow_display(core.window);
        sfMusic_pause(mus);
        sfMusic *loose_music = sfMusic_createFromFile("loose_music.ogg");
        sfMusic_setLoop(loose_music, sfTrue);
        sfMusic_play(loose_music);
        while (sfRenderWindow_waitEvent(core.window, &core.event) && core.event.type != sfEvtKeyReleased);
        sfRenderWindow_close(core.window);
        sfMusic_destroy(loose_music);
        sfMusic_destroy(mus);
        main();
        return 1;
    }
    if (cmb->state == 2) {
        if (all->utile.degueulassor == 1) {
            sfSprite *end = spr_cr("./sprites/win_screen.jpg", 1, 1);
            sfRenderWindow_drawSprite(core.window, end, NULL);
            sfRenderWindow_display(core.window);
            sfMusic_pause(mus);
            sfMusic *win_music = sfMusic_createFromFile("win_music.ogg");
            sfMusic_setLoop(win_music, sfTrue);
            sfMusic_play(win_music);
            while (sfRenderWindow_waitEvent(core.window, &core.event) && core.event.type != sfEvtKeyReleased);
            sfRenderWindow_close(core.window);
            sfMusic_destroy(mus);
            sfMusic_destroy(win_music);
            main();
        }
        add_xp_potion(all->inventory);
        int randd = rand() % 101;
        if (randd > 90){
            add_pv_potion(all->inventory);
            add_am_potion(all->inventory);
            add_ap_potion(all->inventory);
        } else if (randd > 70) {
            add_pv_potion(all->inventory);
        } else if (randd > 50) {
            add_am_potion(all->inventory);
        } else if (randd > 30)
            add_ap_potion(all->inventory);
        while (sfRenderWindow_waitEvent(core.window, &core.event) && core.event.type != sfEvtKeyReleased);
        return 1;
    }
    return 0;
}

void combat(All *all, Core core, int mob, Mob *l_mob, Core core_opt)
{
    sfMusic *mus = music_cmb(core_opt, all);
    u_cmbt cmb;
    cmb.animation = core_opt.options.anime;
    cmb.l_mob = l_mob;
    cmb.mode = -1;
    cmb.state = 0;
    sfVector2u size = sfRenderWindow_getSize(core.window);
    sfSprite *menu1 = spr_cr("sprites/menucmbt/menu.png", (size.x / 240) * 0.65, 1.4);
    sfSprite *menu2 = spr_cr("sprites/menucmbt/menu.png", (size.x / 240) * 0.397, 1.4);

    sfSprite *lb = spr_cr("sprites/menucmbt/life_bar.png", 3, 2);
    sfSprite *xpb = spr_cr("sprites/menucmbt/life_bar.png", 3, 2);

    sfSprite *bc = spr_cr("sprites/menucmbt/bcc.png", 6, 6);
    cmb.curs = spr_cr("sprites/menucmbt/curseur.png", 3, 3);
    if (all->utile.ancien == 1) bc = spr_cr("sprites/menucmbt/dark_background.png", 1.5, 1.5);
    else {
        sfIntRect rec = rect(0, 0, 240, 128);
        sfSprite_setTextureRect(bc, rec);
    }

    sfRectangleShape *lifebar = sfRectangleShape_create();
    sfVector2f taille = {220, 20};
    int taille_mx = 220;
    sfVector2f pos = {700, 900};

    sfRectangleShape *xpbar = sfRectangleShape_create();
    sfVector2f pos2 = {700, 934};

    lb = pos_sprite(lb, pos.x- 10, pos.y - 4);
    xpb = pos_sprite(xpb, pos.x- 10, pos.y - 4 + 34);

    sfRectangleShape_setSize(lifebar, taille);
    sfRectangleShape_setPosition(lifebar, pos);
    sfRectangleShape_setSize(xpbar, taille);
    sfRectangleShape_setPosition(xpbar, pos2);

    sfVector2f or = {0, 160};
    sfSprite_setOrigin(menu1, or);
    sfSprite_setOrigin(menu2, or);
    menu1 = pos_sprite(menu1, 0, size.y);
    menu2 = pos_sprite(menu2, (240 * (size.x / 240) * 0.65) - 4, size.y);
    cmb.list = list_spell();
    cmb.lx = 0;
    cmb.ly = -1;
    cmb = pos_curs(cmb);
    cmb.menu1 = menu1;
    cmb.menu2 = menu2;
    cmb.bc = bc;
    bar_mob(all, cmb, taille_mx);
    boite_de_texte("You are attacked !", core, cmb);
    while (sfRenderWindow_waitEvent(core.window, &core.event) && core.event.type != sfEvtKeyReleased);
    aff_mob(&core, cmb.l_mob, &cmb);
    while (sfRenderWindow_isOpen(core.window) && all->utile.world == 2) {
        combat_event(&core, all, &cmb);
        if (dead_not_dead(&cmb, core, all, mus) == 1) all->utile.world = all->utile.ancien;
        cmb = pos_curs(cmb);
        sfRenderWindow_display(core.window);
        sfRenderWindow_drawSprite(core.window, bc, NULL);
        sfRenderWindow_drawSprite(core.window, menu1, NULL);
        sfRenderWindow_drawSprite(core.window, menu2, NULL);
        sfRenderWindow_drawSprite(core.window, cmb.curs, NULL);

        sfRenderWindow_drawRectangleShape(core.window, lifebar, NULL);
        sfRenderWindow_drawRectangleShape(core.window, xpbar, NULL);

        sfRenderWindow_drawSprite(core.window, lb, NULL);
        sfRenderWindow_drawSprite(core.window, xpb, NULL);

        lifebar = change_life(lifebar, &taille, taille_mx, all);
        xpbar = change_xp(xpbar, &taille, taille_mx, all);
        bar_mob(all, cmb, taille_mx);
        for (int x = 0; x < 3; x++) {
            sfRenderWindow_drawText(core.window, cmb.list[x]->text, NULL);
            print_spell(cmb, cmb.lx, core);
        }
        cmb.l_mob = sup_mob(cmb.l_mob, &cmb, all);
        aff_mob(&core, cmb.l_mob, &cmb);
    }
    sfMusic_stop(mus);
    sfMusic_destroy(mus);
}

void test_cmb(All *all, Core core, Core core_opt)
{
    char **map = all->utile.map;
    const sfView *truc = sfView_create();
    sfRenderWindow_setView(core.window, truc);
    sfMusic_pause(core_opt.title2);
    sfMusic_pause(core_opt.title);
    int w;
    if (all->utile.ancien == 0)
        w = (rand() % 3) + 1;
    else
        w = (rand() % 2) + 7;
    if (all->utile.degueulassor == 1) w = 6;
    Mob *mob = cr_mob_all(all, w);
    combat(all, core, w, mob, core_opt);
}
