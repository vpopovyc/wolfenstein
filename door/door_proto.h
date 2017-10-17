/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_proto.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 21:25:42 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/20 21:25:43 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DOOR_PROTO_H
# define __DOOR_PROTO_H

typedef struct s_draw_world t_draw_world;

t_door	*get_door(signed char mode, size_t info);

void	get_door_from_file(t_door *door, size_t info);

void    fill_texture_to_draw(uint32_t *ref, uint32_t *to_draw, int start_pos);

char	open_door(t_game *myGame, t_door *door, int map[][map_width]);

void    set_doors_on_map(t_door *door, int map[map_height][map_width]);

int 	find_door(t_int2 map, t_door *door);

int   	parse_doors_stack(t_draw_world *worldrender, t_appcore *appcore);

#endif