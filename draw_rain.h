/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rain.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 19:44:21 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/15 19:44:23 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DRAW_RAIN_H
# define __DRAW_RAIN_H

# include "engine.h"

# define NODE_SIZE 16
# define MAX_NODES 64

typedef	struct	s_part
{
	t_int2		pos;
	uint32_t	color;
}				t_part;

/*
** Plotnikov Sergey
*/

typedef	struct	s_ps
{
	t_part		*parts;
	struct s_ps	*next;
}				t_ps;

void			procced_ps(t_appcore *appcore);
void			draw_ps(pthread_t *ps_thread, t_sdl2_tools *sdl);
void			*next_ps_iter(void *arg);
void			render_ps(t_ps *ps, t_sdl2_tools *sdl);

#endif
