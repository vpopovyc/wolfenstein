/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 21:10:25 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/25 21:10:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../s_context.h"
#include "door.h"
#include "door_proto.h"

static inline int		find_closest_door(t_door *door)
{
	int i;

	i = 0;
	while (i < MAX_DOORS_NUMBER)
	{
		if (door[i].is_nearest)
		{
			door[i].is_nearest = !door[i].is_nearest;
			return (i);
		}
		++i;
	}
	return (-1);
}

char					open_door(t_game *my_game, t_door *door,
													int map[][map_width])
{
	int					d;
	static signed char	status;

	d = find_closest_door(door);
	if ((d != -1 && door[d].dist < 1.5) || status)
	{
		if (d == -1)
			d = status - 1;
		else
			status = d + 1;
		door[d].is_active = 1;
		door[d].draw_stripe += door[d].draw_stripe + 1 <= 128 ? 1 : 0;
		door[d].is_active = door[d].draw_stripe == 128 ? 0 : door[d].is_active;
		door[d].is_open = door[d].draw_stripe == 128 ? 1 : 0;
		if (door[d].is_open == 1)
		{
			map[door[d].pos.x][door[d].pos.y] = 0;
			door[d].time.x = my_game->time.x;
			door[d].time.y = my_game->time.x + 5000;
			status = 0;
			return (0);
		}
		return (1);
	}
	return (0);
}
