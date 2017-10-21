/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 21:00:49 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/20 21:00:50 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"
#include "door_proto.h"

static inline void		get_door_from_server(t_door *d_array)
{
	(void)d_array;
}

t_door					*get_door(signed char mode, size_t info)
{
	t_door *d_array;

	d_array = malloc(sizeof(t_door) * MAX_DOORS_NUMBER);
	ft_memset(d_array, '\0', sizeof(t_door) * MAX_DOORS_NUMBER);
	if (mode == 1)
		get_door_from_server(d_array);
	else
		get_door_from_file(d_array, info);
	return (d_array);
}
