#include "my.h"
#include "includes/my_h.h"

typedef struct qte {
    sfVector2f vect;
    sfVector2f vect2;
    sfVector2f pos_target;
    sfRectangleShape *peche;
    sfRectangleShape *target;
    sfSprite *bc;
    sfSprite **wat;
    int nb_wat;
    Clock ani;

    sfSprite *pecheur;
    int rec_l;
    int nb_s;
    Clock pec;

    sfSprite *poisson;

    Clock ani_poi;
} qte;

void ani_wat(qte *qte)
{
    qte->ani.time = sfClock_getElapsedTime(qte->ani.clock);
    if (qte->ani.time.microseconds / 10000 >= 10) {
        for(int x = 0; x < qte->nb_wat; x++) {
            sfIntRect re = sfSprite_getTextureRect(qte->wat[x]);
            re.left = re.left + 116;
            if(re.left > 348)
                re.left = 0;
            sfSprite_setTextureRect(qte->wat[x], re);
        }
        sfClock_restart(qte->ani.clock);
    }
}

void ani_pecheur(qte *qte)
{
    qte->pec.time = sfClock_getElapsedTime(qte->pec.clock);
    if (qte->pec.time.microseconds / 10000 >= 10) {
        sfIntRect re = sfSprite_getTextureRect(qte->pecheur);
        re.left = re.left + qte->rec_l;
        if(re.left > (qte->rec_l * qte->nb_s) - 1)
                re.left = 0;
            sfSprite_setTextureRect(qte->pecheur, re);
        sfClock_restart(qte->pec.clock);
    }
}

void ani_poi(qte *qte)
{
    qte->ani_poi.time = sfClock_getElapsedTime(qte->ani_poi.clock);
    if (qte->ani_poi.time.microseconds / 10000 >= 10) {
        sfIntRect re = sfSprite_getTextureRect(qte->poisson);
        re.left = re.left + 49;
        if(re.left > 293)
                re.left = 0;
        sfSprite_setTextureRect(qte->poisson, re);
        sfClock_restart(qte->ani_poi.clock);
    }
}

void yes(Core core, qte *qte, int vitesse)
{
    qte->pos_target.x = qte->pos_target.x + vitesse;
    sfRenderWindow_clear(core.window, sfBlack);
    sfRenderWindow_drawSprite(core.window, qte->bc, NULL);
    sfRenderWindow_drawSprite(core.window, qte->poisson, NULL);
    ani_wat(qte);
    ani_pecheur(qte);
    ani_poi(qte);
    for(int x = 0; x < qte->nb_wat; x++)
        sfRenderWindow_drawSprite(core.window, qte->wat[x], NULL);
    sfRectangleShape_setSize(qte->peche, qte->vect);
    sfRectangleShape_setFillColor(qte->peche, sfColor_fromRGB(0, 255, 0));
    sfRenderWindow_drawRectangleShape(core.window, qte->peche, NULL);
    sfRectangleShape_setSize(qte->target, qte->vect2);
    sfRectangleShape_setPosition(qte->target, qte->pos_target);
    sfRectangleShape_setFillColor(qte->target, sfColor_fromRGBA(255, 255, 0, 190));
    sfRenderWindow_drawRectangleShape(core.window, qte->target, NULL);
    sfRenderWindow_drawSprite(core.window, qte->pecheur, NULL);
    sfRenderWindow_display(core.window);
}

