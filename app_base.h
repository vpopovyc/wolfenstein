/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_core.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 16:33:29 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/19 11:24:01 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __APP_BASE_H
# define __APP_BASE_H

# define t_bool     unsigned char

# define WHEIGTH    600
# define WWIDTH     800

/*
** Texture resolution
** World shapes
*/

typedef enum 		e_globals
{
	single_player = 0,
	multy_player = 1,
	map_width = 24,
	map_height = 24,
	tex_height = 128,
	tex_width = 128
}					t_globals;

# include <stdint.h>
# include <pthread.h>

typedef struct s_door t_door;
typedef struct s_game t_game;
typedef struct s_sdl2_tools t_sdl2_tools;
typedef struct s_sprite_container t_sprite_container;
typedef struct s_enemy t_enemy;

typedef struct 			s_appcore 
{
    t_sdl2_tools        *mySDL2;
    t_game              *myGame;
    t_sprite_container  *mySprites;
    t_door              *door;
    t_enemy             *enemies;
    uint32_t            **myTexture;
    pthread_t			ps_thread;
    int                 myMap[map_height][map_width];
}						t_appcore;


#endif
