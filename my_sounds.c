/*
** EPITECH PROJECT, 2021
** my_sounds
** File description:
** my_sounds.c
*/

#include "my.h"

// void soundbutton(void)
// {
//     sfSoundBuffer *butbuff = sfSoundBuffer_createFromFile("sounds/button.wav");
//     sfSound *button = sfSound_create();
//     sfSound_setBuffer(button, butbuff);
//     sfSound_play(button);
// }
sfMusic *music_cmb(Core core_opt, All *all)
{
    sfMusic *mus = sfMusic_createFromFile("./sprites/menucmbt/cmb_music.ogg");
    if (all->utile.degueulassor == 1) mus = sfMusic_createFromFile("boss.ogg");
    sfMusic_setLoop(mus, sfTrue);
    sfMusic_play(mus);
    if (core_opt.options.muted == 1) sfMusic_setVolume(mus, 0);
    sfMusic_setVolume(mus, core_opt.options.music_volume);
    return mus;
}

// void soundkill(void)
// {
//     sfSoundBuffer *buffkill = sfSoundBuffer_createFromFile("sounds/killtest.flac");
//     sfSound *button = sfSound_create();
//     sfSound_setBuffer(button, buffkill);
//     sfSound_setVolume(button, 5);
//     sfSound_play(button);
// }

// void soundshoot(void)
// {
//     sfSoundBuffer *buffgun2 = sfSoundBuffer_createFromFile("sounds/2.wav");
//     sfSoundBuffer *buffgun1 = sfSoundBuffer_createFromFile("sounds/1.wav");
//     sfSound *button2 = sfSound_create();
//     if (rand() % 2 == 1)
//         sfSound_setBuffer(button2, buffgun1);
//     else
//         sfSound_setBuffer(button2, buffgun2);
//     sfSound_setVolume(button2, 10);
//     sfSound_play(button2);
// }