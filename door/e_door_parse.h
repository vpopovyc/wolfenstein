/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_door_parse.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 19:07:30 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/24 19:07:31 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __E_DOOR_PARSE_H
# define __E_DOOR_PARSE_H

/*
** Infile data position
*/

typedef	enum		e_door_indexes
{
	x = 1,
	y = 3,
	status = 5,
	texture = 7
}					t_door_indexes;

#endif
