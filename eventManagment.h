/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventManagment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 20:56:08 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/18 13:54:07 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __EVENTMANAGMENT_H
# define __EVENTMANAGMENT_H

# include "door/door.h"
# include "sdl2_tools/sdl2_tools.h"

/*
** Move speed
*/

# define MVSPD		(0.300042)

/*
** Rotation constants
*/

# define RTSPD		(0.1)
# define PSINRT		sin(RTSPD)
# define NSINRT		sin(-RTSPD)
# define PCOSRT		cos(RTSPD)
# define NCOSRT		cos(-RTSPD)

/*
** Volume
*/

# define VLM		(0.1)

/*
** Bounds for mouse
*/

# define HFWIDTH	(WWIDTH / 2)
# define HFHEIGTH	(WHEIGTH / 2)
# define UPBOUND	(HFWIDTH + 8)
# define LWBOUND	(HFWIDTH - 8)

typedef struct		s_mouse	
{
	t_int2			pos;
	double			rotY;
}					t_mouse;

void				eventManagment(t_game *myGame, t_sdl2_tools *mySDL2, t_door *door, int worldMap[][map_width]);

#endif
