/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 17:06:46 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/18 12:09:09 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GAME_H
# define __GAME_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include "game_proto.h"

/*
** App base info
*/

# include "../app_core.h"

/*
** Vector types
*/

# include "../vector_types.h"

/*
** libft.h
*/

# include "../libft/libft.h"

/*
** enum for parsing
*/

typedef	enum		e_map_parsing
{
	first,
	last = map_width - 1,
	info_columns = 4
}					t_map_parsing;

typedef	struct		s_world_map
{
	int				world_map[map_width][map_height];
}					t_world_map;

/*
** Struct that holds games identy
*/

typedef	struct		s_game
{
	t_double2		pos;
	t_double2		dir;
	t_double2		plane;
	t_double2		time;
	double			*z_buffer;
	t_world_map		*map;
	int				ps_density;
}					t_game;

#endif
