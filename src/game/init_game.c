/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** init_game.c
*/

#include "wolf.h"

void init_vertex(global_t *glb)
{
    glb->image = sfImage_createFromFile("assets/textures/floor_texture.jpg");
    glb->wall_image = sfImage_createFromFile("assets/textures/"
        "wall_texture.jpg");
    glb->ceiling_image = sfImage_createFromFile("assets/textures/"
        "ceiling_texture.jpg");
    if (glb->wall_image) {
        glb->texture = sfTexture_createFromImage(glb->wall_image, NULL);
        sfTexture_setSmooth(glb->texture, sfFalse);
    }
    if (glb->image)
        glb->floor_texture = sfTexture_createFromImage(glb->image, NULL);
    if (glb->ceiling_image)
        glb->ceiling_texture = sfTexture_createFromImage(glb->ceiling_image,
            NULL);
    glb->fc_shader = sfShader_createFromFile(NULL, NULL,
        "assets/shaders/floor_ceiling.frag");
    glb->wall_shader = sfShader_createFromFile(NULL, NULL,
        "assets/shaders/wall.frag");
}

static void init_arrays_and_particles(global_t *glb)
{
    glb->wall_array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(glb->wall_array, sfLines);
    sfVertexArray_resize(glb->wall_array, NUM_RAYS * 2);
    for (int i = 0; i < MAX_PARTICLES; i++)
        glb->game->particles[i].active = 0;
}

static void set_init_weapons(global_t *glb)
{
    glb->game->cooldown = sfClock_create();
    glb->game->shoot_info.is_shoting = false;
    glb->game->shoot_info.reload = false;
    glb->game->shoot_info.cur_weapon_type = MP5;
    glb->game->shoot_info.shoting_delay = 0;
    glb->game->shoot_info.reload_delay = 0;
    if (glb->game->inventory) {
        glb->game->inventory->indexes[MEDKIT] = KNIFE;
        glb->game->inventory->cur_ammunation[MEDKIT] = 0;
    }
}

int init_variables(global_t *glb)
{
    glb->game->clock = sfClock_create();
    glb->game->rt = sfRenderTexture_create(SCREEN_WIDTH, SCREEN_HEIGHT,
        sfFalse);
    if (!glb->game->cooldown || !glb->game->clock)
        return ERROR;
    glb->game->shoot_info.is_shoting = false;
    glb->game->shoot_info.reload = false;
    glb->game->shoot_info.cur_weapon_type = MP5;
    glb->game->shoot_info.shoting_delay = 0;
    glb->game->shoot_info.reload_delay = 0;
    glb->game->z_buffer = malloc(sizeof(float) * SCREEN_WIDTH);
    if (!glb->valid_file)
        glb->map = map_generator(MAP_HEIGHT, MAP_WIDTH);
    else
        glb->valid_file = false;
    init_minimap(glb);
    return SUCCESS;
}

static void init_game_over_menu(global_t *glb)
{
    sfColor white = sfWhite;
    sfColor red = sfRed;

    glb->game->game_over_fade = 0.0f;
    glb->game->game_over_title = set_text(&red, &(sfVector2f){710.f, 290.f},
        &(text_info_t){"assets/font/Branda-yolq.ttf", "YOU DIED", 120});
    glb->game->game_over_restart = set_text(&white, &(sfVector2f){850.f, 540.f},
        &(text_info_t){"assets/font/Branda-yolq.ttf", "Restart", 70});
    glb->game->game_over_menu = set_text(&white, &(sfVector2f){710.f, 690.f},
        &(text_info_t){"assets/font/Branda-yolq.ttf", "Return to Menu", 70});
}

static void init_pause_menu(global_t *glb)
{
    sfColor white = sfWhite;

    glb->game->paused = false;
    glb->game->in_settings = false;
    glb->game->pause_title = set_text(&white, &(sfVector2f){840.f, 290.f},
        &(text_info_t){"assets/font/Branda-yolq.ttf", "PAUSE", 100});
    glb->game->pause_resume = set_text(&white, &(sfVector2f){850.f, 440.f},
        &(text_info_t){"assets/font/Branda-yolq.ttf", "Resume", 70});
    glb->game->save_text = set_text(&white, &(sfVector2f){900.f, 540.f},
        &(text_info_t){"assets/font/Branda-yolq.ttf", "Save", 70});
    glb->game->pause_settings = set_text(&white, &(sfVector2f){855.f, 640.f},
        &(text_info_t){"assets/font/Branda-yolq.ttf", "Options", 70});
    glb->game->pause_main_menu = set_text(&white, &(sfVector2f){700.f, 740.f},
        &(text_info_t){"assets/font/Branda-yolq.ttf",
            "Return to main menu", 70});
    glb->game->pause_bg = sfRectangleShape_create();
    sfRectangleShape_setSize(glb->game->pause_bg,
        (sfVector2f){1920.f, 1080.f});
    sfRectangleShape_setFillColor(glb->game->pause_bg,
        (sfColor){0, 0, 0, 150});
}

static void init_utils_game(global_t *glb)
{
    init_vertex(glb);
    init_arrays_and_particles(glb);
    init_shaders(glb);
    init_enemies(glb, &glb->game->enemies, &glb->game->enemy_count, glb->map);
    spawn_random_items(glb);
    init_game_over_menu(glb);
    init_pause_menu(glb);
    init_hud(glb);
    glb->lighter_active = false;
    glb->lighter_sprite = set_sprite("assets/sprites/lighter.png",
        &(sfVector2f){0.9f, 0.9f}, NULL,
        &(sfVector2f){(SCREEN_WIDTH / 2.0f) - 150.0f, SCREEN_HEIGHT - 200.0f});
    glb->lighter_clock = sfClock_create();
}

static void init_cpy_map(global_t *glb)
{
    glb->copy_map = malloc(glb->map_height * sizeof(int *));
    for (int i = 0; i < glb->map_height; i++) {
        glb->copy_map[i] = malloc(glb->map_width * sizeof(int));
        for (int j = 0; j < glb->map_width; j++) {
            glb->copy_map[i][j] = glb->map[i][j];
        }
    }
}

void init_game(global_t *glb)
{
    glb->game = malloc(sizeof(game_t));
    if (!glb->game)
        return;
    memset(glb->game, 0, sizeof(game_t));
    glb->fade_alpha = 255;
    sfRenderWindow_setMouseCursorVisible(glb->window, false);
    init_player(&glb->player);
    init_weapons(glb->window, &glb->game->weapon);
    init_inventory(&glb->game->inventory);
    init_shop(&glb->game->shop);
    set_init_weapons(glb);
    if (!glb->game->weapon || !glb->game->cooldown)
        return;
    init_items(&glb->game->items);
    if (!glb->game->items.ping_sound || !glb->game->items.pick_up_sound)
        return;
    if (init_variables(glb) == ERROR)
        return;
    init_utils_game(glb);
    init_cpy_map(glb);
}
