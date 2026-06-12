/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** utils.c
*/

#include "wolf.h"

int manage_env(char **env)
{
    int display = 0;

    if (!env || !*env)
        return ERROR;
    for (int i = 0; env[i] != NULL; i++) {
        if ((strncmp(env[i], "DISPLAY=", 8) == 0)) {
            display = 1;
            return 1;
        }
    }
    if (!display) {
        write(2, "This program cannot be executed in the tty\n", 44);
        return ERROR;
    }
    return SUCCESS;
}
