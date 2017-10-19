/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 20:20:13 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/19 12:52:37 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

/*
** Inner loop for sprite drawing
** Goes through all sprite y's
*/

static inline void    block_four(t_sdl2_tools *mySDL2, t_sprite_draw *draw, uint32_t **myTexture, int x)
{
    t_int2  tex;
    int     y;
    int     d;
    int     color;
    int     textureID;

    y = draw->start.y;
    tex.x = ((x - draw->presc.y) * draw->presc.x) >> 8;
    textureID = draw->texture_index + SPRITE_INDX;
    while (y < draw->end.y)
    {
        d = (y << 8) - (WHEIGTH << 7)  + (draw->dim << 7);
        tex.y = ((d << 7) / draw->dim) >> 8;
        color = myTexture[textureID][(int)(tex.y << 7) + tex.x];
        if ((color & 0x00FFFFFF) != 0)
            sdl2_put_pixel(mySDL2, color, x, y);
        ++y;
    }
}

/*
** Outer loop for sprite drawing
** Goes through all sprite x's
*/

static inline void    block_three(t_sdl2_tools *mySDL2, t_sprite_draw *draw, double *z_buffer, uint32_t **myTexture)
{
    int     x;

    x = draw->start.x;
    while (x < draw->end.x)
    {
        if (draw->size > 0 && x > 0 && x < WWIDTH && draw->size < z_buffer[x])
            block_four(mySDL2, draw, myTexture, x);
        ++x;
    }
}

/*
** Sets start and end points for sprite drawing 
*/

static inline void    block_two(t_int2 *start, t_int2 *end, int screen_x, int sprite_dim)
{
    start->y = -sprite_dim + (WHEIGTH >> 1);
    if (start->y < 0)
        start->y = 0;
    end->y = sprite_dim + (WHEIGTH >> 1);
    if (end->y >= WHEIGTH)
        end->y = (WHEIGTH - 1);
    start->x = -sprite_dim + screen_x;
    if (start->x < 0)
        start->x = 0;
    end->x = sprite_dim + screen_x;
    if (end->x >= WWIDTH)
        end->x = WWIDTH - 1;
}

/*
** Gets size of sprite on screen
*/

static inline void    block_one(t_game *myGame, t_sprite *sprite, int *screen_x, double *size)
{
    t_float2    pos;
    t_double2   transform;
    double      inv_det;

    pos.x = sprite->pos.x - myGame->pos.x;
    pos.y = sprite->pos.y - myGame->pos.y;
    inv_det = 1.0 / (myGame->plane.x * myGame->dir.y - myGame->dir.x * myGame->plane.y);
    transform.x = inv_det * (myGame->dir.y * pos.x - myGame->dir.x * pos.y);
    transform.y = inv_det * (-myGame->plane.y * pos.x + myGame->plane.x * pos.y);
    *screen_x = (int)((WWIDTH >> 1) * (1 + transform.x / transform.y));
    *size = transform.y;
}

/*
** Entry point for sprite rendering 
*/

void    draw_sprites(t_game *myGame, t_sdl2_tools *mySDL2, t_sprite_container *mySprite, uint32_t **myTexture)
{
    int             i;
    int             screen_x;
    t_sprite        *sprite;
    t_sprite_draw   draw;

    i = 0;
    sprite = mySprite->container;
    while (i < mySprite->count)
    {
        draw.texture_index = sprite[i].texture_index;
        block_one(myGame, &sprite[i], &screen_x, &draw.size);
        draw.dim = abs((int)(WHEIGTH / draw.size));
        block_two(&draw.start, &draw.end, screen_x, draw.dim >> 1);
        draw.presc.x = (1 << 15) / draw.dim;
        draw.presc.y = -(draw.dim >> 1) + screen_x;
        block_three(mySDL2, &draw, myGame->z_buffer, myTexture);
        ++i;
    }
}            
        