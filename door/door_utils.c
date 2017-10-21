/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 14:16:24 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/30 14:16:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "door.h"
#include "../app_base.h"
#include "../vector_types.h"
#include "../stack.h"
#include "../s_context.h"
#include "../ray_info.h"
#include "../ray_on_map.h"
#include "../dda.h"
#include "../draw_world.h"

int		find_door(t_int2 map, t_door *door)
{
	int	i;

	i = 0;
	while (i < MAX_DOORS_NUMBER)
	{
		if (door[i].pos.x == map.x && door[i].pos.y == map.y)
			return (i);
		++i;
	}
	return (-1);
}

void	set_doors_on_map(t_door *door, int map[map_height][map_width])
{
	int i;

	i = 0;
	while (i < MAX_DOORS_NUMBER)
	{
		if (!door[i].pos.x && !door[i].pos.y)
			return ;
		map[door[i].pos.x][door[i].pos.y] = DOORS_INDX + door[i].texture_index;
		++i;
	}
}

void	fill_texture_to_draw(uint32_t *ref, uint32_t *to_draw, int start_pos)
{
	int i;
	int j;

	i = 0;
	while (i < start_pos)
	{
		j = 0;
		while (j < tex_height)
			to_draw[i + tex_height * j++] = 0xff000000;
		++i;
	}
	i = 0;
	while (start_pos < tex_height)
	{
		j = 0;
		while (j < tex_height)
		{
			to_draw[start_pos + tex_height * j] = ref[i + tex_height * j];
			++j;
		}
		++start_pos;
		++i;
	}
}

int		parse_doors_stack(t_draw_world *worldrender, t_appcore *appcore)
{
	t_context	context;
	int			door_id;
	int			texture_id;

	context = top(worldrender->dda->doors_stack);
	worldrender->dda->side = context.side;
	worldrender->ray->map = context.map;
	door_id = context.door_id;
	pop(&(worldrender->dda->doors_stack));
	texture_id = appcore->door[door_id].texture_index + DOORS_INDX;
	fill_texture_to_draw(appcore->myTexture[texture_id],
						appcore->door[door_id].texture_draw,
						appcore->door[door_id].draw_stripe);
	return (door_id);
}
