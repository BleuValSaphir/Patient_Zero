/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** shaders
*/



#ifndef SHADERS_H
    #define SHADERS_H

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <stdbool.h>

    #define NB_SHADERS 3

    #define ATMOSPHERE 0
    #define LIGHTER 1
    #define VIGNETTE 2

typedef struct vignette_s {
    bool is_getting_hit;
    bool is_increasing;
    float increase_var;
    float decrease_var;
    float base_radius;
    float min_radius;
    float radius;
    float red_incr;
    float red_decr;
    float red;
    float max_red;
    sfGlslVec3 color;
    sfClock *clock;
} vignette_t;

    #include "game.h"

typedef struct shaders_s {
    const sfTexture *t;
    sfSprite *s;
    sfShader *shader;
    sfRenderStates states;
} shaders_t;

int init_shaders(global_t *glb);
void render_shaders(sfRenderWindow *window, global_t *glb);
void destroy_shaders(shaders_t **shader, vignette_t *vignette);
void update_vignette(global_t *glb);

typedef shaders_t *(*init_shader_t)(global_t *glb);

shaders_t *init_atmosphere(global_t *glb);
shaders_t *init_vignette(global_t *glb);
shaders_t *init_lighter(global_t *glb);

static const init_shader_t init_each_shaders[] = {
    init_atmosphere,
    init_lighter,
    init_vignette,
    NULL
};

#endif
