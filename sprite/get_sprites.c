/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:13:07 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 16:49:49 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"
#include "sprite_proto.h"

/*
** gets data from server that represents all sprites on current lvl
*/

static inline void    get_sprites_from_server(t_sprite_container *sprites)
{
    (void)sprites;
}


/*
** primary routine to get data about sprites
*/

t_sprite_container    *get_sprites(signed char mode, size_t info)
{
    t_sprite_container *sprites;

    sprites = malloc(sizeof(t_sprite_container));
    ft_memset(sprites, 0, sizeof(t_sprite_container));
    if (mode == 1)
        get_sprites_from_server(sprites);
    else
        get_sprites_from_file(sprites, info);
    return (sprites);
}
