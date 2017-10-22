/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 13:54:36 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/22 13:54:39 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	set_render_range(t_draw_world *worldrender, int xmin, int xmax)
{
	worldrender->render_range.x = xmin;
	worldrender->render_range.y = xmax;
}

void	create_appcore(t_appcore *appcore)
{
	appcore->my_game = get_game(single_player, 1);
	ft_memcpy(appcore->my_map, appcore->my_game->map->world_map,
										map_height * map_width * sizeof(int));
	appcore->sdl = sdl2_init(WWIDTH, WHEIGTH);
	appcore->my_sprites = get_sprites(single_player, 1);
	appcore->my_texture = load_textures();
	appcore->door = get_door(single_player, 1);
	set_doors_on_map(appcore->door, appcore->my_map);
	appcore->enemies = get_enemies(single_player, 1);
}

void	create_worldrender(t_draw_world *worldrender)
{
	worldrender->ray = malloc(sizeof(t_ray_info));
	worldrender->mapped_ray = malloc(sizeof(t_ray_on_map));
	worldrender->dda = malloc(sizeof(t_dda));
}

void	create_engine(t_engine *engine)
{
	t_appcore		appcore;
	t_draw_world	worldrender;

	create_appcore(&appcore);
	create_worldrender(&worldrender);
	engine->appcore = appcore;
	engine->worldrender = worldrender;
}
