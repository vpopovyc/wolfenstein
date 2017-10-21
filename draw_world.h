/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 15:41:50 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/01 15:41:51 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DRAW_WORLD_H
# define __DRAW_WORLD_H

typedef	struct		s_draw_world
{
	t_ray_info		*ray;
	t_ray_on_map	*mapped_ray;
	t_dda			*dda;
	t_int2			render_range;
}					t_draw_world;

typedef struct		s_draw_world_info
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	t_int2			tex;
	int				d;
	int				x;
	uint32_t		color;
}					t_draw_world_info;

#endif
