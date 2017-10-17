/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2_plotVerLine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 19:10:22 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/10 18:59:11 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "sdl2_tools.h"

void                sdl2_plotVerLine(t_sdl2_tools *my_sdl2, int x, int y1, int y2, int color)
{
	uint32_t *pixels;

	pixels = my_sdl2->pixels;
    while (y1 != y2)
    {
    	pixels[y1 * 800 + x] = color;
        ++y1;
    }
}