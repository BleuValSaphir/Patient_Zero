/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** check_prerequisite_map
*/

#include "load.h"

static int check_each_case(global_t *glb, int y)
{
    for (int x = 0; x < MAP_WIDTH; x++) {
        if ((y == 0 || x == 0) && glb->map[y][x] != 1)
            return ERROR;
    }
    return SUCCESS;
}

int check_prerequisite_map(global_t *glb)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        if (check_each_case(glb, y) == ERROR)
            return ERROR;
    return SUCCESS;
}
