/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** input
*/

#ifndef INPUT_H
    #define INPUT_H

    #include "wolf.h"

typedef struct input_s {
    char *buffer;
    int cursor;
    bool is_writing;
    sfText *text_display;
    sfFont *font;
} input_t;

void init_input(global_t *glb);
bool input_function(global_t *glb, sfEvent *event);

#endif
