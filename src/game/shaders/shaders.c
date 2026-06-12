/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** shaders
*/

#include "shaders.h"

void destroy_shaders(shaders_t **shader, vignette_t *vignette)
{
    if (!shader)
        return;
    for (int i = 0; i < NB_SHADERS && shader[i]; i++) {
        if (shader[i]->s)
            sfSprite_destroy(shader[i]->s);
        if (shader[i]->shader)
            sfShader_destroy(shader[i]->shader);
        free(shader[i]);
    }
    free(shader);
    if (vignette->clock)
        sfClock_destroy(vignette->clock);
}

shaders_t *init_atmosphere(global_t *glb)
{
    shaders_t *at = malloc(sizeof(shaders_t));

    at->shader = sfShader_createFromFile(NULL, NULL,
        "assets/shaders/atmosphere.frag");
    at->s = sfSprite_create();
    at->states = sfRenderStates_default();
    if (!at->shader || !at->s)
        return NULL;
    at->t = sfRenderTexture_getTexture(glb->game->rt);
    if (!at->t)
        return NULL;
    sfSprite_setTexture(at->s, at->t, sfTrue);
    at->states.shader = at->shader;
    return at;
}

shaders_t *init_lighter(global_t *glb)
{
    shaders_t *at = malloc(sizeof(shaders_t));

    at->shader = sfShader_createFromFile(NULL, NULL,
        "assets/shaders/lighter.frag");
    at->s = sfSprite_create();
    at->states = sfRenderStates_default();
    if (!at->shader || !at->s)
        return NULL;
    at->t = sfRenderTexture_getTexture(glb->game->rt);
    if (!at->t)
        return NULL;
    sfSprite_setTexture(at->s, at->t, sfTrue);
    at->states.shader = at->shader;
    return at;
}

static void init_vignette_struct(vignette_t *vignette)
{
    vignette->is_getting_hit = false;
    vignette->is_increasing = false;
    vignette->increase_var = 0.02;
    vignette->decrease_var = 0.0025;
    vignette->base_radius = 0.8;
    vignette->min_radius = 0.7;
    vignette->radius = vignette->base_radius;
    vignette->red_incr = 0.06;
    vignette->red_decr = 0.0075;
    vignette->red = 0.;
    vignette->max_red = 0.3;
    vignette->color = (sfGlslVec3){vignette->red, 0., 0.};
    vignette->clock = sfClock_create();
}

shaders_t *init_vignette(global_t *glb)
{
    shaders_t *at = malloc(sizeof(shaders_t));

    init_vignette_struct(&glb->game->vignette);
    at->shader = sfShader_createFromFile(NULL, NULL,
        "assets/shaders/vignette.frag");
    at->s = sfSprite_create();
    at->states = sfRenderStates_default();
    if (!at->shader || !at->s)
        return NULL;
    sfShader_setFloatUniform(at->shader, "radius",
        glb->game->vignette.base_radius);
    sfShader_setFloatUniform(at->shader, "vignette_var", 0.35);
    sfShader_setVec3Uniform(at->shader, "color", glb->game->vignette.color);
    at->t = sfRenderTexture_getTexture(glb->game->rt);
    if (!at->t)
        return NULL;
    sfSprite_setTexture(at->s, at->t, sfTrue);
    at->states.shader = at->shader;
    return at;
}

int init_shaders(global_t *glb)
{
    glb->game->shader = malloc(sizeof(shaders_t) * NB_SHADERS);
    if (!glb->game->shader)
        return ERROR;
    for (int i = 0; i < NB_SHADERS; i++) {
        glb->game->shader[i] = init_each_shaders[i](glb);
        if (!glb->game->shader[i])
            return ERROR;
    }
    return 0;
}
