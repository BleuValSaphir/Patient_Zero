/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** font_text.c
*/

#include "utils.h"


void destroy_text(text_t *txt)
{
    if (!txt)
        return;
    if (txt->font)
        sfFont_destroy(txt->font);
    if (txt->text)
        sfText_destroy(txt->text);
    free(txt);
}

text_t *set_text(sfColor *color, const sfVector2f *pos, text_info_t *inf)
{
    text_t *txt = malloc(sizeof(*txt) * 1);

    if (!txt)
        exit(ERROR);
    txt->font = sfFont_createFromFile(inf->filepath);
    txt->text = sfText_create();
    if (!txt->font || !txt->text) {
        destroy_text(txt);
        exit(ERROR);
    }
    sfText_setFont(txt->text, txt->font);
    sfText_setCharacterSize(txt->text, inf->size);
    sfText_setColor(txt->text, *color);
    sfText_setPosition(txt->text, *pos);
    sfText_setString(txt->text, inf->str);
    return txt;
}
