/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** input
*/

#include "input.h"

bool manage_input_event(global_t *glb, sfEvent *event)
{
    if (event->type == sfEvtTextEntered && glb->ipt->is_writing) {
        if (event->text.unicode == 8 && glb->ipt->cursor > 0) {
            glb->ipt->cursor--;
            glb->ipt->buffer[glb->ipt->cursor] = '\0';
        }
        if (event->text.unicode >= 32 && event->text.unicode < 127 &&
            glb->ipt->cursor < 29) {
            glb->ipt->buffer[glb->ipt->cursor] = (char)event->text.unicode;
            glb->ipt->cursor++;
            glb->ipt->buffer[glb->ipt->cursor] = '\0';
        }
    }
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEnter)
        glb->ipt->is_writing = false;
    return false;
}

bool input_function(global_t *glb, sfEvent *event)
{
    if (manage_input_event(glb, event) == true)
        return true;
    return false;
}

void init_input(global_t *glb)
{
    glb->ipt = malloc(sizeof(input_t));
    if (!glb->ipt)
        return;
    glb->ipt->is_writing = false;
    glb->ipt->cursor = 0;
    glb->ipt->buffer = malloc(sizeof(char) * 256);
    glb->ipt->buffer[0] = '\0';
    glb->ipt->text_display = sfText_create();
    glb->ipt->font = sfFont_createFromFile("./assets/font/Roboto.ttf");
    sfText_setFont(glb->ipt->text_display, glb->ipt->font);
    sfText_setCharacterSize(glb->ipt->text_display, 30);
    sfText_setFillColor(glb->ipt->text_display, sfWhite);
}
