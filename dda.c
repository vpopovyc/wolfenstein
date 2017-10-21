/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 20:44:14 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/30 20:44:28 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "game/game.h"
#include "ray_info.h"
#include "ray_on_map.h"
#include "textures/texture.h"
#include "door/door_proto.h"
#include "door/door.h"
#include "dda.h"

static inline void	x_move(t_ray_info *ray, t_ray_on_map *maped_ray, t_dda *dda)
{
	maped_ray->side_dist.x += ray->delta_dist.x;
	ray->map.x += maped_ray->step.x;
	dda->side = 0;
}

static inline void	y_move(t_ray_info *ray, t_ray_on_map *maped_ray, t_dda *dda)
{
	maped_ray->side_dist.y += ray->delta_dist.y;
	ray->map.y += maped_ray->step.y;
	dda->side = 1;
}

static inline void	door_hit(t_ray_info *ray, t_dda *dda, t_appcore *appcore)
{
	t_context new;

	new.map = ray->map;
	new.side = dda->side;
	new.door_id = find_door(ray->map, appcore->door);
	if (new.door_id == -1)
		perror("FATAL");
	if (stack_size(&(dda->doors_stack)) == 0)
		appcore->door[new.door_id].is_nearest = 1;
	if (appcore->door[new.door_id].is_active)
		dda->door_hit = 1;
	if (appcore->door[new.door_id].is_open == 0 &&
		!appcore->door[new.door_id].is_active)
		dda->hit = 2;
	push(&(dda->doors_stack), new);
}

void				run_dda(t_ray_info *ray, t_ray_on_map *mapped_ray,
											t_dda *dda, t_appcore *appcore)
{
	dda->hit = 0;
	dda->door_hit = 0;
	stack_init(&(dda->doors_stack));
	while (dda->hit == 0)
	{
		if (mapped_ray->side_dist.x < mapped_ray->side_dist.y)
			x_move(ray, mapped_ray, dda);
		else
			y_move(ray, mapped_ray, dda);
		if (appcore->my_map[ray->map.x][ray->map.y] >= DOORS_INDX &&
			appcore->my_map[ray->map.x][ray->map.y] < ENEMY_INDX)
		{
			door_hit(ray, dda, appcore);
		}
		else if (appcore->my_map[ray->map.x][ray->map.y] > 0)
		{
			dda->hit = 1;
		}
	}
}
