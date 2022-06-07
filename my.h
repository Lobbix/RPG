/*
** EPITECH PROJECT, 2021
** my.h
** File description:
** my
*/

#ifndef _MY_H_
#define _MY_H_

    #include <SFML/Window.h>
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/System/Vector2.h>

    #include <stddef.h>
    #include <time.h>
    #include <unistd.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include<fcntl.h>

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <string.h>

typedef struct Chaine {
    char *str;
    sfVector2f pos;
    sfText *texte;
    struct Chaine *next;
    struct Chaine *prev;
} Chaine;

typedef struct Options {
    int muted;
    int music_volume;
    int is_rain;
    int fps_num;
    int anime;
}Options;

typedef struct Core {
    sfEvent event;
    sfRenderWindow *window;
    Options options;
    int x;
    sfMusic *title;
    sfMusic *title2;
}Core;

typedef struct Menu{
    sfVector2i pos_mouse;
    sfVector2f pos_des;
    sfVector2f pos_cursor;
    sfRenderWindow *window;
    sfEvent event;
}Menu;

typedef struct Stat {
    int ap;
    int am;
}Stat;

typedef struct Perso {
    int x;
    int y;
    sfSprite *perso;
    sfSprite *parle;
    sfIntRect rec;
    Stat *stat;
    int wichone;
    int life;
    int level;
    int life_max;
    int xp;
    int xp_max;
    char *parle2;
    char *perso2;
    struct quete *quest;
}Perso;

typedef struct Item {
    char *name;
    sfVector2f pos;
    sfSprite *sprite;
    sfSprite *description;
    int pv;
    int xp;
    int ap;
    int am;
    int life;
    struct Item *next;
}Item;

typedef struct Inventory {
    Item *first;
    sfSprite *sprite;
}Inventory;

typedef struct gr_combat {
    struct gr_combat *next;
    char *sp_att;
    int sp_sh;
    int type;
    char *name;
    int sta;
    int nbr;
    sfText *text;
}gr_combat;

typedef struct Utile {
    char **map;
    char **map2;
    int gauche;
    int haut;
    int maison;
    int monstre;
    int PNJ;
    int world;
    int mapmonde;
    int mapmonde2;
    char *phrase;
    char p_step;
    int arbre;
    int doremem;
    int doremem2;
    int ancien;
    int degueulassor;
}Utile;

typedef struct Portal {
    sfSprite *ouverture;
    sfSprite *permanence;
    sfSprite *cassage;
}Portal;

typedef struct Mob {
    int type;
    sfSprite *sp;
    int move;
    int life;
    int life_max;
    // int level;
    int att;
    // int def;
    sfSprite *slb;
    sfRectangleShape *rlb;
    struct Mob *next;
}Mob;

typedef struct Clock {
    sfClock *clock;
    sfTime time;
}Clock;

typedef struct Map {
    sfSprite *map;
    sfView *view;
    sfView *view2;
}Map;

typedef struct task {
    char *name;
    int x;
    int tot_t;
    int objectif;
    int finished;
} task;

typedef struct quete {
    char *name;
    char *pnj_tx;
    struct task *task;
    struct quete *next;
    int finished;
} quete;

typedef struct pnj {
    sfSprite *sp;
    sfVector2f pos;
    struct quete *quest;
    struct pnj *next;
} pnj;

typedef struct Boss {
    sfSprite *boss;
}Boss;


typedef struct All {
    Perso perso;
    Utile utile;
    Clock un;
    Clock deux;
    Clock trois;
    Map map;
    Mob *mob;
    Core core;
    Portal portal;
    pnj *pnj;
    Boss boss;
    Inventory *inventory;
} All;

typedef struct u_cmbt {
    struct gr_combat **list;
    int lx;
    int ly;
    int mode;
    int animation;
    int state;
    sfSprite *curs;
    struct Mob *l_mob;
    sfSprite *menu1;
    sfSprite *menu2;
    sfSprite *bc;
} u_cmbt;

int counter(char *file);
int counter2(char *file);
char **my_str2(char *file, int nb);
char **ouvre_fichiez(char *str);
void affichage(char **str2);

void print_pnj(All all);

void mvt_perso(All *all);
int cond(char **map, int x, int y, Utile *utile, All *all);
void do_mvt(int x, int y, All *all);
void do_clock2(All *all);
void do_go_mid(All *all);

