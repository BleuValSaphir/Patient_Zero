/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** engine.c
*/

#include "wolf.h"

void handle_event(sfRenderWindow *window, scene_type_t *next_scene,
    scene_t *current_scene, global_t *glb)
{
    sfVector2i pixel_pos;
    sfVector2f world_pos;

    if (glb->event.type == sfEvtMouseButtonPressed ||
        glb->event.type == sfEvtMouseButtonReleased) {
        pixel_pos = (sfVector2i){glb->event.mouseButton.x,
            glb->event.mouseButton.y};
        world_pos = sfRenderWindow_mapPixelToCoords(window, pixel_pos, NULL);
        glb->event.mouseButton.x = (int)world_pos.x;
        glb->event.mouseButton.y = (int)world_pos.y;
    }
    if (glb->event.type == sfEvtMouseMoved) {
        pixel_pos = (sfVector2i){glb->event.mouseMove.x,
            glb->event.mouseMove.y};
        world_pos = sfRenderWindow_mapPixelToCoords(window, pixel_pos, NULL);
        glb->event.mouseMove.x = (int)world_pos.x;
        glb->event.mouseMove.y = (int)world_pos.y;
    }
    if (current_scene->handle_events)
        current_scene->handle_events(glb, &glb->event, next_scene);
}

void manage_event(sfRenderWindow *window, scene_type_t *next_scene,
    scene_t *current_scene, global_t *glb)
{
    sfView *view;

    if (glb->event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (glb->event.type == sfEvtResized) {
        view = sfView_createFromRect((sfFloatRect){0, 0, SCREEN_WIDTH,
                SCREEN_HEIGHT});
        if (view) {
            sfRenderWindow_setView(window, view);
            sfView_destroy(view);
        }
    }
    handle_event(window, next_scene, current_scene, glb);
}

static scene_t *handle_type(scene_type_t next_type)
{
    scene_t *(*const creators[])(void) = {
        create_menu_scene, create_main_menu_scene, create_cinematic_scene,
        create_game_scene, NULL, create_settings_scene, create_load_scene,
        create_save_scene
    };

    if (next_type >= SCENE_MENU && next_type <= SCENE_SAVE &&
        creators[next_type])
        return creators[next_type]();
    return NULL;
}

static void manage_game_music(scene_type_t next_type, global_t *glb)
{
    if (!glb->game_music || !glb->game_music->sound)
        return;
    if (next_type == SCENE_GAME) {
        if (sfSound_getStatus(glb->game_music->sound) != sfPlaying)
            sfSound_play(glb->game_music->sound);
    }
    if (next_type == SCENE_MAIN_MENU || next_type == SCENE_MENU) {
        sfSound_stop(glb->game_music->sound);
    }
}

scene_t *manage_scene(scene_type_t *current_type, scene_type_t next_type,
    scene_t *current_scene, global_t *glb)
{
    if (*current_type != next_type) {
        manage_game_music(next_type, glb);
        if (current_scene && current_scene->destroy)
            current_scene->destroy(glb);
        if (current_scene)
            free(current_scene);
        current_scene = handle_type(next_type);
        if (current_scene && current_scene->init)
            current_scene->init(glb);
        *current_type = next_type;
    }
    return current_scene;
}
