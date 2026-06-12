/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** render_shaders
*/

#include "shaders.h"

static void render(sfRenderTexture *cur_rt, shaders_t *shader)
{
    sfRenderTexture_drawSprite(cur_rt, shader->s, &shader->states);
}

static void update_lighter_shader(global_t *glb)
{
    float time;

    if (!glb->lighter_clock)
        return;
    time = sfTime_asSeconds(sfClock_getElapsedTime(glb->lighter_clock));
    if (glb->game->shader[LIGHTER] && glb->game->shader[LIGHTER]->shader) {
        sfShader_setFloatUniform(glb->game->shader[LIGHTER]->shader,
            "is_active", glb->lighter_active ? 1.0f : 0.0f);
        sfShader_setFloatUniform(glb->game->shader[LIGHTER]->shader,
            "time", time);
        sfShader_setVec2Uniform(glb->game->shader[LIGHTER]->shader,
            "resolution", (sfGlslVec2){SCREEN_WIDTH, SCREEN_HEIGHT});
    }
}

void render_shaders(sfRenderWindow *window, global_t *glb)
{
    update_lighter_shader(glb);
    for (int i = 0; i < NB_SHADERS; i++) {
        if (i == NB_SHADERS - 1) {
            sfRenderWindow_drawSprite(window, glb->game->shader[i]->s,
                &glb->game->shader[i]->states);
            break;
        }
        render(glb->game->rt, glb->game->shader[i]);
    }
}
