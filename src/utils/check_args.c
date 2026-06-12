/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** check_args.c
*/

#include "wolf.h"

int check_args(int ac, char **av)
{
    if ((ac == 2 && strcmp(av[1], "-h") == 0) ||
        (ac == 2 && strcmp(av[1], "-help") == 0)) {
        print_usage();
    }
    return SUCCESS;
}
