/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 20:45:12 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/30 20:45:14 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DDA_H
# define __DDA_H

typedef	struct	s_dda
{
	t_stack		doors_stack;
	double		perp_wall_dist;
	int			hit;
	int			door_hit;
	int			side;
}				t_dda;

void			run_dda(t_ray_info *ray,
						t_ray_on_map *maped_ray,
						t_dda *dda, t_appcore *appcore);

#endif
