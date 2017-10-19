/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_on_map.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 20:44:51 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/30 20:44:52 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __RAY_ON_MAP
# define __RAY_ON_MAP

typedef struct 	s_ray_on_map
{
    t_int2      step;
    t_double2   side_dist;
}				t_ray_on_map;

#endif