void init_qte(qte *qte)
{
    qte->vect.x = 0;
    qte->vect.y = 60;
    qte->vect2.x = 160;
    qte->vect2.y = 60;
    qte->pos_target.x = 0;
    qte->pos_target.y = 0;
    qte->peche = sfRectangleShape_create();
    qte->target = sfRectangleShape_create();
    sfRectangleShape_setSize(qte->peche, qte->vect);
    qte->pos_target.x = rand() % 840;
    qte->bc = spr_cr("./fishing/map_fish.png", 1, 1);
    int w = (rand() % 10) + 1;
    qte->nb_wat = w;
    qte->wat = malloc(sizeof(sfSprite *) * w);
    for(int x = 0; x < w; x++) {
        sfIntRect rec = rect(0, 0, 116, 104);
        rec.left = (rand() % 4) * 116;
        qte->wat[x] = spr_cr("./fishing/moving_water.png", 1, 1);
        sfSprite_setTextureRect(qte->wat[x], rec);
        sfVector2f pos = {rand() % 900, rand() % 500};
        sfSprite_setPosition(qte->wat[x], pos);
    }
    qte->ani.clock = sfClock_create();
    qte->pec.clock = sfClock_create();
    qte->ani_poi.clock = sfClock_create();
    qte->pecheur = spr_cr("./fishing/pecheur.png", 3.5, 3.5);

    sfIntRect rec = rect(5, 0, 73, 42);
    qte->rec_l = rec.width;
    qte->nb_s = 4;
    sfSprite_setTextureRect(qte->pecheur, rec);
    sfVector2f pos = {200, 800};
    pos.x = pos.x - 64;
    sfSprite_setPosition(qte->pecheur, pos);

    qte->poisson = spr_cr("./fishing/fish.png", 2, 2);
    sfIntRect rec2 = rect(0, 0, 49, 19);
    sfSprite_setTextureRect(qte->poisson, rec2);
    sfVector2f pos2 = {((rand() % (800 + 1 - 600) + 600)), 800};
    sfSprite_setPosition(qte->poisson, pos2);
}

void test_pec(qte *qte, int p)
{
    if (p == 1) {
        if (qte->rec_l == 41)
            return;
        sfVector2f pos = sfSprite_getPosition(qte->pecheur);
        pos.x = pos.x - 9;
        pos.y = pos.y + 3;
        sfSprite_setPosition(qte->pecheur, pos);
        qte->rec_l = 41;
        sfIntRect re = sfSprite_getTextureRect(qte->pecheur);
        re.width = 41;
        re.left = 0;
        re.top = 89;
        re.height = 41;
        sfSprite_setTextureRect(qte->pecheur, re);
        return;
    }
    if (p == 2) {
        if(qte->rec_l == 49)
            return;
        sfVector2f pos = sfSprite_getPosition(qte->pecheur);
        pos.x = pos.x + 9;
        pos.y = pos.y - 3;
        sfSprite_setPosition(qte->pecheur, pos);
        qte->rec_l = 49;
        sfIntRect re = sfSprite_getTextureRect(qte->pecheur);
        re.width = 49;
        re.left = 0;
        re.height = 42;
        re.top = 47;
        sfSprite_setTextureRect(qte->pecheur, re);
        return;
    }
}

void move_fish(qte qte)
{
    sfVector2f pos2 = sfSprite_getPosition(qte.poisson);
    if (qte.vect.x >= qte.pos_target.x && qte.vect.x <= qte.pos_target.x + 160) {
        (pos2.x > 400) ? pos2.x = pos2.x - 3 : 0;
    } else {
        (pos2.x < 1000) ? pos2.x = pos2.x + 5 : 0;
    }
    int x = rand() % 3;
    (x == 0 && pos2.y < 940) ? pos2.y = pos2.y + 1 : 0;
    (x == 1 && pos2.y > 700) ? pos2.y = pos2.y - 1 : 0;
    sfSprite_setPosition(qte.poisson, pos2);
}

