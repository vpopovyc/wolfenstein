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
#include "app_base.h"
#include "door/door.h"

static inline void		draw_wall_stripe(t_appcore *appcore, t_draw_world_info *var, t_dda *dda, t_ray_info *ray)
{
	int texNum;

	texNum = appcore->myMap[ray->map.x][ray->map.y];
    sdl2_plotVerLine(appcore->mySDL2, var->x, 0, var->drawStart, 0xcdcdcd);
    while (var->drawStart < var->drawEnd)
    {
        var->d = (var->drawStart << 8) - (WHEIGTH << 7) + (var->lineHeight << 7);
        var->tex.y = ((var->d * tex_height) / var->lineHeight) >> 8;
        var->color = appcore->myTexture[texNum][tex_height * var->tex.y + var->tex.x];
        var->color = dda->side ? (var->color >> 1) & 8355711 : var->color;
        sdl2_put_pixel(appcore->mySDL2, var->color, var->x, var->drawStart);
        ++var->drawStart;
    }       
    sdl2_plotVerLine(appcore->mySDL2, var->x, var->drawEnd, WHEIGTH, 0x2f2f2f);
    appcore->myGame->z_buffer[var->x] = dda->perp_wall_dist;
}

static inline void      draw_door_stripe(t_appcore *appcore, t_draw_world_info *var, t_dda *dda, int door_id)
{
    sdl2_plotVerLine(appcore->mySDL2, var->x, 0, var->drawStart, 0xcdcdcd);
    while (var->drawStart < var->drawEnd)
    {
        var->d = (var->drawStart << 8) - (WHEIGTH << 7) + (var->lineHeight << 7);
        var->tex.y = ((var->d * tex_height) / var->lineHeight) >> 8;
        var->color = appcore->door[door_id].textureToDraw[tex_height * var->tex.y + var->tex.x];
        var->color = dda->side ? (var->color >> 1) & 8355711 : var->color;
        if ((var->color & 0x00FFFFFF) != 0) 
            sdl2_put_pixel(appcore->mySDL2, var->color, var->x, var->drawStart);
        ++var->drawStart;
    }
    sdl2_plotVerLine(appcore->mySDL2, var->x, var->drawEnd, WHEIGTH, 0x2f2f2f);
    appcore->myGame->z_buffer[var->x] = appcore->myGame->z_buffer[var->x] = dda->perp_wall_dist;;
    appcore->door[door_id].dist = dda->perp_wall_dist;
}

static inline void		get_text_hit_points(t_draw_world_info *var, t_ray_info *ray, t_dda *dda)
{
	var->wallX = dda->side ?
		ray->pos.x + dda->perp_wall_dist * ray->dir.x :
		ray->pos.y + dda->perp_wall_dist * ray->dir.y;
    var->wallX -= floor(var->wallX);
    var->tex.x = (int)(var->wallX * (double)(tex_width));
    if ((dda->side == 0 && ray->dir.x > 0) || (dda->side == 1 && ray->dir.y < 0))
        var->tex.x = tex_width - var->tex.x - 1;
}

static inline void		get_draw_range(t_draw_world_info *var)
{
    var->drawStart = (-var->lineHeight >> 1) + (WHEIGTH >> 1);
	if (var->drawStart < 0)
	    var->drawStart = 0;
	var->drawEnd = (var->lineHeight >> 1) + (WHEIGTH >> 1);
	if (var->drawEnd >= WHEIGTH)
	    var->drawEnd = WHEIGTH - 1;
}

void    draw_world(t_appcore *appcore, t_draw_world *worldrender, int x, int door_id)
{
    t_ray_info          *ray;
    t_ray_on_map        *mapped_ray;
    t_dda               *dda;
    t_draw_world_info   var;

	ray = worldrender->ray;
	mapped_ray = worldrender->mapped_ray;
	dda = worldrender->dda;
	dda->perp_wall_dist = dda->side ? 
	(ray->map.y - ray->pos.y + (1 - mapped_ray->step.y) / 2) / ray->dir.y :
	(ray->map.x - ray->pos.x + (1 - mapped_ray->step.x) / 2) / ray->dir.x;
	var.lineHeight = (WHEIGTH / dda->perp_wall_dist);
	var.x = x;
	get_draw_range(&var);
	get_text_hit_points(&var, ray, dda);
	if (door_id == 0)
		draw_wall_stripe(appcore, &var, dda, ray);
	else
		draw_door_stripe(appcore, &var, dda, door_id - 1);
}
