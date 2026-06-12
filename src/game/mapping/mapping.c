/*
** EPITECH PROJECT, 2026
** map generator for wolf3d
** File description:
** map generator
*/
#include "map_generation.h"

static const int dirs[4][2] = {{0, -2}, {2, 0}, {0, 2}, {-2, 0}};

static void shuffle_dirs(int perm[4])
{
    int j = 0;
    int tmp = 0;

    for (int i = 0; i < 4; i++)
        perm[i] = i;
    for (int i = 3; i > 0; i--) {
        j = rand() % (i + 1);
        tmp = perm[i];
        perm[i] = perm[j];
        perm[j] = tmp;
    }
}

void free_map(int **map, int height)
{
    for (int i = 0; i < height; i++) {
        free(map[i]);
    }
    free(map);
}

static int maze_carver(int **map, int top, point_t *stack, point_t *size)
{
    point_t cur = stack[top - 1];
    int perm[4];
    int found = 0;
    int nx = 0;
    int ny = 0;

    shuffle_dirs(perm);
    for (int i = 0; i < 4 && !found; i++) {
        nx = cur.x + dirs[perm[i]][0];
        ny = cur.y + dirs[perm[i]][1];
        if (nx > 0 && nx < size->x - 1 && ny > 0 && ny < size->y - 1
            && map[ny][nx] == 1) {
            map[cur.y + dirs[perm[i]][1] / 2][cur.x + dirs[perm[i]][0] / 2] = 0;
            map[ny][nx] = 0;
            stack[top] = (point_t){nx, ny};
            top++;
            found = 1;
        }
    }
    return found ? top : top - 1;
}

static void carve_maze(int **map, int w, int h)
{
    point_t *stack = malloc(w * h * sizeof(point_t));
    int top = 0;

    map[1][1] = 0;
    stack[top] = (point_t){1, 1};
    top++;
    while (top > 0) {
        top = maze_carver(map, top, stack, &(point_t){w, h});
    }
    free(stack);
}

int **map_generator(int height, int width)
{
    int **map = malloc(height * sizeof(int *));

    if (height != width || height < 3 || width < 3) {
        fprintf(stderr, "error: wrong size\n");
        free(map);
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        map[i] = malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) {
            map[i][j] = 1;
        }
    }
    srand(time(NULL));
    carve_maze(map, width, height);
    generate_rooms(map, width, height);
    map[1][1] = 2;
    map[height - 2][width - 2] = 3;
    return map;
}
