/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** particules
*/

#include "wolf.h"

void spawn_blood(global_t *glb, float x, float y)
{
    int count = 0;

    for (int i = 0; i < MAX_PARTICLES && count < 15; i++) {
        if (!glb->game->particles[i].active) {
            glb->game->particles[i].active = 1;
            glb->game->particles[i].x = x;
            glb->game->particles[i].y = y;
            glb->game->particles[i].vx = ((rand() % 100) - 50) / 1500.0f;
            glb->game->particles[i].vy = ((rand() % 100) - 50) / 1500.0f;
            glb->game->particles[i].life = 1.0f;
            count++;
        }
    }
}

static void update_particules_next(global_t *glb, int i)
{
    if (glb->game->particles[i].active) {
        glb->game->particles[i].x += glb->game->particles[i].vx;
        glb->game->particles[i].y += glb->game->particles[i].vy;
        glb->game->particles[i].life -= 0.05f;
        if (glb->game->particles[i].life <= 0.0f)
            glb->game->particles[i].active = 0;
    }
}

void update_particles(global_t *glb)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        update_particules_next(glb, i);
    }
}

static void draw_single_particle(global_t *glb, particle_t *p, float *c)
{
    float sX = p->x - glb->player.x;
    float sY = p->y - glb->player.y;
    float trY = (-c[3] * sX + c[2] * sY) / (c[2] * c[1] - c[0] * c[3]);
    float trX = (c[1] * sX - c[0] * sY) / (c[2] * c[1] - c[0] * c[3]);
    sfRectangleShape *r;

    if (trY <= 0.1f)
        return;
    sX = (SCREEN_WIDTH / 2) * (1 + trX / trY);
    if (sX < 0 || sX >= SCREEN_WIDTH || trY >= glb->game->z_buffer[(int)sX])
        return;
    r = sfRectangleShape_create();
    sfRectangleShape_setSize(r, (sfVector2f){10 / trY, 10 / trY});
    sfRectangleShape_setPosition(r, (sfVector2f){sX, (SCREEN_HEIGHT / 2) +
            (600.0f + (1.0f - p->life) * 1000.0f) / trY + glb->player.pitch});
    sfRectangleShape_setFillColor(r,
        sfColor_fromRGBA(200, 0, 0, p->life * 255));
    sfRenderTexture_drawRectangleShape(glb->game->rt, r, NULL);
    sfRectangleShape_destroy(r);
}

void render_particles(global_t *glb)
{
    float cam[4] = {
        cos(glb->player.angle), sin(glb->player.angle),
        -sin(glb->player.angle) * tan(FOV / 2),
        cos(glb->player.angle) * tan(FOV / 2)
    };

    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (glb->game->particles[i].active)
            draw_single_particle(glb, &glb->game->particles[i], cam);
    }
}