void ani_start(Core core, qte *qte)
{
    Clock clo;
    clo.clock = sfClock_create();
    int x = 0;
    while (x < 8) {
        clo.time = sfClock_getElapsedTime(clo.clock);
        if (clo.time.microseconds / 10000 >= 12) {
            x++;
            sfIntRect re = sfSprite_getTextureRect(qte->pecheur);
            re.left = re.left + 73;
            if(re.left > 589)
                    re.left = 0;
            sfSprite_setTextureRect(qte->pecheur, re);
            sfClock_restart(clo.clock);
        }
        sfRenderWindow_clear(core.window, sfBlack);
        sfRenderWindow_drawSprite(core.window, qte->bc, NULL);
        sfRenderWindow_drawSprite(core.window, qte->poisson, NULL);
        ani_wat(qte);
        for(int x = 0; x < qte->nb_wat; x++)
        sfRenderWindow_drawSprite(core.window, qte->wat[x], NULL);
        sfRenderWindow_drawSprite(core.window, qte->pecheur, NULL);
        sfRenderWindow_display(core.window);
    }
    sfVector2f pos = sfSprite_getPosition(qte->pecheur);
    pos.x = pos.x + 64;
    sfSprite_setPosition(qte->pecheur, pos);
}

void ani_win(Core core, qte *qte)
{
    Clock clo;
    clo.clock = sfClock_create();
    int x = 0;
    sfIntRect re = sfSprite_getTextureRect(qte->pecheur);
    sfSprite *catch = spr_cr("./fishing/catch.png", 3.5 ,3.5);
    catch = pos_sprite(catch, 300, -100);
    re.width = 45;
    re.height = 53;
    re.top = 130;
    re.left = 0;
    sfSprite_setTextureRect(qte->pecheur, re);
    sfVector2f pos = sfSprite_getPosition(qte->pecheur);
    pos.x = pos.x - 64;
    sfSprite_setPosition(qte->pecheur, pos);
    while (x < 8) {
        clo.time = sfClock_getElapsedTime(clo.clock);
        sfVector2f p = sfSprite_getPosition(catch);
        (p.y < 300) ? catch = pos_sprite(catch, 300, p.y + 20) : 0;
        if (clo.time.microseconds / 10000 >= 12) {
            x++;
            sfIntRect re = sfSprite_getTextureRect(qte->pecheur);
            re.left = re.left + 45;
            if(re.left > 317)
                break;

            sfSprite_setTextureRect(qte->pecheur, re);
            sfClock_restart(clo.clock);
        }
        sfRenderWindow_clear(core.window, sfBlack);
        sfRenderWindow_drawSprite(core.window, qte->bc, NULL);
        ani_wat(qte);
        for(int x = 0; x < qte->nb_wat; x++)
        sfRenderWindow_drawSprite(core.window, qte->wat[x], NULL);
        sfRenderWindow_drawSprite(core.window, qte->pecheur, NULL);
        sfRenderWindow_drawSprite(core.window, catch, NULL);
        sfRenderWindow_display(core.window);
    }
    while(sfWindow_waitEvent(core.window, &core.event) == sfFalse) {
        sfRenderWindow_clear(core.window, sfBlack);
        sfRenderWindow_drawSprite(core.window, qte->bc, NULL);
        ani_wat(qte);
        for(int x = 0; x < qte->nb_wat; x++)
        sfRenderWindow_drawSprite(core.window, qte->wat[x], NULL);
        sfRenderWindow_drawSprite(core.window, qte->pecheur, NULL);
        sfRenderWindow_drawSprite(core.window, catch, NULL);
        sfRenderWindow_display(core.window);
    }
}

