/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 20:18:05 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/24 20:18:09 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_H
# define __STACK_H

# include "s_context.h"
# include <stdlib.h>

typedef	struct				s_stack_elem
{
	struct s_stack_elem		*top_elem;
	struct s_stack_elem		*bot_elem;
	t_context				context;
}							t_stack_elem;

typedef	struct				s_stack
{
	struct s_stack_elem		*top_node;
	struct s_stack_elem		*bot_node;
}							t_stack;

/*
** stack.c
*/

void						stack_init(t_stack *stack);
void						push(t_stack *stack, t_context context);
void						pop(t_stack *stack);
t_context					top(t_stack stack);
int							stack_size(t_stack *stack);

#endif