sfText *text(char *cscore, char *pathfont, int size, int pos1, int pos2);
void parler(All *all, Core *core);
void event(All *all, Core *core);

sfSprite *pos_sprite(sfSprite *sp, int x, int y);
sfSprite *spr_cr(char *Texture, float scalex , float scaley);
sfIntRect rect(int top, int left, int width, int height);

// Mob *cr_mob(int t, sfRectangleShape *rc);
// void aff_mob(All *all, Core *core);
// Mob *add_mob(Mob *list, int t, int x, int y);
// Mob *cr_mob_all(All *all, int k);
// int len_mob_lc(Mob *mob);
// void move_mob(All *all);

float my_atof(char *arr);
Mob *cr_mob(int t, char **info);
int len_mob_lc(Mob *mob);
Mob *add_mob(Mob *list, int t, char **info, int p, All *all);
Mob *sup_mob(Mob *l_mob, u_cmbt *cmb, All *all);
char **get_info_mob(int type);
Mob *cr_mob_all(All *all, int type);


int len_list_sp(gr_combat *list);
void boite_de_texte(char *str, Core core, u_cmbt cmb);
gr_combat *get_stat_spell(char *name, gr_combat *cell);
gr_combat *add_spell(gr_combat *list, char *name, int i, int w);
gr_combat **list_spell();
void print_spell(u_cmbt cmb, int i, Core core);
void do_damage(u_cmbt *cmb, Core core, All *all);
void combat_event(Core *core, All *all, u_cmbt *cmb);
u_cmbt pos_curs(u_cmbt cmb);
sfIntRect rect(int top, int left, int width, int height);
sfRectangleShape *change_xp(sfRectangleShape *xpbar, sfVector2f *taille, int taille_mx, All * all);
sfRectangleShape *change_life(sfRectangleShape *lifebar, sfVector2f *taille, int taille_mx, All * all);
void bar_mob(All * all, u_cmbt cmb, int taille_mx);
void combat(All *all, Core core, int mob, Mob *l_mob, Core core_opt);
void test_cmb(All *all, Core core, Core core_opt);
void aff_mob(Core *core, Mob *mob, u_cmbt *cmb);

void knight(Menu menu, sfSprite *s_knight, sfSprite *s_cursor, Perso *perso);
void elf(Menu menu, sfSprite *s_elf, sfSprite *s_cursor, Perso *perso);
void sorcerer(Menu menu, sfSprite *s_sorcerer, sfSprite *s_cursor, Perso *perso);
void demon(Menu menu, sfSprite *s_demon, sfSprite *s_cursor, Perso *perso);
void main3(Perso perso, Core core_opt);

sfRenderWindow *renderwindow(Core core);
void where_perso(Perso *perso, Utile utile);
void do_clock(Clock *clocki, All *all);
void mapmonde(Clock *clocki, All *all, Core *core, Core core_opt);
void verif(All *all, Core *core);
void mapnormal(Clock *clocki, All *all, Core *core, pnj *pnj1, sfSprite *portal, Core core_opt);
void main2(Core core, All all, Clock clocki, Core core_opt);
void main3();

int get_nbr(char *yes);
int my_putnbr(int n);
char *my_strcpy(char *eee);
char *my_fusion(char *str1, char *str2);

char my_putchar(char c);
void my_putstr(char *str);
int my_strlen(char *str);
char *my_revstr(char *a);
char *get_inf_nbr(int w);

Chaine *add_cell(char *str, int x, int y);
Chaine *creatcell(Chaine *menu, char *str, int x, int y);

void main_classe(Core core);

//my_sounds.c

sfMusic *music_cmb(Core core_opt, All *all);

//pnj.c

struct quete *add_quest();
struct quete *quest(char *file, int c);

//menu.c

void affiche_menu(Chaine *chaine, Core core, size_t i);
int New(Chaine *chaine, Core core);
void Continue(Chaine *chaine);
char *int_to_char(int nb);
void Option(Chaine *chaine, Core core);
void Exit(Chaine *chaine);
int boite_de_texte2(char *str, Core core, sfSprite *one);
int intro(Core core);
int main_clone(Core core);
void main();

void do_clock3(Clock *clocki, All *all);
void mvt_perso2(All *all);

char *int_to_str(int nb);

//portal

sfIntRect portal(Core core, All *all, sfSprite *portal, sfIntRect rectp);

//peche

void QTE(Core core, All *all);

#endif
