/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_context.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 20:06:44 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/24 20:06:47 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __S_CONTEXT_H
# define __S_CONTEXT_H


# include "vector_types.h"

typedef struct 	s_context t_context;

typedef struct 	s_context
{
    t_int2      map;
    int 		side;
    int 		door_id;
}				t_context;

#endif