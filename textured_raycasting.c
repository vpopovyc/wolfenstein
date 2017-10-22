/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_ray->asting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 16:51:39 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/19 18:52:52 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sounds/sounds.h"
#include <pthread.h>

void	render_frame(t_appcore *a, t_draw_world *wrender,
										register int x,
										register int xmax)
{
	register int	door_id;

	x = wrender->render_range.x;
	xmax = wrender->render_range.y;
	procced_ps(a);
	while (x < xmax)
	{
		set_ray_data(wrender->ray, a, x);
		map_ray_to_world(wrender->ray, wrender->mapped_ray);
		run_dda(wrender->ray, wrender->mapped_ray, wrender->dda, a);
		if (wrender->dda->hit == 1 || wrender->dda->door_hit)
			draw_world(a, wrender, x, 0);
		if (wrender->dda->hit == 2 || wrender->dda->door_hit)
		{
			while (stack_size(&(wrender->dda->doors_stack)))
			{
				door_id = parse_doors_stack(wrender, a);
				draw_world(a, wrender, x, door_id + 1);
			}
		}
		++x;
	}
	sort_sprites(a->my_sprites, a->my_game->pos);
	draw_sprites(a->my_game, a->sdl, a->my_sprites, a->my_texture);
	draw_ps(&a->ps_thread, a->sdl);
}

void	engine_execute(t_engine *engine)
{
	register t_appcore		*a;
	register t_draw_world	*w;

	a = &engine->appcore;
	w = &engine->worldrender;
	while (1)
	{
		SDL_UpdateTexture(a->sdl->texture, NULL, a->sdl->pixels,
													WWIDTH * sizeof(uint32_t));
		set_render_range(w, 0, WWIDTH);
		render_frame(a, w, 0, 0);
		SDL_RenderClear(a->sdl->renderer);
		SDL_RenderCopy(a->sdl->renderer, a->sdl->texture, NULL, NULL);
		SDL_RenderPresent(a->sdl->renderer);
		a->my_game->time.y = a->my_game->time.x;
		a->my_game->time.x = SDL_GetTicks();
		event_managment(a->my_game, a->sdl, a->door, a->my_map);
	}
}

void	*music_thread_init(void *args)
{
	(void)args;
	while (1)
		sound(OK);
	pthread_exit(NULL);
}

void	turn_on_music(void)
{
	pthread_t music_thread;

	pthread_create(&music_thread, NULL, music_thread_init, NULL);
	pthread_detach(music_thread);
}

int		main(void)
{
	time_t		t;
	t_engine	engine;

	srand((unsigned)time(&t));
	turn_on_music();
	create_engine(&engine);
	engine_execute(&engine);
	sdl2_release(engine.appcore.sdl);
	return (0);
}
