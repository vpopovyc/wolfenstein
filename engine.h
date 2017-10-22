/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 18:50:59 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/01 18:51:00 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENGINE_H
# define __ENGINE_H

# include "app_core.h"
# include "game/game.h"
# include "event_managment.h"
# include "vector_types.h"
# include "sdl2_tools/sdl2_tools.h"
# include "sprite/sprite.h"
# include "sprite/sprite_proto.h"
# include "textures/texture.h"
# include "door/door.h"
# include "stack.h"
# include "s_context.h"
# include "ray_info.h"
# include "ray_on_map.h"
# include "dda.h"
# include "draw_world.h"
# include "door/door_proto.h"
# include "draw_rain.h"
# include "enemies/enemies_proto.h"

void				set_ray_data(t_ray_info *ray, t_appcore *appcore, int x);

void				map_ray_to_world(t_ray_info *ray, t_ray_on_map *mapped_ray);

void				draw_world(t_appcore *appcore, t_draw_world *worldrender,
														int x, int door_id);

void				set_render_range(t_draw_world *worldrender, int xmin,
																int xmax);

void				create_appcore(t_appcore *appcore);

void				create_worldrender(t_draw_world *worldrender);

typedef	struct		s_engine
{
	t_appcore		appcore;
	t_draw_world	worldrender;
}					t_engine;

void				create_engine(t_engine *engine);

#endif
