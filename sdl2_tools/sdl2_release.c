/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2_release.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 12:23:26 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/08/13 14:36:33 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl2_tools.h"

/*
** Function to free all allocated memory
** Modifiable due requirements
*/

void    sdl2_release(t_sdl2_tools *my_sdl2)
{
    SDL_DestroyRenderer(my_sdl2->renderer);
    SDL_DestroyWindow(my_sdl2->window);
    my_sdl2->renderer = NULL;
    my_sdl2->window = NULL;
    free(my_sdl2);
}