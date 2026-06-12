/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** wolf.c
*/

#include "wolf.h"
#include "input.h"

static void get_fps(fps_t *fps, sfRenderWindow *window)
{
    if (!fps || !window || !fps->clock)
        return;
    fps->time = sfClock_getElapsedTime(fps->clock);
    fps->second = sfTime_asSeconds(fps->time);
    fps->fps = (int)(1.0f / fps->second);
    sfClock_restart(fps->clock);
    sprintf(fps->title, "Patient Zero | FPS: %d", fps->fps);
    sfRenderWindow_setTitle(window, fps->title);
}

static void manage_cinematic(global_t *glb, scene_type_t *next_type)
{
    if (glb->end_cinematic) {
        if (glb->daughter_caught || glb->daughter_killed) {
            *next_type = SCENE_MAIN_MENU;
            glb->daughter_caught = false;
            glb->daughter_killed = false;
        } else {
            *next_type = SCENE_GAME;
        }
        glb->end_cinematic = false;
    }
    if (glb->start_cinematic) {
        *next_type = SCENE_CINEMATIC;
        glb->start_cinematic = false;
        glb->fade_alpha = 0;
        glb->cinematic_step = 0;
        glb->text_index = 0;
    }
}

static void draw_frame(scene_t *current_scene, global_t *glb)
{
    float second = sfTime_asSeconds(sfClock_getElapsedTime(glb->render_clock));

    if (second > 0.01) {
        sfRenderWindow_clear(glb->window, sfBlack);
        if (current_scene->draw)
            current_scene->draw(glb->window, glb);
        sfClock_restart(glb->render_clock);
    }
}

static scene_t *handle_frame(scene_t *current_scene, global_t *glb,
    scene_type_t *current_type, scene_type_t *next_type)
{
    if (!current_scene || !glb)
        return current_scene;
    while (sfRenderWindow_pollEvent(glb->window, &glb->event)) {
        manage_event(glb->window, next_type, current_scene, glb);
    }
    if (current_scene->update)
        current_scene->update(glb, &glb->event);
    manage_cinematic(glb, next_type);
    current_scene = manage_scene(current_type, *next_type, current_scene,
        glb);
    draw_frame(current_scene, glb);
    sfRenderWindow_display(glb->window);
    return current_scene;
}

void game_loop(scene_t *current_scene, global_t *glb)
{
    scene_type_t current_type = SCENE_MENU;
    scene_type_t next_type = current_type;
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(glb->window)) {
        get_fps(&glb->fps, glb->window);
        glb->dt = sfTime_asSeconds(sfClock_restart(clock));
        current_scene = handle_frame(current_scene, glb, &current_type,
            &next_type);
        if (!current_scene)
            break;
    }
    sfClock_destroy(clock);
    if (current_scene && current_scene->destroy)
        current_scene->destroy(glb);
    if (current_scene)
        free(current_scene);
}

static void set_up_var(global_t *glb)
{
    glb->map_width = 41;
    glb->map_height = 41;
    glb->texture = NULL;
    glb->sprite = NULL;
    glb->image = NULL;
    glb->game = NULL;
    glb->wall_array = NULL;
    glb->end_cinematic = false;
    glb->cinematic_step = 0;
    glb->fade_alpha = 0;
    glb->volume = 50;
    glb->is_fullscreen = true;
    glb->valid_file = false;
    glb->instruction = NULL;
    glb->mouse_sens = 1.0f;
    glb->headbobbing = true;
    glb->fps_limit = 120;
}

static void set_up_glb(global_t *glb)
{
    memset(glb, 0, sizeof(global_t));
    set_up_var(glb);
    load_settings(glb);
    glb->window = create_window(glb->is_fullscreen);
    glb->render_clock = sfClock_create();
    glb->fps.clock = sfClock_create();
    init_input(glb);
    sfListener_setGlobalVolume(glb->volume);
    glb->menu_sound = set_sound("assets/sounds/ping.mp3", 100);
    glb->game_music = set_sound("assets/sounds/Cannibal Village Redux.mp3",
        10.0f);
    if (glb->game_music && glb->game_music->sound)
        sfSound_setLoop(glb->game_music->sound, sfTrue);
}

int main(int ac, char **av, char **env)
{
    scene_t *current_scene;
    global_t glb;

    if (ac == 2 && (strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0)) {
        print_usage();
        return SUCCESS;
    }
    current_scene = create_menu_scene();
    if (manage_env(env) == ERROR)
        return ERROR;
    set_up_glb(&glb);
    if (!glb.window || !current_scene || !glb.ipt)
        return ERROR;
    sfRenderWindow_setFramerateLimit(glb.window, glb.fps_limit);
    if (current_scene->init)
        current_scene->init(&glb);
    game_loop(current_scene, &glb);
    destroy_all(&glb);
    return SUCCESS;
}
