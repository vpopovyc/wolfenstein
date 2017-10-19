/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:44:45 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/08/13 14:35:54 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl2_tools.h"

/*
** Function that initializes t_sdl2_tools struct by getting pointer to it
** and implicitly defining each field
** x && y needed to define window height && width respectively
** Modifiable due requirements
*/

t_sdl2_tools	*sdl2_init(const uint x, const uint y)
{
	t_sdl2_tools *my_sdl2;

	my_sdl2 = malloc(sizeof(t_sdl2_tools));
	SDL_Init(SDL_INIT_EVERYTHING);
	my_sdl2->window = SDL_CreateWindow("wolfenstein",
										SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED,
										x,
										y,
										0);
	my_sdl2->renderer = SDL_CreateRenderer(my_sdl2->window, -1,
													SDL_RENDERER_ACCELERATED);
	my_sdl2->texture = SDL_CreateTexture(my_sdl2->renderer,
													SDL_PIXELFORMAT_ABGR8888,
													SDL_TEXTUREACCESS_STREAMING,
													x,
													y);
	my_sdl2->pixels = malloc(sizeof(uint32_t) * x * y);
	memset(my_sdl2->pixels, 0, sizeof(uint32_t) * x * y);
	SDL_ShowCursor(SDL_DISABLE);
	return (my_sdl2);
}
