/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 12:13:26 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/19 12:54:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SPRITE_H
# define __SPRITE_H

# include "../vector_types.h"
# include "../libft/libft.h"
# include "../game/game.h"
# include "../sdl2_tools/sdl2_tools.h"
# include "../textures/texture.h"
# include <stdio.h>
# include <fcntl.h>

/*
** Max number of sprites on map
*/

# define SPRITEINFO_COLUMNS 6
# define MAX_SPRITES_NUMBER 32

/*
** Sprite types that can be used
*/

typedef enum        e_sprite_types
{
    barrel = 0
}                   t_sprite_types;

/*
** Infile data position
*/

typedef enum        e_parse_indexes
{
    x = 1,
    y = 3,
    texture = 5
}                   t_parse_indexes;

/*
** Holds all data needed for sprite drawing
*/

typedef struct      s_sprite_draw
{
    t_int2          start;
    t_int2          end;
    double          size;
    int             dim;
    int             texture_index;
    t_int2          presc;
}                   t_sprite_draw;

/*
** Base sprite-entry struct
*/

typedef struct      s_sprite
{
    t_float2        pos;
    float           distance;
    int             texture_index;
}                   t_sprite;

typedef struct      s_sprite_container
{
    int             count;
    t_sprite        container[MAX_SPRITES_NUMBER];
}                   t_sprite_container;

#endif