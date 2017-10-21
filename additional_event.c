/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 21:58:55 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/21 21:58:57 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_managment.h"

/*
** manages all events related to parcticle system(ps)
*/

void		ps_managment(register SDL_Event *event,
								register t_game *my_game, uint8_t *keystate)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (keystate[SDL_SCANCODE_UP] && keystate[SDL_SCANCODE_LSHIFT])
			my_game->ps_density += my_game->ps_density + 1 < 256 ? 2 : 0;
		if (keystate[SDL_SCANCODE_DOWN] && keystate[SDL_SCANCODE_LSHIFT])
			my_game->ps_density -= my_game->ps_density - 1 >= 0 ? 1 : 0;
	}
}
