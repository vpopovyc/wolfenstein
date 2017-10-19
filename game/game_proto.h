/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_proto.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:07:43 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/18 12:09:48 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __GAME_PROTO_H
# define __GAME_PROTO_H

typedef struct s_game t_game;

t_game 	 *get_game(signed char mode, size_t info);
void	 get_game_from_file(t_game *game, size_t info);
void	 get_game_from_server(t_game *game);
#endif