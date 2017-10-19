/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_proto.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:40:18 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/10/16 15:40:21 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ENEMIES_PROTO_H
# define __ENEMIES_PROTO_H

/*
** Get enemies based on file specified
*/

void		get_enemies_from_file(t_enemy *enemies, size_t info);

/*
** primary routine to get data about enemies
*/

t_enemy		*get_enemies(signed char mode, size_t info);

#endif
