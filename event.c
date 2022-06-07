#include "my.h"
#include "includes/my_h.h"

sfText *text(char *cscore, char *pathfont, int size, int pos1, int pos2)
{
    sfText *tscore = sfText_create();
    sfText_setString(tscore, cscore);
    sfVector2f scorepos = {500, 500};
    sfText_setCharacterSize(tscore, size);
    sfFont *font = sfFont_createFromFile(pathfont);
    sfText_setFont(tscore, font);
    sfVector2f titlepos = {pos1, pos2};
    sfText_setPosition(tscore, titlepos);
    return tscore;
}

void boite_de_texte3(char *str, Core core, sfSprite *bc, All all)
{
    char *ee = my_strcpy(str);
    int x = my_strlen(ee);
    char tmp;
    sfText *txt;
    for (int w = 0; sfRenderWindow_isOpen(core.window) && w != x + 2; w++) {
        (w > 0) ? ee[w - 1] = tmp : 0;
        tmp = ee[w];
        ee[w] = '\0';
        sfVector2f pos = sfView_getCenter(sfRenderWindow_getView(core.window));
        pos.x = pos.x - 300;
        pos.y = pos.y + 300;
        txt = text(ee, "./sprites/menucmbt/3.ttf", 40, 70, 760);
        sfText_setPosition(txt, pos);
        sfRenderWindow_drawSprite(core.window, bc, NULL);
        sfRenderWindow_drawText(core.window, txt, NULL);
        print_pnj(all);
        sfRenderWindow_drawSprite(core.window, all.perso.perso, NULL);
        sfRenderWindow_display(core.window);
    }
}


int my_strncmp(char *or, char *test)
{
    if (my_strlen(or) != my_strlen(test))
        return 0;
    for (int i = 0; i < my_strlen(test); i++) {
        if (or[i] != test[i])
            return 0;
    }
    return 1;
}


quete *get_quest(quete *quest, quete *new)
{
    quete *t = quest;
    int x = 0;
    while (t != NULL) {
        x++;
        if(my_strncmp(t->name, new->name) == 1) return quest;
        t = t->next;
    }
    if (x > 1) return quest;
    quete *tmp = new;
    tmp->next = NULL;
    if(quest == NULL) {
        quest = tmp;
        quest->next = NULL;
        return quest;
    }
    tmp->next = quest;
    quest = tmp;
    return quest;
}

int len_li_quete(quete *q)
{
    quete *t = q;
    int x = 0;
    while(q != NULL) {
        x++;
        q = q->next;
    }
    return x;
}

void parler(All *all, Core *core)
{
    sfSprite *sp = spr_cr("./sprites/menucmbt/menu.png", 4.2, 1.5);
    sfVector2f pos = sfView_getCenter(sfRenderWindow_getView(core->window));
    pos.x = pos.x - 500;
    pos.y = pos.y + 260;
    //1000 980
    sfSprite_setPosition(sp, pos);
    pnj *tmp = all->pnj;
    for (int x = 0; x < all->utile.PNJ; x++)
        tmp = tmp->next;
    quete *tmp_q = tmp->quest;
    while (tmp_q != NULL && tmp_q->finished != 0)
        tmp_q = tmp_q->next;
    boite_de_texte3(tmp_q->pnj_tx, *core, sp, *all);
    if(len_li_quete(all->perso.quest) < 2) {
        all->pnj->quest = all->pnj->quest->next;
        while (sfRenderWindow_waitEvent(core->window, &core->event) && core->event.type != sfEvtKeyPressed);
        all->perso.quest = get_quest(all->perso.quest, tmp_q);
    }
    all->utile.PNJ = -1;
}

void event(All *all, Core *core)
{
    if(all->utile.PNJ != -1)
        parler(all, core);
}