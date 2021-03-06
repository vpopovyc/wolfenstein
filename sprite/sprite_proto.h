/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_proto.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:35:35 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 20:01:22 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SPRITE_PROTO_H
# define __SPRITE_PROTO_H

/*
** ./sprite/sort_sprites.c
*/

void    			 sort_sprites(t_sprite_container *mySprites, t_double2 pos);

/*
** ./sprite/draw_spites.c
*/

void    			 draw_sprites(t_game *myGame, t_sdl2_tools *mySDL2, t_sprite_container *mySprite, uint32_t **myTexture);

/*
** ./sprite/get_sprites_from_file.c
*/

void                 get_sprites_from_file(t_sprite_container *sprites, size_t info);

/*
** ./sprite/get_sprites.c
*/

t_sprite_container   *get_sprites(signed char mode, size_t info);

#endif