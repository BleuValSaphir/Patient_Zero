/*
** EPITECH PROJECT, 2025
** my.h for libmy
** File description:
** my.h
*/

#ifndef MAP_GENERATION_H
    #define MAP_GENERATION_H
    #include "wolf.h"

typedef struct point_s {
    int x;
    int y;
} point_t;

typedef struct size_map_s {
    int height;
    int width;
} size_map_t;

int **map_generator(int height, int width);
void generate_rooms(int **map, int w, int h);

#endif /* !MAP_GENERATION_H */
