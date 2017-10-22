# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/10 18:32:39 by vpopovyc          #+#    #+#              #
#    Updated: 2017/09/28 18:47:24 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = wolf3d

SDL2_SRC := sdl2_tools/sdl2_initialize.c sdl2_tools/sdl2_release.c \
			sdl2_tools/sdl2_plot_ver_line.c sdl2_tools/sdl2_put_pixel.c

SPRITE_SRC := sprite/get_sprites.c sprite/get_sprites_from_file.c \
				sprite/sort_sprites.c sprite/draw_sprites.c

ENEMY_SRC := enemies/get_enemies.c enemies/get_enemies_from_file.c

DOOR_SRC := door/get_door.c door/get_door_from_file.c door/door_utils.c \
			door/open_door.c

GAME_INIT_SRC := game/get_game.c game/get_game_from_file.c \
					game/get_game_from_server.c

LOAD_TEXT := textures/load_textures.c

SOUND_SRC := sounds/sounds.c

GAME_ENGINE_SRC := textured_raycasting.c event_managment.c additional_event.c \
	stack.c ray_utils.c dda.c draw_world.c draw_rain.c rain.c create_engine.c

SRC += $(SDL2_SRC) $(SPRITE_SRC) $(GAME_ENGINE_SRC) $(GAME_INIT_SRC) \
			$(LOAD_TEXT) $(DOOR_SRC) $(SOUND_SRC) $(ENEMY_SRC)

OBJ = $(SRC:.c=.o)

CC = clang

HEADER = -I game.h sdl2_tools/sdl2_tools.h lodepng/lodepng.h libft/libft.h

CCFLAGS = -Wall -Wextra -Werror

FRAMEWORKS = -F ~/Library/Frameworks -framework SDL2

SDLHEADER = -F ~/Library/Frameworks  \
				-I ~/Library/Frameworks/SDL2.framework/Headers/ 

LIBS = lodepng/lodepng.a libft/libft.a

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $(FRAMEWORKS) $(SDLHEADER) $(OBJ) $(LIBS) -o $(EXEC)

%.o: %.c
	$(CC) -g $(CCFLAGS) $(SDLHEADER) -c -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(EXEC)

re: fclean all

.phony: all clean fclean re
