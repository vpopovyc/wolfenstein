/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enemies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:47:25 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/16 14:47:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemies.h"
#include "enemies_proto.h"

/*
** gets data from server that represents all sprites on current lvl
*/

static inline void		get_enemies_from_server(t_enemy *enemies)
{
	(void)enemies;
}

/*
** primary routine to get data about enemies
*/

t_enemy					*get_enemies(signed char mode, size_t info)
{
	t_enemy *enemies;

	enemies = malloc(sizeof(t_enemy) * MAX_NUMBER_ENEMIES);
	ft_memset(enemies, 0, sizeof(t_enemy) * MAX_NUMBER_ENEMIES);
	if (mode == 1)
		get_enemies_from_server(enemies);
	else
		get_enemies_from_file(enemies, info);
	return (enemies);
}
