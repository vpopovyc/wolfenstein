/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 20:50:25 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/18 13:54:21 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_managment.h"
#include "stack.h"
#include "s_context.h"
#include "ray_info.h"
#include "ray_on_map.h"
#include "dda.h"
#include "draw_world.h"
#include "door/door_proto.h"
#include "sounds/sounds.h"

/*
** predicate to decide if tile is walkable
** add enumeration for tyles types
*/

static inline T_BOOL	pred(int map_tile)
{
	if (map_tile == 0)
		return (1);
	return (0);
}

/*
** all defines defined in event_managment.h
** VLM - volume in space in world
** MVSPD - move speed
** s – means sing, defines two fts beahaviours - moving forward or backward
*/

static inline void		vert_move(t_game *my_game, int map[][map_width],
													signed char s)
{
	t_int2		pos;
	t_double2	barrier;

	barrier.x = (my_game->dir.x > 0) ? VLM : -VLM;
	barrier.y = (my_game->dir.y > 0) ? VLM : -VLM;
	pos.x = my_game->pos.x + barrier.x * s + my_game->dir.x * MVSPD * s;
	pos.y = my_game->pos.y;
	if (pred(map[pos.x][pos.y])
	&& pred(map[pos.x][(int)(my_game->pos.y + VLM)])
	&& pred(map[pos.x][(int)(my_game->pos.y - VLM)]))
		my_game->pos.x += my_game->dir.x * MVSPD * s;
	pos.x = my_game->pos.x;
	pos.y = my_game->pos.y + barrier.y * s + my_game->dir.y * MVSPD * s;
	if (pred(map[pos.x][pos.y])
	&& pred(map[(int)(my_game->pos.x + VLM)][pos.y])
	&& pred(map[(int)(my_game->pos.x - VLM)][pos.y]))
		my_game->pos.y += my_game->dir.y * MVSPD * s;
}

/*
** all defines defined in event_managment.h
** PCOSRT || PSINRT is positive cos() or sin() of rotation speed(RTSPD)
** NCOSRT || NSINRT is negative cos() or sin() of rotation speed(RTSPD)
** s – means sing, defines two fts beahaviours - rotating left or right
*/

static inline void		horz_move(t_game *my_game, signed char s)
{
	static double	old_dir_x;
	static double	old_plane_x;
	t_double2		trig;

	trig.x = (s == 1) ? NCOSRT : PCOSRT;
	trig.y = (s == 1) ? NSINRT : PSINRT;
	old_dir_x = my_game->dir.x;
	my_game->dir.x = my_game->dir.x * trig.x - my_game->dir.y * trig.y;
	my_game->dir.y = old_dir_x * trig.y + my_game->dir.y * trig.x;
	old_plane_x = my_game->plane.x;
	my_game->plane.x = my_game->plane.x * trig.x - my_game->plane.y * trig.y;
	my_game->plane.y = old_plane_x * trig.y + my_game->plane.y * trig.x;
}

/*
** all defines defined in event_managment.h
** ft to capture mouse motion
** defines a bounds that mouse must trigger to rotate view
** calls horz_move()
*/

static inline void		mouse_move(t_game *my_game, t_sdl2_tools *sdl)
{
	double mouse_x;

	mouse_x = sdl->event.motion.x;
	if (mouse_x > UPBOUND || mouse_x < LWBOUND)
	{
		SDL_WarpMouseInWindow(sdl->window, HFWIDTH, HFHEIGTH);
		if (mouse_x > HFWIDTH)
			horz_move(my_game, 1);
		else
			horz_move(my_game, -1);
	}
}

/*
** entry point to manage all events
*/

void					event_managment(register t_game *my_game,
										register t_sdl2_tools *sdl,
										t_door *door,
										int world_map[][map_width])
{
	uint8_t		*keystate;
	static char	status;

	keystate = (unsigned char *)SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&sdl->event);
	if ((sdl->event.type == SDL_QUIT) || keystate[SDL_SCANCODE_ESCAPE])
		exit(0);
	if (keystate[SDL_SCANCODE_D])
		horz_move(my_game, 1);
	if (keystate[SDL_SCANCODE_A])
		horz_move(my_game, -1);
	if (keystate[SDL_SCANCODE_W])
		vert_move(my_game, world_map, 1);
	if (keystate[SDL_SCANCODE_S])
		vert_move(my_game, world_map, -1);
	if (sdl->event.type == SDL_MOUSEMOTION)
		mouse_move(my_game, sdl);
	if (keystate[SDL_SCANCODE_O] || status)
		status = open_door(my_game, door, world_map);
	ps_managment(&sdl->event, my_game, keystate);
}
