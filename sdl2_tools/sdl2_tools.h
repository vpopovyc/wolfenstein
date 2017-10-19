/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:40:05 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/19 21:40:12 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SDL2_TOOLS_H
# define __SDL2_TOOLS_H

# include <SDL2/SDL.h>
# include "../app_base.h"

/*
** Struct to keep all needed data together
*/

typedef	struct		s_sdl2_tools
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	SDL_Event		event;
	uint32_t		*pixels;
	int				color;
}					t_sdl2_tools;

/*
** Function that initializes t_sdl2_struct
** Modifiable due requirements
*/

t_sdl2_tools		*sdl2_init(const uint x, const uint y);

/*
** Function to free all allocated memory
** Modifiable due requirements
*/

void				sdl2_release(t_sdl2_tools *my_sdl2);

/*
** Paints vertical line
*/

void				sdl2_plot_ver_line(t_sdl2_tools *my_sdl2, int x,
																int y1,
																int y2);

/*
** Light one pixel
*/

void				sdl2_put_pixel(t_sdl2_tools *my_sdl2, int color, int x,
																	int y);

#endif
