/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** render_floor.c
*/

#include "wolf.h"

static void set_fc_shader_uniforms(global_t *glb)
{
    sfShader_setTextureUniform(glb->fc_shader, "floor_tex",
        glb->floor_texture);
    sfShader_setTextureUniform(glb->fc_shader, "ceil_tex",
        glb->ceiling_texture);
    sfShader_setVec2Uniform(glb->fc_shader, "resolution",
        (sfGlslVec2){(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT});
    sfShader_setVec2Uniform(glb->fc_shader, "player_pos",
        (sfGlslVec2){glb->player.x, glb->player.y});
    sfShader_setFloatUniform(glb->fc_shader, "player_angle",
        glb->player.angle);
    sfShader_setFloatUniform(glb->fc_shader, "player_pitch",
        (float)glb->player.pitch);
}

void render_floor_and_ceiling(sfRenderTexture *rt, global_t *glb)
{
    sfRectangleShape *rect;
    sfRenderStates states;

    if (!glb->fc_shader || !glb->floor_texture || !glb->ceiling_texture)
        return;
    set_fc_shader_uniforms(glb);
    rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect,
        (sfVector2f){(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT});
    states = sfRenderStates_default();
    states.shader = glb->fc_shader;
    sfRenderTexture_drawRectangleShape(rt, rect, &states);
    sfRectangleShape_destroy(rect);
}
