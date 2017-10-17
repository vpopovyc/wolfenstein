/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:47:39 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/16 14:47:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ENEMIES_H
# define __ENEMIES_H

# include "../vector_types.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

/*
** Max number of enemies on one stage
*/

# define MAX_NUMBER_ENEMIES		16
# define ENEMIES_INFO_COLUMNS	10

/*
** Enemy types that can be used
*/

typedef enum        e_enemy_types
{
    officer = 0
}                   t_enemytypes;

/*
** Infile data position
*/

typedef enum        e_parse_indexes
{
    pos_x = 1,
    pos_y = 3,
    dir_x = 5, 
    dir_y = 7,
    texture = 9
}                   t_parse_indexes;

/*
** Enemy entry
*/

typedef struct	s_enemy
{
	t_double2	pos;
	t_double2	dir;
	uint32_t	texture_index;
}				t_enemy;

#endif