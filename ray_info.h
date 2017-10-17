/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_info.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 18:37:06 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/30 18:38:28 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RAY_INFO_H
# define __RAY_INFO_H

typedef struct 	s_ray_info
{
    t_double2   pos;
    t_double2   dir;
    t_double2   delta_dist;
    double      cam_x;
    t_int2      map;
}				t_ray_info;

#endif
