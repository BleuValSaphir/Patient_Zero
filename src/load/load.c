/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** load the map
*/

#include "wolf.h"

int get_map_size(global_t *glb, FILE *file, size_t *line)
{
    char *buf = NULL;

    for (int i = 0; i < 2; i++) {
        if (getline(&buf, line, file) == -1 || !buf) {
            free(buf);
            return ERROR;
        }
        buf[strlen(buf)] = '\0';
        if (i == 0)
            MAP_WIDTH = atoi(buf);
        else
            MAP_HEIGHT = atoi(buf);
    }
    free(buf);
    return (MAP_WIDTH < 20 || MAP_WIDTH != MAP_HEIGHT) ? ERROR : SUCCESS;
}

static int parse_map(global_t *glb, FILE *file, char ***map)
{
    int cur_nb = 0;

    if (!map)
        return ERROR;
    glb->map = malloc(sizeof(int *) * MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        glb->map[i] = malloc(sizeof(int) * MAP_WIDTH);
        for (int j = 0; j < MAP_WIDTH; j++) {
            cur_nb = atoi(map[i][j]);
            glb->map[i][j] = cur_nb;
            free(map[i][j]);
        }
        free(map[i]);
    }
    free(map);
    fclose(file);
    return (check_prerequisite_map(glb) == ERROR) ? ERROR : SUCCESS;
}

static int get_token(global_t *glb, char **strline, char *buf)
{
    char *token = NULL;
    int j = 0;

    token = strtok(buf, ",\n");
    for (; token; j++) {
        strline[j] = strdup(token);
        if (!strline[j])
            return ERROR;
        token = strtok(NULL, ",\n");
    }
    if (j != MAP_WIDTH)
        return ERROR;
    return SUCCESS;
}

static int process_line(global_t *glb, char *buf, char ***map, int i)
{
    if (!buf || i > MAP_HEIGHT)
        return ERROR;
    map[i] = malloc(sizeof(char *) * (MAP_WIDTH + 1));
    if (!map[i])
        return ERROR;
    if (get_token(glb, map[i], buf) == ERROR)
        return ERROR;
    return SUCCESS;
}

int get_inside_of_map(global_t *glb, FILE *file, size_t *line)
{
    char *buf = NULL;
    char ***map = malloc(sizeof(char **) * (MAP_HEIGHT + 1));
    int i = 0;

    for (; getline(&buf, line, file) != -1; i++) {
        if (process_line(glb, buf, map, i) == ERROR) {
            free(buf);
            return ERROR;
        }
    }
    free(buf);
    if (i != MAP_HEIGHT)
        return ERROR;
    return parse_map(glb, file, map);
}

int get_map(global_t *glb, FILE *file)
{
    size_t line = 0;

    if (get_map_size(glb, file, &line) == ERROR)
        return ERROR;
    if (get_inside_of_map(glb, file, &line) == ERROR)
        return ERROR;
    return SUCCESS;
}

void load_map(global_t *glb)
{
    FILE *file = NULL;
    char path[256];

    if (!glb || !glb->ipt || !glb->ipt->buffer)
        return;
    sprintf(path, "saves_wolf3d/%s", glb->ipt->buffer);
    file = fopen(path, "r");
    if (!file)
        return;
    if (get_map(glb, file) == ERROR)
        return;
    glb->valid_file = true;
}
