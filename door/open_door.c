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
		if (door[i].isNearest) 
		{
			door[i].isNearest = !door[i].isNearest;
			return (i);
		}
		++i;
	}
	return (-1);
}

char	open_door(t_game *myGame, t_door *door, int map[][map_width])
{
	int 	d;
	static signed char status;

	d = find_closest_door(door);
	printf("event\n");
	if ((d != -1 && door[d].dist < 1.5) || status)
	{
		if (d == -1)
			d = status - 1;
		else
			status = d + 1;
		door[d].isActive = 1;
		door[d].currentStripe += door[d].currentStripe + 1 <= 128  ? 1 : 0;
		if (door[d].currentStripe == 128)
		{
			door[d].isActive = 0;
			door[d].isOpen = 1;
		}
		if (door[d].isOpen == 1)
		{
			map[door[d].pos.x][door[d].pos.y] = 0;
			door[d].time.x = myGame->time.x;
			door[d].time.y = myGame->time.x + 5000;
			status = 0;
			return (0);
		}
		return (1);
	}
	return (0);
}