void ani_loose(Core core, qte *qte)
{
    Clock clo;
    clo.clock = sfClock_create();
    int x = 0;
    sfIntRect re = sfSprite_getTextureRect(qte->pecheur);
    sfSprite *catch = spr_cr("./fishing/miss.png", 3.5 ,3.5);
    catch = pos_sprite(catch, 350, -100);
    re.width = 76;
    re.height = 69;
    re.top = 183;
    re.left = 0;
    sfSprite_setTextureRect(qte->pecheur, re);
    sfVector2f pos = sfSprite_getPosition(qte->pecheur);
    pos.x = pos.x - 150;
    pos.y= pos.y - 30;
    sfSprite_setPosition(qte->pecheur, pos);
    while (x < 6) {
        clo.time = sfClock_getElapsedTime(clo.clock);
        sfVector2f p = sfSprite_getPosition(catch);
        (p.y < 300) ? catch = pos_sprite(catch, 350, p.y + 20) : 0;
        if (clo.time.microseconds / 10000 >= 12) {
            x++;
            sfIntRect re = sfSprite_getTextureRect(qte->pecheur);
            re.left = re.left + re.width;
            if(re.left > re.left * 7)
                break;
            sfSprite_setTextureRect(qte->pecheur, re);
            sfClock_restart(clo.clock);
        }
        sfRenderWindow_clear(core.window, sfBlack);
        sfRenderWindow_drawSprite(core.window, qte->bc, NULL);
        ani_wat(qte);
        for(int x = 0; x < qte->nb_wat; x++)
        sfRenderWindow_drawSprite(core.window, qte->wat[x], NULL);
        sfRenderWindow_drawSprite(core.window, qte->pecheur, NULL);
        sfRenderWindow_drawSprite(core.window, catch, NULL);
        sfRenderWindow_display(core.window);
    }
    while(sfWindow_waitEvent(core.window, &core.event) == sfFalse) {
        sfRenderWindow_clear(core.window, sfBlack);
        sfRenderWindow_drawSprite(core.window, qte->bc, NULL);
        ani_wat(qte);
        for(int x = 0; x < qte->nb_wat; x++)
        sfRenderWindow_drawSprite(core.window, qte->wat[x], NULL);
        sfRenderWindow_drawSprite(core.window, qte->pecheur, NULL);
        sfRenderWindow_drawSprite(core.window, catch, NULL);
        sfRenderWindow_display(core.window);
    }
}

int test_end(Core core, qte qte, All *all)
{
    sfVector2f pos = sfSprite_getPosition(qte.poisson);
    if(pos.x <= 400) {
        ani_win(core, &qte);
        quete *tmp = (*all).perso.quest;
        while(tmp != NULL) {
            for(int x = 0; tmp->task[x].name != NULL; x++)
                (tmp->task[x].x == 1) ? tmp->task[x].tot_t++ : 0;
            tmp = tmp->next;
        }
        int x = (rand() % 101);
        if(x > 90) add_gold_salmon(all->inventory);
        if(x < 90 && x > 75) add_tuna(all->inventory);
        if(x <= 75 && x > 40)  add_salmon(all->inventory);
        if(x <= 40) add_sardine(all->inventory);
        return 1;
    }
    if(pos.x >= 1000) {
        ani_loose(core, &qte);
        return 2;
    }
    return 0;
}

void QTE(Core core, All *all)
{
    sfView *viex = sfView_create();
    sfVector2f offset = {0, 0};
    sfView_move(viex, offset);
    sfRenderWindow_setView(core.window, viex);
    qte qte;
    init_qte(&qte);
    ani_start(core, &qte);
    int pos_go = rand() % 840;
    int points = 0, vitesse = 0;
    if (qte.pos_target.x > pos_go) vitesse = vitesse * -1;
    while (sfRenderWindow_isOpen(core.window)) {
        while ((vitesse < 0 && pos_go < qte.pos_target.x) || (vitesse > 0 && pos_go > qte.pos_target.x)) {
            while (sfRenderWindow_pollEvent(core.window, &core.event));
            while (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue) {
                if (test_end(core, qte, all) != 0) return;
                (test_pec(&qte, 1));
                (qte.vect.x < 1000) ? qte.vect.x += 20 : 0;
                move_fish(qte);
                yes(core, &qte, vitesse);
            }
            if (test_end(core, qte, all) != 0) return;
            test_pec(&qte, 2);
            move_fish(qte);
            qte.vect.x > 0 ? qte.vect.x -= 20 : 0;
            yes(core, &qte, vitesse);
        }
        pos_go = rand() % 840;
        vitesse = 4 + rand() % 6;
        if (qte.pos_target.x > pos_go) vitesse = vitesse * -1;
    }
}
