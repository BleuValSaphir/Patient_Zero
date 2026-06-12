/*
** EPITECH PROJECT, 2026
** map rooms generator
** File description:
** map rooms generator
*/

#include "map_generation.h"

static void fill_room(int **map, int r[4], int value)
{
    for (int y = r[1]; y < r[1] + r[3]; y++) {
        for (int x = r[0]; x < r[0] + r[2]; x++) {
            map[y][x] = value;
        }
    }
}

static void add_start_end_room(int **map, int w, int h)
{
    int start_r[4] = {1, 1, 4, 4};
    int end_r[4] = {w - 5, h - 5, 4, 4};

    if (start_r[0] + start_r[2] < w && start_r[1] + start_r[3] < h)
        fill_room(map, start_r, 4);
    if (end_r[0] > 0 && end_r[1] > 0)
        fill_room(map, end_r, 4);
}

void generate_rooms(int **map, int w, int h)
{
    int num_rooms = (w * h) / 80;
    int r[4];

    for (int i = 0; i < num_rooms; i++) {
        r[2] = (rand() % 6) + 4;
        r[3] = (rand() % 6) + 4;
        r[0] = (rand() % (w - r[2] - 2)) + 1;
        r[1] = (rand() % (h - r[3] - 2)) + 1;
        fill_room(map, r, 0);
    }
    add_start_end_room(map, w, h);
}
