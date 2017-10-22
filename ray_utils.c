/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 19:51:56 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/30 19:51:59 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_types.h"
#include "ray_info.h"
#include "ray_on_map.h"
#include "game/game.h"

static inline float		square_root(float value)
{
	float result;

	__asm__	(
		"flds %1;"
		"fsqrt;"
		"fstps %0;" : "=g" (result) : "g" (value)
	);
	return (result);
}

void					set_ray_data(t_ray_info *ray, t_appcore *appcore,
																	int x)
{
	ray->cam_x = (x << 1) / (double)WWIDTH - 1;
	ray->pos.x = appcore->my_game->pos.x;
	ray->pos.y = appcore->my_game->pos.y;
	ray->dir.x = appcore->my_game->dir.x +
				appcore->my_game->plane.x * ray->cam_x;
	ray->dir.y = appcore->my_game->dir.y +
				appcore->my_game->plane.y * ray->cam_x;
	ray->map.x = (int)ray->pos.x;
	ray->map.y = (int)ray->pos.y;
	ray->delta_dist.x = square_root(1 + (ray->dir.y * ray->dir.y) /
										(ray->dir.x * ray->dir.x));
	ray->delta_dist.y = square_root(1 + (ray->dir.x * ray->dir.x) /
										(ray->dir.y * ray->dir.y));
}

void					map_ray_to_world(t_ray_info *ray, t_ray_on_map *mapray)
{
	mapray->step.x = (ray->dir.x < 0) ? -1 : 1;
	mapray->step.y = (ray->dir.y < 0) ? -1 : 1;
	mapray->side_dist.x = (ray->dir.x < 0) ?
						(ray->pos.x - ray->map.x) * ray->delta_dist.x :
						(ray->map.x + 1.0 - ray->pos.x) * ray->delta_dist.x;
	mapray->side_dist.y = (ray->dir.y < 0) ?
						(ray->pos.y - ray->map.y) * ray->delta_dist.y :
						(ray->map.y + 1.0 - ray->pos.y) * ray->delta_dist.y;
}
