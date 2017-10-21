/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 15:00:25 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/01 15:00:26 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game/game.h"
#include "stack.h"
#include "ray_on_map.h"
#include "ray_info.h"
#include "dda.h"
#include <math.h>
#include "sdl2_tools/sdl2_tools.h"
#include "draw_world.h"
#include "app_core.h"
#include "door/door.h"

static inline void		draw_wall_stripe(t_appcore *apc, t_draw_world_info *v,
													t_dda *dda, t_ray_info *ray)
{
	int t;

	t = apc->my_map[ray->map.x][ray->map.y];
	apc->sdl->color = 0xcdcdcd;
	sdl2_plot_ver_line(apc->sdl, v->x, 0, v->draw_start);
	while (v->draw_start < v->draw_end)
	{
		v->d = (v->draw_start << 8) - (WHEIGTH << 7) + (v->line_height << 7);
		v->tex.y = ((v->d * tex_height) / v->line_height) >> 8;
		v->color = apc->my_texture[t][tex_height * v->tex.y + v->tex.x];
		v->color = dda->side ? (v->color >> 1) & 8355711 : v->color;
		sdl2_put_pixel(apc->sdl, v->color, v->x, v->draw_start);
		++v->draw_start;
	}
	apc->sdl->color = 0x2f2f2f;
	sdl2_plot_ver_line(apc->sdl, v->x, v->draw_end, WHEIGTH);
	apc->my_game->z_buffer[v->x] = dda->perp_wall_dist;
}

static inline void		draw_door_stripe(t_appcore *apc, t_draw_world_info *v,
													t_dda *dda, int door_id)
{
	apc->sdl->color = 0xcdcdcd;
	sdl2_plot_ver_line(apc->sdl, v->x, 0, v->draw_start);
	while (v->draw_start < v->draw_end)
	{
		v->d = (v->draw_start << 8) - (WHEIGTH << 7) + (v->line_height << 7);
		v->tex.y = ((v->d * tex_height) / v->line_height) >> 8;
		v->color = apc->door[door_id].texture_draw[tex_height *
													v->tex.y + v->tex.x];
		v->color = dda->side ? (v->color >> 1) & 8355711 : v->color;
		if ((v->color & 0x00FFFFFF) != 0)
			sdl2_put_pixel(apc->sdl, v->color, v->x, v->draw_start);
		++v->draw_start;
	}
	apc->sdl->color = 0x2f2f2f;
	sdl2_plot_ver_line(apc->sdl, v->x, v->draw_end, WHEIGTH);
	apc->my_game->z_buffer[v->x] = dda->perp_wall_dist;
	apc->door[door_id].dist = dda->perp_wall_dist;
}

static inline void		get_text_hit_points(t_draw_world_info *var,
											t_ray_info *r, t_dda *dda)
{
	var->wall_x = dda->side ?
		r->pos.x + dda->perp_wall_dist * r->dir.x :
		r->pos.y + dda->perp_wall_dist * r->dir.y;
	var->wall_x -= floor(var->wall_x);
	var->tex.x = (int)(var->wall_x * (double)(tex_width));
	if ((dda->side == 0 && r->dir.x > 0) || (dda->side == 1 && r->dir.y < 0))
		var->tex.x = tex_width - var->tex.x - 1;
}

static inline void		get_draw_range(t_draw_world_info *var)
{
	var->draw_start = (-var->line_height >> 1) + (WHEIGTH >> 1);
	if (var->draw_start < 0)
		var->draw_start = 0;
	var->draw_end = (var->line_height >> 1) + (WHEIGTH >> 1);
	if (var->draw_end >= WHEIGTH)
		var->draw_end = WHEIGTH - 1;
}

void					draw_world(t_appcore *appcore,
								t_draw_world *worldrender, int x, int door_id)
{
	t_ray_info			*ray;
	t_ray_on_map		*mapped_ray;
	t_dda				*dda;
	t_draw_world_info	var;

	ray = worldrender->ray;
	mapped_ray = worldrender->mapped_ray;
	dda = worldrender->dda;
	dda->perp_wall_dist = dda->side ?
	(ray->map.y - ray->pos.y + (1 - mapped_ray->step.y) / 2) / ray->dir.y :
	(ray->map.x - ray->pos.x + (1 - mapped_ray->step.x) / 2) / ray->dir.x;
	var.line_height = (WHEIGTH / dda->perp_wall_dist);
	var.x = x;
	get_draw_range(&var);
	get_text_hit_points(&var, ray, dda);
	if (door_id == 0)
		draw_wall_stripe(appcore, &var, dda, ray);
	else
		draw_door_stripe(appcore, &var, dda, door_id - 1);
}
