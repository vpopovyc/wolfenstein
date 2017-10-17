/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 18:24:36 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 20:04:09 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

/*
** Swaps sprites in array
*/ 

static inline void    sprite_swap(t_sprite *src, t_sprite *dst)
{
    t_sprite    tmp;

    tmp = *src;
    *src = *dst;
    *dst = tmp;
}

/*
** Calculates distance to each sprite depending on viewer position (vx, vy)
*/

static inline void    set_dist(t_sprite *sprite, double vx, double vy, int max)
{
    int i;

    i = 0;
    while (i < max) {
        sprite[i].distance = (vx - sprite[i].pos.x) * (vx - sprite[i].pos.x) +
                             (vy - sprite[i].pos.y) * (vy - sprite[i].pos.y);
        ++i;
    }
}

/*
** Sorts array of sprites according to distance of each sprite 
** to viewer position
*/

static inline void    sprite_sort(t_sprite *sprite, int max)
{
    int i;
    int j;

    j = 0;
    while (j < max)
    {
        i = 0;
        while (i < max) 
        {
            if (sprite[i].distance < sprite[j].distance)
                sprite_swap(&sprite[i], &sprite[j]);
            ++i;
        }
        ++j;
    }
}

void    sort_sprites(t_sprite_container *mySprites, t_double2 pos)
{
    t_sprite *sprite;

    sprite = mySprites->container;
    set_dist(sprite, pos.x, pos.y, mySprites->count);
    sprite_sort(sprite, mySprites->count);
}

