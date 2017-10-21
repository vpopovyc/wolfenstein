/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 21:19:59 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/20 21:20:00 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DOOR_H
# define __DOOR_H

# include "../vector_types.h"
# include "../libft/libft.h"
# include "../game/game.h"
# include "../textures/texture.h"
# include <stdio.h>
# include <fcntl.h>

# define MAX_DOORS_NUMBER 32
# define DOORINFO_COLUMNS 8

/*
** Door types that can be used
*/

typedef	enum		e_door_types
{
	door3 = 0
}					t_door_types;

/*
** Base door-entry struct
*/

typedef	struct		s_door
{
	uint32_t		texture_draw[16384];
	int				texture_index;
	int				draw_stripe;
	t_int2			pos;
	t_int2			time;
	double			dist;
	T_BOOL			is_open;
	T_BOOL			is_active;
	T_BOOL			is_nearest;
}					t_door;

#endif
