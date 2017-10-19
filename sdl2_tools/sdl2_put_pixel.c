/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2_put_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:33:23 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/19 21:33:24 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl2_tools.h"

void	sdl2_put_pixel(t_sdl2_tools *my_sdl2, int color, int x, int y)
{
	my_sdl2->pixels[y * WWIDTH + x] = color;
}
