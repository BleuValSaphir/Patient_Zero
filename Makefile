##
## EPITECH PROJECT, 2025
## wolf3D
## File description:
## Makefile
##

SRC = 	src/wolf.c \
		src/engine.c \
		src/menu/handle_menu_event.c \
		src/menu/init_menu.c \
		src/menu/menu.c \
		src/menu/update_menu.c \
		src/menu/scene_menu.c \
		src/main_menu/handle_main_menu_event.c \
		src/main_menu/init_main_menu.c \
		src/main_menu/main_menu.c \
		src/main_menu/update_main_menu.c \
		src/main_menu/scene_main_menu.c \
		src/settings/init_settings.c \
		src/settings/scene_settings.c \
		src/settings/render_settings.c \
		src/settings/handle_settings_event.c \
		src/settings/update_settings.c \
		src/settings/config.c \
		src/load/init_load.c \
		src/load/render_load.c \
		src/load/scene_load.c \
		src/load/handle_load_event.c \
		src/load/load.c \
		src/load/check_prerequisite_map.c \
		src/cinematic/init_cinematic.c \
		src/cinematic/render_cinematic.c \
		src/cinematic/scene_cinematic.c \
		src/cinematic/handle_cinematic_event.c \
		src/cinematic/update_cinematic.c \
		src/game/handle_game_event.c \
		src/game/init_game.c \
		src/game/game.c \
		src/game/scene_game.c \
		src/game/render_game.c \
		src/game/render_floor_ceiling.c \
		src/game/update_game.c \
		src/game/game_over.c \
		src/game/player/player.c \
		src/game/player/shooting_player.c \
		src/game/particules/particules.c \
		src/game/enemies/daughter.c \
		src/game/enemies/enemy.c \
		src/game/enemies/init_enemies.c \
		src/game/enemies/check_enemy_player.c \
		src/game/enemies/draw_enemy.c \
		src/game/enemies/update_ennemies.c \
		src/game/raycasting/raycasting.c \
		src/game/weapons/weapons.c \
		src/game/weapons/update_weapons.c \
		src/game/inventory/inventory.c \
		src/game/mapping/mapping.c \
		src/game/mapping/map_rooms.c \
		src/game/items/items.c \
		src/game/items/update_item.c \
		src/game/items/render_items.c \
		src/game/hud/init_hud.c \
		src/game/hud/render_hud.c \
		src/game/minimap/minimap.c \
		src/game/minimap/init_minimap.c \
		src/game/hud/update_hud.c \
		src/game/shop/shop.c \
		src/game/shop/render_shop.c \
		src/game/shop/destroy_shop.c \
		src/game/shop/handle_shop_event.c \
		src/game/shop/get_gun.c \
		src/game/shop/get_MP.c \
		src/game/shop/get_special.c \
		src/game/shop/handle_article_price.c \
		src/game/shaders/shaders.c \
		src/game/shaders/render_shaders.c \
		src/game/shaders/update_vignette.c \
		src/save/saving.c \
		src/save/init_save.c \
		src/save/render_save.c \
		src/save/scene_save.c \
		src/input/input.c \
		src/utils/utils.c \
		src/utils/print_usage.c \
		src/utils/check_args.c \
		src/utils/destroy_menu.c \
		src/utils/destroy_main_menu.c \
		src/utils/destroy_game.c \
		src/utils/destroy_settings.c \
		src/utils/destroy_cinematic.c \
		src/utils/destroy_load.c \
		src/utils/destroy_save.c \
		src/utils/sound.c \
		src/utils/sprite.c \
		src/utils/circle.c \
		src/utils/rectangle.c \
		src/utils/font_text.c \
		src/utils/hover_anim.c \
		src/utils/resize_window.c \
		src/utils/handle_txt_click.c \
		src/utils/ending_destroy.c \
		src/utils/create_window.c \
		src/utils/create_pop_up.c 

BIN = bin/

SRC_PATH = $(BIN)src

OBJ = $(patsubst src/%.c,$(SRC_PATH)/%.o,$(SRC))

INCLUDE_DIRS = 	src \
				src/game \
				src/game/player \
				src/game/enemies \
				src/game/particules \
				src/game/raycasting \
				src/game/shop \
				src/game/weapons \
				src/game/inventory \
				src/game/mapping \
				src/game/items \
				src/game/minimap \
				src/game/shaders \
				src/save \
				src/main_menu \
				src/menu \
				src/settings \
				src/load \
				src/input \
				src/cinematic \
				src/game/hud \
				src/utils

INC_FLAGS = $(foreach d, $(INCLUDE_DIRS), -I$d)

CFLAGS = $(INC_FLAGS)

LDFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

CC = epiclang

MAIN = wolf3d

COLOR_BLUE = \033[34m
COLOR_GREEN = \033[32m
END_COLOR = \033[0m

all: $(BIN) $(MAIN)

$(MAIN): $(OBJ)
	@printf "$(COLOR_GREEN)[COMPILED] SRC COMPILED$(END_COLOR)\n"
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(MAIN)

$(SRC_PATH)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@printf '$(COLOR_BLUE)[CC]	$(notdir $<)$(END_COLOR)\n'
	@$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	@mkdir -p $@

clean:
	@$(RM) -rf $(BIN)

fclean: clean
	@$(RM) $(MAIN)

re: fclean all

check_repo:
	@banana-check-repo .

fast: 
	$(MAKE) CC=gcc CFLAGS="$(CFLAGS) -O0" && ./$(MAIN)

refast: fclean fast

.PHONY: all clean fclean re check_repo fast refast