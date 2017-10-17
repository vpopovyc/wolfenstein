/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventManagment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 20:50:25 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/18 13:54:21 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "eventManagment.h"
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

static inline t_bool	pred(int mapTile)
{
	if (mapTile == 0)
		return (1);
	return (0);
}

/*
** all defines defined in eventManagment.h
** VLM - volume in space in world
** MVSPD - move speed
** s – means sing, defines two fts beahaviours - moving forward or backward
*/

static inline void		vertMove(t_game *myGame, int map[][map_width], signed char s)
{
	t_int2 		pos;
	t_double2	barrier;

	barrier.x = (myGame->dir.x > 0) ? VLM : -VLM;
	barrier.y = (myGame->dir.y > 0) ? VLM : -VLM;
	pos.x = myGame->pos.x + barrier.x * s + myGame->dir.x * MVSPD * s;
	pos.y = myGame->pos.y;
	if(pred(map[pos.x][pos.y]) 
	&& pred(map[pos.x][(int)(myGame->pos.y + VLM)]) 
	&& pred(map[pos.x][(int)(myGame->pos.y - VLM)]))
		myGame->pos.x += myGame->dir.x * MVSPD * s;
	pos.x = myGame->pos.x;
	pos.y = myGame->pos.y + barrier.y * s + myGame->dir.y * MVSPD * s;
	if(pred(map[pos.x][pos.y]) 
	&& pred(map[(int)(myGame->pos.x + VLM)][pos.y]) 
	&& pred(map[(int)(myGame->pos.x - VLM)][pos.y]))
		myGame->pos.y += myGame->dir.y * MVSPD * s;
}

/*
** all defines defined in eventManagment.h
** PCOSRT || PSINRT is positive cos() or sin() of rotation speed(RTSPD)
** NCOSRT || NSINRT is negative cos() or sin() of rotation speed(RTSPD)
** s – means sing, defines two fts beahaviours - rotating left or right
*/

static inline void 		horzMove(t_game *myGame, signed char s)
{
    static double 	oldDirX;
	static double 	oldPlaneX;
	t_double2 		trig;

	trig.x = (s == 1) ? NCOSRT : PCOSRT;
	trig.y = (s == 1) ? NSINRT : PSINRT;
    oldDirX = myGame->dir.x;
    myGame->dir.x = myGame->dir.x * trig.x - myGame->dir.y * trig.y;
    myGame->dir.y = oldDirX * trig.y + myGame->dir.y * trig.x;
    oldPlaneX = myGame->plane.x;
    myGame->plane.x = myGame->plane.x * trig.x - myGame->plane.y * trig.y;
	myGame->plane.y = oldPlaneX * trig.y + myGame->plane.y * trig.x;
}

/*
** all defines defined in eventManagment.h
** ft to capture mouse motion
** defines a bounds that mouse must trigger to rotate view
** calls horzMove() 
*/

static inline void		mouseMove(t_game *myGame, t_sdl2_tools *mySDL2)
{
	double mouseX;

	mouseX = mySDL2->event.motion.x;
	if (mouseX > UPBOUND || mouseX < LWBOUND) 
	{
		SDL_WarpMouseInWindow(mySDL2->window, HFWIDTH, HFHEIGTH);
		if (mouseX > HFWIDTH)
			horzMove(myGame, 1);
		else
			horzMove(myGame, -1);
	}
}

/*
** manages all events related to parcticle system(ps)
*/

static inline void		ps_managment(register SDL_Event *event, register t_game *myGame, uint8_t *keystate)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (keystate[SDL_SCANCODE_UP] && keystate[SDL_SCANCODE_LSHIFT])
			myGame->ps_density += myGame->ps_density + 1 < 256 ? 2 : 0;;
		if (keystate[SDL_SCANCODE_DOWN] && keystate[SDL_SCANCODE_LSHIFT])
			myGame->ps_density -= myGame->ps_density - 1 >= 0 ? 1 : 0;
	}
}

/*
** entry point to manage all events
*/

void	eventManagment(register t_game *myGame, register t_sdl2_tools *mySDL2, t_door *door, int worldMap[][map_width])
{
	uint8_t 	*keystate;
	static char status;

	keystate = (unsigned char *)SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&mySDL2->event);
    if ((mySDL2->event.type == SDL_QUIT) || keystate[SDL_SCANCODE_ESCAPE])
        exit(0);
    if (keystate[SDL_SCANCODE_D])
    	horzMove(myGame, 1);
    if (keystate[SDL_SCANCODE_A])
    	horzMove(myGame, -1);
    if (keystate[SDL_SCANCODE_W])
		vertMove(myGame, worldMap, 1);
    if (keystate[SDL_SCANCODE_S])
		vertMove(myGame, worldMap, -1);
	if (mySDL2->event.type == SDL_MOUSEMOTION)
		mouseMove(myGame, mySDL2);
    if (keystate[SDL_SCANCODE_O] || status)
		status = open_door(myGame, door, worldMap);
	ps_managment(&mySDL2->event, myGame, keystate);
}