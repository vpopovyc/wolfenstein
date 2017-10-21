/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 16:31:00 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/18 13:58:34 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_game	*get_game(signed char mode, size_t info)
{
	t_game *new_game;

	new_game = malloc(sizeof(t_game));
	ft_memset(new_game, 0, sizeof(t_game));
	new_game->z_buffer = malloc(sizeof(double) * WWIDTH);
	ft_memset(new_game->z_buffer, 0, sizeof(double) * WWIDTH);
	new_game->dir.x = -1;
	new_game->dir.y = 0;
	new_game->plane.x = 0;
	new_game->plane.y = 0.66;
	new_game->ps_density = 1;
	if (mode == multy_player)
		get_game_from_server(new_game);
	else
		get_game_from_file(new_game, info);
	return (new_game);
}
