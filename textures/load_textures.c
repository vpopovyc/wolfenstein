/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:30:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/19 12:59:43 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

static void		load_doors_textures(uint32_t **tex_array)
{
	uint32_t		width[MAX_DOORS];
	uint32_t		heigth[MAX_DOORS];
	unsigned char	*texture[MAX_DOORS];
	int				i;

	ft_memset(texture, 0, MAX_DOORS);
	lodepng_decode32_file(&texture[0], &width[0], &heigth[0], DOOR_PATH_1);
	i = 0;
	while (i < MAX_DOORS && texture[i])
	{
		tex_array[i + DOORS_INDX] = (uint32_t*)texture[i];
		++i;
	}
}

static void		load_sprite_textures(uint32_t **tex_array)
{
	uint32_t		width[MAX_SPRITE];
	uint32_t		heigth[MAX_SPRITE];
	unsigned char	*texture[MAX_SPRITE];
	int				i;

	ft_memset(texture, 0, MAX_SPRITE);
	lodepng_decode32_file(&texture[0], &width[0], &heigth[0], OBJ_PATH_1);
	i = 0;
	while (i < MAX_SPRITE && texture[i])
	{
		tex_array[i + SPRITE_INDX] = (uint32_t*)texture[i];
		++i;
	}
}

static void		load_world_textures(uint32_t **tex_array)
{
	uint32_t		width[MAX_WALLS];
	uint32_t		heigth[MAX_WALLS];
	unsigned char	*texture[MAX_WALLS];
	int				i;

	ft_memset(texture, 0, MAX_WALLS);
	lodepng_decode32_file(&texture[0], &width[0], &heigth[0], WALL_PATH_1);
	lodepng_decode32_file(&texture[1], &width[1], &heigth[1], WALL_PATH_2);
	lodepng_decode32_file(&texture[2], &width[2], &heigth[2], WALL_PATH_3);
	lodepng_decode32_file(&texture[3], &width[3], &heigth[3], WALL_PATH_4);
	i = 0;
	while (i < MAX_WALLS && texture[i])
	{
		tex_array[i + WALLS_INDX] = (uint32_t*)texture[i];
		++i;
	}
}

static void		load_enemy_textures(uint32_t **tex_array)
{
	uint32_t		width[MAX_ENEMY];
	uint32_t		heigth[MAX_ENEMY];
	unsigned char	*texture[MAX_ENEMY];
	int				i;

	ft_memset(texture, 0, MAX_ENEMY);
	lodepng_decode32_file(&texture[0], &width[0], &heigth[0], ENEM_PATH_1_1);
	lodepng_decode32_file(&texture[1], &width[1], &heigth[1], ENEM_PATH_1_2);
	lodepng_decode32_file(&texture[2], &width[2], &heigth[2], ENEM_PATH_1_3);
	lodepng_decode32_file(&texture[3], &width[3], &heigth[3], ENEM_PATH_1_4);
	i = 0;
	while (i < MAX_ENEMY && texture[i])
	{
		tex_array[i + ENEMY_INDX] = (uint32_t*)texture[i];
		++i;
	}
}

/*
** Loads all scpecified textures in memory
*/

uint32_t		**load_textures(void)
{
	uint32_t **tex_array;

	tex_array = malloc(sizeof(uint32_t*) * MAX_TEX_NUMBER);
	ft_memset(tex_array, 0, sizeof(uint32_t*) * MAX_TEX_NUMBER);
	load_world_textures(tex_array);
	load_sprite_textures(tex_array);
	load_doors_textures(tex_array);
	load_enemy_textures(tex_array);
	return (tex_array);
}
